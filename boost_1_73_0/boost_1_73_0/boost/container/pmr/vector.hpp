//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_VECTOR_HPP
#define BOOST_CONTAINER_PMR_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using vector = boost::container::vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a vector
//! that uses a polymorphic allocator
template<class T>
struct vector_of
{
   typedef boost::container::vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* vector.hpp
8weiEKQfiXplez+k8GeiWPJfiFIYJtqJLkfHduFvELxd/AgLSB78dxKldfUjgIoi+jDR7kR3EO1JdA/RBUQ/ILqQKDJA1US/ILqU6DGivYh+TTSBKLZoItF+RM8leoGNv2nr/xdr1wJeRZGl6z4T8yAvCAEDBLwgBgh5EYiCyc1DEsjLJPIYkAskwUQgyST3Kq8ZeoyMxgjiuMwyrqPiOp+g44j4+BAdFgcVmPHBIL4ddRRnYLOKr8/hY3e9e04=
*/