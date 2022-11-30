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
   ~unsynchronized_pool_resource() BOOST_OVERRIDE;

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
   virtual void* do_allocate(std::size_t bytes, std::size_t alignment) BOOST_OVERRIDE;

   //! <b>Effects</b>: Return the memory at p to the pool. It is unspecified if or under
   //!   what circumstances this operation will result in a call to
   //!   `upstream_resource()->deallocate()`.
   //!
   //! <b>Throws</b>: Nothing.
   virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) BOOST_OVERRIDE;

   //! <b>Returns</b>:
   //!   `this == dynamic_cast<const unsynchronized_pool_resource*>(&other)`.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT BOOST_OVERRIDE;

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