//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_HPP
#define BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/intrusive/set.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/pool_common_alloc.hpp>
#include <boost/container/detail/mutex.hpp>
#include <boost/container/detail/adaptive_node_pool_impl.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/type_traits.hpp>

#include <cstddef>
#include <cmath>
#include <cassert>


namespace boost {
namespace container {
namespace dtl {

//!Pooled memory allocator using an smart adaptive pool. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time.
template< std::size_t NodeSize
        , std::size_t NodesPerBlock
        , std::size_t MaxFreeBlocks
        , std::size_t OverheadPercent
        >
class private_adaptive_node_pool
   :  public private_adaptive_node_pool_impl_ct
            < fake_segment_manager
            , MaxFreeBlocks
            , NodeSize
            , NodesPerBlock
            , OverheadPercent
            , unsigned(OverheadPercent == 0)*::boost::container::adaptive_pool_flag::align_only
               | ::boost::container::adaptive_pool_flag::size_ordered
               | ::boost::container::adaptive_pool_flag::address_ordered
            >
{
   typedef private_adaptive_node_pool_impl_ct
            < fake_segment_manager
            , MaxFreeBlocks
            , NodeSize
            , NodesPerBlock
            , OverheadPercent
            , unsigned(OverheadPercent == 0)*::boost::container::adaptive_pool_flag::align_only
               | ::boost::container::adaptive_pool_flag::size_ordered
               | ::boost::container::adaptive_pool_flag::address_ordered
            > base_t;

   //Non-copyable
   private_adaptive_node_pool(const private_adaptive_node_pool &);
   private_adaptive_node_pool &operator=(const private_adaptive_node_pool &);

   public:
   static const std::size_t nodes_per_block = NodesPerBlock;

   //!Constructor. Never throws
   private_adaptive_node_pool()
      : base_t(0)
   {}
};

//!Pooled memory allocator using adaptive pool. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template< std::size_t NodeSize
        , std::size_t NodesPerBlock
        , std::size_t MaxFreeBlocks
        , std::size_t OverheadPercent
        >
class shared_adaptive_node_pool
   : public private_adaptive_node_pool
      <NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent>
{
 private:
   typedef private_adaptive_node_pool
      <NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent> private_node_allocator_t;
 public:
   typedef typename private_node_allocator_t::multiallocation_chain multiallocation_chain;

   //!Constructor. Never throws
   shared_adaptive_node_pool()
   : private_node_allocator_t(){}

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~shared_adaptive_node_pool()
   {}

   //!Allocates array of count elements. Can throw bad_alloc
   void *allocate_node()
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      return private_node_allocator_t::allocate_node();
   }

   //!Deallocates an array pointed by ptr. Never throws
   void deallocate_node(void *ptr)
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      private_node_allocator_t::deallocate_node(ptr);
   }

   //!Allocates a singly linked list of n nodes ending in null pointer.
   //!can throw bad_alloc
   void allocate_nodes(const std::size_t n, multiallocation_chain &chain)
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      return private_node_allocator_t::allocate_nodes(n, chain);
   }

   void deallocate_nodes(multiallocation_chain &chain)
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      private_node_allocator_t::deallocate_nodes(chain);
   }

   //!Deallocates all the free blocks of memory. Never throws
   void deallocate_free_blocks()
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      private_node_allocator_t::deallocate_free_blocks();
   }

   private:
   default_mutex mutex_;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ADAPTIVE_NODE_POOL_HPP

/* adaptive_node_pool.hpp
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
*/