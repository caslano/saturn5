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