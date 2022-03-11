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