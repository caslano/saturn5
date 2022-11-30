//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_NODE_POOL_HPP
#define BOOST_INTERPROCESS_DETAIL_NODE_POOL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/slist.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/container/detail/node_pool_impl.hpp>
#include <cstddef>


//!\file
//!Describes the real adaptive pool shared by many Interprocess adaptive pool allocators

namespace boost {
namespace interprocess {
namespace ipcdetail {



//!Pooled shared memory allocator using single segregated storage. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template< class SegmentManager, std::size_t NodeSize, std::size_t NodesPerBlock >
class private_node_pool
   //Inherit from the implementation to avoid template bloat
   :  public boost::container::dtl::
         private_node_pool_impl<typename SegmentManager::segment_manager_base_type>
{
   typedef boost::container::dtl::private_node_pool_impl
      <typename SegmentManager::segment_manager_base_type> base_t;
   //Non-copyable
   private_node_pool();
   private_node_pool(const private_node_pool &);
   private_node_pool &operator=(const private_node_pool &);

   public:
   typedef SegmentManager              segment_manager;
   typedef typename base_t::size_type  size_type;

   static const size_type nodes_per_block = NodesPerBlock;
   //Deprecated, use nodes_per_block
   static const size_type nodes_per_chunk = NodesPerBlock;

   //!Constructor from a segment manager. Never throws
   private_node_pool(segment_manager *segment_mngr)
      :  base_t(segment_mngr, NodeSize, NodesPerBlock)
   {}

   //!Returns the segment manager. Never throws
   segment_manager* get_segment_manager() const
   {  return static_cast<segment_manager*>(base_t::get_segment_manager_base()); }
};


//!Pooled shared memory allocator using single segregated storage. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
//!Pooled shared memory allocator using adaptive pool. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template< class SegmentManager
        , std::size_t NodeSize
        , std::size_t NodesPerBlock
        >
class shared_node_pool
   :  public ipcdetail::shared_pool_impl
      < private_node_pool
         <SegmentManager, NodeSize, NodesPerBlock>
      >
{
   typedef ipcdetail::shared_pool_impl
      < private_node_pool
         <SegmentManager, NodeSize, NodesPerBlock>
      > base_t;
   public:
   shared_node_pool(SegmentManager *segment_mgnr)
      : base_t(segment_mgnr)
   {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_NODE_POOL_HPP

/* node_pool.hpp
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
*/