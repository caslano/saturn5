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
jqHwFIYDqK8VunyHUDagXQuLM2qwAgeCmJuBw3KcL9iomcTiWYOdQIZNQIhY5bCy4Sy/Q2Zjm1CcKF3hnkC2uJ3n+/omsBnm++ceQch71FMrhM5GGRpmOgb9VShPlvktz0wXYslWgdpotjP9OJ65LEu53GvrTVoogobvdUGswW/7J8YqjhcCV/HlOoK1L5oHNx1ETXN0nWct8MKUI7sIGgQyxwFmx2+Xr1ZRSEaVnpBLG98YFE5uEm4of+iDldAZa3jJzCDq+tH6pkFVIVt5VwKq+ZKzrxSDw/IvrTIcYiURupDLNctUTWBwHLV6kxqMHYc4AuaV3gJFQ8uppMY1lyHAY46E5jgyXh16+zblHShY4lLCJiWXQ5PG/a2Ooe84UdfdMxh6w60OQsuxxoVGYWCZV+bvdecvakUqPOv2WYEumSm5IQA5IQZnRFD11fTe/wwj9JTzGmuNEZd3tCI4ywqb8dkdor++LokeVOFMNg29B6Fv7CUvmJjRQ1MnDaPkjMZgf3/HOeVzhi7sGrdsNE0KlVx1tiLabAF7wOQH5ildQ+gPd5zAbnuKX5hkP5gcuiHUK9ObTG9X2dmu7ZpH635WmpnlTS8Zlek5M4PkeookWwgwfZgUw0wSpnJglBxZlBl+ZxyQxYrYceS9
*/