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

   //!Allocates array of count elements. Can throw std::bad_alloc
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
   //!can throw std::bad_alloc
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