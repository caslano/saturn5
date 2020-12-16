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
434yfU+a49Pv2f2g1c4um+9pt5c/SV3MZ1kXEoxP97DDaGqR4dy+R3QM5HNNgA31lDweqs9hYf0duke8rnFrlFvuQXm7/V4bNU7Nt0dYnIp/FkuNn2rs/Hx3szqO0pvkuGt3pLFfmzWpQ/CTyHo8avfws3J+bMaYo19XUPXkem23O8nQsN+g4Hl1nc8vZGj3JBhf7sbjErabeLw0YtPdu5npFja+4PXJeRy9m3yMIcXYwQIjia3+GMf6/8OwTVOcWXS39PIhTvvNrvGyJOH/f+V9n4VdkCfeJ38+dlfleW2Gz3mrczOERc8Oq3Ij/512Vfdkq34R/bwH5Vn82SIsp+a5S+wayh9k4zKRPGbyf7+LvfxJ6vWhXfx429wWv54eNr7DuN3UEl//VP7UXcz8APmqvqD+rWLy53X22kVXHzpssq25DssZ6jBWXpmv/b6z3Nd0Y8dndjabx969OX7u7ALg1cbOFaM59kebzfsg3ToWlUMZ8jsTPyzP+3jV3sSXfJLbG3Uim6vjLOSHeMzeITbu3pnWbPhYjMuu8uf3EEtv91l21vgum0sHTIaXTIc3dorXIUkMuXqn9HI3LFPZiXCpDnnbVc/6oDyf5/gNH1t/J/Kj+HNCqB2QvuoYX/XZqSNymuVfaLfzlLqi/kCpW5Ah3G/e3pHL4ONTfc6u6KfalvTkMfKaHbmtySbc3uyZKQv+FSH/JH64wY5mubwkBs++ozwG6/jPPpN+3uz9HbS8AVPGP0z+m3dIR/4w/tMt+JvUcVNLxBzWDvJzkD5oje/rkBf1d0hPPOcCvMLWiIfy2PV3IbjKuYDKPuXtEROx5bhnTaV1Kx5zfXqi4/trrtqe5KG5C8Sxl/3ABLInsVlPQlw+/0t0tIcqs31YHkVnztjL/eJ29nKfNTWZzc5PgJ0E94BJwl0pIW4wTgJMs70qJA/K8dO2SvxT9qk8GrlPxV7nh7ZNprMao6kMjxeEfdy2yJvWS+lcR5SJYor/N9fjUaYLysjblhqPt9s2/lzjNP1lvgS2a2pJhv3RNvbYSXBvnSTc+iThbjRJuFMnCfeNrScH94pJwu1JiGu757Rpa7Nzbmj/4QqrEE+Km7Qeru5bD2LmVj4/6pM6FoP4OJ/P/y2419xmlm+H5doHbRUvu+kZQCpvxNtwK7MxWxKMOVLG+KBVj/PhluE4+2+YLtatW3IcdY5ZxUEfMqt/jsfb0qERuqHP/jhOuFsLcYEP+QFrK3BvS/1cLeBB3dCaK/5bdtY7ya+THWX5Ygsz37sxkIP+vmcLimnIh+Z59O/BorOt6Ldr2kjGsTY4eAssj/x8HhRjBhWbqHRrBHTAl9MBH/nasq6emwxtxOfbeX2/vjmf91bP4JKt2UfJefXmZnIqOMArGgvrXcVyLLGkOnVZ4uy/oRxrZkssKc5rm00MzlWGONxvq5vpfDUd/9zIUB4Jjoox12aIbYYDdNq48s6mWJZiEdkmnfX7aJkQTx9Hbth0YmKIt6mZ7UxxoB1q7bCJIU7U+2Hm2lR9Pwzmmem8l2Y8+tqPNjHTWbdGetsm47Of5NBNgvkN4Xy1BFPnZ1ttkjwX1WFRzqXize/rCbwj6wD0jMadNWItQMX8fGO7dQCJvtL4IuGts+PdG4edX57OflId5nEWmGHnBFFcRTzE2mFjpOFxBHlRG0RZeLzl+IiLcqGsyfWksyMW23j8zofX2fa7jWhNPF1MoAn10Qc2AllCsBqyyDHD8E7eKLrNA56KA3HCDEtn093HyaZRmMttJG8jEkzAA1yOCfc3jNfT5B02s4bgqjo+taE8ns44LpBhnp0C5jcCX23fMLQeQYb08f7ZYHzw6L2Uqs8ijvo=
*/