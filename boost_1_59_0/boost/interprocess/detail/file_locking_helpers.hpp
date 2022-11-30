//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FILE_LOCKING_HELPERS_HPP
#define BOOST_INTERPROCESS_FILE_LOCKING_HELPERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstddef>
#include <boost/interprocess/detail/os_file_functions.hpp>

#include <boost/interprocess/detail/shared_dir_helpers.hpp>

#if defined(BOOST_INTERPROCESS_WINDOWS)

#include <fcntl.h>
#include <io.h>
#include <sys/locking.h>

#else //defined(BOOST_INTERPROCESS_WINDOWS)

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#endif   //defined(BOOST_INTERPROCESS_WINDOWS)

namespace boost{
namespace interprocess{
namespace ipcdetail{

#if defined(BOOST_INTERPROCESS_WINDOWS)

struct locking_file_serial_id
{
   int fd;
   unsigned long dwVolumeSerialNumber;
   unsigned long nFileIndexHigh;
   unsigned long nFileIndexLow;
   //This reference count counts the number of modules attached
   //to the shared memory and lock file. This serves to unlink
   //the locking file and shared memory when all modules are
   //done with the global memory (shared memory)
   volatile boost::uint32_t modules_attached_to_gmem_count;
};

inline bool lock_locking_file(int fd)
{
   int ret = 0;
   while(ret != 0 && errno == EDEADLK){
      ret = _locking(fd, _LK_LOCK, 1/*lock_file_contents_length()*/);
   }
   return 0 == ret;
}

inline bool try_lock_locking_file(int fd)
{
   return 0 == _locking(fd, _LK_NBLCK , 1);
}

inline int open_or_create_and_lock_file(const char *name)
{
   permissions p;
   p.set_unrestricted();
   while(1){
      file_handle_t handle = create_or_open_file(name, read_write, p);
      int fd = _open_osfhandle((intptr_t)handle, _O_TEXT);
      if(fd < 0){
         close_file(handle);
         return fd;
      }
      if(!try_lock_locking_file(fd)){
         _close(fd);
         return -1;
      }
      struct _stat s;
      if(0 == _stat(name, &s)){
         return fd;
      }
      else{
         _close(fd);
      }
   }
}

inline int try_open_and_lock_file(const char *name)
{
   file_handle_t handle = open_existing_file(name, read_write);
   int fd = _open_osfhandle((intptr_t)handle, _O_TEXT);
   if(fd < 0){
      close_file(handle);
      return fd;
   }
   if(!try_lock_locking_file(fd)){
      _close(fd);
      return -1;
   }
   return fd;
}

inline void close_lock_file(int fd)
{  _close(fd); }

inline bool is_valid_fd(int fd)
{
   struct _stat s;
   return EBADF != _fstat(fd, &s);
}

inline bool is_normal_file(int fd)
{
   if(_isatty(fd))
      return false;
   struct _stat s;
   if(0 != _fstat(fd, &s))
      return false;
   return 0 != (s.st_mode & _S_IFREG);
}

inline std::size_t get_size(int fd)
{
   struct _stat s;
   if(0 != _fstat(fd, &s))
      return 0u;
   return (std::size_t)s.st_size;
}

inline bool fill_file_serial_id(int fd, locking_file_serial_id &id)
{
   winapi::interprocess_by_handle_file_information info;
   if(!winapi::get_file_information_by_handle((void*)_get_osfhandle(fd), &info))
      return false;
   id.fd = fd;
   id.dwVolumeSerialNumber = info.dwVolumeSerialNumber;
   id.nFileIndexHigh = info.nFileIndexHigh;
   id.nFileIndexLow = info.nFileIndexLow;
   id.modules_attached_to_gmem_count = 1; //Initialize attached count
   return true;
}

inline bool compare_file_serial(int fd, const locking_file_serial_id &id)
{
   winapi::interprocess_by_handle_file_information info;
   if(!winapi::get_file_information_by_handle((void*)_get_osfhandle(fd), &info))
      return false;

   return   id.dwVolumeSerialNumber == info.dwVolumeSerialNumber  &&
            id.nFileIndexHigh       == info.nFileIndexHigh        &&
            id.nFileIndexLow        == info.nFileIndexLow;
}

#else //UNIX

struct locking_file_serial_id
{
   int fd;
   dev_t st_dev;
   ino_t st_ino;
   //This reference count counts the number of modules attached
   //to the shared memory and lock file. This serves to unlink
   //the locking file and shared memory when all modules are
   //done with the global memory (shared memory)
   volatile boost::uint32_t modules_attached_to_gmem_count;
};

inline bool lock_locking_file(int fd)
{
   int ret = 0;
   while(ret != 0 && errno != EINTR){
      struct flock lock;
      lock.l_type = F_WRLCK;
      lock.l_whence = SEEK_SET;
      lock.l_start = 0;
      lock.l_len = 1;
      ret = fcntl (fd, F_SETLKW, &lock);
   }
   return 0 == ret;
}

inline bool try_lock_locking_file(int fd)
{
   struct flock lock;
   lock.l_type = F_WRLCK;
   lock.l_whence = SEEK_SET;
   lock.l_start = 0;
   lock.l_len = 1;
   return 0 == fcntl (fd, F_SETLK, &lock);
}

inline int open_or_create_and_lock_file(const char *name)
{
   permissions p;
   p.set_unrestricted();
   while(1){
      int fd = create_or_open_file(name, read_write, p);
      if(fd < 0){
         return fd;
      }
      if(!try_lock_locking_file(fd)){
         close(fd);
         return -1;
      }
      struct stat s;
      if(0 == stat(name, &s)){
         return fd;
      }
      else{
         close(fd);
      }
   }
}

inline int try_open_and_lock_file(const char *name)
{
   int fd = open_existing_file(name, read_write);
   if(fd < 0){
      return fd;
   }
   if(!try_lock_locking_file(fd)){
      close(fd);
      return -1;
   }
   return fd;
}

inline void close_lock_file(int fd)
{  close(fd); }

inline bool is_valid_fd(int fd)
{
   struct stat s;
   return EBADF != fstat(fd, &s);
}

inline bool is_normal_file(int fd)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return false;
   return 0 != (s.st_mode & S_IFREG);
}

inline std::size_t get_size(int fd)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return 0u;
   return (std::size_t)s.st_size;
}

inline bool fill_file_serial_id(int fd, locking_file_serial_id &id)
{
   struct stat s;
   if(0 != fstat(fd, &s))
      return false;
   id.fd = fd;
   id.st_dev = s.st_dev;
   id.st_ino = s.st_ino;
   id.modules_attached_to_gmem_count = 1; //Initialize attached count
   return true;
}

inline bool compare_file_serial(int fd, const locking_file_serial_id &id)
{
   struct stat info;
   if(0 != fstat(fd, &info))
      return false;

   return   id.st_dev == info.st_dev  &&
            id.st_ino == info.st_ino;
}

#endif

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_FILE_LOCKING_HELPERS_HPP

/* file_locking_helpers.hpp
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
*/