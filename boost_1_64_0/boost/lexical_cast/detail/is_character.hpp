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
PXCsb2j2oBZtbYiRAz3QdWz6GFazTmI5ZcKr86EFU1A9EQn43WzdBbOBKl3im8EDir3B/NETcxmDLGc4GdEU/xZ+jo3m+5ecEZMfdrLjkg192bRN1acyfTCcfhMpzKeq8vEer3qtnjMmSZbAnMY0hrP3zHc+O9hHpjKJB37p52XXZr0a10jU+5p9rxWlUfeetQ74Le6iTUr4xLft9UzCpcfsP1QXOI3pkg9d2z68LW/9sYoS7qgGQF69RotboLTJxkwffxyLc8PnVcHDoszAXyVU/WTwvAx9umbFDe0w7ioLo69VHmiUy2q6wTjGF0DfAdnhMJ0NrQYr018WWgCHgrpteQuNZ4zyowvAcaW2qthhIsgb2LVnZ+Smc1vJNUmeIDLgZl1NDIdZ8o6LoXrJgz8GWkSikXvmnN+OZJnE3rLWgAH+N/muISz+xWVuBPHXFuXXYiZhfwwBBcaLv5HIPI/09xhBh87pIdJ3uJ+vD6ELKTt7tE8LAOVCV9vkaJFNYquL6tw2Djokr7ThNxjySEEWirsb45px7EudVFNy9Vg+dRjQ26Q01ZFcgQ==
*/