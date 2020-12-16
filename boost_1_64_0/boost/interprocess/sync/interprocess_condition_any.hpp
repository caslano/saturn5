//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CONDITION_ANY_HPP
#define BOOST_INTERPROCESS_CONDITION_ANY_HPP

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
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/detail/condition_any_algorithm.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!\file
//!Describes process-shared variables interprocess_condition_any class

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

//!This class is a condition variable that can be placed in shared memory or
//!memory mapped files.
//!
//!The interprocess_condition_any class is a generalization of interprocess_condition.
//!Whereas interprocess_condition works only on Locks with mutex_type == interprocess_mutex
//!interprocess_condition_any can operate on any user-defined lock that meets the BasicLockable
//!requirements (lock()/unlock() member functions).
//!
//!Unlike std::condition_variable_any in C++11, it is NOT safe to invoke the destructor if all
//!threads have been only notified. It is required that they have exited their respective wait
//!functions.
class interprocess_condition_any
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   interprocess_condition_any(const interprocess_condition_any &);
   interprocess_condition_any &operator=(const interprocess_condition_any &);

   class members
   {
      public:
      typedef interprocess_condition   condvar_type;
      typedef interprocess_mutex       mutex_type;

      condvar_type &get_condvar() {  return m_cond;  }
      mutex_type   &get_mutex()   {  return m_mut; }

      private:
      condvar_type   m_cond;
      mutex_type     m_mut;
   };

   ipcdetail::condition_any_wrapper<members>   m_cond;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   //!Constructs a interprocess_condition_any. On error throws interprocess_exception.
   interprocess_condition_any(){}

   //!Destroys *this
   //!liberating system resources.
   ~interprocess_condition_any(){}

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one()
   {  m_cond.notify_one();  }

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all()
   {  m_cond.notify_all();  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {  m_cond.wait(lock);  }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {  m_cond.wait(lock, pred);  }

   //!Releases the lock on the interprocess_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {  return m_cond.timed_wait(lock, abs_time);  }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {  return m_cond.timed_wait(lock, abs_time, pred);  }
};

}  //namespace interprocess
}  // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_CONDITION_ANY_HPP

/* interprocess_condition_any.hpp
/RVPuc6XgfQ8X8VXhLXHF/+YkC/oua9PfsDfd8dZ2hnzjO3wUn5M/XdFN/U76WStiTftnhNsmBp4TnCsm/Wd9L54J5nro8NzAn+/8rDx8LFMMEaUTYxNinSq9H61KmC/SgS+RGET1GOXof7H0p5RpdqWdhva/MRg50ebaU/QQIaMGvr6Xno+RBP69cfB21PxKDMeOPtFD3NFx/h07/mZGxGOwzNXN83lxLXkbftsBav6JcqMe5Umm9D5dI/KZuqTR1nvPVeT+IE4D0dVNyH65FkKc4mqTig+s34jdQG9T56h5zmKOjKHdUYGr6PW0P13trH/uutk/42sk+/qgP0XLpXyrrJnb+7TWg/Wl+B+PQHuHXHeCqXjlR9OZGEbPOV2BZ7qOnYLiXYM3iAOFV85Loch7BL9nI6r6dkAK085nHpeJfvYcqJJ13UeN5LfyXukvrnTSFv7dT5eIn9yHkN+6zymrod1nvBROu6beMaTBDPPVPxBuI7PETi/lL/RnD+3Wz1Ot9aa89ee7wZPkO+2tW7rGP0h+NHchh/t/GZA+uZ0tiZazsWiPyfr9HOxjN+IxPePA5+FhXD2z8I6WWf/LKyTdR0/C+vjDpyF5edPU5KVP07xZ6fOHzlWMn8cvQLyB+Hs80fbaZ8/2s6O88fRq/38meSfOydb+RONP1lq/uhnSkUG4VFWO3iU1Q4eZXWCR5Ed4JG/DZ1LsfIoDn9yJI/0/uznT0wQ/uS0gz857eBPTif4E9MJ/pxItZ5PFo/4SvxyRGWmMSjkul3JTvtnkpXs7PiZZMhDkDPJZPkOplnL1x3l8+rlM/WRkN+/3naUz9uJ8iEPQconx4C6ntby9eiF++ryzddsrP3VtaOMdZ0o413J9urQm24tYyLK2CzLKPuwjflJczvK19yJ8p0I2EbPr86/Wnf9k9f530hyURc+uudD7/4/fnxZy9UPHd1zy+OfvFxUV8k/qeWrwnJRT9rQ+WdT/vS9fZz77li+Xid18nmfR60b39eoG8900Qq6Pga6bKZLCBFfkUw3uI5/kHRHGei8Mt2A8bXA1THdEabrCXeY6SaDTuBUts06nWWyZgAnAhezzFgJMId12S/l+3P5/jxgEfAqvr+U75cBFwAr+f4avn8966qv5/t38P1N7N8KLAbez/drgdOAdexnW0W8do3yULnMtoou5nKNB6YBJxl1wHcErocLDTa1TzLdKKIz29Ru5vifZxm3F4DxwCNAF/BFtn17mG0gv8Qybz9gW9gvA7MFPae3yL8mCZzD6cXytcY2qwVu4fjvAbqB97Js3X0sW7eP6/Ex4ED267rqtYHb1XBju9LXOgPzp0Twn+nGMp20vS1tzH4P2INtyyYDDzJfmtgm8FOc76e53T0DHCPoOJ0c/1oPMJfTiTKsMa7mdKo43s3M77vYpm0Nx1PkXwsBTuR4YgzrYWUss3gtMAl4HfNxJdvkruR8VQAnsF8/o6AucHtKM9C1BuE/ULZPfa0qeHwnma53qHFsZ2C6C3U6OEkXdHzKkXRB81fCdGkh8ueVdEHzVyfpguavWdIp85fBZwZcEuskWdHFQC9cfayzS23Uhs8N6Lj8aEdkR4/EOrtEfvR/+dyAE7FOW7KkXX12QFietHPypK2oN3ecU8uGK4KrhtsCdwDuGNwZuJRuGM/gKuA2wTXAHYM7B5ce79QmwC2A88DVwDXCtcCdhnO5nNoIuDmusMxq+Bf+hX/hX/gX/oV/4V9X/c6b/H/52urla4QCQOfk//12/RqmkHz/ogV5Bbl5ucWX5l1RvHD+1Jl5unC+ppF8/niDXb9NCvn8ZOyftN5P+yeKyKRdv+6B7Q8hfMflPLor7Mc=
*/