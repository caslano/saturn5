 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINAPI_SEMAPHORE_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_WINAPI_SEMAPHORE_WRAPPER_HPP

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

class winapi_semaphore_functions
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   winapi_semaphore_functions(const winapi_semaphore_functions &);
   winapi_semaphore_functions &operator=(const winapi_semaphore_functions &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   winapi_semaphore_functions(void *hnd)
      : m_sem_hnd(hnd)
   {}

   void post(long count = 1)
   {
      long prev_count;
      winapi::release_semaphore(m_sem_hnd, count, &prev_count);
   }

   void wait()
   {  return winapi_wrapper_wait_for_single_object(m_sem_hnd);  }

   bool try_wait()
   {  return winapi_wrapper_try_wait_for_single_object(m_sem_hnd);  }

   bool timed_wait(const boost::posix_time::ptime &abs_time)
   {  return winapi_wrapper_timed_wait_for_single_object(m_sem_hnd, abs_time);  }

   long value() const
   {
      long l_count, l_limit;
      if(!winapi::get_semaphore_info(m_sem_hnd, l_count, l_limit))
         return 0;
      return l_count;
   }

   long limit() const
   {
      long l_count, l_limit;
      if(!winapi::get_semaphore_info(m_sem_hnd, l_count, l_limit))
         return 0;
      return l_limit;
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   protected:
   void *m_sem_hnd;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};


//Swappable semaphore wrapper
class winapi_semaphore_wrapper
   : public winapi_semaphore_functions
{
   winapi_semaphore_wrapper(const winapi_semaphore_wrapper &);
   winapi_semaphore_wrapper &operator=(const winapi_semaphore_wrapper &);

   public:

   //Long is 32 bits in windows
   static const long MaxCount = long(0x7FFFFFFF);

   winapi_semaphore_wrapper(void *hnd = winapi::invalid_handle_value)
      : winapi_semaphore_functions(hnd)
   {}

   ~winapi_semaphore_wrapper()
   {  this->close(); }

   void *release()
   {
      void *hnd = m_sem_hnd;
      m_sem_hnd = winapi::invalid_handle_value;
      return hnd;
   }

   void *handle() const
   {  return m_sem_hnd; }

   bool open_or_create( const char *name
                      , long sem_count
                      , long max_count
                      , const permissions &perm
                      , bool &created)
   {
      if(m_sem_hnd == winapi::invalid_handle_value){
         m_sem_hnd = winapi::open_or_create_semaphore
            ( name
            , sem_count
            , max_count
            , (winapi::interprocess_security_attributes*)perm.get_permissions()
            );
         created = winapi::get_last_error() != winapi::error_already_exists;
         return m_sem_hnd != winapi::invalid_handle_value;
      }
      else{
         return false;
      }
   }

   bool open_semaphore(const char *name)
   {
      if(m_sem_hnd == winapi::invalid_handle_value){
         m_sem_hnd = winapi::open_semaphore(name);
         return m_sem_hnd != winapi::invalid_handle_value;
      }
      else{
         return false;
      }
   }

   void close()
   {
      if(m_sem_hnd != winapi::invalid_handle_value){
         winapi::close_handle(m_sem_hnd);
         m_sem_hnd = winapi::invalid_handle_value;
      }
   }

   void swap(winapi_semaphore_wrapper &other)
   {  void *tmp = m_sem_hnd; m_sem_hnd = other.m_sem_hnd; other.m_sem_hnd = tmp;   }
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINAPI_SEMAPHORE_WRAPPER_HPP

/* winapi_semaphore_wrapper.hpp
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
*/