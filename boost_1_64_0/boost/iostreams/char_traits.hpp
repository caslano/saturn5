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
srudLvNBuXY9LwOlsgyC58AhV9qluxzxiH76AnpyEvXk4OmBCPaDTgHtA91jjulqqSels0wtUb5p55Wo34XeEr5nZa0KnOmvr6IvfMby+bKVXd52ebws7i9pdIV+1faTZWvLW9zbavVC9ZsuuZx8Mr9lSjxrxX0DvvdNVXkyyCP5qRKeF1Haz3COkrZnA2Kw8/2+8D2t6MQUu95/JW7ZRhdI/lyQba9V7LGdyHusOhY+D/xZaSmaVYodmXnYQWmlyQ3cJHydjHYIq5M8s/wuM3xI6WmgSaBi0EIjVs1bX2t+NgZYLX7WyeksJxi/kbBiIggrkD//rBKWYSvg8+LnzQZ1OFld301dsvQYukGdDRnHscwte4p+d3h7hPF3mc/nLbrY/9ApewueeGr/6MdXXDWx8XYEvQ+bzwfkd7xxxlflXfyuDxf37fHR2b/8udTvif3FvU/9dcjT96xYcemXNRf96v79n4a346i3+9h4e4eNtcuot7P489m51NtfDG//Um/P8ue1v5jhYlvpC9iRSwcdUH5vV36/qvz+XPn9JX9ngA7Zv4HK753K7w3K73eU33/i7+GgL5Tfbym/31V+v638NvcvpQE7gPYqv98ETw7wTtBm/r4f9Bp/rwJt5O9nQG/w9zbQZ/zdEzLayt9n4HfAVhf3WjP+nBBbXV5XeFtn7WjrrA9tnA1TbJzVWHuMuUc6B9jaTKNlmw186cC/ATsBvwF2B34L7AVs5w7Y8Pse9yOBfweO5/MpwCO4Lwa6cH890Au8DRgDfMpMF3CTmR7g28BE4NlIRzJwBLAV8FxgCnA2sDVwHtAM/zfANsA7gMcDl/K5ma/u3LMqMqG83KC2zNcBpMvEzyiHOWCsJL/hCfD3BhVSXyeBLwH4a8o1G9gBOBXYGTgNOABYABwEnAGcBPQDrwKWARcBZwOXAecA1wLnAjcArwK+C7wW+BXwZuBFiHsR8FLgbcDJwN8CC3hfBLwdWAy8C7gAeLcZD/Ae4O+AS4CPAu8DvgxcDtwJfAiIspV0tIVgXgKeCHwZeCZwPXAI74fz/j7gH4APAlcBVwOfBL4ArAJWA1cDNwHXAHcDNwD3Azea+QJuAn4L3Aw8AnyD8l9o79dCmCwv1SbaV7SJ9mfaHK0zAvL/G7A/8B/AmbS9Vgo8ApxHG2x3Al2I5y6gAVzM+3tpU/Ax2hR8Qp7TJqmL+2lkjxTrpegBbfi5A/F2BQ4BdgcWAXsDi4F9gHcD+wKXAE8BPgM8FfgKcADwU+BpwG+ApwO/A54B/BE4CIi0GGcCmwPPAiYDBwNTgUOAacChwE7AEcAewHOAw4Dnsd6MAp4HHA2cBjwfOB+YxfoyDrgGOB64CTgBeAB4MTAG+b4EGA+cBOwKzAaeBswBDgJOAQ4F5gGHA/OBY4DTgROABcBfAy8HFgNnAK8GFgKvAxaxvlbb685Rp9gOpYLWsPznga8PcD4wD3gtsACIMKTcbwI+DrwFuBp4K3Aj8LfArcA7gX8C3g08DLwH+D1wCbClWT+A7YBLgR2A9wO7AZdTrg8CTwY+BDwd+DBwMHAF8BzgI8zHSGv9M9dY54TYCuzGdro72+mewDbAXmxfewP70zaiZau2kuF9x/BUW7UJ4OsITGL70wp4Jm1MjqOtzum01VlIm5w30gbiMtpAfJD8z9IW4hvATsBd5nOmY6W1rhb4HtORDFrGdJzNfA1hvoYC44HjgInAEWwnz2E/dC7wMj6fBRzNdnIMcD7wfOBtwEzgPQxnMXAk8H7eLwdeAHwbOBZYI89Zf611m8AFTK9qUziD6e3H9J3Kfq4/sDdtuOaaz5m+M4DzgIOA19C26w28py1SrkfEfAE=
*/