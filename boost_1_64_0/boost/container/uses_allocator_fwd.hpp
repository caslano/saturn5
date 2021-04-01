//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_USES_ALLOCATOR_FWD_HPP
#define BOOST_CONTAINER_USES_ALLOCATOR_FWD_HPP

#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/std_fwd.hpp>

//! \file
//!   This header forward declares boost::container::constructible_with_allocator_prefix,
//!   boost::container::constructible_with_allocator_suffix and
//!   boost::container::uses_allocator. Also defines the following types:

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   template <int Dummy = 0>
   struct std_allocator_arg_holder
   {
      static ::std::allocator_arg_t *dummy;
   };

   template <int Dummy>                                             //Silence null-reference compiler warnings
   ::std::allocator_arg_t *std_allocator_arg_holder<Dummy>::dummy = reinterpret_cast< ::std::allocator_arg_t * >(0x1234);

typedef const std::allocator_arg_t & allocator_arg_t;

#else

//! The allocator_arg_t struct is an empty structure type used as a unique type to
//! disambiguate constructor and function overloading. Specifically, several types
//! have constructors with allocator_arg_t as the first argument, immediately followed
//! by an argument of a type that satisfies Allocator requirements
typedef unspecified allocator_arg_t;

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! The `erased_type` struct is an empty struct that serves as a placeholder for a type
//! T in situations where the actual type T is determined at runtime. For example,
//! the nested type, `allocator_type`, is an alias for `erased_type` in classes that
//! use type-erased allocators.
struct erased_type {};

//! A instance of type
//! allocator_arg_t
static allocator_arg_t allocator_arg = BOOST_CONTAINER_DOC1ST(unspecified, *std_allocator_arg_holder<>::dummy);

// @cond

template <class T>
struct constructible_with_allocator_suffix;

template <class T>
struct constructible_with_allocator_prefix;

template <typename T, typename Allocator>
struct uses_allocator;

// @endcond

}} // namespace boost { namespace container {

#endif   //BOOST_CONTAINER_USES_ALLOCATOR_HPP

/* uses_allocator_fwd.hpp
V2S4ryFvUNapjVD2xH5ov0iv1yyk3UxqnySDG538J3dpkKGUszL5XY2h//dcPPcj/zmGwgcqAizO5HvikyKWPuZDqsXRhaNEh5bJQw5pSpcRQORIuq9qxRpKfgWDRdDDuEmwNhetZTJxgBtI1p/e1aDjoR7kRjjxiXWW+yU2pFUBc+sJlyY1uzd6l7eev8LnMfQHDhDhibwzCetLcqaIyq/gE55A3UURdLgTiM0U9IXDwcWTItaT3fnf5wjDZWhHPfTUhoEERTIImZO7ox2oQcEjYIZ8577EN87YYAar6YYdhfCo9sPAB8x8Z9szDuZxRAI43AskrTohys+dhXFX5uiQhwq8JJwZEHvPpuq+iRBRmcMknbYFavUuJmN01uqoxi6JwfbwyGgOkwRSFzqJgQ+XaMnGBD6nB9i7mEONcFreBtfLaUbaxuqxh3BevR05OUMf1gEl7wV4XuQiosY5Q79lT67vYQ91VVYLLglFQUq2shcvE1PnWD+NwHG/a3eSBs2qrU8zI5nw6QcfeWfrce63hzAt3AAKrVocRE1CzStYah2MHgizCf78VQ==
*/