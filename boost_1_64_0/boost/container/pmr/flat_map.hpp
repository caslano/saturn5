//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_FLAT_MAP_HPP
#define BOOST_CONTAINER_PMR_FLAT_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key > >
using flat_map = boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
using flat_multimap = boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > >;

#endif

//! A portable metafunction to obtain a flat_map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_map_of
{
   typedef boost::container::flat_map<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

//! A portable metafunction to obtain a flat_multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key> >
struct flat_multimap_of
{
   typedef boost::container::flat_multimap<Key, T, Compare, polymorphic_allocator<std::pair<Key, T> > > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_FLAT_MAP_HPP

/* flat_map.hpp
Imze1S4fKNKzacJD4wa3EYziZbsKNowE0T1M2RYTbVhgyOBMsl+qKvXZyGUMK96uDLY3IiylL+8czDGJ43kz7ljmjsDUE+9qkBWl8yYKWvQtjJSfmYgLgm8oG74pVRO1+dl+AOScB/Ir/3XEi/mcHUAFgMjqC7vaMwjduGCFcSTCnf1ghOLohm5myNfC7q6m7jxRWa4y7+rTGnk9mrAoJA8Gynzg3N0HnOqmDww6LAI4eFpWPCNfzIftpEdG4YjTJoK5a4kD8O7jh1GrAd2JOi/ksFUXRBvP8+QRtmoms0N1pkKZMRxLi/GUq7Y/mo3QaG83kVW56JX7IygZNggQFXKHczN5eaq/4/beXcCJao7KW4GQ7l1BFofyPceynpnhl+CJ+Vn7LWRZ/WPZAOikuSLpg+H34qlNPDXzXEO1MBs1XksdGhMZGVyJqid+k8DGDtYri2A70kPPuyC3NhLtWeCwEfes0pAhl86EmTTn91ILnshS7VOPOpvdh2drWTsQv+4+RPvOp0l86uWwx4EKAYO3+eIuITy0ZwQnTGOYZUmegih2XW35kNUWYQ==
*/