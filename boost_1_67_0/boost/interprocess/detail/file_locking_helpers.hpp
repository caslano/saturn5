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