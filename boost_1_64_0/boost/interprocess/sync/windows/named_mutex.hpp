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
2bgteX0Zt3V9fv+TvauBr6qsw/eyAQMmbGMbEzaYyMdQ0CGopCjjYwRBsBgaGLo7tiHIgBsMG0Y5DAQJ4UZ8CSjLQCZSLaXE0lqGRX7kSjIwP2ZZYZHdjIqKX/W8733uOe895z1359wNq99vl9/Ls3Pv//34/9/P834878iLW2/fo+/QNYN98nMIkaQT0/LgnjA5KNSXaHUeJJvvvQOk7B7/OGi5yZ/Md9FoGJ9QbcDvVD4fWd4M/pGH5e/XIZ6BMpww+HHGyO/u8WfIMilPZC/FdHHVCoUj8LpIev2YB8Y56y567hlIrD8i+exl2OcQ9o3S32qELcslPnj1FsErfBeFUmajfwRKQ19/lRHWOhnWYPWd3phnXSX9HIMW98q4ziKuz8jvbvBDnvO7QYOnqKcRv4zcCGeP9DPAf69vM+cqovEmRecz8DFenSmDdQUpM8Xqx8ibxTLcmX7bPAHzoVjKdzbmKD4in6+36i7XHtJQZ1bjcN8E8R6ZNCo1pYuP5VaZO6BcPeR2yvfmWfb7milzwgirMjWlW2pS3X5Jhaedk4jGfx5+Jgo/3erqUpN6mPXGEn8+Dv7tEvFfVPeI2vaqMpMg84BMY91ONY1qfNWQ2S35ydd8LjUpQ+m7YsMKQe7Hck1mTa2Nc4oyRyCzR3Ki1/1bTZMa3+uQ2RuReRbE6XbedMr5BnNeotuafcq4SsqQp0Wuu02GzINwD8HtTpMo25e0VtbiNhwx1uJsc5J4lmWZPNgx7cz5Ap/8lPrhDziT7UzhNyztTNVSyXSjtDMGx2OVlL3Y/wtfZ137yrCc25YN8vdrZdsSrf8l8rtR9rZFWeObImW6+B/1zTbK/wx5HvZKW93PEXki5bP8P8c6lZe6vkb6ewmrUYuNNd075Xfd/D3w7Qu+iyJ8mnmWOk/9Zsk09RDxyPbGVrepz59kmDNsuogyVIvyM2lotI7m2+poX8rUDGUd7XFtalIFZgyd6ifl9w6N1s/Jonra6yflmoZG62e1OTayyLwzNFo/bzXTZ5FJKWD97LFmoK1uUmZ4VCa97s9OMiUFRt3c4JSemgKjzmVZ61w2npM5H1rfG6jcR5DqVNfIiRTJT9+SqiWiurVe3zD+lfmO8oFnlg9Lf598pU9+nkTAOcAngKvRhzQ3WOthbRkWihSeL0lzZZTVMY/K/sFf7bRXrUGzXqSU1Tfl75nG/pghhyRfl/79oMH9ehJkdZxjOh4xyqrjsZry24G6uwkoq3CnlVdUl69Y4dPdTWAJO0iutRrK5iqyuRbZu+T8SEVNLWXzFdl8ymr5EGnXApkvecZ8/0XSriPZBmJEIH8f5+8Ctg8pg6cJUma8z9YGKuOJRunvJua/37dfPr8Jm2+VacmWbVLsnqtbpMwQ/xu+HkbbF7P+wXZ9l5Sr53M0PeOUtvUOQ5/HpWwpx33RdLyF30sR4tWxHLv085602Tdd+AnKdJ6zt9GGfX8o/faQtuoT2w4b7a4Yx/iGoc0bjnuk5NoK+uyULqnJc7C+4tBOZtBPE/zsj7Q3J6xtZF/KhIez7e1W98tUf2FqSqf4YWaOMMYqa23tHGXGQGZyhpS50zpOyaZMwAxnknbMQ7m1kDsQaQ+7qe9waliHR7Bd9df9LbV7sr2tp1zzCPYbXevCqj3U8cwjCOcgXAPb2EddtrFiPIOyZt1bRF4/2d65Xlsm15+N/y/TePeSbYvlXhC2IZTNBQbJNch9FbL+o03Ad2gTFM5Q1Dfu75P9giyzKMMx/UAftR+wrHdMKfTJz3Tuf5oG9ymRgMP2foDrS1bOR6N+dZZ+JuvfeQ9r22NtO09ZY+znU3jLU+VvN/rkHib0Yafh5LpVao4=
*/