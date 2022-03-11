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