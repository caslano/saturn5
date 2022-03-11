//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MAPPED_REGION_HPP
#define BOOST_INTERPROCESS_MAPPED_REGION_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/move/adl_move_swap.hpp>

//Some Unixes use caddr_t instead of void * in madvise
//              SunOS                                 Tru64                               HP-UX                    AIX
#if defined(sun) || defined(__sun) || defined(__osf__) || defined(__osf) || defined(_hpux) || defined(hpux) || defined(_AIX)
#define BOOST_INTERPROCESS_MADVISE_USES_CADDR_T
#include <sys/types.h>
#endif

//A lot of UNIXes have destructive semantics for MADV_DONTNEED, so
//we need to be careful to allow it.
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__APPLE__)
#define BOOST_INTERPROCESS_MADV_DONTNEED_HAS_NONDESTRUCTIVE_SEMANTICS
#endif

#if defined (BOOST_INTERPROCESS_WINDOWS)
#  include <boost/interprocess/detail/win32_api.hpp>
#  include <boost/interprocess/sync/windows/sync_utils.hpp>
#else
#  ifdef BOOST_HAS_UNISTD_H
#    include <fcntl.h>
#    include <sys/mman.h>     //mmap
#    include <unistd.h>
#    include <sys/stat.h>
#    include <sys/types.h>
#    if defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
#      include <sys/shm.h>      //System V shared memory...
#    endif
#    include <boost/assert.hpp>
#  else
#    error Unknown platform
#  endif

#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

//!\file
//!Describes mapped region class

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

//Solaris declares madvise only in some configurations but defines MADV_XXX, a bit confusing.
//Predeclare it here to avoid any compilation error
#if (defined(sun) || defined(__sun)) && defined(MADV_NORMAL)
extern "C" int madvise(caddr_t, size_t, int);
#endif

namespace ipcdetail{ class interprocess_tester; }
namespace ipcdetail{ class raw_mapped_region_creator; }

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!The mapped_region class represents a portion or region created from a
//!memory_mappable object.
//!
//!The OS can map a region bigger than the requested one, as region must
//!be multiple of the page size, but mapped_region will always refer to
//!the region specified by the user.
class mapped_region
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   //Non-copyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(mapped_region)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   //!Creates a mapping region of the mapped memory "mapping", starting in
   //!offset "offset", and the mapping's size will be "size". The mapping
   //!can be opened for read only, read-write or copy-on-write.
   //!
   //!If an address is specified, both the offset and the address must be
   //!multiples of the page size.
   //!
   //!The map is created using "default_map_options". This flag is OS
   //!dependant and it should not be changed unless the user needs to
   //!specify special options.
   //!
   //!In Windows systems "map_options" is a DWORD value passed as
   //!"dwDesiredAccess" to "MapViewOfFileEx". If "default_map_options" is passed
   //!it's initialized to zero. "map_options" is XORed with FILE_MAP_[COPY|READ|WRITE].
   //!
   //!In UNIX systems and POSIX mappings "map_options" is an int value passed as "flags"
   //!to "mmap". If "default_map_options" is specified it's initialized to MAP_NOSYNC
   //!if that option exists and to zero otherwise. "map_options" XORed with MAP_PRIVATE or MAP_SHARED.
   //!
   //!In UNIX systems and XSI mappings "map_options" is an int value passed as "shmflg"
   //!to "shmat". If "default_map_options" is specified it's initialized to zero.
   //!"map_options" is XORed with SHM_RDONLY if needed.
   //!
   //!The OS could allocate more pages than size/page_size(), but get_address()
   //!will always return the address passed in this function (if not null) and
   //!get_size() will return the specified size.
   template<class MemoryMappable>
   mapped_region(const MemoryMappable& mapping
                ,mode_t mode
                ,offset_t offset = 0
                ,std::size_t size = 0
                ,const void *address = 0
                ,map_options_t map_options = default_map_options);

   //!Default constructor. Address will be 0 (nullptr).
   //!Size will be 0.
   //!Does not throw
   mapped_region();

   //!Move constructor. *this will be constructed taking ownership of "other"'s
   //!region and "other" will be left in default constructor state.
   mapped_region(BOOST_RV_REF(mapped_region) other)
   #if defined (BOOST_INTERPROCESS_WINDOWS)
   :  m_base(0), m_size(0)
   ,  m_page_offset(0)
   ,  m_mode(read_only)
   ,  m_file_or_mapping_hnd(ipcdetail::invalid_file())
   #else
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only), m_is_xsi(false)
   #endif
   {  this->swap(other);   }

   //!Destroys the mapped region.
   //!Does not throw
   ~mapped_region();

   //!Move assignment. If *this owns a memory mapped region, it will be
   //!destroyed and it will take ownership of "other"'s memory mapped region.
   mapped_region &operator=(BOOST_RV_REF(mapped_region) other)
   {
      mapped_region tmp(boost::move(other));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the mapped_region with another
   //!mapped region
   void swap(mapped_region &other);

   //!Returns the size of the mapping. Never throws.
   std::size_t get_size() const;

   //!Returns the base address of the mapping.
   //!Never throws.
   void*       get_address() const;

   //!Returns the mode of the mapping used to construct the mapped region.
   //!Never throws.
   mode_t get_mode() const;

   //!Flushes to the disk a byte range within the mapped memory.
   //!If 'async' is true, the function will return before flushing operation is completed
   //!If 'async' is false, function will return once data has been written into the underlying
   //!device (i.e., in mapped files OS cached information is written to disk).
   //!Never throws. Returns false if operation could not be performed.
   bool flush(std::size_t mapping_offset = 0, std::size_t numbytes = 0, bool async = true);

   //!Shrinks current mapped region. If after shrinking there is no longer need for a previously
   //!mapped memory page, accessing that page can trigger a segmentation fault.
   //!Depending on the OS, this operation might fail (XSI shared memory), it can decommit storage
   //!and free a portion of the virtual address space (e.g.POSIX) or this
   //!function can release some physical memory wihout freeing any virtual address space(Windows).
   //!Returns true on success. Never throws.
   bool shrink_by(std::size_t bytes, bool from_back = true);

   //!This enum specifies region usage behaviors that an application can specify
   //!to the mapped region implementation.
   enum advice_types{
      //!Specifies that the application has no advice to give on its behavior with respect to
      //!the region. It is the default characteristic if no advice is given for a range of memory.
      advice_normal,
      //!Specifies that the application expects to access the region sequentially from
      //!lower addresses to higher addresses. The implementation can lower the priority of
      //!preceding pages within the region once a page have been accessed.
      advice_sequential,
      //!Specifies that the application expects to access the region in a random order,
      //!and prefetching is likely not advantageous.
      advice_random,
      //!Specifies that the application expects to access the region in the near future.
      //!The implementation can prefetch pages of the region.
      advice_willneed,
      //!Specifies that the application expects that it will not access the region in the near future.
      //!The implementation can unload pages within the range to save system resources.
      advice_dontneed
   };

   //!Advises the implementation on the expected behavior of the application with respect to the data
   //!in the region. The implementation may use this information to optimize handling of the region data.
   //!This function has no effect on the semantics of access to memory in the region, although it may affect
   //!the performance of access.
   //!If the advise type is not known to the implementation, the function returns false. True otherwise.
   bool advise(advice_types advise);

   //!Returns the size of the page. This size is the minimum memory that
   //!will be used by the system when mapping a memory mappable source and
   //!will restrict the address and the offset to map.
   static std::size_t get_page_size();

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Closes a previously opened memory mapping. Never throws
   void priv_close();

   void* priv_map_address()  const;
   std::size_t priv_map_size()  const;
   bool priv_flush_param_check(std::size_t mapping_offset, void *&addr, std::size_t &numbytes) const;
   bool priv_shrink_param_check(std::size_t bytes, bool from_back, void *&shrink_page_start, std::size_t &shrink_page_bytes);
   static void priv_size_from_mapping_size
      (offset_t mapping_size, offset_t offset, offset_t page_offset, std::size_t &size);
   static offset_t priv_page_offset_addr_fixup(offset_t page_offset, const void *&addr);

   template<int dummy>
   struct page_size_holder
   {
      static const std::size_t PageSize;
      static std::size_t get_page_size();
   };

   void*             m_base;
   std::size_t       m_size;
   std::size_t       m_page_offset;
   mode_t            m_mode;
   #if defined(BOOST_INTERPROCESS_WINDOWS)
   file_handle_t     m_file_or_mapping_hnd;
   #else
   bool              m_is_xsi;
   #endif

   friend class ipcdetail::interprocess_tester;
   friend class ipcdetail::raw_mapped_region_creator;
   void dont_close_on_destruction();
   #if defined(BOOST_INTERPROCESS_WINDOWS) && !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)
   template<int Dummy>
   static void destroy_syncs_in_range(const void *addr, std::size_t size);
   #endif
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

inline void swap(mapped_region &x, mapped_region &y)
{  x.swap(y);  }

inline mapped_region::~mapped_region()
{  this->priv_close(); }

inline std::size_t mapped_region::get_size()  const
{  return m_size; }

inline mode_t mapped_region::get_mode()  const
{  return m_mode;   }

inline void*    mapped_region::get_address()  const
{  return m_base; }

inline void*    mapped_region::priv_map_address()  const
{  return static_cast<char*>(m_base) - m_page_offset; }

inline std::size_t mapped_region::priv_map_size()  const
{  return m_size + m_page_offset; }

inline bool mapped_region::priv_flush_param_check
   (std::size_t mapping_offset, void *&addr, std::size_t &numbytes) const
{
   //Check some errors
   if(m_base == 0)
      return false;

   if(mapping_offset >= m_size || (mapping_offset + numbytes) > m_size){
      return false;
   }

   //Update flush size if the user does not provide it
   if(numbytes == 0){
      numbytes = m_size - mapping_offset;
   }
   addr = (char*)this->priv_map_address() + mapping_offset;
   numbytes += m_page_offset;
   return true;
}

inline bool mapped_region::priv_shrink_param_check
   (std::size_t bytes, bool from_back, void *&shrink_page_start, std::size_t &shrink_page_bytes)
{
   //Check some errors
   if(m_base == 0 || bytes > m_size){
      return false;
   }
   else if(bytes == m_size){
      this->priv_close();
      return true;
   }
   else{
      const std::size_t page_size = mapped_region::get_page_size();
      if(from_back){
         const std::size_t new_pages = (m_size + m_page_offset - bytes - 1)/page_size + 1;
         shrink_page_start = static_cast<char*>(this->priv_map_address()) + new_pages*page_size;
         shrink_page_bytes = m_page_offset + m_size - new_pages*page_size;
         m_size -= bytes;
      }
      else{
         shrink_page_start = this->priv_map_address();
         m_page_offset += bytes;
         shrink_page_bytes = (m_page_offset/page_size)*page_size;
         m_page_offset = m_page_offset % page_size;
         m_size -= bytes;
         m_base  = static_cast<char *>(m_base) + bytes;
         BOOST_ASSERT(shrink_page_bytes%page_size == 0);
      }
      return true;
   }
}

inline void mapped_region::priv_size_from_mapping_size
   (offset_t mapping_size, offset_t offset, offset_t page_offset, std::size_t &size)
{
   //Check if mapping size fits in the user address space
   //as offset_t is the maximum file size and its signed.
   if(mapping_size < offset ||
      boost::uintmax_t(mapping_size - (offset - page_offset)) >
         boost::uintmax_t(std::size_t(-1))){
      error_info err(size_error);
      throw interprocess_exception(err);
   }
   size = static_cast<std::size_t>(mapping_size - (offset - page_offset));
}

inline offset_t mapped_region::priv_page_offset_addr_fixup(offset_t offset, const void *&address)
{
   //We can't map any offset so we have to obtain system's
   //memory granularity
   const std::size_t page_size  = mapped_region::get_page_size();

   //We calculate the difference between demanded and valid offset
   //(always less than a page in std::size_t, thus, representable by std::size_t)
   const std::size_t page_offset =
      static_cast<std::size_t>(offset - (offset / page_size) * page_size);
   //Update the mapping address
   if(address){
      address = static_cast<const char*>(address) - page_offset;
   }
   return page_offset;
}

#if defined (BOOST_INTERPROCESS_WINDOWS)

inline mapped_region::mapped_region()
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only)
   ,  m_file_or_mapping_hnd(ipcdetail::invalid_file())
{}

template<int dummy>
inline std::size_t mapped_region::page_size_holder<dummy>::get_page_size()
{
   winapi::system_info info;
   winapi::get_system_info(&info);
   return std::size_t(info.dwAllocationGranularity);
}

template<class MemoryMappable>
inline mapped_region::mapped_region
   (const MemoryMappable &mapping
   ,mode_t mode
   ,offset_t offset
   ,std::size_t size
   ,const void *address
   ,map_options_t map_options)
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(mode)
   ,  m_file_or_mapping_hnd(ipcdetail::invalid_file())
{
   mapping_handle_t mhandle = mapping.get_mapping_handle();
   {
      file_handle_t native_mapping_handle = 0;

      //Set accesses
      //For "create_file_mapping"
      unsigned long protection = 0;
      //For "mapviewoffile"
      unsigned long map_access = map_options == default_map_options ? 0 : map_options;

      switch(mode)
      {
         case read_only:
         case read_private:
            protection   |= winapi::page_readonly;
            map_access   |= winapi::file_map_read;
         break;
         case read_write:
            protection   |= winapi::page_readwrite;
            map_access   |= winapi::file_map_write;
         break;
         case copy_on_write:
            protection   |= winapi::page_writecopy;
            map_access   |= winapi::file_map_copy;
         break;
         default:
            {
               error_info err(mode_error);
               throw interprocess_exception(err);
            }
         break;
      }

      //For file mapping (including emulated shared memory through temporary files),
      //the device is a file handle so we need to obtain file's size and call create_file_mapping
      //to obtain the mapping handle.
      //For files we don't need the file mapping after mapping the memory, as the file is there
      //so we'll program the handle close
      void * handle_to_close = winapi::invalid_handle_value;
      if(!mhandle.is_shm){
         //Create mapping handle
         native_mapping_handle = winapi::create_file_mapping
            ( ipcdetail::file_handle_from_mapping_handle(mapping.get_mapping_handle())
            , protection, 0, 0, 0);

         //Check if all is correct
         if(!native_mapping_handle){
            error_info err = winapi::get_last_error();
            throw interprocess_exception(err);
         }
         handle_to_close = native_mapping_handle;
      }
      else{
         //For windows_shared_memory the device handle is already a mapping handle
         //and we need to maintain it
         native_mapping_handle = mhandle.handle;
      }
      //RAII handle close on scope exit
      const winapi::handle_closer close_handle(handle_to_close);
      (void)close_handle;

      const offset_t page_offset = priv_page_offset_addr_fixup(offset, address);

      //Obtain mapping size if user provides 0 size
      if(size == 0){
         offset_t mapping_size;
         if(!winapi::get_file_mapping_size(native_mapping_handle, mapping_size)){
            error_info err = winapi::get_last_error();
            throw interprocess_exception(err);
         }
         //This can throw
         priv_size_from_mapping_size(mapping_size, offset, page_offset, size);
      }

      //Map with new offsets and size
      void *base = winapi::map_view_of_file_ex
                                 (native_mapping_handle,
                                 map_access,
                                 offset - page_offset,
                                 static_cast<std::size_t>(page_offset + size),
                                 const_cast<void*>(address));
      //Check error
      if(!base){
         error_info err = winapi::get_last_error();
         throw interprocess_exception(err);
      }

      //Calculate new base for the user
      m_base = static_cast<char*>(base) + page_offset;
      m_page_offset = page_offset;
      m_size = size;
   }
   //Windows shared memory needs the duplication of the handle if we want to
   //make mapped_region independent from the mappable device
   //
   //For mapped files, we duplicate the file handle to be able to FlushFileBuffers
   if(!winapi::duplicate_current_process_handle(mhandle.handle, &m_file_or_mapping_hnd)){
      error_info err = winapi::get_last_error();
      this->priv_close();
      throw interprocess_exception(err);
   }
}

inline bool mapped_region::flush(std::size_t mapping_offset, std::size_t numbytes, bool async)
{
   void *addr;
   if(!this->priv_flush_param_check(mapping_offset, addr, numbytes)){
      return false;
   }
   //Flush it all
   if(!winapi::flush_view_of_file(addr, numbytes)){
      return false;
   }
   //m_file_or_mapping_hnd can be a file handle or a mapping handle.
   //so flushing file buffers has only sense for files...
   else if(!async && m_file_or_mapping_hnd != winapi::invalid_handle_value &&
           winapi::get_file_type(m_file_or_mapping_hnd) == winapi::file_type_disk){
      return winapi::flush_file_buffers(m_file_or_mapping_hnd);
   }
   return true;
}

inline bool mapped_region::shrink_by(std::size_t bytes, bool from_back)
{
   void *shrink_page_start = 0;
   std::size_t shrink_page_bytes = 0;
   if(!this->priv_shrink_param_check(bytes, from_back, shrink_page_start, shrink_page_bytes)){
      return false;
   }
   else if(shrink_page_bytes){
      //In Windows, we can't decommit the storage or release the virtual address space,
      //the best we can do is try to remove some memory from the process working set.
      //With a bit of luck we can free some physical memory.
      unsigned long old_protect_ignored;
      bool b_ret = winapi::virtual_unlock(shrink_page_start, shrink_page_bytes)
                           || (winapi::get_last_error() == winapi::error_not_locked);
      (void)old_protect_ignored;
      //Change page protection to forbid any further access
      b_ret = b_ret && winapi::virtual_protect
         (shrink_page_start, shrink_page_bytes, winapi::page_noaccess, old_protect_ignored);
      return b_ret;
   }
   else{
      return true;
   }
}

inline bool mapped_region::advise(advice_types)
{
   //Windows has no madvise/posix_madvise equivalent
   return false;
}

inline void mapped_region::priv_close()
{
   if(m_base){
      void *addr = this->priv_map_address();
      #if !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)
      mapped_region::destroy_syncs_in_range<0>(addr, m_size);
      #endif
      winapi::unmap_view_of_file(addr);
      m_base = 0;
   }
   if(m_file_or_mapping_hnd != ipcdetail::invalid_file()){
      winapi::close_handle(m_file_or_mapping_hnd);
      m_file_or_mapping_hnd = ipcdetail::invalid_file();
   }
}

inline void mapped_region::dont_close_on_destruction()
{}

#else    //#if defined (BOOST_INTERPROCESS_WINDOWS)

inline mapped_region::mapped_region()
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only), m_is_xsi(false)
{}

template<int dummy>
inline std::size_t mapped_region::page_size_holder<dummy>::get_page_size()
{  return std::size_t(sysconf(_SC_PAGESIZE)); }

template<class MemoryMappable>
inline mapped_region::mapped_region
   ( const MemoryMappable &mapping
   , mode_t mode
   , offset_t offset
   , std::size_t size
   , const void *address
   , map_options_t map_options)
   : m_base(0), m_size(0), m_page_offset(0), m_mode(mode), m_is_xsi(false)
{
   mapping_handle_t map_hnd = mapping.get_mapping_handle();

   //Some systems dont' support XSI shared memory
   #ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
   if(map_hnd.is_xsi){
      //Get the size
      ::shmid_ds xsi_ds;
      int ret = ::shmctl(map_hnd.handle, IPC_STAT, &xsi_ds);
      if(ret == -1){
         error_info err(system_error_code());
         throw interprocess_exception(err);
      }
      //Compare sizess
      if(size == 0){
         size = (std::size_t)xsi_ds.shm_segsz;
      }
      else if(size != (std::size_t)xsi_ds.shm_segsz){
         error_info err(size_error);
         throw interprocess_exception(err);
      }
      //Calculate flag
      int flag = map_options == default_map_options ? 0 : map_options;
      if(m_mode == read_only){
         flag |= SHM_RDONLY;
      }
      else if(m_mode != read_write){
         error_info err(mode_error);
         throw interprocess_exception(err);
      }
      //Attach memory
      //Some old shmat implementation take the address as a non-const void pointer
      //so uncast it to make code portable.
      void *const final_address = const_cast<void *>(address);
      void *base = ::shmat(map_hnd.handle, final_address, flag);
      if(base == (void*)-1){
         error_info err(system_error_code());
         throw interprocess_exception(err);
      }
      //Update members
      m_base   = base;
      m_size   = size;
      m_mode   = mode;
      m_page_offset = 0;
      m_is_xsi = true;
      return;
   }
   #endif   //ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS

   //We calculate the difference between demanded and valid offset
   const offset_t page_offset = priv_page_offset_addr_fixup(offset, address);

   if(size == 0){
      struct ::stat buf;
      if(0 != fstat(map_hnd.handle, &buf)){
         error_info err(system_error_code());
         throw interprocess_exception(err);
      }
      //This can throw
      priv_size_from_mapping_size(buf.st_size, offset, page_offset, size);
   }

   #ifdef MAP_NOSYNC
      #define BOOST_INTERPROCESS_MAP_NOSYNC MAP_NOSYNC
   #else
      #define BOOST_INTERPROCESS_MAP_NOSYNC 0
   #endif   //MAP_NOSYNC

   //Create new mapping
   int prot    = 0;
   int flags   = map_options == default_map_options ? BOOST_INTERPROCESS_MAP_NOSYNC : map_options;

   #undef BOOST_INTERPROCESS_MAP_NOSYNC

   switch(mode)
   {
      case read_only:
         prot  |= PROT_READ;
         flags |= MAP_SHARED;
      break;

      case read_private:
         prot  |= (PROT_READ);
         flags |= MAP_PRIVATE;
      break;

      case read_write:
         prot  |= (PROT_WRITE | PROT_READ);
         flags |= MAP_SHARED;
      break;

      case copy_on_write:
         prot  |= (PROT_WRITE | PROT_READ);
         flags |= MAP_PRIVATE;
      break;

      default:
         {
            error_info err(mode_error);
            throw interprocess_exception(err);
         }
      break;
   }

   //Map it to the address space
   void* base = mmap ( const_cast<void*>(address)
                     , static_cast<std::size_t>(page_offset + size)
                     , prot
                     , flags
                     , mapping.get_mapping_handle().handle
                     , offset - page_offset);

   //Check if mapping was successful
   if(base == MAP_FAILED){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   //Calculate new base for the user
   m_base = static_cast<char*>(base) + page_offset;
   m_page_offset = page_offset;
   m_size   = size;

   //Check for fixed mapping error
   if(address && (base != address)){
      error_info err(busy_error);
      this->priv_close();
      throw interprocess_exception(err);
   }
}

inline bool mapped_region::shrink_by(std::size_t bytes, bool from_back)
{
   void *shrink_page_start = 0;
   std::size_t shrink_page_bytes = 0;
   if(m_is_xsi || !this->priv_shrink_param_check(bytes, from_back, shrink_page_start, shrink_page_bytes)){
      return false;
   }
   else if(shrink_page_bytes){
      //In UNIX we can decommit and free virtual address space.
      return 0 == munmap(shrink_page_start, shrink_page_bytes);
   }
   else{
      return true;
   }
}

inline bool mapped_region::flush(std::size_t mapping_offset, std::size_t numbytes, bool async)
{
   void *addr;
   if(m_is_xsi || !this->priv_flush_param_check(mapping_offset, addr, numbytes)){
      return false;
   }
   //Flush it all
   return msync(addr, numbytes, async ? MS_ASYNC : MS_SYNC) == 0;
}

inline bool mapped_region::advise(advice_types advice)
{
   int unix_advice = 0;
   //Modes; 0: none, 2: posix, 1: madvise
   const unsigned int mode_none = 0;
   const unsigned int mode_padv = 1;
   const unsigned int mode_madv = 2;
   // Suppress "unused variable" warnings
   (void)mode_padv;
   (void)mode_madv;
   unsigned int mode = mode_none;
   //Choose advice either from POSIX (preferred) or native Unix
   switch(advice){
      case advice_normal:
         #if defined(POSIX_MADV_NORMAL)
         unix_advice = POSIX_MADV_NORMAL;
         mode = mode_padv;
         #elif defined(MADV_NORMAL)
         unix_advice = MADV_NORMAL;
         mode = mode_madv;
         #endif
      break;
      case advice_sequential:
         #if defined(POSIX_MADV_SEQUENTIAL)
         unix_advice = POSIX_MADV_SEQUENTIAL;
         mode = mode_padv;
         #elif defined(MADV_SEQUENTIAL)
         unix_advice = MADV_SEQUENTIAL;
         mode = mode_madv;
         #endif
      break;
      case advice_random:
         #if defined(POSIX_MADV_RANDOM)
         unix_advice = POSIX_MADV_RANDOM;
         mode = mode_padv;
         #elif defined(MADV_RANDOM)
         unix_advice = MADV_RANDOM;
         mode = mode_madv;
         #endif
      break;
      case advice_willneed:
         #if defined(POSIX_MADV_WILLNEED)
         unix_advice = POSIX_MADV_WILLNEED;
         mode = mode_padv;
         #elif defined(MADV_WILLNEED)
         unix_advice = MADV_WILLNEED;
         mode = mode_madv;
         #endif
      break;
      case advice_dontneed:
         #if defined(POSIX_MADV_DONTNEED)
         unix_advice = POSIX_MADV_DONTNEED;
         mode = mode_padv;
         #elif defined(MADV_DONTNEED) && defined(BOOST_INTERPROCESS_MADV_DONTNEED_HAS_NONDESTRUCTIVE_SEMANTICS)
         unix_advice = MADV_DONTNEED;
         mode = mode_madv;
         #endif
      break;
      default:
      return false;
   }
   switch(mode){
      #if defined(POSIX_MADV_NORMAL)
         case mode_padv:
         return 0 == posix_madvise(this->priv_map_address(), this->priv_map_size(), unix_advice);
      #endif
      #if defined(MADV_NORMAL)
         case mode_madv:
         return 0 == madvise(
            #if defined(BOOST_INTERPROCESS_MADVISE_USES_CADDR_T)
            (caddr_t)
            #endif
            this->priv_map_address(), this->priv_map_size(), unix_advice);
      #endif
      default:
      return false;

   }
}

inline void mapped_region::priv_close()
{
   if(m_base != 0){
      #ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
      if(m_is_xsi){
         int ret = ::shmdt(m_base);
         BOOST_ASSERT(ret == 0);
         (void)ret;
         return;
      }
      #endif //#ifdef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS
      munmap(this->priv_map_address(), this->priv_map_size());
      m_base = 0;
   }
}

inline void mapped_region::dont_close_on_destruction()
{  m_base = 0;   }

#endif   //#if defined (BOOST_INTERPROCESS_WINDOWS)

template<int dummy>
const std::size_t mapped_region::page_size_holder<dummy>::PageSize
   = mapped_region::page_size_holder<dummy>::get_page_size();

inline std::size_t mapped_region::get_page_size()
{
   if(!page_size_holder<0>::PageSize)
      return page_size_holder<0>::get_page_size();
   else
      return page_size_holder<0>::PageSize;
}

inline void mapped_region::swap(mapped_region &other)
{
   ::boost::adl_move_swap(this->m_base, other.m_base);
   ::boost::adl_move_swap(this->m_size, other.m_size);
   ::boost::adl_move_swap(this->m_page_offset, other.m_page_offset);
   ::boost::adl_move_swap(this->m_mode,  other.m_mode);
   #if defined (BOOST_INTERPROCESS_WINDOWS)
   ::boost::adl_move_swap(this->m_file_or_mapping_hnd, other.m_file_or_mapping_hnd);
   #else
   ::boost::adl_move_swap(this->m_is_xsi, other.m_is_xsi);
   #endif
}

//!No-op functor
struct null_mapped_region_function
{
   bool operator()(void *, std::size_t , bool) const
      {   return true;   }

   static std::size_t get_min_size()
   {  return 0;  }
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MAPPED_REGION_HPP

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#ifndef BOOST_INTERPROCESS_MAPPED_REGION_EXT_HPP
#define BOOST_INTERPROCESS_MAPPED_REGION_EXT_HPP

#if defined(BOOST_INTERPROCESS_WINDOWS) && !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)
#  include <boost/interprocess/sync/windows/sync_utils.hpp>
#  include <boost/interprocess/detail/windows_intermodule_singleton.hpp>

namespace boost {
namespace interprocess {

template<int Dummy>
inline void mapped_region::destroy_syncs_in_range(const void *addr, std::size_t size)
{
   ipcdetail::sync_handles &handles =
      ipcdetail::windows_intermodule_singleton<ipcdetail::sync_handles>::get();
   handles.destroy_syncs_in_range(addr, size);
}

}  //namespace interprocess {
}  //namespace boost {

#endif   //defined(BOOST_INTERPROCESS_WINDOWS) && !defined(BOOST_INTERPROCESS_FORCE_GENERIC_EMULATION)

#endif   //#ifdef BOOST_INTERPROCESS_MAPPED_REGION_EXT_HPP

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)


/* mapped_region.hpp
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
*/