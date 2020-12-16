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
O8A12pIrBzi9th4zOT1Oox8293D6HRSOB3dD/bCFVxPww5YBXvuh4uUCfqgGeO2HWoDTfqgHOO2HhpeTfkBuK5Orl/A1NOpssofj0YXbm8scuw592jIwKzGYk3jbwPENBIxvbeJDaydyyxG+jYHzeIT52dbExaDbKDhy/N7O4OQ6QKa/vcHRfEhl2MHEy3T/ZEcP5lTkdfVOHryBae5sYlW7KmYameYuBseDKdrZVePbynX9bgoTdUbY7h6sG9PbQ2Ht6qjdpBrm8u/p5bCG5Tiwl+J0+9/bi3WrZ4KM060RHH3FohPt7Ku4ekO2g/0Y409Pou39FdZqmmPUAQpvu5szdqDGWi5jBzHGBUSbB0vM5RbB2kMULloEaQ9VmGwJhB+mcJxuRENAG4drvFxiu0coDFsBYkcqTNQ26Y5SmJ7rj9aYaxdRivgxCucWwT4/VuHB+fU4xYXPr8cbPK9o6Bmcwr3z7okKN+ddfgZncLT6Jvxkhcs5l/BTDBzbM+f5VIWHz52nKT44d55ucq1iQ9zdrBTofWdnKK5GrY3zcSbj6FVaO9HzNY3TfXhuH2ebOBaIxv5zTNy/GuOynWtqPCsyag/nmTw/gz/fi1kOPFGrcHkv8HK4mJT1cSFzYnHJFYJpXCTxdgOSLiN2scS2FnM6xb9EYdJdhF+qcOVItHEZ4zQ9UHkvRyxjrQ4vPkzSnoka3IlU11hXhPOibaFPr/TxPFXC8CJ6Hz8DMzW+PRRX+zn9Bg16DubnHUwe414b4GTW6BrsugDv8o097z266/26Sl3d077Bx9F8SPZv9HGiTfsSoGdhAZ23jDf7+XZN5AC5WwJcA7o0jVe3Eof3QuG6kZ57aUy6GbW3G/gYz1V3aEztObhTY5BNKIyt75fdpTm6Kcnt7W7G14BXiayOgxg/1/Lg+n7SvSYucmOMd/d5OP3s5X4P7qqx9QE/btUrck55UHL9vVV8SwnHeciDN5u9jXplO47zsMlV6yrOIz5cxJPco36u5Gwt+89jIZwZ93E/Dy8rlXGfCOHMuE/6eaem0n0qyHnSfdrPV9sVGfeZEE7Elfyzft6tV7a2ra3ahRKOCc915oUZev4V0Gyl7L8Qwpl5fzGEl3PTS2EcRabnYSYv6r1Xc68wN5jN8MMSvX/sVR9n3uN+zceZe7Be93GiicpyvhHC4dhj0/OMN5mH7+0P+dN8y+D8ab7t48z3Er7D3AbLLwWPleGR09b4VsoqPL5W9/je1RrjMfIGja3YxnshvLZC/eh91hRGXTHsblNvlmJTiOdmEi/RePWh/o0iOV59JHG32DvK94c+ZgxejauwTyQGkMPP5j71YI2CXPN9pnG4fU/Y5xrbXOb9C41VbLKA2i81Xm04pP1KYTiJw/1B0n5NON/RJu03JmbpZ4PfmjhVMvrqO4lX6Xrke/pNuw9we4q7TaFB5fhBcQ11//NHxkq28CHZ/EliztaY9s/6N6w1iuo+zC8a53qh+LFxGG838HcX/RZDE6Y5Dv327H8bV2F10SdrrbF61W5uh/HHY26sSHPl+PRbN6uSWxBLtSLPHRMQ72t21G4nDOUga/J5EvG0TbMG91FY0LN8L/ITd+B7e5dGfpJO/DLLIj9pB36pPoo/WQd+mV661zm55PXyAPEpNE7rKpf64ZQG3iwXe5fuXl6WqLt3adJM1VGz3LJ93J+n9mqWWqZ3WWlnmaWWJc00HTW93Uv3kWbajpqlupfrJc10HTWQM05r+o6aZXuW5nLN0FHTB9VJfptRazxjy0yMQ4eHfkHamRlzXNEx9X67WTRes8cKLRgv0casGq+X+Jp+NgOr8Rp9doXJlkr4HApXrRTbyJx+vFw=
*/