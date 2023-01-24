/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_NOT_POINTER_HPP
#define BOOST_ALIGN_DETAIL_NOT_POINTER_HPP

namespace boost {
namespace alignment {
namespace detail {

template<class T, class U>
struct not_pointer {
    typedef U type;
};

template<class T, class U>
struct not_pointer<T*, U> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* not_pointer.hpp
TwbWY87ojrf4/NTFecG9GYF8i9WARHQyJjG8jkTiJT4UznMW0DtwYe/3DqPrzCMN5duhcHnzusq9eLjnZeCXKXXAv+DhzKU6sT92yT6x276zT/arDpicZZu+CAB0rI7QjT9ZQhB0bK8DWu1A/I6Cm6KaWxWY+S2+WzoI8kgHyIY+bfQhSAsp0tPWzwDORTM0mod/hb6BFBVeTUptbZTn4kl3EC29Jwoo/eTWI7nGaFrOBmB06o/AoUcdM0q+PNYJ2q1+54B/zsNVALd3wUuJY5haveWHSfcFXoZ1c3KUOL11DKDQiR/AeDJ4YS0/gK+ACFpT19Chi/wAsvdBt4TRQbp3n9wHxaHRzrh8OJRzO4e6i+zO4dfDHWZuwkXWY/YFbxp1eedwa1+gVo42tbV4Ck0twk9pmMtZM227yBvM6RoHJc+L+Kki/JII8tR9bUANdK0NSCI3lm6sYfzU1XLjyQ1YPNgXtAwXFPQsaJJ3qidH4GfIVHLjekAxXFDRwyM+QvWm1ZDtn/qMddX92PRl1kXvGoGfQGoADjt4BnRPNqfAOZGA/hLf0ci39jtfcIG9830Xqji/U4NEZzknltG7ou4snk0GopXYDPngXBtcK5irlXihil25mQZX5Oyg2Z4rdXoJ0BL8mHIbG1Ja8R45t3D2NZRfjGffM4LOxA+phD3Bb05I46lwma2x/Lgo3j9bL6LexoNe0hhyRKb+
*/