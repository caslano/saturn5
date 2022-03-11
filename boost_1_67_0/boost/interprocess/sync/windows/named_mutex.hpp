 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP

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
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_mutex_wrapper.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {



class windows_named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_mutex();
   windows_named_mutex(const windows_named_mutex &);
   windows_named_mutex &operator=(const windows_named_mutex &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_mutex(create_only_t, const char *name, const permissions &perm = permissions());

   windows_named_mutex(open_or_create_t, const char *name, const permissions &perm = permissions());

   windows_named_mutex(open_only_t, const char *name);

   ~windows_named_mutex();

   void unlock();
   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();
   winapi_mutex_wrapper m_mtx_wrapper;
   windows_named_sync m_named_sync;

   class named_mut_callbacks : public windows_named_sync_interface
   {
      public:
      named_mut_callbacks(winapi_mutex_wrapper &mtx_wrapper)
         : m_mtx_wrapper(mtx_wrapper)
      {}

      virtual std::size_t get_data_size() const
      {  return 0u;   }

      virtual const void *buffer_with_init_data_to_file()
      {  return 0; }

      virtual const void *buffer_with_final_data_to_file()
      {  return 0; }

      virtual void *buffer_to_store_init_data_from_file()
      {  return 0; }

      virtual bool open(create_enum_t, const char *id_name)
      {
         std::string aux_str  = "Global\\bipc.mut.";
         aux_str += id_name;
         //
         permissions mut_perm;
         mut_perm.set_unrestricted();
         return m_mtx_wrapper.open_or_create(aux_str.c_str(), mut_perm);
      }

      virtual void close()
      {
         m_mtx_wrapper.close();
      }

      virtual ~named_mut_callbacks()
      {}

      private:
      winapi_mutex_wrapper&     m_mtx_wrapper;
   };
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline windows_named_mutex::~windows_named_mutex()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.close(callbacks);
}

inline void windows_named_mutex::dont_close_on_destruction()
{}

inline windows_named_mutex::windows_named_mutex
   (create_only_t, const char *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline windows_named_mutex::windows_named_mutex
   (open_or_create_t, const char *name, const permissions &perm)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline windows_named_mutex::windows_named_mutex(open_only_t, const char *name)
   : m_mtx_wrapper()
{
   named_mut_callbacks callbacks(m_mtx_wrapper);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline void windows_named_mutex::unlock()
{
   m_mtx_wrapper.unlock();
}

inline void windows_named_mutex::lock()
{
   m_mtx_wrapper.lock();
}

inline bool windows_named_mutex::try_lock()
{
   return m_mtx_wrapper.try_lock();
}

inline bool windows_named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   return m_mtx_wrapper.timed_lock(abs_time);
}

inline bool windows_named_mutex::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_MUTEX_HPP
/* named_mutex.hpp
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
*/