//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_NODE_ALLOCATOR_HPP
#define BOOST_INTERPROCESS_NODE_ALLOCATOR_HPP

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
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/allocators/detail/node_pool.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

//!\file
//!Describes node_allocator pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail{

template < unsigned int Version
         , class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class node_allocator_base
   : public node_pool_allocation_impl
   < node_allocator_base
      < Version, T, SegmentManager, NodesPerBlock>
   , Version
   , T
   , SegmentManager
   >
{
   public:
   typedef typename SegmentManager::void_pointer         void_pointer;
   typedef SegmentManager                                segment_manager;
   typedef node_allocator_base
      <Version, T, SegmentManager, NodesPerBlock>   self_t;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   template <int dummy>
   struct node_pool
   {
      typedef ipcdetail::shared_node_pool
      < SegmentManager, sizeof_value<T>::value, NodesPerBlock> type;

      static type *get(void *p)
      {  return static_cast<type*>(p);  }
   };
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   BOOST_STATIC_ASSERT((Version <=2));

   public:
   //-------
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

   typedef boost::interprocess::version_type<node_allocator_base, Version>   version;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;

   //!Obtains node_allocator_base from
   //!node_allocator_base
   template<class T2>
   struct rebind
   {
      typedef node_allocator_base<Version, T2, SegmentManager, NodesPerBlock>       other;
   };

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Not assignable from related node_allocator_base
   template<unsigned int Version2, class T2, class SegmentManager2, std::size_t N2>
   node_allocator_base& operator=
      (const node_allocator_base<Version2, T2, SegmentManager2, N2>&);

   //!Not assignable from other node_allocator_base
   //node_allocator_base& operator=(const node_allocator_base&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   node_allocator_base(segment_manager *segment_mngr)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(segment_mngr)) { }

   //!Copy constructor from other node_allocator_base. Increments the reference
   //!count of the associated node pool. Never throws
   node_allocator_base(const node_allocator_base &other)
      : mp_node_pool(other.get_node_pool())
   {
      node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->inc_ref_count();
   }

   //!Copy constructor from related node_allocator_base. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   node_allocator_base
      (const node_allocator_base<Version, T2, SegmentManager, NodesPerBlock> &other)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(other.get_segment_manager())) { }

   //!Assignment from other node_allocator_base
   node_allocator_base& operator=(const node_allocator_base &other)
   {
      node_allocator_base c(other);
      boost::adl_move_swap(*this, c);
      return *this;
   }

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~node_allocator_base()
   {  ipcdetail::destroy_node_pool_if_last_link(node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool)));   }

   //!Returns a pointer to the node pool.
   //!Never throws
   void* get_node_pool() const
   {  return ipcdetail::to_raw_pointer(mp_node_pool);   }

   //!Returns the segment manager.
   //!Never throws
   segment_manager* get_segment_manager()const
   {  return node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->get_segment_manager();  }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different memory segment, the result is undefined.
   friend void swap(self_t &alloc1, self_t &alloc2)
   {  boost::adl_move_swap(alloc1.mp_node_pool, alloc2.mp_node_pool);  }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   void_pointer   mp_node_pool;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!Equality test for same type
//!of node_allocator_base
template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator==(const node_allocator_base<V, T, S, NPC> &alloc1,
                const node_allocator_base<V, T, S, NPC> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

//!Inequality test for same type
//!of node_allocator_base
template<unsigned int V, class T, class S, std::size_t NPC> inline
bool operator!=(const node_allocator_base<V, T, S, NPC> &alloc1,
                const node_allocator_base<V, T, S, NPC> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         >
class node_allocator_v1
   :  public node_allocator_base
         < 1
         , T
         , SegmentManager
         , NodesPerBlock
         >
{
   public:
   typedef ipcdetail::node_allocator_base
         < 1, T, SegmentManager, NodesPerBlock> base_t;

   template<class T2>
   struct rebind
   {
      typedef node_allocator_v1<T2, SegmentManager, NodesPerBlock>  other;
   };

   node_allocator_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   node_allocator_v1
      (const node_allocator_v1<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail{

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!An STL node allocator that uses a segment manager as memory
//!source. The internal pointer type will of the same type (raw, smart) as
//!"typename SegmentManager::void_pointer" type. This allows
//!placing the allocator in shared memory, memory mapped-files, etc...
//!This node allocator shares a segregated storage between all instances
//!of node_allocator with equal sizeof(T) placed in the same segment
//!group. NodesPerBlock is the number of nodes allocated at once when the allocator
//!runs out of nodes
template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class node_allocator
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::node_allocator_base
         < 2
         , T
         , SegmentManager
         , NodesPerBlock
         >
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   typedef ipcdetail::node_allocator_base
         < 2, T, SegmentManager, NodesPerBlock> base_t;
   public:
   typedef boost::interprocess::version_type<node_allocator, 2>   version;

   template<class T2>
   struct rebind
   {
      typedef node_allocator<T2, SegmentManager, NodesPerBlock>  other;
   };

   node_allocator(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   node_allocator
      (const node_allocator<T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}

   #else //BOOST_INTERPROCESS_DOXYGEN_INVOKED
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

   //!Obtains node_allocator from
   //!node_allocator
   template<class T2>
   struct rebind
   {
      typedef node_allocator<T2, SegmentManager, NodesPerBlock> other;
   };

   private:
   //!Not assignable from
   //!related node_allocator
   template<class T2, class SegmentManager2, std::size_t N2>
   node_allocator& operator=
      (const node_allocator<T2, SegmentManager2, N2>&);

   //!Not assignable from
   //!other node_allocator
   //node_allocator& operator=(const node_allocator&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   node_allocator(segment_manager *segment_mngr);

   //!Copy constructor from other node_allocator. Increments the reference
   //!count of the associated node pool. Never throws
   node_allocator(const node_allocator &other);

   //!Copy constructor from related node_allocator. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   node_allocator
      (const node_allocator<T2, SegmentManager, NodesPerBlock> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~node_allocator();

   //!Returns a pointer to the node pool.
   //!Never throws
   void* get_node_pool() const;

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
//!of node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator==(const node_allocator<T, S, NPC> &alloc1,
                const node_allocator<T, S, NPC> &alloc2);

//!Inequality test for same type
//!of node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator!=(const node_allocator<T, S, NPC> &alloc1,
                const node_allocator<T, S, NPC> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_NODE_ALLOCATOR_HPP

/* node_allocator.hpp
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
*/