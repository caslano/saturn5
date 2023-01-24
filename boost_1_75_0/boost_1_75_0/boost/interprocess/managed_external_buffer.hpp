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
5uCxaCq0/K5gmHkEPHyo4GqVpGY77iHwzDp5CjyIhr/rdhgA4sg68FnszDyyclSkaSEiViSRiOP9q36WxSCfZLEKJaqyPMUZr/buR4zYjVqTg1DbnpS/+BQOWzdvW1xOQVYyOS0JmQ7W1eBWRLv1zunDGhlcBGTTweHH0H3+Muk9gnANH7wNbz1D3pyVSOJLbfc4C6uech3GrmkMhP1W+9K6ukHAMuzNsSd6ARPdioVdI5hgGObhL2RGcylymuMEdM6K2pf25MxLFqjDGc0TxWh+1o7qKQE/BRMlRhwafs1ugkDVP7xBSeyr+V2AhM7Wi4mqxXLXRq6qx8TCywoTwaeQ5W5E2juU8J3F0ey6QF6Q9vhSzRMFyEqxQjjpPjNPXecFXqZ+VAq1uhGWBn+X5AKw6c+98iFNyE03on3bYg7yxNidWYBrW7AXj6oYy9cfbx5N6uWOd/pCFX/3aWCm0AuDZxXYCVuJ0hTBd43GRUSC+kg43WdfW4XSYT8VdueBy3iBzAc//UE/J08UvfW9HLqyPrWtPTS+2EKq0n59FLWhCETsl8Nz+7mPeYsOdzcxF1WJavYuEjJ++8wO7n5mKPNZaDnUU72s40CG4QrF62QyGRO3Tk9uFzzayN16MXgkhAxZjNXRQ8Drlp6t2ezc5AHVigb3HqluDy/B3bzlGJM149Pz+GNhvbyjaoL7p5U8r3wpA/OTde1FD6Eh
*/