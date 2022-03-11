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