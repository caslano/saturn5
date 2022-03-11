//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ADAPTIVE_POOL_HPP
#define BOOST_CONTAINER_ADAPTIVE_POOL_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/detail/version_type.hpp>
#include <boost/container/throw_exception.hpp>
#include <boost/container/detail/adaptive_node_pool.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/dlmalloc.hpp>
#include <boost/container/detail/singleton.hpp>
#include <boost/container/detail/placement_new.hpp>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/move/utility_core.hpp>
#include <cstddef>


namespace boost {
namespace container {

//!An STL node allocator that uses a modified DLMalloc as memory
//!source.
//!
//!This node allocator shares a segregated storage between all instances
//!of adaptive_pool with equal sizeof(T).
//!
//!NodesPerBlock is the number of nodes allocated at once when the allocator
//!needs runs out of nodes. MaxFreeBlocks is the maximum number of totally free blocks
//!that the adaptive node pool will hold. The rest of the totally free blocks will be
//!deallocated to the memory manager.
//!
//!OverheadPercent is the (approximated) maximum size overhead (1-20%) of the allocator:
//!(memory usable for nodes / total memory allocated from the memory allocator)
template < class T
         , std::size_t NodesPerBlock   BOOST_CONTAINER_DOCONLY(= ADP_nodes_per_block)
         , std::size_t MaxFreeBlocks   BOOST_CONTAINER_DOCONLY(= ADP_max_free_blocks)
         , std::size_t OverheadPercent BOOST_CONTAINER_DOCONLY(= ADP_overhead_percent)
         BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I unsigned Version)
         >
class adaptive_pool
{
   //!If Version is 1, the allocator is a STL conforming allocator. If Version is 2,
   //!the allocator offers advanced expand in place and burst allocation capabilities.
   public:
   typedef unsigned int allocation_type;
   typedef adaptive_pool
      <T, NodesPerBlock, MaxFreeBlocks, OverheadPercent
         BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)
         >   self_t;

   static const std::size_t nodes_per_block        = NodesPerBlock;
   static const std::size_t max_free_blocks        = MaxFreeBlocks;
   static const std::size_t overhead_percent       = OverheadPercent;
   static const std::size_t real_nodes_per_block   = NodesPerBlock;

   BOOST_CONTAINER_DOCIGN(BOOST_STATIC_ASSERT((Version <=2)));

   public:
   //-------
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef typename ::boost::container::
      dtl::unvoid_ref<T>::type     reference;
   typedef typename ::boost::container::
      dtl::unvoid_ref<const T>::type     const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;

   typedef boost::container::dtl::
      version_type<self_t, Version>             version;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef boost::container::dtl::
      basic_multiallocation_chain<void*>              multiallocation_chain_void;
   typedef boost::container::dtl::
      transform_multiallocation_chain
         <multiallocation_chain_void, T>              multiallocation_chain;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //!Obtains adaptive_pool from
   //!adaptive_pool
   template<class T2>
   struct rebind
   {
      typedef adaptive_pool
         < T2
         , NodesPerBlock
         , MaxFreeBlocks
         , OverheadPercent
         BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)
         >       other;
   };

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   //!Not assignable from related adaptive_pool
   template<class T2, std::size_t N2, std::size_t F2, std::size_t O2, unsigned Version2>
   adaptive_pool& operator=
      (const adaptive_pool<T2, N2, F2, O2, Version2>&);

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //!Default constructor
   adaptive_pool() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from other adaptive_pool.
   adaptive_pool(const adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from related adaptive_pool.
   template<class T2>
   adaptive_pool
      (const adaptive_pool<T2, NodesPerBlock, MaxFreeBlocks, OverheadPercent
            BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Destructor
   ~adaptive_pool() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Returns the number of elements that could be allocated.
   //!Never throws
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return size_type(-1)/(2u*sizeof(T));   }

   //!Allocate memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   pointer allocate(size_type count, const void * = 0)
   {
      if(BOOST_UNLIKELY(count > size_type(-1)/(2u*sizeof(T))))
         boost::container::throw_bad_alloc();

      if(Version == 1 && count == 1){
         typedef typename dtl::shared_adaptive_node_pool
            <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
         typedef dtl::singleton_default<shared_pool_t> singleton_t;
         return pointer(static_cast<T*>(singleton_t::instance().allocate_node()));
      }
      else{
         return static_cast<pointer>(dlmalloc_malloc(count*sizeof(T)));
      }
   }

   //!Deallocate allocated memory.
   //!Never throws
   void deallocate(const pointer &ptr, size_type count) BOOST_NOEXCEPT_OR_NOTHROW
   {
      (void)count;
      if(Version == 1 && count == 1){
         typedef dtl::shared_adaptive_node_pool
            <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
         typedef dtl::singleton_default<shared_pool_t> singleton_t;
         singleton_t::instance().deallocate_node(ptr);
      }
      else{
         dlmalloc_free(ptr);
      }
   }

   pointer allocation_command(allocation_type command,
                         size_type limit_size,
                         size_type &prefer_in_recvd_out_size,
                         pointer &reuse)
   {
      pointer ret = this->priv_allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);
      if(BOOST_UNLIKELY(!ret && !(command & BOOST_CONTAINER_NOTHROW_ALLOCATION)))
         boost::container::throw_bad_alloc();
      return ret;
   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return dlmalloc_size(p);  }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   pointer allocate_one()
   {
      typedef dtl::shared_adaptive_node_pool
         <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      return (pointer)singleton_t::instance().allocate_node();
   }

   //!Allocates many elements of size == 1.
   //!Elements must be individually deallocated with deallocate_one()
   void allocate_individual(std::size_t num_elements, multiallocation_chain &chain)
   {
      typedef dtl::shared_adaptive_node_pool
         <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      singleton_t::instance().allocate_nodes(num_elements, static_cast<typename shared_pool_t::multiallocation_chain&>(chain));
      //typename shared_pool_t::multiallocation_chain ch;
      //singleton_t::instance().allocate_nodes(num_elements, ch);
      //chain.incorporate_after
         //(chain.before_begin(), (T*)&*ch.begin(), (T*)&*ch.last(), ch.size());
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef dtl::shared_adaptive_node_pool
         <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      singleton_t::instance().deallocate_node(p);
   }

   void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef dtl::shared_adaptive_node_pool
         <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      //typename shared_pool_t::multiallocation_chain ch(&*chain.begin(), &*chain.last(), chain.size());
      //singleton_t::instance().deallocate_nodes(ch);
      singleton_t::instance().deallocate_nodes(chain);
   }

   //!Allocates many elements of size elem_size.
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(size_type elem_size, std::size_t n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));/*
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );*/
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes
            (n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));/*
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );*/
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays
         (n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {/*
      dlmalloc_memchain ch;
      void *beg(&*chain.begin()), *last(&*chain.last());
      size_t size(chain.size());
      BOOST_CONTAINER_MEMCHAIN_INIT_FROM(&ch, beg, last, size);
      dlmalloc_multidealloc(&ch);*/
      dlmalloc_multidealloc(reinterpret_cast<dlmalloc_memchain *>(&chain));
   }

   //!Deallocates all free blocks of the pool
   static void deallocate_free_blocks() BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef dtl::shared_adaptive_node_pool
         <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      singleton_t::instance().deallocate_free_blocks();
   }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different memory segment, the result is undefined.
   friend void swap(adaptive_pool &, adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const adaptive_pool &, const adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const adaptive_pool &, const adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   private:
   pointer priv_allocation_command
      (allocation_type command,   std::size_t limit_size
      ,size_type &prefer_in_recvd_out_size, pointer &reuse_ptr)
   {
      std::size_t const preferred_size = prefer_in_recvd_out_size;
      dlmalloc_command_ret_t ret = {0 , 0};
      if(BOOST_UNLIKELY(limit_size > this->max_size() || preferred_size > this->max_size())){
         return pointer();
      }
      std::size_t l_size = limit_size*sizeof(T);
      std::size_t p_size = preferred_size*sizeof(T);
      std::size_t r_size;
      {
         void* reuse_ptr_void = reuse_ptr;
         ret = dlmalloc_allocation_command(command, sizeof(T), l_size, p_size, &r_size, reuse_ptr_void);
         reuse_ptr = ret.second ? static_cast<T*>(reuse_ptr_void) : 0;
      }
      prefer_in_recvd_out_size = r_size/sizeof(T);
      return (pointer)ret.first;
   }
};




















template < class T
         , std::size_t NodesPerBlock   = ADP_nodes_per_block
         , std::size_t MaxFreeBlocks   = ADP_max_free_blocks
         , std::size_t OverheadPercent = ADP_overhead_percent
         , unsigned Version = 2
         >
class private_adaptive_pool
{
   //!If Version is 1, the allocator is a STL conforming allocator. If Version is 2,
   //!the allocator offers advanced expand in place and burst allocation capabilities.
   public:
   typedef unsigned int allocation_type;
   typedef private_adaptive_pool
      <T, NodesPerBlock, MaxFreeBlocks, OverheadPercent
         BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)
         >   self_t;

   static const std::size_t nodes_per_block        = NodesPerBlock;
   static const std::size_t max_free_blocks        = MaxFreeBlocks;
   static const std::size_t overhead_percent       = OverheadPercent;
   static const std::size_t real_nodes_per_block   = NodesPerBlock;

   BOOST_CONTAINER_DOCIGN(BOOST_STATIC_ASSERT((Version <=2)));

   typedef dtl::private_adaptive_node_pool
      <sizeof(T), NodesPerBlock, MaxFreeBlocks, OverheadPercent> pool_t;
   pool_t m_pool;

   public:
   //-------
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef typename ::boost::container::
      dtl::unvoid_ref<T>::type     reference;
   typedef typename ::boost::container::
      dtl::unvoid_ref<const T>::type            const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;

   typedef boost::container::dtl::
      version_type<self_t, Version>             version;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef boost::container::dtl::
      basic_multiallocation_chain<void*>              multiallocation_chain_void;
   typedef boost::container::dtl::
      transform_multiallocation_chain
         <multiallocation_chain_void, T>              multiallocation_chain;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //!Obtains private_adaptive_pool from
   //!private_adaptive_pool
   template<class T2>
   struct rebind
   {
      typedef private_adaptive_pool
         < T2
         , NodesPerBlock
         , MaxFreeBlocks
         , OverheadPercent
         BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)
         >       other;
   };

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   //!Not assignable from related private_adaptive_pool
   template<class T2, std::size_t N2, std::size_t F2, std::size_t O2, unsigned Version2>
   private_adaptive_pool& operator=
      (const private_adaptive_pool<T2, N2, F2, O2, Version2>&);
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //!Default constructor
   private_adaptive_pool() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from other private_adaptive_pool.
   private_adaptive_pool(const private_adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from related private_adaptive_pool.
   template<class T2>
   private_adaptive_pool
      (const private_adaptive_pool<T2, NodesPerBlock, MaxFreeBlocks, OverheadPercent
            BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I Version)> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Destructor
   ~private_adaptive_pool() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Returns the number of elements that could be allocated.
   //!Never throws
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return size_type(-1)/(2u*sizeof(T));   }

   //!Allocate memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   pointer allocate(size_type count, const void * = 0)
   {
      if(BOOST_UNLIKELY(count > size_type(-1)/(2u*sizeof(T))))
         boost::container::throw_bad_alloc();

      if(Version == 1 && count == 1){
         return pointer(static_cast<T*>(m_pool.allocate_node()));
      }
      else{
         return static_cast<pointer>(dlmalloc_malloc(count*sizeof(T)));
      }
   }

   //!Deallocate allocated memory.
   //!Never throws
   void deallocate(const pointer &ptr, size_type count) BOOST_NOEXCEPT_OR_NOTHROW
   {
      (void)count;
      if(Version == 1 && count == 1){
         m_pool.deallocate_node(ptr);
      }
      else{
         dlmalloc_free(ptr);
      }
   }

   pointer allocation_command(allocation_type command,
                         size_type limit_size,
                         size_type &prefer_in_recvd_out_size,
                         pointer &reuse)
   {
      pointer ret = this->priv_allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);
      if(BOOST_UNLIKELY(!ret && !(command & BOOST_CONTAINER_NOTHROW_ALLOCATION)))
         boost::container::throw_bad_alloc();
      return ret;
   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return dlmalloc_size(p);  }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   pointer allocate_one()
   {
      return (pointer)m_pool.allocate_node();
   }

   //!Allocates many elements of size == 1.
   //!Elements must be individually deallocated with deallocate_one()
   void allocate_individual(std::size_t num_elements, multiallocation_chain &chain)
   {
      m_pool.allocate_nodes(num_elements, static_cast<typename pool_t::multiallocation_chain&>(chain));
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      m_pool.deallocate_node(p);
   }

   void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      m_pool.deallocate_nodes(chain);
   }

   //!Allocates many elements of size elem_size.
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(size_type elem_size, std::size_t n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes
            (n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays
         (n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      dlmalloc_multidealloc(reinterpret_cast<dlmalloc_memchain *>(&chain));
   }

   //!Deallocates all free blocks of the pool
   void deallocate_free_blocks() BOOST_NOEXCEPT_OR_NOTHROW
   {
      m_pool.deallocate_free_blocks();
   }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different memory segment, the result is undefined.
   friend void swap(private_adaptive_pool &, private_adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const private_adaptive_pool &, const private_adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const private_adaptive_pool &, const private_adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   private:
   pointer priv_allocation_command
      (allocation_type command,   std::size_t limit_size
      ,size_type &prefer_in_recvd_out_size, pointer &reuse_ptr)
   {
      std::size_t const preferred_size = prefer_in_recvd_out_size;
      dlmalloc_command_ret_t ret = {0 , 0};
      if(BOOST_UNLIKELY(limit_size > this->max_size() || preferred_size > this->max_size())){
         return pointer();
      }
      std::size_t l_size = limit_size*sizeof(T);
      std::size_t p_size = preferred_size*sizeof(T);
      std::size_t r_size;
      {
         void* reuse_ptr_void = reuse_ptr;
         ret = dlmalloc_allocation_command(command, sizeof(T), l_size, p_size, &r_size, reuse_ptr_void);
         reuse_ptr = ret.second ? static_cast<T*>(reuse_ptr_void) : 0;
      }
      prefer_in_recvd_out_size = r_size/sizeof(T);
      return (pointer)ret.first;
   }
};

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_ADAPTIVE_POOL_HPP

/* adaptive_pool.hpp
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
*/