//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ADAPTIVE_POOL_HPP
#define BOOST_INTERPROCESS_ADAPTIVE_POOL_HPP

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
#include <boost/interprocess/allocators/detail/adaptive_node_pool.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <cstddef>

//!\file
//!Describes adaptive_pool pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail{

template < unsigned int Version
         , class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         , std::size_t MaxFreeBlocks
         , unsigned char OverheadPercent
         >
class adaptive_pool_base
   : public node_pool_allocation_impl
   < adaptive_pool_base
      < Version, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>
   , Version
   , T
   , SegmentManager
   >
{
   public:
   typedef typename SegmentManager::void_pointer         void_pointer;
   typedef SegmentManager                                segment_manager;
   typedef adaptive_pool_base
      <Version, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>   self_t;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

   template <int dummy>
   struct node_pool
   {
      typedef ipcdetail::shared_adaptive_node_pool
      < SegmentManager, sizeof_value<T>::value, NodesPerBlock, MaxFreeBlocks, OverheadPercent> type;

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

   typedef boost::interprocess::version_type<adaptive_pool_base, Version>   version;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;

   //!Obtains adaptive_pool_base from
   //!adaptive_pool_base
   template<class T2>
   struct rebind
   {
      typedef adaptive_pool_base<Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>       other;
   };

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //!Not assignable from related adaptive_pool_base
   template<unsigned int Version2, class T2, class SegmentManager2, std::size_t N2, std::size_t F2, unsigned char O2>
   adaptive_pool_base& operator=
      (const adaptive_pool_base<Version2, T2, SegmentManager2, N2, F2, O2>&);

   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   adaptive_pool_base(segment_manager *segment_mngr)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(segment_mngr)) { }

   //!Copy constructor from other adaptive_pool_base. Increments the reference
   //!count of the associated node pool. Never throws
   adaptive_pool_base(const adaptive_pool_base &other)
      : mp_node_pool(other.get_node_pool())
   {
      node_pool<0>::get(ipcdetail::to_raw_pointer(mp_node_pool))->inc_ref_count();
   }

   //!Assignment from other adaptive_pool_base
   adaptive_pool_base& operator=(const adaptive_pool_base &other)
   {
      adaptive_pool_base c(other);
      boost::adl_move_swap(*this, c);
      return *this;
   }

   //!Copy constructor from related adaptive_pool_base. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   adaptive_pool_base
      (const adaptive_pool_base<Version, T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
      : mp_node_pool(ipcdetail::get_or_create_node_pool<typename node_pool<0>::type>(other.get_segment_manager())) { }

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~adaptive_pool_base()
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
//!of adaptive_pool_base
template<unsigned int V, class T, class S, std::size_t NPC, std::size_t F, unsigned char OP> inline
bool operator==(const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc1,
                const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

//!Inequality test for same type
//!of adaptive_pool_base
template<unsigned int V, class T, class S, std::size_t NPC, std::size_t F, unsigned char OP> inline
bool operator!=(const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc1,
                const adaptive_pool_base<V, T, S, NPC, F, OP> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         , std::size_t MaxFreeBlocks = 2
         , unsigned char OverheadPercent = 5
         >
class adaptive_pool_v1
   :  public adaptive_pool_base
         < 1
         , T
         , SegmentManager
         , NodesPerBlock
         , MaxFreeBlocks
         , OverheadPercent
         >
{
   public:
   typedef ipcdetail::adaptive_pool_base
         < 1, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> base_t;

   template<class T2>
   struct rebind
   {
      typedef adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   adaptive_pool_v1(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   adaptive_pool_v1
      (const adaptive_pool_v1<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
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
//!This node allocator shares a segregated storage between all instances
//!of adaptive_pool with equal sizeof(T) placed in the same segment
//!group. NodesPerBlock is the number of nodes allocated at once when the allocator
//!needs runs out of nodes. MaxFreeBlocks is the maximum number of totally free blocks
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
class adaptive_pool
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::adaptive_pool_base
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
   typedef ipcdetail::adaptive_pool_base
         < 2, T, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> base_t;
   public:
   typedef boost::interprocess::version_type<adaptive_pool, 2>   version;

   template<class T2>
   struct rebind
   {
      typedef adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent>  other;
   };

   adaptive_pool(SegmentManager *segment_mngr)
      : base_t(segment_mngr)
   {}

   template<class T2>
   adaptive_pool
      (const adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other)
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

   //!Obtains adaptive_pool from
   //!adaptive_pool
   template<class T2>
   struct rebind
   {
      typedef adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> other;
   };

   private:
   //!Not assignable from
   //!related adaptive_pool
   template<class T2, class SegmentManager2, std::size_t N2, std::size_t F2, unsigned char OP2>
   adaptive_pool& operator=
      (const adaptive_pool<T2, SegmentManager2, N2, F2, OP2>&);

   //!Not assignable from
   //!other adaptive_pool
   //adaptive_pool& operator=(const adaptive_pool&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   adaptive_pool(segment_manager *segment_mngr);

   //!Copy constructor from other adaptive_pool. Increments the reference
   //!count of the associated node pool. Never throws
   adaptive_pool(const adaptive_pool &other);

   //!Copy constructor from related adaptive_pool. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   adaptive_pool
      (const adaptive_pool<T2, SegmentManager, NodesPerBlock, MaxFreeBlocks, OverheadPercent> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~adaptive_pool();

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
/*
   //!Copy construct an object.
   //!Throws if T's copy constructor throws
   void construct(const pointer &ptr, const_reference v);

   //!Destroys object. Throws if object's
   //!destructor throws
   void destroy(const pointer &ptr);
*/
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
//!of adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator==(const adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

//!Inequality test for same type
//!of adaptive_pool
template<class T, class S, std::size_t NodesPerBlock, std::size_t F, unsigned char OP> inline
bool operator!=(const adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc1,
                const adaptive_pool<T, S, NodesPerBlock, F, OP> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_ADAPTIVE_POOL_HPP


/* adaptive_pool.hpp
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
*/