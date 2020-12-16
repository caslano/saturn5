//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_XSI_KEY_HPP
#define BOOST_INTERPROCESS_XSI_KEY_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/detail/workaround.hpp>

#if !defined(BOOST_INTERPROCESS_XSI_SHARED_MEMORY_OBJECTS)
#error "This header can't be used in operating systems without XSI (System V) shared memory support"
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <sys/types.h>
#include <sys/ipc.h>
#include <cstddef>
#include <boost/cstdint.hpp>

//!\file
//!Describes a class representing a xsi key type.

namespace boost {
namespace interprocess {

//!A class that wraps XSI (System V) key_t type.
//!This type calculates key_t from path and id using ftok,
//!sets key to a specified value,
//!or sets key to IPC_PRIVATE using the default constructor.
class xsi_key
{
   public:

   //!Default constructor.
   //!Represents a private xsi_key.
   xsi_key()
      : m_key(IPC_PRIVATE)
   {}

   //!Creates a new XSI key using a specified value. Constructor is explicit to avoid ambiguity with shmid.
   explicit xsi_key(key_t key)
      : m_key(key)
   {}

   //!Creates a new XSI  shared memory with a key obtained from a call to ftok (with path
   //!"path" and id "id"), of size "size" and permissions "perm".
   //!If the shared memory previously exists, throws an error.
   xsi_key(const char *path, boost::uint8_t id)
   {
      key_t key;
      if(path){
         key  = ::ftok(path, id);
         if(((key_t)-1) == key){
            error_info err = system_error_code();
            throw interprocess_exception(err);
         }
      }
      else{
         key = IPC_PRIVATE;
      }
      m_key = key;
   }

   //!Returns the internal key_t value
   key_t get_key() const
   {  return m_key;  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   key_t m_key;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_XSI_KEY_HPP

/* xsi_key.hpp
XLXjt5qai1IP5EO4ynmF68xlwk76qXBxq1kTLm01G/Z+W435luy31TRAnlsxHRB/3vRAnisxA8KlSjMpXGHcQ/x8cxbyHIZZtvevMmvCacb9tyU/VaZGuGJMG+T5FrMH8hyM2S+cZrxDnn8xk5DnK8yMfZxlFoT5kKMhziKfghfgNLwEB+DFUe5bwHXkOWmw72DrYBs8BvvgS6GsL47DCeSnwFn4MngOvhKuwHF4BT4Vxi9tN4OwGWah3L85CruQj8AB+BI4CV8Dp+GLoKxfDsB55IOSbzgk+YZPk3zDMckvfLOc77PbzfNg9Px2cwLWwKfDdvhC2ANnoKxPT8JxOAFlXfQMmCH+DfAEfAGcg8+EZ+AI5Ho61yXRc9zrRIazkh/inw/X4KvgVfTPknQ/t928HqbgIdgJD8P98I1wDL4ayro3A08hPxkuwEm4BJ8t7QJHJX34XLgBXw4rmBeeI/X6+e3/0fn4/zVkv7vd2Pfaf7DdNLB1sYn+6o7bmHW2DbZrbG/keb7rP91uFte2m78SZB/sX9PlX9j2r+kqxE42xa/YdqupBrKObGqD2PWmLoi9b+qFrA+bxiB2tukExP43zdqMNZ2B2Kmm8/b+pA+ZL5s2IPaoKf5L2z421UJ6R1MLxP409UDsZFMGYg+bJiH2sGkaYg+b5iHze9M5Oz7RdEmYIl2InWyq+ZVtb5qaIfayaQ9kPm3aDxndTeOQ+ahpCvK8YNMpiP1rOguxh00XIfNW0xrETjZdg9jNpupfQ13PNrUgPw92wefDAfgCOAGn4Aw8CBfhU+AyHILr8ASMXGV8QwMPwF1wGHbDV8EMnIRT8NlwAR6CF2AGXoJHoDwzcBRuIL8Mir16Iaz4DXYJpuBrYDt8NeyBxyS/MAvH4bicB07DOfgMeBo+By7BMbgCXwHX4Csl/7/FTsJa+HKph9/+98d1an272cW2qeBX9I/S3vQsYUskUiPsZD1+Qe6rRiLNIvdHIu3CLENBSMXvEVIhPUImmH4hN8IyQh6EGhOusAYX8iDT8uflvnAkcg7KVZIZ0fPUy7x9/ptFzvxR83XzCPshl0U4DkbhRbgFrsIYvALL4Qa07zP+abtJRCgHTEYoB9wKG6AFW6CcoAOmYBesi5B/eAfYB5tgBt4JTsD7wCl4PzgHO+EZeH/JH3wAXIEPjBD+jE0BtXC3nA8+CGbhpl9TuD4Ean+PnqK2OCzrchjd73DLkMPYCYfl8w7jSw4Tqw6T6w63Rv5g00o5rOxwWNVvk/nY4Z1OObzzosPqJYepFYd1qw7vsOGwPr4BqcZah43tDu/aa5Nx6HDnpMPmaYd3mbPJ/TaHLUs2ua7n8O6rDts2hP9D4S90OtqIIUFfYstGWyLr+C2pWybN+vakJ68tt0L2hVfmjy9ExEkp28F+93X2TW1xHX8/dCEBvyMWrb+V+EOxGogfEWuGzCOxDsj8EuuBrONjAxB/KzYOmZdi05D1fOw0ZL6JLdn7JWOXbbk8tm7HJ2PxBrhUHktB5oVYO+S6RqwP4u/ExiC5j52ErJNj8xD/JnYOcr0ldhHix8Wu2vvHYtch81WsolGOS8ZSkHkq1gGZN2O9EP8jNgTxA2ITED8qNg3xn2KLkHkrdgFy/yu2BvGvYtcg9/NiFU2yfyLWDPE7Y10QvzO2H3LfLDZm62OxGVuOxxYg6/DYecg8GVu15fLYhrCF9HaKfmusGTJvxjqFKdKD+M2xDGQ+j01B/OfYLMR/ji1C7ifGliH3E2OXIfN8bANyPzEWb5byJ2INkOsDsU7IfB8bgPhtsTHIfb3YFMTPic1C/JvYIsQPji3b3Bq7CrmvHKu4o+wfi9XaLI+1CfM=
*/