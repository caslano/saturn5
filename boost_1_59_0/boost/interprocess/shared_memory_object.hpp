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
#include <boost/interprocess/detail/char_wchar_holder.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

#if defined(BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS)
#  include <string>
#  include <fcntl.h>        //posix_fallocate, O_CREAT, O_*...
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
   shared_memory_object() BOOST_NOEXCEPT;

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

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a shared memory object with name "name" and mode "mode", with the access mode "mode"
   //!If the file previously exists, throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shared_memory_object(create_only_t, const wchar_t*name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   //!Tries to create a shared memory object with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shared_memory_object(open_or_create_t, const wchar_t*name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, perm);  }

   //!Tries to open a shared memory object with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   shared_memory_object(open_only_t, const wchar_t*name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, permissions());  }

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Moves the ownership of "moved"'s shared memory object to *this.
   //!After the call, "moved" does not represent any shared memory object.
   //!Does not throw
   shared_memory_object(BOOST_RV_REF(shared_memory_object) moved) BOOST_NOEXCEPT
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s shared memory to *this.
   //!After the call, "moved" does not represent any shared memory.
   //!Does not throw
   shared_memory_object &operator=(BOOST_RV_REF(shared_memory_object) moved) BOOST_NOEXCEPT
   {
      shared_memory_object tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the shared_memory_objects. Does not throw
   void swap(shared_memory_object &moved) BOOST_NOEXCEPT;

   //!Erases a shared memory object from the system.
   //!Returns false on error. Never throws
   static bool remove(const char *name);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Erases a shared memory object from the system.
   //!Returns false on error. Never throws
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *name);

   #endif //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

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
   const char *get_name() const BOOST_NOEXCEPT;

   //!Returns true if the size of the shared memory object
   //!can be obtained and writes the size in the passed reference
   bool get_size(offset_t &size) const BOOST_NOEXCEPT;

   //!Returns access mode
   mode_t get_mode() const BOOST_NOEXCEPT;

   //!Returns mapping handle. Never throws.
   mapping_handle_t get_mapping_handle() const BOOST_NOEXCEPT;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //!Closes a previously opened file mapping. Never throws.
   void priv_close();

   //!Opens or creates a shared memory object.
   template<class CharT>
   bool priv_open_or_create(ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, const permissions &perm);

   file_handle_t     m_handle;
   mode_t            m_mode;
   char_wchar_holder m_filename;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline shared_memory_object::shared_memory_object() BOOST_NOEXCEPT
   :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   ,  m_mode(read_only)
{}

inline shared_memory_object::~shared_memory_object()
{  this->priv_close(); }


inline const char *shared_memory_object::get_name() const BOOST_NOEXCEPT
{  return m_filename.getn(); }

inline bool shared_memory_object::get_size(offset_t &size) const BOOST_NOEXCEPT
{  return ipcdetail::get_file_size((file_handle_t)m_handle, size);  }

inline void shared_memory_object::swap(shared_memory_object &other) BOOST_NOEXCEPT
{
   boost::adl_move_swap(m_handle, other.m_handle);
   boost::adl_move_swap(m_mode,   other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t shared_memory_object::get_mapping_handle() const BOOST_NOEXCEPT
{
   return ipcdetail::mapping_handle_from_file_handle(m_handle);
}

inline mode_t shared_memory_object::get_mode() const BOOST_NOEXCEPT
{  return m_mode; }

#if !defined(BOOST_INTERPROCESS_POSIX_SHARED_MEMORY_OBJECTS)

template<class CharT>
inline bool shared_memory_object::priv_open_or_create
   (ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, const permissions &perm)
{
   m_filename = filename;
   std::basic_string<CharT> shmfile;
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

#if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES)

inline bool shared_memory_object::remove(const wchar_t *filename)
{
   BOOST_TRY{
      //Make sure a temporary path is created for shared memory
      std::wstring shmfile;
      ipcdetail::shared_filepath(filename, shmfile);
      return ipcdetail::delete_file(shmfile.c_str());
   }
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

#endif

inline bool shared_memory_object::remove(const char *filename)
{
   BOOST_TRY{
      //Make sure a temporary path is created for shared memory
      std::string shmfile;
      ipcdetail::shared_filepath(filename, shmfile);
      return ipcdetail::delete_file(shmfile.c_str());
   }
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

inline void shared_memory_object::truncate(offset_t length)
{
   if(!ipcdetail::truncate_file(m_handle, (std::size_t)length)){
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

template<class CharT>
inline bool shared_memory_object::priv_open_or_create
   (ipcdetail::create_enum_t type,
    const CharT *filename,
    mode_t mode, const permissions &perm)
{
   #if defined(BOOST_INTERPROCESS_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
   const bool add_leading_slash = false;
   #elif defined(BOOST_INTERPROCESS_RUNTIME_FILESYSTEM_BASED_POSIX_SHARED_MEMORY)
   const bool add_leading_slash = !shared_memory_object_detail::use_filesystem_based_posix();
   #else
   const bool add_leading_slash = true;
   #endif
   std::basic_string<CharT> fname;
   if(add_leading_slash){
      ipcdetail::add_leading_slash(filename, fname);
   }
   else{
      ipcdetail::create_shared_dir_cleaning_old_and_get_filepath(filename, fname);
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
   ::mode_t unix_perm = perm.get_permissions();

   switch(type){
      case ipcdetail::DoOpen:
      {
         //No oflag addition
         m_handle = shm_open(fname.c_str(), oflag, unix_perm);
      }
      break;
      case ipcdetail::DoCreate:
      {
         oflag |= (O_CREAT | O_EXCL);
         m_handle = shm_open(fname.c_str(), oflag, unix_perm);
         if(m_handle >= 0){
            ::fchmod(m_handle, unix_perm);
         }
      }
      break;
      case ipcdetail::DoOpenOrCreate:
      {
         //We need a create/open loop to change permissions correctly using fchmod, since
         //with "O_CREAT" only we don't know if we've created or opened the shm.
         while(true){
            //Try to create shared memory
            m_handle = shm_open(fname.c_str(), oflag | (O_CREAT | O_EXCL), unix_perm);
            //If successful change real permissions
            if(m_handle >= 0){
               ::fchmod(m_handle, unix_perm);
            }
            //If already exists, try to open
            else if(errno == EEXIST){
               m_handle = shm_open(fname.c_str(), oflag, unix_perm);
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
   BOOST_TRY{
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
   BOOST_CATCH(...){
      return false;
   } BOOST_CATCH_END
}

inline void shared_memory_object::truncate(offset_t length)
{
   #ifdef BOOST_INTERPROCESS_POSIX_FALLOCATE
   int ret = EINTR;
   while (EINTR == ret) {
      ret = posix_fallocate(m_handle, 0, length);
   }

   if (ret && ret != EOPNOTSUPP && ret != ENODEV){
      error_info err(ret);
      throw interprocess_exception(err);
   }
   //ftruncate fallback
   #endif //BOOST_INTERPROCESS_POSIX_FALLOCATE

   handle_eintr:
   if (0 != ftruncate(m_handle, length)){
      if (errno == EINTR)
         goto handle_eintr;
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
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
*/