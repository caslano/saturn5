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
agP8sW64QRYNiKqWghd7wX/qpntBdg2j+Wxym0yz/Db8kmdJFk7yURLH41EWJXEKpzB4D7He0pC/H8BAihVNAXwMTs+CYzygX3nVSitywy01HG+cLYPw6TXE4e3YeyXG8h0OyyMYQTBMcd0aSbPDFXZeKdQUwnNw6SJOpmmUer8ItZZtweGcCHSTWX7yulBrjR++I3bgvsFRiWMjcXp+zMoHqdU9sEq3yh7+4aJfjtPRLJrSd2/KsEusM9roboCWm4vOfrmZdruFkUG1FQoCPAgpYcVpGdxWkgOmjUlXXm+Co/dKEZwQaMskwgiM7FbaJel1aQVwhWQ4W5eg+APGNwb9MJm+b46FQ2XO4AUb2pq2Aml5UtBKEffVDpOKflypg9NDl+9dyTuV6txx6RriwQvfnfZUzH+FQBIF5YD1EpJMSHvofpYe76vEA4g2e1Sm0XQ8iWJc0S4+LSJX5FZ8k61tdpiYV4uaS6E4rRb2oKtaLfkjcRDd0pfaEHFYs9ppHzZE2KDv/VU4n2QedbXgG4besGWydQpw3IsxyhojESpRNLuE8KPSXUUwBQduqU6GtntHGdpGSyRNpSYKL6PAmdlB11WctKJwUoBMprMkS0bJJPVCUkg8GX8Jb6eTsReojdcPeQV/fr0BQgl7
*/