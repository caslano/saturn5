//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_SHARED_DIR_HELPERS_HPP
#define BOOST_INTERPROCESS_DETAIL_SHARED_DIR_HELPERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <string>

#if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME) && defined(BOOST_INTERPROCESS_WINDOWS)
   #include <boost/interprocess/detail/windows_intermodule_singleton.hpp>
#endif

namespace boost {
namespace interprocess {
namespace ipcdetail {

#if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
   #if defined(BOOST_INTERPROCESS_WINDOWS)
      //This type will initialize the stamp
      struct windows_bootstamp
      {
         windows_bootstamp()
         {
            //Throw if bootstamp not available
            if(!winapi::get_last_bootup_time(stamp)){
               error_info err = system_error_code();
               throw interprocess_exception(err);
            }
         }
         //Use std::string. Even if this will be constructed in shared memory, all
         //modules/dlls are from this process so internal raw pointers to heap are always valid
         std::string stamp;
      };

      inline void get_bootstamp(std::string &s, bool add = false)
      {
         const windows_bootstamp &bootstamp = windows_intermodule_singleton<windows_bootstamp>::get();
         if(add){
            s += bootstamp.stamp;
         }
         else{
            s = bootstamp.stamp;
         }
      }
   #elif defined(BOOST_INTERPROCESS_HAS_BSD_KERNEL_BOOTTIME)
      inline void get_bootstamp(std::string &s, bool add = false)
      {
         // FreeBSD specific: sysctl "kern.boottime"
         int request[2] = { CTL_KERN, KERN_BOOTTIME };
         struct ::timeval result;
         std::size_t result_len = sizeof result;

         if (::sysctl (request, 2, &result, &result_len, 0, 0) < 0)
            return;

         char bootstamp_str[256];

         const char Characters [] =
            { '0', '1', '2', '3', '4', '5', '6', '7'
            , '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

         std::size_t char_counter = 0;
         //32 bit values to allow 32 and 64 bit process IPC
         boost::uint32_t fields[2] = { boost::uint32_t(result.tv_sec), boost::uint32_t(result.tv_usec) };
         for(std::size_t field = 0; field != 2; ++field){
            for(std::size_t i = 0; i != sizeof(fields[0]); ++i){
               const char *ptr = (const char *)&fields[field];
               bootstamp_str[char_counter++] = Characters[(ptr[i]&0xF0)>>4];
               bootstamp_str[char_counter++] = Characters[(ptr[i]&0x0F)];
            }
         }
         bootstamp_str[char_counter] = 0;
         if(add){
            s += bootstamp_str;
         }
         else{
            s = bootstamp_str;
         }
      }
   #else
      #error "BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME defined with no known implementation"
   #endif
#endif   //#if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)

inline void get_shared_dir_root(std::string &dir_path)
{
   #if defined (BOOST_INTERPROCESS_WINDOWS)
      winapi::get_shared_documents_folder(dir_path);
   #else               
      dir_path = "/tmp";
   #endif

   //We always need this path, so throw on error
   if(dir_path.empty()){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   //Remove final null.
   dir_path += "/boost_interprocess";
}

#if defined(BOOST_INTERPROCESS_SHARED_DIR_FUNC) && defined(BOOST_INTERPROCESS_SHARED_DIR_PATH)
#error "Error: Both BOOST_INTERPROCESS_SHARED_DIR_FUNC and BOOST_INTERPROCESS_SHARED_DIR_PATH defined!"
#endif

#ifdef BOOST_INTERPROCESS_SHARED_DIR_FUNC

   // When BOOST_INTERPROCESS_SHARED_DIR_FUNC is defined, users have to implement
   // get_shared_dir
   void get_shared_dir(std::string &shared_dir);

#else
inline void get_shared_dir(std::string &shared_dir)
{
   #if defined(BOOST_INTERPROCESS_SHARED_DIR_PATH)
      shared_dir = BOOST_INTERPROCESS_SHARED_DIR_PATH;
   #else 
      get_shared_dir_root(shared_dir);
      #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
         shared_dir += "/";
         get_bootstamp(shared_dir, true);
      #endif
   #endif
}
#endif

inline void shared_filepath(const char *filename, std::string &filepath)
{
   get_shared_dir(filepath);
   filepath += "/";
   filepath += filename;
}

inline void create_shared_dir_and_clean_old(std::string &shared_dir)
{
   #if defined(BOOST_INTERPROCESS_SHARED_DIR_PATH) || defined(BOOST_INTERPROCESS_SHARED_DIR_FUNC)
      get_shared_dir(shared_dir);
   #else
      //First get the temp directory
      std::string root_shared_dir;
      get_shared_dir_root(root_shared_dir);

      //If fails, check that it's because already exists
      if(!create_directory(root_shared_dir.c_str())){
         error_info info(system_error_code());
         if(info.get_error_code() != already_exists_error){
            throw interprocess_exception(info);
         }
      }

      #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
         get_shared_dir(shared_dir);

         //If fails, check that it's because already exists
         if(!create_directory(shared_dir.c_str())){
            error_info info(system_error_code());
            if(info.get_error_code() != already_exists_error){
               throw interprocess_exception(info);
            }
         }
         //Now erase all old directories created in the previous boot sessions
         std::string subdir = shared_dir;
         subdir.erase(0, root_shared_dir.size()+1);
         delete_subdirectories(root_shared_dir, subdir.c_str());
      #else
         shared_dir = root_shared_dir;
      #endif
   #endif
}

inline void create_shared_dir_cleaning_old_and_get_filepath(const char *filename, std::string &shared_dir)
{
   create_shared_dir_and_clean_old(shared_dir);
   shared_dir += "/";
   shared_dir += filename;
}

inline void add_leading_slash(const char *name, std::string &new_name)
{
   if(name[0] != '/'){
      new_name = '/';
   }
   new_name += name;
}

}  //namespace boost{
}  //namespace interprocess {
}  //namespace ipcdetail {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //ifndef BOOST_INTERPROCESS_DETAIL_SHARED_DIR_HELPERS_HPP

/* shared_dir_helpers.hpp
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
*/