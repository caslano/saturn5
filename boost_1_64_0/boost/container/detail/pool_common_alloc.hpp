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
2SglMHpi9GtNIgB6joA+3Wz3vrNgNy1wA9NsFw755Os2DR47WKTtUmFLSpghdIiQf9HlC+sihaaJ0cH6VW7RuLD+52X6mGSl5cJ9NJ3ThcR+QxjfQje9gs327eMPiepgtBEP+tG3kbzc96gfnmOi21zTLHUfvP179ogKguomH4/GOD6hT1BpUrelYspaiMhMetXYcn66aSsCoeSb68gBYrTVrqEr1TsdLy05PlksP0gYjRKOaAFGcdZ6ptJV4l3+ZN57Yq5iUSbGNJnoCeIYdjTREzkKlaqMu18PYilhgoRhZ4Eckr2y2QlG+2+K2T6hpJKfMxsEvmWWKA7VOXNvhPsQw8u7Co0UIqTb+q+SzsB0iA4Xc4GSTn8qri5l0Bpp1XSm0Jf7+zuFRsUGiBnaCz8njPqWlKhI9OiZLaZUj9DiPsd58X2Ag+swi1enmr0Pm/iu+kwGBGtg6d9wrRhfj2WjfHR9hX75qBanQ64Uav9Uy4dhkQWXn9+m7e+QuxC1URM/rlZvK7PV790FS7zxt0ScJ0fHNvDSoZKKtcQBaQFPXO5ZgQHLK0y0HA==
*/