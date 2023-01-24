// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CHAR_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CHAR_TRAITS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif 

#include <boost/config.hpp>
#include <cstddef>
#include <cstdio>  // EOF.
#include <string>  // std::char_traits.
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
# include <cwchar>
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::wint_t; }
#endif

namespace boost { namespace iostreams {

// Dinkumware that comes with QNX Momentics 6.3.0, 4.0.2, incorrectly defines
// the EOF and WEOF macros to not std:: qualify the wint_t type (and so does
// Sun C++ 5.8 + STLport 4). Fix by placing the def in this scope.
// NOTE: Use BOOST_WORKAROUND?
#if (defined(__QNX__) && defined(BOOST_DINKUMWARE_STDLIB))  \
    || defined(__SUNPRO_CC)
using ::std::wint_t;
#endif

const int WOULD_BLOCK = (int) (EOF - 1);

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
const std::wint_t WWOULD_BLOCK = (std::wint_t) (WEOF - 1);
#endif

template<typename Ch>
struct char_traits;

template<>
struct char_traits<char> : BOOST_IOSTREAMS_CHAR_TRAITS(char) {
    static char newline() { return '\n'; }
    static int good() { return '\n'; }
    static int would_block() { return WOULD_BLOCK; }
    static bool is_good(int c) { return c != EOF && c != WOULD_BLOCK; }
    static bool is_eof(int c) { return c == EOF; }
    static bool would_block(int c) { return c == WOULD_BLOCK; }
};

#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
template<>
struct char_traits<wchar_t> : std::char_traits<wchar_t> {
    static wchar_t newline() { return L'\n'; }
    static std::wint_t good() { return L'\n'; }
    static std::wint_t would_block() { return WWOULD_BLOCK; }
    static bool is_good(std::wint_t c) { return c != WEOF && c != WWOULD_BLOCK; }
    static bool is_eof(std::wint_t c) { return c == WEOF; }
    static bool would_block(std::wint_t c) { return c == WWOULD_BLOCK; }
};
#endif

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CHAR_TRAITS_HPP_INCLUDED

/* char_traits.hpp
vmjw8UcQ89b5wuXxn8Qq5X0CAOYFTwynAWyFFbt2bVJ0J49rslYiv1Qs1JEjSOWAsuo3cy0/AGScU7ecxdy6klPWJPVuBA3qzyqxNzDfkVeowZC4/9K16pb7y5ynwWvJ1VhS7hbcDahBtMspWmhrK8M/Px8k9KfR4gUdI9ZY6gm1Ql31i6WF0keXPwZ+TyiTUYgbVURTO7bVt1X9YF4z/dQgbGtXjnilK7ASk63ahKEFoKdlYeytv8lwi+sYdFbYvo/QUHTEEJzfp3fR6BzkZb9QXa6wNgERnaCMZv+RcDQvG2Rbb5u01tJ4nYknFydQxqhlcpJ8iqJCPddWts5zDmeeLeMrcthOysoWP4o4qApe2IjI7KAouayCDNl2ss3vVI3KYs2HzcCYjh+PmU4j8u5npPCBEqS/fzJRvxIOT0v74NtdmvGoXBV59iTk5YvjM3gEKCA0yFNyC492lgIlqMBIl6gwO5gejBGO3CWH+CD+RAzH9H/LMltyPAdFrRQw+g0wufCKe02unps66T7uPkmHVvzmG4Yv/QhBBIRskCIMTJ84HoYox/KoRm/XCNK2XBCvtQdbVE0vz3T3iL7A21t91aq7Afjq9ZYPyzyB9/JO/XyUz2WCoc71HNGKvl2IrE6NvXozI1lKlUKVC3qH0toyl08aD0xIozbhAol99DQltFGVhJajA4vY4OT729E5hazdHmx3+bb8dWVu
*/