//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_LIST_HPP
#define BOOST_CONTAINER_PMR_LIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/list.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using list = boost::container::list<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a list
//! that uses a polymorphic allocator
template<class T>
struct list_of
{
   typedef boost::container::list
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* list.hpp
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
*/