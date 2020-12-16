//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// Parts of the pthread code come from Boost Threads code:
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2001-2003
// William E. Kempf
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  William E. Kempf makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP

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
#include <boost/interprocess/exceptions.hpp>
#ifndef BOOST_INTERPROCESS_POSIX_TIMEOUTS
#  include <boost/interprocess/detail/os_thread_functions.hpp>
#  include <boost/interprocess/sync/detail/common_algorithms.hpp>
#endif
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class posix_recursive_mutex
{
   posix_recursive_mutex(const posix_recursive_mutex &);
   posix_recursive_mutex &operator=(const posix_recursive_mutex &);
   public:

   posix_recursive_mutex();
   ~posix_recursive_mutex();

   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();

   private:
   pthread_mutex_t   m_mut;
};

inline posix_recursive_mutex::posix_recursive_mutex()
{
   mutexattr_wrapper mut_attr(true);
   mutex_initializer mut(m_mut, mut_attr);
   mut.release();
}

inline posix_recursive_mutex::~posix_recursive_mutex()
{
   int res = pthread_mutex_destroy(&m_mut);
   BOOST_ASSERT(res == 0);(void)res;
}

inline void posix_recursive_mutex::lock()
{
   if (pthread_mutex_lock(&m_mut) != 0)
      throw lock_exception();
}

inline bool posix_recursive_mutex::try_lock()
{
   int res = pthread_mutex_trylock(&m_mut);
   if (!(res == 0 || res == EBUSY))
      throw lock_exception();
   return res == 0;
}

inline bool posix_recursive_mutex::timed_lock(const boost::posix_time::ptime &abs_time)
{
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   //Posix does not support infinity absolute time so handle it here
   if(abs_time == boost::posix_time::pos_infin){
      this->lock();
      return true;
   }

   timespec ts = ptime_to_timespec(abs_time);
   int res = pthread_mutex_timedlock(&m_mut, &ts);
   if (res != 0 && res != ETIMEDOUT)
      throw lock_exception();
   return res == 0;

   #else //BOOST_INTERPROCESS_POSIX_TIMEOUTS

   return ipcdetail::try_based_timed_lock(*this, abs_time);

   #endif   //BOOST_INTERPROCESS_POSIX_TIMEOUTS
}

inline void posix_recursive_mutex::unlock()
{
   int res = 0;
   res = pthread_mutex_unlock(&m_mut);
   BOOST_ASSERT(res == 0); (void)res;
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_POSIX_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
iaSa21xG2T1vrD2+X8O9lmbE16bieCyGIMukzuFq4wx/OB4yzsr4SjnWZ1qLd4kwmPGN9o2vT1yPKuJ6nlhHFTCudT/j38z/hfZnfpkEyYDPpMqc572rTVv4Ufe6HH6r8/84e3h/gWx2wPBShRZUXiA/5Jhk4PqMZOten8n8YNXnpq7PNo63x/dbocM0cHxRQAeX93umBf+991Sljbo+g2zd67MVccHVZwiDsj7bOMGeXu1FH6269JIVWlDpRn5xfTYurub6LDet7vUZwmKrz/DMgPXZjCJ7/D8TemgDxp8qtKDiPTqt7vUZ/Fa2zSddYw/vTtFnCxxeHkUIrgzy1CKPe9LqXqf9I4g6zVhzEjPRHuc1CES5GWehokGWs68lVB/H8tMoZ+E3h9tvzYIijOsgu8Q3jPwuggvnklq8iyWn8S5eS6j5XRjxnDDV60P7UPF94RngqTg836ubenq7orqtByX3HNcXvWVEmTKuUpb8fpz6CpSsFDLjfJcXSSY2NJXnAZaTOSa0I9ZGLEGM3oLP+7Xmzm6uW3RjTc3uKjprQFFGy2eS/i+XRinUhMeLw34kXfjOCPidjBH1C7AHd7Te0WHo45d7f6X+uDWwf5P8DA31Xy8RL9Y90L0NIenaQ86DzncojPFmGFuQH1vgxzGSey9EhmuqOf92GYUrRYuAjTHGXkx2l7rGInSPOgZouut8U49O5AFx733sMX7LKcI8TZPrVY107EIyOSEO6OHtiBHvt7VB2sP6LY6xrpWmLrinRBgpLlmmjgyv36+HkL/ecMJjOU/UmO7fHbJe7+GYC7/I3gzTCmggu9Wpu57QhX9rrf7JtDvXuvbjU4pnNjThLceKkjhHos87Ho953Xu0w8jVFvftyD2n3W5y3xTpsELbpvV2RBt6Wn/is6443OVkbmSO8z/xM53Nw+coyHAm4jn15Xk82LhXaubXDRY5hf44M5856Fkxzg5ab+xx2aPdrffV9zjSzDnR2IPifiL5udHip1x3xvqOWf9HdXO3nehZEx1nYw21LW5wl0Zzb/juLHMujeh594Q85CzS7PmVw0Dj+nLtm0x/dEOKis15u/0/kjtnunbSEWt7dy6d8yfnozzybxv8o7UwKMk2ejCnRfN1SbR3WI7p8X5WljsBuWawc+uFXjVwb7gjIgKt4WQ3KVPwPdQnvSHltn3GLNN7Cu+TnZ0RisnmqBGhUC4X6evPBMhEiTDWnzfeMrZFMtNhTta8e0lnxvpeT8R4Lzfctof8WUzxvOg4r/lh3K/HFH7cUz35d+10mIh5bLwTnseueZ0zynXexyrndUT5nWAtv/msBw/Nb5dpSUidLmiPLqUzHKfnWL4eunc+7lV473Ww3PPTg4J877/uUOqHpnwzjeo7yku09/VHkZdh1w3+C7P+o9f8PO+NPdfP/IGfeaefud1Pvv4tJLO8/6A0+7RPL/Z+HJhjlHtNCpGOFd52xfQc1WlpvM+kIPBeGnavW+TGqMde/doVMXHB7zEp8D33is1jfOKXMU0dv7Ucvw51jN/aIOO39l8Uv0Mwb3FgPMYJP/XHrvi766z5x59PXfVpasYjl3THWFeosD/704KoSVdfOveriPme9Mzcx7E2MUzYP3XfuEGrXAe+fOOJFqceXLrgCaw3JfsTO9aFP3Dj7CV9Pz+SXzSyeSXaXmTf5/KCpG+HHcqK8CRX3tT+6JtY+19P2K/8dnizB0Yvj7w5arOeeOTpVzXtK7ewf3b4dcP2h97+1I3L4io3//nODehDnCXsu/6a0XLIkVm3PNd3RMP9YbfdhL3n4cLe8URRavqNRzonHU2qn/DymC9Qiw0R9gdC7vqu3YQHEx742f0=
*/