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

template<class CharT>
struct shared_dir_constants;

template<>
struct shared_dir_constants<char>
{
   static char dir_separator()
   {  return '/';   }

   static const char *dir_interprocess()
   {  return "/boost_interprocess";   }
};

template<>
struct shared_dir_constants<wchar_t>
{
   static wchar_t dir_separator()
   {  return L'/';   }

   static const wchar_t *dir_interprocess()
   {  return L"/boost_interprocess";   }
};

#if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
   #if defined(BOOST_INTERPROCESS_WINDOWS)
      //This type will initialize the stamp
      template<class CharT>
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
         std::basic_string<CharT> stamp;
      };

      template <class CharT>
      inline void get_bootstamp(std::basic_string<CharT> &s, bool add = false)
      {
         const windows_bootstamp<CharT> &bootstamp = windows_intermodule_singleton<windows_bootstamp<CharT> >::get();
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

template <class CharT>
inline void get_shared_dir_root(std::basic_string<CharT> &dir_path)
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

   dir_path += shared_dir_constants<CharT>::dir_interprocess();
}

#if defined(BOOST_INTERPROCESS_SHARED_DIR_FUNC) && defined(BOOST_INTERPROCESS_SHARED_DIR_PATH)
#error "Error: Both BOOST_INTERPROCESS_SHARED_DIR_FUNC and BOOST_INTERPROCESS_SHARED_DIR_PATH defined!"
#endif

#ifdef BOOST_INTERPROCESS_SHARED_DIR_FUNC

   // When BOOST_INTERPROCESS_SHARED_DIR_FUNC is defined, users have to implement
   // get_shared_dir
   void get_shared_dir(std::string &shared_dir);

   // When BOOST_INTERPROCESS_SHARED_DIR_FUNC is defined, users have to implement
   // get_shared_dir
   void get_shared_dir(std::wstring &shared_dir);

#else

#if defined(BOOST_INTERPROCESS_SHARED_DIR_PATH)

inline void get_shared_dir(std::string &shared_dir)
{
   shared_dir = BOOST_INTERPROCESS_SHARED_DIR_PATH;
}

#endif

#if defined(BOOST_INTERPROCESS_SHARED_DIR_WPATH)

inline void get_shared_dir(std::wstring &shared_dir)
{
   shared_dir = BOOST_INTERPROCESS_SHARED_DIR_WPATH;
}

#endif

template<class CharT>
inline void get_shared_dir(std::basic_string<CharT> &shared_dir)
{
      get_shared_dir_root(shared_dir);
      #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
         shared_dir += shared_dir_constants<CharT>::dir_separator();
         get_bootstamp(shared_dir, true);
      #endif
}
#endif

template<class CharT>
inline void shared_filepath(const CharT *filename, std::basic_string<CharT> &filepath)
{
   get_shared_dir(filepath);
   filepath += shared_dir_constants<CharT>::dir_separator();
   filepath += filename;
}

template<class CharT>
inline void create_shared_dir_and_clean_old(std::basic_string<CharT> &shared_dir)
{
   #if defined(BOOST_INTERPROCESS_SHARED_DIR_PATH) || defined(BOOST_INTERPROCESS_SHARED_DIR_FUNC)
      get_shared_dir(shared_dir);
   #else
      //First get the temp directory
      std::basic_string<CharT> root_shared_dir;
      get_shared_dir_root(root_shared_dir);

      //If fails, check that it's because already exists
      if(!open_or_create_shared_directory(root_shared_dir.c_str())){
         error_info info(system_error_code());
         throw interprocess_exception(info);
      }

      #if defined(BOOST_INTERPROCESS_HAS_KERNEL_BOOTTIME)
         get_shared_dir(shared_dir);

         //If fails, check that it's because already exists
         if(!open_or_create_shared_directory(shared_dir.c_str())){
            error_info info(system_error_code());
            throw interprocess_exception(info);
         }
         //Now erase all old directories created in the previous boot sessions
         std::basic_string<CharT> subdir = shared_dir;
         subdir.erase(0, root_shared_dir.size()+1);
         delete_subdirectories(root_shared_dir, subdir.c_str());
      #else
         shared_dir = root_shared_dir;
      #endif
   #endif
}

template<class CharT>
inline void create_shared_dir_cleaning_old_and_get_filepath(const CharT *filename, std::basic_string<CharT> &shared_dir)
{
   create_shared_dir_and_clean_old(shared_dir);
   shared_dir += shared_dir_constants<CharT>::dir_separator();
   shared_dir += filename;
}

template<class CharT>
inline void add_leading_slash(const CharT *name, std::basic_string<CharT> &new_name)
{
   if(name[0] != shared_dir_constants<CharT>::dir_separator()){
      new_name = shared_dir_constants<CharT>::dir_separator();
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