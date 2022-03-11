//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP
#define BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <limits>

namespace boost {
namespace interprocess {
namespace ipcdetail {

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
// Condition variable 'any' (able to use any type of external mutex)
//
// The code is based on Howard E. Hinnant's ISO C++ N2406 paper.
// Many thanks to Howard for his support and comments.
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// Required interface for ConditionAnyMembers
// class ConditionAnyMembers
// {
//    typedef implementation_defined mutex_type;
//    typedef implementation_defined condvar_type;
//
//    condvar     &get_condvar()
//    mutex_type  &get_mutex()
// };
//
// Must be initialized as following
//
//    get_condvar()  [no threads blocked]
//    get_mutex()    [unlocked]

template<class ConditionAnyMembers>
class condition_any_algorithm
{
   private:
   condition_any_algorithm();
   ~condition_any_algorithm();
   condition_any_algorithm(const condition_any_algorithm &);
   condition_any_algorithm &operator=(const condition_any_algorithm &);

   typedef typename ConditionAnyMembers::mutex_type      mutex_type;
   typedef typename ConditionAnyMembers::condvar_type    condvar_type;

   template <class Lock>
   static void do_wait(ConditionAnyMembers &data, Lock& lock);

   template <class Lock>
   static bool do_timed_wait(ConditionAnyMembers &data, Lock& lock, const boost::posix_time::ptime &abs_time);

   public:
   template<class Lock>
   static bool wait  ( ConditionAnyMembers &data, Lock &mut
                     , bool timeout_enabled, const boost::posix_time::ptime &abs_time);
   static void signal( ConditionAnyMembers &data, bool broadcast);
};

template<class ConditionAnyMembers>
void condition_any_algorithm<ConditionAnyMembers>::signal(ConditionAnyMembers &data, bool broadcast)
{
   scoped_lock<mutex_type> internal_lock(data.get_mutex());
   if(broadcast){
      data.get_condvar().notify_all();
   }
   else{
      data.get_condvar().notify_one();
   }
}

template<class ConditionAnyMembers>
template<class Lock>
bool condition_any_algorithm<ConditionAnyMembers>::wait
   ( ConditionAnyMembers &data
   , Lock &lock
   , bool tout_enabled
   , const boost::posix_time::ptime &abs_time)
{
   if(tout_enabled){
      return condition_any_algorithm::do_timed_wait(data, lock, abs_time);
   }
   else{
      condition_any_algorithm::do_wait(data, lock);
      return true;
   }
}

template<class ConditionAnyMembers>
template <class Lock>
void condition_any_algorithm<ConditionAnyMembers>::do_wait
   (ConditionAnyMembers &data, Lock& lock)
{
   //lock internal before unlocking external to avoid race with a notifier
   scoped_lock<mutex_type> internal_lock(data.get_mutex());
   {
      lock_inverter<Lock> inverted_lock(lock);
      scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);
      {  //unlock internal first to avoid deadlock with near simultaneous waits
         scoped_lock<mutex_type>     internal_unlock;
         internal_lock.swap(internal_unlock);
         data.get_condvar().wait(internal_unlock);
      }
   }
}

template<class ConditionAnyMembers>
template <class Lock>
bool condition_any_algorithm<ConditionAnyMembers>::do_timed_wait
   (ConditionAnyMembers &data, Lock& lock, const boost::posix_time::ptime &abs_time)
{
   //lock internal before unlocking external to avoid race with a notifier
   scoped_lock<mutex_type> internal_lock(data.get_mutex());
   {
      //Unlock external lock and program for relock
      lock_inverter<Lock> inverted_lock(lock);
      scoped_lock<lock_inverter<Lock> >   external_unlock(inverted_lock);
      {  //unlock internal first to avoid deadlock with near simultaneous waits
         scoped_lock<mutex_type> internal_unlock;
         internal_lock.swap(internal_unlock);
         return data.get_condvar().timed_wait(internal_unlock, abs_time);
      }
   }
}


template<class ConditionAnyMembers>
class condition_any_wrapper
{
   //Non-copyable
   condition_any_wrapper(const condition_any_wrapper &);
   condition_any_wrapper &operator=(const condition_any_wrapper &);

   ConditionAnyMembers m_data;
   typedef ipcdetail::condition_any_algorithm<ConditionAnyMembers> algo_type;

   public:

   condition_any_wrapper(){}

   ~condition_any_wrapper(){}

   ConditionAnyMembers & get_members()
   {  return m_data; }

   const ConditionAnyMembers & get_members() const
   {  return m_data; }

   void notify_one()
   {  algo_type::signal(m_data, false);  }

   void notify_all()
   {  algo_type::signal(m_data, true);  }

   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }

   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         algo_type::wait(m_data, lock, false, boost::posix_time::ptime());
   }

   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if (!lock)
         throw lock_exception();
      return algo_type::wait(m_data, lock, true, abs_time);
   }

   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      if (!lock)
            throw lock_exception();
      while (!pred()){
         if (!algo_type::wait(m_data, lock, true, abs_time))
            return pred();
      }
      return true;
   }
};

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_CONDITION_ANY_ALGORITHM_HPP

/* condition_any_algorithm.hpp
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
*/