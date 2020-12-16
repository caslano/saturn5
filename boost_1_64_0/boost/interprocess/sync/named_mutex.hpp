//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_MUTEX_HPP
#define BOOST_INTERPROCESS_NAMED_MUTEX_HPP

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
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/permissions.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_MUTEX_USES_POSIX_SEMAPHORES)
   #include <boost/interprocess/sync/posix/named_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_mutex.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
#include <boost/interprocess/sync/shm/named_mutex.hpp>
#endif

//!\file
//!Describes a named mutex class for inter-process synchronization

namespace boost {
namespace interprocess {

class named_condition;

//!A mutex with a global name, so it can be found from different
//!processes. This mutex can't be placed in shared memory, and
//!each process should have it's own named_mutex.
class named_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_mutex();
   named_mutex(const named_mutex &);
   named_mutex &operator=(const named_mutex &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global mutex with a name.
   //!Throws interprocess_exception on error.
   named_mutex(create_only_t create_only, const char *name, const permissions &perm = permissions());

   //!Opens or creates a global mutex with a name.
   //!If the mutex is created, this call is equivalent to
   //!named_mutex(create_only_t, ... )
   //!If the mutex is already created, this call is equivalent
   //!named_mutex(open_only_t, ... )
   //!Does not throw
   named_mutex(open_or_create_t open_or_create, const char *name, const permissions &perm = permissions());

   //!Opens a global mutex with a name if that mutex is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_mutex(open_only_t open_only, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_mutex();

   //!Unlocks a previously locked
   //!mutex.
   void unlock();

   //!Locks the mutex, sleeps when the mutex is already locked.
   //!Throws interprocess_exception if a severe error is found
   void lock();

   //!Tries to lock the mutex, returns false when the mutex
   //!is already locked, returns true when success.
   //!Throws interprocess_exception if a severe error is found
   bool try_lock();

   //!Tries to lock the the mutex until time abs_time,
   //!Returns false when timeout expires, returns true when locks.
   //!Throws interprocess_exception if a severe error is found
   bool timed_lock(const boost::posix_time::ptime &abs_time);

   //!Erases a named mutex from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   public:
   #if defined(BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES)
      typedef ipcdetail::posix_named_mutex      internal_mutex_type;
      #undef BOOST_INTERPROCESS_USE_POSIX_SEMAPHORES
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      typedef ipcdetail::windows_named_mutex    internal_mutex_type;
      #undef BOOST_INTERPROCESS_USE_WINDOWS
   #else
      typedef ipcdetail::shm_named_mutex        internal_mutex_type;
   #endif
   internal_mutex_type &internal_mutex()
   {  return m_mut; }

   internal_mutex_type m_mut;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_mutex::named_mutex(create_only_t, const char *name, const permissions &perm)
   :  m_mut(create_only_t(), name, perm)
{}

inline named_mutex::named_mutex(open_or_create_t, const char *name, const permissions &perm)
   :  m_mut(open_or_create_t(), name, perm)
{}

inline named_mutex::named_mutex(open_only_t, const char *name)
   :  m_mut(open_only_t(), name)
{}

inline void named_mutex::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_mut); }

inline named_mutex::~named_mutex()
{}

inline void named_mutex::lock()
{  m_mut.lock();  }

inline void named_mutex::unlock()
{  m_mut.unlock();  }

inline bool named_mutex::try_lock()
{  return m_mut.try_lock();  }

inline bool named_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{  return m_mut.timed_lock(abs_time);  }

inline bool named_mutex::remove(const char *name)
{  return internal_mutex_type::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_MUTEX_HPP

/* named_mutex.hpp
vBymjZ0aYvvS5tkvB21eaOVgDvsd2tdZUgj7wyq5gzdwexJ6lPKQ4N6QxQbRnqK7RkU7EqFaLiVmAo70XoITvNERfKaMy+1WkEjrp8m0A6CirGhxaRnH34Qwm5/pF8IeRenoZJzxnk/37dkdp33pvg27e+910qmRL9a3kb7+pFtpFs66aZazX6p2b65ckf+mdi/knyzkb6Pdn2TlcXO5vuWDvhL9uaq+hdjuq0Kob1Uh1reqEOob8/qtH2f81I+X/8XetcBFVaXxe2cAQUYdEFDJCN+maKioaKb4fis+U1MBBZVCmAW0h9aiW6ZlK5VamRaZW1ZWZJbYui2Vlb2tbNc226ysbNeKyraX1f7PN9+9587cMzAjVLv95Pc7/Oec+53Xd96v7/OrHx/41Y/PyO7k72zn+rEPdWNYpFE/xijrh2/9tcv9CPuZ+h5ZP4iW8i/4Es988ZelWtXYPubrieBtrl8dCbE/cucGXz/cuaHVD2vYKBb8Ek+q5biQkhtwXIDfusf7Y0hUMpix+n9ovBf5jOd8qtu9LNMBLvt470SZZvuXaYhtPjuEMs0OsUyz6yjT3MBlCr+/3lgvy8Wv72V59bfBOGC2wHyNuMoCl0EWbu37lYN8a34N+VuF/OJMRhugfkelLh+zz3uDvjdRv6kKsbyscVW2JPqLrDJ9HqLvi/BSvbGqzKR/KQ8SrymkTJQb6Pu1WhT+X8l0n8Zw/26R+/O8oCOpkTFKWRp30PeLtcUIScoAQFQWvlQRjZvk1WUgcylNjXfuSSSsbpYr3IG362oZFewnE37axqjlmiTCHg77mliUI8y1MGthEmPrlkfXUPUUZcTvQnzlTC/nCHty/98dxpWI/OT51dMQ+v7MvOD7CQst17vCnMV5yjoHWqXsClX9Am3t/TyVJffh1zRgP+7z9p7zwmVgfY9fZx9+gGXUr+C52+UwTVEu5cpyySrMzw2ubMpDKBumlbJuRNujqALM29TlQ7Iq3Ob3Nr7ztzrKSbTJMhCmgx/XwTjbkBxqyKV2OVu7EiONtvVHfFsHUw5zPcwNMIHS8RDFmS1lAWOtll8q+5S/0PdMrQfJvWQaynvppZ48KdvvWaLrhT2YmDrnBfVdD9AbLpP/odUpo62n8yWekfJutvYE+oWMBf51Kr8n4lCUu7pOwb/v2zbip7pOMS2F7QwzwoZIlyXzlXXKSr+K+m5jd0uWw2ii6a+1RQiGHG0Xy924MbZu2fUkW0PNY/l+jvIky0OkPV6m3YfP7XnitZHvUG2AaYS2W+HP5xDmXhULgm+3FQuC71NBq2yzso1KGu5nA7ab+4lujNZZjtc2OdtfE83AWtvVbqLphnYVzjLmuX1z217P7dsqS0ULoq291UB9t7WfPoFMib9ZXNYzYdxirr3QXtbcUQdV3tkLgy/v7IWh9dPZC+su8+yFwZX5YqIbh75Sr7VML17oLfdEhBS4z+aybMB1cjD9prU8I1kvRYZ8j6W1Rx95wKc8F+aVSnm9AefbB8lPY2X5Ijz1fFtVxpJe6uRw192v1SIrlPNvzUO/mE8oDujVivWdi8xONHlBfwNhWsMteZGNJ6XFOJ3QauFJ+0UBeYLwVP2Wkh+gDW29kryoYfjHdc3aR3BdU/N0AMWLPtSPp6Vn8OtteX9Z64h65vHhKYdFwjTUPG0OXE5+3CqecnhSJrTkk1xblxJNSyWf2f8p8UrKpbXz5Rrmy32xvuvmRa29gTbXpB7NJDF2+vIFdU2eZynrG+dtG/lrph5TOW9y3kzBqcfUevCB6wzP9SgOX10/rGOjEwfUESYZea625Rnh1ZLXfUTfTi0fQtYD3l/JLylZkles1lcm6eV+TMk=
*/