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
4sp7SJrc8M/fR3I995BsrHvt+0hq1it9L8mvX7O68j6SX7+H5J+9d6QB/dAXZaNitO5vZde0yj5ln7JP2afsU/Yp+5R9yj5ln7JP2afsU/b5f/i40dj/3O//SS1ayg0A/4Z3AOyINf7nfl+o/QeP/3JW2oLFS/am1x1cNL1TaqNzZb8v2O8xpAj1+UDuH/wYvS9/H0Q75e8jKOI/eL/Zlom/fs/Z+p7W9bxKva5979me/Gvf
*/