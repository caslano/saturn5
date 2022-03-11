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