
#ifndef BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED

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

// BOOST_MPL_PP_DEFAULT_PARAMS(0,T,int): <nothing>
// BOOST_MPL_PP_DEFAULT_PARAMS(1,T,int): T1 = int
// BOOST_MPL_PP_DEFAULT_PARAMS(2,T,int): T1 = int, T2 = int
// BOOST_MPL_PP_DEFAULT_PARAMS(n,T,int): T1 = int, T2 = int, .., Tn = int

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_DEFAULT_PARAMS(n,p,v) \
    BOOST_PP_CAT(BOOST_MPL_PP_DEFAULT_PARAMS_,n)(p,v) \
    /**/
    
#   define BOOST_MPL_PP_DEFAULT_PARAMS_0(p,v)
#   define BOOST_MPL_PP_DEFAULT_PARAMS_1(p,v) p##1=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_2(p,v) p##1=v,p##2=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_3(p,v) p##1=v,p##2=v,p##3=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_4(p,v) p##1=v,p##2=v,p##3=v,p##4=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_5(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_6(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_7(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_8(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v
#   define BOOST_MPL_PP_DEFAULT_PARAMS_9(p,v) p##1=v,p##2=v,p##3=v,p##4=v,p##5=v,p##6=v,p##7=v,p##8=v,p##9=v

#else

#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC(unused, i, pv) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(2,0,pv), BOOST_PP_INC(i) ) \
        = BOOST_PP_TUPLE_ELEM(2,1,pv) \
    /**/

#   define BOOST_MPL_PP_DEFAULT_PARAMS(n, param, value) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_DEFAULT_PARAM_FUNC \
        , (param,value) \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_DEFAULT_PARAMS_HPP_INCLUDED

/* default_params.hpp
aQF6ymycI9Z6Z8YDYXIrhuDpq9s9RvyRkkZ5ItaCMQe6e7zTvH0kpDluaauaonsGeyyhWmo0vHpMuFIIJHhZRVmzwC2cus/od/yj5trH0Ci1BPn5ZDHc5EBvAq7vlSU0P8S+djAwwDoNhe42+ExD0WcDBVSBnfs+J0GwDsfA+ShdTikEaKRg6kVICONsrA0P6oZgQM/bDyL98IwFQNK95yQpUECpRLF/ZY9y8mn5GbNHvocxCGcZjxnDAUVc/jcwNX9dyd+ZxBFLHGUZZRmbGUvnlScKK4p8ELYGRhnmKeYpyinG/PBDrqwB7jKhsJR4y3tR9DK0eeVsxlRBAwD92FEeUYACytCrIRQQWnbiPZOmpMTEstmB+/xMeY57toddXG5LkHKjKA2n+tNILufEjguG6IbuxNKxh+dDDq1XABvQUPxMkKmW+s4XzF/bDc2YArm2PIidZjZ29pnB7/xybNACJ7y0xODO09SIID17kQPHuQ41r/aVI09vv0yamlfW8NPLXwKt3cWba7SHsnIKo/x0TmM61Wq1i8d33n6GubO+8WLPNF964Te/0Cs5LvXGNN802ddwPoj12YDN0lrIuYsRb3ZhZDoeZ5l8zSlq3crKCfbffAMQ14SVnpNE36wCDanPdCc+pmd8XV6q8gnI8+/fdiIUXm1mUANBTkW40MWDPwbStYw2bMAurO0LRlbOFqHNogEmnAoJNcxV
*/