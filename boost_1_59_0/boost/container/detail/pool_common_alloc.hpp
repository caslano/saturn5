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
      multiallocation_chain::pointer_pair ptrs = chain.extract_data();
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
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
*/