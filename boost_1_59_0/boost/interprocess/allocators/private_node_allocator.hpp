//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PRIVATE_NODE_ALLOCATOR_HPP
#define BOOST_INTERPROCESS_PRIVATE_NODE_ALLOCATOR_HPP

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
#include <boost/interprocess/allocators/detail/node_pool.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

//!\file
//!Describes private_node_allocator_base pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

template < unsigned int Version
         , class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class private_node_allocator_base
   : public node_pool_allocation_impl
   < private_node_allocator_base < Version, T, SegmentManager, NodesPerBlock>
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
   typedef private_node_allocator_base
      < Version, T, SegmentManager, NodesPerBlock>       self_t;
   typedef ipcdetail::private_node_pool
      <SegmentManager
      , sizeof_value<T>::value
      , NodesPerBlock
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
      <private_node_allocator_base, Version>              version;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;

   //!Obtains node_allocator from other node_allocator
   template<class T2>
   struct rebind
   {
      typedef private_node_allocator_base
         <Version, T2, SegmentManager, NodesPerBlock>   other;
   };

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   template <int dummy>
   struct node_pool
   {
      typedef ipcdetail::private_node_pool
      <SegmentManager
      , sizeof_value<T>::value
      , NodesPerBlock
      > type;

      static type *get(void *p)
      {  return static_cast<type*>(p);  }
   };

   private:
   //!Not assignable from related private_node_allocator_base
   template<unsigned int Version2, class T2, class MemoryAlgorithm2, std::size_t N2>
   private_node_allocator_base& operator=
      (const private_node_allocator_base<Version2, T2, MemoryAlgorithm2, N2>&);

   //!Not assignable from other private_node_allocator_base
   private_node_allocator_base& operator=(const private_node_allocator_base&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor from a segment manager
   private_node_allocator_base(segment_manager *segment_mngr)
      : m_node_pool(segment_mngr)
   {}

   //!Copy constructor from other private_node_allocator_base. Never throws
   private_node_allocator_base(const private_node_allocator_base &other)
      : m_node_pool(other.get_segment_manager())
   {}

   //!Copy constructor from related private_node_allocator_base. Never throws.
   template<class T2>
   private_node_allocator_base
      (const private_node_allocator_base
         <Version, T2, SegmentManager, NodesPerBlock> &other)
      : m_node_pool(other.get_segment_manager())
   {}

   //!Destructor, frees all used memory. Never throws
   ~private_node_allocator_base()
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

//!Equality test for same type of private_node_allocator_base
template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator==(const private_node_allocator_base<V, T, S, NPC> &alloc1,
                const private_node_allocator_base<V, T, S, NPC> &alloc2)
{  return &alloc1 == &alloc2; }

//!Inequality test for same type of private_node_allocator_base
template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator!=(const private_node_allocator_base<V, T, S, NPC> &alloc1,
                const private_node_allocator_base<V, T, S, NPC> &alloc2)
{  return &alloc1 != &alloc2; }

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         >
class private_node_allocator_v1
   :  public private_node_allocator_base
         < 1
         , T
         , SegmentManager
         , NodesPerBlock
         >
{
   public:
   typedef ipcdetail::private_node_allocator_base
         < 1, T, SegmentManager, NodesPerBlock> base_t;

   template<class T2>
   struct rebind
   {
      typedef private_node_allocator_v1<T2, SegmentManager, NodesPerBlock>  other;
   };

   private_node_allocator_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   private_node_allocator_v1
      (const private_node_allocator_v1<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail {

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!An STL node allocator that uses a segment manager as memory
//!source. The internal pointer type will of the same type (raw, smart) as
//!"typename SegmentManager::void_pointer" type. This allows
//!placing the allocator in shared memory, memory mapped-files, etc...
//!This allocator has its own node pool. NodesPerBlock is the number of nodes allocated
//!at once when the allocator needs runs out of nodes
template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class private_node_allocator
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::private_node_allocator_base
         < 2
         , T
         , SegmentManager
         , NodesPerBlock
         >
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   typedef ipcdetail::private_node_allocator_base
         < 2, T, SegmentManager, NodesPerBlock> base_t;
   public:
   typedef boost::interprocess::version_type<private_node_allocator, 2>   version;

   template<class T2>
   struct rebind
   {
      typedef private_node_allocator
         <T2, SegmentManager, NodesPerBlock>  other;
   };

   private_node_allocator(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   private_node_allocator
      (const private_node_allocator<T2, SegmentManager, NodesPerBlock> &other)
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
   typedef typename segment_manage::difference_type      difference_type;

   //!Obtains private_node_allocator from
   //!private_node_allocator
   template<class T2>
   struct rebind
   {
      typedef private_node_allocator
         <T2, SegmentManager, NodesPerBlock> other;
   };

   private:
   //!Not assignable from
   //!related private_node_allocator
   template<class T2, class SegmentManager2, std::size_t N2>
   private_node_allocator& operator=
      (const private_node_allocator<T2, SegmentManager2, N2>&);

   //!Not assignable from
   //!other private_node_allocator
   private_node_allocator& operator=(const private_node_allocator&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   private_node_allocator(segment_manager *segment_mngr);

   //!Copy constructor from other private_node_allocator. Increments the reference
   //!count of the associated node pool. Never throws
   private_node_allocator(const private_node_allocator &other);

   //!Copy constructor from related private_node_allocator. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   private_node_allocator
      (const private_node_allocator<T2, SegmentManager, NodesPerBlock> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~private_node_allocator();

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
//!of private_node_allocator
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator==(const private_node_allocator<T, S, NodesPerBlock, F, OP> &alloc1,
                const private_node_allocator<T, S, NodesPerBlock, F, OP> &alloc2);

//!Inequality test for same type
//!of private_node_allocator
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator!=(const private_node_allocator<T, S, NodesPerBlock, F, OP> &alloc1,
                const private_node_allocator<T, S, NodesPerBlock, F, OP> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_PRIVATE_NODE_ALLOCATOR_HPP


/* private_node_allocator.hpp
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
*/