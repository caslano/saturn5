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
CpgbuOZKaGhYllRmWmZUVraCCSo5wACjYouSWVFZ2r4XlZWVpZVfWVlRWl+LFe2206JZnxWVfdne/y7/PC7DneG9YUC0d7/vcHjv3Xvm3vPe3Hnnv+ee4xSntKbScuv/xvJ/0/3/3+4uzDwzHfn+KhnLu7GwHxaoa09YLJiWkyNE42skau6qr+lbMCwKti54HLiBl2YrsgMWIlSstDa3KMTOAiZymWwTZa7lL5THcXpfgwXBsdKpkPWYvP6R25+zZJU8rnJPBuqyRvzt0voaLAjtv9AVPGOhUSdB+i8kEDc7XZ6Ldq8QXWFbDHNpfQ8WaPFVE5+8Sl7/wj1OXO7WYKxq34ixcu2BmGAOxnydrLPD7c+jerE8TjBxSF+Z1Im5Zh8lj89wRSGqrtanYYEGr+XnZRpr7PL6D+44ft6t8vh992iMQevbsMA6pqvWPcNorKxZJRpHhs5xH5eL+KB4rjw/kOssbNsF/FMpu6crSSRodVEvRxLve295fZhLPgdKfRciEAfiwgnESnvKPh7udosOiH+fKLT4L+//CFm3L4/9z1QbqevTMZYD5fEAtw4PnoLr98kxbXHX+RYAVlR8C86jPspjZT/n+s97cL4BPsz7mco+yeOAPmWj3Sh5PNjNccnPZB4yU9d/yDrniHZiH62uzwGO3NNY0+xK3JiY8L7M5T4UfBBoMOlT1BsCvrSLeV4eX0n82eBL+T+4JGLLJCnTzKmz2gbOPPmCoDgzHs6m48wJKs5c9/1uEt4Mmbj3PMdngu3lvS83+srnwdyLtBvjz9VpLpwv7Os7d1r5sIm3fbjjnxNL9jh098WfdweceaDguwq4i3imm78TRoknnplAHK/Cxd8PvpdsYm6Ba/kChOHImMr9wE9gzOkCxv4tIz69mPj0TYz9exv4TPBHiVc/Rbz6OeLUrxKnrmLs7I+IU39GnPpL8DHgPxCn/ov4dBT6lAEeA34o8bxc8D7gM8CHgB8Bfhj4keBTwSeCFxG3ngc+CXwp8evbiF/fCZ4Jfh/4TPB14McRrz4e/BPwKeC/EOfu4K69Hgt+Cvgo8FPBj3Uzdwf46eDXgZ9pyAPPBn8ZfBr4B+BngW8Bn26MEzwXfLubMeRxHwaBx4HPBE9tJtywOTDD/xNe6Clv4+wHayaMMFx8sHQd4sauc3DBnVlawP4vQHbJkkjt/39f8f/fyN+9A0Htmdf74hT8Odfc/3/4xMwJRxyflVOIXIUeQRv9/BSZa7FAH/+P7QPzoep8TgPqLkyRnlbT/XJ3GDYI/TQHdBXikm617+ZoxxLcT9PoY7zsI9+/1XyoPGfIXyjr4TMDfCm3ufW6yQyim6ySwmJfbo4l/WTa0E+mDf180L359ePHjqKjG+qnHHUr6vRzzLiA52ZRI3qpsKEXte7iCD43iyzqZbGiFxX3Sm6j10uNRi98ZizppsaGbmps6MbOMxOubvzPTCwxwbF8Xz8ENBUv2RnnmboB0phlGriK36CJ7xwh647G/OfS6Ymy1HzWxSaWli2vJYm9RTsTT5koz7kZB6TWB21Td5nTFLwh5hkd6ONK3dA2rzfeHP40l0vd4zkEFSfhM+qP19xwEICnmWO+TtZfhL7ox7xMM+YEjnmFvHYG9NUG50aY+3lekeePhcyhpi5WyXNRxHV4jHbEUlGMn6I6zLNCXveJWPRiAPTXtoH+GtdnW92zpmAagd+vNDbow0a9QYONZ+h8U6czc318hs6ab3RYwYLloUaHbM/vDH24vULB4c6U16OF+t350Ea+f4n98PPV8US3azgebxKo3nj4jNgYD9orGG3D8VwZ4fH4c4n3ay9k2Y+NUkCbh+BZqR1P7cTH25M1o9Y=
*/