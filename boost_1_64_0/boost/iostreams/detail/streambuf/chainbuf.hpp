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
4U+Mr1s3s25H/vDzblPPZyxlcdl8zMtJIflYjWSGhCjKz0lspuI4wYqX9Z7hNQa7m/20vQTIl2vI1+M6S+e3YsMHibZTkbVVOpAzMEIHsrPGDhiaPsFb/nO/ypdw/heZ8hp/3vM6Z6C3vNb+lHwXNPvxOSaTfOtVkG9RzLLNTzDLtjRStgVTFkyZs9Bj2Sr1KNvSGGRb6lG2pf9l2Ybrrn01ImX7ALINuGSbPjBraBbC5SDevAULvck34JDFtk7R5RuIQb4Bj/INVLF8t3U6OvnurxXZNmy324ZI+eqmwet3AoIOuY0X/eWgWW7XbUNaJW1DDDIPepQ5/ipvG9Ii24b96N8YHugJD23DMtU2/AJjx9G9haFtSDs2bQPy5ZrI17MOhOuvrnVcZUzpQE6aWwdU0+Ax/7lf58v46PUX/rzndU6at7zOSava8jU+xvprkJLtmrqRst1ptw0u2Q5PHzN64HlZ6dkD00eNyR6dPnIs38hL9ybnUodMHu5USTsRg5xLPcq5tIrl/HCM9Vj4nOtDiZFyftRuJ1xyzho6cHQfj/obcMjgSMtK2ocY5BrwKNdAFcv1SMujk2tavUi5DrHbh4pyjanPGHTI4Kbk6HINxiDXoEe5BqtYrjclxybXcLubkRTZ7j6OXFPSK8p11FGMyQhDy22y1LsLKozJLkqP2u5yr3eZp6R7kzn+Km13z0iPbHcz0Lt99flOs4d2d7lqd19SY7KxREzOVmh3M9OPTbuLfLm2IKYxWVgHtjRwlS2lA6UGHVg0NX9Wbgx9r1JH3kyubOwQQ36Xeszv0vSqLWOTY2x7w/2a+BPN8g245RvjmDfgUbaBGGQb8CjbwP+IbHOSI2X7lN0uuGQrOzkGjhrmVW+DDjlMaF5J2xCDbIMeZRusYtlOaH50st3dKFK2T9ttwyCDbEelj/QqW+7XcnjvpKiyxZ932aYM8ibblEFVK9v3TopNtgOUbPc0iWx3n0G2WYMivjtrnA/V+3zNMiacyudDrx8Uve3NikHuWR7ljr9K297pgyLb3gA3ZzSpuvnQpYPMbe+axt7bXrUH8yfPh4bb3vbNXGVM6UHArAeqffCmA4FB3ubtAjHkd8Bjfgdc5WxhDOVMybhK5u1WNjfLN2iUr5oX9VjGgh7lG4xBvkGP8g3+l+Ubrsc+OSlSvs/abcTgCPm65ka9yThlsLe50ZTB3mWcMtibjFMGV62MY50bDcs42DKyrfiD3VYYZexoKjzqMeG45keZvXO2FbhHbStikHuWR7njr/K2And3W3EIPSxsWXXzo0sHH5u2IjR/h3yPoq3Iau0qa0oPAkY9UE2FRx0IDPY2RxqIIb8DHvM7UMXlLNY50iHh/m5KpHyfs9sKg3zN86TeZB0c7G2eNBiDrIMeZR2sYlnHOk8aHls0bRsp6xfsdiMjUtYyV+pRj1MyvM2VpmR4l21KhjfZpmRUrWxjnSsNy7awXaRsN2DJipRtTP3JrAxv86VZMcg2y6Nss6pYtrHOl4bb4uUnR7bFL6K3xQbZjjqKcRvhVDpn+mRG9La4OAa5F3uUO/4qbYtvyYhsi4tsxTu56uZMf5VxbNrio5kzDetBWQdXGVN6EDTqgZo3jaFPFszwNrcXjCHPgx7zPFjFZS3Wub1wfye1o1nGKZkGGcc4Nk7J9CbflEzv8k3J9CbflMz/Dflu6BQp379wb1akfPX8qVf9zcr0Nn+aFYN8szzKN6uK5Rvr/GlYvlaXSPm+bLcVJvmqOVSv8i3O9DaHWhyDfIs9yre4iuUb6xxquJ/zoZLvySqi9pjXkO92LV91OmJaRkzr3bY75PBK1P45/lxyKIxBDqa5ZOISOTjTuLc=
*/