//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP
#define BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/interprocess/allocators/detail/node_pool.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/allocators/detail/node_tools.hpp>
#include <cstddef>

//!\file
//!Describes cached_cached_node_allocator pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {


#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         >
class cached_node_allocator_v1
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 1>
{
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 1> base_t;

   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator_v1
         <T2, SegmentManager, NodesPerBlock>  other;
   };

   typedef typename base_t::size_type size_type;

   cached_node_allocator_v1(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_node_allocator_v1
      (const cached_node_allocator_v1
         <T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail{

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class cached_node_allocator
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 2>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 2> base_t;

   public:
   typedef boost::interprocess::version_type<cached_node_allocator, 2>   version;
   typedef typename base_t::size_type size_type;

   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator<T2, SegmentManager, NodesPerBlock>  other;
   };

   cached_node_allocator(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_node_allocator
      (const cached_node_allocator<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}

   #else
   public:
   typedef implementation_defined::segment_manager       segment_manager;
   typedef segment_manager::void_pointer                 void_pointer;
   typedef implementation_defined::pointer               pointer;
   typedef implementation_defined::const_pointer         const_pointer;
   typedef T                                             value_type;
   typedef typename ipcdetail::add_reference
                     <value_type>::type                  reference;
   typedef typename ipcdetail::add_reference
                     <const value_type>::type            const_reference;
   typedef typename SegmentManager::size_type            size_type;
   typedef typename SegmentManager::difference_type      difference_type;

   //!Obtains cached_node_allocator from
   //!cached_node_allocator
   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator<T2, SegmentManager> other;
   };

   private:
   //!Not assignable from
   //!related cached_node_allocator
   template<class T2, class SegmentManager2, std::size_t N2>
   cached_node_allocator& operator=
      (const cached_node_allocator<T2, SegmentManager2, N2>&);

   //!Not assignable from
   //!other cached_node_allocator
   cached_node_allocator& operator=(const cached_node_allocator&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   cached_node_allocator(segment_manager *segment_mngr);

   //!Copy constructor from other cached_node_allocator. Increments the reference
   //!count of the associated node pool. Never throws
   cached_node_allocator(const cached_node_allocator &other);

   //!Copy constructor from related cached_node_allocator. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   cached_node_allocator
      (const cached_node_allocator<T2, SegmentManager, NodesPerBlock> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~cached_node_allocator();

   //!Returns a pointer to the node pool.
   //!Never throws
   node_pool_t* get_node_pool() const;

   //!Returns the segment manager.
   //!Never throws
   segment_manager* get_segment_manager()const;

   //!Returns the number of elements that could be allocated.
   //!Never throws
   size_type max_size() const;

   //!Allocate memory for an array of count elements.
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate(size_type count, cvoid_pointer hint = 0);

   //!Deallocate allocated memory.
   //!Never throws
   void deallocate(const pointer &ptr, size_type count);

   //!Deallocates all free blocks
   //!of the pool
   void deallocate_free_blocks();

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different memory segment, the result is undefined.
   friend void swap(self_t &alloc1, self_t &alloc2);

   //!Returns address of mutable object.
   //!Never throws
   pointer address(reference value) const;

   //!Returns address of non mutable object.
   //!Never throws
   const_pointer address(const_reference value) const;

   //!Default construct an object.
   //!Throws if T's default constructor throws
   void construct(const pointer &ptr, const_reference v);

   //!Destroys object. Throws if object's
   //!destructor throws
   void destroy(const pointer &ptr);

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold. This size only works for memory allocated with
   //!allocate, allocation_command and allocate_many.
   size_type size(const pointer &p) const;

   pointer allocation_command(boost::interprocess::allocation_type command,
                           size_type limit_size, size_type &prefer_in_recvd_out_size, pointer &reuse);

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void allocate_many(size_type elem_size, size_type num_elements, multiallocation_chain &chain);

   //!Allocates n_elements elements, each one of size elem_sizes[i]in a
   //!contiguous block
   //!of memory. The elements must be deallocated
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain);

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void deallocate_many(multiallocation_chain &chain);

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate_one();

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   multiallocation_chain allocate_individual(size_type num_elements);

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(const pointer &p);

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void deallocate_individual(multiallocation_chain it);
   //!Sets the new max cached nodes value. This can provoke deallocations
   //!if "newmax" is less than current cached nodes. Never throws
   void set_max_cached_nodes(size_type newmax);

   //!Returns the max cached nodes parameter.
   //!Never throws
   size_type get_max_cached_nodes() const;
   #endif
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Equality test for same type
//!of cached_node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator==(const cached_node_allocator<T, S, NPC> &alloc1,
                const cached_node_allocator<T, S, NPC> &alloc2);

//!Inequality test for same type
//!of cached_node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator!=(const cached_node_allocator<T, S, NPC> &alloc1,
                const cached_node_allocator<T, S, NPC> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP


/* cached_node_allocator.hpp
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
*/