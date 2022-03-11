//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SHARED_MEMORY_OBJECT_HPP
#define BOOST_INTERPROCESS_SHARED_MEMORY_OBJECT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>
#include <string>

#if defined(BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS)
#  include <fcntl.h>        //O_CREAT, O_*...
#  include <sys/mman.h>     //shm_xxx
#  include <unistd.h>       //ftruncate, close
#  include <sys/stat.h>     //mode_t, S_IRWXG, S_IRWXO, S_IRWXU,
#  if defined(BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
#     if defined(__FreeBSD__)
#        include <sys/sysctl.h>
#     endif
#  endif
#else
//
#endif

//!\file
//!Describes a shared memory object management class.

namespace boost {
namespace interprocess {

//!A class that wraps a shared memory mapping that can be used to
//!create mapped regions from the mapped files
class shared_memory_object
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable and non-assignable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(shared_memory_object)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Default constructor. Represents an empty shared_memory_object.
   shared_memory_object();

   //!Creates a shared memory object with name "name" and mode "mode", with the access mode "mode"
   //!If the file previously exists, throws an error.*/
   shared_memory_object(create_only_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   //!Tries to create a shared memory object with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   shared_memory_object(open_or_create_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, perm);  }

   //!Tries to open a shared memory object with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   shared_memory_object(open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, permissions());  }

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   shared_memory_object(BOOST_RV_REF(shared_memory_object) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   shared_memory_object &operator=(BOOST_RV_REF(shared_memory_object) moved)
   {
      shared_memory_object tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the shared_memory_objects. Does not throw
   void swap(shared_memory_object &moved);

   //!Erases a shared memory object from the system.
   //!Returns false on error. Never throws
   static bool remove(const char *name);

   //!Sets the size of the shared memory mapping
   void truncate(offset_t length);

   //!Destroys *this and indicates that the calling process is finished using
   //!the resource. All mapped regions are still
   //!valid after destruction. The destructor function will deallocate
   //!any system resources allocated by the system for use by this process for
   //!this resource. The resource can still be opened again calling
   //!the open constructor overload. To erase the resource from the system
   //!use remove().
   ~shared_memory_object();

   //!Returns the name of the shared memory object.
   const char *get_name() const;

   //!Returns true if the size of the shared memory object
   //!can be obtained and writes the size in the passed reference
   bool get_size(offset_t &size) const;

   //!Returns access mode
   mode_t get_mode() const;

   //!Returns mapping handle. Never throws.
   mapping_handle_t get_mapping_handle() const;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   void priv_close();

   //!Opens or creates a shared memory object.
   bool priv_open_or_create(ipcdetail::create_enum_t type, const char *filename, mode_t mode, const permissions &perm);

   file_handle_t  m_handle;
   mode_t         m_mode;
   std::string    m_filename;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shared_memory_object::shared_memory_object()
   :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   ,  m_mode(read_only)
{}

inline shared_memory_object::~shared_memory_object()
{  this->priv_close(); }


inline const char *shared_memory_object::get_name() const
{  return m_filename.c_str(); }

inline bool shared_memory_object::get_size(offset_t &size) const
{  return ipcdetail::get_file_size((file_handle_t)m_handle, size);  }

inline void shared_memory_object::swap(shared_memory_object &other)
{
   boost::adl_move_swap(m_handle, other.m_handle);
   boost::adl_move_swap(m_mode,   other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t shared_memory_object::get_mapping_handle() const
{
   return ipcdetail::mapping_handle_from_file_handle(m_handle);
}

inline mode_t shared_memory_object::get_mode() const
{  return m_mode; }

#if !defined(BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS)

inline bool shared_memory_object::priv_open_or_create
   (ipcdetail::create_enum_t type, const char *filename, mode_t mode, const permissions &perm)
{
   m_filename = filename;
   std::string shmfile;
   ipcdetail::create_shared_dir_cleaning_old_and_get_filepath(filename, shmfile);

   //Set accesses
   if (mode != read_write && mode != read_only){
      error_info err = other_error;
      throw interprocess_exception(err);
   }

   switch(type){
      case ipcdetail::DoOpen:
         m_handle = ipcdetail::open_existing_file(shmfile.c_str(), mode, true);
      break;
      case ipcdetail::DoCreate:
         m_handle = ipcdetail::create_new_file(shmfile.c_str(), mode, perm, true);
      break;
      case ipcdetail::DoOpenOrCreate:
         m_handle = ipcdetail::create_or_open_file(shmfile.c_str(), mode, perm, true);
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   //Check for error
   if(m_handle == ipcdetail::invalid_file()){
      error_info err = system_error_code();
      this->priv_close();
      throw interprocess_exception(err);
   }

   m_mode = mode;
   return true;
}

inline bool shared_memory_object::remove(const char *filename)
{
   try{
      //Make sure a temporary path is created for shared memory
      std::string shmfile;
      ipcdetail::shared_filepath(filename, shmfile);
      return ipcdetail::delete_file(shmfile.c_str());
   }
   catch(...){
      return false;
   }
}

inline void shared_memory_object::truncate(offset_t length)
{
   if(!ipcdetail::truncate_file(m_handle, length)){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
}

inline void shared_memory_object::priv_close()
{
   if(m_handle != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_handle);
      m_handle = ipcdetail::invalid_file();
   }
}

#else //!defined(BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS)

namespace shared_memory_object_detail {

#ifdef BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY

#if defined(__FreeBSD__)

inline bool use_filesystem_based_posix()
{
   int jailed = 0;
   std::size_t len = sizeof(jailed);
   ::sysctlbyname("security.jail.jailed", &jailed, &len, NULL, 0);
   return jailed != 0;
}

#else
#error "Not supported platform for BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY"
#endif

#endif

}  //shared_memory_object_detail

inline bool shared_memory_object::priv_open_or_create
   (ipcdetail::create_enum_t type,
    const char *filename,
    mode_t mode, const permissions &perm)
{
   #if defined(BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
   const bool add_leading_slash = false;
   #elif defined(BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
   const bool add_leading_slash = !shared_memory_object_detail::use_filesystem_based_posix();
   #else
   const bool add_leading_slash = true;
   #endif
   if(add_leading_slash){
      ipcdetail::add_leading_slash(filename, m_filename);
   }
   else{
      ipcdetail::create_shared_dir_cleaning_old_and_get_filepath(filename, m_filename);
   }

   //Create new mapping
   int oflag = 0;
   if(mode == read_only){
      oflag |= O_RDONLY;
   }
   else if(mode == read_write){
      oflag |= O_RDWR;
   }
   else{
      error_info err(mode_error);
      throw interprocess_exception(err);
   }
   int unix_perm = perm.get_permissions();

   switch(type){
      case ipcdetail::DoOpen:
      {
         //No oflag addition
         m_handle = shm_open(m_filename.c_str(), oflag, unix_perm);
      }
      break;
      case ipcdetail::DoCreate:
      {
         oflag |= (O_CREAT | O_EXCL);
         m_handle = shm_open(m_filename.c_str(), oflag, unix_perm);
         if(m_handle >= 0){
            ::fchmod(m_handle, unix_perm);
         }
      }
      break;
      case ipcdetail::DoOpenOrCreate:
      {
         //We need a create/open loop to change permissions correctly using fchmod, since
         //with "O_CREAT" only we don't know if we've created or opened the shm.
         while(1){
            //Try to create shared memory
            m_handle = shm_open(m_filename.c_str(), oflag | (O_CREAT | O_EXCL), unix_perm);
            //If successful change real permissions
            if(m_handle >= 0){
               ::fchmod(m_handle, unix_perm);
            }
            //If already exists, try to open
            else if(errno == EEXIST){
               m_handle = shm_open(m_filename.c_str(), oflag, unix_perm);
               //If open fails and errno tells the file does not exist
               //(shm was removed between creation and opening tries), just retry
               if(m_handle < 0 && errno == ENOENT){
                  continue;
               }
            }
            //Exit retries
            break;
         }
      }
      break;
      default:
      {
         error_info err = other_error;
         throw interprocess_exception(err);
      }
   }

   //Check for error
   if(m_handle < 0){
      error_info err = errno;
      this->priv_close();
      throw interprocess_exception(err);
   }

   m_filename = filename;
   m_mode = mode;
   return true;
}

inline bool shared_memory_object::remove(const char *filename)
{
   try{
      std::string filepath;
      #if defined(BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
      const bool add_leading_slash = false;
      #elif defined(BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
      const bool add_leading_slash = !shared_memory_object_detail::use_filesystem_based_posix();
      #else
      const bool add_leading_slash = true;
      #endif
      if(add_leading_slash){
         ipcdetail::add_leading_slash(filename, filepath);
      }
      else{
         ipcdetail::shared_filepath(filename, filepath);
      }
      return 0 == shm_unlink(filepath.c_str());
   }
   catch(...){
      return false;
   }
}

inline void shared_memory_object::truncate(offset_t length)
{
   if(0 != ftruncate(m_handle, length)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void shared_memory_object::priv_close()
{
   if(m_handle != -1){
      ::close(m_handle);
      m_handle = -1;
   }
}

#endif

//!A class that stores the name of a shared memory
//!and calls shared_memory_object::remove(name) in its destructor
//!Useful to remove temporary shared memory objects in the presence
//!of exceptions
class remove_shared_memory_on_destroy
{
   const char * m_name;
   public:
   remove_shared_memory_on_destroy(const char *name)
      :  m_name(name)
   {}

   ~remove_shared_memory_on_destroy()
   {  shared_memory_object::remove(m_name);  }
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_SHARED_MEMORY_OBJECT_HPP

/* shared_memory_object.hpp
4VAe8pYh1x9+vMzk2eg5rkIbJOOT4+w6pwArpQ+L8qfwRvrx3wVGw/A60aD7F6TN8889NqNMbvshCIwZXI7HfunYm7IoVLoVNfZ+vkW19ieacBYfaAN7Kb5vxw/cfL3uEowvxUWp9g2vKYR/RxdqvuaFMpG8gaNw73S/n1QAyazr51NrNtq1l804hXYFXoht+5AYPtC5cT1ae4FqjI7w7aULYQ1SInuNOVALPXbCTgcpByktLYQ+U7KT5kV6nEndIbUe24Ju9LaEPi0m6N+j5YyUZ+PEEHmIHiABLE80n+R8sn3j8h8Pz7jFLzbJzbH8VPwevsF0fvjXcyhcyHN7v8fqrrviYFkm29+uP+GEvM6xnRySEaMuFKG5WHjDbQLuXmiOwvG27wXJA2F7ykvdCURO+08JOk5wfNdSIyUOD9NRBR5fOAS0Ma8/ZDmJ6QSbqZ3rJkXnTLbDvU7D+wt9mmAs9ytkCzziQAKd0hm8pE75Sub++jbhs+oZQT8DdPeWRhgvFi1EjZbq2u8/jnHtREhDMDWp0xiqwzyrzhX39XgVxDPpy8RT+4C3LjJ7OTKC8J+POXAqOIq3clM9XtIiirr/XFvhA7KYi9fgtXJgKJr5QjknBqbyQh3IHuPpRUIy7IFo0vZ+A2HyLhJGi2Vy0HKBZj1thpBbniauxIjb5UpinZ9OHsIhyEqMmLFffnFKarpA06Yq2nw78W7U5Jkb81D+1Y5zPIvdYU5L1c/G4ntgUAH2sCf8d4ZQD380qjPirgXBFo1/W1+hVrKXefQf7eHGZ5Lo0BD8IYUjcR84F+ODm4JNsWb1NwTSaWRq0eZwPsL2lrUr8xnaDpUE5sI7YHRtQEGjH9cBanjXIZPLSjUNRForlCeqtcirjeqXSBeJYbSSD+JQla5tpuZ5eHxF9KsesKXjWYmCEP0SXim8j9h3HMFawRo/fARfhOyykagvDHzjkW98TLJxoRFfA5q7f17J6F2t8dhnrW/MqRI7XUn3NjZf8Ymk2+OeQrnfnkWu0mB7chfma76IrqirS6eWOM+NQAdh8DuXHMSNM9uRzZrxXSyYiDSQQMRkUO8SlG10JT7S8LCjlQAkbEBOMSxWJLpwB+VoB3DZ9QktOFg58TxlVqsxZK13kJLZNDVHGAnY810Su7xDgVjFybPp3qba90P9x78FGDwGhK+JsV8g48M4++o3jxOz82HDLB3OR6rOrn5t1Z1ugXXid1+OCh3r1aufDiXORx3yUAEut0eeQ15gCpL6dmjyA2nckRKZrFB9O/51j7M5aQcXCgwhJMviXurHozamnP1KZAu6LWJebfteGQF8B8Nbeq7yV14lKLx+UyFvlmbsDkXNRuG0zxEwFxJT7hxkDTJR+gJVfzbuTNCLHmc7q69pi3FuKifsLf9we7YjFde7XoEReAkvov/uHE275ZZ3HpAeVIx7LvDn9AN8j0IEnWicqXS7EoLQbWxQ3pSbPI6cXCkeUFLBA5b8Tnkr00u+M0SgQqAXa4LfdvMOddd9A7vkduAr6N6j3z/WFOX1LLv5SRf1zkqli/8zADDmpP5hEVcMxG4zBbaICaMFpHUOZZCEI9cEaH3JcDKU5rNnk+sfp3FG9ymAueC3tlQlC7VREEXe+pAqU56iG41xYEJNj/k3D4F9Mz5qhgVhAAAs/9OABquW83BfjQuqC7DAfB7jV1/U7howZiKkhS/jiBCB5KPCvYS21DsAhBPdf4RRDwn1UsteTKPvmNennTTyLx+lTiE4KNiNFMjECljgZ0/GXcDMUohofRJkVVVQeKndnrXdZY7t8JQ3d/Oo4eY5Gpe65ZBSMClQuvTj4cg8HNAmV8UONXYSGaipiYmVT1BvWNSc+XZcsaHuSNsWpwAamQKcLxJieu0VY7Hj7ppJiO8/Jr7Yh9nQ2ypF+uJYLscmyhyOJCoJbF00w14PM9pQC5/795+stS4tPLI1tzDa2+GcwdLieDdlYXkcK1vS2+pwGKWe6w7D1KfbOvwhN6gBo90Lc6gP8NNB9TOI+iVfJ43IF1pWC7uVGIpNr3emYp4VDejlF7vuWEtZbJIy7Jhqy6DfNknr0zu8e5trMvwPfeDJg07lJqUZU7KSLJ13zIdj1S9Z5hvvRDmGjaA8+Xi5v3d1FGjrA/WVrK2QFlqcRiC8S6Rf5xJc8rdxKicHdQbJF2D8XYYKh/i93Ob2jJRT/Hf+BO5ycT8+K2QzW6VvwoQNqtiy4K9lGedM32aBrCm2fKLbuFzi+z87yWNRoCwYHa/FRfDeonLEXPO1FrKnfiPfawm3Rz2HqmrESvYD23dUy9R+1W5g5S0Lcy57rcn89i/PNQw66h/y2TDaMcrZjiwLIx3NySjMrYfyfDGdrVgT2dJJ6+YIro3z/yQDMCbxqSzKjH2EnB+pu8SJYspGQHLt2NNEImYqRu13GxIErMH0KMFa7Bht0Cn9dblZd9ezPkbzwgMNADJ5f9rk7KL/iwl7HpU1qF5ofdMV2jLbocq/LnYjUZeLhqFgW2p1Gx9Xyye0BsEwoLKG1rCcHswaEx6a86We92dX518kMYHb5/henv/hG+zlqa94uOGzWWTlJwCETs1SFakAQ6Qh0CA//Ae6zC9pDWwoUNZOe6k7j8MvhigNnc0zev9waPzImLG/zvUa+Rgq1KAt+t85tEqVasXm9dpMmVRbikLB7Orjp2/vHIcEVPsrvPksx9z3Q49earZx+fnNq07VOd9U7jK1F3Ne+a4Nmip7bDlB74slgxExkxoXazmvP5fcZ/Y0BevTpVq/+wOjcXVcB4yZ9FY0+x113CGoXf3MXr0nr2p7EzWid5IaR0+6p0uZ7k6Jmtt/KzyjpZA4eSGa3kxNIjR5ey4v/4XUzlJ56lf15ZIibaMmrP1O2lbR24ncq3ai8vJmdx2bPBUYBXqGm04sPIWv9FBSHRW79w7HbOemcjN+avfswBw7by6a4Bm4O0c4CdzZsrEa1VgBbxkFQUi3cmp46FkfAjtFbbP0cR3Rl7ZV7Op8khzlvC2qWauCYWJNFvtmOR20qa49TPsUjTQmqppS09ml1xVDUQZ37wD4TQicpijGXEMRFmSsWki8uI3/+7VpUykwZpYKuVrO1XGDqE9roHBpIi7e34Lz4PDuwzo++o+detZiq6QaEkTHXzt3CzHETtqq0SauBMQsPMhemXX7K4Zx4YR4s/qUZ3ua2VYR4FT5Nw6S+5HKyzRBXowBGTRuU/Vs8feFhZiRT/S9nzqfo8yAOzDVlqwfPUvuJGYdldcmyjXDHdM7ZF0JZHEjcCTK97D54kvgDD47eLzMxmXtBiDLLLXTuinJq8OrTMfnOISDukxKdVZFL9+mk3+r8NCB4XCJNeKSRtd2beqaaJ++EQbhUL96oTyd19q2OBAfk0AEWDyx9AHIPEYhi9sONDxYJoJHGtYCoqB2zAMvgMYTh+aWHXO9VxWbosstJ4cwUg/my0xK1hBHaYjd1IhIvggMAMfcHDsEd9ay2TOp0cNwTW8njZX3+4sAAjkNqXOCyJuTqO57kJ5x2FIkY9FYSnDWFI04eg0j7aaPM0QKurPJpldlOArAKDjj9BK+dLYbkJSaScj3PiPwN+uCvp/w2kJHhSRzfeVnLiJDHV4ijGcedWYtQxlZTJpzpniRyFGvek5+gkF5RGTzufcydR2G6Fo4iC08MxtVCGSrWwByrLSp7ZGgRamvdzQ53H534VeH2g1PHPL64/0O0SINonlJBX2MJt8aEn7O812G7vxgyYCa+kxGZfeV5klWoYrUGld2uqLoTX2RFg31Ax3dkqP0haMlBnSPEY8lO4nwPiXFkYIlOyXkeyTj1B5DtrlM4Jtg7792hEyeFcI5v75L+MzMnnj+DaLNE/1C1Rycm4jTO1tXQzaOIrOvHOqcx9D0D8D+meTOUD5h80T0KiECpRUIZp45m7HfN5lfTzNKDmY1B1wS9rIL4gd9zuonROxcFTFRnBlKl3mK9ublf0A5GsOsLnqal8lpcqptQE2fQ70wO4LdTh+Y7x1P/EGFZFFyol9hzY/SiY5zx8ssGJ7cW6d8xUiwCB5ntTKMaOYjM1d5wFOdgBDnT0JYQbjumChao6flmMMzmPMbV8elGNXyoDUq//T3tRsxPTvlWCkpbwlqbp5Ne0cmwUDzpdPQNHQ/YlCBkhHC767WDTiBcZURIsSvcUdN43kl6qg5vQyaSJCQ8u+uqqOFga0uGdnz3M8qYRB5cCcvaRyn8zBnA7F7twE3uO1PGHjzrOOtJjqX350jKPB+Do6FvgjpNdp2SKAVTmR6GuHwJlNgoXL3gQnr8fmCq04MBUcrLld6g5hSw7YRhWmVWS9TZMbbVTcMad0gyagwrL1BfsdSz+Pd+lh5kQZEveJpw/8rW4b50gcN+N6HJlpPGXe7POkS9mhr637XEaLzE0m2Q8zyGMtECkC/ug19upTxfLd1xu0Kq+F+LNzAhV6fcI1ah71LzJ7cvLowDEi622GJ2FcaB0N2xNysFd6nEDykWFwdmbMk2pzXFOISRiggloiZ6OG7EfGuOtkQdvRJnDEVHRZHMBHdwehSj3efVcmHedoXNcysUxM74Vtrsp5H1Psgv94ZpeRIh7u3fG6Mjw/3LKhrO36/37FKgINAbR0kQeFp1kzIKIFw7rA67LestSgEcTxjRLySPo7Lxqc8SvpElCtYyQSiGdmPJTDqpUW0bmSTv7e9PWhEADrCh/CRQlUbI+e10AkWvv4EaBcy2bWj4Qkemg3fJ9X3f6Ctq9yHZd7ay/m1cQFzoccphBJA2VFGKxTwkdookBwwTrF55wu9De9MirJQAKlefBCLnJR5tLgys9tGfCapO0zFroDBGgFy2YBPy2mxcZshi3+B1Z6/h5xrl4geQbNHu79BuXP/bZYNj9mD0vDpvtbDjWNaEw3rQgbHe+4UNKthRtHqS2ly/sVTaE96hWiVJkHZfKjh6VDkef5H5siGoYJuM7LBJRF3VeW+U1+sBNI2zoL8GZ0MZbOchYY4JAms1n1j3E1md4JjpH0dsbfO87Cih/T+NJ5xjFx/XvIA6V1TUjfBSnHXBdaXdTL0hjt2C3aRC2HC7WleCHZ/S/DtlfvTktmnNWOGPLuzImf91iB59hZY3dc9R8574aUhYjY9w8oSDJ8Nii6GcnK+XaOPkeahtHaprIkOum0O1Ou/pPOIGW/cwqQFiSCSLwISkWlBxCi25vr52mFFIEevezrFZ0j0hOF94fcaPgjf5V+BN62IWa6J+W6sTw4K24J2O+VvWti4UcXiQYXdk/mk2op8Qt3YrZnV1phyfvNQdooMJDgdeLnTqt7KTkjpBul1z9W7b/ua6jOe0JXzqNWAJb9FAbTVs9m026+0ebyZtEmDgxfDrzZLDONqKw+56ObsPVuWfvdui2j+AobVMzAbez/Nwt4UceS61MSzbmM3f8aRhB7pIUs3EAsGtNTJ5QGX5rAIuWTGkcQxrpuh5sXIGqB7Nip6aAQj0mgYNEKdlibeLxSsl3QWoQFHBGYQZE/OAWCyIBzHOxUC4K/zQR1mKJaPdaK9UxdMWZjGP8roTXMAk/cSybqQOd3swo3JTEFEexB7StynOnzxr1wo7S0EysOWOQgv71WUb9FIkJQirZEcQk68olC2RkR7MwQ64voHfn1YOJ4MxPF6q7rJhbXxsXoRuLQX2GbXPzpWXzHdhl4TRWAbjjiBvyrnxpwEKcHNl0+GhqeFK+gFxw2LZpuCF+xIKqytseeXfT7Hg+Rod9l7tI5lRHYFSTDAjJ83RZlHGMbRwy8jvuFCF43QOepBVryX78X30K4CL9ve5L+Bmw//acYAB48s83tV13c+xJTrlbPFm41XZANztH5XIN0l5wuECMSE82MEf9wnsxxEI6YnQRUOfTci6SxZX1iNZmPr/M1fnYzg2aM6M2ohgfbCNwwbDGlTq82ZLQl6fuyDXyxZGwuBuC6wgMWLaw4iuuzZ5sta0KYP4tX8Dj1i7Z3HHOAGpz6RjGBqoe9m9ny/f3A++Uw0ghIgJpif0XOqJCALjdRHi2tCUgR+TWD9BIhXK2tNuoDFnbobVcbUhVN+RKybydc7IfJTKTz1fEdm7YdZqrAZlkO+KJ4OOiKkBrFBDtoLn5G1j/R7BiJdyg9urk5mB5+ISbhJxLenTmFGbvdWmPx8uxzvzDwy3rYBZ8YWAq1v6zrQLFw5I6qPJLmETEWOGoUoFWJMcedIm4mkdh5ZPdqz6LeeU1rXJ9cTAoVEe7Lo7YPAjQXSDhb9tZfC21Pdln4GAJPkpfs1fCZDKlJ0LoZhkohDzy333IS8AgdqTOIm6yZS4AziDV8bCDdV6/nD2WvyMcYJh4Ma2TXqd1aRit1jR9fLMWVApw5LS6RPD/M5PqN1/KaW0NVPE3kKWrtC/TVMPiVVhrw9ziqVBwqmQ36YeZbunlxRe2ECeqoqVhaBZlTCzemcnCqdAJj4RjrOOD+ILlc/QJUfHsMyEXX6Kw8jYnemZKEXBefjIs4shr3nJBwvhG/4QsgePMsFYYbAwkHZvpRxszjOz6gR+E0HenZkW8kXJUZPI8iJvefOGz8Eas6XmSr/XcTINql+3UywNpX2ukd7Z1GupQlOGyZpWbBb+JIA646kuW4i3NP1Nm+B1fQC6WGWJaP9Vtwawtow2RAYcvYAluGObVDoGj18c1nruxFP4zwOK4eqimV43xo6ljIleasdx4yYxJF+tfHN6M55aBgAenDPsiboZU9EMP6nnU/CIIyE8JV3qqWCQQX3i50/dz9v2x4nu81kLaq1s/+rjd05fvn8vQcUiIp96P/rxMQDPBPMhVjkMQeOHFTKD3HdQTcv70NlrGfRqedQUr/Crw1q0z2iUyGC0D4oXgUuYEIVTfJWawU+YgSqEcl1Gm6K+nCqxMFKPC/vNa3jhV+oRBOM+56HL4FNjPYsxDRfiopv1Ptuzle6sIzRHGy8+gmxJC1foiLdQIN/ABgI7RrU5AWkyXtcffWA14CMGhrNbjPhYdj3+72eM57Jsnegtb9o+oaGMjwKURiZGoOcuZyGegGtvWVIFuYFIWYKuplo1DOA5lf/aMAV7klJ75VNeYQbLfjz2rKHgM3JsXT/OZu2Pu54R2zG1oiCH0XgSKhH1XhOnrmaqRPBw0/G5arP51ou9cZ/ANdCHMGeBVOBq4+oz9aj05hOeErkYagG5k1BZZRBiLiXC9X6eNMQ24mEnUkRzsfvbqWOAA8CYVhwg5jhgoi4d1usU0KlH7FE/OtZELlPZK1daRgBaWcIv7AU+l88e10ay1jR2jPWQThDd1KJLjRdYC/6ETqN3Z4ZuO1FDGoEP11e882avOmkSPaZD8SMJ+kZJPieVcbigG7WSyq5NJGADiRJIU1U/kOYFBogfY9RAH9rGphs27SG5exUY/CvdaQgyBNnvaxGaYmAb0uT3lXGJnz9biQEl6NBpHmHX8k/Wre17mikC+urqgoUhbUWastpaLGmotZkXPppMuGokqrQfxLXDSKZYJBqoTzTQW2UWgmawhIKBBzeBlAkv5dMgc/1oXmErOmVbxPWrPQJS/FoIjROUf/5pbO2hcOmRPlZt/0DL/1sIIc+F03eiZXQokYUQ3Nzpz1nmg01O+iSRIf3P3H3s5ABxia+T2GGDaTJbGpUqbMGZlHPoPjiJNIrL+RdzdMZRrVuCVKyPZL2llxeJJnc6jnZefFxrQVe2nccbaeO2jQ49fvNi0aGZyplYchyre343EQIhp4M2elFisFPEAlxrl9iANCnkGDeXg9qQMRzo7G2BSkTDk0hnMEnv16pO/fV/56SjiJsGBbSPyzn3k0x88TASfE73Zsc4sdV/wUcRsg+QcQfgomNvCoj4mTT5YuC3UzyuD+7N3e9gH+yjN00aoBGzHw4XwuVRKLFtzM8yKDy7VoKFfF+tnInpbl3gDOzCaSbx358awe89m4ZmXBacZrOMRh9PnjfL1XyFtNQjxbRGGXYUjrU4Mj1jOKLQ68PZttFb5873x7IkSuaXTEvmBnOShJTMDjLQF02f+xV9Y0CX7Qf7taempPTqT1gUDpl1nVXHHUtPfmvJ5tsIyJodQjcJnNzbGvOCOCEHdvB/IaCdUoHeorSpOKk9pvYHdapjk//vgmShtHlaPLnFtBl71uPaogyu4hbftk5Zkvmwafpeg/H4z/TJzHVabOgNBsRZ5KZobIe2GXB0YAyJVpfwwhUbEJVajuJC0goGQCHFY9pZzgZ+OrBdWfgPdOk1a/DPiXPvGEpSTv4Bt1xddvI/aO0dcZvomkuoWZVa9R7xqKWzwB4XfprefOJvK80AxKqFUwmtvuQhgoZmJ28xvQnCkkOm3sFkqsElzB9D4sNedEmyJ4QjUxY9o7gGan3bjuMIrjKKVODaYnvc1/Oujp6ZntGjeWrOre1JwONMCQmg2l8Mk3+TZImaq1CsCTwT/ao+3ITxwpB8goiFahK2pM5qPLfRNGCQrv7I1Xuh0Hkr4S6BeTgdzuOg5XVwocGJFUj3ajdOL1ZryMkV5JOZtaBwEyb0Er0F0zVAmuVcyCWYDQWkOLO6cj6F7ZB4qYyFSizO2bK7wKTcHs8HtHr0vreFUXUp3r9so71cfJoVK7of0/CRAbbDPt47gNfNHOS8jMw+xoT07pRXCwydeVLBfYZqqqlpoZO46WBOunQZMwyE0GKRKhLiZD/ObJ4aRN/oDeGOUXkVGvEwVafVT9Mn+YhA1a5r6/D4Fh2lzqLpQ6SZ5QZtm7nFnYl9jXXC4akP1Ajmgk36+EgWmUbWgrnYo1Q3VZUziiEBiCOvCAH/FxsuMghLq2/1yhUHPmO+dm/8Y2byI7U/rJt8qE39ViIErASLW1Sjanl1HEMF0jPbAnjcQ8yUpShJyVNlc2OHKpER9KiNEFVVCxEZlupgtnJ3tsX+MlouohX5/72b6hzFEquVzddynL1pczpAWatHXaKWDQsX5cxbI2MEXne5df2XPAVnJynuExoK2iWg18itF2/Q+27nAeX9yExfOryrO/z4VDJUneFeASUG4EjCbWWNoZbworDG1YGdwHIqqYnUzNuv76SXnTISdBjR7AHg0XMOJehKGzYL/eQcITO0os54d4coMa0VJYBodT3BiR/iUtvwGVi9rlFXYqW7qPYfukA7tzACz20Pa3tIU8lpFB5qkQ=
*/