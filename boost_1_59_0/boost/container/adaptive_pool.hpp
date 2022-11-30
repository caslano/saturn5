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

#include <boost/move/detail/force_ptr.hpp>

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

   //!Copy assignment from other adaptive_pool.
   adaptive_pool & operator=(const adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return *this;  }

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
   //!Throws bad_alloc if there is no enough memory
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
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );*/
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes
            ( n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
            , move_detail::force_ptr<dlmalloc_memchain *>(&chain)))){
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
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );*/
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays
         ( n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
         , move_detail::force_ptr<dlmalloc_memchain *>(&chain)))){
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
      dlmalloc_multidealloc(move_detail::force_ptr<dlmalloc_memchain *>(&chain));
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

   //!Copy assignment from other adaptive_pool.
   private_adaptive_pool & operator=(const private_adaptive_pool &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return *this;  }

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
   //!Throws bad_alloc if there is no enough memory
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
            ( n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
            , move_detail::force_ptr<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_arrays
         (n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
         , move_detail::force_ptr<dlmalloc_memchain *>(&chain)))){
         boost::container::throw_bad_alloc();
      }
   }

   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      dlmalloc_multidealloc(move_detail::force_ptr<dlmalloc_memchain *>(&chain));
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