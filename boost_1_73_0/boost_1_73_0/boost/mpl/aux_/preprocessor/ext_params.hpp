
#ifndef BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED

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

// BOOST_MPL_PP_EXT_PARAMS(2,2,T): <nothing>
// BOOST_MPL_PP_EXT_PARAMS(2,3,T): T2
// BOOST_MPL_PP_EXT_PARAMS(2,4,T): T2, T3
// BOOST_MPL_PP_EXT_PARAMS(2,n,T): T2, T3, .., Tn-1

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/mpl/aux_/preprocessor/filter_params.hpp>
#   include <boost/mpl/aux_/preprocessor/sub.hpp>

#   define BOOST_MPL_PP_EXT_PARAMS(i,j,p) \
    BOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,BOOST_MPL_PP_SUB(j,i),p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_DELAY_1(i,n,p) \
    BOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_DELAY_2(i,n,p) \
    BOOST_MPL_PP_EXT_PARAMS_##i(n,p) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS_1(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9)
#   define BOOST_MPL_PP_EXT_PARAMS_2(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1)
#   define BOOST_MPL_PP_EXT_PARAMS_3(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##3,p##4,p##5,p##6,p##7,p##8,p##9,p1,p2)
#   define BOOST_MPL_PP_EXT_PARAMS_4(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##4,p##5,p##6,p##7,p##8,p##9,p1,p2,p3)
#   define BOOST_MPL_PP_EXT_PARAMS_5(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##5,p##6,p##7,p##8,p##9,p1,p2,p3,p4)
#   define BOOST_MPL_PP_EXT_PARAMS_6(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##6,p##7,p##8,p##9,p1,p2,p3,p4,p5)
#   define BOOST_MPL_PP_EXT_PARAMS_7(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##7,p##8,p##9,p1,p2,p3,p4,p5,p6)
#   define BOOST_MPL_PP_EXT_PARAMS_8(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##8,p##9,p1,p2,p3,p4,p5,p6,p7)
#   define BOOST_MPL_PP_EXT_PARAMS_9(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##9,p1,p2,p3,p4,p5,p6,p7,p8)

#else

#   include <boost/preprocessor/arithmetic/add.hpp>
#   include <boost/preprocessor/arithmetic/sub.hpp>
#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/tuple/elem.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_EXT_PARAM_FUNC(unused, i, op) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(2,1,op) \
        , BOOST_PP_ADD_D(1, i, BOOST_PP_TUPLE_ELEM(2,0,op)) \
        ) \
    /**/

#   define BOOST_MPL_PP_EXT_PARAMS(i, j, param) \
    BOOST_PP_REPEAT( \
          BOOST_PP_SUB_D(1,j,i) \
        , BOOST_MPL_PP_AUX_EXT_PARAM_FUNC \
        , (i,param) \
        ) \
    /**/

#endif

#endif // BOOST_MPL_AUX_PREPROCESSOR_EXT_PARAMS_HPP_INCLUDED

/* ext_params.hpp
+xaDvj+eV/7QsG9HY/qoQkWqqG5ajEWltRE1KXQlNGvskm5qoqDDUNmSVd63dD+6mbe2WbKmfp5f31B8cDOjDjStXDkHNAnwFgihj10Dr7Wv4N8xQcYHPGTaHg7KFEMawfnFavMov+fiIkwm32wlH9KccXQ8KWQZCarLILrtrLc6CKE/AeEJjJOdsJV1XsB/xJNTnwVc8ssJmxDzO03GR+5Q4vk3/gVQSwMECgAAAAgALWdKUqd+nQzSAQAA8wIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2NTlVVAUAAbZIJGBdUu9v2jAQ/W6J/+GE1C/VghNKWbE8pKrrSlc6EE0/T65zIRHBjhLzI//9zg2BbVIU584v793dO+mwdlrVOGUyN6mlY4PNwVZJPWWzOF5+vuDpMWYP76v5Yhn/9uc7Kyt7bJjkF7TkJ4IKy6KhM1FOgbE6Q7351m+w7reUPBpEMAxDWLyw78qhgHiHXyCcwC+7p4sohGgkRhNBkKfXmL1htcdKgC81qD8DnqoNsrmixKtN8jTH5MQS3cDPnfH0xDIUUdixPMZqLaA/jMLhbZDor8HNZDQejiZ3fXavNZYuWCmzxlrAR0NK7MEah8YFczRrlwkY+4xB7XJrBOjC1njG
*/