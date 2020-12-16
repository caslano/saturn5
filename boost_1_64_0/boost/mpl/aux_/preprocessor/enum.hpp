
#ifndef BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>

// BOOST_MPL_PP_ENUM(0,int): <nothing>
// BOOST_MPL_PP_ENUM(1,int): int
// BOOST_MPL_PP_ENUM(2,int): int, int
// BOOST_MPL_PP_ENUM(n,int): int, int, .., int

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_CAT(BOOST_MPL_PP_ENUM_,n)(param) \
    /**/
    
#   define BOOST_MPL_PP_ENUM_0(p)
#   define BOOST_MPL_PP_ENUM_1(p) p
#   define BOOST_MPL_PP_ENUM_2(p) p,p
#   define BOOST_MPL_PP_ENUM_3(p) p,p,p
#   define BOOST_MPL_PP_ENUM_4(p) p,p,p,p
#   define BOOST_MPL_PP_ENUM_5(p) p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_6(p) p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_7(p) p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_8(p) p,p,p,p,p,p,p,p
#   define BOOST_MPL_PP_ENUM_9(p) p,p,p,p,p,p,p,p,p

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>

#   define BOOST_MPL_PP_AUX_ENUM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) param \
    /**/

#   define BOOST_MPL_PP_ENUM(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_ENUM_FUNC \
        , param \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_ENUM_HPP_INCLUDED

/* enum.hpp
O1wl+2O1HIfr5Hhfj3PxRVyC6bgeN8hx9xLuxk35z9eV3wkcL+VQP1+3g5SjMzZEf/TCLvJ56Ip9sBuGYXeMxB6YxbI6tC2tGU6aTcogXSU5tyutCSQZSDtJuSRXYo0+pIWkNFIm6Swpm5RLciQO6UXyJ40mxZBmkNJJGaRzJE1H4pMkH1IwKZJkICWTNpGOkc6RNJ24Tw7JixRACiYlktJIp0jnSXkkx86lNX6k0aREUjLpfhbLwkzSm6RsUkVio24kH1IAKZI0g5RMWkvaSTpEOkfKIVXsQn6SHymQNJw0j5RGyiCdI+WQqnSlPiQfUgBpOCmGNIOUTsognSVlk3JJ7t1MMdq+pNEkHWkhKY20lZRFOk+6Qcoj+cyroAkixZBSSDtJZ0g35tljuvbJPv2VpofU/g/Rxsf/4Wf/12V8fyA/kkGVlfa+0qyiBRESlRAbYXr2vPLv6b78zoxR/zuNE31cLBmM8YPtqnsHBEm7vpvED7qQOvHvKab4QfdBg0Ji4sIiQ2RJlEX/wDiCub3iWMpWe8XW+b6t8+6SOy8ubnvCVrtn7Fzl9afLed7NWfN09JxDc0+3alznK9vtG9N5jmxX2d7nSerznIZyPt4Y62ITbIGe2AGbYxf0wmTc+Qy/KST1b3waydHq91sjv9HnSF7ym6z+7XWT39W1Vr+l8nspv5Usk5Rh9VuoI91+xv6bZp/sk32yT/bJPtkn+2Sf7JN9+u+Y/tz2fyz/hSS2be2tM/X+//H+/1flWn51//ev6IQ/4zalY+aKqd+1f8hwVh0SqY3nLnwhuvjoSVo6gE19lG6/20dZ9rGY68a2KmELS5/lUTqGdGjqs5R5b7lu1zzfynI/+XUNiIPrTPOu+fPexnm3/PlWxnl3mdfK8j3wH8xHGBKN857MT2nIfLgm/9oYg0b64KXPVFm/QdUfbCzPJG9NVennNZVXKaGpjzgT+7LN3sVnrln6iHNk2ea+5Dz+IbC0qX/i0euWfLfNZVD1HavHJ3hIv/x96T/OI+1Q7vH/ZYH9w6XU2vgwgzZkuG5yEcYnlH2s2Y3C9o1lW1c0z0+29JcbSLHh0QSKZP9Ybd88q+13X7UN1Nd3+Uvn9ttSp+OkV5Rj7kZhdbIcdUXpG69K3VrfNNctjtr9+8ce8/nHmmv+fCurY0/zbx1791XHnnq8gKPck+KsbJszpF3KtjHWqZR8FeR/Htm0RR+PYqxftNQ/v/zRpvpblde58PLK8cy+Ns/rTbtHY4nbEZeyHbd7zhj3mpMY9sq3teN+fOtUL7chsXdaFz8OV3g8r+TicyeM5Tzi0bhF3Kiyxy49/snrwSenDDbF4W6Uku9H+d48hu1IFyUW6iv9cn7ojB3RAzthc/RHX+yCHbEr9sUAHITdMQx7og57SX9uH1yK/TAV++MqDMJ9OBBfw8H4EQbjBRyKP+AwvI+j0JWyjsY6OBbbYoj0V4fhSAzHEIzE6ajF2TgO03A8rsMJeAQn4gmMwyuowxsYjxq2kx7LYiJWxCRsgdOwC07HHjgDh+NTOAZnYhLOwuk4m/+W4HzcggtwJy7EV3ERZuJi3I/J+B4+i2dxKf4DU/AarsDb+DzmYRr+jKukH/aURr5v8T7pGMmFdIikTBtkf29Fd9wm/cnb8QnMwJ64W/bzXhyOmTgO9+PTeABXYxauxdcwA1/Ht/EQnsLD+A4elf38Bn6Bx/E6vom38CR+j6cwD09LfdI18l2Lb0t9HiOlSn0+lvqcl+P3U6nXBWyMF/FJ/Azb4+fYG7MxFC9hOF7GRLyC0/AqbsdruBO/xL14C4/ibTyO30g5MzTyvYdnpZzVSJuknDWknK5SzproibVku9c=
*/