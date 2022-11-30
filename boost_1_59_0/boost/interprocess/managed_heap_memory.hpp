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
   basic_managed_heap_memory() BOOST_NOEXCEPT
   {}

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
   basic_managed_heap_memory(BOOST_RV_REF(basic_managed_heap_memory) moved) BOOST_NOEXCEPT
   {  this->swap(moved);   }

   //!Moves the ownership of "moved"'s managed memory to *this. Does not throw
   basic_managed_heap_memory &operator=(BOOST_RV_REF(basic_managed_heap_memory) moved) BOOST_NOEXCEPT
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
   void swap(basic_managed_heap_memory &other) BOOST_NOEXCEPT
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
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
*/