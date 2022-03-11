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
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
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

   bool timed_lock(const boost::posix_time::ptime &abs_time)
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

   bool open_or_create(const char *name, const permissions &perm)
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