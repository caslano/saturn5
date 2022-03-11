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

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
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
#include <boost/interprocess/sync/posix/ptime_to_timespec.hpp>
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
   try{
      std::string sem_str;
      #ifndef BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SEMAPHORES
      add_leading_slash(semname, sem_str);
      #else
      shared_filepath(semname, sem_str);
      #endif
      return 0 == sem_unlink(sem_str.c_str());
   }
   catch(...){
      return false;
   }
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

inline bool semaphore_timed_wait(sem_t *handle, const boost::posix_time::ptime &abs_time)
{
   #ifdef BOOST_INTERPROCESS_POSIX_TIMEOUTS
   //Posix does not support infinity absolute time so handle it here
   if(abs_time == boost::posix_time::pos_infin){
      semaphore_wait(handle);
      return true;
   }

   timespec tspec = ptime_to_timespec(abs_time);
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