//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PRIVATE_ADAPTIVE_POOL_HPP
#define BOOST_INTERPROCESS_PRIVATE_ADAPTIVE_POOL_HPP

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
#include <boost/assert.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/interprocess/allocators/detail/adaptive_node_pool.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

//!\file
//!Describes private_adaptive_pool_base pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

template < unsigned int Version
         , class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         , std::size_t MaxFreeBlocks
         , unsigned char OverheadPercent
         >
class private_adaptive_pool_base
   : public node_pool_allocation_impl
   < private_adaptive_pool_base < Version, T, SegmentManager, NodesPerBlock
                                , MaxFreeBlocks, OverheadPercent>
   , Version
   , T
   , SegmentManager
   >
{
   public:
   //Segment manager
   typedef SegmentManager                                segment_manager;
   typedef typename SegmentManager::void_pointer         void_pointer;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef private_adaptive_pool_base
      < Version, T, SegmentManager, NodesPerBlock
      , MaxFreeBlocks, OverheadPercent>                  self_t;
   typedef ipcdetail::private_adaptive_node_pool
      <SegmentManager
      , sizeof_value<T>::value
      , NodesPerBlock
      , MaxFreeBlocks
      , OverheadPercent
      > node_pool_t;

   BOOST_STATIC_ASSERT((Version <=2));

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<T>::type                         pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<const T>::type                   const_pointer;
   typedef T                                             value_type;
   typedef typename ipcdetail::add_reference
                     <value_type>::type                  reference;
   typedef typename ipcdetail::add_reference
                     <const value_type>::type            const_reference;
   typedef typename segment_manager::size_type           size_type;
   typedef typename segment_manager::difference_type     difference_type;
   typedef boost::interprocess::version_type
      <private_adaptive_pool_base, Version>              version;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;

   //!Obtains node_allocator from other node_allocator
   template<class T2>
   struct rebind
   {
      typedef private_adaptive_pool_base
         <Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>   other;
   };

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   template <int dummy>
   struct node_pool
   {
      typedef ipcdetail::private_adaptive_node_pool
      <SegmentManager
      , sizeof_value<T>::value
      , NodesPerBlock
      , MaxFreeBlocks
      , OverheadPercent
      > type;

      static type *get(void *p)
      {  return static_cast<type*>(p);  }
   };

   private:
   //!Not assignable from related private_adaptive_pool_base
   template<unsigned int Version2, class T2, class MemoryAlgorithm2, std::size_t N2, std::size_t F2, unsigned char OP2>
   private_adaptive_pool_base& operator=
      (const private_adaptive_pool_base<Version2, T2, MemoryAlgorithm2, N2, F2, OP2>&);

   //!Not assignable from other private_adaptive_pool_base
   private_adaptive_pool_base& operator=(const private_adaptive_pool_base&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor from a segment manager
   private_adaptive_pool_base(segment_manager *segment_mngr)
      : m_node_pool(segment_mngr)
   {}

   //!Copy constructor from other private_adaptive_pool_base. Never throws
   private_adaptive_pool_base(const private_adaptive_pool_base &other)
      : m_node_pool(other.get_segment_manager())
   {}

   //!Copy constructor from related private_adaptive_pool_base. Never throws.
   template<class T2>
   private_adaptive_pool_base
      (const private_adaptive_pool_base
         <Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : m_node_pool(other.get_segment_manager())
   {}

   //!Destructor, frees all used memory. Never throws
   ~private_adaptive_pool_base()
   {}

   //!Returns the segment manager. Never throws
   segment_manager* get_segment_manager()const
   {  return m_node_pool.get_segment_manager(); }

   //!Returns the internal node pool. Never throws
   node_pool_t* get_node_pool() const
   {  return const_cast<node_pool_t*>(&m_node_pool); }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different shared memory segments, the result is undefined.
   friend void swap(self_t &alloc1,self_t &alloc2)
   {  boost::adl_move_swap(alloc1.m_node_pool, alloc2.m_node_pool);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   node_pool_t m_node_pool;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!Equality test for same type of private_adaptive_pool_base
template<unsigned int V, class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator==(const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc2)
{  return &alloc1 == &alloc2; }

//!Inequality test for same type of private_adaptive_pool_base
template<unsigned int V, class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator!=(const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool_base<V, T, S, NodesPerBlock, F, OP> &alloc2)
{  return &alloc1 != &alloc2; }

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         , std::size_t MaxFreeBlocks = 2
         , unsigned char OverheadPercent = 5
         >
class private_adaptive_pool_v1
   :  public private_adaptive_pool_base
         < 1
         , T
         , SegmentManager
         , NodesPerBlock
         , MaxFreeBlocks
         , OverheadPercent
         >
{
   public:
   typedef ipcdetail::private_adaptive_pool_base
         < 1, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> base_t;

   template<class T2>
   struct rebind
   {
      typedef private_adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   private_adaptive_pool_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   private_adaptive_pool_v1
      (const private_adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail {

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!An STL node allocator that uses a segment manager as memory
//!source. The internal pointer type will of the same type (raw, smart) as
//!"typename SegmentManager::void_pointer" type. This allows
//!placing the allocator in shared memory, memory mapped-files, etc...
//!This allocator has its own node pool.
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
class private_adaptive_pool
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::private_adaptive_pool_base
         < 2
         , T
         , SegmentManager
         , NodesPerBlock
         , MaxFreeBlocks
         , OverheadPercent
         >
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   typedef ipcdetail::private_adaptive_pool_base
         < 2, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> base_t;
   public:
   typedef boost::interprocess::version_type<private_adaptive_pool, 2>   version;

   template<class T2>
   struct rebind
   {
      typedef private_adaptive_pool
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   private_adaptive_pool(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   private_adaptive_pool
      (const private_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
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

   //!Obtains private_adaptive_pool from
   //!private_adaptive_pool
   template<class T2>
   struct rebind
   {
      typedef private_adaptive_pool
         <T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> other;
   };

   private:
   //!Not assignable from
   //!related private_adaptive_pool
   template<class T2, class SegmentManager2, std::size_t N2, std::size_t F2, unsigned char OP2>
   private_adaptive_pool& operator=
      (const private_adaptive_pool<T2, SegmentManager2, N2, F2>&);

   //!Not assignable from
   //!other private_adaptive_pool
   private_adaptive_pool& operator=(const private_adaptive_pool&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   private_adaptive_pool(segment_manager *segment_mngr);

   //!Copy constructor from other private_adaptive_pool. Increments the reference
   //!count of the associated node pool. Never throws
   private_adaptive_pool(const private_adaptive_pool &other);

   //!Copy constructor from related private_adaptive_pool. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   private_adaptive_pool
      (const private_adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~private_adaptive_pool();

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
   void allocate_individual(size_type num_elements, multiallocation_chain &chain);

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
   #endif
};

#ifdef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Equality test for same type
//!of private_adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator==(const private_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

//!Inequality test for same type
//!of private_adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator!=(const private_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const private_adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_PRIVATE_ADAPTIVE_POOL_HPP


/* private_adaptive_pool.hpp
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
*/