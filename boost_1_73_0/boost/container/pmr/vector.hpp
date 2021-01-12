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
KhgYxHaIvRXWxv6L2Afgi9h/F/sS3IBdIVGOE+Cb2LXEbgujOU64RexkWAn7DrGnw5rYvxd7GWyF/YzYr8O+2JvF3gP7Y38m9ik4xM3xec0SOwKu8nz/w9fhbeJPhZuxc+Bb8H7xF8N3sZfC9+AG8W+GrV2Ma7G/gLN82F44G/rX4ngTRsL7YXmo9jNYjfq0EbsTTMYeIfYYmOjHfCD2NFjkz3VMsZ+Ej2G/JvYWuBZ7v9hf
*/