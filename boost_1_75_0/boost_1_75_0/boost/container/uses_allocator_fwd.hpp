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
NTXytsm9fgSMiCzJaXJ5S+zUHt/zXrzfLtS95z00Dn2S3mPKtWkpG0kyKwrePQ8Xhc2aC2DBpQrOQR6apWmbmztFzNR5f/ojfV/1w4ajbGS9p7JRw+uXSQX6feNHnMzxykbefAeyFnyTxKHlxqYi3O53gb523pSV3mamsjI4MJJEIqHh8CHy+Y3KMLRMTilXDu2KiTf6M11S0qpTzJQH0DpaxpGrSvxPtcw9n8i5HPPI/labd9conWh1EhthuVFdgkVVGKVxpTUJhYem/CNxYBnky1XsfHmivYhZfqptNsb2W6jGV5l3shVQZIwxomgGuHby094+NQHrfp1F6CuWJQHzfHvZfPygwSnetRt6fY6lh++hSH2YoH/qG7knWGuCb3+taZbvrYGNMWFewdCsAfr9OsldndsNqUTT9FzdBzdNEkRArMM4v+OjqJ/RTgcbAYbL0b/CJJxKNJarBkYNMx6+/uHtJ1lkUep7YJGsy8alDrzFahtu6mxYXg+LfZiGkCsuBi13nm9OyJIXxgpaJ0ZmSK4jc82B+eADNe7CPw0aJKFGKWHywo9Cf4Icw3SDHwwCAAxKuW4tj+a6Lx7W7IdJIPB09TAWyMbh14xzTXxNsMmJxKEngmdmfj6cQ25knw9IcJ0bP5AoAgHNtxtQ5D0Eh99p69gZH5CO8HDu3UuD8Yhl27J6yUO/x48eFdgPpc9x+MEclvSWox3H
*/