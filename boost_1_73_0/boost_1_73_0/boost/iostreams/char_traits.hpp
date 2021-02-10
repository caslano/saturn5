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
UEsDBAoAAAAIAC1nSlIxzvqUEAYAAN+eAAAuAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzcvc3JjL2N1cmwudG1wbFVUBQABtkgkYO2dW0/bSBTHn+FTWFYfirolNNndrtqkFTgJWGsIigP0IVI0sQc6W8eOZmxKqv3wOzO2c2tCkqWFFP8lEDPjuZ65/DhnTpzqx7tBYNxSLlgU1sw3+wemQUMv8ll4Y9QM84qFfvRVvH5T/qNsfvywW71kIiGBGyc+i8559A/14t2dLNAZDWnNTHMY1qtX5u7OZV7z2/2DAxk/IwOZxUt4ICOu52Ul0+Q0yYk8EpyT+LNM+LC7Uz0PSHwd8YGQkUlMhrPKZBcrZbOkspam81atKLxmNwknsexBWnomaVKFYx8ZbRpQIqjx2lCx1pCGruv8m1aucraSeJjEdcZldyM+qpn73f2pn37CAr+rs3cvrbfdFy9n2lLt7Ol67DCmfEB9RmI6VduLly1d+15XcE9nnCmfivaNfnAhaOv6tGnVzAMdP+w4pyxkA/aNCqudhB02oA7rc8JHF4LcyHLNQ8dtKGFKEXSiKFCBbOiXluVY0WDIAsrVI13jzqHvM9UsCVpDLb2aWWqcCM9IH9thwELaTEJPPWzcDUmY
*/