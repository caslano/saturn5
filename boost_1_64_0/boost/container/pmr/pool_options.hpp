//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP
#define BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! The members of pool_options comprise a set of constructor options for pool resources.
//! The effect of each option on the pool resource behavior is described below:
//!
//! - `std::size_t max_blocks_per_chunk`: The maximum number of blocks that will be allocated
//!   at once from the upstream memory resource to replenish a pool. If the value of
//!   `max_blocks_per_chunk` is zero or is greater than an implementation-defined limit,
//!   that limit is used instead. The implementation may choose to use a smaller value
//!   than is specified in this field and may use different values for different pools.
//!
//! - `std::size_t largest_required_pool_block`: The largest allocation size that is required
//!   to be fulfilled using the pooling mechanism. Attempts to allocate a single block
//!   larger than this threshold will be allocated directly from the upstream memory
//!   resource. If largest_required_pool_block is zero or is greater than an
//!   implementation-defined limit, that limit is used instead. The implementation may
//!   choose a pass-through threshold larger than specified in this field.
struct pool_options
{
   pool_options()
      : max_blocks_per_chunk(0u), largest_required_pool_block(0u)
   {}
   std::size_t max_blocks_per_chunk;
   std::size_t largest_required_pool_block;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_POOL_OPTIONS_HPP

/* pool_options.hpp
GcMnHJNFc8dFN3YBtiq9SzNdRrMs1e2YkslcAESuMxBWja5k4VFz51xaahyoe1+iu3xgloL2jWiLWDFh/9dhazyBavpNpiFF+qilsK/EMBg0KqNBvJW6G+morke0EfBOC8DHU+v4O0ztGgvxMm/Voa1tPRlN11vbtYjy6ZFogAnth3o4bGcL6NcnaPO8Ax3/3GWdIJGbeTAo8d/mD048sbaOyPRw8+BG9kYVRgH762YOPpuejsn8Zcz7S+apsdD1+xu4Qbtlu+eK41/5N+eBZ48i8LnIIdPLONci1d9oHpmHhiJWcqLo+XZ8ol5GhtdMdzmtxjqf42CDq6ns2PTKBY5SfozhZwhZG89LJmvgfk5lBVPvXvY9PbsPWjENjOrM4nbOf1by0X88sNH9fYiRTq5Na8K3IRAP8lx2GmS92zya02qItdt5+uLkziN3Dmc8zSpzhegP7gMIgD6qVxEpQ+B+DB+EoG2KHhO3qukQv6CmV1soJm6mFYQIwB1bwrcV+xahKOgkjG6i9m06i51PL85GuCOFW2pyNpDqDsVVva8winTcd8ijXccI2w==
*/