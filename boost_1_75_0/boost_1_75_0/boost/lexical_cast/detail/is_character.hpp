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
oTAdAS7soIXMNg2TYLQOTRYRHzGJAPuH2giydoWZFKLb1MWsSbrHw/OU5Ltk2Cd6B9HzrAjNii9pdNQdXa2fhIfAgSzeSKxzBYIAvalPZjpqDfstWdVjvZ6odGnpvCwhdXPLLxU29sl5sklcgjF9H0ucNqYtOZWZetFPj5QUvovsGqzRNWduKLTvkWepVfxS8Nad0D0hXRtSPSE3HQxj4Gxswi0oemo67M9jOao4pv7TdmYBNDsEY7NU0IBOqtDxLpAqCAOVaAflQr5JqwEVaUvAI+53TzDVM0OAXMFgIswJ7gPnPBMtGEm8MTwjRWk1WCs/aCvogosu0+Ojg5A7pu+RV+wsUCxk/iGBZFLgF1sar1jbM6QsKTFAb2QEzJKlLFgZ+jFpAmuQg/ZI/3FENU1ZlCOps/YmgdWw/5ovzUMStP8gafT7ej1Jj0b3zQr5cleeeG+ZT0Ko1q5hWdkws7GBVhEt4GzEDhyYOJ1eYeBU05bT5rdO4RbVrmoOmtFlrBldc5klT46RfL8xuwwya5Vqladkpe0h5C73VzldplkSb+PI1XFoW1inFrSEXIKLbh0z1Pq5DSWULxeRHYfaDoGWOyFFvNEfzHcuabzLyLq+lD+noGSCpMP8k5+tZHi7wDJcp/3rCN+Pu8/k0KckDIOHp7iYqIYv+dgXR41ROd0b3ec7gw8r8oALj1DqmQwUNdN9hByS9qJT6mqC
*/