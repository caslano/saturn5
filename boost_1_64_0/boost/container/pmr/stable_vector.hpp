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
VnQUdunxWNtQHdCRbH69+jKJYWee8pD67gWXb9AaUGaKM4OS6nC/pIlIgJB/1nZnhi/SVyV6FPzVIuLNz4ngIvzbtvZ5DTA3L94adIYC0j7i7loWnQXHH7+2bCz+OqrtYS+sszm5s5eXJvE95Vz9AhGV1v5wTP1rXpH/+oxGEFqr2VmQQki3vQgwrjOLPPpAxv3hJipZjIbDSKyM7qAIEycMwHcN9MvGVmszggTKeGCf7kX1Hyms23Dg7y5BevzuzrvpuOKSyNUd/ky5il0q+EZchzYyTlFEziujfOv98bS019m5wvaUSRVIKmK4f1Muwcp7Y0sbcnPlJ8STdhhYsbZMdak+Qnk+E0A2zpXRPJPgD5jr+2YkMGYXjJOQSI2C23/0f+ePKHKyZlBTaLA8WNQa/OmpluzlYzYmWFrIel0PUvSuat1NWBLts33Nb4rVHw6/43yqbyXZpG88ebDJMoimal1KgwZNt+1RoOFGl2d1ZYQTLnZoM2o1azTjjoM7wJhWlUigKByezJ9Ne9QrzbbsA7qbyXpzNirdzTxqElrs1JEhwfISCkUomw==
*/