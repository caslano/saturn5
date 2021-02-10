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
gFM8PMKubxEfxa/SyA+pKjj5sDdjR0Pv++WpXl+Ykw8TWpSNcKTCz2E0CS+iSZQtvJDo0/CibhwHx85gNs7msxg+h5P52Jtxi9psuhh5cvPckU5MqGymrWvdWGov6X5nOI9v4uQuzhO3lOSkdN+wQToeQzhJExSii9ke+Z51CgOcHR8G+5ldJ2m2p0+9lfcvUEsDBAoAAAAIAC1nSlL4cGiYOAYAAKgOAAAzAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE1PUFRfUElQRUxJTklORy4zVVQFAAG2SCRgrVZtb9tGDP6uX0F4wOYEihwnRbNu3TAnURutjmRYStsMAYSzdI6ulXWa7hQnQH/8yNP5JW9rPtRBJPnMl4fkQ1LeVQ92f9jH8cgcfPeTmv8UP3hfKU0a+YVn+mmFNP0G3R8qXuH9Ba4GsNH6lu7Ai7S+Qd9opdbXW3pO0xe4uyKQdBmQ8lVKj3jSaVr9E1nfNeK60NA/2YHhmze/wh4c7A/fuHDKKsFLiDWvZry5duFtbk7+Ktjtraf4ny5wDaz07hlMCqFAyblesoYDPpci45XiOTAFOVdZI2b4RVSgCw5zUXI4iSaXQfjehWUhssLauZMtqEK2ZQ4Fu+HQ8IyLm85M
*/