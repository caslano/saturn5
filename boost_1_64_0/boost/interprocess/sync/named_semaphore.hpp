 //////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP
#define BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/interprocess_tester.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

#if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
#include <boost/interprocess/sync/posix/named_semaphore.hpp>
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_semaphore.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
#include <boost/interprocess/sync/shm/named_semaphore.hpp>
#endif

//!\file
//!Describes a named semaphore class for inter-process synchronization

namespace boost {
namespace interprocess {

//!A semaphore with a global name, so it can be found from different
//!processes. Allows several resource sharing patterns and efficient
//!acknowledgment mechanisms.
class named_semaphore
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   named_semaphore();
   named_semaphore(const named_semaphore &);
   named_semaphore &operator=(const named_semaphore &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Creates a global semaphore with a name, and an initial count.
   //!If the semaphore can't be created throws interprocess_exception
   named_semaphore(create_only_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens or creates a global semaphore with a name, and an initial count.
   //!If the semaphore is created, this call is equivalent to
   //!named_semaphore(create_only_t, ...)
   //!If the semaphore is already created, this call is equivalent to
   //!named_semaphore(open_only_t, ... )
   //!and initialCount is ignored.
   named_semaphore(open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm = permissions());

   //!Opens a global semaphore with a name if that semaphore is previously.
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_semaphore(open_only_t, const char *name);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_semaphore();

   //!Increments the semaphore count. If there are processes/threads blocked waiting
   //!for the semaphore, then one of these processes will return successfully from
   //!its wait function. If there is an error an interprocess_exception exception is thrown.
   void post();

   //!Decrements the semaphore. If the semaphore value is not greater than zero,
   //!then the calling process/thread blocks until it can decrement the counter.
   //!If there is an error an interprocess_exception exception is thrown.
   void wait();

   //!Decrements the semaphore if the semaphore's value is greater than zero
   //!and returns true. If the value is not greater than zero returns false.
   //!If there is an error an interprocess_exception exception is thrown.
   bool try_wait();

   //!Decrements the semaphore if the semaphore's value is greater
   //!than zero and returns true. Otherwise, waits for the semaphore
   //!to the posted or the timeout expires. If the timeout expires, the
   //!function returns false. If the semaphore is posted the function
   //!returns true. If there is an error throws sem_exception
   bool timed_wait(const boost::posix_time::ptime &abs_time);

   //!Erases a named semaphore from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction();

   #if defined(BOOST_INTERPROCESS_NAMED_SEMAPHORE_USES_POSIX_SEMAPHORES)
      typedef ipcdetail::posix_named_semaphore   impl_t;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      typedef ipcdetail::windows_named_semaphore impl_t;
   #else
      typedef ipcdetail::shm_named_semaphore     impl_t;
   #endif
   impl_t m_sem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline named_semaphore::named_semaphore
   (create_only_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(create_only, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore
   (open_or_create_t, const char *name, unsigned int initialCount, const permissions &perm)
   :  m_sem(open_or_create, name, initialCount, perm)
{}

inline named_semaphore::named_semaphore(open_only_t, const char *name)
   :  m_sem(open_only, name)
{}

inline named_semaphore::~named_semaphore()
{}

inline void named_semaphore::dont_close_on_destruction()
{  ipcdetail::interprocess_tester::dont_close_on_destruction(m_sem);  }

inline void named_semaphore::wait()
{  m_sem.wait();  }

inline void named_semaphore::post()
{  m_sem.post();  }

inline bool named_semaphore::try_wait()
{  return m_sem.try_wait();  }

inline bool named_semaphore::timed_wait(const boost::posix_time::ptime &abs_time)
{  return m_sem.timed_wait(abs_time);  }

inline bool named_semaphore::remove(const char *name)
{  return impl_t::remove(name);   }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NAMED_SEMAPHORE_HPP

/* named_semaphore.hpp
5sJjIowYcsySa2nK9+3kZ6SKlwhPOd6Zfj+k7zeo52xFwe8jMK1cqynK7D2iaYt9E5f67naRcj6pWFNJWrlvZOET68KpJJofiIaWTb5zTtK5I/ViFc233kvYRn6deqB9rd30/XPF3FPm9z9Ek4R+Ms7Uo3tXEeuohms+TB9tFvHyNV6TrAKKOVEG2yvkvQbSFzOE9JXVrQte7E2s9Nj01PJcA2mV/b1tnqvek2A3Wa5EG2efExNfkWw5J7bIma5yBJYbrZaLHFietFo+dGA502r5x4HkTweWx/zkaOHe+NPtYz7cd5lz4+0PP3xxo8s+bTh50mq5zqHLmVbLdQ5dzrdannTDyYFWy+0OJOf715UbnasFLze6O8t4ngIj7ipW87uK1fxb8OkP/HsGfq/i39ksgzndeI/I/qq5T0/hNHyie2XsfQbsAKwBCj+fs8y1zjBH2H8C+3fAtGb/U0HXRMTN9OnGey1AiSK+r0EXDfwWeAbwOyC9WWP/i2DK2f889i/SN5v9Z3F82cBkwUtgb5bheh5wIXCMCAc4he3T2D6HZbxmAy+0pNedG5g/7zN/PmD+fMj8+cjCn+zcwPwZzekdz/Q3w5Qx/W1M74ZZy/TdQSf8pzF/BgOTgH2APYB9Of504CRgf+As4Lksm3gAMB94HnAJcCBwGfsvB2YAN3K4m4D9gFvILvlB95yBPRX8eIz5sRfYEvgXYHfg4+x/FEw5+1/B/kmPIvvfx+X/DLAV8FngXOB+4Dy2Xy7sHF6meV8TfS+H1whmGIcnZIMKfAToBj4K7M4yTlNZpmkPlnE6guxSJnAFh7uRw7XKBO7I4XYBNgF2BSYRH7z1rRewD7AbUPAfcVI+zgEuBaYCbxA8BG4Q9BzvDOMeHHAWxxsJM47j7cfxDuB4z+N4BwL7AzOAA4GDgYPYPpPskv8HOPwMO/9JlqfAZcz/FcCzgMu5/VwBFOH+wSxPvucEHKQIr4jD83B9WML19XdAQVMMFOm9mMPLMO//sJxBXgOmcXh/5PDWASNZhiq93eB03mippxUcTnNFPT3M4bwNFO7/BMYC37HUq2r230lRrx5g/w9yfa1k/w8x33Zy//MwsCNwlyVdNbWk624Odzun6x4O914Lf9z5gfmziv1fzfxZw/y5hvlzrbVf4n47XNEvHeBwXrXQZ9ZC/wLTv2htl5zOyQr+tQadE3gWkO7Kcf/ZBih40Zb77Xbcj3XgcKvN80E6HyV7vOAvh3sVt4trgW2p3/Ty/zqWnb0OmCH4C5zBspEvEvwFlrKM5EtZNvIy4HrgKuAG4J3Am4B3A28GVgE3AZ8Fbga+AKwAfgK8A/gVy2D+EfgnoFMX4bJMaZ3PbPgsrBp4DsyVunlfvkxnGeVRwAnA9sCJwE7AFSwTfBIwnXjsHc9gSHbwCs7fdGAu8HxgIcvMLQPOAl4LvIBl2+YCd7CM3J0sI7eaZeTuZ9m2L3O4rwBnAz8CzgVG6KhLQDcwB5gEFPTtdUHPMtCBKcALgcPYfTiwgGVEL2ZZt78DLmHZuVeyLNty4HKRTuDvgVvZ/50s43YHu+9k94eBhSK9nI6D7P4GsJRl3i4FogLT9wjgCtn/8rkAeK/of93c3ptzfY0DdgG24nqbADwX2AI4FNgSOJa+y3ZUVks7upXb0WYLvacW+o1Mf5Nu0bmwODiZtVphcHTuIOmSCwPL6J2iyflbKtMVKeZvj3O9/yuQ7gQCewGfAk4F7gNmA58WbAQ+A8wHPsvt+AlgIdmlLOtqjq+C47PKskabpfnUS8Bo4Ms8fh8Angd8FZgDfJ3j+TvwSuAhlg39JstO/wfwZuBb3J7eAN5Odtlv0X4C8ExFv/U=
*/