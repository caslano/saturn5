//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MAP_HPP
#define BOOST_CONTAINER_PMR_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using map = boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using multimap = boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

#endif

//! A portable metafunction to obtain a map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct map_of
{
   typedef boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

//! A portable metafunction to obtain a multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct multimap_of
{
   typedef boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_MAP_HPP

/* map.hpp
HA7HwJEwDY6R8HSYDvNhBpwCx8G7YSZ8EI6H82A2XCjpFsFc+KjYZ2Cxec8unCz1Dkczpd5tpd4doXofGqwJO8OWsCtsC7vB3rA7HAR7SH17wkw4EGbBfnA8HABzxJ8L+8BJYp+Bhr7fVt1/q+rFlG+craCqpdZX9HAVbAdXw87wWanHc7A/zAhhnU74jbTbUZgNv4UTJbwInsaeJfZSWbf0j2K/LuuSbhb7U+hmkjsg9lkY
*/