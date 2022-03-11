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