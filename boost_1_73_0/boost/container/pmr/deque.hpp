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
rDL0XDLYiqfnkmibz6zfT+na19IsY/9t2qfnnLdsPjO/z620+nhyzzjLZ5YRZY2hFub2/sHKTx873m3zmXUZYfOZ29vG5jPrN3S45TPr18HmSzLHi1VnPa89YvOZ5Va20ur5ytfmM8v9dpjlM8v90OYzy33O8uljxwctnz52zLJ81vxn+fT8lzFU+/T8t8Pap/Vx4ulu2qePCTfZfGa5T1g+PSdm2nxmfm1tPnPbQq266Plv
*/