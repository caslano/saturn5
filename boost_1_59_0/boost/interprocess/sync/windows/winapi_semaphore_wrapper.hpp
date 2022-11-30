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

   template<class TimePoint>
   bool timed_wait(const TimePoint &abs_time)
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

   template <class CharT>
   bool open_or_create( const CharT *name
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