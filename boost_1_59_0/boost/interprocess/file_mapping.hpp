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
#include <boost/interprocess/detail/char_wchar_holder.hpp>
#include <boost/move/utility_core.hpp>

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
   file_mapping() BOOST_NOEXCEPT;

   //!Opens a file mapping of file "filename", starting in offset
   //!"file_offset", and the mapping's size will be "size". The mapping
   //!can be opened for read-only "read_only" or read-write "read_write"
   //!modes. Throws interprocess_exception on error.
   file_mapping(const char *filename, mode_t mode);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Opens a file mapping of file "filename", starting in offset
   //!"file_offset", and the mapping's size will be "size". The mapping
   //!can be opened for read-only "read_only" or read-write "read_write"
   //!modes. Throws interprocess_exception on error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   file_mapping(const wchar_t *filename, mode_t mode);
   #endif

   //!Moves the ownership of "moved"'s file mapping object to *this.
   //!After the call, "moved" does not represent any file mapping object.
   //!Does not throw
   file_mapping(BOOST_RV_REF(file_mapping) moved) BOOST_NOEXCEPT
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
      ,  m_mode(read_only)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file mapping to *this.
   //!After the call, "moved" does not represent any file mapping.
   //!Does not throw
   file_mapping &operator=(BOOST_RV_REF(file_mapping) moved) BOOST_NOEXCEPT
   {
      file_mapping tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to file_mappings.
   //!Does not throw.
   void swap(file_mapping &other) BOOST_NOEXCEPT;

   //!Returns access mode
   //!used in the constructor
   mode_t get_mode() const BOOST_NOEXCEPT;

   //!Obtains the mapping handle
   //!to be used with mapped_region
   mapping_handle_t get_mapping_handle() const BOOST_NOEXCEPT;

   //!Destroys the file mapping. All mapped regions created from this are still
   //!valid. Does not throw
   ~file_mapping();

   //!Returns the name of the file
   //!used in the constructor.
   const char *get_name() const BOOST_NOEXCEPT;

   //!Removes the file named "filename" even if it's been memory mapped.
   //!Returns true on success.
   //!The function might fail in some operating systems if the file is
   //!being used other processes and no deletion permission was shared.
   static bool remove(const char *filename);

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Removes the file named "filename" even if it's been memory mapped.
   //!Returns true on success.
   //!The function might fail in some operating systems if the file is
   //!being used other processes and no deletion permission was shared.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   static bool remove(const wchar_t *filename);
   #endif

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Closes a previously opened file mapping. Never throws.
   void priv_close();
   file_handle_t  m_handle;
   mode_t         m_mode;
   char_wchar_holder    m_filename;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline file_mapping::file_mapping() BOOST_NOEXCEPT
   :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   ,  m_mode(read_only)
{}

inline file_mapping::~file_mapping()
{  this->priv_close(); }

inline const char *file_mapping::get_name() const BOOST_NOEXCEPT
{  return m_filename.getn(); }

inline void file_mapping::swap(file_mapping &other) BOOST_NOEXCEPT
{
   (simple_swap)(m_handle, other.m_handle);
   (simple_swap)(m_mode, other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t file_mapping::get_mapping_handle() const BOOST_NOEXCEPT
{  return ipcdetail::mapping_handle_from_file_handle(m_handle);  }

inline mode_t file_mapping::get_mode() const BOOST_NOEXCEPT
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

#ifdef BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES
inline file_mapping::file_mapping
   (const wchar_t *filename, mode_t mode)
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

inline bool file_mapping::remove(const wchar_t *filename)
{  return ipcdetail::delete_file(filename);  }

#endif


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