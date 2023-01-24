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
S/FqYstvTXDd7G9eT/ff08S7HR5T6IMuq9WfWauDeQjKxzed9CDCoXh4+MVgHvJ6D0zlHLNxjh0w6XjEW4k2YV9kuVBwkfW86fX8e+vmEPw7T88/i8Y/fCxvrjlSNQcBSLYT7xB8ZJrazHkvZpoCeBLMs0hswKOdj9wegNzB9yGmNoKSfudn1PLjG4N9NDQbOMcenNhRtYGT0vYtNGWOHoe70uHt2+TwDaxXrA+/wMgvysMAMxUc+akCtbxX+MZnYgwFWyqjJZAa/w1Rtsr4S2IjygH/8Snp+iUhnd7/S5LvxQhNZTguc2NQ03FdVF5YcL2rc7nn+mssNW+DWjOSr1qtny9DzUZiKooblI41I0Dp+O552I0+iXvYxbSAZqvhl54XuJesKlwRefD5TNQcc9T1qM24HgXMkPMXCcyQNpvSADOkjYYZslFbj4qzutc9T+tRiK3RbDaDBYGrV98N4+rVSSaK7KtAtyry3RbDRC8TkI2kY9ktheuYkqV+88qw9lTVRvZNUd5vLLHFwRJ77j3ncgdLK8UeA5PBONZGPVwj1c+mDqPwCta6l0iTc8hHyz2z8Ju/oW1i/2qJZVeHp4kt4BvK+xVc0s99hMPz5c4GJGO+E7/4uUxT83/ZFM9SO72TVdVvB6h+Hxarqh9r6+bFGEVtRDZZvX/67KTS/MIZRRjhr32OMwDXyMm8N6lRjliKDs+pG1m0dq7l
*/