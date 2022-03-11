//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_FILE_MAPPING_HPP
#define BOOST_INTERPROCESS_FILE_MAPPING_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_MAPPED_FILES)
#error "Boost.Interprocess: This platform does not support memory mapped files!"
#endif

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>
#include <boost/move/utility_core.hpp>
#include <string>    //std::string

//!\file
//!Describes file_mapping and mapped region classes

namespace boost {
namespace interprocess {

//!A class that wraps a file-mapping that can be used to
//!create mapped regions from the mapped files
class file_mapping
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_MOVABLE_BUT_NOT_COPYABLE(file_mapping)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructs an empty file mapping.
   //!Does not throw
   file_mapping();

   //!Opens a file mapping of file "filename", starting in offset
   //!"file_offset", and the mapping's size will be "size". The mapping
   //!can be opened for read-only "read_only" or read-write "read_write"
   //!modes. Throws interprocess_exception on error.
   file_mapping(const char *filename, mode_t mode);

   //!Moves the ownership of "moved"'s file mapping object to *this.
   //!After the call, "moved" does not represent any file mapping object.
   //!Does not throw
   file_mapping(BOOST_RV_REF(file_mapping) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file mapping to *this.
   //!After the call, "moved" does not represent any file mapping.
   //!Does not throw
   file_mapping &operator=(BOOST_RV_REF(file_mapping) moved)
   {
      file_mapping tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to file_mappings.
   //!Does not throw.
   void swap(file_mapping &other);

   //!Returns access mode
   //!used in the constructor
   mode_t get_mode() const;

   //!Obtains the mapping handle
   //!to be used with mapped_region
   mapping_handle_t get_mapping_handle() const;

   //!Destroys the file mapping. All mapped regions created from this are still
   //!valid. Does not throw
   ~file_mapping();

   //!Returns the name of the file
   //!used in the constructor.
   const char *get_name() const;

   //!Removes the file named "filename" even if it's been memory mapped.
   //!Returns true on success.
   //!The function might fail in some operating systems if the file is
   //!being used other processes and no deletion permission was shared.
   static bool remove(const char *filename);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Closes a previously opened file mapping. Never throws.
   void priv_close();
   file_handle_t  m_handle;
   mode_t         m_mode;
   std::string    m_filename;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline file_mapping::file_mapping()
   :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   ,  m_mode(read_only)
{}

inline file_mapping::~file_mapping()
{  this->priv_close(); }

inline const char *file_mapping::get_name() const
{  return m_filename.c_str(); }

inline void file_mapping::swap(file_mapping &other)
{
   (simple_swap)(m_handle, other.m_handle);
   (simple_swap)(m_mode, other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t file_mapping::get_mapping_handle() const
{  return ipcdetail::mapping_handle_from_file_handle(m_handle);  }

inline mode_t file_mapping::get_mode() const
{  return m_mode; }

inline file_mapping::file_mapping
   (const char *filename, mode_t mode)
   :  m_filename(filename)
{
   //Check accesses
   if (mode != read_write && mode != read_only){
      error_info err = other_error;
      throw interprocess_exception(err);
   }

   //Open file
   m_handle = ipcdetail::open_existing_file(filename, mode);

   //Check for error
   if(m_handle == ipcdetail::invalid_file()){
      error_info err = system_error_code();
      this->priv_close();
      throw interprocess_exception(err);
   }
   m_mode = mode;
}

inline bool file_mapping::remove(const char *filename)
{  return ipcdetail::delete_file(filename);  }

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void file_mapping::priv_close()
{
   if(m_handle != ipcdetail::invalid_file()){
      ipcdetail::close_file(m_handle);
      m_handle = ipcdetail::invalid_file();
   }
}

//!A class that stores the name of a file
//!and tries to remove it in its destructor
//!Useful to remove temporary files in the presence
//!of exceptions
class remove_file_on_destroy
{
   const char * m_name;
   public:
   remove_file_on_destroy(const char *name)
      :  m_name(name)
   {}

   ~remove_file_on_destroy()
   {  ipcdetail::delete_file(m_name);  }
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_FILE_MAPPING_HPP

/* file_mapping.hpp
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
*/