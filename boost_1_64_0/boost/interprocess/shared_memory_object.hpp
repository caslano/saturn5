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
OARPwGn4PLgAnw+X4TMkPfgCuAGfHiEnn9lmpqCBL4UN8DmwEx6F/fBlcBxOw3n4ZEkPTkp6MCf5g8dg9LPbzHGYgi+EHfApsBe+CGbhi+EUfDmcg+PwHDwp6cJXwDX4VBg5z3wGa+AzJT34NCnv+f8NO0kdRGj3st6fSvvGyvogVqZsHNLvy2Yh/bfsDKR/l12A9O+yVcgYLLsK6V9l1yD9o6xize73ZbWQ/lG2C9LvyzogrVXWZcucD7LOL+sTrsfLxiD9tewEpJ+WzUHGV9k5SD8sW4b0w7JVyLgs24CMnzLzM7v/l7UIp0lfaBJl+yH9sWwAMp7KxiHjp+wkpL+Wnbb15WUXIOOs7DJk/JRtQMZnWfznkn55WTNkfJZ1QsZNWY/QkG9hivQh47Asa8uJskmIfSg7CRlHZaegazyULSAPwrNwFC7D43AVHoAb8CCs/sU2MwQb4DBsh0dhHzwEx2AOTsGnwFk4IunDw5I+zEj6cAxehsfgVZiF8SuMA1gLj8C2K/+d/hh3b2p/y9duXy39q3wD0g/LK1LQF54UiaQvPKvavA9ehnMwMlltBmAKDsJOeAAOwINwBg7B0/Bd8Cwchpfgu+E6PAQrnl0t9ZhugxnYB4/ASXgUnoIjkg7MwnPwyXAZjsKrMAdrn1NN/ZMOPAb3w0U4AY/DefgUOR6Ow4vwqVKO51bjL1AO+BbYDt8K++G85AO+TcoDnwYX4dOlPuCHJB04IfmA74fRE9ViP9MGPlPSg8+CXfA9UNa3k7AX+dkwA58j+YTvhSfgc+EsPCHng2+X8sJ3wCvwA/A6fJ7U3/OqsdvkHy7AFvgCuAdOST3Ad8Ip+EKpB/giaQ/4YmlPeFLaA75E8v/8auw7+YQvk/zDaUkPvhwOwFdIvcBXSvvAGalX+Cq4Al8t9QFfI/mEs7DhBdXmtVIP8IOSDnwdnIavl3LCU1DWu2+QekU+A9fgG+E1+CZYPeXqny2x9LnjyJ3J9DKkP6cvQ/zm9DWIv5qufYrdr9PtEPua7oXY1/QQxL6mT0D6f3oGYk/TZyB2NH0Jsk5IX4XYtXR8XNKLpash8366AWKn0m0QO5Xugvjp6X6IvUpPQuxS+hTEXqeXIPYwvQaxl+noU+W4ZLpWmCUd4STpQOxgeghi79JTEDueXoDY1fQFiD1NX4HY03T8aRKfTDdA5pd0B2SEp/dA5oV0BjIfpCchdj59CmLn02cgdj59yY5Ppq/axyfS8afL8cl0M8T+pzuF05QLcr0pPSlcT6YXIP5/ekW4lExfF66SjwmYjad7IPNFehwyX6TnIOu39AWI3U+vQ+ahdM0zJB3OA5nf0kOQeSo9Dbm+kV6C2Pn0mnAymY4+U8qVSO+CXJ9I90Cuv6UHbP3W9BhkfkhPQa7LpBeEnYn0OWFPIn1B2E96wizlfZakm0inhNOJdAfkuk26D3I9Jj0JuX6TnhEuJdLzwpVE+uyzqv8rdvx/PZx5YXi9MFbvuEQcY/SOFyFj8o5rkDF5xw3ommvuGH8RcwtMwUHYDoud7/TLsE9VMbPO1mNiZtrAW8TMak3MmFvHTAvbIrql/H4pft9gv9DzYCcqG6btvFe2QexHZSdk3Fb2QMZt5QBk3FZmIeO+chIy3iunIeO9ct6Oj1WegdiZygsQ+1F5CWJnKtchdqYy/nLbnlTWQuxN5S6IPanshNidyh5I3VX2wUL2mCcrh5BzcBIOwFk4CM/BLLwIj8B1eABWv8Kejyub4SHYBg/DPjgKZb2egRnkg3AcPhmegmPwDByCl17xbxwHq7Gq66+0y1lVPWPXd9UuSH1W7YHUV9V+SJ+pykLqq2oKUl9Vs5D6rlqA1Hc=
*/