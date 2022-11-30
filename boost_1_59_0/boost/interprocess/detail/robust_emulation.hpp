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
   template<class TimePoint>
   bool timed_lock(const TimePoint &abs_time);
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
   : mtx(), owner((boost::uint32_t)get_invalid_process_id()), state(correct_state)
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
      atomic_write32(&this->owner, static_cast<boost::uint32_t>(get_current_process_id()));
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
template<class TimePoint>
inline bool robust_spin_mutex<Mutex>::timed_lock
   (const TimePoint &abs_time)
{  return try_based_timed_lock(*this, abs_time);   }

template<class Mutex>
inline void robust_spin_mutex<Mutex>::owner_to_filename(boost::uint32_t own, std::string &s)
{
   robust_emulation_helpers::create_and_get_robust_lock_file_path(s, (OS_process_id_t)own);
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
   boost::uint32_t cur_owner = static_cast<boost::uint32_t>(get_current_process_id());
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
   if(own == static_cast<boost::uint32_t>(get_invalid_process_id())){
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
   atomic_write32(&this->owner, static_cast<boost::uint32_t>(get_invalid_process_id()));
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