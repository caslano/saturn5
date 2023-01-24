//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP
#define BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/value_init.hpp>

namespace boost {
namespace container {

//In place construction

template<class Allocator, class T, class InpIt>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T* dest, InpIt source)
{     boost::container::allocator_traits<Allocator>::construct(a, dest, *source);  }

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, value_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest);
}

template <class T, class Difference>
class default_init_construct_iterator;

template<class Allocator, class T, class U, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, default_init_construct_iterator<U, D>)
{
   boost::container::allocator_traits<Allocator>::construct(a, dest, default_init);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class Allocator, class T, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void construct_in_place(Allocator &a, T *dest, emplace_iterator<U, EF, D> ei)
{
   ei.construct_in_place(a, dest);
}

//Assignment

template<class DstIt, class InpIt>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, InpIt source)
{  *dest = *source;  }

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, value_init_construct_iterator<U, D>)
{
   dtl::value_init<U> val;
   *dest = boost::move(val.get());
}

template <class DstIt, class Difference>
class default_init_construct_iterator;

template<class DstIt, class U, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, default_init_construct_iterator<U, D>)
{
   U u;
   *dest = boost::move(u);
}

template <class T, class EmplaceFunctor, class Difference>
class emplace_iterator;

template<class DstIt, class U, class EF, class D>
BOOST_CONTAINER_FORCEINLINE void assign_in_place(DstIt dest, emplace_iterator<U, EF, D> ei)
{
   ei.assign_in_place(dest);
}

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONSTRUCT_IN_PLACE_HPP

/* construct_in_place.hpp
9ILk3ILvmLzvmLzvmLz/6zF5/zPfB5OgjzjfCX/798GTv1qX7Bnzo6vOmsKy4yawRO06SCvTYYGSHsw7pANzDmjBHIUrMGvPZZix59Lu/sofNHMFu8gsKj4NS4P7gW/B3CcGDF3D4apdIJyz8gY1C1eYvVej37Yr3fWE5LIqCMsuA6+kfLCNyoA7QW/ByC8WNJ3D4aw13rc/8IHfDmr1W/6YlQ8UVNVBIt5jbVU5BYlFFZBWVg15VfVQ9qkBLjuEwunHL0BSUbff3+OdsQ2CD/VNeJ/2GdYfOgZblU7AriNn4MDJc6B89iIYPI+Ci/YhIKNqCAUhLt2Rh2e77BgG9cxWKPvciG16DbZv5eCXVgiOMVnwIDQFTF/Gg45HJCw7acTZL5G9Et6r8crTGdE9/ReaCpb+iWDmHUv1n5ZdAKf/brnC6jM3qP0G5xkgvbv8Tf+Eb+o/OfVb1J6BspO4Dl55S6zjt/TfFs17/eLx7KIzv6n/5PUe9YvH80zI+6b+UzC06RePF4z3N2ml1RBV8AFepBaBa3wOtrNpYIH74Bqeh5qur+CsTSBV/mt4PFIHKesSxyl7KyAJrnm/AU0nTlkS//+Kx0OTslvRpEJ8rYWec2oP4EjrJxqBPnoDESgSR18cX8GXeLyRvfB4o3rh8Ub3wuP92AuPN6YXHm8st13/p5xXywu882q52C4h3nm1vPNru8+rJefX6qOe
*/