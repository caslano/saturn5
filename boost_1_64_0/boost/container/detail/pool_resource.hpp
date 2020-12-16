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
oo4VzH6kf9vbXVgVmZOZvd7C6kQcz9lAZjHr9cS6EFibMPt+PpjVx6u99uUF5k9mMrOXT1gImYtZeo/bk2HRSs54lvMn+re9PsBSySxm9noEy+ZxopYCHif6V0aGMftZjFmFYlXMmr1scccaZr/Rv7nVMWsR1qBYk2ItwuxjIlibMHu9hfnd4tucilnMZHtuMovZJZcnLoAFC9t270e7YJFkJrNJzmMfwuKU9hKUOpO822PzTuOnxP2Pr/uPr3re4wB+joaDgy++uocOTlqZLE616sgwWgz9GE2GpakTp+6qacPSZNXK1KrJMBktzTUshrnGnZoahmGYa9hlaZiaaxiG0X1/bvd1e5/34/F9/1eP5+P94/P9fr4/d77fb4noxcwlWKXIaX4/D6sXdvrDOyxYq8hp7qnCupTx9Tha8YA+Vu8X+r8ZH8wK0jbGbPFDCa/CAmQeZmYuweIUCyoWUiwp6Nxnuojj48sUcfeePGAiLE/Y2VNa3LASxarEcjH7HlgdmcXMrHdYM5mPmfmdI6xL1PtsfdZDMNfIaEtJL/gK5iPzM8veOrwZFiLjvQwZduVa2CRh5pwWlinqrUr95TlYHhkf+5y7+16BFYm4LWdMPxNWIfrMu/6mT2ENZFh/v9L/zbEK1kTmY9bxRO80WKew2SMOuwzmGhVt5m/eMD+ZBybmWayIu+fVj06FJQk78aPfzoFlkPmZjUg9+BZYvhJXRuZlZo7FsCoym5k5VsEaRE7zO39YO1mA2b6kuqEw1+jouFuv/+VLmF/YxJwPLFiILMD7/KA/BMsgi2N22c8vxMKKyJzWUSVZLLOqW1sTYc1kTuuolQzL+jezrH+Yeyas18TBRFy/YjEJ1Ccz8w4NWICM1zPntLAkMovZm1tH3QhLI7OZ/fbI4ONhWcKm//DD5bBCUS/74NhFsEoyL7Nrs/MHwGpF3AtD6g6BtYrxDXx8zV2wHjGGlmcP/woWMybaVhx+70MwHxly/m72fbHNe2EJZDazGSe2ngCbRGYxW3zmGbfBMsn8MLFuC0TOMd3/fABWJqzV/5c1sBrR578OGroY1ix62TU4+CasQ9jgu6bGwnrJMJf6xT6rX7GYsc7mJfPCxL7AT2YxM9+PgwXJbGZdo98Pw1JEnPldOixDxCXPdgdguUpcEY8T+6UKPj6xjVWJOPMdVFiDsJ2Rfz8IaxO9DJ/8wBmwbmV59irWr1jMOOf1YJM5jc9PZsHEsT9IZsPE+UuKsF0X//AlLJPMx+z1W15aC8sX9cx7eGAlok9zbgorE3Hm+ghWrYyvVvTpfntQCNYs+hz5U1UXrEvUq73x9UJYv4hbk9f+BcwXiq43z5u7FRYMibGfflQIlizijn1rcxYsg4zXW3X6+GNheSLnaKv2K1gxjxPH2yoyD0ycf9Ywk8uzTolrYPaHiGsis2Bi/bWTeWHi3LSbzMes59wZRTDP2bTMmJlnmmABMp7z2vNL22BBZrJeEhkfw8Z9I1+FpZA5jSFDiQuLuM+rZ5wMyxNjyD74t2NhJcIeW/thIqxK5PwkrzYDVk/mY/bNe+4HYG0i7rgHXx0J6yZzWn+9ivUrFjPe2bxkXpg8digWr+RMIPMz+znpklthaTxOzN0MJWdYsSzFchXLV3opVOKKySxmH/dWHgWrILOZeef074TViZzmHcmwBhFXs6P8PVibMP+GqffCekQvsy88+ChYzDnRcTeEbroO5ifjcaUbnvgFFiTD+vuT/m++rw1LJbOZrX/plx9hETIPTBw7skXc5JJT02FFwnY1fO+HVShWR+aFiX1IE+9FrL8WxdoU61Csi5s4L+hR+nQlsvGJ/adP2PnffPYlLJjonDM=
*/