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
Ng0XeK/Yu84KzsPzMLoI08gMKq2Es8N2uxuPx+BP4ggn8fvZ40GDi8MIC/zVaTAdT4JQ33bd2Rft3fGFHyR3DmenI3j18ujA+Q9QSwMECgAAAAgALWdKUu77WLqyCAAAPhUAADUACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMTU9QVF9QVVNIRlVOQ1RJT04uM1VUBQABtkgkYK1YbW/byBH+zl8xVdFEchTJ8eWaXpIeqjhyo0aWBEm+1IABYUUuTV4oLrFLWlEv99/7zO5Sb46TtDgFtkzuzOy8PjOTzk2DTv6wT9BhcfTNz8L+LPDBd8000epXGZZfZlgsPpP7B8YbfH/HVV3acX1etOi7uD5T03It/F2v+e/F4juuu2El+VeXmW8W/CfeOE7Pf66KjU5vk5Ka5y169tNPf6OndHZ6dtqmtyJPZUazUuZLqW/b9Dqyb/6RiE+fOkb+3CZZksg6BwLnSWrIqLhcCy0Jf2dpKHMjIxKGImlCnS7xkOZUJpLiNJN0Pp5cD0b/bNM6ScPEy9moikyiqiyiRNxJ0jKU6Z0TUwhdkoohAfKj1JSQWZWpyju4XlIp9cp4MayEyIwicSfSTCxxnSgpKcvCvOx2w0pnsKQbqdB0w9oVnaRc
*/