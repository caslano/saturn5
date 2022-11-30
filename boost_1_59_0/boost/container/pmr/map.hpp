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
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
*/