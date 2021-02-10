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
4KBEtlRImm8isq1v9wYdkxdFKjWqybHG9d6LTxf+PPGj0JoT3DXy2NAoj9QUeeWAL5HGjSRMkRT5hTZq+Sjspq+xYSjerTaSqlkiLaXnNVF1KR9VBIskpFKzAuFATKURtam7mj5Ut5p8onuO1s5Lj6/oLWsa1tzCmBYFNm1sFdVGERklr4bNVkwcOEMiniVzW++VymXtcr2YfTUZPElGUaWDqHDiFuMoTVlj7ApFX6kQqjCs6ZX0sSBYrq5vlZj6tuIknziWdVXSBgWroJlBAWsUjIGmIg/cablgGh4WZY16otvOWfGMVFPB+y6jlm6jWzYPXVN2m8ccRBeTyKxDdRrsMmtWVWoORd62al34bpmgpjdjBIOm5nJvuc5AmDN3GSQWHhcNl6ov5np8voiS6DQKYusiUSvSy4r1/cwPPG3j/eFeztU7asAwWsN/84jvrGFyjNxkxVgNTuBfa4+6ZnHpQ5HewLmXpH6SxtGldxFdHe+bK9ypYP/QLwxTN06vvCA4trYej/WmBnY6w4cNo0K2eIDQO4JNjToZr0cT7Tw9MKh2O6sOHE3qLUxbvQm2QoKu6IZj1V+ev4OD6fdTfynxpyV4AEHEJyiQ6wOG50RfzoPIxc49Cx6iaJFwSSrIiSRAat6b1oZtXf01
*/