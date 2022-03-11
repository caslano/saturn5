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