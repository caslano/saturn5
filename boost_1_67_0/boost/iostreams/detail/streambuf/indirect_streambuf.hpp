// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
// See http://www.boost.org/libs/iostreams for documentation.

// This material is heavily indebted to the discussion and code samples in
// A. Langer and K. Kreft, "Standard C++ IOStreams and Locales",
// Addison-Wesley, 2000, pp. 228-43.

// User "GMSB" provided an optimization for small seeks.

#ifndef BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED

#include <algorithm>                             // min, max.
#include <cassert>
#include <exception>
#include <boost/config.hpp>                      // Member template friends.
#include <boost/detail/workaround.hpp>
#include <boost/core/typeinfo.hpp>
#include <boost/iostreams/constants.hpp>
#include <boost/iostreams/detail/adapter/concept_adapter.hpp>
#include <boost/iostreams/detail/buffer.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/double_object.hpp> 
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/detail/optional.hpp>
#include <boost/iostreams/detail/push.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC, BCC 5.x

namespace boost { namespace iostreams { namespace detail {

//
// Description: The implementation of basic_streambuf used by chains.
//
template<typename T, typename Tr, typename Alloc, typename Mode>
class indirect_streambuf
    : public linked_streambuf<BOOST_DEDUCED_TYPENAME char_type_of<T>::type, Tr>
{
public:
    typedef typename char_type_of<T>::type                    char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef typename category_of<T>::type                     category;
    typedef concept_adapter<T>                                wrapper;
    typedef detail::basic_buffer<char_type, Alloc>            buffer_type;
    typedef indirect_streambuf<T, Tr, Alloc, Mode>            my_type;
    typedef detail::linked_streambuf<char_type, traits_type>  base_type;
    typedef linked_streambuf<char_type, Tr>                   streambuf_type;
public:
    indirect_streambuf();

    void open(const T& t BOOST_IOSTREAMS_PUSH_PARAMS());
    bool is_open() const;
    void close();
    bool auto_close() const;
    void set_auto_close(bool close);
    bool strict_sync();

    // Declared in linked_streambuf.
    T* component() { return &*obj(); }
protected:
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)

    //----------virtual functions---------------------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
    void imbue(const std::locale& loc);
#endif
#ifdef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
    public:
#endif
    int_type underflow();
    int_type pbackfail(int_type c);
    int_type overflow(int_type c);
    int sync();
    pos_type seekoff( off_type off, BOOST_IOS::seekdir way,
                      BOOST_IOS::openmode which );
    pos_type seekpos(pos_type sp, BOOST_IOS::openmode which);

    // Declared in linked_streambuf.
    void set_next(streambuf_type* next);
    void close_impl(BOOST_IOS::openmode m);
    const boost::core::typeinfo& component_type() const { return BOOST_CORE_TYPEID(T); }
    void* component_impl() { return component(); }
private:

    //----------Accessor functions--------------------------------------------//

    wrapper& obj() { return *storage_; }
    streambuf_type* next() const { return next_; }
    buffer_type& in() { return buffer_.first(); }
    buffer_type& out() { return buffer_.second(); }
    bool can_read() const { return is_convertible<Mode, input>::value; }
    bool can_write() const { return is_convertible<Mode, output>::value; }
    bool output_buffered() const { return (flags_ & f_output_buffered) != 0; }
    bool shared_buffer() const { return is_convertible<Mode, seekable>::value || is_convertible<Mode, dual_seekable>::value; }
    void set_flags(int f) { flags_ = f; }

    //----------State changing functions--------------------------------------//

    virtual void init_get_area();
    virtual void init_put_area();

    //----------Utility function----------------------------------------------//

    pos_type seek_impl( stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which );
    void sync_impl();

    enum flag_type {
        f_open             = 1,
        f_output_buffered  = f_open << 1,
        f_auto_close       = f_output_buffered << 1
    };

    optional<wrapper>           storage_;
    streambuf_type*             next_;
    double_object<
        buffer_type,
        is_convertible<
            Mode,
            two_sequence
        >
    >                           buffer_;
    std::streamsize             pback_size_;
    int                         flags_;
};

//--------------Implementation of indirect_streambuf--------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
indirect_streambuf<T, Tr, Alloc, Mode>::indirect_streambuf()
    : next_(0), pback_size_(0), flags_(f_auto_close) { }

//--------------Implementation of open, is_open and close---------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::open
    (const T& t, std::streamsize buffer_size, std::streamsize pback_size)
{
    using namespace std;

    // Normalize buffer sizes.
    buffer_size =
        (buffer_size != -1) ?
        buffer_size :
        iostreams::optimal_buffer_size(t);
    pback_size =
        (pback_size != -1) ?
        pback_size :
        default_pback_buffer_size;

    // Construct input buffer.
    if (can_read()) {
        pback_size_ = (std::max)(std::streamsize(2), pback_size); // STLPort needs 2.
        std::streamsize size =
            pback_size_ +
            ( buffer_size ? buffer_size: std::streamsize(1) );
        in().resize(static_cast<int>(size));
        if (!shared_buffer())
            init_get_area();
    }

    // Construct output buffer.
    if (can_write() && !shared_buffer()) {
        if (buffer_size != std::streamsize(0))
            out().resize(static_cast<int>(buffer_size));
        init_put_area();
    }

    storage_.reset(wrapper(t));
    flags_ |= f_open;
    if (can_write() && buffer_size > 1)
        flags_ |= f_output_buffered;
    this->set_true_eof(false);
    this->set_needs_close();
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline bool indirect_streambuf<T, Tr, Alloc, Mode>::is_open() const
{ return (flags_ & f_open) != 0; }

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::close()
{
    using namespace std;
    base_type* self = this;
    detail::execute_all(
        detail::call_member_close(*self, BOOST_IOS::in),
        detail::call_member_close(*self, BOOST_IOS::out),
        detail::call_reset(storage_),
        detail::clear_flags(flags_)
    );
}

template<typename T, typename Tr, typename Alloc, typename Mode>
bool indirect_streambuf<T, Tr, Alloc, Mode>::auto_close() const
{ return (flags_ & f_auto_close) != 0; }

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::set_auto_close(bool close)
{ flags_ = (flags_ & ~f_auto_close) | (close ? f_auto_close : 0); }

//--------------Implementation virtual functions------------------------------//

#ifndef BOOST_IOSTREAMS_NO_LOCALE
template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::imbue(const std::locale& loc)
{
    if (is_open()) {
        obj().imbue(loc);
        if (next_)
            next_->pubimbue(loc);
    }
}
#endif

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::underflow()
{
    using namespace std;
    if (!gptr()) init_get_area();
    buffer_type& buf = in();
    if (gptr() < egptr()) return traits_type::to_int_type(*gptr());

    // Fill putback buffer.
    std::streamsize keep = 
        (std::min)( static_cast<std::streamsize>(gptr() - eback()),
                    pback_size_ );
    if (keep)
        traits_type::move( buf.data() + (pback_size_ - keep),
                           gptr() - keep, keep );

    // Set pointers to reasonable values in case read throws.
    setg( buf.data() + pback_size_ - keep,
          buf.data() + pback_size_,
          buf.data() + pback_size_ );

    // Read from source.
    std::streamsize chars =
        obj().read(buf.data() + pback_size_, buf.size() - pback_size_, next_);
    if (chars == -1) {
        this->set_true_eof(true);
        chars = 0;
    }
    setg(eback(), gptr(), buf.data() + pback_size_ + chars);
    return chars != 0 ?
        traits_type::to_int_type(*gptr()) :
        traits_type::eof();
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::pbackfail(int_type c)
{
    if (gptr() != eback()) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    } else {
        boost::throw_exception(bad_putback());
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::int_type
indirect_streambuf<T, Tr, Alloc, Mode>::overflow(int_type c)
{
    if ( (output_buffered() && pptr() == 0) ||
         (shared_buffer() && gptr() != 0) )
    {
        init_put_area();
    }
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (output_buffered()) {
            if (pptr() == epptr()) {
                sync_impl();
                if (pptr() == epptr())
                    return traits_type::eof();
            }
            *pptr() = traits_type::to_char_type(c);
            pbump(1);
        } else {
            char_type d = traits_type::to_char_type(c);
            if (obj().write(&d, 1, next_) != 1)
                return traits_type::eof();
        }
    }
    return traits_type::not_eof(c);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
int indirect_streambuf<T, Tr, Alloc, Mode>::sync()
{
    try { // sync() is no-throw.
        sync_impl();
        obj().flush(next_);
        return 0;
    } catch (...) { return -1; }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
bool indirect_streambuf<T, Tr, Alloc, Mode>::strict_sync()
{
    try { // sync() is no-throw.
        sync_impl();
        return obj().flush(next_);
    } catch (...) { return false; }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekoff
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return seek_impl(off, way, which); }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seekpos
    (pos_type sp, BOOST_IOS::openmode which)
{ 
    return seek_impl(position_to_offset(sp), BOOST_IOS::beg, which); 
}

template<typename T, typename Tr, typename Alloc, typename Mode>
typename indirect_streambuf<T, Tr, Alloc, Mode>::pos_type
indirect_streambuf<T, Tr, Alloc, Mode>::seek_impl
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{
    if ( gptr() != 0 && way == BOOST_IOS::cur && which == BOOST_IOS::in && 
         eback() - gptr() <= off && off <= egptr() - gptr() ) 
    {   // Small seek optimization
        gbump(static_cast<int>(off));
        return obj().seek(stream_offset(0), BOOST_IOS::cur, BOOST_IOS::in, next_) -
               static_cast<off_type>(egptr() - gptr());
    }
    if (pptr() != 0) 
        this->BOOST_IOSTREAMS_PUBSYNC(); // sync() confuses VisualAge 6.
    if (way == BOOST_IOS::cur && gptr())
        off -= static_cast<off_type>(egptr() - gptr());
    bool two_head = is_convertible<category, dual_seekable>::value ||
                    is_convertible<category, bidirectional_seekable>::value;
    if (two_head) {
        BOOST_IOS::openmode both = BOOST_IOS::in | BOOST_IOS::out;
        if ((which & both) == both)
            boost::throw_exception(bad_seek());
        if (which & BOOST_IOS::in) {
            setg(0, 0, 0);
        }
        if (which & BOOST_IOS::out) {
            setp(0, 0);
        }
    }
    else {
        setg(0, 0, 0);
        setp(0, 0);
    }
    return obj().seek(off, way, which, next_);
}

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::set_next
    (streambuf_type* next)
{ next_ = next; }

template<typename T, typename Tr, typename Alloc, typename Mode>
inline void indirect_streambuf<T, Tr, Alloc, Mode>::close_impl
    (BOOST_IOS::openmode which)
{
    if (which == BOOST_IOS::in && is_convertible<Mode, input>::value) {
        setg(0, 0, 0);
    }
    if (which == BOOST_IOS::out && is_convertible<Mode, output>::value) {
        sync();
        setp(0, 0);
    }
    if ( !is_convertible<category, dual_use>::value ||
         is_convertible<Mode, input>::value == (which == BOOST_IOS::in) )
    {
        obj().close(which, next_);
    }
}

//----------State changing functions------------------------------------------//

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::sync_impl()
{
    std::streamsize avail, amt;
    if ((avail = static_cast<std::streamsize>(pptr() - pbase())) > 0) {
        if ((amt = obj().write(pbase(), avail, next())) == avail)
            setp(out().begin(), out().end());
        else {
            const char_type* ptr = pptr();
            setp(out().begin() + amt, out().end());
            pbump(static_cast<int>(ptr - pptr()));
        }
    }
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_get_area()
{
    if (shared_buffer() && pptr() != 0) {
        sync_impl();
        setp(0, 0);
    }
    setg(in().begin(), in().begin(), in().begin());
}

template<typename T, typename Tr, typename Alloc, typename Mode>
void indirect_streambuf<T, Tr, Alloc, Mode>::init_put_area()
{
    using namespace std;
    if (shared_buffer() && gptr() != 0) {
        obj().seek(static_cast<off_type>(gptr() - egptr()), BOOST_IOS::cur, BOOST_IOS::in, next_);
        setg(0, 0, 0);
    }
    if (output_buffered())
        setp(out().begin(), out().end());
    else
        setp(0, 0);
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC, BCC 5.x

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_INDIRECT_STREAMBUF_HPP_INCLUDED

/* indirect_streambuf.hpp
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
*/