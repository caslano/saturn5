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
pQ6Om1M35UfrsntFhpBEm8933iXmMWYa3glwNmuozBzk2R9mgNibneSWvM1IIp9C0v4+koi8UJ4ZFip36zt5Xy6NixQxI3y4VzM903cAYbxd8t7hRXlar+l4/3TvXq0fyHtsCTzsJGHmzecFbFsSSI65G0OFGOuX7ZI27nTbfkySvNo3lGA6hTzy2arxpdOsmzfEzmBPu1rTqNa0yp7++grJL+Q9b9maleiWrapACqUs09wT
*/