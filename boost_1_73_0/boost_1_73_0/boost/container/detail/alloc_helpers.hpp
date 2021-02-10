//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP
#define BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorType>
inline void swap_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void swap_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  boost::adl_move_swap(l, r);   }

template<class AllocatorType>
inline void assign_alloc(AllocatorType &, const AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void assign_alloc(AllocatorType &l, const AllocatorType &r, dtl::true_type)
{  l = r;   }

template<class AllocatorType>
inline void move_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void move_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  l = ::boost::move(r);   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

/* alloc_helpers.hpp
9sENGjP5CXf1mcCofle9NZ/38WP5bzN8WPZfO02t0fe4AVqBhS4m9no04y/u0VDL7bax8aYYoV8s/ftiuQUz2nqfPH/pvfeXfrKxvDzvL2zsFffYrK8WyXoVwCdvuV5Yq6GKOr9FGp5hIkaavn+0AWTXtlzgbdLfcP3GdXAWhOdBGhpzalDDVV9sO14swFvGIfbe+9VDQcBGc2GVHtRyXDCwu3rNMVZvzK/ox337leN/UEsDBAoAAAAIAC1nSlKL194D0QMAAFYIAAA2AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fU0laRV9VUExPQURfVC4zVVQFAAG2SCRgrVRrb9s2FP2uX3GnYYMTqHKaIui6ZsVUW16EOJJgyc08GBBoiYpYyKImUnmg6X/vJSkvz6H5UBk2ZZLnnMtz76W7tmH/hz2Wq+jgu0+mvxk+OO5Accc/01w+D8iyWzAfBK5xfIHUGO5Qt9kevAh1CyONygatY/WeZS+QW6sg1c9YgdeZesUZgxzwE97edOyikjCa7MHrd+9+g1dweHB44MCUNIzWkEjabGh34cBxoWf+rMj1tSvoBweoBFK7DwjTigkQvJRXpKOA7zXLaSNoAURAQUXesQ3+YQ3IikLJ
*/