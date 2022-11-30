//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_WRAPPER_HPP
#define BOOST_INTERPROCESS_POSIX_SEMAPHORE_WRAPPER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>
#include <boost/interprocess/permissions.hpp>

#include <fcntl.h>      //O_CREAT, O_*...
#include <unistd.h>     //close
#include <string>       //std::string
#include <semaphore.h>  //sem_* family, SEM_VALUE_MAX
#include <sys/stat.h>   //mode_t, S_IRWXG, S_IRWXO, S_IRWXU,
#include <boost/assert.hpp>

#ifdef SEM_FAILED
#define BOOST_INTERPROCESS_POSIX_SEM_FAILED (reinterpret_cast<sem_t*>(SEM_FAILED))
#else
#define BOOST_INTERPROCESS_POSIX_SEM_FAILED (reinterpret_cast<sem_t*>(-1))
#endif

#ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
#include <boost/interprocess/sync/posix/timepoint_to_timespec.hpp>
#else
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/sync/detail/locks.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#endif

namespace boost {
namespace interprocess {
namespace ipcdetail {

#ifdef BOOST_INTERPROCESS_POSIX_NAMED_SEMAPHORES

inline bool semaphore_open
   (sem_t *&handle, create_enum_t type, const char *origname,
    unsigned int count = 0, const permissions &perm = permissions())
{
   std::string name;
   #ifndef BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
   add_leading_slash(origname, name);
   #else
   create_shared_dir_cleaning_old_and_get_filepath(origname, name);
   #endif

   //Create new mapping
   int oflag = 0;
   switch(type){
      case DoOpen:
      {
         //No addition
         handle = ::sem_open(name.c_str(), oflag);
      }
      break;
      case DoOpenOrCreate:
      case DoCreate:
      {
         while(1){
            oflag = (O_CREAT | O_EXCL);
            handle = ::sem_open(name.c_str(), oflag, perm.get_permissions(), count);
            if(handle != BOOST_INTERPROCESS_POSIX_SEM_FAILED){
               //We can't change semaphore permissions!
               //::fchmod(handle, perm.get_permissions());
               break;
            }
            else if(errno == EEXIST && type == DoOpenOrCreate){
               oflag = 0;
               if( (handle = ::sem_open(name.c_str(), oflag)) != BOOST_INTERPROCESS_POSIX_SEM_FAILED
                   || (errno != ENOENT) ){
                  break;
               }
            }
            else{
               break;
            }
         }
      }
      break;
      default:
      {
         error_info err(other_error);
         throw interprocess_exception(err);
      }
   }

   //Check for error
   if(handle == BOOST_INTERPROCESS_POSIX_SEM_FAILED){
      throw interprocess_exception(error_info(errno));
   }

   return true;
}

inline void semaphore_close(sem_t *handle)
{
   int ret = sem_close(handle);
   if(ret != 0){
      BOOST_ASSERT(0);
   }
}

inline bool semaphore_unlink(const char *semname)
{
   BOOST_TRY{
      std::string sem_str;
      #ifndef BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
      add_leading_slash(semname, sem_str);
      #else
      shared_filepath(semname, sem_str);
      #endif
      return 0 == sem_unlink(sem_str.c_str());
   }
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

#endif   //BOOST_INTERPROCESS_POSIX_NAMED_SEMAPHORES

#ifdef BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES

inline void semaphore_init(sem_t *handle, unsigned int initialCount)
{
   int ret = sem_init(handle, 1, initialCount);
   //According to SUSV3 version 2003 edition, the return value of a successful
   //sem_init call is not defined, but -1 is returned on failure.
   //In the future, a successful call might be required to return 0.
   if(ret == -1){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

inline void semaphore_destroy(sem_t *handle)
{
   int ret = sem_destroy(handle);
   if(ret != 0){
      BOOST_ASSERT(0);
   }
}

#endif   //BOOST_INTERPROCESS_POSIX_UNNAMED_SEMAPHORES

inline void semaphore_post(sem_t *handle)
{
   int ret = sem_post(handle);
   if(ret != 0){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

inline void semaphore_wait(sem_t *handle)
{
   int ret = sem_wait(handle);
   if(ret != 0){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

inline bool semaphore_try_wait(sem_t *handle)
{
   int res = sem_trywait(handle);
   if(res == 0)
      return true;
   if(system_error_code() == EAGAIN){
      return false;
   }
   error_info err = system_error_code();
   throw interprocess_exception(err);
}

#ifndef BOOST_INTERPROCESS_POSIX_TIMEOUTS

struct semaphore_wrapper_try_wrapper
{
   explicit semaphore_wrapper_try_wrapper(sem_t *handle)
      : m_handle(handle)
   {}

   void wait()
   {  semaphore_wait(m_handle);  }

   bool try_wait()
   {  return semaphore_try_wait(m_handle);  }

   private:
   sem_t *m_handle;
};

#endif

template<class TimePoint>
inline bool semaphore_timed_wait(sem_t *handle, const TimePoint &abs_time)
{
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   //Posix does not support infinity absolute time so handle it here
   if(ipcdetail::is_pos_infinity(abs_time)){
      semaphore_wait(handle);
      return true;
   }

   timespec tspec = timepoint_to_timespec(abs_time);
   for (;;){
      int res = sem_timedwait(handle, &tspec);
      if(res == 0)
         return true;
      if (res > 0){
         //buggy glibc, copy the returned error code to errno
         errno = res;
      }
      if(system_error_code() == ETIMEDOUT){
         return false;
      }
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   return false;
   #else //#ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS

   semaphore_wrapper_try_wrapper swtw(handle);
   ipcdetail::lock_to_wait<semaphore_wrapper_try_wrapper> lw(swtw);
   return ipcdetail::try_based_timed_lock(lw, abs_time);

   #endif   //#ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //#ifndef BOOST_INTERPROCESS_POSIX_SEMAPHORE_WRAPPER_HPP

/* semaphore_wrapper.hpp
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
*/