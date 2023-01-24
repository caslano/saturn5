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
4BPndrjtR89zx4f68MerXH1BYytDliuO3lFxTqZoScmTCQkKIxlM1rn7zD6TX/9/kL//QZ55dINpKcw3E4XZaLIFgu+WSkDPfvQI673oeQ4gpgNbq0gShXJ1c5CWhY1+fm2fG0nztQwv8gStDEFaCqSW2sVMwXicr7mDhVDUnAKKHElIWFItIVhwBSLhGVyAkOfgXHABssyxsd6jsnYuH6e9rLVzIcCF119TFiAEBSB1mytiBKBODKLx7Wd1AkDDB3jvcN7hvGU0Hdaoa7YOg/vfQfDjnaJuhzwXbmkEPzzrXei/d2Ll51mxv0i32+Py+GFePPqbaLdPT1JM4pn4CZ0sJVcGcYGAKS3YCexZweYaSRwYzXrRZ5hc48jq7/D9w5Kv33gb5ugmWceQeMNkpPHmJirdZi0/QtesUiTLDCvhvHyNo/19lpM++7LPA4MpX9kq8aqP1yrODfB4SUC5MNRXAipIuwlpoeNgoEA3hf3dEvo4WFPXQ0PqY8Thxw5GFj8q8WMLpceVDusc3WV41/fDleEKX7xS8r4f3uf43re59Og6Z/98g8mV0yyvb1DoXVaSAkNOhiZXinJ/mbtPO9Lf+DzVf/Mhnnmsj688B0nBNhK4RXiwDik23YPae8HjvVBVjqrSlKWJdQGaxDqUErzE+7IY258zszLbNU1NQ9s61+a/9u9bRUKL7sDcxmz3HOCQ49ovHVKM1CiF
*/