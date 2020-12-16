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
qw8BigUxe0wcX4eQOWFiPxbB40TOKMViFItj7Y0T7SWRWTDR90zF8skcMLn/IzOZ/TktfCCsjMzF7HRDlyJYrWhv2/hdo2DNImfhnX2+hvntYrWIZclJxvu+a9Wq62BuMl7Lsbsm58NCeJycI96enCNh7dcxMUfM4uQcKZagWBI3sZylchP7h3QlLlOJyyZzM1s02N8BK+ZxYh5KyZzM8uZ+/wasksxi1vRg+ApYvbDhffc+DWslM5n5PXRJHsxZ6W1vXD72MpiHzOJ9OOr6DRYi7ObFezbDooT9sDS5FpYg2rO/bQVLq+R9F8/+V/qe2xzRXq8n1oXAioRt++rHw7AKUQt/NqJWxF2yZOByWLMS5/epVx/a7wWHWV4mnrljJvse7DMudno4s/FGcjK3aDKTmX2sCEsgs5jZ2yxYOpmDmT3WsEwyFzP7/S+wAqWWEmH29gVWIXLa5zKwelGLva7AGpU6m4Xxdwy2snGZII6hnbupFph43jdAWMTv61+GhZNZzP5VfuEAWCyZCRPHGklkDpg89hY582ZM7gnL5nFiG5KrWL5ihUotxaIP/XatLoVViDoXz7nxYlgdzym2nw1Ke03MJgprITNhYv4ce3ybW7EgMl/thZA5mXX//WATLILMzWxj48TFsAQyi1nC3y1tsHRRy9DRe2+B5QjbdbRpJ6yQ5xTXRstFH9hvyZMqWVy8MXOufQwNqyczmdnjAmshczDjOduE2fs/mF+Vd3vF2+4ZC3MLc/+09GpYMBmvxX6vAyyCzFctUWROZva2BxYn2puXsf9yWKrPnLHj05k9Tt8Wsd83CstETljV5w/A8oWdzDv/YlipMHtfBasWRkdaXWCNZCazBSn/HgBrI3MxO/xizWqYa693H+zlGuYh4+3ZyxIshIznZNv58dFKzljF4hVLJHMy++iTpgRYmqjz67/qOsNyyExm3YtP/QkrVNorFjkfuPX9fbBKkXNmeefusDphfJ/azNpLEPujVjKTGY9z7vNtHsWCyXy1F6rERYk4vg+IYXFP0N/uXaynYYlkLmb2MgHLJHPCxLFNLpkDJvdHSlwxWTizo8PnP3PWphhtrM4p9LdrRWELzPyM6oTxOskCyZww3h5ZKJkDxuskC1fioskCmbVVXTvjrE1LzmA5p9L2xp4jWBaZk5mdE5Yn4lAL2bgCZonGpGks57giMiczlnNcmYg7l7P37AoyrA//MlL728eDsDoyF7P3Rj/xIKxVxDX3TZsPM6tpjpjZz+3C/Ml4Tvt9lbAwMlnLP8sni5tGy/K9j1x1KSyFzGS29OXn3oRliriFy11bYQUizv5GAKyUzGKWcfPNM2HVIuf73To3wZpETvv5VJixn+aI2QMznvgAZpI5mPFvP7nIeHurrhk3CRZMxtuzn6eERZC5mX3wxx8XwxIUyxSW06NnCKxQmOvHXRln7e+/K8kwZtP59TqyejIHM/u4HNaoxBkHWBw/PiNzcOPHmGQmmQXj90GQBQj7bpXf67AwMhPGf88hixZxQz47fAKWqMSlK3VmcuPbHrJsxXKVcclXrNDnuCSllLO4JGP6BDsOVqlYtWK1itUr1qhYs2KtPi050Th4zmbQV/LteYA5hPE4U5i97MJcwuxjYZhHsQAyi9n9yweUwMKE/b3j+2ZYDJnJzD9zcRYsUbTX9bfr58BSyFzMsk/+NR+WLXLaxz2wAjInsxduTXTBSkSdQ9f+PA9WJdqbMMPxFKxRxH3/Z+idMKPGuxb7u48wi4z3z14fYG4ynvPcvmOKEUyGWmYa05PSe9yeDIsiM5nZ7++BxQt7uOjL1/7fXnIqay+F9l0B0Tc4YNlkbmaf7d5TcNaeMIo=
*/