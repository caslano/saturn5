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
   bool priv_open_or_create(ipcdetail::create_enum_t type, const char *filename, mode_t mode, const permissions &perm);

   file_handle_t  m_handle;
   mode_t         m_mode;
   std::string    m_filename;
};

inline file_wrapper::file_wrapper()
   : m_handle(file_handle_t(ipcdetail::invalid_file()))
   , m_mode(read_only), m_filename()
{}

inline file_wrapper::~file_wrapper()
{  this->priv_close(); }

inline const char *file_wrapper::get_name() const
{  return m_filename.c_str(); }

inline bool file_wrapper::get_size(offset_t &size) const
{  return get_file_size((file_handle_t)m_handle, size);  }

inline void file_wrapper::swap(file_wrapper &other)
{
   (simple_swap)(m_handle,  other.m_handle);
   (simple_swap)(m_mode,    other.m_mode);
   m_filename.swap(other.m_filename);
}

inline mapping_handle_t file_wrapper::get_mapping_handle() const
{  return mapping_handle_from_file_handle(m_handle);  }

inline mode_t file_wrapper::get_mode() const
{  return m_mode; }

inline bool file_wrapper::priv_open_or_create
   (ipcdetail::create_enum_t type,
    const char *filename,
    mode_t mode,
    const permissions &perm = permissions())
{
   m_filename = filename;

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
   if(!truncate_file(m_handle, length)){
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
cFtiaOG6mqsTDwZk+eZWGiw2YvNobHu7Wcc8zMvYlk3IbnFLdQ99PsYrNo200u78Enc3d8otwhbwYNSOFySMtuCOOuq6fyHCaflUojluYS8GiwSnuCXrF9GcGF9Qv6gX68XxhMeZxbycoPT7gEM4PZDy86SghhoO21/Sy9N4yVy3j3MdeJEft4EezdElikv3aHo1Ln2K+FIBvAfzt3QQl/5CfpkAT7Ssv2WJl0s6jLOcFzOHZ+T7vLwos9Noim/okc3liZdLLcz/Cl5MPTdZ0cTb/JzIi8kMo52VNefpv6tIvOGoeW1VibXpHs1q+rdn/ooTrt+xS79xOBYJiclA1mnCx4mJQHLJALfMspJL+bml+lS8fh8nBn/JreHnyu1akcu8puRqQLB/0hJrV7GbSTtr+XB0ANtZmzjPHoMBwugWH9seNDFj319G4q7dLtVxvYPtJBvExb/G5P3VIeKRkLbWYUyLCR8mPNDWchI3xp+8wvT4sy5j+vqV/LKeiTut7cyxaX3FtQSMdjaQmJqPyc6GGleTgizTRpJTczXhG2vc0x5HJL5VE39vIn+3RzHepvq3pw9YEt+moK4XN2OsVacdZfqt4pTvgodXb0JGblRzegjgtIrMwfWbSr8kMVicSsyWGGRW+qPM2NaFStsW0yLjY4xv47Q2J+eSjc0Jx0kKBlLUOoit228NpgbN551bmPhYsy73VW/px2nLF8apGJz5bKPqw2XaNYk3bRq4OY26wBPxXN6ze4ifx0jOu4MI7W2luJJtxmlK3PshC4zjSs6XTkvh9UA6bcnxziFZl1sjrjYP4dy4DWKp4Xy6P52A5jKUHUgn0qmceZ9u2w4aaWO7Drx5Xbo9agbjCXFRKrfhcRl3kJy68CZ8Rw+un2fuZOK4oua747grj+LubGpERtgHuyi836kVKvTcRmHpmsPz8G4KW5duurHd3SUu9nW0q2pP+h6E56wE9CC4B5iGO9LmNfueIbzcC7dXCGfu5dw7hKfBWRSYNPtITYoagl0SX7yVDY00+4Zr7Jqh2S9Ug2dNREtCzf5as7VdqTdIox6UouYAqRm2i7bTaA3T1hcWdaPmwHCNdBudBwvXYK3TwEL7Sw8O16k9coeE8+jmRYA/1OCdhgNeVg5Y296O3s8Nwx1qD/tNLWXN4fciH+7Vcu156+WIUI2qF0zzyFANpdWAihEtQfrsqHDtloWmIxNGm0d31pHhQkXcmkXtMb+jlekvAdpjf09bbzpj4CFp+7jf0zftLV3WHt9ZK82qejrhN7SudBzbPbGD1t5SZsJRZ0FO+g2tmf7JHXSwC0Q3KE7/lI5aXRcu+/fU39HiVnW7qdrgaaF6cgF4ANM//Tc0jYLr0vqDz8n9ltb49tGZoTrcaoD8WZLP4RezZKOvl/ia7GzFQ3lokOEnevxMz8M3RXzlV6k5N6jR/mTNeZ001ZJo1ljm8/2aYOdD3QVBna6TQgvWpKS7MKjz1x3Wy0VBHQ7GUlc0ntddHKaF/5X8JUGeTx5Qni7txEMBaeYh3WWsExft3VbCboqvMxVhWKfvPrmynVzu0Q3bW8NyXlx5CMMkpTn1ClOHJSL8Si/elHvarvLgTdm4RFvGdK8O53U75nq/xtD1+CYGOd9f69HovF3nxdUe0+tNXKdNMeVzRUMjK1KdrzM4vpFguVW4TQHHB2T8mwyNIjn+zR6uBVdXhaYWUd5vkZpivdqgjcz0TJFx3jhAzxRNDJdMhN9u4mm9V+8OjeslAdu6kzk1CXF93uXD1WqDy3R3GK9qk2zcE64BI/zcUfHOmF6HEHefl+M2z88emVOzMfvqAYmXhU8onw8yhh3ZO+ip73Y85NHojiY=
*/