 /*
 * Copyright (c) 2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         mem_block_cache.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: memory block cache used by the non-recursive matcher.
  */

#ifndef BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP
#define BOOST_REGEX_V4_MEM_BLOCK_CACHE_HPP

#include <new>
#ifdef BOOST_HAS_THREADS
#include <boost/regex/pending/static_mutex.hpp>
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifndef BOOST_NO_CXX11_HDR_ATOMIC
  #include <atomic>
  #if ATOMIC_POINTER_LOCK_FREE == 2
    #define BOOST_REGEX_MEM_BLOCK_CACHE_LOCK_FREE
    #define BOOST_REGEX_ATOMIC_POINTER std::atomic
  #endif
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_REGEX_MEM_BLOCK_CACHE_LOCK_FREE /* lock free implementation */
struct mem_block_cache
{
  std::atomic<void*> cache[BOOST_REGEX_MAX_CACHE_BLOCKS];

   ~mem_block_cache()
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       if (cache[i].load()) ::operator delete(cache[i].load());
     }
   }
   void* get()
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       void* p = cache[i].load();
       if (p != NULL) {
         if (cache[i].compare_exchange_strong(p, NULL)) return p;
       }
     }
     return ::operator new(BOOST_REGEX_BLOCKSIZE);
   }
   void put(void* ptr)
   {
     for (size_t i = 0;i < BOOST_REGEX_MAX_CACHE_BLOCKS; ++i) {
       void* p = cache[i].load();
       if (p == NULL) {
         if (cache[i].compare_exchange_strong(p, ptr)) return;
       }
     }
     ::operator delete(ptr);
   }

   static mem_block_cache& instance()
   {
      static mem_block_cache block_cache = { { {nullptr} } };
      return block_cache;
   }
};


#else /* lock-based implementation */


struct mem_block_node
{
   mem_block_node* next;
};

struct mem_block_cache
{
   // this member has to be statically initialsed:
   mem_block_node* next;
   unsigned cached_blocks;
#ifdef BOOST_HAS_THREADS
   boost::static_mutex mut;
#endif

   ~mem_block_cache()
   {
      while(next)
      {
         mem_block_node* old = next;
         next = next->next;
         ::operator delete(old);
      }
   }
   void* get()
   {
#ifdef BOOST_HAS_THREADS
      boost::static_mutex::scoped_lock g(mut);
#endif
     if(next)
      {
         mem_block_node* result = next;
         next = next->next;
         --cached_blocks;
         return result;
      }
      return ::operator new(BOOST_REGEX_BLOCKSIZE);
   }
   void put(void* p)
   {
#ifdef BOOST_HAS_THREADS
      boost::static_mutex::scoped_lock g(mut);
#endif
      if(cached_blocks >= BOOST_REGEX_MAX_CACHE_BLOCKS)
      {
         ::operator delete(p);
      }
      else
      {
         mem_block_node* old = static_cast<mem_block_node*>(p);
         old->next = next;
         next = old;
         ++cached_blocks;
      }
   }
   static mem_block_cache& instance()
   {
#ifdef BOOST_HAS_THREADS
      static mem_block_cache block_cache = { 0, 0, BOOST_STATIC_MUTEX_INIT, };
#else
      static mem_block_cache block_cache = { 0, 0, };
#endif
      return block_cache;
   }
};
#endif

#if BOOST_REGEX_MAX_CACHE_BLOCKS == 0

inline void* BOOST_REGEX_CALL get_mem_block()
{
   return ::operator new(BOOST_REGEX_BLOCKSIZE);
}

inline void BOOST_REGEX_CALL put_mem_block(void* p)
{
   ::operator delete(p);
}

#else

inline void* BOOST_REGEX_CALL get_mem_block()
{
   return mem_block_cache::instance().get();
}

inline void BOOST_REGEX_CALL put_mem_block(void* p)
{
   mem_block_cache::instance().put(p);
}

#endif
}
} // namespace boost

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif


/* mem_block_cache.hpp
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
*/