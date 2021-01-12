//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP
#define BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/small_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T, std::size_t N>
using small_vector = boost::container::small_vector<T, N, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a small_vector
//! that uses a polymorphic allocator
template<class T, std::size_t N>
struct small_vector_of
{
   typedef boost::container::small_vector
      < T, N, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

/* small_vector.hpp
7HfF/gJ+j/2N2JfgGWx3NMcdMBSeg5HQE14N/oRdS+wO8CJ2F7Fvg4FwNAyCmTAETpDwaTAM3gPD4QMwEi6Q8CfhYLgGDoGvwlvgZjgMvg2Hw90Sfx/MZxweFPsM9Ow3NWO4XxDeCD3+HvBT7FSxM+Eh7Huhajc4wcX8IPYauAV7HdwKP4Xvwi/hLngRfgqbxXL8AFvBr2FHeBDeDA/B4fAwTIVvwwKJVwQ95TwMT2I/Ab+H
*/