 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/sync/windows/named_sync.hpp>
#include <boost/interprocess/sync/windows/winapi_semaphore_wrapper.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {



class windows_named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_semaphore();
   windows_named_semaphore(const windows_named_semaphore &);
   windows_named_semaphore &operator=(const windows_named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   windows_named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   windows_named_semaphore(open_only_t, const char *name);

   ~windows_named_semaphore();

   void post();
   void wait();
   bool try_wait();
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class interprocess_tester;
   void dont_close_on_destruction();
   winapi_semaphore_wrapper m_sem_wrapper;
   windows_named_sync m_named_sync;

   class named_sem_callbacks : public windows_named_sync_interface
   {
      public:
      typedef __int64 sem_count_t;
      named_sem_callbacks(winapi_semaphore_wrapper &sem_wrapper, sem_count_t sem_cnt)
         : m_sem_wrapper(sem_wrapper), m_sem_count(sem_cnt)
      {}

      virtual std::size_t get_data_size() const
      {  return sizeof(sem_count_t);   }

      virtual const void *buffer_with_final_data_to_file()
      {  return &m_sem_count; }

      virtual const void *buffer_with_init_data_to_file()
      {  return &m_sem_count; }

      virtual void *buffer_to_store_init_data_from_file()
      {  return &m_sem_count; }

      virtual bool open(create_enum_t, const char *id_name)
      {
         std::string aux_str  = "Global\\bipc.sem.";
         aux_str += id_name;
         //
         permissions sem_perm;
         sem_perm.set_unrestricted();
         bool created;
         return m_sem_wrapper.open_or_create
            ( aux_str.c_str(), static_cast<long>(m_sem_count)
            , winapi_semaphore_wrapper::MaxCount, sem_perm, created);
      }

      virtual void close()
      {
         m_sem_wrapper.close();
      }

      virtual ~named_sem_callbacks()
      {}

      private:
      sem_count_t m_sem_count;
      winapi_semaphore_wrapper&     m_sem_wrapper;
   };

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline windows_named_semaphore::~windows_named_semaphore()
{
   named_sem_callbacks callbacks(m_sem_wrapper, m_sem_wrapper.value());
   m_named_sync.close(callbacks);
}

inline void windows_named_semaphore::dont_close_on_destruction()
{}

inline windows_named_semaphore::windows_named_semaphore
   (create_only_t, const char *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoCreate, name, perm, callbacks);
}

inline windows_named_semaphore::windows_named_semaphore
   (open_or_create_t, const char *name, unsigned int initial_count, const permissions &perm)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, initial_count);
   m_named_sync.open_or_create(DoOpenOrCreate, name, perm, callbacks);
}

inline windows_named_semaphore::windows_named_semaphore(open_only_t, const char *name)
   : m_sem_wrapper()
{
   named_sem_callbacks callbacks(m_sem_wrapper, 0);
   m_named_sync.open_or_create(DoOpen, name, permissions(), callbacks);
}

inline void windows_named_semaphore::post()
{
   m_sem_wrapper.post();
}

inline void windows_named_semaphore::wait()
{
   m_sem_wrapper.wait();
}

inline bool windows_named_semaphore::try_wait()
{
   return m_sem_wrapper.try_wait();
}

inline bool windows_named_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{
   return m_sem_wrapper.timed_wait(abs_time);
}

inline bool windows_named_semaphore::remove(const char *name)
{
   return windows_named_sync::remove(name);
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
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
*/