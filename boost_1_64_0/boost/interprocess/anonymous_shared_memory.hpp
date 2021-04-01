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
zzHltFLoE5Wdpwq9Ynhopke++qIA7zD21rz98E4zcsgcId+seH7LN/hVKpDJFMeZjGsgqqT6KunOZnRJ0/orh48ufHBO0ht0KqkjsVcLKS18bWMSpD8T8w6v7Wb0yerc+3OLErcgsTcg93lHO/ulAEI0RYO2LNMOhzPyxdenLlkbolfc776nCS7XGGewJbXGUhxX/3l9/lnXYAA0f1r1ivEFYAn4UagcHnfJNbGWjjtyvwsJAPIPApNqxbz4nua58lBLbPfgcHyiW9k69ZaLA6c/y5FVS2NPoeAMrIamMAeWnKH3eXe+8VgHbT5bjVbOsL6JimO+Nuc++Cg6Zx6D+uQfBsHgav+rHBTp9M71WCc093Tl10iplfsvfl07W71ZqJoCKc3A+CAA5L/1CELp6hVAzURhsVM06a7+X3KofpRCvt5lXjIPrL8v4zvuy8nqtEw5XXqzftwIOHyUGk46SI8UPAl9kv7bTLgCzzdSNJ3WLrllsR+BJn+zAK6tS0x7Su9p7qVgT4kolknArJakbnbDj4S1YN3cFIQhpmOHKXHYf5rrFt5uav6xxw==
*/