//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP
#define BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP

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
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/assert.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

//!\file
//!Describes a named user memory allocation user class.

namespace boost {
namespace interprocess {

//!A basic user memory named object creation class. Inherits all
//!basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>*/
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_external_buffer
   : public ipcdetail::basic_managed_memory_impl <CharType, AllocationAlgorithm, IndexType>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType>    base_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_external_buffer)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename base_t::size_type              size_type;

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_external_buffer()
   {}

   //!Creates and places the segment manager. This can throw
   basic_managed_external_buffer
      (create_only_t, void *addr, size_type size)
   {
      //Check if alignment is correct
      BOOST_ASSERT((0 == (((std::size_t)addr) & (AllocationAlgorithm::Alignment - size_type(1u)))));
      if(!base_t::create_impl(addr, size)){
         throw interprocess_exception("Could not initialize buffer in basic_managed_external_buffer constructor");
      }
   }

   //!Creates and places the segment manager. This can throw
   basic_managed_external_buffer
      (open_only_t, void *addr, size_type size)
   {
      //Check if alignment is correct
      BOOST_ASSERT((0 == (((std::size_t)addr) & (AllocationAlgorithm::Alignment - size_type(1u)))));
      if(!base_t::open_impl(addr, size)){
         throw interprocess_exception("Could not initialize buffer in basic_managed_external_buffer constructor");
      }
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_external_buffer(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      this->swap(moved);
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_external_buffer &operator=(BOOST_RV_REF(basic_managed_external_buffer) moved)
   {
      basic_managed_external_buffer tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   void grow(size_type extra_bytes)
   {  base_t::grow(extra_bytes);   }

   //!Swaps the ownership of the managed heap memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_external_buffer &other)
   {  base_t::swap(other); }
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_external_buffer
//!of narrow characters
typedef basic_managed_external_buffer
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_external_buffer;

//!Typedef for a default basic_managed_external_buffer
//!of wide characters
typedef basic_managed_external_buffer
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_external_buffer;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_EXTERNAL_BUFFER_HPP


/* managed_external_buffer.hpp
BG8CgIXZfchhGyeSPZr1C5TGSbNCiFXev3WkNGbenQNGkgnvV66SUUgu627ptOsJjP1HBKNjQN/ZCiY0GVs66bUC5mrUrWrUJTXqXI1AWZy4uQHyvEvtD2ybvx3tdPf3WftRE/zYcEwOrmCZz4W9kqtxR303HtrFMVNCIXhrrPE1gsjoLxijf0DQEYTq740CYiHx4iwaaa7HWxBc4sMZV1QD5y0lYl7LxtP+H5GCjHhnKambezFWaM1zBO6SqrtFOD63MW8Bl3eQ2EIFlIFPoEWgETqEENhoKlFD8opMimDeKUR9UogMBdL/r4b1/6Nh/X9omDj+cSwmE2lm/2fEJMP5JG8QXVS+tqp2fmjYX13OhwMEahUYxMwOF8PRfGgblo5zrU0m9bu38NtSMcIwFNKmKbeus7llLrCUYPNQmH0YycF4x6GLQ/fpY1K4DtbFzSVrnsFaMAwvY6a03au3sN028BRSuzA1ZM8ppFgaheTGekhtr21dK6KDyP5qgByxu085Q0cQcuNYxzFIjfy5rGeIC0b6IopgOUxtctTVKselduF9IGVphgdwc8TWPGdIJWV8CCDbZKWyYM2kKBmSBRAr8pO1YkajbpSPOV1eDjIMGj5BFoGBpY3PqB5VlTseogKmJGxG2cYFtnOs1o6IQEu0c3XKKhZ3ZEl5NrwpFtJs3jDquUfki/pFSJ7w7zU/UQlNd45bjTZymmq07NyOlU+HvHgeILgd8lM4FdXxxDUF6sPs+oFymR0c4A/pwXSzFKKPpRgdLIWa3pWDhbQ8OEExZbgcneJKcLlIGG3FOm9U5jEGjVgQlpjSmXNeYpTtccrsNpla5WmT5X/KUZLhcHJnXwADLO0SUahRSFpBKO9NhY4iJ9UCyh0/YNnxh3PvHIqkjMeCHI6kzseCHC9l4muTs7yfz1mpu2qN0spNhnfdPjjByyXJRxzdPuLodIDR0QCj2wYY/b8GFH3kgCL8/+lqdTzyQB+h4aJmyz55Mc69H2DB/4HmHhAw8YE5nOWQd3w4LT0czv/o48Ro7+V+8be9vZyQmnuQGqtIoDs7zCzzDLoCbULWGDOgM14Balorj8gwaMCYam7gK0BeLDetEOberDu7m2O5sRYKTlassSd3ByygDlEuIc1h7mUqgFsF7CbXzkFeaCmAvE9SQrcKGdiHCnN8N8Mw0hzDRktgIceNQuWtoeQ4gRy8aaFWHBLlIG8EFcD1nUL6G23csABypdyx1TJ++QxuOl8BLWlmt9BcN9nMsZtf9lJXvOmly3iGRsB0MLD3lAkpdu6x1PaFwaTdGn+G5bnAKHcjLqhj0cwKeXZHQyOhjakzgOfscoytNTCcdyCNvcEt63d2QmF7pwD2ArAAxxWnjgjIy4lDizXK/b7LCxE63NXLPlJI22WuAGbCC725s3OTjW2+NrG9yXObJMvRJnEO+yw4rtzi2RaTNTlkYJNBhpr09JNr3o1tjN0Jb+835Prmja5LITxCai9mXh5TZpzFPncdNXfFJCw7YmSo7EdnLLbjMowJV4K5Z/vQdcqhfpGE2adFcp4Vs8ge3jlH7ANOOaNNDYxwLWnQewYxh0mhxWEKcYkA66/uKBfQ3NdCkRnOnbmZaPoI1eijVSMTsJxxRJXhlioE3DwyWWhSTDIvyUwqcBXNuVjAaLFUjuZZ1+RIR3N97CBUeVaUP6NNlL08m8Y675qWVTSRskbMWp+OmmKpHfunedybHmUeXaXEoK6+L+ZcXz/7IGEex86liwz9PxJj4hmmj6iHbquHPqoeYo055/+oIXFamzN+fKnMuHNb0+ojNZR0dhMBo26ihwxdtkDOQqykRikSbC4qSGlWVwG0SW0SMo4=
*/