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
   posix_named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   posix_named_mutex(open_only_t open_only, const char *name);

   ~posix_named_mutex();

   void unlock();
   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
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

inline bool posix_named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
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
WY+1oJNL4unzeq+ywvE6FAvpvZhrcw9EW9pKPaKfCWkZXoW8gKjEMfr4Z6pK/zrALqAcGpV5ybE3stmN7JqOvmj73QjNkHomvvgQ/LjaQqRCsl28mk9UmxVNeFzC1IPjeHMwsgmU/ukbfEVtGdGqTc5dEOOZwI66vLhKFO5TCT/oPwnHW0WRmOjo8tdEArsZDNNeo9i+IbqPR3pEfIWA0u9IODUlLH3UIaizP14hnyfMw2BQs5g5c9SBrv3TQUifQS9wy9kK3ZPAk7eOeEsPJZHiYyUwjcaDno4BwRz7BB08EJlRsyL3xKyjcWRp66mSW8NvREO34p3GrcJcxHTrfWnFXIezhO+K3kwS2sy0QniKthJWuGpPJVAQDZxZwfHU88UQxej41PV1eVXsxg4asoaY+Byyjqh2pwvYjfhMhB6ABurNQCMXwx9ck6DZYZaVeYt22Kvzejud6M3+SREOPnoAOoUVJuGX8ZPdHzfbgOPCZktA7nT7eOC7oig/YesbGCP9rLz9G3HHSGFJ+yOFRHeaMwEwQZay2UEsKF38+x8nD6tb1r8N54WVldwSiZ0l2h7FpCbawyDKuYSafinpiy2QP7mkuyOw/RSalEMWFEmqiQizou3FQGeGod7EODqcE+fxpanW67M2iU4JN2ezyrflk2jtW8b28v5NUxPXZ2G9ZelU3vAjcDDUnU48mm1IaYORgIkzGJKjdQbJ
*/