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
    #if defined(BOOST_MSVC)
      #pragma warning(push)
      #pragma warning(disable: 4127) // conditional expression is constant
    #endif
    if ( !is_convertible<category, dual_use>::value ||
         is_convertible<Mode, input>::value == (which == BOOST_IOS::in) )
    {
        obj().close(which, next_);
    }
    #if defined(BOOST_MSVC)
      #pragma warning(pop)
    #endif
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