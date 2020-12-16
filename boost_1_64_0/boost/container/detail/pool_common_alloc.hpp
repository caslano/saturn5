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
58ACyRzM7D7AghULVSxcsUgyk5n9uxMsjsxiZh+jwFKVuCxh15xf+issX+R0ftbnCKxUxNnvDoNViT6wZ5aNGqV/dWRuZtPXTdoHa1Pi/Dy+zamY5fE9t/6KBZNZfDzfn3gIFqnExSqWqNSZoliaYhmiPfbMuZFD5mIWcWylBSsW/fO/uLg7rJKMz3vh9E96wuqUWhpEzruG714HaxN2stvv+2DWdd5WOSsiBBZIxmsZtaS1FBYm7PhT64/AokXO62funQdLFDZm1+V7YRkiZ9e3Vz+H7W4uGfpey79dSZavWCFrj6z9nARWLuIap/UeCKsUZm8jYdVKe7U+7cmO9ayWI/Tv7w//uBHWKqwiIzQXZl5P48Js15rm8TB/YRnbL50PCyHjOe8b07QOFiWsfGTL5bAEkfPwgvyrYWnC7G/fw7JFTvtbYbBCYfa3wmDlIqd9rAGrYXFf0L9/mPtKD1iTsPlFlZEwvx6Uk9mpzU+mwFxkmKOj9G8+Rx5mdcICyJzMdv7n/BdhIWQBzJJ7fJAGiyczmfnXTRxx1jI6ppJhm/wl/Tv3zfk3wnLJLGarak/eBysW5g79JQ9WSWYyqz3++E+wOmGrHkxrhTULS7uxdSfMz9/bVmwteQfmInMx+/i2zctgwWS8zhN5O66GRQoLGNrUCIsX7T0wuXERLFXY+K0dtsOyyDzMeuy9IwFWTMbH+uuY86+EVYs+LIobGA5rEu3Z7+mGGTecW16OGRntywvMoZhJZjE7tmpyISyAzM3MfmcALELEdR0TlAeLEzarc60BSyUzmfWa/K8IWJao0z6egOUofchj9pWwAjInM3tfDCsRZu83YRVKziph9rUuWI0SV6dYg2JNSh/alDi/nr7NSWYxs/dHMH8yk5l9DgsLYVZP/7avR8IiyRzM7Gv3sGgyJ0yMdbxiKSzn1/Rve/8HS1Msg8wJE2OWQ2bCRP8KuYn+lZFZzA489MUIWI2wrL7dt8CaRM4tqw/1gBk3escVxQ8eB3OR8T7wcQkg4znvmvXJelgomYvZusJlf8JihEUO+eUOWIowd2yHlbBs0d5zK198A1Yga1m35QSslNlxMZ5VZJi/b8T81ShWp1gDa6+B/m2fA8FaySxm9rkTzAzwttD9Wx+DBQhb8fiGZFgYmQMm1rEIxaIUiyFzMrOv6cASRC2tT9eYsHRh0b07RcNyeU6xPhQqtRQrVkrmZhbRe/Y1sFoeJ7bl9UrORsWaFWtVzLjJdy0ObnLfSMbHzJg9ayDMQ+ZiFjh94p+wUDI+D+Mej+sFixY57Xs8YfGslhOilkRuog8p3MR2N03JmaFYFpkJE9vIfDInM8/kb1bDislczOz7dGBVSns1itUp1qBYk2ItirVxE9sXv17n5vakvR75XXIa5hbWELNqFSyYzGRmnwfAIsjQ3rdyO8FyNtK/t6W2rYUlCPvPzntXwtLJTGb2Ny9hOWQeZhsXJ/SDlQpb8/ur42B1rM7v5DyQOZmZPXuOhrWQuZi19fgyC2beTH1gtmn9bWNgAWQms18jexmwUGH8XCaKDHV+L7etZE6Y2A4mKHFJPE7si9N5nDgezFRyZguzn/2A5Spx+cLs79/CCsksZiO3fH4nrJzMZLZriV8HWI3SXp1iDWRuZvZ3O2F+gawWcYzpJjNhYvsSxOwHccwQTuaAiW1dJJkTJuYoVrFEMvShyV4mdh8rhWWx9sjYcxO0HpGZzOJeu/AVWKHIeeri9wtglWQWswPjpnaB1Yu4kHt2FsGM3t7tLbxuzYMwS9gfX/9+ABZAxtsrjSy1YGFk/sw2DnoyC5Yg7L1Hj9wKyxY5LffUKFihqKXXbc8tgZWROWBey9I=
*/