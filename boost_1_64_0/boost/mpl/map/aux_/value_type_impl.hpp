
#ifndef BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct value_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : second<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_VALUE_TYPE_IMPL_HPP_INCLUDED

/* value_type_impl.hpp
YcX7/lW0vcp5e1LF26tctC+6aLdzNaalq/a8irdjVbT9z0U7qIt2NVftly7aTV22C7puN400tf/5vvbJo8cP7Gs/L2rW9IcW1trmsn1U+kbKdyYGEOZV1fa56Sx9i0KwEXbBC7i2inwPyvfjPEJnc58p06uXtI/1Rj/sg82xLwZjOHbHftgH++MIHIBjMAKTcCCm4iDMwME4E4fgAzgUH8ZhuBmH41sYiZ+iZc7AkViGo7AKaYzCJjgau2M09sMxOAhjMBnHYgGOwwfwLlyNsbgVx+MunIAf4934BU7EYpyEX2M8lmACnsZELMVk/AlTpO+JHuvjZOyFaXgXTsXxOA3zMQP/hJm4HA34AmbjJsyxjn0o36HoK8dbPaZhU9Vye2S5euUsV+zGcsE6+f6Amk7KVXspVx2wOnaU9QoIPrLe+7JebTTKev5SrgIwAG/HrtgEoyT+GGyGM7A5PoItcD22xDexFe7DO/BtbIOHMAgLPXXlttWG8VngbBnnUTXG4/7Z2nEejynvCerxHtMfoL2RYGnX3fCAs3EfCQ9cZ+xH/s3nQdozCZZxIFP5O58wk78XoLN24MIHbW3BJQ9qx4asPod9IoQTUgjrCXsI9uNFlvKZeqzIBg9p25BLCAV8Fsr7DXiYoB43skRZfq7j+JF+fLYeQ9G+vTlmrnYsyWOhHqa25zl8LuNJSjs08fFZDJZgGSGfv/0eNrdLh6JlbMk5D9vGl1zP3/sJljbrs/ztOc/Wdt1mnq39OnWew7iTju3ZLLNzHvL+LFrGnfSc72TsSeUzjMX2fGbAU+xfMZ8t4++AcJa1awPfOd+98Sh1j3A8CbEE9diUBbwv5X0R0mZuGp/ysPK30jcLaT+v0BiV7R+9/jiVUY86H6cy+HI1azv76kdtbe1F/H2W4LPA3O7eBp21vUcucG/8yiHEYxnD0rjA3Da/DMN4vxNjsRgvESxjWgY8RjnEcHQ2tuUcPjfgaiyLZVksIShjXXou1LbvB/C+CCMwdDz7gsd4vwDjeF+I6jEwixdqx8Fs8Dj79hR93FZ664IJUYR8wmrCnpU3do/gD6r/Z6Wl3Jz7/wdVz/j7uKj/F57T1v+JXOoS5ddZ1HX/HlIfzZT+BVOxuB7hnKXub676uzO/vLt1feWzUqmXp2ea6hnWeeXbkyr2xVrHZj2WkfqLvDc41uPN9Rn596xcqetTD/9B2Q/+free+X2v8+b33v7m9wvt3m9XvZe6o2asAC85Dh5Sdyzkxw3/kWRt1bEiz7g5qzsaPZzXHfdo45OqozvzHVy/7uivqjuycUvVUVtvdFFHVNclszjw9vX+Eg/nbR5Hvr+5bR6W+FI8nbczlH7/+7Yz3Gg92fncAxWvP/+v1pOd14cr3u/l/62ePNtUT867dG7+r12bJv/Y48yBWg1bNi+/nlx4znU9OUTqM12wEYZa6kFV5DtDvkuU9VqYn2UxvXpLfaY/NsUB2AojsB0OxM44CLvgYOyJQ3AADsUROAxjcDimYiTm4ih8BEfjIozGJzEGn8Wx+AKOwx14F76DsfgBjsdvcAKewbvxPMbhJZyIl3ESekg9tykmYCtMxCBMwnBMxhGYgnGoRz2m4lRMk3xro5PvEPSS/K6KlvFSO0p+d1LVG/eUuqo32uY7bYIB2BS7YiBGYTOMwRY4A1tKvrXC9dga38Q7cB8G4dvYFg9hO2v9WK7fcl0fcp16dKksV8/FcvM83KuHmuqgFZxnYMMDN3euAeqVTuYbcFp/dGuegQ12dUbHuqJ78w1IPdGhjhhDkHrhb55vwMlcAy7nGZA5BqR+J3W732GegRupw93IPAPq+pvU3ai3/ba5BpzU1f6w+QY=
*/