//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NULL_MUTEX_HPP
#define BOOST_INTERPROCESS_NULL_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>


//!\file
//!Describes null_mutex classes

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

//!Implements a mutex that simulates a mutex without doing any operation and
//!simulates a successful operation.
class null_mutex
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   null_mutex(const null_mutex&);
   null_mutex &operator= (const null_mutex&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Constructor.
   //!Empty.
   null_mutex(){}

   //!Destructor.
   //!Empty.
   ~null_mutex(){}

   //!Simulates a mutex lock() operation. Empty function.
   void lock(){}

   //!Simulates a mutex try_lock() operation.
   //!Equivalent to "return true;"
   bool try_lock()
   {  return true;   }

   //!Simulates a mutex timed_lock() operation.
   //!Equivalent to "return true;"
   bool timed_lock(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock() operation.
   //!Empty function.
   void unlock(){}

   //!Simulates a mutex lock_sharable() operation.
   //!Empty function.
   void lock_sharable(){}

   //!Simulates a mutex try_lock_sharable() operation.
   //!Equivalent to "return true;"
   bool try_lock_sharable()
   {  return true;   }

   //!Simulates a mutex timed_lock_sharable() operation.
   //!Equivalent to "return true;"
   bool timed_lock_sharable(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock_sharable() operation.
   //!Empty function.
   void unlock_sharable(){}

   //!Simulates a mutex lock_upgradable() operation.
   //!Empty function.
   void lock_upgradable(){}

   //!Simulates a mutex try_lock_upgradable() operation.
   //!Equivalent to "return true;"
   bool try_lock_upgradable()
   {  return true;   }

   //!Simulates a mutex timed_lock_upgradable() operation.
   //!Equivalent to "return true;"
   bool timed_lock_upgradable(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates a mutex unlock_upgradable() operation.
   //!Empty function.
   void unlock_upgradable(){}

   //!Simulates unlock_and_lock_upgradable().
   //!Empty function.
   void unlock_and_lock_upgradable(){}

   //!Simulates unlock_and_lock_sharable().
   //!Empty function.
   void unlock_and_lock_sharable(){}

   //!Simulates unlock_upgradable_and_lock_sharable().
   //!Empty function.
   void unlock_upgradable_and_lock_sharable(){}

   //Promotions

   //!Simulates unlock_upgradable_and_lock().
   //!Empty function.
   void unlock_upgradable_and_lock(){}

   //!Simulates try_unlock_upgradable_and_lock().
   //!Equivalent to "return true;"
   bool try_unlock_upgradable_and_lock()
   {  return true;   }

   //!Simulates timed_unlock_upgradable_and_lock().
   //!Equivalent to "return true;"
   bool timed_unlock_upgradable_and_lock(const boost::posix_time::ptime &)
   {  return true;   }

   //!Simulates try_unlock_sharable_and_lock().
   //!Equivalent to "return true;"
   bool try_unlock_sharable_and_lock()
   {  return true;   }

   //!Simulates try_unlock_sharable_and_lock_upgradable().
   //!Equivalent to "return true;"
   bool try_unlock_sharable_and_lock_upgradable()
   {  return true;   }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_NULL_MUTEX_HPP

/* null_mutex.hpp
HJKrQLc8ESmQroREK9AxYzQKVGNIugKdMkaiQDWGBCzQKWMUClRjSsYCpTJHoEA3psQsUCpz9Ml+6BZ0LJRsxav9QvMqDa4Lneb3/sbv9wfdIN+I7SVn6R4ftY5ar45eHf/SOu60o85YXvtl7nWtaExVt9X6vvrvdq4bk++Lb75/6x0ff98u8HunvayWSxuiY5WKtWhgclHl+cGy1EPHHtMqlqVyqSKm00kVDnXzr4E5tsmUmK5mFO6cn9Noq1i+lcV0M7HqgjN6sdpEz543pxLmM4f2FJzNyxYIm8vp1fGaycuaJMzjDBUzzKGIiGrh63JqpLLwdTlKFc5zOb3TZc3mqM6VNp/Tu1nmjJazLqfYPcLX5V1FhM3lctfl3Y5JmMflrcuh31JJWZUTfqMkZU0OK1LCLE7qcJmzONyxUmdxUhfLm8XyVuJYD6eUdXhTDUHzt/w1eLNTwuduOevvzq+lpXgrEn6FLMVXUer6m9bhMq07QetvWhfLm8XyPBSx+5dS/BMlrr/JnS1/9grwTMR3r7SZG53lQ97qF9Oe0oc3pl5Ruku+YyNbI1pzMTM9Kq2S9IeP1HRF0m/ISNlKXuHTVRE1RSN7LwwF6ToIvWnUeNZJiaiUvpZGSCbtdhG7nkf0XIFbpTy6JKY7
*/