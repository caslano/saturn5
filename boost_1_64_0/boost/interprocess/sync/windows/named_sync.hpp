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
TMpfrOezseTJXhd70I33ZZknS2LSvJbvwUX0MA7uCsiFtWmWFpL78O+LnLNcDosvhc31/CZMa6w81Hbi9aZ8NuTvN+Srly1bvDKo3etv8RMy/NxZtXzRglXac6uKH9oenyXGOdqkevHbCMO+u13YN5v2FTpmmTYhnw6/V3Tvy/fu+/m9qiN+k+kN8TdFF/KskOud760BjoPL4AqhS1F9bL6VV1YWli2vunPZ4qrK6Bm03em0k3J2pVj6u8V3vZbfn+HynTYnQ/hHoNp3WsryDMyGzihjqPBfl2fSB6rnFGVY72eR80U533Sb9N/TOM+0Rj7nyPMw0TAbEObjMkyTq+LDPL9mvEu7OicTyTvYRNpbPRMj9Myiniqv/96u9rb2alHPY20vZ2G7094Oc7Dwk/gc7G7NnRRjU+xp24v/WixpYxfA9Dn2AfCXeB8g04dw1XK7qVtE8Ebul7wB7lpRB78Umz55JcX8VWUVVctrtOWWZ9+6SH+jsS+9kyb9DJfldmNupNw6zcVQVtqkgnlma3Mop56ZewrW2JPu/sycrqwhbfiO5/zYPlQwfwWX90gZJ/r5vNh24HXexTDQZ/Y910GmxMGeK9CalFfr7ZkBnC399ff1ceDjL/Fgz6hshsFFz9gd2nLKt1q+3NqRZ6rItW7ELe25yMGedbzXQALPDFwPmTq7PeVosKyyvKbcXj7146k26Ke2P+Ee+nFUyJLGRTXu1y7OWsZQanyzU+1jqLFiDGWJD4MDz2OnCYwjlXccZFEgE+5G0aZa4lgBu3NEztG4tL0Yr0NOjt/NcZT0m65vdz3mhQg/i+Gr5SXMdPfymTYqQrpbrOlOoLy0KHUtKVnIwrMTH55HfXR1R8SRxTjUPuU0M76Pz5wr35IrDifE6MiRinPbkizle+N3XVvN8Nj+zpX+l+t0hVziuvakrnPld8tlW5Ahw8Pe5bzY88ZNvSxlkmfI8qm3+mJZsSQo0z0+I84dAEy3KTdfqx/ljLo0MqP1uhTtcxGu7HOpJ5/nx+RnIM0+Rpggxo52vTiG4ZhPP4aBv8THMAjXto6cnG5JH20Q0KRPHcfkONsefhMfxyBc27tsbbq+DQ7ss6XRUzt8LMv5fqeWdHs7PFH0TXa7JNQWX8Fyn88C/0d/RK/3gIMvRlu3V8YjXkoqsH9XOY+NeZ7l5TWLli3V2R7+9Ge9s+VdMfwdsR3C3Swj/QPVuoDf3HMyUFZpL6tqy5ffrn0HVGXPSn2x92SFz+BK++KD4vcV2PM/2eDVueghyV1j3HGzW8o8KsN4L51h+MwwGuXvtyKENHsYbCN9bJf68j3sbzJdv/UPwwGAaXA74EweCPBPKpxC22X4a5Xfly6qVO4q+I78vYTPft9B+dxH3l3wDuI+D3t+HwgOmQNg1hH8Ot0c+XXoJx8RHwOCT+ZJGwcZZSZB5onekElbs97KLTIBz714l+MRyHwD7psSTfcwfhsL1wD3JJ7L4QKog59Oh3Nxxw7fx3mW3iibmnP3cfkp2B/KMiT7ieEPcV9/nk8+zzCfOV7ivRrZNs4EWX8azfqzaOkCb3Woca97voRGD3Wm0UOdoSznDckrwrHWN+VvXY139lflc2c5BzAIAcyBTY5K7iOTByOc4e6ehAuRnypn7Uly6tfznXQfXEkenh828oszKGWLVqxYWbW8bEl5TcVCV2M4GQb+2e9V5H1S8vfbcG6kszEX0yi/G+Trhv81+YswdXMx+vylrIVnkTyG8rcZvmKGdUpyeN0ew2Pa7ctyDG3k6yXiGSnrK+7xyEY9he2mQTA1abpoQpLAppWsbT8oH4D8dCGfGjA5DC1cJ0+JdKQTNfU91cU4j2XDdo8=
*/