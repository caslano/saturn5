//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/permissions.hpp>

#include <boost/interprocess/sync/posix/named_semaphore.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class named_condition;

class posix_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   posix_named_mutex();
   posix_named_mutex(const posix_named_mutex &);
   posix_named_mutex &operator=(const posix_named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   posix_named_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_only_t, const char *name);

   ~posix_named_mutex();

   void unlock();
   void lock();
   bool try_lock();

   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);

   template<class TimePoint>
   bool try_lock_until(const TimePoint &abs_time)
   {  return this->timed_lock(abs_time);  }

   template<class Duration>
   bool try_lock_for(const Duration &dur)
   {  return this->timed_lock(duration_to_ustime(dur)); }

   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();

   posix_named_semaphore m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline posix_named_mutex::posix_named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_sem(create_only, name, 1, perm)
{}

inline posix_named_mutex::posix_named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_sem(open_or_create, name, 1, perm)
{}

inline posix_named_mutex::posix_named_mutex(open_only_t, const char *name)
   :  m_sem(open_only, name)
{}

inline void posix_named_mutex::dont_close_on_destruction()
{  interprocess_tester::dont_close_on_destruction(m_sem);  }

inline posix_named_mutex::~posix_named_mutex()
{}

inline void posix_named_mutex::lock()
{  m_sem.wait();  }

inline void posix_named_mutex::unlock()
{  m_sem.post();  }

inline bool posix_named_mutex::try_lock()
{  return m_sem.try_wait();  }

template<class TimePoint>
inline bool posix_named_mutex::timed_lock(const TimePoint &abs_time)
{  return m_sem.timed_wait(abs_time);  }

inline bool posix_named_mutex::remove(const char *name)
{  return posix_named_semaphore::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_POSIX_NAMED_MUTEX_HPP

/* named_mutex.hpp
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
*/