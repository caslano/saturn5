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
X1NPQ0tFVERBVEEuM1VUBQABtkgkYK1Ua2+jRhT9zq+4daXWtlicNFulaZJViUM2KMRYBmdryRIaYAizixnEDHGiZv977wygyHlo82GxMDBz7rnnvsZaD2D80y7DUnTwwyvSd4QXPnujec2/0kS+bhBFj9D+0HCNz3e4msCT1WM0gndZPcJQW0WdrxP1HkXvcLdWItXfRBmvI/WKK61lZz/l1UPNbnMJw+kI9o+O/oIP8Mfe/qEJ56RktIBA0jKm9a0JJ6le+Scn9/eWoJ9MoBJIYe0QhjkTIHgmt6SmgO8FS2gpaApEQEpFUrMYP1gJMqeQsYLC1J+v3NlnE7Y5S/KO54E3IHLeFCnk5I5CTRPK7lqaitQSeIYMyJ8yIZGzkYyXFrqnIGm9ER2NEkEKwYHcEVaQGN0RCbmUlfh7MkmausBIJilPxCTpU2HlcvMsqhWq2ZAH4JUEyaER1ASFN2HDU5apJ6YIF6smLpjIzSdZ6LBMJ7wGQYuio0NTRkUbAoWgy5apkFCheibVQ/BSKG/bnG92gJjWjihr6hLdYVoQl3JMvAlNmdJa43Uiei9dlnXKf1CyJ+0p8BJVwcAOwA0GEBPBhAlf3PDSX4bwxV4s7Fm4Av8C7Nmq47tyZ+fYGwy91kDvq5oKVFED
*/