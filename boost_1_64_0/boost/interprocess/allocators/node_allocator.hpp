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
+R+OH47/wqPtcOHv7pH/cPy/HAnxwZDKGt838vnH90/+Sn7HxMBvJMpZ30uY3lb44fjugzZS+e8IYbiQx38HCcP4NFS4ULiA9FD+ew6fg+OJxE++pn3j/9qTPsJIq++5t/nmOhoZCZQXE6qEUnzescI5sEyIUnI5HlIF16wJrqEnVcSKcwz/DXzX/uQP5JoJ/PRhAddPES6AE7g7OHKFEj6lUbtKWC4M51826RyhinvGkVfIc/uRUwJjXGULYf5Njv87i2ua76vmX1mQ5r6xnOegHXry7CN1zUKqKY134J4Y/63gPo5vPpurSqhhFXlFpMq4cgwpcqg7B0/pcLRcnhLlTHWr8iSuCESkbTjwnVK4PmirWHAtLODOo63Q/ARqRvnUjHLOp7bB+A9x34XxGo9F4vcdeS6p777/LGpfxr+gnO6UE29R8mqCFv2H+iCX6ysoYTzlB/GMzHt/o5xvvP23332R4HNPNleNDWofHwmV1LP5nUqCcv9KXhplWPwzGT2yIJLSyftb9RxAXWKcq4jX5KwgJ3hzeLTE6ngqCqNwUtC3XEl8GcwB3oLe/fao5ugbnxG5Qf+TyxiDrcdOx8SV/8BfGf9w/HD8nx1N/DAqxv2gmCT1kQqkxdI0+Vr5ZnmR/KT8jPxr+Q35KzlROVZJUxzlbOU8ZZRyp7JUeVhZp2xX3lY+Vg4ox6l9VV3NUi9SR6nF6iS1Qb1NvVddpb6k/kb9QN2vhrRe2hmaoQ3TLtHGaGXafG2p9pT2oval1l4/SZf1K/Qy/Rp9vv6c/pr+vn5IP97qa8mWa11qFVgV1pXWQmuJ9aj1ivW29UfrayvJ9uwhdq49xp5lX2/fZi+2N9ov2dvtD+0D9mG7s3Ocozmuc66T61Q4U5zrnFudnztPOc877zl/dFLcY90T3KFuvlvtXu8+6r7gvu3ud9M9w8v2xng3efd5a70tXvCFXv7GCSSKXcSe4oni6aIo+uIg8WIxXywRK8Rp4iyxQbxNXCY+LK4V14sviFvFt8X3xS/ERClFOlY6STpVkiRT+oX8rLxL/r2coJjK+UqBMkFZQIsdVHqoZ9Bis2inFeoa9X01omVrY7Vp2nXa09pr2gfaYe0sfaA+Ui/Ub9F7mXlmkXm1Oce8x1xmXuYtopbrvWe91723vOC3hrOp50X02zxpvWQrI5UZ6l3q79VuxijzE/N5e6f9sX2IVpGdM90Bbr17j+t7F3uPepu9dv5U/37/Q78scm1kQ2RfRNjXXNY70kdSN7mn7PAzCJnqCOo2RFuurdBWaqu1Ndo6rUm7Tl+odzBKjBTqtcmc63zi9vXu8G7y1/knRrIjNZHtETR13J49KA6Vrpa6yBXyNOUk9QV1vPagtkHfpecYB81e9hy70V5pt6PHws4gp9iZ6jQ499NXOe4893n3TfcD9yv3NM/yLqBvrvRe8g55LHb7SX6KH/K7+6l+bz/N5yEhLB3oKo4XJ4qd5HPkbHmQMkKZoSxT3lW+Vhz1UfUsfYC+T/9aTzFOMAYYVxg3GT+znrV2WT3tmXaV86FjuJPdJvcd16Hmwe8zjwZvSS/KvZVK5UtlqDpZXaA+o76jfqF+qC3U1+nnGjXGQuOnxgvGW0aC+Yb5lala260L7LtswbnTOcGNebXedK/Om+2d5s/1m/wzI8Mit0Q+jAhiglBL2apYL/5WXCk9Lp0uj5fbKScpYWWoUq7MUu5WVikfqaONHxvdzCGmY02ilh9Yn1q97P72UDtqV9mr7IP2iU6Nc7Nzu7PaedFp64bcQe4w9zq30X3OlbydXhu/k9/TP9u/xK/gyZXBO2Vi2cE08V5xojSPOf6udI1Sr6SqM9XF6tPqZbw=
*/