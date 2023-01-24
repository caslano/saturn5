
#ifndef BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/tuple.hpp>

#if defined(BOOST_MPL_CFG_BROKEN_PP_MACRO_EXPANSION)
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_MPL_PP_SUB_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_SUB_DELAY(i,j) \
    BOOST_PP_CAT(BOOST_MPL_PP_TUPLE_11_ELEM_##i,BOOST_MPL_PP_SUB_##j) \
    /**/
#else
#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_MPL_PP_SUB_DELAY(i,j) \
    /**/

#   define BOOST_MPL_PP_SUB_DELAY(i,j) \
    BOOST_MPL_PP_TUPLE_11_ELEM_##i BOOST_MPL_PP_SUB_##j \
    /**/
#endif

#   define BOOST_MPL_PP_SUB_0 (0,1,2,3,4,5,6,7,8,9,10)
#   define BOOST_MPL_PP_SUB_1 (0,0,1,2,3,4,5,6,7,8,9)
#   define BOOST_MPL_PP_SUB_2 (0,0,0,1,2,3,4,5,6,7,8)
#   define BOOST_MPL_PP_SUB_3 (0,0,0,0,1,2,3,4,5,6,7)
#   define BOOST_MPL_PP_SUB_4 (0,0,0,0,0,1,2,3,4,5,6)
#   define BOOST_MPL_PP_SUB_5 (0,0,0,0,0,0,1,2,3,4,5)
#   define BOOST_MPL_PP_SUB_6 (0,0,0,0,0,0,0,1,2,3,4)
#   define BOOST_MPL_PP_SUB_7 (0,0,0,0,0,0,0,0,1,2,3)
#   define BOOST_MPL_PP_SUB_8 (0,0,0,0,0,0,0,0,0,1,2)
#   define BOOST_MPL_PP_SUB_9 (0,0,0,0,0,0,0,0,0,0,1)
#   define BOOST_MPL_PP_SUB_10 (0,0,0,0,0,0,0,0,0,0,0)

#else

#   include <boost/preprocessor/arithmetic/sub.hpp>

#   define BOOST_MPL_PP_SUB(i,j) \
    BOOST_PP_SUB(i,j) \
    /**/
    
#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_SUB_HPP_INCLUDED

/* sub.hpp
jv5AOIbIFsDQgjTssrfJ91DpJMgvKJw6hjiXO/4zV+ilqBmoo/57YV42bGTym0q5n1GUjNZWG0v2jtMfovcpXl6Gfhv+IFeiKx/0qhNWjfzkhJ0rZoujY8mxyRVuV5CqEpxGO5SojK881kInFqJJzzlAp2MZrslkj3Ew0ylbE6DcpT5+36FaE4nVmBS09EkpuE4MuUJ3YdaYIeq3MWZ2hUd4IYGSdHK4mXGR5teUCFxjY5glHmP+B0XknNtSz0qO2ifnbettbUMSQ6TPQnxwHbdCxgNBIo9lGClSmtR5yv3OH+gpK5Nqv4vGg6Ef32Er+n5crzTihfphSiEoj85+LPj1qCKo2fNHFwzKUIxtL/oOx80IFoOMQXXMd4sRErOf7UN33CK86sSlXv7QqeYn2++00oOoSNMcaZdL9BkhyL+DQ+wOI+c92i0w4WVvv1/lYW7lnH6ry6R2N+jou+VZMToo+wrlO6qrQ98DYY/Qqfweq7I7QWxiO8rT+7KXOIe4duwyrFOmQqXSjthaxQeysOD2h1aZUu+EPZGNWH5yHBiKyEaJLs6p/IF03qWaPu7pZd7uzRBuzuOYS35tt/64cwnJWWyO86QvK76w9YKz1EbGddcvzDU5iXxzd/IVh5HJOA7i6FhHZLvy6+XzS6LGUPKI7CsdILuFOw15tdkYA7tC0fHj1KF/9HlfdI7sTxInC+7qeom3rHuXdakF
*/