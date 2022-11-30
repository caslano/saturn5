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

#ifndef BOOST_REGEX_V5_MEM_BLOCK_CACHE_HPP
#define BOOST_REGEX_V5_MEM_BLOCK_CACHE_HPP

#include <new>
#ifdef BOOST_HAS_THREADS
#include <mutex>
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

#if BOOST_REGEX_MAX_CACHE_BLOCKS != 0
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
   mem_block_node* next { nullptr };
   unsigned cached_blocks { 0 };
#ifdef BOOST_HAS_THREADS
   std::mutex mut;
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
      std::lock_guard<std::mutex> g(mut);
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
      std::lock_guard<std::mutex> g(mut);
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
      static mem_block_cache block_cache;
      return block_cache;
   }
};
#endif
#endif

#if BOOST_REGEX_MAX_CACHE_BLOCKS == 0

inline void*  get_mem_block()
{
   return ::operator new(BOOST_REGEX_BLOCKSIZE);
}

inline void  put_mem_block(void* p)
{
   ::operator delete(p);
}

#else

inline void*  get_mem_block()
{
   return mem_block_cache::instance().get();
}

inline void  put_mem_block(void* p)
{
   mem_block_cache::instance().put(p);
}

#endif
}
} // namespace boost

#endif


/* mem_block_cache.hpp
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
*/