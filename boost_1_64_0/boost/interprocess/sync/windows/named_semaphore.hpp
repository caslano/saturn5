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
/vvJMdwArAA+BlzCuwxqeUfBdmAj8GvAx32yXOBkrNRDcpi3iLiAYeBRIHSXHObngE8B/8nnbqI/A0IHKZ8PFOGgLEvu8iJgE3AS8FngLOAPgDfzeS7wGDDA7+8A/hC4FNgMXA58Hngn8AXgWuCLwK3AHwO/AnwZ+ATl3+f7h4/j4uls51P4t4+cyH5yIqcBV9FudwEHkSN5FDmSJwI/Q27szzL8OmN+EHWJ4asc4Cco8iqwK/DnQPH7SZbTU+SW/gXwUnKvDwW+RQ7nFt4x8Tbj/yWwmJzsU4G/Vri4A0zHXUyHysX9Ceo5D5gJvI16BhjvfOCVwCpyzS8gF/gyxruI5egOcr8vJud7Ne9EWApcJeXN/jVAuw+39a/yzKy0Sx7Hb/nAxgiHdKvc0aO3Jfnmwa2Fa4R7Ea4F7jxczvYkySU9GrjwqVhO6en4TscrXbk9KSFu6Vr4c+KX3oXfnt6e1G480zp+6WaEr3JMn9me1O4801aOaZVfOnlHkiuO6dGQK9mR5IlrOgA58k3H45o2eKZrdrSdZzq0I8kV13Qj5E4CW4DngU5802d3JLWJczpnZ1K78k4fm5bkmXuavNPgaPfGPT0FaVf5p+fh2cJBHZd/erWQhzsGdxoudVeSrxBuNlwQLgR3BK4Z7gxc6gMoi3BT4CrhNsDthzsOdxouczc4qOEq4TbAPQ13Bi5/D8omXB1cA9wJuPNwBXvxPVwtXD1cE1wLnO9B+IErggs82MFp3fHp+HR8PvjPB8P/V1VbU7VUEAC2if9vIHYkDsVgM9zH4OsrnjO7eEbp1JkzSP9ncP9NybHLmMx/Ec6+r/b2GbwANQ6cfc0H5XqoJSBvnG/z4nC+5Wg4+/qJcze6eAUhGjkX3nPmQ4NfT3xoMRwD72k4+57WpPETcrJLk0buimEanblFGjxxolnSaOdEG+3E2aezo0cuu+Fx8q9ew9mXi/zL19oGuxcS4OeKxnUs2c5f0h9xFcm4yF+ixseycllfx3yAX/f8JUUe9psWNSTOX3JZX+/8JVEbne5st1G+OEftZKPSiI0ac+Lwe3iwUcCDjQJtsFFjTuI2erGLnQNloDiv3KByoKjlqPX6XNfgngOlriFxDpT3XPK8NHa16zgIOtY76chycDbO3db1HnSsb4OOSENcHc+K8PzO+xT0+ymc9wvo94M477N4brH4fvP7C/7Z77rt/WZmXnPX/qc++q739X/9/gvn/QX6fSjO+zv0+1mc9pV43wdhrBscNNeHay3rMznqugHlMjRyuYqcr8FZrq8i1+QYr0TKwTG8nq2EV0S5vq3IBeLI9VPk6iiX3Up49U5yDG9bJ8g9hPduOMwfuJ6PU+fici3zb9a5t5NwypybOtfGuTV382qngbtKzHm0ZmAYTsybbdLMl22DU+fIxppzY+q8GOfCjDmwuHNfw+Hsc13m/FYy57Esc1iO81cni5zmq5znqhrglLkpzkvZ56R2jVfmoZznoBznm3ZF5phc3WtmnVeaB+ebq84fmXNH1ShrIbgjcCfhzsHl7sN8DVwl3IZ9HXM2HZ///88H8/5fsbxavv23jf8/+v6/Ict4t59VfPPMacWT+PZPnv6t6EyDuHA2SZzxEHGXLamqWeiT/rtkY2+P/K2yakH5ymrz92WV8p0QMgUXo68245g4azpY0CfPLCtfWSvDGJyHd0v770Yi+jKM+uwYGXhH+NThaMxv9Mp5iUZlXmKM5t27APHX7eP7pZIAlY98SF6csfq+xN+9ES7fvU3OyMOd9O/eQU0avXBir82OM2+iee8eJsb3mjgT5cU23pcY1yUUyIcbjriaLHF9tHj2lJmTzDsLLpN5sMQ433E=
*/