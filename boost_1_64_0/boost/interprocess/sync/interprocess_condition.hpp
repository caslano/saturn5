//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONDITION_HPP
#define BOOST_INTERPROCESS_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/limits.hpp>
#include <boost/assert.hpp>

#if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined(BOOST_INTERPROCESS_POSIX_PROCESS_SHARED)
   #include <boost/interprocess/sync/posix/condition.hpp>
   #define BOOST_INTERPROCESS_USE_POSIX
//Experimental...
#elif !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION) && defined (BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/sync/windows/condition.hpp>
   #define BOOST_INTERPROCESS_USE_WINDOWS
#elif !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   #include <boost/interprocess/sync/spin/condition.hpp>
   #define BOOST_INTERPROCESS_USE_GENERIC_EMULATION
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition class

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

class named_condition;

//!This class is a condition variable that can be placed in shared memory or
//!memory mapped files.
//!Destroys the object of type std::condition_variable_any
//!
//!Unlike std::condition_variable in C++11, it is NOT safe to invoke the destructor if all
//!threads have been only notified. It is required that they have exited their respective wait
//!functions.
class interprocess_condition
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_condition(const interprocess_condition &);
   interprocess_condition &operator=(const interprocess_condition &);
   friend class named_condition;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs a interprocess_condition. On error throws interprocess_exception.
   interprocess_condition()
   {}

   //!Destroys *this
   //!liberating system resources.
   ~interprocess_condition()
   {}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one()
   {  m_condition.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_condition.notify_all();  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock);
   }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      m_condition.wait(internal_lock, pred);
   }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time);
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      ipcdetail::internal_mutex_lock<L> internal_lock(lock);
      return m_condition.timed_wait(internal_lock, abs_time, pred);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   private:
   #if defined (BOOST_INTERPROCESS_USE_GENERIC_EMULATION)
      #undef BOOST_INTERPROCESS_USE_GENERIC_EMULATION
      ipcdetail::spin_condition m_condition;
   #elif defined(BOOST_INTERPROCESS_USE_POSIX)
      #undef BOOST_INTERPROCESS_USE_POSIX
      ipcdetail::posix_condition m_condition;
   #elif defined(BOOST_INTERPROCESS_USE_WINDOWS)
      #undef BOOST_INTERPROCESS_USE_WINDOWS
      ipcdetail::windows_condition m_condition;
   #else
      #error "Unknown platform for interprocess_mutex"
   #endif
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_HPP

/* interprocess_condition.hpp
7wAXAf8FvILt7c1keymLgf2AVwGHAcuBE4GlwLnAJcDFwKVsp60M6GE6vd0xf6LIzpGZPw8b6Lw26Wps0tXZpGu0SddsoCsJYieoxSbdSZt0rTbosh08d+W5+HHNrF+5gvX1qoBpwGrWp14DzAbuYP3JG4BFwLXAy4HrgIvZfzX7b2e927tZ7/Z+tu+3HbiR9SLvAO5l+36vs57we6wf/DGwBhjh8OlJJwFFugOB24AjgDuA2cBvAfOBd7N9ni3ACuA9wOvYXmAl2wn8MnA90Au8DXgr8EbgNmAt8FHgduB+jj8yCvyZKHXcIHsM/jqRZ2eXySCfeyEsh/xZlEPOePGzJ4ts1xaPHXlkaX8nLJf8aZFLPoBx6QSc5nBqQ+AWwN0EVw93FO4MXEaEU8uFWwG3Be4w3Gm4DKdTy4erhquFOwj3FlxspFML/8K/8C/8C//Cv/Av/Av/Pn2/8yf/Xzquq/T/hyZpun2cU7wOUQrn4HWMN8RZ3jtZ1q6qeOr8glHFs6aOm79g3qyCme3YH6Q4eM9ufKKgRyEMdkbepudXapPZFohyf5jj4P09ltGS8mbaLvH885CGi2C5K2k7Te6rqmwnhd6TEXlOpTybbQp5eWp+I/NsHdwiFKhkl//MhI7zrGSX/T1VojWdn1AF2Q9pF6Gcnq/RMvB3GpwHTrW3KuNhW1ht6unr9LyQLKHNhmNbdcTjYUk+HA4ckRSa52Jf7M5dndsXo3MaRFk/JeecdtX5CvOmiPvT3Ddf/v2LbrnmifqNTeNezfzwk9/b+qTPJ+2qcyz+V/e2fOdJ8ljHY3GzZj5Psi+fw5cF7AHsz/sRA4BTgAOB0/ncuVzgBbw/MZjt/g8BLubnV/G5DyXsF+nX+McB4I2cvkhnA6d/Iac/EhgHzAZmAkcD+wGnAgcAx/L69RTOTw5wJj/PB17M+yLjgV8GTgCu4efXA78AXMf+LaiPorPh8yfC676fvTXfrlrvDZ8/8elZ5/VGYk03vC4b/oV/4d/5/v6/tnzVqi7Q/89k/f/8HKEDXbggP29ewdQv5vnV/rX+/HwzPc/LnVU0dd6CK0wkRHNS6CcTzcy8grx5U+cUE83SCiIBDZ8fUDe1LY353ICLDGsRbynODXhLyCxvp+9qU2ZYJJ1keN9MCqjbiLAd101HvKSvaLLpH+DMAM2aR5QztI6+Xyf9QI5FJ11Ps1lxVsDbQsdVkSZUGdqth+7nf5nijICl4twGXzrGSjSdDXBXsDMbOsF/xGvh//EAZwN4rHls15kAB6Za+K/zJVdxJsAfhI18a5odPgvAX74JXLAjcLGMNwv9JGtawjAi8f+XzP9hLPNeT7SHtXEYIWbCXQG3HO5muLtgTeF+LUqtu8R1JeNcol3AcusH6NkBbRDiGA83C+5KuJVwt2iJivUpGZ+Uh19dXrVmhbikeJOBe4jmeW008pQLdxlcBdw6uM3gTCb4KFgyEpnIhhsFpwldRbjRSVpIW/sJmstXhztYdhLrT0N81wPnFIwapfG9NHkvW+N1qkj93kTy/2273z+B/Cd1/3jyv6b7L9bb8C/NNjDZv8TcprnOe2pSx/svos53WOu8bI2pztX1uMPc58YkhW6DbfJrav83xVjHhd4YF5oV+eNhIWQem3d0fFyQeZT68Sd4oZEqlM+9/LtYx1bkERZ/s4srqyvKVxeUrvTp+HBe8ZI16Gq8RWEvVOWf43VQ2Kt7kp5f5bIyhOV23UrPe6jXtHfIfvFeOoVlbSMZ/t9Ek6Rar0X4kHZYTWcpEL+obHJdVeQ5lfOcxuuqIi+pMi+mcxbO8vkDczSJ/wB91gMB+EuxmNqBztchFCZXxVeKz2zL2FM=
*/