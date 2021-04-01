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
b636JK0gcTF6dHSEbcCGp3YpfdGIiQRGfaWQQ5+0SMPwmAZmP4SNq9j4eRhDRGChdxsl2GYRx/RKHna2NZOFBqypXx16n6vAcxMMxxuWm6JWzj2cTURy9UJMSLkpUCiG27TcerWCfCLGM1Xbqj6ORFl0tq499Nfs8mNWF+FCaw1F2mFIbbJq0KCVCfvGUQ6D637N2hKEBQJsqPnE9oJ0LNvTGXaAWWjR8aqKOwD0KCKT1MpQ09XHxWP9ciorr3zK3NcmKuSdnNJIaIgVh7awsdFGOAh4j46+0h8iqgIhxPCxpUnA2UUb/eAEXznGlHq1mKQPrY5iTXeSPC6rNkohU70P3mvTNd365ptLlStgwv/U9IJBdc5SkjDiafVXtxqJT9H4kXD2UmQdG+/BxPo8r++XxYWjxED58uTrFw+sgz0PG4KIa26wqVahTcA20UUPjy5x4WcXbq0SsLLdLxync2luw9jTKnGRXjzfWB0LAk7p9kQnHgSujINU5GUquVX+wrx1/AV1cEcenrgBPW0usiID3/MLevQBRoTQUE6CXTuGPDOvYeG07LeZCg==
*/