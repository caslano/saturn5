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

#include <climits>
#include <limits>
#include <string>
#include <boost/move/detail/type_traits.hpp> //make_unsigned

#if defined (BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#  include <wchar.h> //wcsxxx()
#else
#  ifdef BOOST_HAS_UNISTD_H
#     include <fcntl.h>
#     include <unistd.h>
#     include <sys/types.h>
#     include <sys/stat.h>
#     include <dirent.h>
#     include <cerrno>
#     include <cstdio>
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

template<class CharT>
inline bool create_directory(const CharT *path)
{  return winapi::create_directory(path); }

template<class CharT>
inline bool open_or_create_directory(const CharT *path)
{
   //If fails, check that it's because it already exists
   return create_directory(path)
      ||  error_info(system_error_code()).get_error_code() == already_exists_error;
}

template<class CharT>
inline bool open_or_create_shared_directory(const CharT *path)
{
   return open_or_create_directory(path);
}

template <class CharT>
inline bool remove_directory(const CharT *path)
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
   const bool ret = required_len && (buf_len > required_len);
   if(ret && buffer[required_len-1] == '\\'){
      buffer[required_len-1] = '\0';
   }
   return ret;
}

inline bool get_temporary_path(wchar_t *buffer, std::size_t buf_len, std::size_t &required_len)
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
   if(ret && buffer[required_len-1] == L'\\'){
      buffer[required_len-1] = L'\0';
   }
   return ret;
}

template<class CharT>
inline file_handle_t create_new_file
   (const CharT *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      ( name, (unsigned int)mode, winapi::create_new, attr
      , (winapi::interprocess_security_attributes*)perm.get_permissions());
}

template <class CharT>
inline file_handle_t create_or_open_file
   (const CharT *name, mode_t mode, const permissions & perm = permissions(), bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      ( name, (unsigned int)mode, winapi::open_always, attr
      , (winapi::interprocess_security_attributes*)perm.get_permissions());
}

template<class CharT>
inline file_handle_t open_existing_file
   (const CharT *name, mode_t mode, bool temporary = false)
{
   unsigned long attr = temporary ? winapi::file_attribute_temporary : 0;
   return winapi::create_file
      (name, (unsigned int)mode, winapi::open_existing, attr, 0);
}

inline bool delete_file(const char *name)
{  return winapi::unlink_file(name);   }

inline bool delete_file(const wchar_t *name)
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
      if(!winapi::set_file_pointer(hnd, filesize, 0, winapi::file_begin)){
         return false;
      }
      //We will write zeros in the end of the file
      //since set_end_of_file does not guarantee this
      for(std::size_t remaining = size - std::size_t(filesize), write_size = 0
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
      if(!winapi::set_file_pointer(hnd, size, 0, winapi::file_begin)){
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
{  return winapi::set_file_pointer(hnd, off, 0, (unsigned long) pos); }

inline bool get_file_pointer(file_handle_t hnd, offset_t &off)
{  return winapi::set_file_pointer(hnd, 0, &off, winapi::file_current); }

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
   acquired = true;
   return true;
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
   
   acquired = true;
   return true;
}

inline bool release_file_lock_sharable(file_handle_t hnd)
{  return release_file_lock(hnd);   }

template<class CharT>
struct os_file_traits;

template<>
struct os_file_traits<char>
{
   static const char *any_file()
   {  return "\\*.*";   }

   static const char *backslash()
   {  return "\\";   }

   static char dot()
   {  return '.';   }

   typedef winapi::win32_find_data_a win32_find_data_t;

   static int cmp(const char *a, const char *b)
   {  return std::strcmp(a, b); }
};

template<>
struct os_file_traits<wchar_t>
{
   static const wchar_t *any_file()
   {  return L"\\*.*";   }

   static const wchar_t *backslash()
   {  return L"\\";   }

   static wchar_t dot()
   {  return L'.';   }

   typedef winapi::win32_find_data_w win32_find_data_t;

   static int cmp(const wchar_t *a, const wchar_t *b)
   {  return std::wcscmp(a, b); }
};

template<class CharT>
inline bool delete_subdirectories_recursive
   (const std::basic_string<CharT> &refcstrRootDirectory, const CharT *dont_delete_this, unsigned int count)
{
   bool               bSubdirectory = false;       // Flag, indicating whether
                                                   // subdirectories have been found
   void *             hFile;                       // Handle to directory
   std::basic_string<CharT>        strFilePath;                 // Filepath
   std::basic_string<CharT>        strPattern;                  // Pattern
   typedef os_file_traits<CharT> traits_t;
   typename traits_t::win32_find_data_t  FileInformation;     // File information

   //Find all files and directories
   strPattern = refcstrRootDirectory + traits_t::any_file();
   hFile = winapi::find_first_file(strPattern.c_str(), &FileInformation);
   if(hFile != winapi::invalid_handle_value){
      do{
         //If it's not "." or ".." or the pointed root_level dont_delete_this erase it
         if(FileInformation.cFileName[0] != traits_t::dot() &&
            !(dont_delete_this && count == 0 && traits_t::cmp(dont_delete_this, FileInformation.cFileName) == 0)){
            strFilePath.erase();
            strFilePath = refcstrRootDirectory + traits_t::backslash() + FileInformation.cFileName;

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
template <class CharT>
inline bool delete_subdirectories(const std::basic_string<CharT> &refcstrRootDirectory, const CharT *dont_delete_this)
{
   return delete_subdirectories_recursive(refcstrRootDirectory, dont_delete_this, 0u);
}


template<class Function>
inline bool for_each_file_in_dir(const char *dir, Function f)
{
   void *             hFile;                       // Handle to directory
   winapi::win32_find_data_a  FileInformation;     // File information

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
{
   ::mode_t m = ::mode_t(0777);
   return ::mkdir(path, m) == 0;
}

inline bool open_or_create_directory(const char *path)
{
   ::mode_t m = ::mode_t(0777);
   return ::mkdir(path, m) == 0 || (errno == EEXIST);
}

inline bool open_or_create_shared_directory(const char *path)
{
   ::mode_t m = ::mode_t(01777);
   const bool created_or_exists = (::mkdir(path, m) == 0) || (errno == EEXIST);
   return created_or_exists && (::chmod(path, m) == 0);
}

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
   while(true){
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

inline std::string get_temporary_path()
{
   std::size_t required_len = 0;
   get_temporary_path((char*)0, 0, required_len);
   std::string ret_str(required_len, char(0));
   get_temporary_path(&ret_str[0], ret_str.size(), required_len);
   while(!ret_str.empty() && !ret_str[ret_str.size()-1]){
      ret_str.erase(ret_str.size()-1);
   }

   return ret_str;
}

#ifdef BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES

inline std::wstring get_temporary_wpath()
{
   std::size_t required_len = 0;
   get_temporary_path((wchar_t*)0, 0, required_len);
   std::wstring ret_str(required_len, char(0));
   get_temporary_path(&ret_str[0], ret_str.size(), required_len);
   while(!ret_str.empty() && !ret_str[ret_str.size()-1]){
      ret_str.erase(ret_str.size()-1);
   }

   return ret_str;
}

#endif

}  //namespace ipcdetail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_OS_FILE_FUNCTIONS_HPP

/* os_file_functions.hpp
yBTcebTV/8sToVJucbTL3c34Jh41uELe7sif2/3ETtMzd0vkYbm7F8j0SbYuQO2BZxV225u7tF0fJNOi0NkNtVVu4IkV1jcQcB6RAe/6OcgwD2M+1NWf/hRESNm+qwv8mEQPAoia/W1ywzj1S7scD/9kmLxKD8HB793C/Z8ulKgKJJMwfIQ7YxROL74SjLSfML851961V4MPluS5yROkQZRSG3tI8jsvn1kbNibX7fwDvnVZ5Tej9XXVh8abX4bMfjtwcHw3AP0h6cKkJezto9fHkxmPZm3s87tg+wFqCnc9nxL+uz0LB4wAHh4CIRCdH79yoTZWC0pQjB3WM3umZHDiubRcGKPBcR1B6dmBeUeziTkaNECDrnVKT1qrbEGVV8556lrVkJQJRDHIQuzj6GhJJF/H7PedAWnAIlv0CdYYSzTqfWqMZITgpI3RnCFsfNUPdYPjT/DEV2x6eGmvpWpn921rEGatQgg3/PCL41uD1pwuAy/EiI9lhVmEBTpXMCHvrXlnfoygTw4agV1SmpuWLOprwb/zN9Rgedg2WfMtUP7RVfzXMBTPPHVeNJjfO2+r12bff9tBYiUL25DSYTmz9MNOTxDPWzeYOYEWIyMrAHhfSKG2QzTTAZVvOzxH9eOFg3rZxkAHGZ64myDDlkGs2g7Ul0art3b8/ZBzhCsCHat7Qil9rpAj3esiIVFoH+HFfAkNrcXaxzxoiCvrIuuixNS4CT2rbrIuUVB1fpKEWwe2duvJMSCbVKG2iP8BvPQp+0uuUZmp56NRWm3sEY6xzcg9TvsmHlJWjBD8nq46m5KOGmYe7aH7AxJir2aV1J4IZVMJOOVLFR8GbP04cUne6FTSBrNI2mLxm+csxBU1O7KBq1w0YqzmwDmmVtytHUTY7Lwijakl7P6nLTm1amFAfT0RmX3I4S2rDoNwf7oiEcKGAHzZriKt5vFJDZxRCd5VXM+lQc2E0o348swxtklBoxCZEvFbe94fhi4WoyzUSG5xj5qs20enusLLxiOkRf1Dbi35YtrRGmwaFSbPPcgVS1HEGUn4DQ0IUGo+TCoVurE3dzZjzQe4u79tQfCsPCaNjk792w3QmxxUZHwfeSh9GQNKMIj8NMYdUBNZ4IwaE32HFdr6K8XT5tWF8Ar4X4xHpSB11HSnZzdpjFZl55OBYkn6dNHDTvu1d437Jw6vIQ0qLiWMDhW8A/fdF8LjzMpskwu4bFL3AnkdaUkMqmwMHx6yvmf16LOSbQzS6z+s0E0s3AZKweLPd3mx/fT/VAFYbF08OjR4OjoEzANxWMXkknY2//7tAXNd3Nipdy/oe1v3hklLz5Z7UCfQcxHVmDbiNJGsBBhWFaXFBS+51saCRvKKFrorH38soED9RP3IsAaDGAg8l0a27WD8Txe4kmarUhhH5SnlopIKSqEsuQ4pUHLQHEupdkF0vxCa7siuoZeUKcbeCyigPE9hj1a8kpnpYB6KuCJ2Jd+FZ5rDXctxOyLx9PK2FIRCE7Oo2msfRr2dcb0FR6qztHWwYgQWtf3ilcwU3AkfE7I0FajMD7kseAMjV6r98S+TyCLmCIa0OF0eAOv3j/NkppCUswfI+N2ayPaKglvImwU7aB4C4LmvieUKsJc7j90Yjj3TLJ4q7/bPiBAFaV5vs1w/EhzGu1hGrH5q+BDDLkw1geHRXte4Uo/j+LjIvFmKzEzrf8NMQCxCOFIZXNo12rWY0NYYavzK8tv7+NhpX2vu1FeCci6AMVK7MKNYJ0qAmvZt2gauVH3EToiXdBuOZ0rvDyVYmmKEsVWKXma9gx1t8GP2aObMK5+q9q7t10Sz+8buA14pQdltMq9gMfPndPdsOxlUCwhGRrkZtExt4YAsYwuFkgCGM9iTU11haWKPJ8k6QhjdY4u1oVNjLiIUlEdtzbZAOK6lTSRf9DPQGoizHbOy0JIz9u1EEmJIaVCzBwqZ8n5EpXwYeUx3LU6xyJLXOM+PLAh89iZvIqZ8S8vTLRrbvfnGzBJDXo+ValOqsmDaAt4/8LyycjGyDecSOwXwS/8BdBOYxB6LpxeNqodNgyEnbV8CBK593n/mNk2LsfBmmN4oVXGne+HPObqAeMGFf4CyAZO6waGAA5km+vB0M/baMU5AhXWZ8sRlXqJcJgfjbgSs4atMk0SwxElkmoksD7tkh7942TUi9nKO2PccGo5bfE1oujuKqFsyXiLKfsdjQgVhB1xQxPU64ZZFGcj0i5TLnpIa0JtO5zq6e4CcF5WOZvhy71ngXrICYz4Kp9quLSySvqZQ8OKQ7hEBI9/rRq0HYjh2+B0dAlB9YUcH2fInmmtaLi2CSKtKvqOql6qJB/oqqR2ISG1gkickFNwjK0pJ2odK++qmUCkaCRKoXi0mHi9//seZ+w2jj+eRKiKF/VNCPZP0+9/VwjR/GmVo/kRm/zX7JjceXu8cDEPiLq/VbMIKZAV9AzM3DoWyi9/cUEKv8/IzKjvBKE8TyT+bI8KPC3eS8SXDvZDHQ9u210Q0SU3MAPYepHcEQofCtCNzBg3CCUhpeK5VOP5DGLk74uvmvQdPiWnimIdzuYmdxKhN60Of4H8JcF9PKsLNkUxN86jV/UaOW5ozCL9nLITPi40b2PdpNUL1/ul1UFEimsjfECWvJzvuH9opT0LZ9lj1IIJOdAvP8dYJJS9Eb9Y4qdxbwMW2rlFIeCvezi1Hl4kOBHqFdMgJnDwv2MAomQVrnGiM/ojcK+EhEZle+0fmvzZT/Ov4i2MgR/1h0JLmQhlXoqGPEoPJ8Is9ocsvpL+UEPYhvS66We6nX49rasXQJh/T16dck36NohVESHEanKs2mEfqHXGz/2HSIyDy9A1+/TCe1aBh7BTyGJqaAkAwzHxoG5YWjuFiBlKB+9XiCgQdRXZALbr1TONWGvS/IYdbc5ucDRKiEZs9DjziEdnau1c5pSFzXZdoG3SBOQxcyKZzBhhASXY9oe8jmlgrn9zW9njPCPHsJUMsPrjFSMKjVXh4rrUy93S7X+win083fOPSzVDb2qOtEddRK/U70zAGpCASz/RWure+DPzDj/OxGnslM1bj61Agv9w1EOYpj9Wdk6wkrawTqkbf+J5H8oxheBSPYon6bWVIaWbcojQtcqYLqFZ/DpMrnFVsSSGRieb49OFohwCi90orToUUSv8lYq7792huc8tp1z2tq2z22wooedcRRhNJBtskrUUbHKgNFe1h8h9ldN1ppCLBjxGIyb1d6zXW0aslvJyrqK1LmGD5OhZp0+2PdUzWGDMHdYWRxiJpjXM1NmD8z/n3IdS6YElbV7fHV8uDQ+fNjy7PZz2ohhW+OebDat558deOrKX7iubTylA+eIAS+iBx2RutrCjhB6qr1Jqm8tpzMPJVnJz++2uNCuIVFJOaBl5kGb7289A2xluT6T8h1eM8ZqLBoQcvJxHQ7l1x1Ebj0YLM0Ls6oEpNmpPS/gBLWF5AoVkZsSG5u2HNKZd+0UvYB8ZTHvPySXf3MDedKvunr0xExucLfyk3Q3rKQ0U0vCuSnMmHCU0qe3ANb+orar63t64F5iVz0uwSJ7BeLDz4SH2i7uCZZVgwIqXkuCHLC8RT/C4Sg8sAEX7ThQRXFQVDbKIkqvsijfleIIe2QKnI2dUYKD/+roDPXN/4zu/1+QDywkJCuWMhHKMhOy8o7nD5BP3DhUc908cfsltVaNkgqNOvAPg5vcy91hKoNqAmnUYNKddhEclP/mvq4d5oSz22qDNaRedZrzNbgXNtH6sBfJsQ0UMxpXBWQVoe1cs2ic3MhH9UiIcw5tTWKWxnuD5Db3m5ngYKk/yrBRjDQ8aOKKyGiwZm/HPJybQIs5HG2/W3OJ4+AFzEcf+x++VA2nzYxsIo6ize+cV+gjcX8NrBoxIDKyXBmNplksKyRtlHWfKNY7RlawSrStxDAwNqnlDccBijXuN+8OAm23CGB8MNl+Ts/sh2xqiWPl0Gsx3CGUWhYArcn+IStN+Z5LVn3DR3ec3KYaGPKN5T9+Ypm0gCNmEuwcYediDIsn/kjeW1Ih3HXU9GAH20PmL4qntg2/xXlG6J4s27WoWOWgiiZjWE+TUxsjrOvjTB2WlV6GOADuXNHMCwEGI1g/eYkSQ7W9aMemqZ+R+AadgPmZtn32jAp/NVmEIG/6dBsqnt1hNUfMDugPXSmw5VJi4B43wIYOdu0LGX1lPBrHsLJGrvuZ9fwik318pKcxnMDKhYg7r9GlM8Wx2J5+NwqlgHfYo0PlzOy3Cn9X5A6qceeypUyDOanlMcGk3V6XwnPckvSl/fVt8MbcFPUnpxVNU09OhPUaBrcC4u1pZaUMDJpC3ctgk2+lI09OKOZ1EJo61rnU/HmU3x4eTAhCKszXH0+m6D2mrw/YqH4sz+O2oEBYb5RVwyVUj5ivw1gyYTATH1csoDD4ffDYDWM6blhKMtGfyHVpdH1dv2lhnHQO6PvXHCdpAJe549TwsC301a7SK2rync/LR1iRyJdPgusFy+WCRX3ajCjz/qmC0f9Go5tAAYykIgbRylTq66vTRtoRwlWhqsTrF1xnu+BxcwF329Q1XLIV2ev9EKKdo/7N2LIrbGLNWb8TTyyymhM1IuC4VRe7ZAaythfq74gGC2ADC1yaAxOEs0te59xnjICDeNDw/OjoBu5UQ45XVkG7m4vAOV0Zd1Eq2KaCYMilpaalLrUixYHIuLtKFYYDVI6eRN30eA8o12DmqpIm2ti2aY7sfW1H0+bt0LkrSGGPCmX8kYTITez3WEdeMBAepVwutn/LEqsQyCxrrYaXVefv467HylSdaGli82TXz0HGm2PjzXyOHhEC4rtgBKiiF+WYwc0oRZuBLKdg+M/ZLs2kGzYT+yc1iKlfqTGKxNS1C0Jwe2WuUqZDXcTsCJauEXZuJrr69DGVQa98DLTYBGFoD0mImu4lTeOwkweTa0r1jsyeXi6oVqEC1Qw3OqN96h3lu1oQ4QaOba4o3ulrtouo721yu/nSmZCr1DzkXTB1DfEmPq+J8pdgssvmKVvJvomNMzevmz0vmC8yTSPo1E6T08p63n3T2LiY2nKUAj2mj26TFrLNVNTAr3kzIIza4whuGD6sQSB6u8dFNLgqwNsM/fsIIfbVv5q4p/wTPa+YkFX6rQuYCKoGi9RFiqET36/8pLyrsA6L7bKLf1cN2qefAaIQ32RebjhpPHA47N/FVYf98EopkJXxKhcvxaAQ/XP6ij3FnPAvQRnQC9/FK/jbW77D7Ac7KrRux6y5O9K2rMMZtU5wVyaNVxBPVLfGCSvojY0BDUJkfyUr9gkl/jOQyE+3I5W38mHCOJFKvBI9q09x2CHG/1qxrYu6WydSmyKL9onMytom2EL6wiI9SmxjB3nIVOgFf6uQ8AP9pKBmcr59eyT66U+t/YC8HFyIIgE1tXEe4TajkfADT4qOTKlafg/60bT0x8TLR25k0a/WPbRLQJqGLcN1evkTfedH0MxlYw4hByR4cGYXvdgSw54SqFF3svJ8t80vmxzZ+Gm9GpuaVtda1JDRnSrCgZKE/RIAkQQDG6oELTkLjpMpwHudtjJPV27xmCAn0Cn2Moi5Xjc50fiym9PvPYUQ4advNMVcCmksu9kbdoPMn2OcOOURUvU3xS4HQsdrKeISF8KmiXlzwBglg9apKfuoK0m/sugPc01PQuSARWPragblZhT0oOEfRQptJAJEiqosaX22vACGTpKOmL0ZWDK3NMiHGVobbjHqt0TbiAY5hCBWLhi3GSX2E9AMYryakEP4Vg0gFF4JB1isc1cATrH+eHnTY+GzI7DvgfHIDjfyw7vOjKEH+LTIiDYNb+jrvTUn9IyjeCB3TqE+h3m2Ix3ymzUIyY6TomPMuxTeMCoZ2Smjge2hHP5Pda/WVbCXqCG1Vm/FwXHhPQCH3UTjDmMzhIpi4zgIgx/E0DRv4r5G1VT6iCRZsHYTWZg1aHLX+LLWhczcQBHGk9JDqUb4Oii82Itjl6xN6LKQ4qvOQ9uZhanfQDGKqOEXD+mh2utdwHNn0b4LWLDCm656Q9yjjTivtKm6JRr6ya1594J2oNT52PEgx9sJ1vm1/iFyOWNcsFqgon60GHtIdRhr4n7IP6TSI3JS8SiMfdu35fFwdiju8vTp7OAzMmjCtaNRKKYI9DXpWRrY9tR5jIQsAuC/46p+92ZiJNYOAlOHd9S519d4IxHDFFThg1ZkDsterziVWYoPz72D1MZbVedOSnpQm/73QyagIknuingHQNHg6o8tBOtwI1upbk6P0tm7HgcgWR55NkSaukuLg2le7H6pLShU8ePWpMnO8O1aXTwN2V2plRJkIqQswfyFXXO56KuxDfgQ8uYokl2Q43BduwfyWUWYb3xgHV4xMGMHyFI44ZigJPY7zvRvnFc44ogDVtDv0oBwQU0KLguHlLPpf/2aiuPBokna8g1syNaG/ZTba775LGBevprTlF/dzzDycPbpe0DCLGZ3piV5kYZ/sbfbdi5LH8b/Q+XgeBL+Xbhv4lcz76x5jGMQWUJRh7W6JtejkWcPecWDnmtupbUhCiSM6uaGy8TWp6CD9zeeJQ/0XD5x/wD2fVBm+KVxpNrOGG+nE0RxwGfaUFkBOtALOsFtRW5RqhirvhIe1LrG+OuYo+tGbOj4aG7vLgTqqgwrxOAL/AAodJC2LYNJthkBiTMN4OetLRrajCOGCFFsmu7sYiOzABk0gTV/0o/p8VKoOZUofjwt3+z6+xQ8xGgPR7zA1fV3PqhuXFeuMBaDErCNBeRPZJGeeRfdE9TAQCGQ3ccq+dIQNoE/TcWdH6MOQA8EkVjzrDZgaKqvb4OB5ayTON4gKBnkudlG5vvaOG9m051/uRnflsMTA2eDWRdYPZWXWv4JOhHtL8xFt00M4ihCchmFGtZLO/wNTuES2E8Q9d030I7VgHPFk/EvnY1zHN3sYzkk+H0HmhF2Zjgts6VVJAWez33WHPHntwzwnWa0GRMO7FPt1GVM6zSwDdUgDu76LZ/PCrAG3g5laSH9gB+msgOsjU4OcBexopCdZJ8JU0JvMOcjR1fnHk4p8+owlToCg8rGJ2LfmbUaqFzlauWFwT5ZmmtY4mMBe8ZU9jBqzD3pbtag0+BswBFwuV30Ww5nz2NNCHVIFSC4hEaevze10Gx3WRJkgimKfbv336o1RHlsKtoVrHM96LU0CL0zYH78tY8b00kOwkyIt3eBt+c4Q/tAQSWLUaLS3My/Ov1aKVdMzbT4JrbzQGc/VaJMdX0EeJ3cU1Na3QjTUakGwwuHmUrd8dBxiMvfhJBaUkZnGhoKjyF3XkC8KgUdI7UwTTtRLAd2FYlKsLY67dY4tanrqwLZ/xbyWls2YLwceEnxDJMJoUfIYyJllmJZOpOy/PRDdePrBRgdV9SuoJzVsazG+FsWJ35h53+ItoeI/5OedulWzVB3dBWJKBOI4IM4JAzIIoMstN87Xw0L8niYUgnSw1kD1VlVDhV3mOeinSnlijNt91aw8PYN7e5GUFtEt13wmHo8eI/AZmMBKcNbvCbhz9hufjYqtwIp9dqmgZe0ut6oobrOJCwRVEOW5TwlgxhMLsfQbFSdMjtyaw3JkOWdBH5HkckmfH
*/