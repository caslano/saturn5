//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PORTABLE_INTERMODULE_SINGLETON_HPP
#define BOOST_INTERPROCESS_PORTABLE_INTERMODULE_SINGLETON_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/detail/managed_global_memory.hpp>
#include <boost/interprocess/detail/intermodule_singleton_common.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/detail/os_thread_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/file_locking_helpers.hpp>
#include <boost/assert.hpp>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>

namespace boost{
namespace interprocess{
namespace ipcdetail{

typedef basic_managed_global_memory<shared_memory_object, true>    managed_global_memory;

namespace intermodule_singleton_helpers {

static void create_tmp_subdir_and_get_pid_based_filepath
   (const char *subdir_name, const char *file_prefix, OS_process_id_t pid, std::string &s, bool creation_time = false)
{
   //Let's create a lock file for each process gmem that will mark if
   //the process is alive or not
   create_shared_dir_and_clean_old(s);
   s += "/";
   s += subdir_name;
   if(!open_or_create_directory(s.c_str())){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   s += "/";
   s += file_prefix;
   if(creation_time){
      std::string sstamp;
      get_pid_creation_time_str(sstamp);
      s += sstamp;
   }
   else{
      pid_str_t pid_str;
      get_pid_str(pid_str, pid);
      s += pid_str;
   }
}

static bool check_if_filename_complies_with_pid
   (const char *filename, const char *prefix, OS_process_id_t pid, std::string &file_suffix, bool creation_time = false)
{
   //Check if filename complies with lock file name pattern
   std::string fname(filename);
   std::string fprefix(prefix);
   if(fname.size() <= fprefix.size()){
      return false;
   }
   fname.resize(fprefix.size());
   if(fname != fprefix){
      return false;
   }

   //If not our lock file, delete it if we can lock it
   fname = filename;
   fname.erase(0, fprefix.size());
   pid_str_t pid_str;
   get_pid_str(pid_str, pid);
   file_suffix = pid_str;
   if(creation_time){
      std::size_t p = fname.find('_');
      if (p == std::string::npos){
         return false;
      }
      std::string save_suffix(fname);
      fname.erase(p);
      fname.swap(file_suffix);
      bool ret = (file_suffix == fname);
      file_suffix.swap(save_suffix);
      return ret;
   }
   else{
      fname.swap(file_suffix);
      return (file_suffix == fname);
   }
}

template<>
struct thread_safe_global_map_dependant<managed_global_memory>
{
   private:
   static const int GMemMarkToBeRemoved = -1;
   static const int GMemNotPresent      = -2;

   static const char *get_lock_file_subdir_name()
   {  return "gmem";  }

   static const char *get_lock_file_base_name()
   {  return "lck";  }

   static void create_and_get_singleton_lock_file_path(std::string &s)
   {
      create_tmp_subdir_and_get_pid_based_filepath
         (get_lock_file_subdir_name(), get_lock_file_base_name(), get_current_process_id(), s, true);
   }

   struct gmem_erase_func
   {
      gmem_erase_func(const char *shm_name, const char *singleton_lock_file_path, managed_global_memory & shm)
         :shm_name_(shm_name), singleton_lock_file_path_(singleton_lock_file_path), shm_(shm)
      {}

      void operator()()
      {
         locking_file_serial_id *pserial_id = shm_.find<locking_file_serial_id>("lock_file_fd").first;
         if(pserial_id){
            pserial_id->fd = GMemMarkToBeRemoved;
         }
         delete_file(singleton_lock_file_path_);
         shared_memory_object::remove(shm_name_);
      }

      const char * const shm_name_;
      const char * const singleton_lock_file_path_;
      managed_global_memory & shm_;
   };

   //This function applies shared memory erasure logic based on the passed lock file.
   static void apply_gmem_erase_logic(const char *filepath, const char *filename)
   {
      int fd = GMemMarkToBeRemoved;
      try{
         std::string str;
         //If the filename is current process lock file, then avoid it
         if(check_if_filename_complies_with_pid
            (filename, get_lock_file_base_name(), get_current_process_id(), str, true)){
            return;
         }
         //Open and lock the other process' lock file
         fd = try_open_and_lock_file(filepath);
         if(fd < 0){
            return;
         }
         //If done, then the process is dead so take global shared memory name
         //(the name is based on the lock file name) and try to apply erasure logic
         str.insert(0, get_map_base_name());
         try{
            managed_global_memory shm(open_only, str.c_str());
            gmem_erase_func func(str.c_str(), filepath, shm);
            shm.try_atomic_func(func);
         }
         catch(interprocess_exception &e){
            //If shared memory is not found erase the lock file
            if(e.get_error_code() == not_found_error){
               delete_file(filepath);
            }
         }
      }
      catch(...){

      }
      if(fd >= 0){
         close_lock_file(fd);
      }
   }

   public:

   static bool remove_old_gmem()
   {
      std::string refcstrRootDirectory;
      get_shared_dir(refcstrRootDirectory);
      refcstrRootDirectory += "/";
      refcstrRootDirectory += get_lock_file_subdir_name();
      return for_each_file_in_dir(refcstrRootDirectory.c_str(), apply_gmem_erase_logic);
   }

   struct lock_file_logic
   {
      lock_file_logic(managed_global_memory &shm)
         : mshm(shm)
      {  shm.atomic_func(*this); }

      void operator()(void)
      {
         retry_with_new_map = false;

         //First find the file locking descriptor id
         locking_file_serial_id *pserial_id =
            mshm.find<locking_file_serial_id>("lock_file_fd").first;

         int fd;
         //If not found schedule a creation
         if(!pserial_id){
            fd = GMemNotPresent;
         }
         //Else get it
         else{
            fd = pserial_id->fd;
         }
         //If we need to create a new one, do it
         if(fd == GMemNotPresent){
            std::string lck_str;
            //Create a unique current pid based lock file path
            create_and_get_singleton_lock_file_path(lck_str);
            //Open or create and lock file
            int fd_lockfile = open_or_create_and_lock_file(lck_str.c_str());
            //If failed, write a bad file descriptor to notify other modules that
            //something was wrong and unlink shared memory. Mark the function object
            //to tell caller to retry with another shared memory
            if(fd_lockfile < 0){
               this->register_lock_file(GMemMarkToBeRemoved);
               std::string s;
               get_map_name(s);
               shared_memory_object::remove(s.c_str());
               retry_with_new_map = true;
            }
            //If successful, register the file descriptor
            else{
               this->register_lock_file(fd_lockfile);
            }
         }
         //If the fd was invalid (maybe a previous try failed) notify caller that
         //should retry creation logic, since this shm might have been already
         //unlinked since the shm was removed
         else if (fd == GMemMarkToBeRemoved){
            retry_with_new_map = true;
         }
         //If the stored fd is not valid (a open fd, a normal file with the
         //expected size, or does not have the same file id number,
         //then it's an old shm from an old process with the same pid.
         //If that's the case, mark it as invalid
         else if(!is_valid_fd(fd) ||
               !is_normal_file(fd) ||
               0 != get_size(fd) ||
               !compare_file_serial(fd, *pserial_id)){
            pserial_id->fd = GMemMarkToBeRemoved;
            std::string s;
            get_map_name(s);
            shared_memory_object::remove(s.c_str());
            retry_with_new_map = true;
         }
         else{
            //If the lock file is ok, increment reference count of
            //attached modules to shared memory
            atomic_inc32(&pserial_id->modules_attached_to_gmem_count);
         }
      }

      bool retry() const { return retry_with_new_map; }

      private:
      locking_file_serial_id * register_lock_file(int fd)
      {
         locking_file_serial_id *pinfo = mshm.construct<locking_file_serial_id>("lock_file_fd")();
         fill_file_serial_id(fd, *pinfo);
         return pinfo;
      }

      managed_global_memory &mshm;
      bool retry_with_new_map;
   };

   static void construct_map(void *addr)
   {
      std::string s;
      intermodule_singleton_helpers::get_map_name(s);
      const char *MapName = s.c_str();
      const std::size_t MapSize = intermodule_singleton_helpers::get_map_size();;
      ::new (addr)managed_global_memory(open_or_create, MapName, MapSize);
   }

   struct unlink_map_logic
   {
      unlink_map_logic(managed_global_memory &mshm)
         : mshm_(mshm)
      {  mshm.atomic_func(*this);  }

      void operator()()
      {
         locking_file_serial_id *pserial_id =
            mshm_.find<locking_file_serial_id>
               ("lock_file_fd").first;
         BOOST_ASSERT(0 != pserial_id);
         if(1 == atomic_dec32(&pserial_id->modules_attached_to_gmem_count)){
            int fd = pserial_id->fd;
            if(fd > 0){
               pserial_id->fd = GMemMarkToBeRemoved;
               std::string s;
               create_and_get_singleton_lock_file_path(s);
               delete_file(s.c_str());
               close_lock_file(fd);
               intermodule_singleton_helpers::get_map_name(s);
               shared_memory_object::remove(s.c_str());
            }
         }
      }

      private:
      managed_global_memory &mshm_;
   };

   static ref_count_ptr *find(managed_global_memory &map, const char *name)
   {
      return map.find<ref_count_ptr>(name).first;
   }

   static ref_count_ptr *insert(managed_global_memory &map, const char *name, const ref_count_ptr &ref)
   {
      return map.construct<ref_count_ptr>(name)(ref);
   }

   static bool erase(managed_global_memory &map, const char *name)
   {
      return map.destroy<ref_count_ptr>(name);
   }

   template<class F>
   static void atomic_func(managed_global_memory &map, F &f)
   {
      map.atomic_func(f);
   }
};

}  //namespace intermodule_singleton_helpers {

template<typename C, bool LazyInit = true, bool Phoenix = false>
class portable_intermodule_singleton
   : public intermodule_singleton_impl<C, LazyInit, Phoenix, managed_global_memory>
{};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_PORTABLE_INTERMODULE_SINGLETON_HPP

/* portable_intermodule_singleton.hpp
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
*/