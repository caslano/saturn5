//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2009-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP
#define BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP

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
#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/detail/shared_dir_helpers.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/exceptions.hpp>

#include <boost/interprocess/xsi_shared_memory.hpp>

//!\file
//!Describes a class representing a pseudo-file implemented on top of xsi shared memory.

namespace boost {
namespace interprocess {

class xsi_shared_memory_file_wrapper
   : public xsi_shared_memory
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   BOOST_MOVABLE_BUT_NOT_COPYABLE(xsi_shared_memory_file_wrapper)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:

   xsi_shared_memory_file_wrapper() : xsi_shared_memory() {}

   xsi_shared_memory_file_wrapper(create_only_t, const xsi_key &key, mode_t , std::size_t size, const permissions& perm = permissions())
      : xsi_shared_memory(create_only_t(), key, size, perm.get_permissions())
   {}

   xsi_shared_memory_file_wrapper(open_or_create_t, const xsi_key &key, mode_t , std::size_t size, const permissions& perm = permissions())
      : xsi_shared_memory(open_or_create_t(), key, size, perm.get_permissions())
   {}

   xsi_shared_memory_file_wrapper(open_only_t, const xsi_key &key, mode_t, const permissions& = permissions())
      : xsi_shared_memory(open_only_t(), key)
   {}

   xsi_shared_memory_file_wrapper(BOOST_RV_REF(xsi_shared_memory_file_wrapper) moved)
   {  this->swap(moved);   }

   xsi_shared_memory_file_wrapper &operator=(BOOST_RV_REF(xsi_shared_memory_file_wrapper) moved)
   {
      xsi_shared_memory_file_wrapper tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Swaps two xsi_shared_memory_file_wrapper. Does not throw
   void swap(xsi_shared_memory_file_wrapper &other)
   {  this->xsi_shared_memory::swap(other);  }
};

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_XSI_SHARED_MEMORY_FILE_WRAPPER_HPP

/* xsi_shared_memory_file_wrapper.hpp
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
*/