//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2018-2018. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// This code is partially based on the lightweight mutex implemented
// by Boost.SmartPtr:
//
//  Copyright (c) 2002, 2003 Peter Dimov
//  Copyright (c) Microsoft Corporation 2014
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#ifndef BOOST_CONTAINER_DETAIL_THREAD_MUTEX_HPP
#define BOOST_CONTAINER_DETAIL_THREAD_MUTEX_HPP

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#if defined(BOOST_HAS_PTHREADS)

#include <pthread.h>
#include <boost/assert.hpp>

namespace boost{
namespace container {
namespace dtl {

class thread_mutex
{
   public:
   thread_mutex()
   {
      BOOST_VERIFY(pthread_mutex_init(&m_mut, 0) == 0);
   }

   ~thread_mutex()
   {
     BOOST_VERIFY(pthread_mutex_destroy(&m_mut) == 0);
   }

   void lock()
   {
      BOOST_VERIFY(pthread_mutex_lock( &m_mut) == 0);
   }

   void unlock()
   {
      BOOST_VERIFY(pthread_mutex_unlock(&m_mut) == 0);
   }

   private:
   thread_mutex(thread_mutex const &);
   thread_mutex & operator=(thread_mutex const &);
   
   pthread_mutex_t m_mut;
};

} // namespace dtl {
} // namespace container {
} // namespace boost {

#else //!BOOST_HAS_PTHREADS (Windows implementation)

#ifdef BOOST_USE_WINDOWS_H

#include <windows.h>

namespace boost{
namespace container {
namespace dtl {

typedef ::CRITICAL_SECTION win_critical_section;

} // namespace dtl {
} // namespace container {
} // namespace boost {

#else //! BOOST_USE_WINDOWS_H

struct _RTL_CRITICAL_SECTION_DEBUG;
struct _RTL_CRITICAL_SECTION;
   
namespace boost{
namespace container {
namespace dtl {

#ifdef BOOST_PLAT_WINDOWS_UWP
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSectionEx(::_RTL_CRITICAL_SECTION *, unsigned long, unsigned long);
#else
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(::_RTL_CRITICAL_SECTION *);
#endif
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(::_RTL_CRITICAL_SECTION *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(::_RTL_CRITICAL_SECTION *);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(::_RTL_CRITICAL_SECTION *);

struct win_critical_section
{
   struct _RTL_CRITICAL_SECTION_DEBUG * DebugInfo;
   long LockCount;
   long RecursionCount;
   void * OwningThread;
   void * LockSemaphore;
   #if defined(_WIN64)
   unsigned __int64 SpinCount;
   #else
   unsigned long SpinCount;
   #endif
};

} // namespace dtl {
} // namespace container {
} // namespace boost {

#endif   //BOOST_USE_WINDOWS_H

namespace boost{
namespace container {
namespace dtl {

class thread_mutex
{
   public:
   thread_mutex()
   {
      #ifdef BOOST_PLAT_WINDOWS_UWP
      (InitializeCriticalSectionEx)(reinterpret_cast< ::_RTL_CRITICAL_SECTION* >(&m_crit_sect), 4000, 0);
      #else
      (InitializeCriticalSection)(reinterpret_cast< ::_RTL_CRITICAL_SECTION* >(&m_crit_sect));
      #endif
   }

   void lock()
   {
      (EnterCriticalSection)(reinterpret_cast< ::_RTL_CRITICAL_SECTION* >(&m_crit_sect));
   }

   void unlock()
   {
      (LeaveCriticalSection)(reinterpret_cast< ::_RTL_CRITICAL_SECTION* >(&m_crit_sect));
   }

   ~thread_mutex()
   {
      (DeleteCriticalSection)(reinterpret_cast< ::_RTL_CRITICAL_SECTION* >(&m_crit_sect));
   }
  
   private:
   thread_mutex(thread_mutex const &);
   thread_mutex & operator=(thread_mutex const &);
   
   win_critical_section m_crit_sect;
};

} // namespace dtl {
} // namespace container {
} // namespace boost {

#endif   //BOOST_HAS_PTHREADS

#include <boost/container/detail/config_end.hpp>

#endif // #ifndef BOOST_CONTAINER_DETAIL_THREAD_MUTEX_HPP

/* thread_mutex.hpp
wSwpOGG4iI7VdX9Jd6uPhIf4opJhFX3Lh9wnHrrm2vbdlakSB5cvJw7ec+VUDE2hOlj3ZZIaYjmawnACjQDIFAM9o9dt2x2d0tr4gTiOOTw8LBEAay8QSZLs1r1vbSSgLo1eZQTvEThvm0SpvpIsSH59EilgNBwSOl+XtwpQCsHu3i5HwwC0XQbs6/vrysX+jCyVOw03d8RBWYz0jY4rxEA3qytltAaVaZIEJjMYTzWTqZECkgwaVkx2sVrlOivvWk2rwklNGdWiCwhE7fR3gk9Nn3LC4O41Jd7pnjtVwpcgsqwIfpo2jLdECvMsjjO62YwgaFqCUngCnIswCALSNOXw8LAk/ntSwgt1718iAHU4pRc9uAtwWqRfFak1n15NqHzwNfoxGg7p9fvz0V0CDg6PGE9aC9jfKvDdcycFTbH71LqWfw97fPa4QpLQmHDaJDVegOkMprExBKbWI6A0yGo1VQRcQX+qXTwV1JQXi24qDhmfFssKYZij0aXEsnSgAiMFBJmpN0khVtCIoRGmdCPBYLBtz2OYX5tgPC/Z3DMPXqlLrLcBVF5An2Vwzwhn5fS1fv6Vhfz83r0tu6wKV/9kMmGwtZXHAAAgBFmWcjyaMk0GpuI6bl7Sr6W9XfQRlsz+WqlgUfm6eioi0ByWODm4jMVam01EMyVIM8001kYCmBhCkKSFGhDIU9LBUj8ofbPaoTorkfCa8ttw
*/