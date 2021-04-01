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
jH90TCO973rGXiuSkUBaTinX9kq+42uqOH+mAgj4pQuSCdEIkVCRHzCGiB5alXcgJz2Q9aR4GxHBCIdDJanZfmu+2TM6rXzJxceAATadD4xPKDC1X2c9GF6S9B9PlBan4tkqWAutODC+lZJTfx1/xGr2M+MoBOFbdB8Sz0rSwPbl5UKGK5WrqMUeES1eimzrgB5sgq60wunNPlK0nCpkp+mMgPHSrXFtEY+Q8dIrca5RKv33h5eoh6vxVnL7JvffJF7H5MKLEPEiAeDB74QXq2G9LzJkQR6no0Zpg6Juawbou3/5LYTpYRZdjwMn7W5f8rn6A+WPAFwc1JU5xh2Ng5pAJOY5j4/hFX7jMGeIjMlF0qtcmEe+pBibey6yo2dFsg7tvTvgcQlwNTFI5W/Swp+0tofDq4e0ENPrWNHqzj1psrcOccLRCC3qVmNm1GZ0Kh4NJS9WUA2yAI1G666klM00m9meSZHbTbIwshhqC1xTIl4KQ7ZhJG3aCZuR8m5umtOwTmXpHGdRRE9Xl8/UDq6ZKn/hnVkeaON1aVA4MP5PPFko9nbbgo+zOw==
*/