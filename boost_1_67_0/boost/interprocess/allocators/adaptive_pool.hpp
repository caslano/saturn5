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
xBsndYdNh9akrCb2iQPbCiyzOGUesP8TmtLKdSx6jaeUBCjVsQoXa1vk6wk2gtaOQ3bts1LxtVE3sdnEFnmnjk9+jErqC/LfUgNux1E9iaAueJCRUGbrgw2+H0Dvswd5bwrQDwAWPospgk2KqdeeJczUupeVaD08VGwqNvZ86PeYizrk9L+OItVgO32Kn/Pqu5lKxPvxmAgWYROYcwzgUg/9e3YAPH21GAbaqdC8xG+CR99or5p4Deh96Fu8n58zInen4vyO6fXwb9pQXwdmsG0b5/ECn3eMpTGIyIjCDMdD7gWJaE/ZuQuOyy1b+dqCtzBwpy9jVQsoK8kNvHOnlu/pB5RVYJYevN78bj2mn6Z96bvHcxLdqwhwiR/oEeJmzYAa0T7ZmkMFlbi0OaoYi1E76I/APKVf/XCz+4k8heHl3fxo7jmU0dd8ekcHlcXS0ZW8HDpHQDBamJLl45d7GXCjwQd8wFte3ksC3Czxk75PJKFM0wcKy2MSuRJptqIrQzIjxWFUKiH5bYl4w0THCLRoiw1s18BxYHRVTESAtfVftcYfQ8OxXD1f6lIVPIzwHiOUY/o+2GfXCsgZu+3vt5uadFMuVfZKxY787u29f5B0KsfQ7dWVhJ6Qmz2N3zUqFQVLFCwUlS3aWed8Gdp28iSazo6X0/myrAZkzyEWKbYmyVt61uxlSQnzkP40LNnwV5uyzc5JqL0aw91VNewzfaJSz2A8ZQUTFqU5mxr6tRWI1JAoIkTtebGRYX1ArBQ2EGLmZTvo5I6PcbZlKsiXLOS/AcrCU++TVfyxOKdTAM7OvPiO/8ZbIrhBf4If+HVO2n0CsEFBQOodiYDGD/N0Af3KxCND2vqTWBPqxkKwZc7A91VyyLHaRX69Z0XS6SmV61wRx+PeXkqjCRQHOGNLgWya8T9r+K1/k4PSAw1cH/2OzF9N/oU75YKh6wd5Ols3DFSZsQBQTWN18sk1BlNwnBLoreMUcWfvSZojA+uMoGx+PFM0L6L0wrbQR2u0wKAtqcMY4R58GUwiNHqS94ZqoUThXawVmriHi3cg/IdzHGe95PFN9wumO7Ykgq5/rYjcptg3aXIOWk0v0nTHCBuP56zfO59RZgxCMr2r6u82u3GDQG4buTDdtPtWHTf2WE4/loAkhDk/ODNkkS/ubXhYQJB/nyGPNEPi+nhPzPGNAi0NlDPcgs8SMPgfke/VpsQxfAvmxkGFqAnGXOw/d5rMySVQoknpym1ZNdFldSR184r5Mwj3J6vyTt+17bJ3iSqFZ8DtVqMeb7DYhRbAmVtJXZhzjr9wIHmMArgAzJ4SD0m3YFuL25py3qzial6npoHcIW/AK/GWOA91GCCaojWTLH8dey0N9YRWMw7xLNvzUil/XU05umdhUd7DYQm9jAt+ybqKrb5UmEYJrMA8QENrHjCILQ15KTOHY+pPDKQjehcQ9ZuOY322WJZJEwduvJqEycFDf9JynWGvaupYz/CyN4shbSEC+65JBGab1SosFakD5RQurTW5cOdXu9Xuig0oMqF19HqnxsAvr6XqV8hSnqA0VHhEclEvZwBVcAK0dNW/1LNoPtC4O3Kbde+YE+4OAp8DKu0s6iBASfP3GvTLkGSIouVtCIjtyy+aomNF5NO0IGuemrF6fSE8m5xeQbU8jzQN0tYX0AevQjczYAn1kex6W9EvvIv1hiqcD9Y3DkqFWdUsO3jfa8epYjVKlb2T/DJdrLvAYdsEpvmNjrjCaRLfHytyWnDmzhF7Rw7+zLrw/3xM+zf4UjqIqLo5UTcRNDLHpR795aiOIiI3yswLjwDkUiKrtnyhcvmkcqkJhVNd0j/w/xMMFDPY6QpPIO5XDOedqHbWe86Y0fHvfw1UZ7yao+nq9T4+0nNLu9P4QZraXdQ3X0V4xOETXvXlNCt6hLZANrIFwGEaIK0FESZqTZfKy4uUigWOhSsUZ90403BpGpmtFkG1DqrHFhs9/WjFVAVqdv0Ad1ur89uwAWlD3mz9ddYwxXdp9A7BMmp3i6nKEpIF0ejbnaKNbIxBrSaooQsHdHhIuOxFNRgaCnhQctd45zRtcHR36eBFePxwz13wH98XSJdqofeuwf86f/eHk4gQ/ym35boiL1R8n2yukGrfDYBWY0RXLEBVQxvZs0Kk/RdsvWGrWPpZ4nvsupsio/g8FoCCdVV0mO9FSh2me+8uwA9V/HY/TarCfz/vwGfJdM6DFP2PNSj+bvUzEQJfJKG3z7E//N1okXBazzvZelgfDLpPuXDo9EBJ0tZARvcOyHfp1WezopALpr/CAnrjQNJGClrmZZAIlxyLY14x4+okz8rH82iq4b6Em2X3DSjS0m5wRjWb6XvY/L14MiSiV+7BrN4jIYJUxXDmS0c6jyB24YysEVGjcHqGLtiuuzpt71sw2tEea2Tc74eAJgzoreia5CZiD5OeWj88bXj+Lwjz/vFKPKlXPCow6YH4u2gSIucetwUIiCB6JtTDzLOFGWXONpm3lb43y7gbAZ+1eykzsnjzZwyu2iCJ683glZE7vGFEd9RvV70/FAo1o6pYt6tRzYWNsDD7Q+QBegeYmPYfwQLkPAf25iwfZYd9FaHQl+ED/ysQmSKR5iMGQ4DppKJOBSDo7UH8HwAagOV/zC2iRZxhy8p8fA7gZNMKq0xBZMlpIB1BI+9xfgJmfhPe0xBx9Zb5fHiLRDlmNKSiABrFx54hqgz+unLhAUFlRoFvXAFu/vvXQHvBAq3ij72JpMeDwaDUrqbxwHqU+PXVolzhfuyWz66H9y7gkCzu1YQvH2pLRXEzai8ajHGuIh13OrS6SmLFq9guEmWOmHIxX9sPyM0zB1K1lVUeLVsGueCGv+aXKXxPdnIm2cNWKGFdthMzoLNr2ag6DRTxkkJnSnAo85pBM46w7CrNioIkcmbAk7lnryEHVmvGEooUwSym2E5g93h2DqBNemm4dSFeVjBgXJvDp4LDhagZH9mBsgZ6GsvbYnEuHopsTld0NAv5iLKIWKduw/UgjQJT636LPvTpMULGt9lOFFZYg5n8SQKBG1b8EXysmhqw4vVXFZ0YZteA6H6p3iLx7+CJt22ED/+D/Zq9D3glLeKqw+2iTXha395IARe3sCpYOn13RHNnsd6oEcQZtGgjHqHo3gWvYfiPU2zVh9FxDGYOXS9LtgOgge2NuPdwULnRF3E189celDF/EB4pYJ4Or1hcXkt/VQdlHfLJ8FpY0YkT0glCD0jIekOli7RQ6Tyrl/9tu0gMaSTmxPXt8deWm6xgvIE5lN2N80dnX2Ghv97QRwoITCXXcZicVH7nx+hTtoVKFtEXdb3zTSDfkYasj7laANMcGF4WM0Tm1pVr7hyxUUdk4deHSLNlCKGEdyZAVQvoHmtwCFiOMbDOYNUA4iMI8e6X0BKEh7aXMFBt77M8Vs87ckH/m/Fum5dxDifn6nPI1glebWfOVaqD83fwMGWVGaa2sgrYd694BfZdUeXT2dcXZ19eWMEVMCK44F4AUljRHpRDzVpHhRA+x76n0DOveiCmXVIBHHFcrWhFTH+mZbeAYCt0dCpewlVXHDejc9MppF6T4zjFUcoxqQvatoLVeIXI4r5FnIQZDcb3K3uETYQnYXgjvDQ5MEmUDsJ7ef8zmGncyaeujWk+N12exyeBSrFpIFGuRxIqYwMmUBT8690x7TmSYMZA6kJUVC/fjzIKNIMy3P8b3C7Df3jl0h5hXUTHMddRmtxf/2Pw5L53m5hcVtGKW2UtJK0P8nHQsLD6uJKJR1L0QRZWdypZYgfD7swLDqEvXsA7X2hfdRH0d+S0BlhU4crmYmUz5yKeM3rApAFn8yR5MJd/jsZiFpr0sILEXgtAuAmIUFkRN/9QVqmumO0Eb+9FBYizG5S9+ux6xeySUEfuIrmEGxYwT2YP7+lDLd6lSxhQxrclIulCBYkW6FkdxrkE986naUneABbGd3CmJdueGHtHIaourOppBAmARu9qRQqmWXY1qsUKvy6OrOcsVBEx1oKnZjBP0jMIuYQ9RLhgn2XUJ8i0F+wg0+pexs8mw3H403Hdd3omaxnZra/ifQgGoObarUhGOTI3Vu5fOg03iYYzR0yXrGVlFFPY2YrBN1cv/wgoFNkIakPj/HM0QXtZF+//CvMSKxO7A2c32jbQaOy/4o2a/y+NluFcBK2iHXqD9kTTSLyp+fxNJ2Pi0rp6uiiEWm9ajwt2UMkmca/GKajf809uj0OUzw/xs1NnQ9xCUfVebvgKz5gntwQLVtsRb/g8NCS6fYnVkjAeVKtWr/WyXusHsKg4B4vNOhb3f3k2FoNbXkYt78BUK8zbgsmWy91aWQ5bN6ef3DW1JGcw5K065EvOgTwI87e+E5h/3ykwtw7uv0Wv9kestnE3csBfP4tP4/7O83NAvNF/DDT6ItHo4f9Lo8Lv9ChHKv/oQ52DduscdDoBZVbn+TkoDuXbbiFp1ommcRh0Kgi/z+zUqfID432J2ltF+3jjF/TGh6N64x/ofMUPdL5Db78x+t93fu35On9Zb1w20DkIjXsS9yOe/hXdj/jM8rjJjWEqimx4fML4vvi3Ikz1CoqLYnna08A5lton4W3aH+gR4w/T0KNR5k7bin+mTduGf66c9gz+uWDas/gHzYsqoevxfsroL8QzcnK0QjzTCeMybaXQEps24Lk+Y7RIJFrZTnjIeE34Xx/geX6Px7/YqL9HR4l2uMSj+8UzsjPYfIPjWCdDNVlSMMu/AaQeX4U3cuiZJ84sVpqFvrQssvay/G5LtpXbyKzAQ79teHMfD30DhN5BaV7Z21+iUyH2JrKfpqjVMf0KxE3obDuzbAfsTZbHGuxHgDGnf4ATJGtHwaZocsQweZ5nkivezrNyaecE7+VrtzxaT9Z5BpgTZK6ByQoN22DisnfgPv4pJR10WCs8Duz91+TikLbgkJ67LmlIuaw0d9CQluGQFo0ePKQdJ//HQ8pNHtJ/vP/DQ5o++n8xJFRqo0+iBV7FSkz8njNJ97nhd1pX4rvxmvguYKr7HK3A2PBEtMZ8wwirthNzlOOHxK+3ZkqhPaQD5wdvYutQCWo7t5AqBMmYZzsAvP7bBtZAlsdD76H83B7/Vhb1xTPY0nht68Ydkrgg68mdfXooqCkNFS/f8yUQo3hEctrl/KS0y3veGvD7/XjZV11uGmD/LGLvsKphOgLgyMFdmTw1fJTect1qpAWeYDGww+or+3A70foVWKMVMTFYnvkNOhKEFD/45z7tTbz0zBcJt0JVj/oUHqWmpBv1qZl4mLRkDG1Kie/d6hv4R8ueCtMQeqMNntPuzWSOfHXdE3RYTH0K/6pPbYbPwicRkWBGUxj/zkMyvoJPfOYwzLxY92j8HNXI48Ai9JXHzVtwKT1GQ6iPbMRbtZaohsgezIJeoqYjn67DE9OAEjqlqanLoDunwgia+tRUQFm1ijc216xW5YrnpqI8ujBTVHNPjdfIUkvyxXOgaL5aMl48r30rT5KlIe5Jta4scA9F2aJJmrZa49u/IqePbSRI0+U4/Jmtn5ithU/inCi5ARgPPtEGvI//fhhuwN/wZ4yRZhU+iTOlzNRewb/6RPz8L5hqJJ5H/a0PvHXbgSWqHKpPCaxy83vGYhoG0OrfOt5UUS0x63xqCSNJAingYHfW0ZHi9XjeMBLGHFC3f9+NI6yRPTixAUNTeh0IgKZ1NLfw5Cl8Ctsq6f71zixrNNX/BPwBtwTA2BtXlTMCAWbBY83wt9y/SpiB4fr7Uvmjx4AS8e8fxwVSDq5GWW64vuozUa6KxRBupuftSRzC9vPbLZT7FMipuwO52j9MXI/UGnpdH1NmKtRjOF7bqcJ7JioXsxCtxXsmMsChfCZImf2WJxvsh4GFZMQlhHULl01VrtOWTUVX+ZYXsZQagQck4363VjYv0U5pRscVFiTmtkkvDUAwW2rfRW5ZZrZpSwpvsNT+3YDXRt9qzpQiijPFy9360/xijLrPD34GUhLvN3kSlck5hz1+tb8PD97TRsDl78S7CS1up6vPoRfLui9x4u/5qk8kxE96vk/zxuVReyYQpgWgptwamWFIAnsZgI3f1PGsF9vl/pkuB2LTuyNzpJTysshMKcWNbmCxhCKjnbk6IwsqUzyquYlHEGyXAOtMBnvo78imOQTXUjsLXQuEXf/CD8COahkS0BGvdAVSqjOPmDBVf59Vc2BQIKIsT+Fb/0p+Ikr5B0bRuc1WMS0M94vagGmsulS1nWINMDu1BcAxhcG2FRdqk3r4LwAjTekx8UXw4ISFEGy79wsfL/97nJTzbQemF5bkrDAyMFYFYGsZsEhWkqy21H6ABm1I56dlucEhhcsmWGptGGno6ewTp0pe2x6HqV80BBXFyXRtWS7eynX6Txh9acPKlG04f0cf3nMUqokZaoZpK7oRyLg/Uxm4aTvATQtoWHZnFHfdu2Ft3MTmttlv6l59/ZLQ1JsWBA1FjBHGhRHTTe4yzTd1ENKXkhXeJo7ApvBbobvoUJEHNuwv1I0+JK2waoIysrCmOzhSWzYBuxz2J/oeipQZiLL/OMgBn/dV6bZRoL3b+M/ATbM3rbo8vkLaSGtNJOUNy+OIpXYbJsw4RLkszgp08Q+gW5gmahSZ21WOqZ9YYTyKneWxOI1fxZz3cMkkJXWIqyuavnZxlwZDeVXKO7v0YyyVpJTBpZrW/yretTW49GtR13p23a9PFU2SlbSQq0uOmkKLu3qglvWsttD4Vbyhe3DpaoJoOLvuGSg1nF0X8wqKJqVQPynUD+Aon12rByEWnV36JradY1CGrHV1SZJJ0vvp0wpfQl1JMPMI5sfsd2I+upjRo7nzkay5feghZ8QNhVCnOdmL6+YVeMrUYUUXjqyS05gDQ76cX1qTugZmJws4j1PecYxPfk6YZNnyqxixiA327zbQnT5ZleEDyi68FPcSQ9RqO3aTfa+SDrLCvjeYog5nrhjKzEN/7qPuR308yMcD9ChXhHSVDxaO2C4UKpOV5bGbc4sKjhqPldtOREzTQee3Z5GNoWUXYdrBHqp2WHX0Yhj1wS8wg9zEr7obdxlIPs8zsTEYQ1Iu0ZaZEiG0LF2Pw0o16bJTe5dfiacmhZZUHd1QiZDomT5JgplTUtVlOdE0Lz/8n7F4reB4sGPvPA1sLNAV9t89JtI5ZlqbjzVE7jNEx4T2oOaUhPWopPMlmFedyu/HaEovc3SHFuVIFOjWLYiAAdF9Vwv2JvY7htALpopApx//C68yVkysKWoMpMzD3dHGgLXuIdSOP02nO7lP2U441Yr2wl2IqiX8BlJjYZ6ldiUKsZ9wXX1890eY/TdJqKRHXF1lPjzygmcfqpYyRxfyRTvwBfAoOvr2/cFRyaVSHpbiBWBQGpnbKThIreikRY5sNBakPnbz4jOYVY5Pv8brEDCAhwxFwMgUDvLQ/i4v3w/ajFXL80P1MEo1nT+Ocqmpgw7ePUizUUSzYandER/Ps2QTfdEntoLHwXhAddMNvl4s6AYpra3MY2PQQwW/QnvXzcuXYsSz3eu/I/luDKgNtko6v/RZkJvpAY1/jNlPji48QaFMJmDPCmA6mMw4mMXngpnITzyDSrArbjMcwpHREIDJmUvmJ7ZRBhVfnibO8Wr8buwv2NXxDZ54GV93DCezOlW4VsWFe8Q89hvjjIbT0IoBGDdm91s2DBPx5MpO5Cl7n/JjnNFOnNFOzV0FFtpFzJnHLB7UxFqw1aeVrQJFrNMf/CW3zBytkbk8PotczCKC/hMJGY6aIp/Q7gxV4WZCDPTYMtJjFc9QsVvosdBBNAQ6+ZOUJdbJqrpBz4MOuw90WLHgcE8ZK8m7uQyIwV8wwhjBXBDlEfN9UDpeW5bP/xO/oCWurczl6fg2O9d2LLQvf4k6Z3oKxXqJjcQFmyABloC4sp2AcXRcmBI34ZFlUvBeBnNKnHSRuUfL/QvAPlUrjuIoh+Mgv0T6OY5G5h4vVyuO0+CXYvkhKj+O5G5Bcudj4YtU2BKZe6g8MretHIh8iFrgoc8wBgop34/shEe29OnSiFRgdYyBp+Fo06nclVgr14EYF+TTLfeiPLzYsqvE7eNqCqb6d3FjCiUpwWNkVXFKfBG1IeDB8GC6V2Mt6P8nuMQrOkP3k9mxnKbrxa1U5kk2O7rwbOisbja3C2bqpzBT03Wsc4dABfPIMnakoCQXsHrndEEDItVtyJSMFV0e/kvDuVjhLLTF/VwaTkkeK8qNzCw5Y+9dPhpohwQV1AsYdMrVTkSL79zq6bZ6cOii+clf2Y4BE5TEkouw4Awyg77m5j2L7NeiY+E4Hn84Kh70Gzb2fa9pugXHL/qMJu0Q/8dTKKboNk8te8vL6OEoQ+ibz57u0/g3n1K9o/yVRD3QLi+IeiOWhKZcHTSDQ0ZV/vY0YtG+hBV163qi+tCSguLuJer0KVRe0g0oLSmAP48/Sj7sT6+PlHTx/4IlhXeRPvJM4sbYB+GR3wQ80Lj2vkkgJW68N0O7JyuQyt+9pj8ecRNJdafDpyzrQ9gZZhLVrApo9pXyqsyIaaybbyhLk6IutlKmtxp4wzSgYlPBSfZ+w6cp7GS5Otfa8K+USNbEci1oNR6MmNaDtMNt88aGthQ3VDXux2TQeUPp1z5C+3LZfvgCnGg228RGqFngjJpmBb/WA2X88X19eBUGB5uS3WzCi0rLeP2rifRZjGX8MymWse3VpLOuuXWnUA5ul3SXjy2fagMJ36ZWc3tPcHwglxdjddUBJTF7k5JJl43cOaZfw61ZCqF0wZd0WhjTShaNpbwMGQ87ODqjdwayeBoCgKYXqlUmtcqqVpnVKrlJInR7QdZHjWp1u7a8iH7t44ha3ak6YrzYnSYRwCkAUJ0SHQtTlHQFa2hxp1T36grc4wKcwV52yOryqbghD/ypyrxaElLfXHcZpuw8jo7RSebMsZ3oOTrDptU2KoHCminBIhjfnXX6vS8cR3gEzxIX8XW5AwP0aCtmwvfOKbwBfy6hdIqP/3EMIqVWTsJDaOKSt8O8uV9csFE6hYfwlzFKJ6lyx4uoR6Gn24EQ/bsSPVVgT+n8+8skSreBLqkn0Y2zEFo7pxRWyatT+at7aXNcnYI/kQFKu3KSWt3FZ9KVE10epLsP5oovhM4BGWUmIHIjJSVO8VAm0CQ=
*/