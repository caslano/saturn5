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
flO/md/cb+G39Fv5rf02flu/nd/e7+B39Dv5nf0ufle/m9/d7+H39Hv5vf0+fl+/n9/fH+AP9Af5g/0h/lB/mD/cH+GP9Ef5o/0x/lh/nD/en+BP9Cf5k/0p/lR/mj/dn+HP9Gf5s/05/lx/nj/f/8tf4C/0F/mL/SX+Un+Zv9xf4a/0V/mr/TX+Wn+d/7e/3t/gb/Q3+Zv9Lf5Wf5u/3d/h7/R3+bv9Pf5ef5+/3z/g/+Mf9A/5h/0j/lH/mH/cP+Gf9E/5p/0z/ln/nH/ev+Bf9C/5l/0r/lX/mn/dv+Hf9G/5t/07/l3/nn/ff+A/9B/5j/0n/lP/mf/cf+G/9F/5r/03/lv/nf+v/97/4H/0P/mf/S/+V/+b/93/4f/kUa8diEAGKnACHZjADbzAD4IgDCJBlCBqEC2IHsQIfgn+E8QMYgW/Br8FsYM4wX+DuMHvQbwgfvBHkCBIGCQKEgdJgqTBn0GyIHmQIkgZpApSB2mCtEG6IH2QIcgYZAoyB1mCrEG2IHuQI8gZ5ApyB3mCvEG+IH9QICgYFAoKB0WCokGxoHhQIigZlApKB2WCskG5oHxQIagYVAoqB1WCqkG1oHpQI6gZ1ApqB3WCukG9oH7QIGgYNAoaB02CpkGzoHnQImgZtApaB22CtkG7oH3QIegYdAo6B12CrkG3oHvQI+gZ9Ap6B32CvkG/oH8wIBgYDAoGB0OCocGwYHgwIhgZjApGB2OCscG4YHwwIZgYTAomB1OCqcG0YHowI5gZzApmB3OCucG8YH7wV7AgWBgsChYHS4KlwbJgebAiWBmsClYHa4K1wbrg72B9sCHYGGwKNgdbgq3BtmB7sCPYGewKdgd7gr3BvmB/cCD4JzgYHAoOB0eCo8Gx4HhwIjgZnApOB2eCs8G54HxwIbgYXAouB1eCq8G14HpwI7gZ3ApuB3eCu8G94H7wIHgYPAoeB0+Cp8Gz4HnwIngZvApeB2+Ct8G74N/gffAh+Bh8Cj4HX4Kvwbfge/Aj+MmDfjsUoQxV6IQ6NKEbeqEfBmEYRsIoYdQwWhg9jBH+Ev4njBnGCn8Nfwtjh3HC/4Zxw9/DeGH88I8wQZgwTBQmDpOEScM/w2Rh8jBFmDJMFaYO04Rpw3Rh+jBDmDHMFGYOs4RZw2xh9jBHmDPMFeYO84R5w3xh/rBAWDAsFBYOi4RFw2Jh8bBEWDIsFZYOy4Rlw3Jh+bBCWDGsFFYOq4RVw2ph9bBGWDOsFdYO64R1w3ph/bBB2DBsFDYOm4RNw2Zh87BF2DJsFbYO24Rtw3Zh+7BD2DHsFHYOu4Rdw25h97BH2DPsFfYO+4R9w35h/3BAODAcFA4Oh4RDw2Hh8HBEODIcFY4Ox4Rjw3Hh+HBCODGcFE4Op4RTw2nh9HBGODOcFc4O54Rzw3nh/PCvcEG4MFwULg6XhEvDZeHycEW4MlwVrg7XhGvDdeHf4fpwQ7gx3BRuDreEW8Nt4fZwR7gz3BXuDveEe8N94f7wQPhPeDA8FB4Oj4RHw2Ph8fBEeDI8FZ4Oz4Rnw3Ph+fBCeDG8FF4Or4RXw2vh9fBGeDO8Fd4O74R3w3vh/fBB+DB8FD4On4RPw2fh8/BF+DJ8Fb4O34Rvw3fhv+H78EP4MfwUfg6/hF/Db+H38Ef4k2UeOyIiMqIiTkRHTMSNeBE/EkTCSCQSJRI1Ei0SPRIj8kvkP5GYkViRXyO/RWJH4kT+G4kb+T0SLxI/8kckQSRhJFEkcSRJJGnkz0iySPJIikjKSKpI6kiaSNpIukj6SIZIxkimSOZIlkjWSLZI9kiOSM5IrkjuSJ5I3ki+SP5IgUjBSKFI4UiRSNFIsUjxSIlIyUipSOk=
*/