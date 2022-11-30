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
274qVa37REz78mEKT1oEZOdq4FpjC9Eb4QX/5ZfCJ+OLqDcuCaqkZTDtl34UkwM//DsTosKx1vbKBHJRKXLbLNSUZclNHMPbaVdOU6KnGVn2FQWFCtpBi+AOZeYyzno4l/Sy8RszE1nI3EvT4r9l9OuMZN69qEM0oNWUgVtjRiozvpHd27wUqRracHu+6USj9lfiigysDB6apFirmhwhfSsYa9G1KkZyd/VwhiaIY93U+a1CcvMsTyVvYTWv1S8Dc/goL5sDGzO1rZ4MnUssIfAnp2DK5GuUPvCwDjpoBdlparYBSo16rlt/I8sWVdQ3k3q1JMwaBhRgq5wiS7VMezic5bVwO8MKq8B2hMfV4uz6WNULdla2IlcXPRhkoq5F3rVyFwpyT1stI7Qu/MuU6l6jHfZbYCf8R9i9YL63lWZergCOi+2FTO+BQftmWx8roJWTamoyL5Yme8/EJKXTUoNqXDdtnbs76xWcln17Mg1JdCgJuHgYlBJIc/Pd14GAMeG+wnv1CG3hJEmBs2NtS7hBDo4TEQCzWWM3uRgMHClpt75AI0fJuyYV6i09oE9D/bkZWh7GyASdx5I19LcenWk7t/Z0o1BMFX4rOtWpBC15W/S3FxbTCgCb5Fa8GzfmpM/AziekLBSPFMt4mnOuW8XIKc7FcL2e2c2dOcR3Wm9ocDH75iTYjXUPm5lr4CphhB2akiQVylyuy56RHFttn5nc0hs8XdkeKP9rvFeOMsGRjJ7DW3dZslY3M3tHM8aMnWuN3RJDi07Tlk4Kdx2d1qr+acuiWd0iotCIp22JXh5KDVNvpa3bKI5pk5HcFv87sPTRQ6J1eq7+DhkIMlPuXcq2QgHQlXAmt4qy2qwnypuTvzIupTVtrajpFFXLqy+cm73Nk9VGljVSiv1crlBF+Z5bBchjnTTVFb4c7VA1cH0qABwmTueDKc7XDSllx5klvp/jdsdV6IAcOZ/Kku20muDeZzXq3L+ApbWxTe5W9U3SS/txTO18tE0f+deoxNpWLTG8bdKlctIjWxYJzys6wNtCyFtIFldOp7o03rZn8vzuyyStNVnMUVN9R2DpsC6/s1PklvpsHqOZG9/GoiVoQzkfPZvD7rhN7b6FnPaz21uUv82So7a7okK/xrsi2MtcUW8WFxdSr8ovXb0VSu4i+gwnrR16k8mr9Mr6ROux5ajMkQZovbnHrPLkisTVgxbqsgkszvxJ7gTa9i3gHc3EkhVIlcyjWxILPbFmN62kVCs92Z4LAIequRSdtKWAqq6JL9JTy766sohPjUuHkqTcImUetD5V7raFt1O7ZDXFOt7JGlKVrTHRJvtKxalrBxspKc4DYt2SwW22RFyUisWLjKh+CJVKS2cvyrrS0naP8gpvIbCSvrNEPH066csvnxcytvjglARD9D8MJiDlQ+Vhx4rK3DXHnjGk0xOmGUqaJ9u9Ey7uXZ+1iyjGXGWth+beexJa74a+Kq3e9oJupK9YrzveXdrWpASrKtE77ZfPQo8u+kqWEjPXoZaodGg/iBeK2n8XoYdiL48uWKVv5L23jnNWl7I1uwmn73U8kaUp4EibKB12Z/ZrhYeB0LUUVnZ4ui67v1Hnfyc7vp1JV0ez2ZNd88WduhOwKtukWzydPz9uVQm+VZ5/2GyVFGWom1k1VycO2ZqUWiGae0MEs9xofiOkt0oqGx9diTafT5H9hScdj5UA4YCMaMuaIR4vjpY6m5kuz50AvrZWfnok5kfaZrnxTWN75zK+9Wok7tf87a22/BbAat1xOBqR1B+m0o766HrR+0vdu2uweBvgle6kQzdm4HMKR4SaVbh9qCWWCdS7zAjlzhebdLBUsENVWjyuOw52vode9OmDu3me5T+QXc2HndDljkncxrqxEOq8lVaEobEhGMNuN1LgNck7mEm0n3A/E1khSMQnze9wXT++JqWuyJW6KpOBGilf6He5QjGSfZcnIXRCd8rJbGvYXU4xK2tHqCXphW3BPlIdxmS1d9ZyvJZycRpSIp3F1jJ72CrGV9IoaMqkkuZXV5fbiuobKMXueCWY8t1z0JQSrLnhJRQ152+FncsQ0jjertFbMrmeFViMCbIyF69W6RwCr2C7+z3G/KsLu1bELXRldySWdYg2v9G0f2wzOlNVxIsSVFyeSWquMi50E/eXniI8vmOXKVK9Qo1ee2w6i8SXsm7aCwRTGpaP89KFtYetaxc6zJQrJNXzg4+Jn9hrGk4JSGrh3ZqknaQdJ2btCxBZOweoRGsaO32TaL1GtyeKfByOAoo8PK81GWeKeWa4KlJemWvXQpRT0hbSo93Tld+N5HtWm35RbncLV0kArOYPdFU0pQK3nsJjP1VHnanviUJ3CdEUKjRG8GFHPbUZEj/CMWV7DEUiAd4lbBhNoHZ+G2WkiKCOWkys0HGOxLfyXps9YiUCEFQ+0bNKJ84ss4R1rUymPa3HI0Gnn4gj2DPxIb2NpWXbvLlv0tJ3q4Z664Sfjwbx+T4f8lp1GZ6QY7WLgnUY5qvyXkd1dONYm52GQWBWnpsVVLVaf7hON9SwlRHgXmcawyWedezMdqeeV6P+rFrrriop59yttHVatmJDxz09G2tbiave3OqeJAbahaio1EVYGCzZ28Km01nwAMCbkTOFQ2LbK2nxHbkuvlWTjKivTG/MJcS+fZPRpe8Cd5Ozt8mlte9xyBK3IP/uTmrK3BJCxGI8LtoD1tPYiqKazPIVo6e1twsONK13wi+kE6fi+72bXFJHF2771WKg9TZLQqo4s1Fv2VJvcojCPJU+omh6nfURlpNWIUBYzhTxudaPcKlp9RXGSCZa17HuxxeVe+uwW19SlMQYyyfMJxEYVCIyNvmUhzoyzn8sD754Ll/wm/pWsLsbLGevoCMbT5Ull4jobHavbnBct8WWU69hAB3pIvDcyZXBpX748fCdaC/tv9c38GxbIjx36gVgWATX/m0jjygzwTVh+dThAOBtfFmFw0h94uTcXg66eQnw+NvPIlY6paQ+ajLN+DRSDdJt5UjOsB95nTfZnnKpbQJlJIcOLZFDTGRppHm4fd4cKRvCqWzaytScE6KB0HbgrOldbmqwOlRMK23Kre6vuO5n+AamPGpqOZaxSM5triGY4SpmoG1oxcTn+jcGrbPE4bxrWkjgTgSt45AHazK8i5PqZnnaP61exW10vs6O8FXb1ZH0MO3envjtnZvKc94HGgkxS4jxOUaY1OTUC2zbMHdK5SSduy5N2hSZNvQL6bIN94xnrHfdlzD7RjLVSTUQyeQgN121QF7gmrAjvrA+8DCsICm17eBuVqcgOUEz03rvLHcWbLio1tOivG0+/FjvkCWHqZbmP1ONhJWzqZdOiDgW0SHM3tQWpJBe7liHNAI5z1Z+qc8UgbmprvnGHRqfre73DtxeOgEfcyROz7feGYomcbm9d+92jYVmPBTSwsPuZJTigtjeq4RgAPc8+2cPJ7liDPtXNHZPS9olugWVpds4xrGsrWN/KcVwBxoiImcqwgim8lonef+EV3owmluW24L7XqGacmvqnOpsUSYe8e2DjVZjtj1tZi0azrHf3UxdzDOi1aW6uOV0D1Wt7D70llKPJCqpcRTZqpp0juBAJXWaup0ZL15v/czlO5UBWxnfOMrCmviexfI1MkuMDh0uE8Ne6GgA4oScayZY50f2qruET5KhsuFvVzvCKDNXrRiEZcZPbba1ZVANfv2UW+483WCg7UdxacS1rh6ajqH17u8lu2m2tsFskGmZ1Ty3bAXHDIiY7ZjyRtaAQJ7n/C06Zrwy7/qe/EjYOIASEm71mBVdo6uImS697QLq8nRpzRREM7+LrYQextIGeGRH8NjUVOl66yi0mLardnSbeSwp44y5fVXVvbJ95AKlvxYIoyPxQU2jj625RPdmDz/LHaFNHkpNFUmh3WulzFdRna+qna+xeHu54E+R+vaw9g5yOd/R+o7x+k4A1p8KHSKaG2SnAzBM+3OhvdvkBeCk8udRfU9i4c/bDL5N/FEAUCMCZYbrm8X6RBZt4RXtkT2gIbCoo64rM4eRPP9C/eIGMmd6Z/nGypD707XF6vk9cYAczw+hvQ/S3WXWEbzPF534VFNN/yKW9uLpKcXWtUdaGT6xRO4VB274wh+3fZP405UE/376c/TKTFClijgvHFjAofj+9YRfbICp+gnrxDZQyAZsnpltNR09EbIOA1Lew76gCd2cyPuolfdujsBS1guQ9Svv1Hr2fW7+xb/NTL2bGJbXmDkXMM7Lw7QsDvTxAhE/JUsrzqSP9PHE/crzh5EXiCm/83WIimznk2LqZZZHsZ7O4nyKoqEs/jnGUWIYgvEc+nGJ9kgrMDgtTyNVnoK6PEEdd4O5+g45P/q8AAODKogZOGeQm6p8XyGeqgCppAjOTeRfHc+7KfukyBugLK+j+PZgXlbHSlr52hRs2gY0cPFv8Czv8HQu3V8Bt3Yj0r+BqLAP3XUDFHqOLmsB+dT517Cm+2ktl+atYAj6iMoXMCyfI7IOgrgOIntmVq5yX7b439QHw6l9lERO9oje7Orrss7faaZntKVn4kzP4JKe8ZieIeDcIz45RUNyitBl/zXy83mDNeoBbdXNY7ClV2jps/PR+yKQ88Ewo8mMzFPFzdMglQcic5qC8TCFZXhlUOpfUQNeqMwL1NEHWFVgXefB7veifl7QnDqQrYywboJDYed38eqroRsw5RSXps87PW+SSV+gTV+oSV+ymL5gXU65XYq9wRb+hS4EFKXvOBCOgZC6Q/2wB8VmC8n1CqvRFtKlyVGdz6ilX7PoT3J2OiP5dMbcvN42B0nsDVX3ia3hFtpBb2IbncoFcJzx58j159CVSeH7r1xgku/fOEMjX4LDwQJFhC5sFe0Z7h2u68YunCSdP1noL1G/pnOzHgPJW0K6FwTO+oXYdIAdy4/BmBua2RqNdQztbo+cboOnoutTcuv74QKqSNPjmfI3QV/zza0Xp62XqPVjYPlQPRiVwRlWwRnVxRrSRfrxAf2K6ycW15uY9ZoFeD7xE4FOp/yrtwPVekN5vcV8LeW8l3jygk46RTVvB+beBtbs+OPt3/boP8YAxJHz1zFdr0Ldy6MP0/VP0WsoqWso6zNQeiv56WcSwM+05wRSRhqK5gSKlQXYK673M6kPOFn0mK4GKlWl0Bk9riytq09YqU9aaUhhCfDb7N90SzfRwS/glX8DULoBdLIBueYB/MwF9KPzj80NGEjjP6Ca7oSNf0fdGfZDBcCFN3gUmS3kl31oIpruB7n3uKT2SQWMncw5YUCEXn+RNDPBf6Wk/2I5PYK19wIe7wmJdY6CrXda5bkyMNwFnoB380ymz5tLL5aaXkQpvQB7co6KuByThjWsDGVQK0qvdpheNZJeIz61wswyRlWn8fONiGkMt9AC+60zBG4Hc+3iqDN6ZWXw2TprS+/PeaJtDeR9DRz4uP8GfHIP/tEPhDUI7W3vt/bl9Rvw9gXd1QJ+kCh71nmnA+L3JdDvGxdBduKK/TlAxxL+xyWMqRV8+d/ZqEatq02tU1Tm9m4OhjpEYewJhN3oPAegg6+z4tI/iKV/IDnvbIxkoz9ibI39E3cERa4HzES2G6nrnfKDYHtjIN0nQahxgtIF3tgF2GKlh9XqJ2/jb8fR38adn+Sxv0UQf0Pcekf/en9egllyBPx+hDnuGnbtHVxtBgTbNfx9DwgK4h800D8gr5fBdn9H91J+dLp0wnxigbbOBt+kAMBLo6+h7OdR4+dl2T/mbK0+PUO9f6Sxlwf/Ur1zwsP6BeD6BT59hGiyCfyxCrXxe/iARL8AVf9EMfeMyfgBE77hejCigwZSC5MjXJ8z7JcTIxvrl59IQrZ3PSWGZk4Zc6bLRg7omOLfUdGvssK/w8rhWhrEdYuSqXVaBAU7B46C9x/Fo//Py0i/jmJ+7dsYEOQVxrue2wNUUA+4qA8w7iPx1xgfQzo00WA/lHxeg9sDZDtXnDRgaXECpl6TNgM8ko44it/mxBh0/AYKoihUQwc81ApopCXg6Nb/uLPf8eeY536b/sPfxwEEm3FglV1qNuA21/9ON1FKv1vFMYbnkaYDVPTBDxLgIaReQbQeZdj/J7Yeg7gXAkocz74fEPx7yqGf4UwXlskmVMMl+GNpWBrSEHO5w6bG38npfKjybDZd/ALrT1KXLLCW3cyNy7TxDs+lbKUMwVMa6UfQBfBpJYvu9+x5hs8V4WejOhKut+Aljb3Xn/PyE8VLCBGFTZhlYlZ+dO8vYXLOzJIvBC82nkA2iYh26Wip2PYu99L9IOpktfekhWc0regYVYEQbX2/pXnuu5Fi7zAJR6u7UsGykNG5StU9wPwBjGG/luesteegF+dgNKcUvFMazTkJ+5FH4xjD45gl45i+ZZqCskhymYmt3PxWaYn7xMRwZEs4fC2C+A5J5PRtrcPvTR0JyfJDt+IE+hEub5+kl19tHjbFW+fzdez5hm6mx/CXqkka2JvpMT37iaQOlWWXhrNbO9qdxOtAZ1fu7gpRL3d8icJZRvY+1q1R7HHuMHz33hbx4IRQBq5TWrdeQlceucioV5RSrZFmSV74KmGwu8MYVTLGrRFO7xuDYeU6BE6Mzyk/9vwF7bVDME4zSkMeuFRgpmPMrn1CrH2qrGMmzSPK5hHTS67WXrTWXqaVXrqXXmS0Xni2XmC1Xm7XXvLUXuSWXviVXuK3Xty3U2BPNG+zgmJFiYoxjMAxTKIxTOQxzIUxnKd30bt8489kphfbclWniYPzq+6cufNk5iYgbZds17Ot+3WUfkXpGSPlnJlz+bqv2XTtb4IFq5CXRSLEMgGqglOlkufziNR5PEJycgwkhX3e5lO+ye8n8+XnVcDyNaKymsZFg4GyqXHZVKVi1lIpj+XYxHNg6xmrbiks8we+emO+r8j0RPNDXGSWiYXDMSzy/l/KKU3ltJVy0me21yWFaVgmz3J1xcZ6Xs0GZUqkDaV/6PMVTboHpW8Pggp/onBGmeRD5sai2/+YXedVbAzbcYLzTLsFLikHJ1dAWiiiOMrpjEdPxrO0EBhUCikqP6fBsXiVb/BpNNktK4te+M/KOykWXBaL7Ez4V9g6nXZKwHVeNvBaUh2FRfIoX+v1Ten6Jv9c7Y3M4FK+0oVBT/7JsHidN/4hsnj9KFi9+sP8Wlm1PmT5uv3saTSBM3+pVW9wqiS8eQ/YCb4cZdKVgFY4IrsUlWNWOdezVOhiL5b85Go+/NWE2sG/v85ZwV86j72cx2XNE7xJxmnH03aA+DiCcp7YnqdcLdKwlerJ6gJuPuLkozOBNnqPFHpqctlkt35gnsTTJoP6kNtJj8U84kTBPElReU8VjqxRgz1Hz2WoNRxkoSJ6ni16y5VI95UQqzlnPLGZLu4lavgd5kctCKWVRNVOwkSxKlGHTjfEIxM83H1+2PYj8nR79JYS0oE3p7/x6B++ZX9YYPWqoHDELYnlFlE9Reo+ap1CSQRuRuemsOhQGXyqEoc8Ju5Ob4oEbQj6dJ6VOs9dfEfmVmrw8VCLOTccXxh1lCadxEqAxEVIGM6qVbFB7pXhJ1ETxzCOoQHEhAkuUuOmi3wMI5s9tAZf2Eos7Cl+apdYNc200Yc6L0rc
*/