//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_CONDITION_HPP
#define BOOST_INTERPROCESS_POSIX_CONDITION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <pthread.h>
#include <errno.h>
#include <boost/interprocess/sync/posix/pthread_helpers.hpp>
#include <boost/interprocess/sync/posix/ptime_to_timespec.hpp>
#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/sync/posix/mutex.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_condition
{
   //Non-copyable
   posix_condition(const posix_condition &);
   posix_condition &operator=(const posix_condition &);

   public:
   //!Constructs a posix_condition. On error throws interprocess_exception.
   posix_condition();

   //!Destroys *this
   //!liberating system resources.
   ~posix_condition();

   //!If there is a thread waiting on *this, change that
   //!thread's state to ready. Otherwise there is no effect.
   void notify_one();

   //!Change the state of all threads waiting on *this to ready.
   //!If there are no waiting threads, notify_all() has no effect.
   void notify_all();

   //!Releases the lock on the posix_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), and then reacquires the lock.
   template <typename L>
   void wait(L& lock)
   {
      if (!lock)
         throw lock_exception();
      this->do_wait(*lock.mutex());
   }

   //!The same as:
   //!while (!pred()) wait(lock)
   template <typename L, typename Pr>
   void wait(L& lock, Pr pred)
   {
      if (!lock)
         throw lock_exception();

      while (!pred())
         this->do_wait(*lock.mutex());
   }

   //!Releases the lock on the posix_mutex object associated with lock, blocks
   //!the current thread of execution until readied by a call to
   //!this->notify_one() or this->notify_all(), or until time abs_time is reached,
   //!and then reacquires the lock.
   //!Returns: false if time abs_time is reached, otherwise true.
   template <typename L>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock);
         return true;
      }
      return this->do_timed_wait(abs_time, *lock.mutex());
   }

   //!The same as:   while (!pred()) {
   //!                  if (!timed_wait(lock, abs_time)) return pred();
   //!               } return true;
   template <typename L, typename Pr>
   bool timed_wait(L& lock, const boost::posix_time::ptime &abs_time, Pr pred)
   {
      if (!lock)
         throw lock_exception();
      //Posix does not support infinity absolute time so handle it here
      if(abs_time == boost::posix_time::pos_infin){
         this->wait(lock, pred);
         return true;
      }
      while (!pred()){
         if (!this->do_timed_wait(abs_time, *lock.mutex()))
            return pred();
      }
      return true;
   }


   void do_wait(posix_mutex &mut);

   bool do_timed_wait(const boost::posix_time::ptime &abs_time, posix_mutex &mut);

   private:
   pthread_cond_t   m_condition;
};

inline posix_condition::posix_condition()
{
   int res;
   pthread_condattr_t cond_attr;
   res = pthread_condattr_init(&cond_attr);
   if(res != 0){
      throw interprocess_exception("pthread_condattr_init failed");
   }
   res = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
   if(res != 0){
      pthread_condattr_destroy(&cond_attr);
      throw interprocess_exception(res);
   }
   res = pthread_cond_init(&m_condition, &cond_attr);
   pthread_condattr_destroy(&cond_attr);
   if(res != 0){
      throw interprocess_exception(res);
   }
}

inline posix_condition::~posix_condition()
{
    int res = 0;
    res = pthread_cond_destroy(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::notify_one()
{
    int res = 0;
    res = pthread_cond_signal(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::notify_all()
{
    int res = 0;
    res = pthread_cond_broadcast(&m_condition);
    BOOST_ASSERT(res == 0); (void)res;
}

inline void posix_condition::do_wait(posix_mutex &mut)
{
   pthread_mutex_t* pmutex = &mut.m_mut;
   int res = 0;
   res = pthread_cond_wait(&m_condition, pmutex);
   BOOST_ASSERT(res == 0); (void)res;
}

inline bool posix_condition::do_timed_wait
   (const boost::posix_time::ptime &abs_time, posix_mutex &mut)
{
   timespec ts = ptime_to_timespec(abs_time);
   pthread_mutex_t* pmutex = &mut.m_mut;
   int res = 0;
   res = pthread_cond_timedwait(&m_condition, pmutex, &ts);
   BOOST_ASSERT(res == 0 || res == ETIMEDOUT);

   return res != ETIMEDOUT;
}

}  //namespace ipcdetail
}  //namespace interprocess
}  //namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_CONDITION_HPP

/* condition.hpp
a9eHPLHuTD+yrv3I/1QfMnn9f38/8o/SK1gXnYJ16Vee6VOeXp9yC8qmQ7gajoLOQFyjR53pD575O/NXl79/a/+fuv+n1/8X/frPqV/PZ6dy3/Uu1o1xJ65N4jzkNGMPuH9fKfi1muQH/ouVfStEomisVR/S9yRzq7IfZXX/eCyfCz+paKpVf06ndCFTX/Y7pTuzTyrXm2P7rUUHxlGSu5bN6NGRXw4tFf22MDEfJvYasz6LL2It5iDWmSvXFLJ9uOzncXr4nYko4+l7DrpTvR+2MuP09sNWZtR9b2Gg/bBHner9sFUZp7cftioj+D1nVRl133NWm/2wT7rU+2G1zNPbD6tl/vH7YeND1PthYzL/Nfth8VO51zIl8/T2WqZkBr/XMiXzX7vX0jyfOYrXvDuRzuCV4LtJsE831rzXvSyFHwHXvVN4W3h1paZr9+iKNID7ms9sXkkyfZwf6yGY607X05wRah2Y6b7lusblmFV30HktIYNaZbBFd9ARCmMbcuehlGLNbuzOBb5Mfufo2TgVLFXYwfQ92dV3JmOlVpneBuvsoGfN8SjO9Qknv/CZk1+sfstMkxfI3TpHJk5IMnRurKMwhOhjEa47tc6YK3eZ50d/QPKtnYF0tfVu4aurbYEw81r/ApIvKCyFgyROg7Pp/kt6N8T5cy0H5+ndT2GTaXEKd1bb9ydyWAdTGvbCuTKR5tnUWymMmU6V/rcO5Ge0qctwHcmmOcuQK97UL9HrOaNsYW/Ce2yeIPNAfajWDhoez8eZOWkIbxalb0dv+sq6ivPL0+SmqX4jvupK1rNItTnZj8UZ0t116CilM33fpbCc67zOMdm2N8II71Fy97Z2DlJlPnx7He/IcE/3YNMO0jJMUwtLoYaPwsRpUJ/S7K9weZVWijQ3zqH+lJ7f3Blov8VPdP9uvanen/e+GfmunjMCceyov6lHm/mWkoL8/gF+v05yPZ1iT4UL5V3XSGNPhdut13OHN3brs1sE2EeUyG7GRhp7Kvq48UBZZ/nJLYrkPROuOSvckdH2/ZsstzLS2Psx5yFZdvvKbItknXuhc4b569wbBHOcQufePbhexdUb5odg/w+LbtY+uK6H3YW4dsRKPa87mKTHpIZ9GUdb1G1fhvJM6f+TMfOsIcK+ebcGz+aHnZ8ePu+2g30XfBxyZsz8f33MXOzZ6GnZszHa3LMhfw/n85l5D4b5+0PLbzrb0ug3cV9wu9/Zlpm8lvocXluWxXsuWvPZnm3ATmA22AM8FxwGtuO1tefxGZ854PVge3AB2JHP+OxkXUOZIdcyjq5m7WZVkHJapu0sLPUayiDlUoKQgz23k6g9SOnZAdcanqPuw+k4GIzhM9YaszmZ1yinsLkPrz0exGevLQSvtJy59hGvSf6UzWfpeCY4ChTuS8Cx4M285ngRrzl+APSAz/Ja49fAq8HNYB74Fa9Z3gVWgPt4LfJhXmP8OzgNdCJjzOQ1xdeBqbzWuDOvNb4AvAEcBj4IXg0+BI4HHwaLwT+B14KPgPPBChFOcC54H69NfojXJm8Cbwe3gEvBr8H7wD3s7givXY5zeu+ngOJ+S1DcPwcsBHPY3BEcB3YFx4MDwSLwSr6/1iXPnFpw9I9bE3hmPqfu8zn/yXWBZ+Z0/vg5nTNrBU9/Xke7Cucu4eqNawKuRbhW4dp+1Zn5nTN/Z/7O/J35O/N35u/M35m/P+rv3zf/P3Zs6R8w/5+K9exNGmCcN0WsZ++XewG8LZw6dVB+yfhCY/l/C5bp1MxHZkCpV6pgAu8RMPya5SvXa8LkogIWM/1a6yvTJ7+4aNJMeqD0a38i0jNVyl2I5fYTp2K5fWGxkKK1C1/FaqY=
*/