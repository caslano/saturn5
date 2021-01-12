/* Copyright 2006-2009 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_NESTED_XXX_IF_NOT_PH_HPP
#define BOOST_FLYWEIGHT_DETAIL_NESTED_XXX_IF_NOT_PH_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/flyweight/detail/is_placeholder_expr.hpp>
#include <boost/mpl/if.hpp>

/* nested_##name##_if_not_placeholder_expression<T>::type is T::name unless
 * T is an MPL placeholder expression, in which case it defaults to int.
 */

#define BOOST_FLYWEIGHT_NESTED_XXX_IF_NOT_PLACEHOLDER_EXPRESSION_DEF(name) \
struct nested_##name##_if_not_placeholder_expression_helper                \
{                                                                          \
  typedef int name;                                                        \
};                                                                         \
                                                                           \
template<typename T>                                                       \
struct nested_##name##_if_not_placeholder_expression                       \
{                                                                          \
  typedef typename boost::mpl::if_<                                        \
    boost::flyweights::detail::is_placeholder_expression<T>,               \
    nested_##name##_if_not_placeholder_expression_helper,                  \
    T                                                                      \
  >::type::name type;                                                      \
};

#endif

/* nested_xxx_if_not_ph.hpp
OMO5P6EDZdv6VV5RyRTe6GkljJ1ryV93iH+JqieuVkp95okTmQOx9h25H4y3L3NZBTX1k+07DpKwnRho7rRwGmh4L5M6KJKQzL69DZF993XOcPoHO8jzmkmmmD6GH1vHV4ofrQPtmJ+cTJpeYK7x7tVLOxt7l7bidwO7H89poh9JzjrReGQ6tg81Se4fK3m9SuVTZZPYlswT3xsl38zT+I7W7+ODpYTlTHZWONSZYRKoR28M
*/