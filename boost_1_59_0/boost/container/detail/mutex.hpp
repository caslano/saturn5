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
      #include <boost/winapi/critical_section.hpp>
      #include <boost/winapi/thread.hpp>
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
      #include <boost/detail/interlocked.hpp>
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
      #define SPIN_LOCK_YIELD  boost::winapi::SleepEx(SLEEP_EX_DURATION, 0)
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