/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_IS_PLACEHOLDER_EXPR_HPP
#define BOOST_FLYWEIGHT_DETAIL_IS_PLACEHOLDER_EXPR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/not.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

namespace boost{

namespace flyweights{

namespace detail{

/* is_placeholder_expression<T> indicates whether T is an
 * MPL placeholder expression.
 */

template<typename T>
struct is_placeholder_expression_helper
{
  template<
    BOOST_PP_ENUM_PARAMS(
      BOOST_MPL_LIMIT_METAFUNCTION_ARITY,typename BOOST_PP_INTERCEPT)
  >
  struct apply{
    typedef int type;
  };

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_placeholder_expression_helper,(T))
};

template<typename T>
struct is_placeholder_expression:
  mpl::not_<is_same<
    typename mpl::apply<
      is_placeholder_expression_helper<T>,
      BOOST_PP_ENUM_PARAMS(
        BOOST_MPL_LIMIT_METAFUNCTION_ARITY,int BOOST_PP_INTERCEPT)
    >::type,
    int
  > >
{};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* is_placeholder_expr.hpp
Ut2myvkmVa84YjwH/1Pebjp2W0oYn05g9vr1L/ACXh6+PLThPWkYrSCWtFnR7taGk1yP/FaSuztH0Lc2UAmkcvYCJiUTIHgh16SjgO8Vy2gjaA5EQE5F1rEV/mANyJJCwSoKp9H82g/PbViXLCuHOBvegyh5X+VQks8UOppR9tmEaUkngRcYAePnTEiM2UvGGwfTU5C0q8UQRoEgleBAPhNWkRWmIxJKKVvx63Sa9V2FK5nmPBPTbFsKp5T1k1VdI5qabIC3EiSHXlAblL0NNc9ZoZ5YIhxs+1XFRGnvYGHCJp/yDgStqiEcujIqzBIoxEO1bGUJLaJnUj0Eb4TKti55vWeIZR0CFX3XYDosC9rlHAtvQ9/ktNP2uhDbLEOVdcm/s2U77DnwBlHByI3Bj0ewIoIJG6785CJaJnDlLhZumFxDdAZueD3E++CH75EbDLN2QO/ajgpE0QGr24rRfC/5D1W65SQXcLpcBNE8SRdevLz00rNFdJkG7uLcg1cwmh3B732DBJ/9PIJRxVaKAXDkvDpyDnFA/UopEZtUUKn2Gr9IK4GR4wsI3UvP+nb4mxe4xSgIaDlrNE1w4X2N29CRRhRYi6LjtY4UX4fRPPZjy2kK6yfWZFWfUzhR6Q0ny7eWzpRxHH+Kaqxm
*/