/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/not_placeholder_expr.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
>
class hashed_factory_class;

template<
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct hashed_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory_fwd.hpp
Q3BDBLwIKCiifi4gBr1eUVBWEYIi4AYigorvIrKJQN45VdU1PU1Y5fve64/m/PXX0qfrVFedqurp8GWelqJqNBsLxdI1pY7TizuabMijcGP1BQacdVBbf47Pet3zTd6P0lTLfNXdKw/PuaC+sU5995oSrKy3zWrms3vUmnJPeFnrO3zVrkHTG8XjDaarO3Z4U3TF3+pZcfRoTZs8XzXQuBT0mNBsNol3XN9oW4fUkdck0GzF7WxMFktrbCuRPPY=
*/