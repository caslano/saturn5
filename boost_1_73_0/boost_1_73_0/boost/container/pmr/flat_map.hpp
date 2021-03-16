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
kJ31HrlDsuyV88rmn2m/1n1IdflZ8L+yNyiH2tE+T3VZ9a/syZhX7eiy6hLvvJOJQsefdHhOT3bYIT7ZKN7CqtozvS7zOspXk5xpT1aEiotqvb7akpNNvcOWLJrnJaQ8C890FtYtgyDlbPRkSHiFt8JTTQHZyS6Ll06+pkBpzNNCASHW6baR3yY43Va0u063CQcsZxPUxXqdBP9eCa5AlHA7bkuXP+etEb17L9j7zohtjy3Kal16LCPl2vqeS+w=
*/