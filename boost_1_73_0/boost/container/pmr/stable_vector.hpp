//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/stable_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using stable_vector = boost::container::stable_vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a stable_vector
//! that uses a polymorphic allocator
template<class T>
struct stable_vector_of
{
   typedef boost::container::stable_vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

/* stable_vector.hpp
fxR7tdhvwtNwO1TjC9b3YbthA3gYNoRHYSN4XOL9DJtiB8dxnAerQjXeYEvsG8XuAe/C7i92HlyIPQ0+BB+HD8Nl8BH4KnwMbpb478InsY+IfRyuwD4ttl959hNPPaDHrgrfwa4pdhv4PvYQsUfAvdip8BOYBT+Ds+BBuBgegkvg53A1PAzXSfo34VfY28R+H57E/hqehZfgeRgeL/M4jPDl+wZGwdowFraG5WEPGA8Hwgow
*/