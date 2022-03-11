//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2010-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ROBUST_EMULATION_HPP
#define BOOST_INTERPROCESS_ROBUST_EMULATION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_recursive_mutex.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/detail/intermodule_singleton.hpp>
#include <boost/interprocess/detail/portable_intermodule_singleton.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/sync/spin/wait.hpp>
#include <boost/interprocess/sync/detail/common_algorithms.hpp>
#include <string>

namespace boost{
namespace interprocess{
namespace ipcdetail{

namespace robust_emulation_helpers {

template<class T>
class mutex_traits
{
   public:
   static void take_ownership(T &t)
   {  t.take_ownership(); }
};

inline void remove_if_can_lock_file(const char *file_path)
{
   file_handle_t fhnd = open_existing_file(file_path, read_write);

   if(fhnd != invalid_file()){
      bool acquired;
      if(try_acquire_file_lock(fhnd, acquired) && acquired){
         delete_file(file_path);
      }
      close_file(fhnd);
   }
}

inline const char *robust_lock_subdir_path()
{  return "robust"; }

inline const char *robust_lock_prefix()
{  return "lck"; }

inline void robust_lock_path(std::string &s)
{
   get_shared_dir(s);
   s += "/";
   s += robust_lock_subdir_path();
}

inline void create_and_get_robust_lock_file_path(std::string &s, OS_process_id_t pid)
{
   intermodule_singleton_helpers::create_tmp_subdir_and_get_pid_based_filepath
      (robust_lock_subdir_path(), robust_lock_prefix(), pid, s);
}

//This class will be a intermodule_singleton. The constructor will create
//a lock file, the destructor will erase it.
//
//We should take in care that another process might be erasing unlocked
//files while creating this one, so there are some race conditions we must
//take in care to guarantee some robustness.
class robust_mutex_lock_file
{
   file_handle_t fd;
   std::string fname;
   public:
   robust_mutex_lock_file()
   {
      permissions p;
      p.set_unrestricted();
      //Remove old lock files of other processes
      remove_old_robust_lock_files();
      //Create path and obtain lock file path for this process
      create_and_get_robust_lock_file_path(fname, get_current_process_id());

      //Now try to open or create the lock file
      fd = create_or_open_file(fname.c_str(), read_write, p);
      //If we can't open or create it, then something unrecoverable has happened
      if(fd == invalid_file()){
         throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: could not open or create file");
      }

      //Now we must take in care a race condition with another process
      //calling "remove_old_robust_lock_files()". No other threads from this
      //process will be creating the lock file because intermodule_singleton
      //guarantees this. So let's loop acquiring the lock and checking if we
      //can't exclusively create the file (if the file is erased by another process
      //then this exclusive open would fail). If the file can't be exclusively created
      //then we have correctly open/create and lock the file. If the file can
      //be exclusively created, then close previous locked file and try again.
      while(1){
         bool acquired;
         if(!try_acquire_file_lock(fd, acquired) || !acquired ){
            throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: try_acquire_file_lock");
         }
         //Creating exclusively must fail with already_exists_error
         //to make sure we've locked the file and no one has
         //deleted it between creation and locking
         file_handle_t fd2 = create_new_file(fname.c_str(), read_write, p);
         if(fd2 != invalid_file()){
            close_file(fd);
            fd = fd2;
            continue;
         }
         //If exclusive creation fails with expected error go ahead
         else if(error_info(system_error_code()).get_error_code() == already_exists_error){ //must already exist
            //Leak descriptor to mantain the file locked until the process dies
            break;
         }
         //If exclusive creation fails with unexpected error throw an unrecoverable error
         else{
            close_file(fd);
            throw interprocess_exception(other_error, "Robust emulation robust_mutex_lock_file constructor failed: create_file filed with unexpected error");
         }
      }
   }

   ~robust_mutex_lock_file()
   {
      //The destructor is guaranteed by intermodule_singleton to be
      //executed serialized between all threads from current process,
      //so we just need to close and unlink the file.
      close_file(fd);
      //If some other process deletes the file before us after
      //closing it there should not be any problem.
      delete_file(fname.c_str());
   }

   private:
   //This functor is execute for all files in the lock file directory
   class other_process_lock_remover
   {
      public:
      void operator()(const char *filepath, const char *filename)
      {
         std::string pid_str;
         //If the lock file is not our own lock file, then try to do the cleanup
         if(!intermodule_singleton_helpers::check_if_filename_complies_with_pid
            (filename, robust_lock_prefix(), get_current_process_id(), pid_str)){
            remove_if_can_lock_file(filepath);
         }
      }
   };

   bool remove_old_robust_lock_files()
   {
      std::string refcstrRootDirectory;
      robust_lock_path(refcstrRootDirectory);
      return for_each_file_in_dir(refcstrRootDirectory.c_str(), other_process_lock_remover());
   }
};

}  //namespace robust_emulation_helpers {

//This is the mutex class. Mutex should follow mutex concept
//with an additonal "take_ownership()" function to take ownership of the
//mutex when robust_spin_mutex determines the previous owner was dead.
template<class Mutex>
class robust_spin_mutex
{
   public:
   static const boost::uint32_t correct_state = 0;
   static const boost::uint32_t fixing_state  = 1;
   static const boost::uint32_t broken_state  = 2;

   typedef robust_emulation_helpers::mutex_traits<Mutex> mutex_traits_t;

   robust_spin_mutex();
   void lock();
   bool try_lock();
   bool timed_lock(const boost::posix_time::ptime &abs_time);
   void unlock();
   void consistent();
   bool previous_owner_dead();

   private:
   static const unsigned int spin_threshold = 100u;
   bool lock_own_unique_file();
   bool robust_check();
   bool check_if_owner_dead_and_take_ownership_atomically();
   bool is_owner_dead(boost::uint32_t own);
   void owner_to_filename(boost::uint32_t own, std::string &s);
   //The real mutex
   Mutex mtx;
   //The pid of the owner
   volatile boost::uint32_t owner;
   //The state of the mutex (correct, fixing, broken)
   volatile boost::uint32_t state;
};

template<class Mutex>
inline robust_spin_mutex<Mutex>::robust_spin_mutex()
   : mtx(), owner(get_invalid_process_id()), state(correct_state)
{}

template<class Mutex>
inline void robust_spin_mutex<Mutex>::lock()
{  try_based_lock(*this);  }

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::try_lock()
{
   //Same as lock() but without spinning
   if(atomic_read32(&this->state) == broken_state){
      throw interprocess_exception(lock_error, "Broken id");
   }

   if(!this->lock_own_unique_file()){
      throw interprocess_exception(lock_error, "Broken id");
   }

   if (mtx.try_lock()){
      atomic_write32(&this->owner, get_current_process_id());
      return true;
   }
   else{
      if(!this->robust_check()){
         return false;
      }
      else{
         return true;
      }
   }
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::timed_lock
   (const boost::posix_time::ptime &abs_time)
{  return try_based_timed_lock(*this, abs_time);   }

template<class Mutex>
inline void robust_spin_mutex<Mutex>::owner_to_filename(boost::uint32_t own, std::string &s)
{
   robust_emulation_helpers::create_and_get_robust_lock_file_path(s, own);
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::robust_check()
{
   //If the old owner was dead, and we've acquired ownership, mark
   //the mutex as 'fixing'. This means that a "consistent()" is needed
   //to avoid marking the mutex as "broken" when the mutex is unlocked.
   if(!this->check_if_owner_dead_and_take_ownership_atomically()){
      return false;
   }
   atomic_write32(&this->state, fixing_state);
   return true;
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::check_if_owner_dead_and_take_ownership_atomically()
{
   boost::uint32_t cur_owner = get_current_process_id();
   boost::uint32_t old_owner = atomic_read32(&this->owner), old_owner2;
   //The cas loop guarantees that only one thread from this or another process
   //will succeed taking ownership
   do{
      //Check if owner is dead
      if(!this->is_owner_dead(old_owner)){
         return false;
      }
      //If it's dead, try to mark this process as the owner in the owner field
      old_owner2 = old_owner;
      old_owner = atomic_cas32(&this->owner, cur_owner, old_owner);
   }while(old_owner2 != old_owner);
   //If success, we fix mutex internals to assure our ownership
   mutex_traits_t::take_ownership(mtx);
   return true;
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::is_owner_dead(boost::uint32_t own)
{
   //If owner is an invalid id, then it's clear it's dead
   if(own == (boost::uint32_t)get_invalid_process_id()){
      return true;
   }

   //Obtain the lock filename of the owner field
   std::string file;
   this->owner_to_filename(own, file);

   //Now the logic is to open and lock it
   file_handle_t fhnd = open_existing_file(file.c_str(), read_write);

   if(fhnd != invalid_file()){
      //If we can open the file, lock it.
      bool acquired;
      if(try_acquire_file_lock(fhnd, acquired) && acquired){
         //If locked, just delete the file
         delete_file(file.c_str());
         close_file(fhnd);
         return true;
      }
      //If not locked, the owner is suppossed to be still alive
      close_file(fhnd);
   }
   else{
      //If the lock file does not exist then the owner is dead (a previous cleanup)
      //function has deleted the file. If there is another reason, then this is
      //an unrecoverable error
      if(error_info(system_error_code()).get_error_code() == not_found_error){
         return true;
      }
   }
   return false;
}

template<class Mutex>
inline void robust_spin_mutex<Mutex>::consistent()
{
   //This function supposes the previous state was "fixing"
   //and the current process holds the mutex
   if(atomic_read32(&this->state) != fixing_state &&
      atomic_read32(&this->owner) != (boost::uint32_t)get_current_process_id()){
      throw interprocess_exception(lock_error, "Broken id");
   }
   //If that's the case, just update mutex state
   atomic_write32(&this->state, correct_state);
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::previous_owner_dead()
{
   //Notifies if a owner recovery has been performed in the last lock()
   return atomic_read32(&this->state) == fixing_state;
}

template<class Mutex>
inline void robust_spin_mutex<Mutex>::unlock()
{
   //If in "fixing" state, unlock and mark the mutex as unrecoverable
   //so next locks will fail and all threads will be notified that the
   //data protected by the mutex was not recoverable.
   if(atomic_read32(&this->state) == fixing_state){
      atomic_write32(&this->state, broken_state);
   }
   //Write an invalid owner to minimize pid reuse possibility
   atomic_write32(&this->owner, get_invalid_process_id());
   mtx.unlock();
}

template<class Mutex>
inline bool robust_spin_mutex<Mutex>::lock_own_unique_file()
{
   //This function forces instantiation of the singleton
   robust_emulation_helpers::robust_mutex_lock_file* dummy =
      &ipcdetail::intermodule_singleton
         <robust_emulation_helpers::robust_mutex_lock_file>::get();
   return dummy != 0;
}

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif

/* robust_emulation.hpp
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
*/