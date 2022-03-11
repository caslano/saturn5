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
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
*/