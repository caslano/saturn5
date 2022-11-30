// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
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

#ifndef BOOST_LEXICAL_CAST_DETAIL_IS_CHARACTER_HPP
#define BOOST_LEXICAL_CAST_DETAIL_IS_CHARACTER_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {

    namespace detail // is_character<...>
    {
        // returns true, if T is one of the character types
        template < typename T >
        struct is_character
        {
            typedef BOOST_DEDUCED_TYPENAME boost::integral_constant<
                bool,
                boost::is_same< T, char >::value ||
                    #if !defined(BOOST_NO_STRINGSTREAM) && !defined(BOOST_NO_STD_WSTRING)
                        boost::is_same< T, wchar_t >::value ||
                    #endif
                    #ifndef BOOST_NO_CXX11_CHAR16_T
                        boost::is_same< T, char16_t >::value ||
                    #endif
                    #ifndef BOOST_NO_CXX11_CHAR32_T
                        boost::is_same< T, char32_t >::value ||
                    #endif
                        boost::is_same< T, unsigned char >::value ||
                        boost::is_same< T, signed char >::value
            > type;

            BOOST_STATIC_CONSTANT(bool, value = (type::value) );
        };
    }
}

#endif // BOOST_LEXICAL_CAST_DETAIL_IS_CHARACTER_HPP


/* is_character.hpp
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
*/