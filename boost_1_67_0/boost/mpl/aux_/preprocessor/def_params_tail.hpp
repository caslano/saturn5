
#ifndef BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

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

#include <boost/mpl/limits/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/config/preprocessor.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/identity.hpp>
#include <boost/preprocessor/empty.hpp>

// BOOST_MPL_PP_DEF_PARAMS_TAIL(1,T,value): , T1 = value, .., Tn = value
// BOOST_MPL_PP_DEF_PARAMS_TAIL(2,T,value): , T2 = value, .., Tn = value
// BOOST_MPL_PP_DEF_PARAMS_TAIL(n,T,value): <nothing>

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/filter_params.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, value_func) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1( \
          i \
        , BOOST_MPL_PP_SUB(BOOST_MPL_LIMIT_METAFUNCTION_ARITY,i) \
        , param \
        , value_func \
        ) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1(i, n, param, value_func) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i,n,param,value_func) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i, n, param, value_func) \
    BOOST_PP_COMMA_IF(BOOST_PP_AND(i,n)) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_##i(n,param,value_func) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_0(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##1 v(),p##2 v(),p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v())
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_1(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##2 v(),p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_2(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##3 v(),p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_3(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##4 v(),p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_4(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##5 v(),p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_5(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##6 v(),p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4,p5)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_6(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##7 v(),p##8 v(),p##9 v(),p1,p2,p3,p4,p5,p6)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_7(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##8 v(),p##9 v(),p1,p2,p3,p4,p5,p6,p7)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_8(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p##9 v(),p1,p2,p3,p4,p5,p6,p7,p8)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_9(i,p,v) BOOST_MPL_PP_FILTER_PARAMS_##i(p1,p2,p3,p4,p5,p6,p7,p8,p9)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC(unused, i, op) \
    , BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(3, 1, op) \
        , BOOST_PP_ADD_D(1, i, BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(3, 0, op))) \
        ) BOOST_PP_TUPLE_ELEM(3, 2, op)() \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, value_func) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB_D(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, i) \
        , BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC \
        , (i, param, value_func) \
        ) \
    /**/


#endif // BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES

#define BOOST_MPL_PP_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_IDENTITY(=value)) \
    /**/

#if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#   define BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_IDENTITY(=value)) \
    /**/
#else
#   define BOOST_MPL_PP_NESTED_DEF_PARAMS_TAIL(i, param, value) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_IMPL(i, param, BOOST_PP_EMPTY) \
    /**/
#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

/* def_params_tail.hpp
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
*/