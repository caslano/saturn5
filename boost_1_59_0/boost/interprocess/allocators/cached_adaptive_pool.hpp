//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CACHED_ADAPTIVE_POOL_HPP
#define BOOST_INTERPROCESS_CACHED_ADAPTIVE_POOL_HPP

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
#include <boost/interprocess/allocators/detail/adaptive_node_pool.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/allocators/detail/node_tools.hpp>
#include <cstddef>

//!\file
//!Describes cached_adaptive_pool pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         , std::size_t MaxFreeBlocks = 2
         , unsigned char OverheadPercent = 5
         >
class cached_adaptive_pool_v1
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_adaptive_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            , MaxFreeBlocks
            , OverheadPercent
            >
         , 1>
{
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_adaptive_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            , MaxFreeBlocks
            , OverheadPercent
            >
         , 1> base_t;

   template<class T2>
   struct rebind
   {
      typedef cached_adaptive_pool_v1
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   typedef typename base_t::size_type size_type;

   cached_adaptive_pool_v1(SegmentManager *segment_mngr,
                           size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_adaptive_pool_v1
      (const cached_adaptive_pool_v1
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail{

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!An STL node allocator that uses a segment manager as memory
//!source. The internal pointer type will of the same type (raw, smart) as
//!"typename SegmentManager::void_pointer" type. This allows
//!placing the allocator in shared memory, memory mapped-files, etc...
//!
//!This node allocator shares a segregated storage between all instances of
//!cached_adaptive_pool with equal sizeof(T) placed in the same
//!memory segment. But also caches some nodes privately to
//!avoid some synchronization overhead.
//!
//!NodesPerBlock is the minimum number of nodes of nodes allocated at once when
//!the allocator needs runs out of nodes. MaxFreeBlocks is the maximum number of totally free blocks
//!that the adaptive node pool will hold. The rest of the totally free blocks will be
//!deallocated with the segment manager.
//!
//!OverheadPercent is the (approximated) maximum size overhead (1-20%) of the allocator:
//!(memory usable for nodes / total memory allocated from the segment manager)
template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         , std::size_t MaxFreeBlocks
         , unsigned char OverheadPercent
         >
class cached_adaptive_pool
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_adaptive_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            , MaxFreeBlocks
            , OverheadPercent
            >
         , 2>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_adaptive_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            , MaxFreeBlocks
            , OverheadPercent
            >
         , 2> base_t;

   public:
   typedef boost::interprocess::version_type<cached_adaptive_pool, 2>   version;

   template<class T2>
   struct rebind
   {
      typedef cached_adaptive_pool
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   cached_adaptive_pool(SegmentManager *segment_mngr,
                         std::size_t max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_adaptive_pool
      (const cached_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
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
   typedef typename segment_manager::size_type           size_type;
   typedef typename segment_manager::difference_type     difference_type;

   //!Obtains cached_adaptive_pool from
   //!cached_adaptive_pool
   template<class T2>
   struct rebind
   {
      typedef cached_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> other;
   };

   private:
   //!Not assignable from
   //!related cached_adaptive_pool
   template<class T2, class SegmentManager2, std::size_t N2, std::size_t F2, unsigned char OP2>
   cached_adaptive_pool& operator=
      (const cached_adaptive_pool<T2, SegmentManager2, N2, F2, OP2>&);

   //!Not assignable from
   //!other cached_adaptive_pool
   cached_adaptive_pool& operator=(const cached_adaptive_pool&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   cached_adaptive_pool(segment_manager *segment_mngr);

   //!Copy constructor from other cached_adaptive_pool. Increments the reference
   //!count of the associated node pool. Never throws
   cached_adaptive_pool(const cached_adaptive_pool &other);

   //!Copy constructor from related cached_adaptive_pool. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   cached_adaptive_pool
      (const cached_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~cached_adaptive_pool();

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

   //!Copy construct an object.
   //!Throws if T's copy constructor throws
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
   void deallocate_individual(multiallocation_chain &chain);
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
//!of cached_adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, std::size_t OP> inline
bool operator==(const cached_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const cached_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

//!Inequality test for same type
//!of cached_adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, std::size_t OP> inline
bool operator!=(const cached_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const cached_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_CACHED_ADAPTIVE_POOL_HPP


/* cached_adaptive_pool.hpp
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
*/