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
pifXvYapyKyZmZ/ybg7TSHE9fr1oC9OS2TBra3fgMkwnrRk73X8TzJ/MntmHqksOwcLIrJgNq91vFiyWzJxZo9f3asESJNNY1voISyJTMTtS6Xg5WJqUi1/k5ChYplTD4kVvD8MMUl+ympZ9CcuVrOH47gNhhVLPojac2AUzW0P/8V7HfLWEqcl4Lke32W+FeZOp+Bx0j11gOjILZv9+u+AL8yez5FbOSakvSLKo720rwfRkfEYb6w4thMWTOTAr2+dNBCyJjM+oVvl3E2Epkt370LoLLF3KZZjnpGhlRlLtqz0rN4blkPFem8yqPxSWL9nGMn1OwESycc9e/9K4J0xFxmsvVdDBFKaR4q6HZ36Dacl4DZ2951SG6ch4Db+NPaHUEEhmx2xLuSWjYHppvzXzbtaExUs29o9f/WCJ0n6V/b5/UeYgxdW2KWigzIHMjFnm2+tKfZlk1swaNjxbEWYg82BmPfXVcphYK4Qrs/jAYc4wDZkts5Qy6wJgvmR8DtNHBCi1+5Hx2dZY+yQPFkhWiZlb7mI/WDyZPbNOU5/XgSWReTKrcuvpAVgGGZ/R8dTUQUrtkm1TXxsCy5fqa1nrv7aw0utK7jXIxIBuWd9hKjIet6Xa4zSYN5mamWmu+zaYHxnv9YgGH8NhYWQOzP6a1fA2LJ6sMrN1B18ugqWRVWR26kEbJc6wTjrPej7frNROZs0sssqCYTDxl3F9HTu7XIapyZyZ/fLgoID5kvHafTq8/AsWSP9yZOb4v+jnML0U13yXRTYskcyeWY03l9bAUqQ1o52yC2AZUp7NzZYkwXLIbJh1Wdn6NSxf2i92ZG0LmNl64zW/Xm0fCPMm4/OL0DRbD9PRv9yZ7Q+o3AUWRlaer/l1XXlYApkls8HDvbJhSWS4jxxAj0seTc+EZZPVLLaBgnJp0n87TLWh5B5zED0e+iO3HkxPhr6QieCXNVbD4slqMls/YFFNWDqZBbPQqB0VYZmSnWpUVsByWC5BgtZ/9+4MTLex5PWITCwe7tkD5k9Wg1naDk/7IusfmUiGNYNFTEyK1cXasHwynNc/rOtyj1Yws020P7NX9geU+nRkWDOEHktfuXMWlkyG5xiZ6HpLu1vpC5kPs7J7S15X8sksmY2Nq5EMEynG1vJcmcMwFRlyGUyP4vzbizA9GXIhE6F7LxWfg9GhiSxuiIgeXyfv9nlYPhmuBT+stsu8jzDxN/WFWUMLN1NYAzK8D/9h8y+2GQ/zJSvNbOjycddhOjIztubRX3PLwjpJa07qH9oS5k9myuxJ3ydxsAAprnerMhVhgVJc3deTgmD9JRvtZu4BC5Ksivm53rAhkr052KMjLIzMnNW3o+oX9+LzLDieDN+3GSpCRmTvrHwDptusPP9+2vBKVs4wfzInZue9Ot2D6clqMHtddcfcIovUp5Fh7sNE6JCJc349iHNetaXEwuicdwq4egWmJ8Pr3w9bc8TgoFwLyPA57XD6Z6VfhlYoshEiY2vJz1dG0GOHmVnViywiJi1VCL9iG0l9SvnT80yxDVJtK7FwERphETbwWJHVGhtG5l1c3ygR22jejWNdi+z79yQy1B5Jj0tnti5+vutHZ5NprIvW1IvIEOvWH0OLLCY88XDJmlEiPNTLvEpssYVmkGnLFsXFUH8flWk8odhitKdK4kZTbis8FhSfL8NFEBl6Nka0ERsDZ46ChZHhOk8m1h9Kfw5LIHNhNjlv7TdYCpkzs5rbq3yCZZKpmH2Pdz0Fy6F/OTDr7+OwFlZIZsFs2bBNrWBmp43tgEO7dTA1Gd8vpPP33TAtmSWz+vsca8B0kk3YUDcO5k9mzeyyR34hLIiM9/Ouy7rrsDA=
*/