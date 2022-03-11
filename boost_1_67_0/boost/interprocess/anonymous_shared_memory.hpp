//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP
#define BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP

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
#include <boost/move/move.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstddef>

#if (!defined(BOOST_INTERPROCESS_WINDOWS))
#  include <fcntl.h>        //open, O_CREAT, O_*...
#  include <sys/mman.h>     //mmap
#  include <sys/stat.h>     //mode_t, S_IRWXG, S_IRWXO, S_IRWXU,
#else
#include <boost/interprocess/windows_shared_memory.hpp>
#endif


//!\file
//!Describes a function that creates anonymous shared memory that can be
//!shared between forked processes

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail{

   class raw_mapped_region_creator
   {
      public:
      static mapped_region
         create_posix_mapped_region(void *address, std::size_t size)
      {
         mapped_region region;
         region.m_base = address;
         region.m_size = size;
         return region;
      }
   };
}

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!A function that creates an anonymous shared memory segment of size "size".
//!If "address" is passed the function will try to map the segment in that address.
//!Otherwise the operating system will choose the mapping address.
//!The function returns a mapped_region holding that segment or throws
//!interprocess_exception if the function fails.
//static mapped_region
static mapped_region
anonymous_shared_memory(std::size_t size, void *address = 0)
#if (!defined(BOOST_INTERPROCESS_WINDOWS))
{
   int flags;
   int fd = -1;

   #if defined(MAP_ANONYMOUS) //Use MAP_ANONYMOUS
   flags = MAP_ANONYMOUS | MAP_SHARED;
   #elif !defined(MAP_ANONYMOUS) && defined(MAP_ANON) //use MAP_ANON
   flags = MAP_ANON | MAP_SHARED;
   #else // Use "/dev/zero"
   fd = open("/dev/zero", O_RDWR);
   flags = MAP_SHARED;
   if(fd == -1){
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }
   #endif


   address = mmap( address
                  , size
                  , PROT_READ|PROT_WRITE
                  , flags
                  , fd
                  , 0);

   if(address == MAP_FAILED){
      if(fd != -1)
         close(fd);
      error_info err = system_error_code();
      throw interprocess_exception(err);
   }

   if(fd != -1)
      close(fd);

   return ipcdetail::raw_mapped_region_creator::create_posix_mapped_region(address, size);
}
#else
{
   windows_shared_memory anonymous_mapping(create_only, 0, read_write, size);
   return mapped_region(anonymous_mapping, read_write, 0, size, address);
}

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_ANONYMOUS_SHARED_MEMORY_HPP

/* anonymous_shared_memory.hpp
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
*/