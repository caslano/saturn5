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
sA4ym9ngXzPehvWR+ZjVlGxrgtnX0P6a2f1H7DwZliBs4upnj4KlkXlg4v5uhjB+fA8rlsVN3BfOJcP4hoh7uMVkXmbm3RSwcuREHK13WKUwM5dg1UpcrWL1ohdzXIE1K3GtirWTWczMtQWsR7GYa53H5yWzmT20+KEyWCwZz2n+tgQLKTmTFEsR9TqW1n0CyxT1zG/IYblKznwyp2VdrMSVKnGVZE7roVrJWassz2ZleXYoObsc+8zO7WP1YumeuNkeYFaGs8UJ21h+uxfnYElk6GWYe2G26QWWoliqYumKZSoWUSxbsTwyHzNXx7vTYaVkNrPUnNDdsGoyi9nviyIfwBpEXP+QvR/C2si8zMw6gnWJPs1cgvWIeubb6bCYGdFxqz7rvQjmZSbHbivmVyxWsXjFEpjJ8SWSWczMfgmWquRMF2auc2CZSlzE0XLmZDM7zZ1xvTnmwPKE8bgCJa6IzGZ2V8Kf42AVGDtyvjNhA6xW5DTHOFg9mZfZmfddciusmczH7NMhqcNgXcIS3xn9FSzmuuh65pkfmJeZHLvNTI7dr8TFKhYvzPymFJZAxsewdui0Z2CpZBYz860wWFipl0XmZTZ+2cJYWD6ZzWzcrkNzYaXCXh+493ZYtegl/f17UmENws5dNmXV/yynlfUZ5x5xi1mesHZhZgywTiWum8xmZuYgLGYm9cLMzEGYj4znNHMQFmAme4ljJnsJOsbNWRBidrp7xCxTD5YkjMelCDP1YKlkNrN9H37/BCxCZjEzY4flK/UKlT6LnePCpcyGu8dlmD5h5cJ4XKUSV01mMzPrFtZIZjEz44O1iZxmDLAOpZcupZcex7jwiD5mZ9B+19SDuTKjjcd5hJl6MIvMZmbWLSyOzGJmxg5LVOolM5N9TnKMo+scZvHuRbOjrnOE8biwsKjrHDKbmRkfrJDMYmbGBytT6lUofVY5xmUvrGE2wn3XANMnrE4Yj2tQ4prIbGZm7sI6yCxmZnywXpHTjAHWr/QSc71zL15h5pgDs8l8zMwxBxYk432aYw4s+XqnXm7JmcTsTPfYBDMGWJowHpchzIwBFiazmZn5Assns5iZ5QkrUeqVKX1WOMbNnlXF7Cz3zYtMHKxGGI+rE2bGB2sgs5mZ8cHayCxmZnywbqVer9JnvzC+H4yZdcCCYh/pVcxWzK9YrGLxZD5mkxvjumApZDYz894tWKawpYdN+RqWJ3KO6/rrHlgpmZ/ZTVsih8FqlT7rybzMzDUQrFn0klxwTzesU8nZreTsV3Las6PHZ97NBAuS8XrmegUWEnEXJf9eDUsj4/X+efPGT2BZZAFmHXd3XgUrEXG/Va27EVZFZjHrLr3sJFg9GR+7uQcIa1asXeQ8sv3H72E9Yuzj/DcOgvWJuMnntnwA84aj58TY9/d9BYsn43FfnDXxZFiSiLMOPvhgWGbYed1mK1Yg7OeW1z+AlYSd51IZmc3sxhlD7oDVCHvryJ5zYE1KvTalXgczOc+6yHzMLrjcNREWMyd6ed59z4KZMB+ZU72AYnHMZC9BMqdlnSTicjq3pcNSyALMhn/x/jxYlhjDZ++f/i6sQKlXQmYzO2PDs4WwKjIfs7odMS2wRlHP/OYL1ibifv8ubgOsV1lm/YrF3OBsXm7iPNlmNlKcY/rJsK2MovOzUctLP4ElmjhmUb/VFMZzTlIsjQzLZTTdV3z0nCGnwrLJbGanrli/ElZEZjGb8pe7K2HlIm7dBxmvwGqVuCbRy/ivpvfDOkXOqfcEH4X1C9u9c/cumH2jqDd3rQsWR+aByXdakPlh4veKqWRemPhdXibPKX8LQMb7LL/zy+9gBcKCH419ElbmWG/1gCo=
*/