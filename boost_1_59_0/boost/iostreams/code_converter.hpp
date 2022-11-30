// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains machinery for performing code conversion.

#ifndef BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/detail/config/wide_streams.hpp>
#if defined(BOOST_IOSTREAMS_NO_WIDE_STREAMS) || \
    defined(BOOST_IOSTREAMS_NO_LOCALE) \
    /**/
# error code conversion not supported on this platform
#endif

#include <algorithm>                       // max.
#include <cstring>                         // memcpy.
#include <exception>
#include <boost/config.hpp>                // DEDUCED_TYPENAME, 
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/constants.hpp>   // default_filter_buffer_size.
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/detail/adapter/direct_adapter.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/call_traits.hpp>
#include <boost/iostreams/detail/codecvt_holder.hpp>
#include <boost/iostreams/detail/codecvt_helper.hpp>
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/functional.hpp>
#include <boost/iostreams/detail/ios.hpp> // failure, openmode, int types, streamsize.
#include <boost/iostreams/detail/optional.hpp>
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // Borland 5.x

namespace boost { namespace iostreams {

struct code_conversion_error : BOOST_IOSTREAMS_FAILURE {
    code_conversion_error() 
        : BOOST_IOSTREAMS_FAILURE("code conversion error")
        { }
};

namespace detail {

//--------------Definition of strncpy_if_same---------------------------------//

// Helper template for strncpy_if_same, below.
template<bool B>
struct strncpy_if_same_impl;

template<>
struct strncpy_if_same_impl<true> {
    template<typename Ch>
    static Ch* copy(Ch* tgt, const Ch* src, std::streamsize n)
    { return BOOST_IOSTREAMS_CHAR_TRAITS(Ch)::copy(tgt, src, n); }
};

template<>
struct strncpy_if_same_impl<false> {
    template<typename Src, typename Tgt>
    static Tgt* copy(Tgt* tgt, const Src*, std::streamsize) { return tgt; }
};

template<typename Src, typename Tgt>
Tgt* strncpy_if_same(Tgt* tgt, const Src* src, std::streamsize n)
{
    typedef strncpy_if_same_impl<is_same<Src, Tgt>::value> impl;
    return impl::copy(tgt, src, n);
}

//--------------Definition of conversion_buffer-------------------------------//

// Buffer and conversion state for reading.
template<typename Codecvt, typename Alloc>
class conversion_buffer 
    : public buffer<
                 BOOST_DEDUCED_TYPENAME detail::codecvt_extern<Codecvt>::type,
                 Alloc
             > 
{
public:
    typedef typename Codecvt::state_type state_type;
    conversion_buffer() 
        : buffer<
              BOOST_DEDUCED_TYPENAME detail::codecvt_extern<Codecvt>::type,
              Alloc
          >(0) 
    { 
        reset(); 
    }
    state_type& state() { return state_; }
    void reset() 
    { 
        if (this->size()) 
            this->set(0, 0);
        state_ = state_type(); 
    }
private:
    state_type state_;
};

//--------------Definition of converter_impl----------------------------------//

// Contains member data, open/is_open/close and buffer management functions.
template<typename Device, typename Codecvt, typename Alloc>
struct code_converter_impl {
    typedef typename codecvt_extern<Codecvt>::type          extern_type;
    typedef typename category_of<Device>::type              device_category;
    typedef is_convertible<device_category, input>          can_read;
    typedef is_convertible<device_category, output>         can_write;
    typedef is_convertible<device_category, bidirectional>  is_bidir;
    typedef typename 
            iostreams::select<  // Disambiguation for Tru64.
                is_bidir, bidirectional,
                can_read, input,
                can_write, output
            >::type                                         mode;      
    typedef typename
            mpl::if_<
                is_direct<Device>,
                direct_adapter<Device>,
                Device
            >::type                                         device_type;
    typedef optional< concept_adapter<device_type> >        storage_type;
    typedef is_convertible<device_category, two_sequence>   is_double;
    typedef conversion_buffer<Codecvt, Alloc>               buffer_type;

    code_converter_impl() : cvt_(), flags_(0) { }

    ~code_converter_impl()
    { 
        try { 
            if (flags_ & f_open) close(); 
        } catch (...) { /* */ } 
    }

    template <class T>
    void open(const T& dev, std::streamsize buffer_size)
    {
        if (flags_ & f_open)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("already open"));
        if (buffer_size == -1)
            buffer_size = default_filter_buffer_size;
        std::streamsize max_length = cvt_.get().max_length();
        buffer_size = (std::max)(buffer_size, 2 * max_length);
        if (can_read::value) {
            buf_.first().resize(buffer_size);
            buf_.first().set(0, 0);
        }
        if (can_write::value && !is_double::value) {
            buf_.second().resize(buffer_size);
            buf_.second().set(0, 0);
        }
        dev_.reset(concept_adapter<device_type>(dev));
        flags_ = f_open;
    }

    void close()
    {
        detail::execute_all(
            detail::call_member_close(*this, BOOST_IOS::in),
            detail::call_member_close(*this, BOOST_IOS::out)
        );
    }

    void close(BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::in && (flags_ & f_input_closed) == 0) {
            flags_ |= f_input_closed;
            iostreams::close(dev(), BOOST_IOS::in);
        }
        if (which == BOOST_IOS::out && (flags_ & f_output_closed) == 0) {
            flags_ |= f_output_closed;
            detail::execute_all(
                detail::flush_buffer(buf_.second(), dev(), can_write::value),
                detail::call_close(dev(), BOOST_IOS::out),
                detail::call_reset(dev_),
                detail::call_reset(buf_.first()),
                detail::call_reset(buf_.second())
            );
        }
    }

    bool is_open() const { return (flags_ & f_open) != 0;}

    device_type& dev() { return **dev_; }

    enum flag_type {
        f_open             = 1,
        f_input_closed     = f_open << 1,
        f_output_closed    = f_input_closed << 1
    };

    codecvt_holder<Codecvt>  cvt_;
    storage_type             dev_;
    double_object<
        buffer_type, 
        is_double
    >                        buf_;
    int                      flags_;
};

} // End namespace detail.

//--------------Definition of converter---------------------------------------//

#define BOOST_IOSTREAMS_CONVERTER_PARAMS() , std::streamsize buffer_size = -1
#define BOOST_IOSTREAMS_CONVERTER_ARGS() , buffer_size

template<typename Device, typename Codecvt, typename Alloc>
struct code_converter_base {
    typedef detail::code_converter_impl<
                Device, Codecvt, Alloc
            > impl_type;
    code_converter_base() : pimpl_(new impl_type) { }
    shared_ptr<impl_type> pimpl_;
};

template< typename Device, 
          typename Codecvt = detail::default_codecvt, 
          typename Alloc = std::allocator<char> >
class code_converter 
    : protected code_converter_base<Device, Codecvt, Alloc>
{
private:
    typedef detail::code_converter_impl<
                Device, Codecvt, Alloc
            >                                                       impl_type;
    typedef typename impl_type::device_type                         device_type;
    typedef typename impl_type::buffer_type                         buffer_type;
    typedef typename detail::codecvt_holder<Codecvt>::codecvt_type  codecvt_type;
    typedef typename detail::codecvt_intern<Codecvt>::type          intern_type;
    typedef typename detail::codecvt_extern<Codecvt>::type          extern_type;
    typedef typename detail::codecvt_state<Codecvt>::type           state_type;
public:
    typedef intern_type                                             char_type;    
    struct category 
        : impl_type::mode, device_tag, closable_tag, localizable_tag
        { };
    BOOST_STATIC_ASSERT((
        is_same<
            extern_type, 
            BOOST_DEDUCED_TYPENAME char_type_of<Device>::type
        >::value
    ));
public:
    code_converter() { }
    BOOST_IOSTREAMS_FORWARD( code_converter, open_impl, Device,
                             BOOST_IOSTREAMS_CONVERTER_PARAMS, 
                             BOOST_IOSTREAMS_CONVERTER_ARGS )

        // fstream-like interface.

    bool is_open() const { return this->pimpl_->is_open(); }
    void close(BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
    { impl().close(which); }

        // Device interface.

    std::streamsize read(char_type*, std::streamsize);
    std::streamsize write(const char_type*, std::streamsize);
    void imbue(const std::locale& loc) { impl().cvt_.imbue(loc); }

        // Direct device access.

    Device& operator*() { return detail::unwrap_direct(dev()); }
    Device* operator->() { return &detail::unwrap_direct(dev()); }
private:
    template<typename T> // Used for forwarding.
    void open_impl(const T& t BOOST_IOSTREAMS_CONVERTER_PARAMS()) 
    { 
        impl().open(t BOOST_IOSTREAMS_CONVERTER_ARGS()); 
    }

    const codecvt_type& cvt() { return impl().cvt_.get(); }
    device_type& dev() { return impl().dev(); }
    buffer_type& in() { return impl().buf_.first(); }
    buffer_type& out() { return impl().buf_.second(); }
    impl_type& impl() { return *this->pimpl_; }
};

//--------------Implementation of converter-----------------------------------//

// Implementation note: if end of stream contains a partial character,
// it is ignored.
template<typename Device, typename Codevt, typename Alloc>
std::streamsize code_converter<Device, Codevt, Alloc>::read
    (char_type* s, std::streamsize n)
{
    const extern_type*   next;        // Next external char.
    intern_type*         nint;        // Next internal char.
    std::streamsize      total = 0;   // Characters read.
    int                  status = iostreams::char_traits<char>::good();
    bool                 partial = false;
    buffer_type&         buf = in();

    do {

        // Fill buffer.
        if (buf.ptr() == buf.eptr() || partial) {
            status = buf.fill(dev());
            if (buf.ptr() == buf.eptr())
                break;
            partial = false;
        }

        // Convert.
        std::codecvt_base::result result =
            cvt().in( buf.state(),
                      buf.ptr(), buf.eptr(), next,
                      s + total, s + n, nint );
        buf.ptr() += next - buf.ptr();
        total = static_cast<std::streamsize>(nint - s);

        switch (result) {
        case std::codecvt_base::partial:
            partial = true;
            break;
        case std::codecvt_base::ok:
            break;
        case std::codecvt_base::noconv:
            {
                std::streamsize amt = 
                    std::min<std::streamsize>(next - buf.ptr(), n - total);
                detail::strncpy_if_same(s + total, buf.ptr(), amt);
                total += amt;
            }
            break;
        case std::codecvt_base::error:
        default:
            buf.state() = state_type();
            boost::throw_exception(code_conversion_error());
        }

    } while (total < n && status != EOF && status != WOULD_BLOCK);

    return total == 0 && status == EOF ? -1 : total;
}

template<typename Device, typename Codevt, typename Alloc>
std::streamsize code_converter<Device, Codevt, Alloc>::write
    (const char_type* s, std::streamsize n)
{
    buffer_type&        buf = out();
    extern_type*        next;              // Next external char.
    const intern_type*  nint;              // Next internal char.
    std::streamsize     total = 0;         // Characters written.
    bool                partial = false;

    while (total < n) {

        // Empty buffer.
        if (buf.eptr() == buf.end() || partial) {
            if (!buf.flush(dev()))
                break;
            partial = false;
        }
       
        // Convert.
        std::codecvt_base::result result =
            cvt().out( buf.state(),
                       s + total, s + n, nint,
                       buf.eptr(), buf.end(), next );
        int progress = (int) (next - buf.eptr());
        buf.eptr() += progress;

        switch (result) {
        case std::codecvt_base::partial:
            partial = true;
            BOOST_FALLTHROUGH;
        case std::codecvt_base::ok:
            total = static_cast<std::streamsize>(nint - s);
            break;
        case std::codecvt_base::noconv:
            {
                std::streamsize amt = 
                    std::min<std::streamsize>( nint - total - s, 
                                               buf.end() - buf.eptr() );
                detail::strncpy_if_same(buf.eptr(), s + total, amt);
                total += amt;
            }
            break;
        case std::codecvt_base::error:
        default:
            buf.state() = state_type();
            boost::throw_exception(code_conversion_error());
        }
    }
    return total;
}

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // Borland 5.x

#endif // #ifndef BOOST_IOSTREAMS_CODE_CONVERTER_HPP_INCLUDED

/* code_converter.hpp
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
*/