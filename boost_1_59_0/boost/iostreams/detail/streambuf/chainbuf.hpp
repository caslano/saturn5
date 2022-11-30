// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif      

#include <boost/config.hpp>                    // BOOST_MSVC, template friends.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/chain.hpp>
#include <boost/iostreams/detail/access_control.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/streambuf/linked_streambuf.hpp>
#include <boost/iostreams/detail/translate_int_type.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/noncopyable.hpp>

namespace boost { namespace iostreams { namespace detail {

//--------------Definition of chainbuf----------------------------------------//

//
// Template name: chainbuf.
// Description: Stream buffer which operates by delegating to the first
//      linked_streambuf in a chain.
// Template parameters:
//      Chain - The chain type.
//
template<typename Chain, typename Mode, typename Access>
class chainbuf
    : public BOOST_IOSTREAMS_BASIC_STREAMBUF(
                 typename Chain::char_type,
                 typename Chain::traits_type
             ),
      public access_control<typename Chain::client_type, Access>,
      private noncopyable
{
private:
    typedef access_control<chain_client<Chain>, Access>      client_type;
public:
    typedef typename Chain::char_type                        char_type;
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(typename Chain::traits_type)
protected:
    typedef linked_streambuf<char_type, traits_type>         delegate_type;
    chainbuf() { client_type::set_chain(&chain_); }
    int_type underflow() 
        { sentry t(this); return translate(delegate().underflow()); }
    int_type pbackfail(int_type c)
        { sentry t(this); return translate(delegate().pbackfail(c)); }
    std::streamsize xsgetn(char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsgetn(s, n); }
    int_type overflow(int_type c)
        { sentry t(this); return translate(delegate().overflow(c)); }
    std::streamsize xsputn(const char_type* s, std::streamsize n)
        { sentry t(this); return delegate().xsputn(s, n); }
    int sync() { sentry t(this); return delegate().sync(); }
    pos_type seekoff( off_type off, BOOST_IOS::seekdir way,
                      BOOST_IOS::openmode which =
                          BOOST_IOS::in | BOOST_IOS::out )
        { sentry t(this); return delegate().seekoff(off, way, which); }
    pos_type seekpos( pos_type sp,
                      BOOST_IOS::openmode which =
                          BOOST_IOS::in | BOOST_IOS::out )
        { sentry t(this); return delegate().seekpos(sp, which); }
protected:
    typedef BOOST_IOSTREAMS_BASIC_STREAMBUF(
                 typename Chain::char_type,
                 typename Chain::traits_type
             )                                               base_type;
private:

    // Translate from std int_type to chain's int_type.
    typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)           std_traits;
    typedef typename Chain::traits_type                      chain_traits;
    static typename chain_traits::int_type 
    translate(typename std_traits::int_type c)
        { return translate_int_type<std_traits, chain_traits>(c); }

    delegate_type& delegate() 
        { return static_cast<delegate_type&>(chain_.front()); }
    void get_pointers()
        {
            this->setg(delegate().eback(), delegate().gptr(), delegate().egptr());
            this->setp(delegate().pbase(), delegate().epptr());
            this->pbump((int) (delegate().pptr() - delegate().pbase()));
        }
    void set_pointers()
        {
            delegate().setg(this->eback(), this->gptr(), this->egptr());
            delegate().setp(this->pbase(), this->epptr());
            delegate().pbump((int) (this->pptr() - this->pbase()));
        }
    struct sentry {
        sentry(chainbuf<Chain, Mode, Access>* buf) : buf_(buf)
            { buf_->set_pointers(); }
        ~sentry() { buf_->get_pointers(); }
        chainbuf<Chain, Mode, Access>* buf_;
    };
    friend struct sentry;
    Chain chain_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHAINBUF_HPP_INCLUDED

/* chainbuf.hpp
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
*/