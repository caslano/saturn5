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
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
*/