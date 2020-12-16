
#ifndef BOOST_MPL_MAP_MAP20_HPP_INCLUDED
#define BOOST_MPL_MAP_MAP20_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/map/map10.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER map20.hpp
#   include <boost/mpl/map/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(11, 20, <boost/mpl/map/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_MAP_MAP20_HPP_INCLUDED

/* map20.hpp
+b3L+NqFvtJ+89L6/ouD7GbjWrFkx9cOt68b/XubzSt5t5GdbW1dnJUuTkznu9DFHel8LzpfkHcfiM5Xc0/QFzHss8DBRaOLnvk1/5UxZV0VRTpfh953dMJI4/f3T6w+54YNvr/3ixEHfvTcSY9t2fc9ydR7+3wImSuFfw9xA8Wmz5R8FZJPtelnKTZ8NpwNt4Rz4NZwX1gA94N+OBfuB/dXv8so5W/goEe6kq8zSr5Rkm8JqVvy7SX51oR1km97sVV3gMPgjnA43AmOgpNgFpwMx8Kd4VZwF6nPrnAyzIdTYAEsg4WWnhz6dlW/bynPJn6LUp8OUkDyXS350uCyKPFqqXAMXB9mwY3hJtIv2XAC3BRuDzeHO8McuAfcAs6EY+EcmAsr4VbwIDgONsGt4XEwDx4Pt4FL4Xh4JZxg+Q7k+QPLRX/Vd7Cb8s7iSFgCx8BSmAPLIIm+tNpNnhvUWddukq87Sr7RVj6538L0GOXl6/JJeSetjG4zeA+JxPcX8V3EjsWzfBm2WDzVj4EPQ+LvwmLvxG8RPdbunnOTfM+RzJg7nxJrl7wnepBKSG0OMXX4LqxYujW56S2nnFzxYfhakiSezoqlEz9G9Pi5SlI25zrFzk3m91yYIfFx4d/g1MfGqXFxjZSx/Enn726+T1Li4iQmTo2Hs8XCOfow9HFv7TATntWS5CrWTY1zm0hSYtqseLbeGSn0K+9VkspJjaQLSe2kLlIPKXXPFF8eqYwU2PP/7c8YfPu/kX8rmhrr+r/+b9juJytr+V1iR/vhWrAAnmDsJXN7cE5mSK+oXlQxr/rA2PuKGd/je/QO63t8Ude7MtGhsTHc5qhvqqvjRGvfr3xuzvMaDwyet77sD2bIaaipq6lqXLTYcR92sQ1Opg4obe3DbujQcFBddeicHdd9Llg/9iVYP/R3fkhv3ymTwmMPWsXe3lDaZxQ8jTz57WHtg4F4SMz20baH1H9RwL4Oy9+if6PsL76e1O8bMhlCw9ogmd/4yVzbPtNog6YlYXPwvCTbnugSA9B+Z199auqrgt4DN7aamzVNs0/OQh/KDtOnU/SZJvoUij55d4XrU1tf2zgU+gSk8GNFnyNJ55CvxabP4poGrsCamPqYNgp9Y9hidhtFrv9IfdNc6pst9vdVou9lpBby5d0drm/DvMP63Z+fiH2pjFn+plYudd5FdH5YdM4WnWVdHSOkT2c8ShVV8xfVVtVUmMO9X7qH6SVjhYId1vuh6LUb6TyjLW16Ge0ZaBxYfWSshvlWPjXjD0SfjUgXGNeiTZ+Damvqqg2N+tm/1j1ZdJI8xucrwvqvVez48aLXOJJxT+xU9GqI7L9+xfc02r65kKqJ5eEe6dTHsmeW95iEv8se9xqT4DV2wtl+18Ue6GInvMc8OMeo6PwM+tiVz4P+inPS/UcsrJnxzKuLjvlh5/qVU3SxMQMXO+EcA6PfIyy0Z5PMp2Se9Zxtz6Z7xB59EI6GD8Es+CjcCj4OJ8GnYCF8GpbAZ+Ce8Fk4F74Ma+Er8Gj4KjwbvgFvhm/Cp+Bb8DnYDX+CH8GV0OljmAI/h2nwC7g+/BJuBL+G2fAbuCv8FhZAc++uLp/Mi+CGUs8NgnqHjp2knrvCTWA+3BIWwAlwCiyChXAPWATnQD88GE6FC+E0eBjcDTbDYnga3B22wj3g9XA6XAZnwBdgGXwFlsOf4Sz4pxkTgq77SH3nwFFwX8sfJfMjOJf0nM0f1SD1aoKZ8DC4GTwcToJLpF5HwFJ4JJwNj7ZiMWS+A6dJ+Wosxnwpf4GUf4iUXwe3hgvhjrAeFsIApFwo8xZ4rJSr7kV0gZR7kZR7sZR3ifTHUin3UlgOL4M=
*/