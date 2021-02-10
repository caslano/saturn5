
#ifndef BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

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

// BOOST_MPL_PP_PARAMS(0,T): <nothing>
// BOOST_MPL_PP_PARAMS(1,T): T1
// BOOST_MPL_PP_PARAMS(2,T): T1, T2
// BOOST_MPL_PP_PARAMS(n,T): T1, T2, .., Tn

#if !defined(BOOST_MPL_CFG_NO_OWN_PP_PRIMITIVES)

#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_PARAMS(n,p) \
    BOOST_PP_CAT(BOOST_MPL_PP_PARAMS_,n)(p) \
    /**/

#   define BOOST_MPL_PP_PARAMS_0(p)
#   define BOOST_MPL_PP_PARAMS_1(p) p##1
#   define BOOST_MPL_PP_PARAMS_2(p) p##1,p##2
#   define BOOST_MPL_PP_PARAMS_3(p) p##1,p##2,p##3
#   define BOOST_MPL_PP_PARAMS_4(p) p##1,p##2,p##3,p##4
#   define BOOST_MPL_PP_PARAMS_5(p) p##1,p##2,p##3,p##4,p##5
#   define BOOST_MPL_PP_PARAMS_6(p) p##1,p##2,p##3,p##4,p##5,p##6
#   define BOOST_MPL_PP_PARAMS_7(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7
#   define BOOST_MPL_PP_PARAMS_8(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8
#   define BOOST_MPL_PP_PARAMS_9(p) p##1,p##2,p##3,p##4,p##5,p##6,p##7,p##8,p##9

#else

#   include <boost/preprocessor/comma_if.hpp>
#   include <boost/preprocessor/repeat.hpp>
#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>

#   define BOOST_MPL_PP_AUX_PARAM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) \
    BOOST_PP_CAT(param, BOOST_PP_INC(i)) \
    /**/

#   define BOOST_MPL_PP_PARAMS(n, param) \
    BOOST_PP_REPEAT( \
          n \
        , BOOST_MPL_PP_AUX_PARAM_FUNC \
        , param \
        ) \
    /**/

#endif 

#endif // BOOST_MPL_AUX_PREPROCESSOR_PARAMS_HPP_INCLUDED

/* params.hpp
nZJNb8IwDIbvkfofLBDitEW7cEARGoNO40RHC4hjaFxRrU2qJMD493PLt7TD2Cl548f26yTCo/OpdDhgIteZoeULD3tjlRuw9yRigl+14EeEtVkbYrQ7tE8uV8iExao4EKCklzV3Xk/nhI+KHLU/4WkjCHBNkQHLfEX0WbXBG1NA7mC/kZ4EbB1Crp1HqcBk0E23tugyUWMDVuTrXu+F8o+SgdCypIGGO5MrsKi2WkntYbQcOwryYxREaspSatV073Pe+ZjGySTqd2jsaDpLOFW8ILQ9eW6GX6DNswPUY4LMPFrwG4T6LmEjHawRNbTcxvgWE7uGpRKVNd6ktcV5HM5AaqMPpdm6gEXDOAZy8YrfsqwKfKa+dLocB4xMA89ModAOAxZG8SJgySoKYRKwWZjMgEa/o97O1DX6OZ8kwSNNf2lz9sD/0O9G36c9bCRexcm/026TBb/evuCXJ+HX7/8DUEsDBAoAAAAIAC1nSlJn8K/QDgIAABMFAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjYyVVQFAAG2SCRgxZRLT+MwEMfvlvIdRqBe0AanWRaJyFupYhEgurRqA3fXmTYWiR0l7uvbM3mUdhFc0Eoc8rAzM/7Nf2YiHFZOyQoHTGiz
*/