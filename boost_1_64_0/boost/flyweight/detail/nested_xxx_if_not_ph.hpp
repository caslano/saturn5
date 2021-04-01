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
o2CLvbnUm2PgY6RTsc2qBmenpjwfLsf0grTyQGLflIAcXnb4pLpNffgqmWrhpRF2LgtC+vYQsJsjfhCvSd2yEOGyC4NIJ4MTnSHtaUGWQTf/y0ORz2aNMz62xAVHxMeaSBGNiIupOO6U6ubiB7JyTstB9j5zLmeBzU5PWI8bWwLSa2KB2ULnFnCDgDhjGfprGe2FC7VNs6YuQirZLDuMjRvcNngWs7nEJPG0QeFLt2BkpVVRx2LNArP8ACxFnoe4OwcmeU4dRkjQrOXql9AOslnD9yFszetM65gDgRxjlAyoHTtmxjBpBd0FEwdCuHCkxF2O1Asp+ApamSU5z010Bf3bvrjB4cXlWefc5Zz7x80C//eIXGyDWMAtqzGgzYw8HOybDEVcAkjmMQ7kGr2Ac5cbxpNVDfsyCOfNN59RqAiJV6X+ZfFvfRMvWKSIwwgJ9IuPWgjKbodDaEV6TXOjWrR0PzPgaswiAIZdbfLgp98+R5eA47NPlslu183x6CplJVfO4ojyFk5uTGx233RDngc0p0gtsne8LqUpNH2DAiCijPyY8KwhI45q7g==
*/