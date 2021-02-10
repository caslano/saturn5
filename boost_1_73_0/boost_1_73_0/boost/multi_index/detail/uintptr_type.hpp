/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_UINTPTR_TYPE_HPP
#define BOOST_MULTI_INDEX_DETAIL_UINTPTR_TYPE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/bool.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* has_uintptr_type is an MPL integral constant determining whether
 * there exists an unsigned integral type with the same size as
 * void *.
 * uintptr_type is such a type if has_uintptr is true, or unsigned int
 * otherwise.
 * Note that uintptr_type is more restrictive than C99 uintptr_t,
 * where an integral type with size greater than that of void *
 * would be conformant.
 */

template<int N>struct uintptr_candidates;
template<>struct uintptr_candidates<-1>{typedef unsigned int           type;};
template<>struct uintptr_candidates<0> {typedef unsigned int           type;};
template<>struct uintptr_candidates<1> {typedef unsigned short         type;};
template<>struct uintptr_candidates<2> {typedef unsigned long          type;};

#if defined(BOOST_HAS_LONG_LONG)
template<>struct uintptr_candidates<3> {typedef boost::ulong_long_type type;};
#else
template<>struct uintptr_candidates<3> {typedef unsigned int           type;};
#endif

#if defined(BOOST_HAS_MS_INT64)
template<>struct uintptr_candidates<4> {typedef unsigned __int64       type;};
#else
template<>struct uintptr_candidates<4> {typedef unsigned int           type;};
#endif

struct uintptr_aux
{
  BOOST_STATIC_CONSTANT(int,index=
    sizeof(void*)==sizeof(uintptr_candidates<0>::type)?0:
    sizeof(void*)==sizeof(uintptr_candidates<1>::type)?1:
    sizeof(void*)==sizeof(uintptr_candidates<2>::type)?2:
    sizeof(void*)==sizeof(uintptr_candidates<3>::type)?3:
    sizeof(void*)==sizeof(uintptr_candidates<4>::type)?4:-1);

  BOOST_STATIC_CONSTANT(bool,has_uintptr_type=(index>=0));

  typedef uintptr_candidates<index>::type type;
};

typedef mpl::bool_<uintptr_aux::has_uintptr_type> has_uintptr_type;
typedef uintptr_aux::type                         uintptr_type;

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* uintptr_type.hpp
AC1nSlK+XLJhngQAAIMLAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTI1LmNVVAUAAbZIJGCtVVFz2jgQfudXbLgXw7iQZu7hGtKbOuA0vnKGAdMcd7nxCFvGam3LI8kQ7tL/fisZArm0hYeaAcmr3f2+/SQt3faPexrQhqNPaL4hPjiaiLHgn2ikvu4dho9QfzDqHsdjIF3YhzyGLTge8giWCQm3KFd6HobHgO41N/3T1ZH3oZ6iBcN0ZJ+XG8GWqQKr34LXb978Aq/g4vzi3IYBKRjNYKposaBiacNVbCzvUvLw0JH0VxuoApJ1Xua5OH/9sw0f2SeygTEplinJMHxV1tN3OVmygigWyU7E88M8OlWQMgmSJ2pNBAWcZyyihaQxEAkxlZFgC3xhBaiUQsIyCv3ReO75721YpyxKdZINr0CmvMpiSMmKgqARZas6R0mEAp5gOCaPmVSYsFKMFx3EpqCoyKXOoeFJJjmQFWEZWSAQUZAqVcrLbjeqRIYqdGMeyW60K7+TqvypkjmSyFECXipQHCpJbdCeNuQ8ZokeUVg0ltUiYzK192wQqoi7XICkWaZzYRyjsqZNYbqVx9ZuUCJjpvQgeSE11Drl+TNH1FFnSSpRIBDqgE4xR5lt
*/