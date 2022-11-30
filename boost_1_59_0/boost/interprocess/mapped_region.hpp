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
   mapped_region() BOOST_NOEXCEPT;

   //!Move constructor. *this will be constructed taking ownership of "other"'s
   //!region and "other" will be left in default constructor state.
   mapped_region(BOOST_RV_REF(mapped_region) other)  BOOST_NOEXCEPT
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
   mapped_region &operator=(BOOST_RV_REF(mapped_region) other) BOOST_NOEXCEPT
   {
      mapped_region tmp(boost::move(other));
      this->swap(tmp);
      return *this;
   }

   //!Swaps the mapped_region with another
   //!mapped region
   void swap(mapped_region &other) BOOST_NOEXCEPT;

   //!Returns the size of the mapping. Never throws.
   std::size_t get_size() const BOOST_NOEXCEPT;

   //!Returns the base address of the mapping.
   //!Never throws.
   void*       get_address() const BOOST_NOEXCEPT;

   //!Returns the mode of the mapping used to construct the mapped region.
   //!Never throws.
   mode_t get_mode() const BOOST_NOEXCEPT;

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
   //!function can release some physical memory without freeing any virtual address space(Windows).
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
   static std::size_t get_page_size() BOOST_NOEXCEPT;

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

inline void swap(mapped_region &x, mapped_region &y) BOOST_NOEXCEPT
{  x.swap(y);  }

inline mapped_region::~mapped_region()
{  this->priv_close(); }

inline std::size_t mapped_region::get_size() const BOOST_NOEXCEPT
{  return m_size; }

inline mode_t mapped_region::get_mode() const BOOST_NOEXCEPT
{  return m_mode;   }

inline void*    mapped_region::get_address() const BOOST_NOEXCEPT
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

   if(mapping_offset >= m_size || numbytes > (m_size - size_t(mapping_offset))){
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
   //as offset_t is the maximum file size and it's signed.
   if(mapping_size < offset ||
      boost::uintmax_t(mapping_size - (offset - page_offset)) >
         boost::uintmax_t(std::size_t(-1))){
      error_info err(size_error);
      throw interprocess_exception(err);
   }
   size = static_cast<std::size_t>(mapping_size - offset);
}

inline offset_t mapped_region::priv_page_offset_addr_fixup(offset_t offset, const void *&address)
{
   //We can't map any offset so we have to obtain system's
   //memory granularity
   const std::size_t page_size  = mapped_region::get_page_size();

   //We calculate the difference between demanded and valid offset
   //(always less than a page in std::size_t, thus, representable by std::size_t)
   const std::size_t page_offset =
      static_cast<std::size_t>(offset - (offset / offset_t(page_size)) * offset_t(page_size));
   //Update the mapping address
   if(address){
      address = static_cast<const char*>(address) - page_offset;
   }
   return offset_t(page_offset);
}

#if defined (BOOST_INTERPROCESS_WINDOWS)

inline mapped_region::mapped_region() BOOST_NOEXCEPT
   :  m_base(0), m_size(0), m_page_offset(0), m_mode(read_only)
   ,  m_file_or_mapping_hnd(ipcdetail::invalid_file())
{}

template<int dummy>
inline std::size_t mapped_region::page_size_holder<dummy>::get_page_size()
{
   winapi::interprocess_system_info info;
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
            , protection, 0, (char*)0, 0);

         //Check if all is correct
         if(!native_mapping_handle){
            error_info err ((int)winapi::get_last_error());
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
            error_info err((int)winapi::get_last_error());
            throw interprocess_exception(err);
         }
         //This can throw
         priv_size_from_mapping_size(mapping_size, offset, page_offset, size);
      }

      //Map with new offsets and size
      void *base = winapi::map_view_of_file_ex
                                 (native_mapping_handle,
                                 map_access,
                                 ::boost::ulong_long_type(offset - page_offset),
                                 static_cast<std::size_t>(page_offset + size),
                                 const_cast<void*>(address));
      //Check error
      if(!base){
         error_info err((int)winapi::get_last_error());
         throw interprocess_exception(err);
      }

      //Calculate new base for the user
      m_base = static_cast<char*>(base) + page_offset;
      m_page_offset = static_cast<std::size_t>(page_offset);
      m_size = size;
   }
   //Windows shared memory needs the duplication of the handle if we want to
   //make mapped_region independent from the mappable device
   //
   //For mapped files, we duplicate the file handle to be able to FlushFileBuffers
   if(!winapi::duplicate_current_process_handle(mhandle.handle, &m_file_or_mapping_hnd)){
      error_info err((int)winapi::get_last_error());
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

inline mapped_region::mapped_region() BOOST_NOEXCEPT
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
                     , static_cast<std::size_t>(page_offset) + size
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
   m_page_offset = static_cast<std::size_t>(page_offset);
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

inline std::size_t mapped_region::get_page_size() BOOST_NOEXCEPT
{
   if(!page_size_holder<0>::PageSize)
      return page_size_holder<0>::get_page_size();
   else
      return page_size_holder<0>::PageSize;
}

inline void mapped_region::swap(mapped_region &other) BOOST_NOEXCEPT
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