//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/pool_resource.hpp>
#include <boost/container/detail/thread_mutex.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! A synchronized_pool_resource is a general-purpose memory resources having
//! the following qualities:
//!
//! - Each resource owns the allocated memory, and frees it on destruction,
//!   even if deallocate has not been called for some of the allocated blocks.
//!
//! - A pool resource consists of a collection of pools, serving
//!   requests for different block sizes. Each individual pool manages a
//!   collection of chunks that are in turn divided into blocks of uniform size,
//!   returned via calls to do_allocate. Each call to do_allocate(size, alignment)
//!   is dispatched to the pool serving the smallest blocks accommodating at
//!   least size bytes.
//!
//! - When a particular pool is exhausted, allocating a block from that pool
//!   results in the allocation of an additional chunk of memory from the upstream
//!   allocator (supplied at construction), thus replenishing the pool. With
//!   each successive replenishment, the chunk size obtained increases
//!   geometrically. [ Note: By allocating memory in chunks, the pooling strategy
//!   increases the chance that consecutive allocations will be close together
//!   in memory. - end note ]
//!
//! - Allocation requests that exceed the largest block size of any pool are
//!   fulfilled directly from the upstream allocator.
//!
//! - A pool_options struct may be passed to the pool resource constructors to
//!   tune the largest block size and the maximum chunk size.
//!
//! A synchronized_pool_resource may be accessed from multiple threads without
//! external synchronization and may have thread-specific pools to reduce
//! synchronization costs.
class BOOST_CONTAINER_DECL synchronized_pool_resource
   : public memory_resource
{
   dtl::thread_mutex m_mut;
   pool_resource     m_pool_resource;

   public:

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(const pool_options&,memory_resource*)
   synchronized_pool_resource(const pool_options& opts, memory_resource* upstream) BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource()
   synchronized_pool_resource() BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(memory_resource*)
   explicit synchronized_pool_resource(memory_resource* upstream) BOOST_NOEXCEPT;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::unsynchronized_pool_resource(const pool_options&)
   explicit synchronized_pool_resource(const pool_options& opts) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   synchronized_pool_resource(const synchronized_pool_resource&) = delete;
   synchronized_pool_resource operator=(const synchronized_pool_resource&) = delete;
   #else
   private:
   synchronized_pool_resource          (const synchronized_pool_resource&);
   synchronized_pool_resource operator=(const synchronized_pool_resource&);
   public:
   #endif

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::~unsynchronized_pool_resource()
   virtual ~synchronized_pool_resource();

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::release()
   void release();

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::upstream_resource()const
   memory_resource* upstream_resource() const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::options()const
   pool_options options() const;

   protected:

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_allocate()
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment);

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_deallocate(void*,std::size_t,std::size_t)
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment);

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::do_is_equal(const memory_resource&)const
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT;

   //Non-standard observers
   public:
   
   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_count()
   std::size_t pool_count() const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_index(std::size_t)const
   std::size_t pool_index(std::size_t bytes) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_next_blocks_per_chunk(std::size_t)const
   std::size_t pool_next_blocks_per_chunk(std::size_t pool_idx) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_block(std::size_t)const
   std::size_t pool_block(std::size_t pool_idx) const;

   //! @copydoc ::boost::container::pmr::unsynchronized_pool_resource::pool_cached_blocks(std::size_t)const
   std::size_t pool_cached_blocks(std::size_t pool_idx) const;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_SYNCHRONIZED_POOL_RESOURCE_HPP

/* synchronized_pool_resource.hpp
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
*/