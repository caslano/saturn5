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