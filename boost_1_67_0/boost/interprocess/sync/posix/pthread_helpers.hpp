//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP
#define BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/exceptions.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail{

   #if defined BOOST_INTERPROCESS_POSIX_PROCESS_SHARED

   //!Makes pthread_mutexattr_t cleanup easy when using exceptions
   struct mutexattr_wrapper
   {
      //!Constructor
      mutexattr_wrapper(bool recursive = false)
      {
         if(pthread_mutexattr_init(&m_attr)!=0 ||
            pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0 ||
             (recursive &&
              pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE)!= 0 ))
            throw interprocess_exception("pthread_mutexattr_xxxx failed");
      }

      //!Destructor
     ~mutexattr_wrapper()  {  pthread_mutexattr_destroy(&m_attr);  }

      //!This allows using mutexattr_wrapper as pthread_mutexattr_t
      operator pthread_mutexattr_t&()  {  return m_attr;  }

      pthread_mutexattr_t m_attr;
   };

   //!Makes pthread_condattr_t cleanup easy when using exceptions
   struct condattr_wrapper
   {
      //!Constructor
      condattr_wrapper()
      {
         if(pthread_condattr_init(&m_attr)!=0 ||
            pthread_condattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0)
            throw interprocess_exception("pthread_condattr_xxxx failed");
      }

      //!Destructor
     ~condattr_wrapper() { pthread_condattr_destroy(&m_attr); }

      //!This allows using condattr_wrapper as pthread_condattr_t
      operator pthread_condattr_t&(){  return m_attr;  }

      pthread_condattr_t m_attr;
   };

   //!Makes initialized pthread_mutex_t cleanup easy when using exceptions
   class mutex_initializer
   {
    public:
      //!Constructor. Takes interprocess_mutex attributes to initialize the interprocess_mutex
      mutex_initializer(pthread_mutex_t &mut, pthread_mutexattr_t &mut_attr)
      : mp_mut(&mut)
      {
         if(pthread_mutex_init(mp_mut, &mut_attr) != 0)
            throw interprocess_exception("pthread_mutex_init failed");
      }

     ~mutex_initializer() {  if(mp_mut) pthread_mutex_destroy(mp_mut);  }

      void release() {mp_mut = 0; }

    private:
      pthread_mutex_t *mp_mut;
   };

   //!Makes initialized pthread_cond_t cleanup easy when using exceptions
   class condition_initializer
   {
    public:
      condition_initializer(pthread_cond_t &cond, pthread_condattr_t &cond_attr)
      : mp_cond(&cond)
      {
         if(pthread_cond_init(mp_cond, &cond_attr)!= 0)
            throw interprocess_exception("pthread_cond_init failed");
      }

     ~condition_initializer()   {  if(mp_cond) pthread_cond_destroy(mp_cond);  }

      void release()       { mp_cond = 0; }

    private:
      pthread_cond_t *mp_cond;
   };

   #endif   //   #if defined BOOST_INTERPROCESS_POSIX_PROCESS_SHARED

   #if defined(BOOST_INTERPROCESS_POSIX_BARRIERS) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)

   //!Makes pthread_barrierattr_t cleanup easy when using exceptions
   struct barrierattr_wrapper
   {
      //!Constructor
      barrierattr_wrapper()
      {
         if(pthread_barrierattr_init(&m_attr)!=0 ||
            pthread_barrierattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED)!= 0)
            throw interprocess_exception("pthread_barrierattr_xxx failed");
      }

      //!Destructor
     ~barrierattr_wrapper()  {  pthread_barrierattr_destroy(&m_attr);  }

      //!This allows using mutexattr_wrapper as pthread_barrierattr_t
      operator pthread_barrierattr_t&()  {  return m_attr;  }

      pthread_barrierattr_t m_attr;
   };

   //!Makes initialized pthread_barrier_t cleanup easy when using exceptions
   class barrier_initializer
   {
    public:
      //!Constructor. Takes barrier attributes to initialize the barrier
      barrier_initializer(pthread_barrier_t &mut,
                          pthread_barrierattr_t &mut_attr,
                          int count)
      : mp_barrier(&mut)
      {
         if(pthread_barrier_init(mp_barrier, &mut_attr, count) != 0)
            throw interprocess_exception("pthread_barrier_init failed");
      }

     ~barrier_initializer() {  if(mp_barrier) pthread_barrier_destroy(mp_barrier);  }

      void release() {mp_barrier = 0; }

    private:
      pthread_barrier_t *mp_barrier;
   };

   #endif   //#if defined(BOOST_INTERPROCESS_POSIX_BARRIERS) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)

}//namespace ipcdetail

}//namespace interprocess

}//namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif //ifdef BOOST_INTERPROCESS_PTHREAD_HELPERS_HPP

/* pthread_helpers.hpp
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
*/