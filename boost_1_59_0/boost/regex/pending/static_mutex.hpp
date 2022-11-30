/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         static_mutex.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares static_mutex lock type, there are three different
  *                implementations: POSIX pthreads, WIN32 threads, and portable,
  *                these are described in more detail below.
  */

#ifndef BOOST_REGEX_STATIC_MUTEX_HPP
#define BOOST_REGEX_STATIC_MUTEX_HPP

#include <boost/config.hpp>
#include <boost/regex/config.hpp> // dll import/export options.

#ifdef BOOST_HAS_PTHREADS
#include <pthread.h>
#endif

#if defined(BOOST_HAS_PTHREADS) && defined(PTHREAD_MUTEX_INITIALIZER)
//
// pthreads version:
// simple wrap around a pthread_mutex_t initialized with
// PTHREAD_MUTEX_INITIALIZER.
//
namespace boost{

class static_mutex;

#define BOOST_STATIC_MUTEX_INIT { PTHREAD_MUTEX_INITIALIZER, }

class BOOST_REGEX_DECL scoped_static_mutex_lock
{
public:
   scoped_static_mutex_lock(static_mutex& mut, bool lk = true);
   ~scoped_static_mutex_lock();
   inline bool locked()const
   {
      return m_have_lock;
   }
   inline operator void const*()const
   {
      return locked() ? this : 0;
   }
   void lock();
   void unlock();
private:
   static_mutex& m_mutex;
   bool m_have_lock;
};

class static_mutex
{
public:
   typedef scoped_static_mutex_lock scoped_lock;
   pthread_mutex_t m_mutex;
};

} // namespace boost
#elif defined(BOOST_HAS_WINTHREADS)
//
// Win32 version:
// Use a 32-bit int as a lock, along with a test-and-set
// implementation using InterlockedCompareExchange.
//

#include <boost/cstdint.hpp>

namespace boost{

class BOOST_REGEX_DECL scoped_static_mutex_lock;

class static_mutex
{
public:
   typedef scoped_static_mutex_lock scoped_lock;
   boost::int32_t m_mutex;
};

#define BOOST_STATIC_MUTEX_INIT { 0, }

class BOOST_REGEX_DECL scoped_static_mutex_lock
{
public:
   scoped_static_mutex_lock(static_mutex& mut, bool lk = true);
   ~scoped_static_mutex_lock();
   operator void const*()const
   {
      return locked() ? this : 0;
   }
   bool locked()const
   {
      return m_have_lock;
   }
   void lock();
   void unlock();
private:
   static_mutex& m_mutex;
   bool m_have_lock;
   scoped_static_mutex_lock(const scoped_static_mutex_lock&);
   scoped_static_mutex_lock& operator=(const scoped_static_mutex_lock&);
};

} // namespace

#else
//
// Portable version of a static mutex based on Boost.Thread library:
// This has to use a single mutex shared by all instances of static_mutex
// because boost::call_once doesn't alow us to pass instance information
// down to the initialisation proceedure.  In fact the initialisation routine
// may need to be called more than once - but only once per instance.
//
// Since this preprocessor path is almost never taken, we hide these header
// dependencies so that build tools don't find them.
//
#define BOOST_REGEX_H1 <boost/thread/once.hpp>
#define BOOST_REGEX_H2 <boost/thread/recursive_mutex.hpp>
#define BOOST_REGEX_H3 <boost/thread/lock_types.hpp>
#include BOOST_REGEX_H1
#include BOOST_REGEX_H2
#include BOOST_REGEX_H3
#undef BOOST_REGEX_H1
#undef BOOST_REGEX_H2
#undef BOOST_REGEX_H3

namespace boost{

class BOOST_REGEX_DECL scoped_static_mutex_lock;
extern "C" BOOST_REGEX_DECL void boost_regex_free_static_mutex();

class BOOST_REGEX_DECL static_mutex
{
public:
   typedef scoped_static_mutex_lock scoped_lock;
   static void init();
   static boost::recursive_mutex* m_pmutex;
   static boost::once_flag m_once;
};

#define BOOST_STATIC_MUTEX_INIT {  }

class BOOST_REGEX_DECL scoped_static_mutex_lock
{
public:
   scoped_static_mutex_lock(static_mutex& mut, bool lk = true);
   ~scoped_static_mutex_lock();
   operator void const*()const;
   bool locked()const;
   void lock();
   void unlock();
private:
   boost::unique_lock<boost::recursive_mutex>* m_plock;
   bool m_have_lock;
};

inline scoped_static_mutex_lock::operator void const*()const
{
   return locked() ? this : 0;
}

inline bool scoped_static_mutex_lock::locked()const
{
   return m_have_lock;
}

} // namespace

#endif

#endif

/* static_mutex.hpp
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
*/