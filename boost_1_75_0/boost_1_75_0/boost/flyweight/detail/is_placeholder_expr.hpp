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
iim3e+acc7mlcLUz9pAODg8PzvsvvoWQfLLBMGFlObewqqVcVQbhmoZgFRJZcwG3Sjn/OrxO+F7YtG3ZTV3z5xhQBkw3jz4KUDPb9VAz1IQNrAk3uFtJvsE5zZ3V5GMeOWvy3ObDMSJ5ztlzr2xeqybff/bcbc0Pq8mfjJw8xbK8X1K5t7/UfOYM4JHAJyOi+2RA80b1k+ToPnE2P65+suHhqD4Z1DxB/eT+6D4pab5S/aR3dJ8MbVZOi0/8D0X6hOkfZtG2L0VM6c6Q1xYWTEmyPNygNHj7lzYvUYu4IfKHDrlfkueY2Z3k7T+yuZx95TkWSzc3sRt778/crQq9d45sHoiv4ujVdXgTb6npxX7Ag0vV4rY/GFUjlDWfOKW2W3Sf3NjcqH5SEvmTdNYxqyQAY3roqzRT82L1u0MPRFXU8OaR7BNLaoLQ0QaJoPeqWoVKGepWSSgZq8Y257BvCuVbCU9HhLun3Yd1tCHBpPXmycEgJiStTWtpenqxSVgkf18jfv24ht7VkijXYRNQbLzHOwfExtsVeG7jw5f0oIIY1SoXJSpilNDhbkv1zWbahBZQaBLfIyP8VIKCsVRfjHd7CcWEx0hAbYO18JSRAGmjIdrgpNWOp0L8+tZ0OB4+Btiaz0xUpM2wd4VK9rtcG7GhroLyq3s7nrsGIWqj09GUhXF7yABfo4WtEtPuk8vOcrADg/6dNylUcFhk
*/