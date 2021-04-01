//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SET_HPP
#define BOOST_CONTAINER_PMR_SET_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/flat_set.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class Compare = std::less<Key> >
using flat_set = boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> >;

template <class Key
         ,class Compare = std::less<Key> >
using flat_multiset = boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> >;

#endif

//! A portable metafunction to obtain a flat_set
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_set_of
{
   typedef boost::container::flat_set<Key, Compare, polymorphic_allocator<Key> > type;
};

//! A portable metafunction to obtain a flat_multiset
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key> >
struct flat_multiset_of
{
   typedef boost::container::flat_multiset<Key, Compare, polymorphic_allocator<Key> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SET_HPP

/* flat_set.hpp
B1qUbgUvg6CICDaGqs4xVrXU3Ui+r3CGInA2ZM9Nqd8LEU5Bm+gX9L+BflLnlJA5ihccNxseg5sKgSSUhvpvm9MO6+IAtUkIb23VkCHES6FumRUu7Warrc4pHxvLX6tt6b7il9ub/iJy5gEH1BdIFjc5w1GcSzmhV5JxwFYk+HqWpeSeaxrY3srQzFXCSR9yEr0aDVRKAlZvdNu7GFF33nzWSPo20O8U+wvfd1WKT0fUoTYfudCTOMb9biu4r62gcdyg8aiCQhG6EbbCjrxzWKEgDK1vMRHl7zR8f7ySZ3iPLZFTJNil5w3kYg//8cxrdnbYdq61qjLG8/bJraRhs2gqUl66myUvNFyKHf0VnsS2mRtiR3svI78jM/zBUyzI/Dv8zLrvb4bHR3P/wuaYLXuSEOW2POtiCI1HNBGotp7KlsHGvSxjLrZS1CGIHwAXgj7S99XnNskZVZdVRnP0/aJfROaZFvvvP8N+agaahqV9hdarMm3Vfwg7Vt0FWWE8bCPkVPlBwCev7H1Mh9FA71foI86mT7AG5B+TV5vwWDkalmLo7/02QYR9mQ==
*/