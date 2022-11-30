//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_LOCKS_HPP
#define BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

template<class Lock>
class internal_mutex_lock
{
   typedef void (internal_mutex_lock::*unspecified_bool_type)();
   public:

   typedef typename Lock::mutex_type::internal_mutex_type  mutex_type;


   BOOST_INTERPROCESS_FORCEINLINE internal_mutex_lock(Lock &l)
      : l_(l)
   {}

   BOOST_INTERPROCESS_FORCEINLINE mutex_type* mutex() const
   {  return l_ ? &l_.mutex()->internal_mutex() : 0;  }

   BOOST_INTERPROCESS_FORCEINLINE void lock()    { l_.lock(); }

   BOOST_INTERPROCESS_FORCEINLINE void unlock()  { l_.unlock(); }

   BOOST_INTERPROCESS_FORCEINLINE operator unspecified_bool_type() const
   {  return l_ ? &internal_mutex_lock::lock : 0;  }

   private:
   Lock &l_;
};

template <class Lock>
class lock_inverter
{
   Lock &l_;
   public:
   BOOST_INTERPROCESS_FORCEINLINE lock_inverter(Lock &l)
      :  l_(l)
   {}

   BOOST_INTERPROCESS_FORCEINLINE void lock()    {   l_.unlock();   }

   BOOST_INTERPROCESS_FORCEINLINE void unlock()  {   l_.lock();     }
};

template <class Lock>
class lock_to_sharable
{
   Lock &l_;

   public:
   BOOST_INTERPROCESS_FORCEINLINE explicit lock_to_sharable(Lock &l)
      :  l_(l)
   {}

   BOOST_INTERPROCESS_FORCEINLINE void lock()    {  l_.lock_sharable();     }

   BOOST_INTERPROCESS_FORCEINLINE bool try_lock(){  return l_.try_lock_sharable(); }

   BOOST_INTERPROCESS_FORCEINLINE void unlock()  {  l_.unlock_sharable();   }
};

template <class Lock>
class lock_to_wait
{
   Lock &l_;

   public:
   BOOST_INTERPROCESS_FORCEINLINE explicit lock_to_wait(Lock &l)
      :  l_(l)
   {}
   BOOST_INTERPROCESS_FORCEINLINE void lock()     {  l_.wait();     }

   BOOST_INTERPROCESS_FORCEINLINE bool try_lock() {  return l_.try_wait(); }

   template<class TimePoint>
   BOOST_INTERPROCESS_FORCEINLINE bool timed_lock(const TimePoint &abs_time)
      {  return l_.timed_wait(abs_time);   }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

/* locks.hpp
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
*/