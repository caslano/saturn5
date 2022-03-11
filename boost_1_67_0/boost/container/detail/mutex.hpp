//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Stephen Cleary 2000 
// (C) Copyright Ion Gaztanaga  2015-2017.
//
// Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_MUTEX_HPP
#define BOOST_CONTAINER_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//#define BOOST_CONTAINER_NO_MT
//#define BOOST_CONTAINER_NO_SPINLOCKS

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// Extremely Light-Weight wrapper classes for OS thread synchronization

#define BOOST_MUTEX_HELPER_NONE         0
#define BOOST_MUTEX_HELPER_WIN32        1
#define BOOST_MUTEX_HELPER_PTHREAD      2
#define BOOST_MUTEX_HELPER_SPINLOCKS    3

#if !defined(BOOST_HAS_THREADS) && !defined(BOOST_NO_MT)
# define BOOST_NO_MT
#endif

#if defined(BOOST_NO_MT) || defined(BOOST_CONTAINER_NO_MT)
  // No multithreading -> make locks into no-ops
  #define BOOST_MUTEX_HELPER BOOST_MUTEX_HELPER_NONE
#else
   //Taken from dlmalloc
   #if !defined(BOOST_CONTAINER_NO_SPINLOCKS) &&                           \
         ((defined(__GNUC__) &&                                            \
         ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)) ||      \
         defined(__i386__) || defined(__x86_64__))) ||                     \
      (defined(_MSC_VER) && _MSC_VER>=1310))
      #define BOOST_MUTEX_HELPER BOOST_MUTEX_HELPER_SPINLOCKS
   #endif

   #if defined(BOOST_WINDOWS)
      #include <windows.h>
      #ifndef BOOST_MUTEX_HELPER
         #define BOOST_MUTEX_HELPER BOOST_MUTEX_HELPER_WIN32
      #endif
   #elif defined(BOOST_HAS_UNISTD_H)
      #include <unistd.h>
      #if !defined(BOOST_MUTEX_HELPER) && (defined(_POSIX_THREADS) || defined(BOOST_HAS_PTHREADS))
         #define BOOST_MUTEX_HELPER BOOST_MUTEX_HELPER_PTHREAD
      #endif
   #endif
#endif

#ifndef BOOST_MUTEX_HELPER
  #error Unable to determine platform mutex type; #define BOOST_NO_MT to assume single-threaded
#endif

#if BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_NONE
   //...
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_SPINLOCKS
   #if defined(_MSC_VER)
      #ifndef _M_AMD64
         /* These are already defined on AMD64 builds */
         #ifdef __cplusplus
            extern "C" {
         #endif /* __cplusplus */
            long __cdecl _InterlockedCompareExchange(long volatile *Dest, long Exchange, long Comp);
            long __cdecl _InterlockedExchange(long volatile *Target, long Value);
         #ifdef __cplusplus
            }
         #endif /* __cplusplus */
      #endif /* _M_AMD64 */
      #pragma intrinsic (_InterlockedCompareExchange)
      #pragma intrinsic (_InterlockedExchange)
      #define interlockedcompareexchange _InterlockedCompareExchange
      #define interlockedexchange        _InterlockedExchange
   #elif defined(WIN32) && defined(__GNUC__)
      #define interlockedcompareexchange(a, b, c) __sync_val_compare_and_swap(a, c, b)
      #define interlockedexchange                 __sync_lock_test_and_set
   #endif /* Win32 */

   /* First, define CAS_LOCK and CLEAR_LOCK on ints */
   /* Note CAS_LOCK defined to return 0 on success */

   #if defined(__GNUC__)&& (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
      #define BOOST_CONTAINER_CAS_LOCK(sl)     __sync_lock_test_and_set(sl, 1)
      #define BOOST_CONTAINER_CLEAR_LOCK(sl)   __sync_lock_release(sl)

   #elif (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
      /* Custom spin locks for older gcc on x86 */
      static inline int boost_container_x86_cas_lock(int *sl) {
         int ret;
         int val = 1;
         int cmp = 0;
         __asm__ __volatile__  ("lock; cmpxchgl %1, %2"
                                 : "=a" (ret)
                                 : "r" (val), "m" (*(sl)), "0"(cmp)
                                 : "memory", "cc");
         return ret;
      }

      static inline void boost_container_x86_clear_lock(int* sl) {
         assert(*sl != 0);
         int prev = 0;
         int ret;
         __asm__ __volatile__ ("lock; xchgl %0, %1"
                                 : "=r" (ret)
                                 : "m" (*(sl)), "0"(prev)
                                 : "memory");
      }

      #define BOOST_CONTAINER_CAS_LOCK(sl)     boost_container_x86_cas_lock(sl)
      #define BOOST_CONTAINER_CLEAR_LOCK(sl)   boost_container_x86_clear_lock(sl)

   #else /* Win32 MSC */
      #define BOOST_CONTAINER_CAS_LOCK(sl)     interlockedexchange((long volatile*)sl, (long)1)
      #define BOOST_CONTAINER_CLEAR_LOCK(sl)   interlockedexchange((long volatile*)sl, (long)0)
   #endif

   /* How to yield for a spin lock */
   #define SPINS_PER_YIELD       63
   #if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
      #define SLEEP_EX_DURATION     50 /* delay for yield/sleep */
      #define SPIN_LOCK_YIELD  SleepEx(SLEEP_EX_DURATION, FALSE)
   #elif defined (__SVR4) && defined (__sun) /* solaris */
      #include <thread.h>
      #define SPIN_LOCK_YIELD   thr_yield();
   #elif !defined(LACKS_SCHED_H)
      #include <sched.h>
      #define SPIN_LOCK_YIELD   sched_yield();
   #else
      #define SPIN_LOCK_YIELD
   #endif /* ... yield ... */

   #define BOOST_CONTAINER_SPINS_PER_YIELD       63
   inline int boost_interprocess_spin_acquire_lock(int *sl) {
      int spins = 0;
      while (*(volatile int *)sl != 0 ||
         BOOST_CONTAINER_CAS_LOCK(sl)) {
         if ((++spins & BOOST_CONTAINER_SPINS_PER_YIELD) == 0) {
            SPIN_LOCK_YIELD;
         }
      }
      return 0;
   }
   #define BOOST_CONTAINER_MLOCK_T               int
   #define BOOST_CONTAINER_TRY_LOCK(sl)          !BOOST_CONTAINER_CAS_LOCK(sl)
   #define BOOST_CONTAINER_RELEASE_LOCK(sl)      BOOST_CONTAINER_CLEAR_LOCK(sl)
   #define BOOST_CONTAINER_ACQUIRE_LOCK(sl)      (BOOST_CONTAINER_CAS_LOCK(sl)? boost_interprocess_spin_acquire_lock(sl) : 0)
   #define BOOST_MOVE_INITIAL_LOCK(sl)      (*sl = 0)
   #define BOOST_CONTAINER_DESTROY_LOCK(sl)      (0)
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_WIN32
   //
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_PTHREAD
   #include <pthread.h>
#endif

namespace boost {
namespace container {
namespace dtl {

#if BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_NONE
   class null_mutex
   {
   private:
      null_mutex(const null_mutex &);
      void operator=(const null_mutex &);

   public:
      null_mutex() { }

      static void lock() { }
      static void unlock() { }
   };

  typedef null_mutex default_mutex;
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_SPINLOCKS

   class spin_mutex
   {
   private:
      BOOST_CONTAINER_MLOCK_T sl;
      spin_mutex(const spin_mutex &);
      void operator=(const spin_mutex &);

   public:
      spin_mutex() { BOOST_MOVE_INITIAL_LOCK(&sl); }

      void lock() { BOOST_CONTAINER_ACQUIRE_LOCK(&sl); }
      void unlock() { BOOST_CONTAINER_RELEASE_LOCK(&sl); }
   };
  typedef spin_mutex default_mutex;
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_WIN32
   class mutex
   {
   private:
      CRITICAL_SECTION mtx;

      mutex(const mutex &);
      void operator=(const mutex &);

   public:
      mutex()
      { InitializeCriticalSection(&mtx); }

      ~mutex()
      { DeleteCriticalSection(&mtx); }

      void lock()
      { EnterCriticalSection(&mtx); }

      void unlock()
      { LeaveCriticalSection(&mtx); }
   };

  typedef mutex default_mutex;
#elif BOOST_MUTEX_HELPER == BOOST_MUTEX_HELPER_PTHREAD
   class mutex
   {
   private:
      pthread_mutex_t mtx;

      mutex(const mutex &);
      void operator=(const mutex &);

   public:
      mutex()
      { pthread_mutex_init(&mtx, 0); }

      ~mutex()
      { pthread_mutex_destroy(&mtx); }

      void lock()
      { pthread_mutex_lock(&mtx); }

      void unlock()
      { pthread_mutex_unlock(&mtx); }
   };

  typedef mutex default_mutex;
#endif

template<class Mutex>
class scoped_lock
{
   public:
   scoped_lock(Mutex &m)
      :  m_(m)
   { m_.lock(); }
   ~scoped_lock()
   { m_.unlock(); }

   private:
   Mutex &m_;
};

} // namespace dtl
} // namespace container
} // namespace boost

#undef BOOST_MUTEX_HELPER_WIN32
#undef BOOST_MUTEX_HELPER_PTHREAD
#undef BOOST_MUTEX_HELPER_NONE
#undef BOOST_MUTEX_HELPER
#undef BOOST_MUTEX_HELPER_SPINLOCKS

#include <boost/container/detail/config_end.hpp>

#endif

/* mutex.hpp
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
*/