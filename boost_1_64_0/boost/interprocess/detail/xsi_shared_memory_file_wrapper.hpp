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
FBi0tCKtaHs4jaO64s0MfC1wea/ExHcTQH5koegCSnf3oq8Z9ZmlfPD2Or65YIHriA5WX/rBLMlOjfvjJu9mGYkWk9xy1XGE3HRc5DaFRqHkmA49oHmuB2S6iFof26jnTr7W9Ol9QOVeh3/YK9Jd6iijq9P8FMv51NHbmEl2GdyVwKsRol5ZQS41a4QvGzbmJf5tycvE66T5YE3e9nrXC4Wx11PrwjggL6Azyy/rYBGoixtjE8FoGAaLDs/CV7iFs9Qh7ZtRDNlD+8y9jUl4HGi0ujZY3W/bkKs1KRvKPD19CRhfvGVkesl1HvE1m0okYBPYPj1Lq2zFR19M4LsBV1C8XRyK52nDj3tDCLwW/Xn3uwPm5Roxr8pHM55PMjjFChkukfqi/l0i/VrVyUcqFuvW0046UA5tZP9vWtqmUfvB705XU9YOUU2fxM94RM5EjKqdsaaf3AVl8861NqEcqZztAE+ObQCmEpfIu+GiD7M4ddlvIBhs7L5z3iy8wZDhw7U/uOZKLBPy8K/E1soro51aJpoXgik+bOibm6X8J/MtS72d1jkodwM2+Q==
*/