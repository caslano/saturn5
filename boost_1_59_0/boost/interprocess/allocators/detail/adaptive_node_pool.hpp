//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_ADAPTIVE_NODE_POOL_HPP
#define BOOST_INTERPROCESS_DETAIL_ADAPTIVE_NODE_POOL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/math_functions.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/slist.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/mem_algo/detail/mem_algo_common.hpp>
#include <boost/interprocess/allocators/detail/node_tools.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <cstddef>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/container/detail/adaptive_node_pool_impl.hpp>
#include <boost/assert.hpp>

//!\file
//!Describes the real adaptive pool shared by many Interprocess pool allocators

namespace boost {
namespace interprocess {
namespace ipcdetail {

template< class SegmentManager
        , std::size_t NodeSize
        , std::size_t NodesPerBlock
        , std::size_t MaxFreeBlocks
        , unsigned char OverheadPercent
        >
class private_adaptive_node_pool
   :  public boost::container::dtl::private_adaptive_node_pool_impl_rt
         < typename SegmentManager::segment_manager_base_type
         , ::boost::container::adaptive_pool_flag::size_ordered |
           ::boost::container::adaptive_pool_flag::address_ordered
         >
{
   typedef boost::container::dtl::private_adaptive_node_pool_impl_rt
      < typename SegmentManager::segment_manager_base_type
      , ::boost::container::adaptive_pool_flag::size_ordered |
        ::boost::container::adaptive_pool_flag::address_ordered
      > base_t;
   //Non-copyable
   private_adaptive_node_pool();
   private_adaptive_node_pool(const private_adaptive_node_pool &);
   private_adaptive_node_pool &operator=(const private_adaptive_node_pool &);

   public:
   typedef SegmentManager              segment_manager;
   typedef typename base_t::size_type  size_type;

   static const size_type nodes_per_block = NodesPerBlock;

   //!Constructor from a segment manager. Never throws
   private_adaptive_node_pool(segment_manager *segment_mngr)
      :  base_t(segment_mngr, NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent)
   {}

   //!Returns the segment manager. Never throws
   segment_manager* get_segment_manager() const
   {  return static_cast<segment_manager*>(base_t::get_segment_manager_base()); }
};

//!Pooled shared memory allocator using adaptive pool. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template< class SegmentManager
        , std::size_t NodeSize
        , std::size_t NodesPerBlock
        , std::size_t MaxFreeBlocks
        , unsigned char OverheadPercent
        >
class shared_adaptive_node_pool
   :  public ipcdetail::shared_pool_impl
      < private_adaptive_node_pool
         <SegmentManager, NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent>
      >
{
   typedef ipcdetail::shared_pool_impl
      < private_adaptive_node_pool
         <SegmentManager, NodeSize, NodesPerBlock, MaxFreeBlocks, OverheadPercent>
      > base_t;
   public:
   shared_adaptive_node_pool(SegmentManager *segment_mgnr)
      : base_t(segment_mgnr)
   {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_ADAPTIVE_NODE_POOL_HPP

/* adaptive_node_pool.hpp
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
*/