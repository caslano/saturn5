//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP
#define BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/container_rebind.hpp>
#include <boost/container/detail/is_container.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorOrContainer, class ToType, bool = is_container<AllocatorOrContainer>::value>
struct container_or_allocator_rebind_impl
   : container_rebind<AllocatorOrContainer, ToType>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind_impl<AllocatorOrContainer, ToType, false>
   : allocator_traits<AllocatorOrContainer>::template portable_rebind_alloc<ToType>
{};

template<class ToType>
struct container_or_allocator_rebind_impl<void, ToType, false>
   : real_allocator<ToType, void>
{};

template<class AllocatorOrContainer, class ToType>
struct container_or_allocator_rebind
   : container_or_allocator_rebind_impl<AllocatorOrContainer, ToType>
{};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_OR_ALLOCATOR_REBIND_HPP

/* container_or_allocator_rebind.hpp
82rJ+bXGGv/RebX6mr3Pq0XUebRUeXJerT4SEuedV9uiGxKI0DmS1jVRPRXdoqHlTZE559dGt6iPQZzmUOfXHmlRF+Oi06jza3GaS+acX0vShHxOnHN+7bUWDpmcf0vUvVhPkdW9z3H14ZYWEOc0iJQewylPBUIW6+lMMdyTY4YKdaeHemNOQh/TTeaU55QZgyhJ4vxlBCjmnjrPUYkx/CPIJ4BTbe8kh5l3Xi1uwiT9bzuvlnum2WR8H0zBURBHIXYEGoHjpMgItIJdgrTYUN8OUIrrjtJqB2Mcb07CCd12TmxZwf1x4P+p59We45xXqy/AOa8WCVDn1YohcXJerTEZXXJeLa6VnFeLkwJjyKCLi3mT0RQQI8ODPw8lk2SMAOn5Pz2vFqf1p+HbRsjEWH9EoIn+z+Li+osAOk4DuyU2UL+17jse7/t77u/vub+/5/6PzqvNpBnSDA37Py+2s1OErnzdK90t0T2uXw664uqjpp4pSYlxSSL9nL2JyctVj/tkpMQ5EzzYF5Xr6Sorr1a9ke6ZxAAWg44ZaJISnD/8T8HZI96FtvyoaXqSO+WGhk68mxEHasJGIkZGdBGGsIeHs6GyeboXJmdmiuBW0Ag8q9tJHv6c5Uy/4cVIw9JFjHEFdMrDDQUAo3NRYh5LFHBpYREROt2wk0Zc3JAaGAwRDoiNocDIpDFcRAzphnQals9gcWpIE8FV0kWM
*/