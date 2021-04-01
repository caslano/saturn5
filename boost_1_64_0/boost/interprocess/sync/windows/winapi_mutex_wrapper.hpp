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
w+5qKr9rJ8G5GQ8kvEie2rn/5bWmdD7conEvhK/g7KkbLchTQ1eYHLYZ/WDmBtC0ciq7QqK4WaU48h+5yKKdyLgrPIFaOGRIm/gCrc4aU7FWHowClTkI4Wcx6Dyhrj0iGdolLDU2LPF1vbdZ65ma6bW7l/+8DyjkZ0bbU98gmC6uX9N42E1VcH2fDdJiGDTWpzSDs9V9D7FkjSLSBsSTKb3pLaNUYtL+5yNz4JZ25Soy5GYCVsQwFb/Z2Q16vDIDXxiZ5GvxDCKC51v4qBkhQg2CEnJAvcp+I+RZ60DUSkL1JeiAbL++dO4qRvHjte4hIBHIZahjyA64l4g5i/+3jR1xqNYhw2MwdPcyB9jOsXMnC+1s8NaKv0zYxGPQfBsqo+4vOZ6ZgxBYVEn4ojUmvvXi3Wj4P/LGE4V6rboJIgQbiFa7NcWvx9HCVXCuOmTWeMPZVbolEsPhMrUV61o4YJY58KgVPKKo/5Etbq9Zs52dWB/x0kZ6oFWRKoKSR12d4dWbjcc7tAgp1QXRwajKPdRI1piBzV3acz+RWx1A8AuTvG/mjJLlKa8viw==
*/