/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP
#define BOOST_MULTI_INDEX_DETAIL_ADL_SWAP_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <algorithm>

namespace boost{

namespace multi_index{

namespace detail{

template<typename T>
void adl_swap(T& x,T& y)
{

#if !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
  using std::swap;
  swap(x,y);
#else
  std::swap(x,y);
#endif

}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* adl_swap.hpp
rH/hmJkH0RQ+0Fq6GJCXFV3VmVpYCa+cdc88V8eOGN2vxV27RevTPqmKFEIqnWVombPlVcep4AGjCXQeecAl/STKNF6rjPLl6yohTNNUQtS4dunYLJWy1KQudGYHxquwF6RmxvmpBNeszeT+8Y1BtN85oiuGeGmmAzb5zIx5xh3tDq/pIm+1qmPi8TZP0Har32KQN6NfsUO1P8DdPWBhSOqMPPhLTCUZnf3OUl8BTemcFy13zuMJm3EvhXi8Bfd0beIwbokJK9nA6dSghRFKHCNowfXOgL+2gw24f1VBZ9oQ0HhcWQkQ2Lkcag4Owb5vPsfiSFhCzzwuDnJFAlwlEJyDN/BAA+sbCZazEiTIuka3W6XPMW00ezdwudbnfndguCtLQ6APgVV9jahupQ3vrNM+1Edu93GFf3W9xUtcimTKh8EvDKE8HNrSH5S92dbsdBXm+3yNDoQB8xbIdXyR42mqa0JXt7Ws+EGHSFkCCg/m0Npt6d6ZSAkePQcw2YwckrzIZzhZhWHST9+qLfNhHpq5BvMtWtKJr5iQFNQfTH7/WpK5FAm7+YskhA==
*/