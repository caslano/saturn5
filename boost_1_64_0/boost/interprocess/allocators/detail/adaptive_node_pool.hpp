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
iH9q2q6daW93St3D+DZneiO8WdiPL70h/nORt/AJv4rb4bbCOnC8aIuZ4jDxUmb3HPEmcZG4XPyF+KXYReopZUijpXypSCrBC6mUrmDOs6pCvHeZMgddfaLaTTtOu1W/R1+Orvsdax+/QcNlmP1M0VRN03TNTDOLKDDbzDFz0XqjzXwi7hKzzKw0Y2atOd2sY7y0t2vtbs4YNPfjTgdiwR7ENPnuj7wTvb7eOL/an+I/6D/tv+KPiIyPXB95Ed/y64iQ1lbYSt0vF8vEG5i1iZIo/UJqIh7IlUfJo+V8uUgukcvwqmPEBj9VPmWVJ0lNUd9W22DJpmjXY8Xe1xL1LkQ6p+q2/hwxWNjIZDTfzzx+0XjP+IPRxTzRjJgLaOWnzdfMTsQEJ1uSNdAqw99ejMfzqNWE9n7N6moX2KX2NPziBizROrsJTbPJ3mxvYX5vs3ewgrHb3ozW6+8N9S70rvCKGJlTvZu9h7znvDe9Yf5i/1n/o2A+i22F6aBQGicFtZ4u1xHVzJHriQsa5fnyAtr+JFXC7jygdtX68BZz0baqfjkW8mb9cqOIWKbW2EXNO5tnEs3cbK40I9Y51mprjbWOum60Nlmf2ZIzwrncqXNmO2e7yd54/2ai+0CfthVSgBPXh82f54r3iMKWtvH9tHn4ss+bwXxpK2SCn6jnaJX6p/q9xqfGUDPQKyEr3XrUPt4xnEtZB7nDWeu87nyJN3UTc1FnBaSTX+Nv4kmJ8f9Xz2XiXvEk6S1ZVV5BP35sWtZ4p737vi+EEoXenPdZcdmgbFUf0BqtZ6wPveygjmmJ8bqMl7fIB61aWxAT4/U8TblHEzKb7+uFzzNb/W0Q13u3e6u9gx6ZOYnxOmdJ86VHpKnKp2oWa3WP6COIsWuM2ayD/MzYaGwxZpvbzM/NaXYRcf0nXmdWlvpGInGfIFHIAl+L18u3E13exargx8QtL2inW1fZgXe7xF3urnBXuqvxHNexDjMf/Xxu5HK0znORrcy3vcTeifHYewBa7VrlLlbQjiH20dRa9Vr1TnUpcd6b6k1YlYdYDdiMd/2e/om+2ExwT3fPx4ua5eZ7Nd4yVhums9LgRbIiQl1zOyaxvmdIC+R75VHoqYHqL9V69yU3sNmJQkbQzsoILU/bT8x4iDWGRCPJSDFCRndjj7M/ciByKCIsSozHaLSlmCSmiCGxu3i5nKglaSlaa+/jU1aJupp9TMk8z5xNlHy6nWU/Zs91NjrbnXrvHm+jt8t73/vCq/DHR+J6jK2K7GA8yVcydlehwZ9jTWuaulZ9WX3NOGh0Rz+46IWHzYOWyArLUOcBZ6Rb4lbiMV7v3sEq3yPu43gLTf7HvtCUKKiUVSJ+JIeUxfoyvZpxfib2JsuULAMrVmlPwcI/bS92l7l98VuCGLH5+cNZ5WwSt4vtpFek11gXTJFL5YlykvIjrY1xjPEjoxdW8mLjSuMJI/CXpljP2DpR4RTvVu9W/2f+C/7KyPPEfolCavATU2KjuFu8TXlUe9943g7mQnN+Dzmd2dlTOVe7jOh5sR78Is4+8rvJJ+M3lmJJ5hJVdVUuJJpy1On098l4cYWsjJxCpD3DuMaYRzy/1ljPatzrRg/zBDwIw7zAvJiIuNx8wFyFr/i8+bb5vvl7s43lW4Ow3nmsq11JTP4Tayuxw3usTaTYx9on2Wfa4+0q/It6+177AeL0jfZop5B15CudRtb1lrHe9hGryG3xjjPwOBx3iDsbf+M29z7G7QZGzg431TsJe2HhhY30CrFWK73HvA3Yjj3eJ8ymDv5A/1x/hF/kT/NnseZ1RzAvQ+3iseqxyvFEQqIyWLlAuZSIaKGyRFmpPElUvEM=
*/