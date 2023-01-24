
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
tb3zL268mD10W5UwhcZw+0WcRM5VF/e6r1d2bl2j+/+2tcnaNTRwf60k4S2+dfJm+fd5Fph6w6nejJc40zEXiWTMrqwh47T8RQpBhBYXl9qcBpyVLXLsCTOMBs9qZXc9q7S0PaRUTgtn1UF9H+OZnL5aXaSK0ioPPpIIESc+vyPIX+/7ZW53MbtjLwOexSSWEWqbdpGCUMczWRxvfTJ3P28x9I2jUrIbMI5zJ/QWcO17ZVZo4fJ+bO2L+7vfCXGKaZLZKzIqROSA78W/1Gy/GThltTtijpRoluqpgu/aqkj269YiVPdmV7nbDYHzFbQSnloSX+19wTOL89tHk+5XFAsWTJbpGyslAoLl/isVXacUHoKFQQfyZ+HBQxM4O9YYFy5dpkwS4ZPrqapZZGMIhw56CRyQGWvq9WzUyPiDATrzog9r6i+ViBXvsamMWm+ydemVdK6xgZRFraIEjkRHDG9t5p7HtK1WFI0Qze/gcRze3cY5+uvzi4FHw3ebYu82Rd5tSlinn0jPXVKvkB82aFn35IqQFpk5INO1omo6267qjXcki7onAsBzOxjDwBYddNhbpaddwc/X2C3zsYh9YuhX/R0cfavcdcD6Yvqnp83iJfwe/aI1O+y6h9OEo9vKwybh67HkhBUcfS4g9KSF4/aE2A5q3/ioZGWAWoYuTsCM5fS4bhBemvcjfbv6NYxQw0mqTQ1hymXHlQzt
*/