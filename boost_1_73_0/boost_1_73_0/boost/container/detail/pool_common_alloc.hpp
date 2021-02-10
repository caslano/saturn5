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
YG3tGecgpIYNNRtQDEeOdm0lec7Mbgg/EMKBoTuK2ysAB9vMWilr3bOwHrK4dL+lkR95cz/wejIdvtO36LO7nCeWOeRyWhB0AOwIb9qhnfTnJ55ExJwbhq+Z+4oiFfadHBRmgqDaO9qVjBZhEk7DeWzNkiQaxqP2rffNvYzmnuWIwuqttYUPD32HVtBDdE7b7S256Xz+AY4neL23fnbo9mWuPJQypixYS8b96vpz99yf+8nKcvP8YLuTiTNpAxZeslwE8NWdLz1rQTWeiaoDS8MLo7qRoRvgVv2mqoz+eXfedoFIKAivgjRsB8AkYXc7iQax54E7j0Mc/vPF/S76RpkzdYBdsmHwYIdhkHhB8uSp0Ac/LvZE538E/gdQSwMECgAAAAgALWdKUlT2A9QXBAAA2AgAAEQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMTU9QVF9DT05URU5UX0xFTkdUSF9QRU5BTFRZX1NJWkUuM1VUBQABtkgkYK1UYW+bSBD9zq8Y+b4kFcFOU10v17Q64tAahQAyuKlPltAalrCn9S7HLk5c5cffLOAmuVaqPxTLBi8z772debPOagSvftllOQYOfnpl3TfDC+/7pLiR/9Bc/zghyx6h/2DiCu8H
*/