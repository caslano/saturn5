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
P/qrIXIs+ULZb7ZC1u+Lz4jWjQ/yNPOhMr7l8vqe+t+O8xvNwV5vrEb/4tE/7bxHv/GnpUz5uyqPX1GO1bzQGR30+qlW9QPXz1C62dqIbqob0c3XIXRT3Qy6+ZO6WETdtFtgHtebL9d2UL8L4FyPSpb1y/AunDUdL8kFyJydZ2SE9udF/6h7HX0M+sTCc2z61EYwvpIeowyOaerzE0cu7tLiUdLHdIpv7FWn/db/gJTNb2+e/uXlkcM09dhlMKxz98U09Rh0ZLHOCX5bie+Wm+rn/ZI+oe3B5zDf8DzmzSsF7w8+n3kUzwH3y8sMIW8h5V1IeRdR3sWUdwnllSvyKkLIu5XyKijvLsq7m/KWU949iryaEPIeoLyHKG8V5a2mvEco71EzXyDfDcHHUp6aDy+O+fDimX8wgT6tSeB7gndlXsNu9PHsQd/WJMovN9/D8D/ldwKd55/LKH8A5e3LPJcD6Ts6iPLTwfvRN3oM889lEHM+mpjzdPAR4DOJNV9IjPkStjfzZnPe7cP+qHnIDhLMn8v8nYeDdwY/FLw3j/1yvCHkjKeciZQzmXImUc5k9fmgnP0093MG5eRRL7OpF48hh8cpPPbLqw4h7yrKu5byrqe8Gwx5PE7hMeXhd4bj1Mg7jvKOZ17lE8A7MQ91V/DT+PydDl5mEcOOfbL149jM22YZz15xeJsmY9qVP0XXy9vW8aSYiOZuq8O4d27OtubK19aSWHdL5mlbC6x7E0g8EyN6gDJA2aAy0HLQy6CtoOhnHUzcKU5xilOc4hSnOMUpzVOiQTOad/0/P2uet8mx/7qJjnsX9Dcwjyhgn/Nm5RV7vIWFBtIspF/AZ8q+AO5rxXkU2vs5icBjzjHXJEwBVvcFpBD/bst19URWSABNR7+qamXPyCuYJmXSv5txU7RrHGyjxn3CaHRrompdrnd8jvHeEd943/04N/rSIG4EPrPeGtVgjnEFxwjxJs/CGMtqx5hXkOezNL4yTZ9vC7PP6j3YGCVk6cVGPUGX4LmqqO3fHG/ONF+uxXtQodyDRLkmhcbT9PdArTtHSLmFcwp82rgzFZqx3x7m2P33y+hfPPvnj9E1R94f2Y9mWROw688cKex/jcT+t/748Oji2Ek3tRs0b+ui0W9PiRz2r1+7cPycW3JNIFVwTuZcXanGc6A/siBG3IbxM/ztqtguUdMume16gycQu6a/NeckfGfYTvW3TmC7ROVzKli/l+ZzurN+D2KnPcGzFey037Mx/zv8NNLYqYObOrhpBr5Hp4O8oMUONuoUpzjFKREpLeD/n59Vkjdzbm5xkzEAw87/UvH/X0ln1n9dQvQH/wb8UsMO9Jl2/jjpd3hC3syC8dIyb2AT9qGP6gbZ5g3XALG3mIw+XYS3ubNdncUFUI3WbvRx37ppu2OQMkVfXVzTV2Sd912D6ff2pDxe4xoqEsQU0VUUw4thEzTxI+hPeJSscLXR2p3qZ83xfxbjV/bhfuRn+VmwkcVU0E0gn2svcSlIa5/6gvsZfzFHxugEbhJr+vDGyXOHCzfewrvRf/Z6ee5hnIsX+4hMcTX++veRD5xrXMuDjFOlzr/vLverS6UPYPuNsg9Pu3qi1ZGgafCLfhXSvgB9JyoakZUjZXWirGGyL/vy2CWGzlVsdSVmP3Qh44h2UvaTq3Hq48x9+dhQnCU/wvyMx+VnTGzwGXGMifuUvL4ZvkLDFb2W1OVslPU785jtMaoUYATtDV9EjOsu7gPfF1TO/4eCVuHa0i7g9A3MtLi/W4cnJKj4j/LcJvgxBf/5urjdUmcSa6Ae6+/Jhg7pK/mVvKdCLKGvZIc59Y/HBRwvDTj+POA4a655XM/vOJM=
*/