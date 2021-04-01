//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_DEQUE_HPP
#define BOOST_CONTAINER_PMR_DEQUE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/deque.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using deque = boost::container::deque<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a deque
//! that uses a polymorphic allocator
template<class T>
struct deque_of
{
   typedef boost::container::deque
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_DEQUE_HPP

/* deque.hpp
N8RJluL6h04r7Ugvse9Ujz8Mmavtj1j+rg157xi2ADz2jm8H5z/zBIwU5BTWyWjqrGUELxHiyY5JCKwrLYfKy8JY7tECEJk1C4anRoEIPF40mQIEirCbq4a1InaxLmSkiZfmFtjPrtteUZUdGCHKLfNjDnj/IQJZu6OACpRNlz74iLDiU+MkPYVBtaJM4zN8vroV0gSUVagmyA/Xu8l2WVorDsi9b9H/Sln8Iqw1VamcKVQus+CwLOWjuhc2l5g+FsRyoCsRmyfJZK2zCaXoLvy8fuUmVqaCEc+IAo5mJrpXdEdorWYxquEN7iPWSCZGwDr+6jY115eymXcukhT1jmG5OzqT8X1Ljp95Aq8U3iW5xLH1kQDNnU1izRIPz8kFWUmsIcVCaDNaWZ6GcYjJ4pPKE3VxYgkQoU+LmgFvT20Mwb1c5UlUKk4j5M/37P/Wzfz+3+7bZxx3oCiMlBL2syQ4/4yMeU6p1aOYVnz/ytf1Yft/NRhwPx7DWjmMK0bZcKX9rVjdBLgfqJfIMmTQpkQuZ2cIOhnfuOgaFPS5KX+FUDGNXBB30R/eFg==
*/