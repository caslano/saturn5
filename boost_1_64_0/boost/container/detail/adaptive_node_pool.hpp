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
WD6ZFbMKX/q+hIlg4+tEwMdygTBVsBQ34FAiTCOZXf3KATAtGZ9R0+QNTWFtyPj52XubZyWYP5k1z+VhuDssiMyVWdkPV5U148lUzPItctvBksgsmJ1a2cZT6TWZG7N5BVtPwjLJ+NyP9nV+CDOQOTOb/NfQvrBCqQZNs0HKfmYhxuY1M+w9TE3G59DjVsBimDdZeWYTupsugPmRqZlteDsgGBYmxTm+eNIAlkDmxGxwmah9Sl+kPPdETt0BSyczZ1bFr1eB0jMyd2b7rm6sDntBxq+Rk7p5tITlk/H5LapW6Q3MbLDxefZ32/bKbNVkDsx6hzYqDdOS8flFdk68C9OR2TIbNe5JyWuOtGZFy8sDYXoy3pdajxNbwOLJPJklHPpmD1tPxl9Tu7k36QtLI+PP2y0u9e7Bssns+Nw/3XeF5UrWPr99DEwMMc5z4fE6VWEqsjIsl8+/TVRyUZPxXlfuvHkkzJuM92yl+kAqTEfGe7apqXtlWKC0Zqm7kfthYWRuzK7PeaiHJZDx+obd/dgWlkzGe/ala8ZCWAYZP8/cGq2dCcsk48+H0RXf91f6KfUsy7f5GVghmSuzS3ePn4WpQ42vL//bs6ozzJvMjFm4p8demC+ZM7NPoROSYIFkTjxuT7oeNpqMz2+GZ9/1sDiyssyuNBoXCEsg473u+8Cg5JlCZs5s4x+VlfrSyTTMmnTvOACWQ8b78ibjoZKLGGrcF/uTvmtgKjI1X3NdbieYlkzFTPP5l8kwPzJPZoVbVn2G6cksmf2q9aoOiycrzXsWrM2EJZDxc8JQ2zBa6QsZr2/Yu1s9YZlkNszW2F1RcjGQ2TN7tz+lDyyfjM9oc/Vuy2CFZHzu2/rMj4Sphxnn6XGy2TSYLxnPM3bt/f9ggWRmzLz7q5XZhpHxufdzadMIFivtR4mcgiWR1WS2/POAWkWmj8wmw/vUtWJWqWspem2RjY0xCzNR3t+uE40a5DSd5V1kg0N0zP4SY6I7r+zSVcmFrGKxraf9Bgb4v4Mlk3kx+/xwoTLbbDINs+fOtUspvZZs/i/TsmCa4cZWmHduB8yPrAKz5gWFx2B6KS7rYJoJLEmKK7elQ1tYhmSDvz9NgOWS8dofDnD4FaYaYSKqMqvffsR6mI7Mg9nR73sPwsLI3JhtCmkwE5ZAxmvYVvrYR1gamTuzSh3dAmAGMjtmjz/svArLJ7NmZuvd0wMmRtLrCrPjqq5eMDWZK7NOZ072hfmS8f0Obm/RD+ZPZs7shdrwDhZE5sRsbMrC+bB4Ml7ffv2RObAUMkdmr0JaPIBlkDkzW/T7uaOwHDLe638r10mDiXC6njEb5lV2JcybjNe3U73vHkxHZsmsyvOUdKV2Mt7P2hvUp2FhUtzVEbVaw2Kl/dw77xwJSyTjfXHM6K+CpZO5MPs17XkVmEGyTJ9vL2GF0pq7ejzsD9OMMj6v943vcFipj8yR2ZZ6b6Yp9ZGZMas2susypT4yPofE1j5/wpLI7JnpJt8wgaWROTOrUKf1cFg2WUVm6Ru97JX6yDTM7A6fbarUF2H83BRHl46B+ZE5MevRrv0apT4yPj9D0KZHSn1k1sx2G2I0sAQyG2ZfquRWVWon4zPadMAhXZktGZ/D6WCTLFguGe/Z00o3PsJEpPFsbR+a74Z5k/Haz7qfU/rpT1aR77d5iEapj8yBWS+XD8NgiWQ8l4xpcSX3NmRVmIkNY17DDGRuzBbU23dFmZ+034P/dSh5X6w3EZWYTX937jPMl8yVme+8EfGwQDIVs7a9J5SG6cmcmLX+x2GKUh8ZzyVjmX6AUh+ZGbO3Ve5lKfMj431pn5hfA5Ytmc/eUWeV2ZKZM3OyXhg=
*/