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