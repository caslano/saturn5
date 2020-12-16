#ifndef BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP
#define BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_streambuf_locale_saver.hpp

// (C) Copyright 2005 Robert Ramey - http://www.rrsd.com

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note derived from boost/io/ios_state.hpp
// Copyright 2002, 2005 Daryle Walker.  Use, modification, and distribution
// are subject to the Boost Software License, Version 1.0.  (See accompanying
// file LICENSE_1_0.txt or a copy at <http://www.boost.org/LICENSE_1_0.txt>.)

//  See <http://www.boost.org/libs/io/> for the library's home page.

#ifndef BOOST_NO_STD_LOCALE

#include <locale>     // for std::locale
#include <ios>
#include <streambuf>  // for std::basic_streambuf

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost{
namespace archive{

template < typename Ch, class Tr >
class basic_streambuf_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_streambuf_locale_saver(std::basic_streambuf<Ch, Tr> &s) :
        m_streambuf(s),
        m_locale(s.getloc())
    {}
    ~basic_streambuf_locale_saver(){
        m_streambuf.pubsync();
        m_streambuf.pubimbue(m_locale);
    }
private:
    std::basic_streambuf<Ch, Tr> &       m_streambuf;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_istream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_istream_locale_saver(std::basic_istream<Ch, Tr> &s) :
        m_istream(s),
        m_locale(s.getloc())
    {}
    ~basic_istream_locale_saver(){
        // libstdc++ crashes without this
        m_istream.sync();
        m_istream.imbue(m_locale);
    }
private:
    std::basic_istream<Ch, Tr> & m_istream;
    std::locale const  m_locale;
};

template < typename Ch, class Tr >
class basic_ostream_locale_saver :
    private boost::noncopyable
{
public:
    explicit basic_ostream_locale_saver(std::basic_ostream<Ch, Tr> &s) :
        m_ostream(s),
        m_locale(s.getloc())
    {}
    ~basic_ostream_locale_saver(){
        m_ostream.flush();
        m_ostream.imbue(m_locale);
    }
private:
    std::basic_ostream<Ch, Tr> & m_ostream;
    std::locale const  m_locale;
};


} // archive
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_NO_STD_LOCALE
#endif // BOOST_ARCHIVE_BASIC_STREAMBUF_LOCALE_SAVER_HPP

/* basic_streambuf_locale_saver.hpp
iKSgGRH41on4zj+BP/No24N15jF7Fj+PuTN1baKL1Qx1naJjiuSI/fX2kFvhqVuf2pmeMukmFRtDNmInxBMzfFdTrgOSGY+2EV9JuvuPZ9Wb+FH3yIHEap4hwgNgbz/8lC2SvRacYgYRpAZ67wbCg92gcomABZuXh9OvU0DnKyDPzBByd1LWH1RWLcrClhjppFbd2DOX8Z75h1McYAN+RrjVA/Wl1AbJNVu1wunLFNB0AVKtLqSs91TWeGRlkzeUbjupu/AxKcxynpm+kCrUx6j0Pmb6DBqAPlDSC7KQ7iu8LeSFiURTiceR1XhGoSc0KqPxDETdSPBiFQd9ay16DRf135GBd8PCzIVIX4v0qXq7c6Vrx5kbyZyqlqlGtrFM+oV+5jUvvEmctQxtzz+b4idH1cdPT2i1J7QKsPAH7oHY5s1swgB2Cp4AfogqGYck/C3sEtJPjjU9RnRCID6/j4TINFPh+R6SyOx+PzXDazGVyKFZ1++RrGz8VmNYqPfaTmMblmbqNfQnvkteuoCp/FdhrpZ9iMhCt0ImC7lEFO68i2T7y1b+L32U//uhpn+Qzkb8V0+0+K9DTX9oBnzz8VH9ObeXEnqzZsbtKedOQ8J8k+YkWUUNdtDszyAlBf6a08BiWyiZDfSU25XWZwGOZ7J/9kJ7RwzoGbqacU3s4rFNHsJ9pODT3YDsCvV8pBnciw8aukyeaMZolSL2TnLBHHiXeO2IDAiN+WzWWS6bD6cHf1VEtQr+BX/KU508rG3R30+Wm3KQbsonKr8pd8qyjGGTPvBsHkOqdQwf9hBzclsHgRjIzZ1kIFOvPy0fgFZ+s3WeofuL16gXfPwa1VkeJWKx7Qg9AmlOP1QEMQgOAZvOSw4JeyJk4M7i3a7aayFhX8emFO04CEHOHSiOR6ksHz9KzSS585EQ2/lmZwT57+I75e+WXqaViUiCpnZlJz/P3ES+LKApGalEedrOV5S92jlQlqO/ZxhPBnUhJeMng52u2sVkuWZj//uYWvZiaFjSyZtIJ29cytaIgxe1pVBs7EvZkhKeN85PgyA8rzkmcmBTIunaQqhi6vsaMAa4tJJT3C+m/+vBxtopfxMW19dYzVUdeTXPGyvL+SfNWE5HzlmyQO925AXaUW5ST9ndNfgVzy1eSD5nFrE46qtBBrvy2SqDXWkNXoU7Wehxln3N4sUXQeOFS5mhuJQiFv/qjTsKSzL0LuO95ws6lHKeQnIpvpF4d7N+L36ySmWi1oTuR5e33R55Pzr6BZ+iCa22ayX5Wwf1pVqKOlDlUAV8J0sF3AMfha2di0zmjAr83+jjOohwuV4s62/IIftDgTxJX6Aem84xMKexe3Z9YA5vhc+DNSHaORBDPsEIQxoShtRI2Qq5c9BtRZIsLcjSq8MAVTTYPXIvftCLjHvkMHxjxurzGIId5CI50s+ZIrr6BGn4TSFHyjIN9m0Zlk3Nl0fe0Nujwzjj8RUJxL9dXhDm3wZRUwlss3AMzfwlzL+Fwif76y5hN7Ls+DcFpw9VQH8sx78dpKzeKquOwb/Flufffgjzb+5wq5eoUpvs+DcFp7sU0Mxy/FtzyjpQQ7KeQ5YwHm7qrnZC37dROLI8ymF26yDl6Ks4XTg4SW9OTemzVLpwcJm0/LlJFA/rlnh34Q2hUVnx7pHriH/Twb/hxqSaOqjnqYYakuD5Oqc/SfohrQ05y8GZR5X63fkZJgPWDgyY5v+GUt1IxV/iwQY/afJgfyEe7F7wYBErdTxBxvyaw5zRgxY+bIvKDiDb2pUNG5gXe8iatr0pwQ66kzBnJe2G/PZiIHrkZ1MZFfuFmLbhBgcHjk1xbmpXa9jNwsG1Jg5uXIA=
*/