//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP
#define BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/permissions.hpp>

#include <string>
#include <limits>
#include <climits>
#include <boost/move/detail/type_traits.hpp> //make_unsigned

#if defined (BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#     include <fcntl.h>
#     include <unistd.h>
#     include <sys/types.h>
#     include <sys/stat.h>
#     include <errno.h>
#     include <cstdio>
#     include <dirent.h>
#     if 0
#        include <sys/file.h>
#     endif
#  else
#    error Unknown platform
#  endif
#endif

#include <cstring>
#include <cstdlib>

namespace boost {
namespace interprocess {

#if defined (BOOST_INTERPROCESS_WINDOWS)

typedef void *                   file_handle_t;
typedef __int64  offset_t;
typedef struct mapping_handle_impl_t{
   void *   handle;
   bool     is_shm;
}  mapping_handle_t;

typedef enum { read_only      = winapi::generic_read
             , read_write     = winapi::generic_read | winapi::generic_write
             , copy_on_write
             , read_private
             , invalid_mode   = 0xffff
             } mode_t;

typedef enum { file_begin     = winapi::file_begin
             , file_end       = winapi::file_end
             , file_current   = winapi::file_current
             } file_pos_t;

typedef unsigned long      map_options_t;
static const map_options_t default_map_options = map_options_t(-1);

namespace ipcdetail{

inline mapping_handle_t mapping_handle_from_file_handle(file_handle_t hnd)
{
   mapping_handle_t ret;
   ret.handle = hnd;
   ret.is_shm = false;
   return ret;
}

inline mapping_handle_t mapping_handle_from_shm_handle(file_handle_t hnd)
{
   mapping_handle_t ret;
   ret.handle = hnd;
   ret.is_shm = true;
   return ret;
}

inline file_handle_t file_handle_from_mapping_handle(mapping_handle_t hnd)
{  return hnd.handle; }

inline bool create_directory(const char *path)
{  return winapi::create_directory(path); }

inline bool remove_directory(const char *path)
{  return winapi::remove_directory(path); }

inline bool get_temporary_path(char *buffer, std::size_t buf_len, std::size_t &required_len)
{
   required_len = 0;
   //std::size_t is always bigger or equal than unsigned long in Windows systems
   //In case std::size_t is bigger than unsigned long
   unsigned long buf = buf_len;
   if(buf_len != buf){   //maybe overflowed
      return false;
   }
   required_len = winapi::get_temp_path(buf_len, buffer);
   const bool ret = !(buf_len < required_len);
   if(ret && buffer[required_len-1] == '\\'){
      buffer[required_len-1] = 0;
   }
   return ret;
}

inline file_handle_t create_new_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      ( name, (unsigned int)mode, winapi::create_new, attr
      , (winapi::interprocess_security_attributes*)perm.get_permissions());
}

inline file_handle_t create_or_open_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      ( name, (unsigned int)mode, winapi::open_always, attr
      , (winapi::interprocess_security_attributes*)perm.get_permissions());
}

inline file_handle_t open_existing_file
   (const char *name, mode_t mode, bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      (name, (unsigned int)mode, winapi::open_existing, attr, 0);
}

inline bool delete_file(const char *name)
{  return winapi::unlink_file(name);   }

inline bool truncate_file (file_handle_t hnd, std::size_t size)
{
   offset_t filesize;
   if(!winapi::get_file_size(hnd, filesize))
      return false;

   typedef ::boost::move_detail::make_unsigned<offset_t>::type uoffset_t;
   const uoffset_t max_filesize = uoffset_t((std::numeric_limits<offset_t>::max)());
   const uoffset_t uoff_size = uoffset_t(size);
   //Avoid unused variable warnings in 32 bit systems
   if(uoff_size > max_filesize){
      winapi::set_last_error(winapi::error_file_too_large);
      return false;
   }

   if(offset_t(size) > filesize){
      if(!winapi::set_file_pointer_ex(hnd, filesize, 0, winapi::file_begin)){
         return false;
      }
      //We will write zeros in the end of the file
      //since set_end_of_file does not guarantee this
      for(std::size_t remaining = size - filesize, write_size = 0
         ;remaining > 0
         ;remaining -= write_size){
         const std::size_t DataSize = 512;
         static char data [DataSize];
         write_size = DataSize < remaining ? DataSize : remaining;
         unsigned long written;
         winapi::write_file(hnd, data, (unsigned long)write_size, &written, 0);
         if(written != write_size){
            return false;
         }
      }
   }
   else{
      if(!winapi::set_file_pointer_ex(hnd, size, 0, winapi::file_begin)){
         return false;
      }
      if(!winapi::set_end_of_file(hnd)){
         return false;
      }
   }
   return true;
}

inline bool get_file_size(file_handle_t hnd, offset_t &size)
{  return winapi::get_file_size(hnd, size);  }

inline bool set_file_pointer(file_handle_t hnd, offset_t off, file_pos_t pos)
{  return winapi::set_file_pointer_ex(hnd, off, 0, (unsigned long) pos); }

inline bool get_file_pointer(file_handle_t hnd, offset_t &off)
{  return winapi::set_file_pointer_ex(hnd, 0, &off, winapi::file_current); }

inline bool write_file(file_handle_t hnd, const void *data, std::size_t numdata)
{
   unsigned long written;
   return 0 != winapi::write_file(hnd, data, (unsigned long)numdata, &written, 0);
}

inline file_handle_t invalid_file()
{  return winapi::invalid_handle_value;  }

inline bool close_file(file_handle_t hnd)
{  return 0 != winapi::close_handle(hnd);   }

inline bool acquire_file_lock(file_handle_t hnd)
{
   static winapi::interprocess_overlapped overlapped;
   const unsigned long len = ((unsigned long)-1);
//   winapi::interprocess_overlapped overlapped;
//   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::lock_file_ex
      (hnd, winapi::lockfile_exclusive_lock, 0, len, len, &overlapped);
}

inline bool try_acquire_file_lock(file_handle_t hnd, bool &acquired)
{
   const unsigned long len = ((unsigned long)-1);
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   if(!winapi::lock_file_ex
      (hnd, winapi::lockfile_exclusive_lock | winapi::lockfile_fail_immediately,
       0, len, len, &overlapped)){
      return winapi::get_last_error() == winapi::error_lock_violation ?
               acquired = false, true : false;

   }
   return (acquired = true);
}

inline bool release_file_lock(file_handle_t hnd)
{
   const unsigned long len = ((unsigned long)-1);
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::unlock_file_ex(hnd, 0, len, len, &overlapped);
}

inline bool acquire_file_lock_sharable(file_handle_t hnd)
{
   const unsigned long len = ((unsigned long)-1);
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   return winapi::lock_file_ex(hnd, 0, 0, len, len, &overlapped);
}

inline bool try_acquire_file_lock_sharable(file_handle_t hnd, bool &acquired)
{
   const unsigned long len = ((unsigned long)-1);
   winapi::interprocess_overlapped overlapped;
   std::memset(&overlapped, 0, sizeof(overlapped));
   if(!winapi::lock_file_ex
      (hnd, winapi::lockfile_fail_immediately, 0, len, len, &overlapped)){
      return winapi::get_last_error() == winapi::error_lock_violation ?
               acquired = false, true : false;
   }
   return (acquired = true);
}

inline bool release_file_lock_sharable(file_handle_t hnd)
{  return release_file_lock(hnd);   }

inline bool delete_subdirectories_recursive
   (const std::string &refcstrRootDirectory, const char *dont_delete_this, unsigned int count)
{
   bool               bSubdirectory = false;       // Flag, indicating whether
                                                   // subdirectories have been found
   void *             hFile;                       // Handle to directory
   std::string        strFilePath;                 // Filepath
   std::string        strPattern;                  // Pattern
   winapi::win32_find_data  FileInformation;     // File information

   //Find all files and directories
   strPattern = refcstrRootDirectory + "\\*.*";
   hFile = winapi::find_first_file(strPattern.c_str(), &FileInformation);
   if(hFile != winapi::invalid_handle_value){
      do{
         //If it's not "." or ".." or the pointed root_level dont_delete_this erase it
         if(FileInformation.cFileName[0] != '.' &&
            !(dont_delete_this && count == 0 && std::strcmp(dont_delete_this, FileInformation.cFileName) == 0)){
            strFilePath.erase();
            strFilePath = refcstrRootDirectory + "\\" + FileInformation.cFileName;

            //If it's a directory, go recursive
            if(FileInformation.dwFileAttributes & winapi::file_attribute_directory){
               // Delete subdirectory
               if(!delete_subdirectories_recursive(strFilePath, dont_delete_this, count+1)){
                  winapi::find_close(hFile);
                  return false;
               }
            }
            //If it's a file, just delete it
            else{
               // Set file attributes
               //if(::SetFileAttributes(strFilePath.c_str(), winapi::file_attribute_normal) == 0)
               //return winapi::get_last_error();
               // Delete file
               winapi::unlink_file(strFilePath.c_str());
            }
         }
      //Go to the next file
      } while(winapi::find_next_file(hFile, &FileInformation) == 1);

      // Close handle
      winapi::find_close(hFile);

      //See if the loop has ended with an error or just because we've traversed all the files
      if(winapi::get_last_error() != winapi::error_no_more_files){
         return false;
      }
      else
      {
         //Erase empty subdirectories or original refcstrRootDirectory
         if(!bSubdirectory && count)
         {
            // Set directory attributes
            //if(::SetFileAttributes(refcstrRootDirectory.c_str(), FILE_ATTRIBUTE_NORMAL) == 0)
               //return ::GetLastError();
            // Delete directory
            if(winapi::remove_directory(refcstrRootDirectory.c_str()) == 0)
               return false;
         }
      }
   }
   return true;
}

//This function erases all the subdirectories of a directory except the one pointed by "dont_delete_this"
inline bool delete_subdirectories(const std::string &refcstrRootDirectory, const char *dont_delete_this)
{
   return delete_subdirectories_recursive(refcstrRootDirectory, dont_delete_this, 0u);
}


template<class Function>
inline bool for_each_file_in_dir(const char *dir, Function f)
{
   void *             hFile;                       // Handle to directory
   winapi::win32_find_data  FileInformation;     // File information

   //Get base directory
   std::string str(dir);
   const std::size_t base_root_dir_len = str.size();

   //Find all files and directories
   str  +=  "\\*.*";
   hFile = winapi::find_first_file(str.c_str(), &FileInformation);
   if(hFile != winapi::invalid_handle_value){
      do{   //Now loop every file
         str.erase(base_root_dir_len);
         //If it's not "." or ".." skip it
         if(FileInformation.cFileName[0] != '.'){
            str += "\\";   str += FileInformation.cFileName;
            //If it's a file, apply erase logic
            if(!(FileInformation.dwFileAttributes & winapi::file_attribute_directory)){
               f(str.c_str(), FileInformation.cFileName);
            }
         }
      //Go to the next file
      } while(winapi::find_next_file(hFile, &FileInformation) == 1);

      // Close handle and see if the loop has ended with an error
      winapi::find_close(hFile);
      if(winapi::get_last_error() != winapi::error_no_more_files){
         return false;
      }
   }
   return true;
}


#else    //#if defined (BOOST_INTERPROCESS_WINDOWS)

typedef int       file_handle_t;
typedef off_t     offset_t;

typedef struct mapping_handle_impl_t
{
   file_handle_t  handle;
   bool           is_xsi;
}  mapping_handle_t;

typedef enum { read_only      = O_RDONLY
             , read_write     = O_RDWR
             , copy_on_write
             , read_private
             , invalid_mode   = 0xffff
             } mode_t;

typedef enum { file_begin     = SEEK_SET
             , file_end       = SEEK_END
             , file_current   = SEEK_CUR
             } file_pos_t;

typedef int map_options_t;
static const map_options_t default_map_options = map_options_t(-1);

namespace ipcdetail{

inline mapping_handle_t mapping_handle_from_file_handle(file_handle_t hnd)
{
   mapping_handle_t ret;
   ret.handle = hnd;
   ret.is_xsi = false;
   return ret;
}

inline file_handle_t file_handle_from_mapping_handle(mapping_handle_t hnd)
{  return hnd.handle; }

inline bool create_directory(const char *path)
{  return ::mkdir(path, 0777) == 0 && ::chmod(path, 0777) == 0; }

inline bool remove_directory(const char *path)
{  return ::rmdir(path) == 0; }

inline bool get_temporary_path(char *buffer, std::size_t buf_len, std::size_t &required_len)
{
   required_len = 5u;
   if(buf_len < required_len)
      return false;
   else{
      std::strcpy(buffer, "/tmp");
   }
   return true;
}

inline file_handle_t create_new_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   (void)temporary;
   int ret = ::open(name, ((int)mode) | O_EXCL | O_CREAT, perm.get_permissions());
   if(ret >= 0){
      ::fchmod(ret, perm.get_permissions());
   }
   return ret;
}

inline file_handle_t create_or_open_file
   (const char *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   (void)temporary;
   int ret = -1;
   //We need a loop to change permissions correctly using fchmod, since
   //with "O_CREAT only" ::open we don't know if we've created or opened the file.
   while(1){
      ret = ::open(name, ((int)mode) | O_EXCL | O_CREAT, perm.get_permissions());
      if(ret >= 0){
         ::fchmod(ret, perm.get_permissions());
         break;
      }
      else if(errno == EEXIST){
         if((ret = ::open(name, (int)mode)) >= 0 || errno != ENOENT){
            break;
         }
      }
      else{
         break;
      }
   }
   return ret;
}

inline file_handle_t open_existing_file
   (const char *name, mode_t mode, bool temporary = false)
{
   (void)temporary;
   return ::open(name, (int)mode);
}

inline bool delete_file(const char *name)
{  return ::unlink(name) == 0;   }

inline bool truncate_file (file_handle_t hnd, std::size_t size)
{
   typedef boost::move_detail::make_unsigned<off_t>::type uoff_t;
   if(uoff_t((std::numeric_limits<off_t>::max)()) < size){
      errno = EINVAL;
      return false;
   }
   return 0 == ::ftruncate(hnd, off_t(size));
}

inline bool get_file_size(file_handle_t hnd, offset_t &size)
{
   struct stat data;
   bool ret = 0 == ::fstat(hnd, &data);
   if(ret){
      size = data.st_size;
   }
   return ret;
}

inline bool set_file_pointer(file_handle_t hnd, offset_t off, file_pos_t pos)
{  return ((off_t)(-1)) != ::lseek(hnd, off, (int)pos); }

inline bool get_file_pointer(file_handle_t hnd, offset_t &off)
{
   off = ::lseek(hnd, 0, SEEK_CUR);
   return off != ((off_t)-1);
}

inline bool write_file(file_handle_t hnd, const void *data, std::size_t numdata)
{  return (ssize_t(numdata)) == ::write(hnd, data, numdata);  }

inline file_handle_t invalid_file()
{  return -1;  }

inline bool close_file(file_handle_t hnd)
{  return ::close(hnd) == 0;   }

inline bool acquire_file_lock(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}

inline bool try_acquire_file_lock(file_handle_t hnd, bool &acquired)
{
   struct ::flock lock;
   lock.l_type    = F_WRLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno == EAGAIN || errno == EACCES) ?
               (acquired = false, true) : false;
   }
   return (acquired = true);
}

inline bool release_file_lock(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_UNLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLK, &lock);
}

inline bool acquire_file_lock_sharable(file_handle_t hnd)
{
   struct ::flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   return -1 != ::fcntl(hnd, F_SETLKW, &lock);
}

inline bool try_acquire_file_lock_sharable(file_handle_t hnd, bool &acquired)
{
   struct flock lock;
   lock.l_type    = F_RDLCK;
   lock.l_whence  = SEEK_SET;
   lock.l_start   = 0;
   lock.l_len     = 0;
   int ret = ::fcntl(hnd, F_SETLK, &lock);
   if(ret == -1){
      return (errno == EAGAIN || errno == EACCES) ?
               (acquired = false, true) : false;
   }
   return (acquired = true);
}

inline bool release_file_lock_sharable(file_handle_t hnd)
{  return release_file_lock(hnd);   }

#if 0
inline bool acquire_file_lock(file_handle_t hnd)
{  return 0 == ::flock(hnd, LOCK_EX); }

inline bool try_acquire_file_lock(file_handle_t hnd, bool &acquired)
{
   int ret = ::flock(hnd, LOCK_EX | LOCK_NB);
   acquired = ret == 0;
   return (acquired || errno == EWOULDBLOCK);
}

inline bool release_file_lock(file_handle_t hnd)
{  return 0 == ::flock(hnd, LOCK_UN); }

inline bool acquire_file_lock_sharable(file_handle_t hnd)
{  return 0 == ::flock(hnd, LOCK_SH); }

inline bool try_acquire_file_lock_sharable(file_handle_t hnd, bool &acquired)
{
   int ret = ::flock(hnd, LOCK_SH | LOCK_NB);
   acquired = ret == 0;
   return (acquired || errno == EWOULDBLOCK);
}

inline bool release_file_lock_sharable(file_handle_t hnd)
{  return 0 == ::flock(hnd, LOCK_UN); }
#endif

inline bool delete_subdirectories_recursive
   (const std::string &refcstrRootDirectory, const char *dont_delete_this)
{
   DIR *d = opendir(refcstrRootDirectory.c_str());
   if(!d) {
      return false;
   }

   struct dir_close
   {
      DIR *d_;
      dir_close(DIR *d) : d_(d) {}
      ~dir_close() { ::closedir(d_); }
   } dc(d); (void)dc;

   struct ::dirent *de;
   struct ::stat st;
   std::string fn;

   while((de=::readdir(d))) {
      if( de->d_name[0] == '.' && ( de->d_name[1] == '\0'
            || (de->d_name[1] == '.' && de->d_name[2] == '\0' )) ){
         continue;
      }
      if(dont_delete_this && std::strcmp(dont_delete_this, de->d_name) == 0){
         continue;
      }
      fn = refcstrRootDirectory;
      fn += '/';
      fn += de->d_name;

      if(std::remove(fn.c_str())) {
         if(::stat(fn.c_str(), & st)) {
            return false;
         }
         if(S_ISDIR(st.st_mode)) {
            if(!delete_subdirectories_recursive(fn, 0) ){
               return false;
            }
         } else {
            return false;
         }
      }
   }
   return std::remove(refcstrRootDirectory.c_str()) ? false : true;
}

template<class Function>
inline bool for_each_file_in_dir(const char *dir, Function f)
{
   std::string refcstrRootDirectory(dir);

   DIR *d = opendir(refcstrRootDirectory.c_str());
   if(!d) {
      return false;
   }

   struct dir_close
   {
      DIR *d_;
      dir_close(DIR *d) : d_(d) {}
      ~dir_close() { ::closedir(d_); }
   } dc(d); (void)dc;

   struct ::dirent *de;
   struct ::stat st;
   std::string fn;

   while((de=::readdir(d))) {
      if( de->d_name[0] == '.' && ( de->d_name[1] == '\0'
            || (de->d_name[1] == '.' && de->d_name[2] == '\0' )) ){
         continue;
      }
      fn = refcstrRootDirectory;
      fn += '/';
      fn += de->d_name;

      if(::stat(fn.c_str(), & st)) {
         return false;
      }
      //If it's a file, apply erase logic
      if(!S_ISDIR(st.st_mode)) {
         f(fn.c_str(), de->d_name);
      }
   }
   return true;
}


//This function erases all the subdirectories of a directory except the one pointed by "dont_delete_this"
inline bool delete_subdirectories(const std::string &refcstrRootDirectory, const char *dont_delete_this)
{
   return delete_subdirectories_recursive(refcstrRootDirectory, dont_delete_this );
}

#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

inline bool open_or_create_directory(const char *dir_name)
{
   //If fails, check that it's because it already exists
   if(!create_directory(dir_name)){
      error_info info(system_error_code());
      if(info.get_error_code() != already_exists_error){
         return false;
      }
   }
   return true;
}

inline std::string get_temporary_path()
{
   std::size_t required_len = 0;
   get_temporary_path(0, 0, required_len);
   std::string ret_str(required_len, char(0));
   get_temporary_path(&ret_str[0], ret_str.size(), required_len);
   while(!ret_str.empty() && !ret_str[ret_str.size()-1]){
      ret_str.erase(ret_str.size()-1);
   }

   return ret_str;
}

}  //namespace ipcdetail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP

/* os_file_functions.hpp
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
*/