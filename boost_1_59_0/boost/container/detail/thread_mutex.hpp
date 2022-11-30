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
extern "C" __declspec(dllimport) int __stdcall InitializeCriticalSectionEx(::_RTL_CRITICAL_SECTION *, unsigned long, unsigned long);
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
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
*/