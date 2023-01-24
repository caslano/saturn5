// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2014

#ifndef BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP
#define BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

namespace boost 
{
    namespace detail // '0', '-', '+', 'e', 'E' and '.' constants
    {
        template < typename Char >
        struct lcast_char_constants {
            // We check in tests assumption that static casted character is
            // equal to correctly written C++ literal: U'0' == static_cast<char32_t>('0')
            BOOST_STATIC_CONSTANT(Char, zero  = static_cast<Char>('0'));
            BOOST_STATIC_CONSTANT(Char, minus = static_cast<Char>('-'));
            BOOST_STATIC_CONSTANT(Char, plus = static_cast<Char>('+'));
            BOOST_STATIC_CONSTANT(Char, lowercase_e = static_cast<Char>('e'));
            BOOST_STATIC_CONSTANT(Char, capital_e = static_cast<Char>('E'));
            BOOST_STATIC_CONSTANT(Char, c_decimal_separator = static_cast<Char>('.'));
        };
    }
} // namespace boost


#endif // BOOST_LEXICAL_CAST_DETAIL_LCAST_CHAR_CONSTANTS_HPP


/* lcast_char_constants.hpp
IRxjGAAYWkH+wLwC5u17sDIBbp9S8jmL2i/a86PNPi4xhANGfH4uKT7T4vcLXSnsaBw5H8UWeqDld1I8P9JM3H9+vPHAvJiBGkOBD2AA9ypK9JL85pn89LGZy/Du8Gk+9LEjZdMh6PEfnXOmt4k2Ov+X6Rz/jemCwv82pc7/L6ef+lCu+AGxQv/kNV8canadvMtO//uUujXaNwPHWCYaQcc+R9liJnX+tpdG++t06WYvih1HhI5UvHIz0w4U3Oexvx5rpIarvKu6oQANn9uWA94/laUca8iU1ok/zrY6SeoHzIsqAQIut0aImOg/p4RfaVxkgS/CckNm+g7zQ8jiegCoAMrwa/IAGqSDUTJ+s/idU1WWUPCJyqDW+Wuq4menKgPvanWARkEVLGQgxm+DaaUJLaD/92kES+FbRzSzSOEd6Z3wj32eaO1oq2xP7qMItCyUDdy1FDL10i5rsJgroWfEnlNedqk1WqgzJP9prO1OuAfpUBz0a/LJ6jgpBJD3iFV9GD2mYIkR10KVg+7UfvEpfo9ByXZNyNSerqC+GMAK5f4mVvMW+tJzlfUGo0kEnhIVIv9kXZN/U7w4Gjp8jwFmrFkCvF2doUIgwmijQxgDil2WraDPMZEEm4/39yAF/WRjfCRdcwCesKNVFLJvoGsUBxEWULKxUl4QSLUn3WaGkAxrW5pDhduOzW7PhhRJJF/MlkShyLZNF9ja
*/