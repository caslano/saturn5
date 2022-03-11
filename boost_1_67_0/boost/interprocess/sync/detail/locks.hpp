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


   internal_mutex_lock(Lock &l)
      : l_(l)
   {}

   mutex_type* mutex() const
   {  return l_ ? &l_.mutex()->internal_mutex() : 0;  }

   void lock()    { l_.lock(); }

   void unlock()  { l_.unlock(); }

   operator unspecified_bool_type() const
   {  return l_ ? &internal_mutex_lock::lock : 0;  }

   private:
   Lock &l_;
};

template <class Lock>
class lock_inverter
{
   Lock &l_;
   public:
   lock_inverter(Lock &l)
      :  l_(l)
   {}
   void lock()    {   l_.unlock();   }
   void unlock()  {   l_.lock();     }
};

template <class Lock>
class lock_to_sharable
{
   Lock &l_;

   public:
   explicit lock_to_sharable(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.lock_sharable();     }
   bool try_lock(){  return l_.try_lock_sharable(); }
   void unlock()  {  l_.unlock_sharable();   }
};

template <class Lock>
class lock_to_wait
{
   Lock &l_;

   public:
   explicit lock_to_wait(Lock &l)
      :  l_(l)
   {}
   void lock()    {  l_.wait();     }
   bool try_lock(){  return l_.try_wait(); }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_LOCKS_HPP

/* locks.hpp
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
*/