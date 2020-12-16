//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/named_condition_any.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#else
   #include <boost/interprocess/sync/shm/named_condition_any.hpp>
#endif

//!\file
//!Describes a named condition class for inter-process synchronization

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
namespace ipcdetail{ class interprocess_tester; }
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//! A global condition variable that can be created by name.
//! This condition variable is designed to work with named_mutex and
//! can't be placed in shared memory or memory mapped files.
class named_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   named_condition_any();
   named_condition_any(const named_condition_any &);
   named_condition_any &operator=(const named_condition_any &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Creates a global condition with a name.
   //!If the condition can't be created throws interprocess_exception
   named_condition_any(create_only_t, const char *name, const permissions &perm = permissions())
      :  m_cond(create_only_t(), name, perm)
   {}

   //!Opens or creates a global condition with a name.
   //!If the condition is created, this call is equivalent to
   //!named_condition_any(create_only_t, ... )
   //!If the condition is already created, this call is equivalent
   //!named_condition_any(open_only_t, ... )
   //!Does not throw
   named_condition_any(open_or_create_t, const char *name, const permissions &perm = permissions())
      :  m_cond(open_or_create_t(), name, perm)
   {}

   //!Opens a global condition with a name if that condition is previously
   //!created. If it is not previously created this function throws
   //!interprocess_exception.
   named_condition_any(open_only_t, const char *name)
      :  m_cond(open_only_t(), name)
   {}

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~named_condition_any()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.*/
   void notify_one()
   {  m_cond.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_cond.notify_all();  }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  return m_cond.wait(lock); }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  return m_cond.wait(lock, pred); }

   //!Releases the lock on the named_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time); }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred); }

   //!Erases a named condition from the system.
   //!Returns false on error. Never throws.
   static bool remove(const char *name)
   {  return condition_any_type::remove(name);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   #if defined(BOOST_INTERPROCESS_USE_WINDOWS)
   typedef ipcdetail::windows_named_condition_any   condition_any_type;
   #else
   typedef ipcdetail::shm_named_condition_any       condition_any_type;
   #endif
   condition_any_type m_cond;

   friend class ipcdetail::interprocess_tester;
   void dont_close_on_destruction()
   {  ipcdetail::interprocess_tester::dont_close_on_destruction(m_cond); }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_NAMED_CONDITION_ANY_HPP

/* named_condition_any.hpp
y+8CY4AfA2M5nXHAdGA88HLWlZwFTOH0nwOcxrqWZwG7ANcArwDuBI4Ffg84DlgLHA98hnUx/xmYCvwEeAGwfYRHN7QT2BPYGdgL2B/YDzgM2B94Gd+P5PvxwAHAKcAo4I18Xw7MBG4BDgc+COwNfAF4EfA9YB/gh8B0kW/gIJEOyP1iYF/gYOAg4EgRP3A8l1OVsb/Rsw/zOJ/1Xu/9oAc+XfAAU4FTgb2A07ieXAWcwO6z2AbGHGAB15drgQuA17HO6Hzgrey+ETgd+DA/3y+ec7qqde8+OOSJ608GaBPXnz1cfx4FXsi667OA+4E5Ii/A7wCfAG4HPgu8l20tHGDbCk8BD7JufJD7Lba18Du2sXAG+DLbjDkM7AN8DTgG+DowF/gmsADYwDYF3gGWAX8BdFN7Qz6BvwRuAb4LvBv4nkb1idJ9FPg74E+Bvwf+HlgL/Cfr3D8/Av00sAfwRWAGsB44BPgWMBeI6TLVl7eBy4FvALcBj4l8An8MfAb4a+CbwA+ATcDfAD8Ffgj8HPgJ8Avgn4HJkHsTMA34F+BFQLizrR/eAwTspLD1s43rzXZgF9YpPhBYDbwauAvoAt7HtjnuB65lGxpVbGNjB9vYEGHu0dmWAfBZ4MPAQ8B9wDc5vN+yTZDPgPuBZ4AHgIk66gHXK7ex9wN54XR34Hc6jXWdO4ErOb03cT2/GTgFeCv3R7dx+m8HrgOuZZsi64CPsc7zA8DVwLeAIryPSYc5y0/n78H8bVuk42JP/ug3U9haAOazTvsCYApwLtvYmQfMYBsQmSIM1nG/gG3uLAQuAC5iGxwgsoVyA7CM76vYZsdu4FK2FVEG/ABYzjaUlgM/Aq4AfiLkAoxg2xftgW62vVEJ7A1cC8wQ+QcOAt4CHA+8A3gVcBNwNnAbMB+4HYixg9JzK3An67LfBbyb71FHKJ/fBd7MtjbWAJ8A7gA+C7wL2AC8m9vRZuCHQt4i3cCtwM+AG4B6BMoP6AAWA7sCXcARwN1CjsD7gNcA7wcWAB8wj88bpO2CimbjLtIi5302+VJt8mVssGcTI8smX65NvvwN/m1E/NPE57LJ57bJV2WTr8YmX20Avs/M8zmbfA02+RqD8O2Gg9lWQfUlVhsFO0CdYLsgsw90bIPWg/aCjoJOg5zpDqV9gr54Lm0USPsE0jbBt2OX4JuwSZCHvPuzS1CU7vhWbROEapfArj0Cu7YI2A5BIBsEbH/AantgR7ojJPsDZ8P2gK/dAfAhDYFsDzTAne0PsO2B8O0OqGwOnEY8vnYH/jttDrC9AT+2BlpuZyC6L+QDmglyg2pAh0DHQZ+Dkvo5tMGgmaBVoN2gelAj6Azo3P6wKwAqAm0EPQI6BjoNShqAsEG5oDLQDlAtqAF0ChSdARswoDGgfNB60COgY6DToKSB6DNB+SA36BHQMVAT6Fy8LGWBFg1qtTXQ+mv9tf5af62/1l/rr/XX+mv92f19c/r/lxUvIPX/4en/F/qhDyTgjD0WUR1asQh1jvd0QDd2qyM3cipaVFC6iBlIj/5akx79o6yffgSoPe8r+ETsdZwr1oNIf+5VF88ZOzNvzuhpOVBBPZ8y4dn/9Ava/0T36v2Oc5VnmNT7HZk3wTijJHUjWM8p+Ya9K57CLiniM28JwP3k3kahh8vX74nOdD6IDr+Bl84rkY4nPBXfMNYhMGfihca+rPUJnnMg3vtbEqznOjQ/unWFvJJJXuozHCk+Zzhk/sFLeRD5TOZ84hmlVaQ/mdLvq9cxV0RIYUr8DLyNfsuV6hHJ5N0g5doYQrk2hliujUHK9aTfcpV+ZVkF1yXtLZt3z2LZmMuhnpVul/I37WWgLzuLKtc=
*/