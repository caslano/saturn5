//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_POOL_RESOURCE_HPP
#define BOOST_CONTAINER_POOL_RESOURCE_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/pmr/memory_resource.hpp>
#include <boost/container/detail/block_list.hpp>
#include <boost/container/pmr/pool_options.hpp>

#include <cstddef>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

class pool_data_t;

static const std::size_t pool_options_minimum_max_blocks_per_chunk = 1u;
static const std::size_t pool_options_default_max_blocks_per_chunk = 32u;
static const std::size_t pool_options_minimum_largest_required_pool_block =
   memory_resource::max_align > 2*sizeof(void*) ? memory_resource::max_align : 2*sizeof(void*);
static const std::size_t pool_options_default_largest_required_pool_block =
   pool_options_minimum_largest_required_pool_block > 4096u
      ? pool_options_minimum_largest_required_pool_block : 4096u;

#endif   //BOOST_CONTAINER_DOXYGEN_INVOKED

class pool_resource
{
   typedef block_list_base<> block_list_base_t;

   pool_options m_options;
   memory_resource&   m_upstream;
   block_list_base_t  m_oversized_list;
   pool_data_t *m_pool_data;
   std::size_t  m_pool_count;

   static void priv_limit_option(std::size_t &val, std::size_t min, std::size_t max);
   static std::size_t priv_pool_index(std::size_t block_size);
   static std::size_t priv_pool_block(std::size_t index);

   void priv_fix_options();
   void priv_init_pools();
   void priv_constructor_body();

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
   pool_resource(const pool_options& opts, memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(pool_options(), get_default_resource())`.
   pool_resource() BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(pool_options(), upstream)`.
   explicit pool_resource(memory_resource* upstream) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Same as
   //!   `pool_resource(opts, get_default_resource())`.
   explicit pool_resource(const pool_options& opts) BOOST_NOEXCEPT;

   #if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   pool_resource(const pool_resource&) = delete;
   pool_resource operator=(const pool_resource&) = delete;
   #else
   private:
   pool_resource          (const pool_resource&);
   pool_resource operator=(const pool_resource&);
   public:
   #endif

   //! <b>Effects</b>: Calls
   //!   `this->release()`.
   virtual ~pool_resource();

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

   public:  //public so that [un]synchronized_pool_resource can use them

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
   //!   `this == dynamic_cast<const pool_resource*>(&other)`.
   virtual bool do_is_equal(const memory_resource& other) const BOOST_NOEXCEPT;

   //Non-standard observers
   public:
   //! <b>Returns</b>: The number of pools that will be used in the pool resource.
   //!
   //! <b>Note</b>: Non-standard extension.
   std::size_t pool_count() const;

   //! <b>Returns</b>: The index of the pool that will be used to serve the allocation of `bytes`.
   //!   from the pool specified by `pool_index`. Returns `pool_count()` if `bytes` is bigger
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

#endif   //BOOST_CONTAINER_POOL_RESOURCE_HPP

/* pool_resource.hpp
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
*/