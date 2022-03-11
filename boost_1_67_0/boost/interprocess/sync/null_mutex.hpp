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
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
*/