//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP
#define BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP

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
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/sync/windows/sync_utils.hpp>
#include <boost/interprocess/errors.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <string>
#include <boost/assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

class windows_named_sync_interface
{
   public:
   virtual std::size_t get_data_size() const = 0;
   virtual const void *buffer_with_final_data_to_file() = 0;
   virtual const void *buffer_with_init_data_to_file() = 0;
   virtual void *buffer_to_store_init_data_from_file() = 0;
   virtual bool open(create_enum_t creation_type, const char *id_name) = 0;
   virtual void close() = 0;
   virtual ~windows_named_sync_interface() = 0;
};

inline windows_named_sync_interface::~windows_named_sync_interface()
{}

class windows_named_sync
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Non-copyable
   windows_named_sync(const windows_named_sync &);
   windows_named_sync &operator=(const windows_named_sync &);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   windows_named_sync();
   void open_or_create(create_enum_t creation_type, const char *name, const permissions &perm, windows_named_sync_interface &sync_interface);
   void close(windows_named_sync_interface &sync_interface);

   static bool remove(const char *name);

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   void *m_file_hnd;

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

inline windows_named_sync::windows_named_sync()
   : m_file_hnd(winapi::invalid_handle_value)
{}

inline void windows_named_sync::close(windows_named_sync_interface &sync_interface)
{
   const std::size_t buflen = sync_interface.get_data_size();
   const std::size_t sizeof_file_info = sizeof(sync_id::internal_type) + buflen;
   winapi::interprocess_overlapped overlapped;
   if(winapi::lock_file_ex
      (m_file_hnd, winapi::lockfile_exclusive_lock, 0, sizeof_file_info, 0, &overlapped)){
      if(winapi::set_file_pointer_ex(m_file_hnd, sizeof(sync_id::internal_type), 0, winapi::file_begin)){
         const void *buf = sync_interface.buffer_with_final_data_to_file();

         unsigned long written_or_read = 0;
         if(winapi::write_file(m_file_hnd, buf, buflen, &written_or_read, 0)){
            //...
         }
      }
   }
   sync_interface.close();
   if(m_file_hnd != winapi::invalid_handle_value){
      winapi::close_handle(m_file_hnd);
      m_file_hnd = winapi::invalid_handle_value;
   }
}

inline void windows_named_sync::open_or_create
   ( create_enum_t creation_type
   , const char *name
   , const permissions &perm
   , windows_named_sync_interface &sync_interface)
{
   std::string aux_str(name);
   m_file_hnd  = winapi::invalid_handle_value;
   //Use a file to emulate POSIX lifetime semantics. After this logic
   //we'll obtain the ID of the native handle to open in aux_str
   {
      create_shared_dir_cleaning_old_and_get_filepath(name, aux_str);
      //Create a file with required permissions.
      m_file_hnd = winapi::create_file
         ( aux_str.c_str()
         , winapi::generic_read | winapi::generic_write
         , creation_type == DoOpen ? winapi::open_existing :
               (creation_type == DoCreate ? winapi::create_new : winapi::open_always)
         , 0
         , (winapi::interprocess_security_attributes*)perm.get_permissions());

      //Obtain OS error in case something has failed
      error_info err;
      bool success = false;
      if(m_file_hnd != winapi::invalid_handle_value){
         //Now lock the file
         const std::size_t buflen = sync_interface.get_data_size();
         typedef __int64 unique_id_type;
         const std::size_t sizeof_file_info = sizeof(unique_id_type) + buflen;
         winapi::interprocess_overlapped overlapped;
         if(winapi::lock_file_ex
            (m_file_hnd, winapi::lockfile_exclusive_lock, 0, sizeof_file_info, 0, &overlapped)){
            __int64 filesize = 0;
            //Obtain the unique id to open the native semaphore.
            //If file size was created
            if(winapi::get_file_size(m_file_hnd, filesize)){
               unsigned long written_or_read = 0;
               unique_id_type unique_id_val;
               if(static_cast<std::size_t>(filesize) != sizeof_file_info){
                  winapi::set_end_of_file(m_file_hnd);
                  winapi::query_performance_counter(&unique_id_val);
                  const void *buf = sync_interface.buffer_with_init_data_to_file();
                  //Write unique ID in file. This ID will be used to calculate the semaphore name
                  if(winapi::write_file(m_file_hnd, &unique_id_val, sizeof(unique_id_val), &written_or_read, 0)  &&
                     written_or_read == sizeof(unique_id_val) &&
                     winapi::write_file(m_file_hnd, buf, buflen, &written_or_read, 0) &&
                     written_or_read == buflen ){
                     success = true;
                  }
                  winapi::get_file_size(m_file_hnd, filesize);
                  BOOST_ASSERT(std::size_t(filesize) == sizeof_file_info);
               }
               else{
                  void *buf = sync_interface.buffer_to_store_init_data_from_file();
                  if(winapi::read_file(m_file_hnd, &unique_id_val, sizeof(unique_id_val), &written_or_read, 0)  &&
                     written_or_read == sizeof(unique_id_val) &&
                     winapi::read_file(m_file_hnd, buf, buflen, &written_or_read, 0)  &&
                     written_or_read == buflen   ){
                     success = true;
                  }
               }
               if(success){
                  //Now create a global semaphore name based on the unique id
                  char unique_id_name[sizeof(unique_id_val)*2+1];
                  std::size_t name_suffix_length = sizeof(unique_id_name);
                  bytes_to_str(&unique_id_val, sizeof(unique_id_val), &unique_id_name[0], name_suffix_length);
                  success = sync_interface.open(creation_type, unique_id_name);
               }
            }

            //Obtain OS error in case something has failed
            err = system_error_code();

            //If this fails we have no possible rollback so don't check the return
            if(!winapi::unlock_file_ex(m_file_hnd, 0, sizeof_file_info, 0, &overlapped)){
               err = system_error_code();
            }
         }
         else{
            //Obtain OS error in case something has failed
            err = system_error_code();
         }
      }
      else{
         err = system_error_code();
      }

      if(!success){
         if(m_file_hnd != winapi::invalid_handle_value){
            winapi::close_handle(m_file_hnd);
            m_file_hnd = winapi::invalid_handle_value;
         }
         //Throw as something went wrong
         throw interprocess_exception(err);
      }
   }
}

inline bool windows_named_sync::remove(const char *name)
{
   try{
      //Make sure a temporary path is created for shared memory
      std::string semfile;
      ipcdetail::shared_filepath(name, semfile);
      return winapi::unlink_file(semfile.c_str());
   }
   catch(...){
      return false;
   }
}

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_WINDOWS_NAMED_SYNC_HPP

/* named_sync.hpp
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
*/