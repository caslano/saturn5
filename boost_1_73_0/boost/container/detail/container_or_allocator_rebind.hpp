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
m+bIuND7KjUc94QyfdiGxn/LVzrxD2DfT7z5brBTzHwR3xo4S0Lzmw77iv0qJEHXqNB/S+Yi+prclToe1PyOFv38qubXcRN9ptdzovdrPrQ/knyE/TwobhLNnMoG9JEyvJ7RMMTe6OMrlU8yWMtA5B1pnWyqzzy21MlVIl+E4Tl10oI6SIj/Kc+0H1foWFLL5DPRf2jlV10u6i7J5Gm3pjHmzCEjt2OsuF9on02+c+xR0fWr
*/