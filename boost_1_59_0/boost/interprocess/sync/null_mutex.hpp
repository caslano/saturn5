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
   null_mutex() BOOST_NOEXCEPT {}

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
   template<class TimePoint>
   bool timed_lock(const TimePoint &)
   {  return true;   }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class TimePoint>
   bool try_lock_until(const TimePoint &)
   {  return true;  }

   //!Same as `timed_lock`, but this function is modeled after the
   //!standard library interface.
   template<class Duration> 
   bool try_lock_for(const Duration &)
   {  return true; }

   //!Simulates a mutex unlock() operation.
   //!Empty function.
   void unlock(){}

   //!Simulates a mutex lock_sharable() operation.
   //!Empty function.
   void lock_sharable(){}

   //!Same as `lock_sharable` but with a std-compatible interface
   //! 
   void lock_shared()
   {  this->lock_sharable();  }

   //!Simulates a mutex try_lock_sharable() operation.
   //!Equivalent to "return true;"
   bool try_lock_sharable()
   {  return true;   }

   //!Same as `try_lock_sharable` but with a std-compatible interface
   //! 
   bool try_lock_shared()
   {  return this->try_lock_sharable();  }

   //!Simulates a mutex timed_lock_sharable() operation.
   //!Equivalent to "return true;"
   template<class TimePoint>
   bool timed_lock_sharable(const TimePoint &)
   {  return true;   }

   //!Simulates a mutex unlock_sharable() operation.
   //!Empty function.
   void unlock_sharable(){}

   //!Same as `unlock_sharable` but with a std-compatible interface
   //! 
   void unlock_shared()
   {  this->unlock_sharable();  }

   //!Simulates a mutex lock_upgradable() operation.
   //!Empty function.
   void lock_upgradable(){}

   //!Simulates a mutex try_lock_upgradable() operation.
   //!Equivalent to "return true;"
   bool try_lock_upgradable()
   {  return true;   }

   //!Simulates a mutex timed_lock_upgradable() operation.
   //!Equivalent to "return true;"
   template<class TimePoint>
   bool timed_lock_upgradable(const TimePoint &)
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
   template<class TimePoint>
   bool timed_unlock_upgradable_and_lock(const TimePoint &)
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