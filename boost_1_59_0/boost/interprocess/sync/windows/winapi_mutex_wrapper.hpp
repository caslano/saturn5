 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/win32_api.hpp>
#include <boost/interprocess/sync/windows/winapi_wrapper_common.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class winapi_mutex_functions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_mutex_functions(const winapi_mutex_functions &);
   winapi_mutex_functions &operator=(const winapi_mutex_functions &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_mutex_functions(void *mtx_hnd)
      : m_mtx_hnd(mtx_hnd)
   {}

   void unlock()
   {  winapi::release_mutex(m_mtx_hnd);   }

   void lock()
   {  return winapi_wrapper_wait_for_single_object(m_mtx_hnd);  }

   bool try_lock()
   {  return winapi_wrapper_try_wait_for_single_object(m_mtx_hnd);  }

   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time)
   {  return winapi_wrapper_timed_wait_for_single_object(m_mtx_hnd, abs_time);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   protected:
   void *m_mtx_hnd;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//Swappable mutex wrapper
class winapi_mutex_wrapper
   : public winapi_mutex_functions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_mutex_wrapper(const winapi_mutex_wrapper &);
   winapi_mutex_wrapper &operator=(const winapi_mutex_wrapper &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //Note that Windows API does not return winapi::invalid_handle_value
   //when failing to create/open a mutex, but a nullptr

   public:
   winapi_mutex_wrapper(void *mtx_hnd = 0)
      : winapi_mutex_functions(mtx_hnd)
   {}

   ~winapi_mutex_wrapper()
   {  this->close(); }

   void *release()
   {
      void *hnd = m_mtx_hnd;
      m_mtx_hnd = 0;
      return hnd;
   }

   void *handle() const
   {  return m_mtx_hnd; }

   template<class CharT>
   bool open_or_create(const CharT *name, const permissions &perm)
   {
      if(m_mtx_hnd == 0){
         m_mtx_hnd = winapi::open_or_create_mutex
            ( name
            , false
            , (winapi::interprocess_security_attributes*)perm.get_permissions()
            );
         return m_mtx_hnd != 0;
      }
      else{
         return false;
      }
   }

   void close()
   {
      if(m_mtx_hnd != 0){
         winapi::close_handle(m_mtx_hnd);
         m_mtx_hnd = 0;
      }
   }

   void swap(winapi_mutex_wrapper &other)
   {  void *tmp = m_mtx_hnd; m_mtx_hnd = other.m_mtx_hnd; other.m_mtx_hnd = tmp;   }
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINAPI_MUTEX_WRAPPER_HPP

/* winapi_mutex_wrapper.hpp
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
*/