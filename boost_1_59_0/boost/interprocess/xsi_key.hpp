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
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
*/