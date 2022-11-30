///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ALLOCATOR_HPP
#define BOOST_INTERPROCESS_ALLOCATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/intrusive/pointer_traits.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/containers/allocation_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/assert.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/container/detail/placement_new.hpp>

#include <cstddef>
#include <stdexcept>

//!\file
//!Describes an allocator that allocates portions of fixed size
//!memory buffer (shared memory, mapped file...)

namespace boost {
namespace interprocess {


//!An STL compatible allocator that uses a segment manager as
//!memory source. The internal pointer type will of the same type (raw, smart) as
//!"typename SegmentManager::void_pointer" type. This allows
//!placing the allocator in shared memory, memory mapped-files, etc...
template<class T, class SegmentManager>
class allocator
{
   public:
   //Segment manager
   typedef SegmentManager                                segment_manager;
   typedef typename SegmentManager::void_pointer         void_pointer;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:

   //Self type
   typedef allocator<T, SegmentManager>   self_t;

   //Pointer to void
   typedef typename segment_manager::void_pointer  aux_pointer_t;

   //Typedef to const void pointer
   typedef typename boost::intrusive::
      pointer_traits<aux_pointer_t>::template
         rebind_pointer<const void>::type          cvoid_ptr;

   //Pointer to the allocator
   typedef typename boost::intrusive::
      pointer_traits<cvoid_ptr>::template
         rebind_pointer<segment_manager>::type          alloc_ptr_t;

   //Not assignable from related allocator
   template<class T2, class SegmentManager2>
   allocator& operator=(const allocator<T2, SegmentManager2>&);

   //Not assignable from other allocator
   allocator& operator=(const allocator&);

   //Pointer to the allocator
   alloc_ptr_t mp_mngr;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef T                                    value_type;
   typedef typename boost::intrusive::
      pointer_traits<cvoid_ptr>::template
         rebind_pointer<T>::type                pointer;
   typedef typename boost::intrusive::
      pointer_traits<pointer>::template
         rebind_pointer<const T>::type          const_pointer;
   typedef typename ipcdetail::add_reference
                     <value_type>::type         reference;
   typedef typename ipcdetail::add_reference
                     <const value_type>::type   const_reference;
   typedef typename segment_manager::size_type               size_type;
   typedef typename segment_manager::difference_type         difference_type;

   typedef boost::interprocess::version_type<allocator, 2>   version;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   //Experimental. Don't use.
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   //!Obtains an allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef allocator<T2, SegmentManager>     other;
   };

   //!Returns the segment manager.
   //!Never throws
   segment_manager* get_segment_manager()const
   {  return ipcdetail::to_raw_pointer(mp_mngr);   }

   //!Constructor from the segment manager.
   //!Never throws
   allocator(segment_manager *segment_mngr)
      : mp_mngr(segment_mngr) { }

   //!Constructor from other allocator.
   //!Never throws
   allocator(const allocator &other)
      : mp_mngr(other.get_segment_manager()){ }

   //!Constructor from related allocator.
   //!Never throws
   template<class T2>
   allocator(const allocator<T2, SegmentManager> &other)
      : mp_mngr(other.get_segment_manager()){}

   //!Allocates memory for an array of count elements.
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate(size_type count, cvoid_ptr hint = 0)
   {
      (void)hint;
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      return pointer(static_cast<value_type*>(mp_mngr->allocate(count*sizeof(T))));
   }

   //!Deallocates memory previously allocated.
   //!Never throws
   void deallocate(const pointer &ptr, size_type)
   {  mp_mngr->deallocate((void*)ipcdetail::to_raw_pointer(ptr));  }

   //!Returns the number of elements that could be allocated.
   //!Never throws
   size_type max_size() const
   {  return mp_mngr->get_size()/sizeof(T);   }

   //!Swap segment manager. Does not throw. If each allocator is placed in
   //!different memory segments, the result is undefined.
   friend void swap(self_t &alloc1, self_t &alloc2)
   {  boost::adl_move_swap(alloc1.mp_mngr, alloc2.mp_mngr);   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold. This size only works for memory allocated with
   //!allocate, allocation_command and allocate_many.
   size_type size(const pointer &p) const
   {
      return (size_type)mp_mngr->size(ipcdetail::to_raw_pointer(p))/sizeof(T);
   }

   pointer allocation_command(boost::interprocess::allocation_type command,
                           size_type limit_size, size_type &prefer_in_recvd_out_size, pointer &reuse)
   {
      value_type *reuse_raw = ipcdetail::to_raw_pointer(reuse);
      pointer const p = mp_mngr->allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse_raw);
      reuse = reuse_raw;
      return p;
   }

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void allocate_many(size_type elem_size, size_type num_elements, multiallocation_chain &chain)
   {
      if(size_overflows<sizeof(T)>(elem_size)){
         throw bad_alloc();
      }
      mp_mngr->allocate_many(elem_size*sizeof(T), num_elements, chain);
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]in a
   //!contiguous block
   //!of memory. The elements must be deallocated
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      mp_mngr->allocate_many(elem_sizes, n_elements, sizeof(T), chain);
   }

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void deallocate_many(multiallocation_chain &chain)
   {  mp_mngr->deallocate_many(chain); }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate_one()
   {  return this->allocate(1);  }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void allocate_individual(size_type num_elements, multiallocation_chain &chain)
   {  this->allocate_many(1, num_elements, chain); }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(const pointer &p)
   {  return this->deallocate(p, 1);  }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void deallocate_individual(multiallocation_chain &chain)
   {  this->deallocate_many(chain); }

   //!Returns address of mutable object.
   //!Never throws
   pointer address(reference value) const
   {  return pointer(boost::addressof(value));  }

   //!Returns address of non mutable object.
   //!Never throws
   const_pointer address(const_reference value) const
   {  return const_pointer(boost::addressof(value));  }

   //!Constructs an object
   //!Throws if T's constructor throws
   //!For backwards compatibility with libraries using C++03 allocators
   template<class P>
   void construct(const pointer &ptr, BOOST_FWD_REF(P) p)
   {  ::new((void*)ipcdetail::to_raw_pointer(ptr), boost_container_new_t()) value_type(::boost::forward<P>(p));  }

   //!Destroys object. Throws if object's
   //!destructor throws
   void destroy(const pointer &ptr)
   {  BOOST_ASSERT(ptr != 0); (*ptr).~value_type();  }

};

//!Equality test for same type
//!of allocator
template<class T, class SegmentManager> inline
bool operator==(const allocator<T , SegmentManager>  &alloc1,
                const allocator<T, SegmentManager>  &alloc2)
   {  return alloc1.get_segment_manager() == alloc2.get_segment_manager(); }

//!Inequality test for same type
//!of allocator
template<class T, class SegmentManager> inline
bool operator!=(const allocator<T, SegmentManager>  &alloc1,
                const allocator<T, SegmentManager>  &alloc2)
   {  return alloc1.get_segment_manager() != alloc2.get_segment_manager(); }

}  //namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

template<class T>
struct has_trivial_destructor;

template<class T, class SegmentManager>
struct has_trivial_destructor
   <boost::interprocess::allocator <T, SegmentManager> >
{
   static const bool value = true;
};
#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_ALLOCATOR_HPP


/* allocator.hpp
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
*/