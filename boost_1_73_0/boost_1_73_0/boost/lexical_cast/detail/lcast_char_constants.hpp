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
9V9HffyWEDcwfMmlY5NeHLj5+e+X71r3btPXxULcy/DCXdtnfXT62fwvnv7HrfE7Ln+Y5ITh76/44K3TJ+7+dnnzpQNfWH8zwVK7MZ13dt09+tqN3096uPuO+a4H3xGikuHT/nfMaNfJlXc9M+OmQce7Nd8hxCMM/12vvq+4J05847qLrpyyZHjeECH+wPC9VV913fz82tT0mOfavvjjh93lj/jE4jvWFVG/6Cy/4lzqq/FU1VdoML7LPH7RuQ0=
*/