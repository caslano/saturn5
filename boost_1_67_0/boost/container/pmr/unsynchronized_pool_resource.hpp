//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_UNSYNCHRONIZED_POOL_RESOURCE_HPP
#define BOOST_CONTAINER_PMR_UNSYNCHRONIZED_POOL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/pool_resource.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

//! A unsynchronized_pool_resource is a general-purpose memory resources having
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
//! An unsynchronized_pool_resource class may not be accessed from multiple threads
//! simultaneously and thus avoids the cost of synchronization entirely in
//! single-threaded applications.
class BOOST_CONTAINER_DECL unsynchronized_pool_resource
   : public memory_resource
{
   pool_resource m_resource;

   public:

   //! <b>Requires</b>: `upstream` is the address of a valid memory resource.
   //!
   //! <b>Effects</b>: Constructs a pool resource object that will obtain memory
   //!   from upstream whenever the pool resource is unable to satisfy a memory
   //!   request from its own internal data structures. The resulting object will hold
   //!   a copy of upstream, but will not own the resource to which upstream points.
   //!   [ Note: The intention is that calls to upstream->allocate() will be
   //!   substantially fewer than calls to this->allocate() in most cases. - end note 
   //!   The behavior of the pooling mechanism is tuned according to the value of
   //!   the opts argument.
   //!
   //! <b>Throws</b>: Nothing unless upstream->allocate() throws. It is unspecified if
   //!   or under what conditions this constructor calls upstream->allocate().
   unsynchronized_pool_resource(const pool_options& opts, memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `unsynchronized_pool_resource(pool_options(), get_default_resource())`.
   unsynchronized_pool_resource() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `unsynchronized_pool_resource(pool_options(), upstream)`.
   explicit unsynchronized_pool_resource(memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `unsynchronized_pool_resource(opts, get_default_resource())`.
   explicit unsynchronized_pool_resource(const pool_options& opts) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   unsynchronized_pool_resource(const unsynchronized_pool_resource&) = delete;
   unsynchronized_pool_resource operator=(const unsynchronized_pool_resource&) = delete;
   #else
   private:
   unsynchronized_pool_resource          (const unsynchronized_pool_resource&);
   unsynchronized_pool_resource operator=(const unsynchronized_pool_resource&);
   public:
   #endif

   //! <b>Effects</b>: Calls
   //!   `this->release()`.
   virtual ~unsynchronized_pool_resource();

   //! <b>Effects</b>: Calls Calls `upstream_resource()->deallocate()` as necessary
   //!   to release all allocated memory. [ Note: memory is released back to
   //!   `upstream_resource()` even if deallocate has not been called for some
   //!   of the allocated blocks. - end note ]
   void release();

   //! <b>Returns</b>: The value of the upstream argument provided to the
   //!   constructor of this object.
   memory_resource* upstream_resource() const;

   //! <b>Returns</b>: The options that control the pooling behavior of this resource.
   //!   The values in the returned struct may differ from those supplied to the pool
   //!   resource constructor in that values of zero will be replaced with
   //!   implementation-defined defaults and sizes may be rounded to unspecified granularity.
   pool_options options() const;

   protected:

   //! <b>Returns</b>: A pointer to allocated storage with a size of at least `bytes`.
   //!   The size and alignment of the allocated memory shall meet the requirements for
   //!   a class derived from `memory_resource`.
   //!
   //! <b>Effects</b>: If the pool selected for a block of size bytes is unable to
   //!   satisfy the memory request from its own internal data structures, it will call
   //!   `upstream_resource()->allocate()` to obtain more memory. If `bytes` is larger
   //!   than that which the largest pool can handle, then memory will be allocated
   //!   using `upstream_resource()->allocate()`.
   //!
   //! <b>Throws</b>: Nothing unless `upstream_resource()->allocate()` throws.
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment);

   //! <b>Effects</b>: Return the memory at p to the pool. It is unspecified if or under
   //!   what circumstances this operation will result in a call to
   //!   `upstream_resource()->deallocate()`.
   //!
   //! <b>Throws</b>: Nothing.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment);

   //! <b>Returns</b>:
   //!   `this == dynamic_cast<const unsynchronized_pool_resource*>(&other)`.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT;

   //Non-standard observers
   public:
   //! <b>Returns</b>: The number of pools that will be used in the pool resource.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_count() const;

   //! <b>Returns</b>: The index of the pool that will be used to serve the allocation of `bytes`.
   //!   Returns `pool_count()` if `bytes` is bigger
   //!   than `options().largest_required_pool_block` (no pool will be used to serve this).
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_index(std::size_t bytes) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number blocks that will be allocated in the next chunk
   //!   from the pool specified by `pool_idx`.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_next_blocks_per_chunk(std::size_t pool_idx) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number of bytes of the block that the specified `pool_idx` pool manages.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_block(std::size_t pool_idx) const;

   //! <b>Requires</b>: `pool_idx < pool_index()`
   //!
   //! <b>Returns</b>: The number of blocks that the specified `pool_idx` pool has cached
   //!   and will be served without calling the upstream_allocator.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_cached_blocks(std::size_t pool_idx) const;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_PMR_UNSYNCHRONIZED_POOL_RESOURCE_HPP

/* unsynchronized_pool_resource.hpp
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
*/