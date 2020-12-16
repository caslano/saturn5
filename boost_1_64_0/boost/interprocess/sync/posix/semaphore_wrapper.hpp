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
agjXMtABvgA6wfWgC9wJhoJjXN743QTGwHwzWJ/z41pDZzj4I7/vBJGu/L4nuLzfwzVgEjiJ31sJOBCcDI4GPeB4cApYxOZiNpeCU8EbwTJwDjgdXMfuPwavBz8HZ4FfgtPASjZ/AxaD37F5NzgRPMBmEY9s1jVNZSPHw4kr3RjfD/F+D6EgjQGDlN+EW3bXn91F4hrF7upBjvqZYARYHzwLbADWA2NB8Yx4sBOYCPbh+xeLsICXklm2R5bw8xIc9vZIb5c3X/fj7+ZSsIMIG9gZxLsk/waAHjAXvBccAj4NXgG+Cw4X7vGQwWAncCT4MCjcrQXzwb+Dwr/t4FDwH2w+AA4CfxZmTt9yQ68qeB2nk0gHHu4Q5Tblk0IwHhwPni3SF2xJI+Xe+FwDdqfyxJt/SsChIp+Ak8BSUPg5FZwOjgNnslmEY4/OOkBJn6psl+/g8uFBLo8eBS8CK8AZ4ArwevA58CY2LwafB5eBfwFfBl8A1wu/OX+tAk+AL4FReMbLYAtwNdgaPAK2BY9zOp8Au4MnwQvBx8CrwWVgCbgcnAU+C84G3wIrwHXgi+B68ANwA1gJvg3GImH/DqaA74DZ4EawC7gJ7MP2w0Dh3zTwJ3ApWAU+Dv4MrgUPgh+Ch8HvQBH+OKf3fmtQxKMDKOLRFRTx6Am+C5aCH4DXglvAOeBW8B7wY/ARcBv4PPgJ+Db4GbgJ3A5+An4BVoE7RbqC34DIe9pu8E7wO/BhEP5yu4l1woFJNfSDttjk1P2LKpucul0dkxBYrrMm20vZLHe7or00hdsxpaDwpwxsCc4EhdsbuD6eDi5g863gVHAxm81w83MSa0iHmESWqyEdsm1y6nTIlXIB06GTzvpVqO0FOS57s/i7/LvmTYdNoPDzXTALfA+8DNwMDge3gVPBj8DZ4FZwLvgB+CD4GfgUhQPlF/gFuA38B/g5+CW4G/wK3AtWgr+CX4O/gd+CYQjILjAC/B5sAO4GG4F7wZbgPjAT3A92BA+AncGfwL5gFdgPRNypXv8VHA+eAEvBk+BdYCj6c3eDv8H8GCji/xoYAvu1fF+kXwUuD6fzMU7n+riWcjo/w+Xrs5x+z3G5ugLsBj4P5oIvgRPBV7j8XC3CAb4Gime8Dj4OrgRXgy+An7G/+8G/8ft8EzwC/pXSDWa232LoUmCdEtt5LHgDh7Mc/zcF54HNwZtFOlL8vPXjfLA/+CB4JfgQeAP4MHgfuBh8EbwD/ABcAn4K3gl+Dd4FxupIF35v94jngPfy+7qP39f9/L4WgEPAheJ5YAU4DrwVXCTMHK9hhs4B7u9u5/FmY26lL7fLLwajwcvBGDAXrC/kwEQ2i/S4BEwmM9dbxn581kWwncuVHez/Nzr8F3JgPXAfKMLxA49P7AczwANgK/BHsC34M9iBzV3YnAseBEeBv4DXg4fA3XxfvM/fQLeot8AW4O/CH1AX7WbQCY4EQ8F8MAosBI9AbgKbi8AI8FowEryB7Tk/8z5r5EVFfp4Lf5zgPLAZeDOYDd4C5oC3giLtF4OjwQdBD/gQOBV8GCwD7+D4LQHngHeC88G7wIfAu8Fl4L3gX8D7wJfZvQhnQ5336vK+5e1c5rm53Poz5KLA5SKdwGc5vb8AO4MrwAFsHgiuBKeBfwUXgy+CT4Ivg2vB18Ct4jsE94JvcDj+Bh4X3xmPM60D40R7QKQPuAHsBr4DXgZuBPPBd8GJ4HviueBmcCb4IbgE3AJWgB+Bz4LbwBfAT0CEhcK9RsQbfBf8HNzC9vweeQ8n3pXiPWY6vOVSK+6nt+HxiHZgDnge99dzwK5gB/ASsBd4KdiJxwu6gaPALtyP78n9swvAmeCF4I0=
*/