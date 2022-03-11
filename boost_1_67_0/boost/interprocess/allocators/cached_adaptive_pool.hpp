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