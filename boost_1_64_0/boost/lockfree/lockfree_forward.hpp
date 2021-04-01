//  Copyright (C) 2008-2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_LOCKFREE_FORWARD_HPP_INCLUDED
#define BOOST_LOCKFREE_FORWARD_HPP_INCLUDED


#ifndef BOOST_DOXYGEN_INVOKED

#include <cstddef> // size_t

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost    {
namespace lockfree {

// policies
template <bool IsFixedSized>
struct fixed_sized;

template <size_t Size>
struct capacity;

template <class Alloc>
struct allocator;


// data structures

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class queue;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class stack;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class spsc_queue;

}
}

#endif // BOOST_DOXYGEN_INVOKED

#endif // BOOST_LOCKFREE_FORWARD_HPP_INCLUDED

/* lockfree_forward.hpp
h32s7EliFVbZ9LGhY9VBcHb2Y51jRb0fIBE0ULyjpg6T30+/hDbxgjlhJ3R4rYupUqAHMn9clrsbOgeCREul2WZehMK+TRjcTN6jfuFvxU3Sb7+m9nxiSXADlOKCg2eIOFRIB1iNjr8aUulHBR0RecNV3bGwvPKzZRPscflzrxIZRBiR+W+gEVCgBvKJjMJuI2OKWRvcIj19N+Fr6HkHgbM7zDK8Jzj0tIToSLXPLkrJBL4C6iJW8Y9FQF/KkJtYgzGmojcIFZmHTYkLku0JF6f68SM/ffSuKVD4t1iowJoNuE+M0/dz8vaysKT6+Tzyr7cQGd8WnnsCytu1nA/I80Uvvh6KUYZIivW2hfil9/c0FuPu2ZuINNwA0oqJzkrZCm+lbf0I5s56poPY2UrPMRa4C+vE5VZMGxszTOjtgyACHpo9iYX7u+iscUCp4ONTv1SK1HdHt538nBAJMHA7bGdbooMWCdMncdxMAzLh3jHUZMtqVu0FHIDbErw2MECO8tK+d7tzWucdJlswDb58e0oxkKQ1s7Y9OlMepDjmPnw9yNCcaY0Nno59JQ==
*/