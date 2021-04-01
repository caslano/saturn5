//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP
#define BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorType>
inline void swap_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void swap_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  boost::adl_move_swap(l, r);   }

template<class AllocatorType>
inline void assign_alloc(AllocatorType &, const AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void assign_alloc(AllocatorType &l, const AllocatorType &r, dtl::true_type)
{  l = r;   }

template<class AllocatorType>
inline void move_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void move_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  l = ::boost::move(r);   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

/* alloc_helpers.hpp
yXwOIL0mqoZCNIWf23gubYhTTHebcQWQnlx2k8Z6BKAZ9u+3c+P9aMx7Gl+zbvwTMHWFn20fhuDHiqc1j1NPSEqAQtLQOfknnDCidH4Qma0KX5Bdqpd9NptUUHVoW3KXRoqN5drvSAQ+lxFHcDj8gIb+Vy9ig5q/Lk2as7e+5poN7Tck4P09q1UOSPZVE0jq8lChX0u0W4Jqykl2K9WZllDRtLSv49PAFLpOJ/vW2+W4OnJ211jXdsgFUMhgqlMpzfzBweViMwrWLtnxlY0BS7k5DRKr0sQEOaBxZs/oRhBg3dY3Des0uJxYcIQEg7UVBq/5Zt5EZOv7MTslZSY1+9zKCyEs23UqZXr2QPXt//vjNMwfatp2hSUo7jSHgtr6BuPAwXGe9va1kheUNa0QWFq4QXnDryKcqb+e97MMGA77QWxNyDW4ofDb9T4GSGKNZy4qYVrkzzQrYGqFUSXKtg0kqXmvpz4+We+VKVJ6PmIbUuI0Nm/62ZEmeOJD7zNJleC2Nb5E+0tLUUPrhMpszCiZxDIoTEGsIBU+JhmYaTgdbxdZBNPSFe/J6A==
*/