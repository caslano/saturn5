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
PvD2H4R2fjFOgsnY/wz9g5eHt87VukdXvdY1Jlb/ibFE462WSgmkoNete8qKoFHaDW7Pbop3I4TlxAZ+B9sw8TFqWhloxk5xokzelX/TKJRgd3VsWmTbkmUO2ul8T6ZREp1E49ghRP14x5z6n0fn6M7xqrlj198C/tjejUgj3cdNN9g1OXpqD+0OnMfLdPHMAn0cKq3RuTBwRh9HwXh0HIyD5NIZ5Xk3mY+84WusL5yvi6PaupaN7rp1I0ad7VlmwmTdBM5KnHJkJ4XVsMRB11M/uZiG8HE0vvCdKcc9iBw2EaTRByowEcKOI2JQZ5IWLNGzE7wIP4TRpzCNzMsAKeF068z3Yt+H0TiO8H3neLpJzfno8yo9fjr2w/f4htXrH+648EBwk8M0DhI/PR4/LXcShYkfJtZWOvHD0Ti5RJ1//GcUzhD2y8UJ8FkUG0ehf0KBxs9KWpnnBZ439R9QSwMECgAAAAgALWdKUtyfhjdoBAAAkgkAAD0ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMTU9QVF9QSVBFTElOSU5HX1NFUlZFUl9CTC4zVVQFAAG2SCRgrVVdc5s4FH3nV9xhX5IOwc7Htk2b7SxJacOEAGNwsp71DoNBBLVYYpBw
*/