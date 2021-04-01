
#ifndef BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void.hpp>
#include <boost/mpl/lambda_fwd.hpp>
#include <boost/mpl/int_fwd.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) \
template< \
      BOOST_MPL_PP_PARAMS(i, typename T) \
    , typename Tag \
    > \
struct lambda< \
      name< BOOST_MPL_PP_PARAMS(i, T) > \
    , Tag \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<i>) \
    > \
{ \
    typedef false_ is_le; \
    typedef name< BOOST_MPL_PP_PARAMS(i, T) > result_; \
    typedef result_ type; \
}; \
/**/

#else

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) /**/

#endif

#endif // BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

/* lambda_spec.hpp
royX0xHwZXA4Cpgw3YpHktejIEuh9d9pV9C0qIG8LjpGMjdxUsTbx51c1QRRX5CKwd3vkuPtN3ugPOXPYOJfO17CrZhZ7wJioVPmIQ5DfJQ26VMPQOhHsuMq9FYkHSy8ofgOoUKAPh6gL9S81xcS6GzS9aKe6s/oisGi5oeQ23IE8jtC6Q5j9IzXxdpoU5gwANOgusaTTM7fz8XshDTzFk04SZ5XSkg+AMWP2NGXtOPEj/iYRvPLK/Ds5MVLJoTnAS0micz3qal1/FubC1su+wXfLlDzYrXNuHmE3Z5B2PNupdeZxOrFu1O9d3wcLqofwOYHiUJCtwVhjNOBqtPUhD6EkT6XJQaS1xYm/GBoxVOr/NKFauT2+sGKhQ5NjM/ulZmT9nCeoexfF2aOdjjm++snL6iLNP8cJnlA9YtH8CQERxlveAyQkPS0I0N9MSSIqaF6m5YgJUXGfDsm2uUHiBpkVzf3R39wderLshaBuY9NRRSCs+63oem5q7znL/qPz6Fdmj6UFOAth5m7S6ssIwaQXS+sCFM4MAaquInK9Rib8N4cD5ATkcbo0w==
*/