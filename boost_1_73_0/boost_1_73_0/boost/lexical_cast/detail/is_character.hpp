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
24KLBnzsjj7c3I3gY3swaPdHn+DmGtr9T8Ts393+Fbqeo7AY2GoeM4HCY+CzecCZm8r8+z7N2iseOkHiMqjLKAoswWQyP/Drtdorl3k8ZNDpt9/1Otbl3aD3u3U76PZH17XmPjkOoiSGaBnCPOah9AwTTRk6BBoBFc4Ei5VmWpXmeBOCED1afxKFCxbLLU9mYiK2TRhb7niy5QGiOFiTPWMzl40TogZcypSxuQY+BkKvPRxBRomrqAlpS+7AIuIuuMlsbqBqQoLj2zHsSz5DRh5BuDTIVrJR20gW191eB/YRG8yeZROSUPBJiEDRM+cyboDgX5kl1c8WLjK2Haa/5cOcggeNa/HQi+gWsgvztIZequ1jkNhBMLadKXiII/Lize3Iuuq8u3t/fde/HHVv+jVaJnoQlL2UZdCcBtHCvo/BFGyIUaI3lUuX4drSfmkd2qD7CKOYyM3aN6RB4yRYBW4wam3C0WUUenwC+1E2AOeQzTgt6N8H0dgOMmJH/55DPuvtxURR0BTthSiR80QijSZ+e8HiOIoFEax7siSHvL2wA5ALRUgkKQA+H7W+0Bjd0pqZg7zw3qBVmtqGp4S1MJK0AldBC4B7RqaBdinON+GbMlcmdAb7YbQ8TccUGFMxbB45vhV5HkZt5Tk5
*/