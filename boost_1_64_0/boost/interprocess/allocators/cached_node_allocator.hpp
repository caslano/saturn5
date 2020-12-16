//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP
#define BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP

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
#include <boost/interprocess/allocators/detail/node_pool.hpp>
#include <boost/interprocess/allocators/detail/allocator_common.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/interprocess/containers/version_type.hpp>
#include <boost/interprocess/allocators/detail/node_tools.hpp>
#include <cstddef>

//!\file
//!Describes cached_cached_node_allocator pooled shared memory STL compatible allocator

namespace boost {
namespace interprocess {


#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace ipcdetail {

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock = 64
         >
class cached_node_allocator_v1
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 1>
{
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 1> base_t;

   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator_v1
         <T2, SegmentManager, NodesPerBlock>  other;
   };

   typedef typename base_t::size_type size_type;

   cached_node_allocator_v1(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_node_allocator_v1
      (const cached_node_allocator_v1
         <T2, SegmentManager, NodesPerBlock> &other)
      : base_t(other)
   {}
};

}  //namespace ipcdetail{

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

template < class T
         , class SegmentManager
         , std::size_t NodesPerBlock
         >
class cached_node_allocator
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   :  public ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 2>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{

   #ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public:
   typedef ipcdetail::cached_allocator_impl
         < T
         , ipcdetail::shared_node_pool
            < SegmentManager
            , sizeof_value<T>::value
            , NodesPerBlock
            >
         , 2> base_t;

   public:
   typedef boost::interprocess::version_type<cached_node_allocator, 2>   version;
   typedef typename base_t::size_type size_type;

   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator<T2, SegmentManager, NodesPerBlock>  other;
   };

   cached_node_allocator(SegmentManager *segment_mngr,
                         size_type max_cached_nodes = base_t::DEFAULT_MAX_CACHED_NODES)
      : base_t(segment_mngr, max_cached_nodes)
   {}

   template<class T2>
   cached_node_allocator
      (const cached_node_allocator<T2, SegmentManager, NodesPerBlock> &other)
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
   typedef typename SegmentManager::size_type            size_type;
   typedef typename SegmentManager::difference_type      difference_type;

   //!Obtains cached_node_allocator from
   //!cached_node_allocator
   template<class T2>
   struct rebind
   {
      typedef cached_node_allocator<T2, SegmentManager> other;
   };

   private:
   //!Not assignable from
   //!related cached_node_allocator
   template<class T2, class SegmentManager2, std::size_t N2>
   cached_node_allocator& operator=
      (const cached_node_allocator<T2, SegmentManager2, N2>&);

   //!Not assignable from
   //!other cached_node_allocator
   cached_node_allocator& operator=(const cached_node_allocator&);

   public:
   //!Constructor from a segment manager. If not present, constructs a node
   //!pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   cached_node_allocator(segment_manager *segment_mngr);

   //!Copy constructor from other cached_node_allocator. Increments the reference
   //!count of the associated node pool. Never throws
   cached_node_allocator(const cached_node_allocator &other);

   //!Copy constructor from related cached_node_allocator. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2>
   cached_node_allocator
      (const cached_node_allocator<T2, SegmentManager, NodesPerBlock> &other);

   //!Destructor, removes node_pool_t from memory
   //!if its reference count reaches to zero. Never throws
   ~cached_node_allocator();

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

   //!Default construct an object.
   //!Throws if T's default constructor throws
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
   void deallocate_individual(multiallocation_chain it);
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
//!of cached_node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator==(const cached_node_allocator<T, S, NPC> &alloc1,
                const cached_node_allocator<T, S, NPC> &alloc2);

//!Inequality test for same type
//!of cached_node_allocator
template<class T, class S, std::size_t NPC> inline
bool operator!=(const cached_node_allocator<T, S, NPC> &alloc1,
                const cached_node_allocator<T, S, NPC> &alloc2);

#endif

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_CACHED_NODE_ALLOCATOR_HPP


/* cached_node_allocator.hpp
U4SBwy7JyW15nTsTmhu7MFpdPZI6VUweHiuIlVaUC09zJt7kF44ZFy2MDWVEVU2InxopjGlzPtcXjI2eXVE7Urh4+KBhR1rnLoGnTYq/4JhoVW5Fbgl9wMLn4iP5zRm5FfHz/PZOu+GTS2OFJUcyOidkMZRi0ebUE0LQhUdS9yScE69Cy7Ppr7faUMfhUxi+E3JLJ0SFmnZHE0GJZdHgE30WXJddUB0bVFVVwVP7tBv+F+lfxcuJFQ1htJZx/eAgHb99SmVUONRuZFVpUAlOVQZnzq8oqimLNl9MLZaSF2/DAUxE6sbqY9vza8pipWdPiVGNkQyjgSUFVXzvLz5KWh6yNCHow+zSMVUFVVOE1W2zKwqKWlL8MMJjrdM8o+Kbzx1US25lQjCO4qUK0+Kfzymtqo7XnLPXxXMuoOubM/a0a6kK/fLn+gm7/rINB1T/udn8xItqolVTcqJV8a4vL2Qk1TCUqoRjg3sG1lRVoRxaBs/QIuHrIDe3tHB8cFnwJcW2g8sqxhSUnR+dUFE1JRhXNbSNzFVMjkmlVRXlE7h/REFVacGYoH79EwYFpQ+ksRm3ZcMZdcFAFFa2zY4WTIp+Kz+37dBysgrKSqd+8+SA8qLhlaXlzRVJaR5T3yqg59G3aBmWvIQwt11uWfWAsrIKlu1vDD4PjlLHspqocFOQGn4kVR+kgi4U/hjMFIZ3dUVZlC5i/IxMHEZpLVn0ZkHrND2zJ3H4N+64JGFQbemRthTuaHdxeUm8m4sG1RZGK4Pq0i1B0wuXBWP3b57u9u2eEaa0y41WTSgtZyIdyRKmtR1a3ZKoqDonStdUcTJazW1CjHNZ0TE1Y8dGq47kbQrKpQurYjWVgSoYKYxq1frDszEhQ4KJft6gYRcMym7RBmijCdEJhZVo6CHBp+ooo+JcARVcWMKbnBd8in8cHJydUDEpyk+lTC6sJpudiOBs/FNWcDa4DN2ZF42/cF7z61epeYUV3FiO3szLq44V5cWYsHmB9csralb1eWVUTRBGDBx28QW5Q88fJKlic91KhNLqotKxpTHhBqF4cjDB+TZg8MxYRU2ZcFPwqbxwQiU/5pIXYzboqqAKeUFmaZBbwd01lZW0eDmfqisLsKW3CbGKsorJ5B0nTKRZeSy1KiisiuWVVozJK64pL8TBLa6siVULYwTujeuemFBcGEzg4O+ziqMVxezbwuZzk4Xi4rKawFZNFYox7dX8IE5eMfOzvEK4GtsftPh1QnF1NDpeuF4ojkV5sZOFPO7mAmEk9Y3GJsTH1wxqWdv8ukIo8BKi5ZP4qe74GxXVVAqplMZQpuYTCprH/ilBW3N51+aWLa1oaeq8SdWTK/E3YtS087fPNZ+iJasKSquD/iyIVZTyGwvN7clQKGhuY3qg7bfuLm65+9rgmqCZheMFXjKoEC2WN7m4ArMrXCk0syS4Kt5SeYzok4S8sRNaeqqIty0owwDTt0FJ1ZXlwi3Bp+AD/USzjKmh/olCXmEJDSQEb1lcjYbS1VJF5rdG8o4m+Hv0alyEgjIi83h7lcZrFvr2u1cXFpRTauaRUSoJwoCgD0ros2B25jHwaGFuKC8uHcuMyysvoPqT8wqqxk6Kj+7SI1Pqz6eiRzWlIOh/cUVFedBBeTG0Jz3nC3lHHLwjZxhxzZqub1CjaGFN7Bs30WbB6EQxBD194pFU3sQatHhz9ws9yW3+ZDY/nQdMEKyjn/OiwjghdkTDCAWVpf0nVPefXFren9L6B+1VPrZ/mdRf6t888759BY3Y6oJvni9sdhy+44qg17/rCTWx0rLS2JTvKKEKO3G0kL92xdF++K6alEQLKr+rJsHcrY7b2u+6Ch+npPU=
*/