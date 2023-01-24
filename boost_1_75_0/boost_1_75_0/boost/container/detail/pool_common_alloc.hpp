//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_POOL_COMMON_ALLOC_HPP
#define BOOST_CONTAINER_DETAIL_POOL_COMMON_ALLOC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/throw_exception.hpp>

#include <boost/intrusive/slist.hpp>
#include <boost/container/detail/pool_common.hpp>
#include <boost/container/detail/dlmalloc.hpp>
#include <cstddef>

namespace boost{
namespace container{
namespace dtl{

struct node_slist_helper
   : public boost::container::dtl::node_slist<void*>
{};

struct fake_segment_manager
{
   typedef void * void_pointer;
   static const std::size_t PayloadPerAllocation = BOOST_CONTAINER_ALLOCATION_PAYLOAD;

   typedef boost::container::dtl::
      basic_multiallocation_chain<void*>              multiallocation_chain;
   static void deallocate(void_pointer p)
   { dlmalloc_free(p); }

   static void deallocate_many(multiallocation_chain &chain)
   {
      std::size_t size = chain.size();
      std::pair<void*, void*> ptrs = chain.extract_data();
      dlmalloc_memchain dlchain;
      BOOST_CONTAINER_MEMCHAIN_INIT_FROM(&dlchain, ptrs.first, ptrs.second, size);
      dlmalloc_multidealloc(&dlchain);
   }

   typedef std::ptrdiff_t  difference_type;
   typedef std::size_t     size_type;

   static void *allocate_aligned(std::size_t nbytes, std::size_t alignment)
   {
      void *ret = dlmalloc_memalign(nbytes, alignment);
      if(!ret)
         boost::container::throw_bad_alloc();
      return ret;
   }

   static void *allocate(std::size_t nbytes)
   {
      void *ret = dlmalloc_malloc(nbytes);
      if(!ret)
         boost::container::throw_bad_alloc();
      return ret;
   }
};

}  //namespace boost{
}  //namespace container{
}  //namespace dtl{

namespace boost {
namespace container {
namespace dtl {

template<class T>
struct is_stateless_segment_manager;

template<>
struct is_stateless_segment_manager
   <boost::container::dtl::fake_segment_manager>
{
   static const bool value = true;
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_POOL_COMMON_ALLOC_HPP

/* pool_common_alloc.hpp
hiHaxuIbD0DM3t4RmXrEc/VVxXhN+UPcKai0kSP3KdsXxkMZBoJWCwZ9uLht/na2oBGR07Esg1RBpgrkz5T5jdOQJAvJFMQJxOlFkyeBowQOVIpKM+R0QsAxwf4xASMa4jatYETzm8/TaUxpRTHtlqDbiRj0urTaTVrNFo8/8T6aDbcCUiIDEyiFAKW0H9pcHq0au8LcEFSeLVM56upwKuPlhx5yUoTEuD4jKWULa7h86623Pp5H8Umptdaz4XD4+he/+MVvX7hw4Zc+8YlPvLnsU4UUAT327ereppJe4t5eksCsVsN/phFYv7ZFzOLlyxVr4RibKWMGxtaTX+tavK6+gls1l8801yehTUMl44BB/hf2vsVLt59bSPCceL+udDEaDo0B0EoAgVLoLNsBW38AACAASURBVENKSZYl7O4dk6lWuYFyhM2dxX3txHm//fNrMJAG2bstGPRgZwAXt6DZNM+0NgsfM21WVyapQf5MGcKQZJBm5rkjDmnmiANkWUiiQmZJkzTbNs9TGKUwVBk6S2E8JWJEcHRMwJimuE1DjGiGh3S+9W9phDOaEfQ6TQb9Dq1WRLvdpN/rcfmhh4uNVawNpDAESqbT6VI3p4/sDqGrkoB75odU++WX2Sa01jz88MN5vVJKkWVZ64tf/OIzN27ceKbRaHz8G9/4xl/8xCc+8R0WQCEBLOGuCPhbP/I/LfvW9UXXtNze
*/