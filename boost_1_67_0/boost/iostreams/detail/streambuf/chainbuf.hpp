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