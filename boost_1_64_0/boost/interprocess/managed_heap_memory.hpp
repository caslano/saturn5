//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_MANAGED_HEAP_MEMORY_HPP
#define BOOST_INTERPROCESS_MANAGED_HEAP_MEMORY_HPP

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
#include <boost/move/utility_core.hpp>
#include <vector>
#include <boost/interprocess/detail/managed_memory_impl.hpp>
#include <boost/core/no_exceptions_support.hpp>
//These includes needed to fulfill default template parameters of
//predeclarations in interprocess_fwd.hpp
#include <boost/interprocess/mem_algo/rbtree_best_fit.hpp>
#include <boost/interprocess/sync/mutex_family.hpp>
#include <boost/interprocess/indexes/iset_index.hpp>

//!\file
//!Describes a named heap memory allocation user class.

namespace boost {
namespace interprocess {

//!A basic heap memory named object creation class. Initializes the
//!heap memory segment. Inherits all basic functionality from
//!basic_managed_memory_impl<CharType, AllocationAlgorithm, IndexType>*/
template
      <
         class CharType,
         class AllocationAlgorithm,
         template<class IndexConfig> class IndexType
      >
class basic_managed_heap_memory
   : public ipcdetail::basic_managed_memory_impl <CharType, AllocationAlgorithm, IndexType>
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   typedef ipcdetail::basic_managed_memory_impl
      <CharType, AllocationAlgorithm, IndexType>             base_t;
   BOOST_MOVABLE_BUT_NOT_COPYABLE(basic_managed_heap_memory)
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public: //functions
   typedef typename base_t::size_type              size_type;

   //!Default constructor. Does nothing.
   //!Useful in combination with move semantics
   basic_managed_heap_memory(){}

   //!Destructor. Liberates the heap memory holding the managed data.
   //!Never throws.
   ~basic_managed_heap_memory()
   {  this->priv_close();  }

   //!Creates heap memory and initializes the segment manager.
   //!This can throw.
   basic_managed_heap_memory(size_type size)
      :  m_heapmem(size, char(0))
   {
      if(!base_t::create_impl(&m_heapmem[0], size)){
         this->priv_close();
         throw interprocess_exception("Could not initialize heap in basic_managed_heap_memory constructor");
      }
   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_heap_memory(BOOST_RV_REF(basic_managed_heap_memory) moved)
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_heap_memory &operator=(BOOST_RV_REF(basic_managed_heap_memory) moved)
   {
      basic_managed_heap_memory tmp(boost::move(moved));
      this->swap(tmp);
      return *this;
   }

   //!Tries to resize internal heap memory so that
   //!we have room for more objects.
   //!WARNING: If memory is reallocated, all the objects will
   //!be binary-copied to the new buffer. To be able to use
   //!this function, all pointers constructed in this buffer
   //!must be offset pointers. Otherwise, the result is undefined.
   //!Returns true if the growth has been successful, so you will
   //!have some extra bytes to allocate new objects. If returns
   //!false, the heap allocation has failed.
   bool grow(size_type extra_bytes)
   {
      //If memory is reallocated, data will
      //be automatically copied
      BOOST_TRY{
        m_heapmem.resize(m_heapmem.size()+extra_bytes);
      }
      BOOST_CATCH(...){
         return false;
      }
      BOOST_CATCH_END

      //Grow always works
      base_t::close_impl();
      base_t::open_impl(&m_heapmem[0], m_heapmem.size());
      base_t::grow(extra_bytes);
      return true;
   }

   //!Swaps the ownership of the managed heap memories managed by *this and other.
   //!Never throws.
   void swap(basic_managed_heap_memory &other)
   {
      base_t::swap(other);
      m_heapmem.swap(other.m_heapmem);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Frees resources. Never throws.
   void priv_close()
   {
      base_t::destroy_impl();
      std::vector<char>().swap(m_heapmem);
   }

   std::vector<char>  m_heapmem;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Typedef for a default basic_managed_heap_memory
//!of narrow characters
typedef basic_managed_heap_memory
   <char
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
managed_heap_memory;

//!Typedef for a default basic_managed_heap_memory
//!of wide characters
typedef basic_managed_heap_memory
   <wchar_t
   ,rbtree_best_fit<null_mutex_family>
   ,iset_index>
wmanaged_heap_memory;

#endif   //#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_MANAGED_HEAP_MEMORY_HPP


/* managed_heap_memory.hpp
YC7TaYBrcbDVH1xz2bMCusk0oJschYzSN/66SZABlBpikovQSZQw52bpIUGTZUqTXqAmx4SMI+xwnNqkS7A4YS7GTZtz2iZlhvq0XMF53LU2ZLgTzA9gKUYfSiDvQjfGUctARy0DHbYMZNwyAHHLAGQtA+ZbIqWTKEHON7xWabQH9lVPafKKILxASKOZKOfDfkz5UQrIq01Iua1FMBkUAeJRLQHNva6sxMchg6Epj55FTYckEBmOoPKhCDDKNhonoGWMCIFoohOUlg0eOY72cxD9Z+A+dpGhuawyZuQgU3OjkaKItMhyJ6nIW4TW5YeXiNZHqUC3qECXVKBLKtAlFWRGkw8ZAv4PFegjVKBTFRiTZhRwQJhGcB4YCdwZlDiyG11zIx0OgLDGgw6TsZSWLAGdJj2NXiQFzeXDeukaLMlS+AqrN+KM35AEoMA86bt+jiyXVzFKj/CA9xEekdf2WHTOUFWJk8OBBWUclpw5lseUh46ay75zJs/ZzpprliJWc8yf1x0bzwC2OmNMU5v2MnVrpXShUrpYKbQfCyfXungouyWmhcNWSwuH22E8x8x5YF8qh7DJYVfHuHRigcQqgeLDpBTGdmKoMZEC1Cg4x83FMQlOW8WIdyw5XBJB249d5rCZLua4O4fLOfYkLmfET7mHfJ4sExtt3rgNLS+JzqM1ERG+DCI4bVRiuBctMwBtDwvoZCRyhFcIhSCKGKR0lh2guc0FLyGp3R5DBsTpQXNx4nb0ViQUe6IpsLOWIGx8Ek7A7TRa04QJdPvDbi+CjqXlHcvKO1Yq71hWHkvuEQ9/NLPIfvPcTsROGgCk6AvSe5hyRtqVDrIDrM44tMMgbJ1gSifNhvHd3nsWgRrrjKHYg8jMK4Fyv5BNu3JOXpxMvXLYmX6RgxUXRMqsOJ6d5XCmvfw1pJyFk2iDmW97TvpKUiuDGVBvQrA1QpZr7GbzyV7OyRWvy4rXrYrXbYrXrYrXZcXrNsXrdsXrsuJ1q+J1m+L1/1K8blE8dxOwX1d05rRHRHTwSZ1wruWrlSOJhhjOxu4q6AyVoU7gfJzTPPBfErNt3NOpz9SZz9Qln6kzn6mP9pmwm0l1jkQTlKShoVIlMfGXTOIs7YGqp50RJHScYWIQbbgk2uHmlmaR4Sm/ooi3U5JNEjuXO7DPHDoo3OeDtE7fkDxpyaUQzFp7Kc3Qh5lxKcaxVg4vvce83mFMc+NECvCTQjGA24hoboWI6IOkkEnCn+x72t+jlgEYcD8CuehF6CuuxgqBpmoxTU1SgHxSKAaoWkRTtYg+SAqhajG9H9Fx1QDyqtFCUVWg47Zt5UDHPGSLaOqbAigghWIABUQ0Cojog6QQFBDT+xEdKwCgqADftnv7ThcEzR0ijkAQG/Rl7I14tHh177LHVgNSO7X07O0pvvfkIPooovwU8QKKvnIQWTMQqWPQGXEO5nKJ+RbxHM3kctacgZlczs5yMJdLrKqI52gmlzOyDBS5OD2/bCAQlLUMoclAKEl5+y7/Vi8VEc2ni45d+lKXbdA+BkjWEqYyAUEpIXUFT1CghPuDMHzpiPC5C0ARKUI5GXSFCElLvDS1jAHb1QRJi87LSTMN8wzDd/VZMa6b79hBBKfJ9muSgMHD1Qk4vQvTlcmhmSSyhBk09zJ5wkgnJKJ5wsty2L+M/b2s+/U+EsKLRrhnnMKst8qndJYlefJylwnJKCwyQHkRCCOBC1/G/ZKvCzY+2UnVXKdJdd2jFznEXHJs4OGUi/e4uWYFyrzXiTiesH1LaCTyhBdJp8oVlRDgGpwVguGAQfDSV/Coc593uf1wNppO+KAw939s8PXIazUvJ91kZ+067m2FHGfOU0A=
*/