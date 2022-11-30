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
   if(!open_or_create_shared_directory(s.c_str())){
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
      BOOST_TRY{
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
         BOOST_TRY{
            managed_global_memory shm(open_only, str.c_str());
            gmem_erase_func func(str.c_str(), filepath, shm);
            shm.try_atomic_func(func);
         }
         BOOST_CATCH(interprocess_exception &e){
            //If shared memory is not found erase the lock file
            if(e.get_error_code() == not_found_error){
               delete_file(filepath);
            }
         } BOOST_CATCH_END
      }
      BOOST_CATCH(...){

      } BOOST_CATCH_END
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