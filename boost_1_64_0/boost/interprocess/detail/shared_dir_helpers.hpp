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
8UzyqXdO4HUNcGgZ/rS8s0T2m06KDa7p6PnkY8QT77/aiCUeg+LJQTxaTv2JeM76co36lXRHvW9Vr5cUUp4Pw+2bwSTfjAQrDH36UsSzQ93/EocovjqGjiPX8osYIjJL5thfUZwLEec08HB9fUJu38GNykq/pzy/vDTkPRcOqdzPC7JmVZJRpRRXBuogifhkPov4ipFqHdeEgeCjcuV0vTBIPcdad57+SP51VLw0B55Oz+XeD8zOps7nLCu+7eSfZO2HiBss+ZayvIX8h3i3IXw9K58zsDlDz18+Hsjl4Mce4zeNhlZaPJS21RTXIcQVRc+veCLNqSFpmQd/tsMsp3jGeJ+0pbXYSuvnA+11cgc9Lzd7GIPMBHnH1eQ22bvWiDSfRzwNKB5px6KoBW0x64l3mdkN4RtInW4kt57euyiss74SpL76c1hcR9HMc5mnjaF5s/Ir846mMl1htod1psx4l8bBqZ3R/noEx5IiuptjXXeMjT1kLCmnoSTsPfL+9JrHkkbE00aPJZKOIT1kLBlY/fphMN1vWele2kilewSeD4J4DLygVmPgw+k1j9/PEk+C73zjeW/ltPt6BtcGv65xbVDxpwT5l44k/ui68t0X8cuYKbwVPXktL9q3bG60NxJLenWi2mM9L6bMqHE9L5ba+hLbu7cF3738SLVpvRturWnM5vJ7EfRwJfoj6CXQA5pojWc/6GXQtlCSeNZTXdh/vxIS559ABySuVx1xsa7wZ9BrYeoMwTXG90mOb/ZFGndiv8EVRqx5k1fpDu1roTtsGBKiO+C5eIj9G50G9jlr4Sw9X7HNCe177iFaHd++SF8P2136u+gYPGbhzC3RIc4OsOsQpel2//vTtb9t/tlXvuWCpxpTWwK7K1vWMJtOoZcnwpx/UnjH/FPvtRhG/g3MeIy5RaAfQQ49QcfjmHsGbWjLyf9dowtqdi+oqvFb9Y1tvdDuekvfmFKzDFL8I/pY36G8rWTQQYQfAjf+DuUvtbLXRg2vnb1WvX9xn6Dceajavhx02/ALdO21VIaToGsPdn5/8gtttnru7tIXpA2PH2a3x75e6dk/3L3NLk/jBKkMtwKeAtPP4Nk73Nlm3fe46jn8SQrzgRmso/foOdn9W5Xhui2eidN7XYPrOZ+S/yfmYORyK0JGYs/szSBnu7bH1dyn5+pNpX98Sf7vm33xtfJmA9ZKaAm9zUnOeX/luEL25jUV/fZD8j9mjjWwvgSqj/n4rSCnXcAZF4tCbRO4cITyL0AeEq15eKuRtG4uPNj5Sjyz1LfpzENuOl69Z1bbwp8g/3rY3xRr7AS5xuXs2zT3UP0ypy/Snhrsl/e56QY19rvGEs+JVOlzS6jLxbnLCM2f3D/YR3+qUTdQ/BlB/qUL5QXVz6l/E6P79R0h61m/CbOfB/XndCpLL/bglBs3GKXOefUv/NYMfSF0zyS1z+Y+PVfW82f7fstjLjIhktKIAVfGrUYj7ONaxEi7f4OR7t+onU6XPTQe3hMy08M28OmjLBlBxzGE840ahzGr/D5gcIbyHwDeS6z5zXBy89OcbReFKcJBF9bZB9Yc963Riu8qbu9WuKux0uKhsDt02JLKYQ9QuiJIdumwHVz3q5+RMXBlGspqQLD9fVVte50PtyQD/DGaXge9AXoT9BbobdA7oHdBh0Dvgd4H/QV0GPSBhPsQ9BHoCOhj0CegT0FHQZ+BPgd9AdoXZpsOyuuMDL3W6Kvhe2sqn6q/t7bv9+Wyoza2KcNuz3kqo7J9JobtM4P5hd+AlMPXoC/AUzxGt7n8vFI25pdWHpP0vtklxP8h4vUYM0A3glxt/GPc94A4xxs7b7FPryNa9hryn4w=
*/