//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_NODE_POOL_HPP
#define BOOST_CONTAINER_DETAIL_NODE_POOL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/detail/mutex.hpp>
#include <boost/container/detail/pool_common_alloc.hpp>
#include <boost/container/detail/node_pool_impl.hpp>
#include <boost/container/detail/mutex.hpp>
#include <boost/move/utility_core.hpp>
#include <cstddef>
#include <cassert>

namespace boost {
namespace container {
namespace dtl {

//!Pooled memory allocator using single segregated storage. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template< std::size_t NodeSize, std::size_t NodesPerBlock >
class private_node_pool
   //Inherit from the implementation to avoid template bloat
   :  public boost::container::dtl::
         private_node_pool_impl<fake_segment_manager>
{
   typedef boost::container::dtl::
      private_node_pool_impl<fake_segment_manager>   base_t;
   //Non-copyable
   private_node_pool(const private_node_pool &);
   private_node_pool &operator=(const private_node_pool &);

   public:
   typedef typename base_t::multiallocation_chain multiallocation_chain;
   static const std::size_t nodes_per_block = NodesPerBlock;

   //!Constructor from a segment manager. Never throws
   private_node_pool()
      :  base_t(0, NodeSize, NodesPerBlock)
   {}

};

template< std::size_t NodeSize
        , std::size_t NodesPerBlock
        >
class shared_node_pool
   : public private_node_pool<NodeSize, NodesPerBlock>
{
   private:
   typedef private_node_pool<NodeSize, NodesPerBlock> private_node_allocator_t;

   public:
   typedef typename private_node_allocator_t::free_nodes_t  free_nodes_t;
   typedef typename private_node_allocator_t::multiallocation_chain multiallocation_chain;

   //!Constructor from a segment manager. Never throws
   shared_node_pool()
   : private_node_allocator_t(){}

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~shared_node_pool()
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

   //!Deallocates all blocks. Never throws
   void purge_blocks()
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      private_node_allocator_t::purge_blocks();
   }

   std::size_t num_free_nodes()
   {
      //-----------------------
      scoped_lock<default_mutex> guard(mutex_);
      //-----------------------
      return private_node_allocator_t::num_free_nodes();
   }

   private:
   default_mutex mutex_;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_NODE_POOL_HPP

/* node_pool.hpp
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
*/