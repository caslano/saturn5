// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/assert.hpp>
#include <cstddef>
#include <utility>                                 // pair.
#include <boost/config.hpp>                        // BOOST_DEDUCED_TYPENAME, 
#include <boost/core/typeinfo.hpp>
#include <boost/iostreams/detail/char_traits.hpp>  // member template friends.
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/execute.hpp>
#include <boost/iostreams/detail/functional.hpp>
#include <boost/iostreams/detail/ios.hpp>
#include <boost/iostreams/detail/optional.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/throw_exception.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // MSVC.

namespace boost { namespace iostreams { 
    
namespace detail {

template< typename T,
          typename Tr = 
              BOOST_IOSTREAMS_CHAR_TRAITS(
                 BOOST_DEDUCED_TYPENAME char_type_of<T>::type 
              ) >
class direct_streambuf 
    : public linked_streambuf<BOOST_DEDUCED_TYPENAME char_type_of<T>::type, Tr>
{
public:
    typedef typename char_type_of<T>::type                char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
private:
    typedef linked_streambuf<char_type, traits_type>      base_type;
    typedef typename category_of<T>::type                 category;
    typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(
                char_type, traits_type
            )                                             streambuf_type;
public: // stream needs access.
    void open(const T& t, std::streamsize buffer_size, 
              std::streamsize pback_size);
    bool is_open() const;
    void close();
    bool auto_close() const { return auto_close_; }
    void set_auto_close(bool close) { auto_close_ = close; }
    bool strict_sync() { return true; }

    // Declared in linked_streambuf.
    T* component() { return storage_.get(); }
protected:
    BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base_type)
    direct_streambuf();

    //--------------Virtual functions-----------------------------------------//

    // Declared in linked_streambuf.
    void close_impl(BOOST_IOS::openmode m);
    const boost::core::typeinfo& component_type() const { return BOOST_CORE_TYPEID(T); }
    void* component_impl() { return component(); } 
#ifdef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
    public:
#endif

    // Declared in basic_streambuf.
    int_type underflow();
    int_type pbackfail(int_type c);
    int_type overflow(int_type c);
    pos_type seekoff( off_type off, BOOST_IOS::seekdir way,
                      BOOST_IOS::openmode which );
    pos_type seekpos(pos_type sp, BOOST_IOS::openmode which);
private:
    pos_type seek_impl( stream_offset off, BOOST_IOS::seekdir way,
                        BOOST_IOS::openmode which );
    void init_input(any_tag) { }
    void init_input(input);
    void init_output(any_tag) { }
    void init_output(output);
    void init_get_area();
    void init_put_area();
    bool one_head() const;
    bool two_head() const;
    optional<T>  storage_;
    char_type   *ibeg_, *iend_, *obeg_, *oend_;
    bool         auto_close_;
};
                    
//------------------Implementation of direct_streambuf------------------------//

template<typename T, typename Tr>
direct_streambuf<T, Tr>::direct_streambuf() 
    : ibeg_(0), iend_(0), obeg_(0), oend_(0), auto_close_(true) 
{ this->set_true_eof(true); }

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::open
    (const T& t, std::streamsize, std::streamsize)
{
    storage_.reset(t);
    init_input(category());
    init_output(category());
    setg(0, 0, 0);
    setp(0, 0);
    this->set_needs_close();
}

template<typename T, typename Tr>
bool direct_streambuf<T, Tr>::is_open() const 
{ return ibeg_ != 0 || obeg_ != 0; }

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close() 
{ 
    base_type* self = this;
    detail::execute_all( detail::call_member_close(*self, BOOST_IOS::in),
                         detail::call_member_close(*self, BOOST_IOS::out),
                         detail::call_reset(storage_) );
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::underflow()
{
    if (!ibeg_) 
        boost::throw_exception(cant_read());
    if (!gptr()) 
        init_get_area();
    return gptr() != iend_ ? 
        traits_type::to_int_type(*gptr()) : 
        traits_type::eof();
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::pbackfail(int_type c)
{
    using namespace std;
    if (!ibeg_) 
        boost::throw_exception(cant_read());
    if (gptr() != 0 && gptr() != ibeg_) {
        gbump(-1);
        if (!traits_type::eq_int_type(c, traits_type::eof()))
            *gptr() = traits_type::to_char_type(c);
        return traits_type::not_eof(c);
    }
    boost::throw_exception(bad_putback());
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::int_type 
direct_streambuf<T, Tr>::overflow(int_type c)
{
    using namespace std;
    if (!obeg_)
        boost::throw_exception(BOOST_IOSTREAMS_FAILURE("no write access"));
    if (!pptr()) init_put_area();
    if (!traits_type::eq_int_type(c, traits_type::eof())) {
        if (pptr() == oend_)
            boost::throw_exception(
                BOOST_IOSTREAMS_FAILURE("write area exhausted")
            );
        *pptr() = traits_type::to_char_type(c);
        pbump(1);
        return c;
    }
    return traits_type::not_eof(c);
}

template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekoff
    (off_type off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{ return seek_impl(off, way, which); }

template<typename T, typename Tr>
inline typename direct_streambuf<T, Tr>::pos_type
direct_streambuf<T, Tr>::seekpos
    (pos_type sp, BOOST_IOS::openmode which)
{ 
    return seek_impl(position_to_offset(sp), BOOST_IOS::beg, which);
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::close_impl(BOOST_IOS::openmode which)
{
    if (which == BOOST_IOS::in && ibeg_ != 0) {
        setg(0, 0, 0);
        ibeg_ = iend_ = 0;
    }
    if (which == BOOST_IOS::out && obeg_ != 0) {
        sync();
        setp(0, 0);
        obeg_ = oend_ = 0;
    }
    boost::iostreams::close(*storage_, which);
}

template<typename T, typename Tr>
typename direct_streambuf<T, Tr>::pos_type direct_streambuf<T, Tr>::seek_impl
    (stream_offset off, BOOST_IOS::seekdir way, BOOST_IOS::openmode which)
{
    using namespace std;
    BOOST_IOS::openmode both = BOOST_IOS::in | BOOST_IOS::out;
    if (two_head() && (which & both) == both)
        boost::throw_exception(bad_seek());
    stream_offset result = -1;
    bool one = one_head();
    if (one && (pptr() != 0 || gptr()== 0))
        init_get_area(); // Switch to input mode, for code reuse.
    if (one || ((which & BOOST_IOS::in) != 0 && ibeg_ != 0)) {
        if (!gptr()) setg(ibeg_, ibeg_, iend_);
        ptrdiff_t next = 0;
        switch (way) {
        case BOOST_IOS::beg: next = off; break;
        case BOOST_IOS::cur: next = (gptr() - ibeg_) + off; break;
        case BOOST_IOS::end: next = (iend_ - ibeg_) + off; break;
        default: BOOST_ASSERT(0);
        }
        if (next < 0 || next > (iend_ - ibeg_))
            boost::throw_exception(bad_seek());
        setg(ibeg_, ibeg_ + next, iend_);
        result = next;
    }
    if (!one && (which & BOOST_IOS::out) != 0 && obeg_ != 0) {
        if (!pptr()) setp(obeg_, oend_);
        ptrdiff_t next = 0;
        switch (way) {
        case BOOST_IOS::beg: next = off; break;
        case BOOST_IOS::cur: next = (pptr() - obeg_) + off; break;
        case BOOST_IOS::end: next = (oend_ - obeg_) + off; break;
        default: BOOST_ASSERT(0);
        }
        if (next < 0 || next > (oend_ - obeg_))
            boost::throw_exception(bad_seek());
        pbump(static_cast<int>(next - (pptr() - obeg_)));
        result = next;
    }
    return offset_to_position(result);
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_input(input)
{
    std::pair<char_type*, char_type*> p = input_sequence(*storage_);
    ibeg_ = p.first;
    iend_ = p.second;
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_output(output)
{
    std::pair<char_type*, char_type*> p = output_sequence(*storage_);
    obeg_ = p.first;
    oend_ = p.second;
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_get_area()
{
    setg(ibeg_, ibeg_, iend_);
    if (one_head() && pptr()) {
        gbump(static_cast<int>(pptr() - obeg_));
        setp(0, 0);
    }
}

template<typename T, typename Tr>
void direct_streambuf<T, Tr>::init_put_area()
{
    setp(obeg_, oend_);
    if (one_head() && gptr()) {
        pbump(static_cast<int>(gptr() - ibeg_));
        setg(0, 0, 0);
    }
}

template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::one_head() const
{ return ibeg_ && obeg_ && ibeg_ == obeg_; }

template<typename T, typename Tr>
inline bool direct_streambuf<T, Tr>::two_head() const
{ return ibeg_ && obeg_ && ibeg_ != obeg_; }

//----------------------------------------------------------------------------//

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_STREAMBUF_HPP_INCLUDED

/* direct_streambuf.hpp
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
*/