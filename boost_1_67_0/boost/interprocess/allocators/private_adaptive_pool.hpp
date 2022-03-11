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
   typedef typename segment_manager::size_type           difference_type;
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