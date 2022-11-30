//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP
#define BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

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
#include <boost/interprocess/creation_tags.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/simple_swap.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail{

class file_wrapper
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_MOVABLE_BUT_NOT_COPYABLE(file_wrapper)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   //!Default constructor.
   //!Represents an empty file_wrapper.
   file_wrapper();

   //!Creates a file object with name "name" and mode "mode", with the access mode "mode"
   //!If the file previously exists, throws an error.
   file_wrapper(create_only_t, const char *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   //!Tries to create a file with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   file_wrapper(open_or_create_t, const char *name, mode_t mode, const permissions &perm  = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, perm);  }

   //!Tries to open a file with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   file_wrapper(open_only_t, const char *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, permissions());  }

   #if defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //!Creates a file object with name "name" and mode "mode", with the access mode "mode"
   //!If the file previously exists, throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   file_wrapper(create_only_t, const wchar_t *name, mode_t mode, const permissions &perm = permissions())
   {  this->priv_open_or_create(ipcdetail::DoCreate, name, mode, perm);  }

   //!Tries to create a file with name "name" and mode "mode", with the
   //!access mode "mode". If the file previously exists, it tries to open it with mode "mode".
   //!Otherwise throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   file_wrapper(open_or_create_t, const wchar_t *name, mode_t mode, const permissions &perm  = permissions())
   {  this->priv_open_or_create(ipcdetail::DoOpenOrCreate, name, mode, perm);  }

   //!Tries to open a file with name "name", with the access mode "mode".
   //!If the file does not previously exist, it throws an error.
   //! 
   //!Note: This function is only available on operating systems with
   //!      native wchar_t APIs (e.g. Windows).
   file_wrapper(open_only_t, const wchar_t *name, mode_t mode)
   {  this->priv_open_or_create(ipcdetail::DoOpen, name, mode, permissions());  }

   #endif   //defined(BOOST_INTERPROCESS_WCHAR_NAMED_RESOURCES) || defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //!Moves the ownership of "moved"'s file to *this.
   //!After the call, "moved" does not represent any file.
   //!Does not throw
   file_wrapper(BOOST_RV_REF(file_wrapper) moved)
      :  m_handle(file_handle_t(ipcdetail::invalid_file()))
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s file to *this.
   //!After the call, "moved" does not represent any file.
   //!Does not throw
   file_wrapper &operator=(BOOST_RV_REF(file_wrapper) moved)
   {
      file_wrapper tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps to file_wrappers.
   //!Does not throw
   void swap(file_wrapper &other);

   //!Erases a file from the system.
   //!Returns false on error. Never throws
   static bool remove(const char *name);

   //!Sets the size of the file
   void truncate(offset_t length);

   //!Closes the
   //!file
   ~file_wrapper();

   //!Returns the name of the file
   //!used in the constructor
   const char *get_name() const;

   //!Returns the name of the file
   //!used in the constructor
   bool get_size(offset_t &size) const;

   //!Returns access mode
   //!used in the constructor
   mode_t get_mode() const;

   //!Get mapping handle
   //!to use with mapped_region
   mapping_handle_t get_mapping_handle() const;

   private:
   //!Closes a previously opened file mapping. Never throws.
   void priv_close();
   //!Closes a previously opened file mapping. Never throws.
   template <class CharT>
   bool priv_open_or_create(ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, const permissions &perm);

   file_handle_t  m_handle;
   mode_t         m_mode;
};

inline file_wrapper::file_wrapper()
   : m_handle(file_handle_t(ipcdetail::invalid_file()))
   , m_mode(read_only)
{}

inline file_wrapper::~file_wrapper()
{  this->priv_close(); }

inline bool file_wrapper::get_size(offset_t &size) const
{  return get_file_size((file_handle_t)m_handle, size);  }

inline void file_wrapper::swap(file_wrapper &other)
{
   (simple_swap)(m_handle,  other.m_handle);
   (simple_swap)(m_mode,    other.m_mode);
}

inline mapping_handle_t file_wrapper::get_mapping_handle() const
{  return mapping_handle_from_file_handle(m_handle);  }

inline mode_t file_wrapper::get_mode() const
{  return m_mode; }

template <class CharT>
inline bool file_wrapper::priv_open_or_create
   ( ipcdetail::create_enum_t type, const CharT *filename, mode_t mode, const permissions &perm)
{
   if(mode != read_only && mode != read_write){
      error_info err(mode_error);
      throw interprocess_exception(err);
   }

   //Open file existing native API to obtain the handle
   switch(type){
      case ipcdetail::DoOpen:
         m_handle = open_existing_file(filename, mode);
      break;
      case ipcdetail::DoCreate:
         m_handle = create_new_file(filename, mode, perm);
      break;
      case ipcdetail::DoOpenOrCreate:
         m_handle = create_or_open_file(filename, mode, perm);
      break;
      default:
         {
            error_info err = other_error;
            throw interprocess_exception(err);
         }
   }

   //Check for error
   if(m_handle == invalid_file()){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   m_mode = mode;
   return true;
}

inline bool file_wrapper::remove(const char *filename)
{  return delete_file(filename); }

inline void file_wrapper::truncate(offset_t length)
{
   if(!truncate_file(m_handle, (std::size_t)length)){
      error_info err(system_error_code());
      throw interprocess_exception(err);
   }
}

inline void file_wrapper::priv_close()
{
   if(m_handle != invalid_file()){
      close_file(m_handle);
      m_handle = invalid_file();
   }
}

}  //namespace ipcdetail{
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_FILE_WRAPPER_HPP

/* file_wrapper.hpp
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
*/