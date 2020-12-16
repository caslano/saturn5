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
JUtBB9YRhc+x69GDb9l93Wvdx9xs/3G/U8SPTI78LqhXUzshCxwjDpSuJhbsrijKVdizU9hNm8eaeQpWa4JebFzkTHDeZF1yBF7gbd55eNS9IhdG7oh8EvdD2glpQbuxUtxLPkN5U7lRvc/4pdPbPeCOi8e87YRMcIZ4p7RV6ih3xIKOIdZbj83M0F7XRrKOdJpxI1pqPnWeb4fxBjuzd5rif+KfEo9fm++/n5G0jHW0AqVCuVt9Va3X+uhD9dv1HKLSieyjfmzdzKpzI7b/Jvegd6H/hj+J+f01JbSP+39PSh9KI+T98kvqqdoFrCLcS3wvs7JxgTHX2I23FqwY5FtPEEF8Zfd3MhmLG53nnE6u6k5xZ7DCm0ifZqDdR6FF1gV6I8RvXcX1xpmiLI5hl/kt1mguC9Zo2PN4hz2b9qqoZqtj8ATuUx9Tx7Jydr/+Crb1RGOo8b45gOd9Zrd3Xg3eMa290AgSxTAxagPR6WdSW/kYdMhQ+efyS9j885RLlI30cxZrUTXM4CSthzZdu5Uyn9AcfSg2YIf+gR5lffLHxHa9zExa5Kdoa9W+0C60y+yfsq/nsJuxzzndFVmTL2c0vOy+5u4hdrbQsWf7F7OTcwv7Aav9X/qv+gNYC24fjz8niGvYOd8vdpJ6S7I0SBqOzlvDns4r8lvyJ/h8vjJMKWEevsBcaav+SE1XG4L3xeNIxNsYzj7gMu3n2gasVxu9O7tSn7LDqxmD8CseNH5vtDcHEzWXEytPNTdbbewz7LPtYdS43P6ImdoOa206Q51hziXYkKhTjZc331nK6udBYqkn3Rfd7aytaexqxLwnvWe8bv7pvsRKTzG7qjNa9kKX+yuwCItZCYv/PrQwB3Snv5aIbdDnl0kxqa+cK5cSe+rKYXZbVdb7Hmbf9EX1S1p5F/7ux9qP9LNY72zAN9qq9zUcYwze7Br2XgZgRafio2wguivGF3kKLbPfGmgXESs/x17ZQGc0nml7ouE13qvej/0yfIJl1CP4fbXVoFG8X9woPiQ9xapeB/kkWWAd5hj2xXqws3KyvpDV4K90lzigkT3KTeY9aJpe9qmsfwy0s+0xWN1r7Fvs2+21xOOvE4P/3u7NvnAWrZXPTv0ip9692V3oLnV/4T7NvnkbL8nr4fWmtyPeJV4eLdbINwLWeb/ythGj38ge3m728D7Bbh5Ey3eIdI50j6RGekfSIn0Z99PY822eR53FxWKK0ks5Q7HQPI+om9RkbaQ2UXucdWGd1ezHiO0Sjd7GdONR42UjEw9jnPVr5212gwS3CyPvMneWdyt9td27CQsc2I32cdvUSTxeHCsn4dNeq9ynnKmerGfow/VfGBuxF6/juXzMusu75haigW3WDmuntRvNu9d61TkVb6yMnciYX3t0R/gvd8Pjf0k/GkyTa7Gvb6tL9F8aZ1mbrW+Wto/eO2AdOrrX+DfXnbL4fsuH/mfxtWN+2w6MxHu7mDE0WN2h7lR34/vvVfcRpR9QD6mCdjTe/K7V7hwtl5W3N61H3GBfJvM7VosrIpNY6bsNf2YN3syzxN+fx+1Me2E3PmY7fJmTRU10xYFiqVgpzmI3YhEaKvBn3hU/YtX/GOkEKSzpkicFazFT2Ou5TVrB2sFaaaf0nvSFlMS3S05nH9OQL2edaRJeTKO8VH5IXi2/zm7K53IbpatyMmNAUkbSY5VYjZuURXyb40+MnXmcTvUex491VmbGzoQZu8Zy9v2cZ+xkaQbZZV9HGkIjypLiRq61SGS7lCVryj6EMGTLFsmIEi2Erijd93NG97rr6/rn3MrMc57f8v1+tt/vvq98Bg+5pvyqxKjlyRylhBNH4JeRcJG31EU=
*/