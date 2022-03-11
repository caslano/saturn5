//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ALLOCATOR_DETAIL_ALLOCATOR_COMMON_HPP
#define BOOST_INTERPROCESS_ALLOCATOR_DETAIL_ALLOCATOR_COMMON_HPP

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
#include <boost/interprocess/detail/utilities.hpp> //to_raw_pointer
#include <boost/utility/addressof.hpp> //boost::addressof
#include <boost/assert.hpp>   //BOOST_ASSERT
#include <boost/interprocess/exceptions.hpp> //bad_alloc
#include <boost/interprocess/sync/scoped_lock.hpp> //scoped_lock
#include <boost/interprocess/containers/allocation_type.hpp> //boost::interprocess::allocation_type
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/interprocess/mem_algo/detail/mem_algo_common.hpp>
#include <boost/interprocess/detail/segment_manager_helper.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/container/detail/placement_new.hpp>
#include <boost/move/adl_move_swap.hpp>

namespace boost {
namespace interprocess {

template <class T>
struct sizeof_value
{
   static const std::size_t value = sizeof(T);
};

template <>
struct sizeof_value<void>
{
   static const std::size_t value = sizeof(void*);
};

template <>
struct sizeof_value<const void>
{
   static const std::size_t value = sizeof(void*);
};

template <>
struct sizeof_value<volatile void>
{
   static const std::size_t value = sizeof(void*);
};

template <>
struct sizeof_value<const volatile void>
{
   static const std::size_t value = sizeof(void*);
};

namespace ipcdetail {

//!Object function that creates the node allocator if it is not created and
//!increments reference count if it is already created
template<class NodePool>
struct get_or_create_node_pool_func
{

   //!This connects or constructs the unique instance of node_pool_t
   //!Can throw boost::interprocess::bad_alloc
   void operator()()
   {
      //Find or create the node_pool_t
      mp_node_pool =    mp_segment_manager->template find_or_construct
                        <NodePool>(boost::interprocess::unique_instance)(mp_segment_manager);
      //If valid, increment link count
      if(mp_node_pool != 0)
         mp_node_pool->inc_ref_count();
   }

   //!Constructor. Initializes function
   //!object parameters
   get_or_create_node_pool_func(typename NodePool::segment_manager *mngr)
      : mp_segment_manager(mngr){}

   NodePool                            *mp_node_pool;
   typename NodePool::segment_manager  *mp_segment_manager;
};

template<class NodePool>
inline NodePool *get_or_create_node_pool(typename NodePool::segment_manager *mgnr)
{
   ipcdetail::get_or_create_node_pool_func<NodePool> func(mgnr);
   mgnr->atomic_func(func);
   return func.mp_node_pool;
}

//!Object function that decrements the reference count. If the count
//!reaches to zero destroys the node allocator from memory.
//!Never throws
template<class NodePool>
struct destroy_if_last_link_func
{
   //!Decrements reference count and destroys the object if there is no
   //!more attached allocators. Never throws
   void operator()()
   {
      //If not the last link return
      if(mp_node_pool->dec_ref_count() != 0) return;

      //Last link, let's destroy the segment_manager
      mp_node_pool->get_segment_manager()->template destroy<NodePool>(boost::interprocess::unique_instance);
   }

   //!Constructor. Initializes function
   //!object parameters
   destroy_if_last_link_func(NodePool *pool)
      : mp_node_pool(pool)
   {}

   NodePool                           *mp_node_pool;
};

//!Destruction function, initializes and executes destruction function
//!object. Never throws
template<class NodePool>
inline void destroy_node_pool_if_last_link(NodePool *pool)
{
   //Get segment manager
   typename NodePool::segment_manager *mngr = pool->get_segment_manager();
   //Execute destruction functor atomically
   destroy_if_last_link_func<NodePool>func(pool);
   mngr->atomic_func(func);
}

template<class NodePool>
class cache_impl
{
   typedef typename NodePool::segment_manager::
      void_pointer                                          void_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<NodePool>::type                     node_pool_ptr;
   typedef typename NodePool::multiallocation_chain         multiallocation_chain;
   typedef typename NodePool::segment_manager::size_type    size_type;
   node_pool_ptr                 mp_node_pool;
   multiallocation_chain         m_cached_nodes;
   size_type                     m_max_cached_nodes;

   public:
   typedef typename NodePool::segment_manager            segment_manager;

   cache_impl(segment_manager *segment_mngr, size_type max_cached_nodes)
      : mp_node_pool(get_or_create_node_pool<NodePool>(segment_mngr))
      , m_max_cached_nodes(max_cached_nodes)
   {}

   cache_impl(const cache_impl &other)
      : mp_node_pool(other.get_node_pool())
      , m_max_cached_nodes(other.get_max_cached_nodes())
   {
      mp_node_pool->inc_ref_count();
   }

   ~cache_impl()
   {
      this->deallocate_all_cached_nodes();
      ipcdetail::destroy_node_pool_if_last_link(ipcdetail::to_raw_pointer(mp_node_pool));
   }

   NodePool *get_node_pool() const
   {  return ipcdetail::to_raw_pointer(mp_node_pool); }

   segment_manager *get_segment_manager() const
   {  return mp_node_pool->get_segment_manager(); }

   size_type get_max_cached_nodes() const
   {  return m_max_cached_nodes; }

   void *cached_allocation()
   {
      //If don't have any cached node, we have to get a new list of free nodes from the pool
      if(m_cached_nodes.empty()){
         mp_node_pool->allocate_nodes(m_max_cached_nodes/2, m_cached_nodes);
      }
      void *ret = ipcdetail::to_raw_pointer(m_cached_nodes.pop_front());
      return ret;
   }

   void cached_allocation(size_type n, multiallocation_chain &chain)
   {
      size_type count = n, allocated(0);
      BOOST_TRY{
         //If don't have any cached node, we have to get a new list of free nodes from the pool
         while(!m_cached_nodes.empty() && count--){
            void *ret = ipcdetail::to_raw_pointer(m_cached_nodes.pop_front());
            chain.push_back(ret);
            ++allocated;
         }

         if(allocated != n){
            mp_node_pool->allocate_nodes(n - allocated, chain);
         }
      }
      BOOST_CATCH(...){
         this->cached_deallocation(chain);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   void cached_deallocation(void *ptr)
   {
      //Check if cache is full
      if(m_cached_nodes.size() >= m_max_cached_nodes){
         //This only occurs if this allocator deallocate memory allocated
         //with other equal allocator. Since the cache is full, and more
         //deallocations are probably coming, we'll make some room in cache
         //in a single, efficient multi node deallocation.
         this->priv_deallocate_n_nodes(m_cached_nodes.size() - m_max_cached_nodes/2);
      }
      m_cached_nodes.push_front(ptr);
   }

   void cached_deallocation(multiallocation_chain &chain)
   {
      m_cached_nodes.splice_after(m_cached_nodes.before_begin(), chain);

      //Check if cache is full
      if(m_cached_nodes.size() >= m_max_cached_nodes){
         //This only occurs if this allocator deallocate memory allocated
         //with other equal allocator. Since the cache is full, and more
         //deallocations are probably coming, we'll make some room in cache
         //in a single, efficient multi node deallocation.
         this->priv_deallocate_n_nodes(m_cached_nodes.size() - m_max_cached_nodes/2);
      }
   }

   //!Sets the new max cached nodes value. This can provoke deallocations
   //!if "newmax" is less than current cached nodes. Never throws
   void set_max_cached_nodes(size_type newmax)
   {
      m_max_cached_nodes = newmax;
      this->priv_deallocate_remaining_nodes();
   }

   //!Frees all cached nodes.
   //!Never throws
   void deallocate_all_cached_nodes()
   {
      if(m_cached_nodes.empty()) return;
      mp_node_pool->deallocate_nodes(m_cached_nodes);
   }

   private:
   //!Frees all cached nodes at once.
   //!Never throws
   void priv_deallocate_remaining_nodes()
   {
      if(m_cached_nodes.size() > m_max_cached_nodes){
         priv_deallocate_n_nodes(m_cached_nodes.size()-m_max_cached_nodes);
      }
   }

   //!Frees n cached nodes at once. Never throws
   void priv_deallocate_n_nodes(size_type n)
   {
      //This only occurs if this allocator deallocate memory allocated
      //with other equal allocator. Since the cache is full, and more
      //deallocations are probably coming, we'll make some room in cache
      //in a single, efficient multi node deallocation.
      size_type count(n);
      typename multiallocation_chain::iterator it(m_cached_nodes.before_begin());
      while(count--){
         ++it;
      }
      multiallocation_chain chain;
      chain.splice_after(chain.before_begin(), m_cached_nodes, m_cached_nodes.before_begin(), it, n);
      //Deallocate all new linked list at once
      mp_node_pool->deallocate_nodes(chain);
   }

   public:
   void swap(cache_impl &other)
   {
      ::boost::adl_move_swap(mp_node_pool, other.mp_node_pool);
      ::boost::adl_move_swap(m_cached_nodes, other.m_cached_nodes);
      ::boost::adl_move_swap(m_max_cached_nodes, other.m_max_cached_nodes);
   }
};

template<class Derived, class T, class SegmentManager>
class array_allocation_impl
{
   const Derived *derived() const
   {  return static_cast<const Derived*>(this); }
   Derived *derived()
   {  return static_cast<Derived*>(this); }

   typedef typename SegmentManager::void_pointer         void_pointer;

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
   typedef typename SegmentManager::size_type            size_type;
   typedef typename SegmentManager::difference_type      difference_type;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;


   public:
   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold. This size only works for memory allocated with
   //!allocate, allocation_command and allocate_many.
   size_type size(const pointer &p) const
   {
      return (size_type)this->derived()->get_segment_manager()->size(ipcdetail::to_raw_pointer(p))/sizeof(T);
   }

   pointer allocation_command(boost::interprocess::allocation_type command,
                         size_type limit_size, size_type &prefer_in_recvd_out_size, pointer &reuse)
   {
      value_type *reuse_raw = ipcdetail::to_raw_pointer(reuse);
      pointer const p = this->derived()->get_segment_manager()->allocation_command
         (command, limit_size, prefer_in_recvd_out_size, reuse_raw);
      reuse = reuse_raw;
      return p;
   }

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void allocate_many(size_type elem_size, size_type num_elements, multiallocation_chain &chain)
   {
      if(size_overflows<sizeof(T)>(elem_size)){
         throw bad_alloc();
      }
      this->derived()->get_segment_manager()->allocate_many(elem_size*sizeof(T), num_elements, chain);
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]in a
   //!contiguous block
   //!of memory. The elements must be deallocated
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      this->derived()->get_segment_manager()->allocate_many(elem_sizes, n_elements, sizeof(T), chain);
   }

   //!Allocates many elements of size elem_size in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. The elements must be deallocated
   //!with deallocate(...)
   void deallocate_many(multiallocation_chain &chain)
   {  this->derived()->get_segment_manager()->deallocate_many(chain); }

   //!Returns the number of elements that could be
   //!allocated. Never throws
   size_type max_size() const
   {  return this->derived()->get_segment_manager()->get_size()/sizeof(T);  }

   //!Returns address of mutable object.
   //!Never throws
   pointer address(reference value) const
   {  return pointer(boost::addressof(value));  }

   //!Returns address of non mutable object.
   //!Never throws
   const_pointer address(const_reference value) const
   {  return const_pointer(boost::addressof(value));  }

   //!Constructs an object
   //!Throws if T's constructor throws
   //!For backwards compatibility with libraries using C++03 allocators
   template<class P>
   void construct(const pointer &ptr, BOOST_FWD_REF(P) p)
   {  ::new((void*)ipcdetail::to_raw_pointer(ptr), boost_container_new_t()) value_type(::boost::forward<P>(p));  }

   //!Destroys object. Throws if object's
   //!destructor throws
   void destroy(const pointer &ptr)
   {  BOOST_ASSERT(ptr != 0); (*ptr).~value_type();  }
};


template<class Derived, unsigned int Version, class T, class SegmentManager>
class node_pool_allocation_impl
   :  public array_allocation_impl
      < Derived
      , T
      , SegmentManager>
{
   const Derived *derived() const
   {  return static_cast<const Derived*>(this); }
   Derived *derived()
   {  return static_cast<Derived*>(this); }

   typedef typename SegmentManager::void_pointer         void_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<const void>::type                cvoid_pointer;

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
   typedef typename SegmentManager::size_type            size_type;
   typedef typename SegmentManager::difference_type      difference_type;
   typedef boost::container::dtl::transform_multiallocation_chain
      <typename SegmentManager::multiallocation_chain, T>multiallocation_chain;


   template <int Dummy>
   struct node_pool
   {
      typedef typename Derived::template node_pool<0>::type type;
      static type *get(void *p)
      {  return static_cast<type*>(p); }
   };

   public:
   //!Allocate memory for an array of count elements.
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate(size_type count, cvoid_pointer hint = 0)
   {
      (void)hint;
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      else if(Version == 1 && count == 1){
         return pointer(static_cast<value_type*>
         (pool->allocate_node()));
      }
      else{
         return pointer(static_cast<value_type*>
            (pool->get_segment_manager()->allocate(count*sizeof(T))));
      }
   }

   //!Deallocate allocated memory. Never throws
   void deallocate(const pointer &ptr, size_type count)
   {
      (void)count;
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      if(Version == 1 && count == 1)
         pool->deallocate_node(ipcdetail::to_raw_pointer(ptr));
      else
         pool->get_segment_manager()->deallocate((void*)ipcdetail::to_raw_pointer(ptr));
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate_one()
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      return pointer(static_cast<value_type*>(pool->allocate_node()));
   }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void allocate_individual(size_type num_elements, multiallocation_chain &chain)
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      pool->allocate_nodes(num_elements, chain);
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(const pointer &p)
   {
      typedef typename node_pool<0>::type node_pool_t;
      node_pool_t *pool = node_pool<0>::get(this->derived()->get_node_pool());
      pool->deallocate_node(ipcdetail::to_raw_pointer(p));
   }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void deallocate_individual(multiallocation_chain &chain)
   {
      node_pool<0>::get(this->derived()->get_node_pool())->deallocate_nodes
         (chain);
   }

   //!Deallocates all free blocks of the pool
   void deallocate_free_blocks()
   {  node_pool<0>::get(this->derived()->get_node_pool())->deallocate_free_blocks();  }

   //!Deprecated, use deallocate_free_blocks.
   //!Deallocates all free chunks of the pool.
   void deallocate_free_chunks()
   {  node_pool<0>::get(this->derived()->get_node_pool())->deallocate_free_blocks();  }
};

template<class T, class NodePool, unsigned int Version>
class cached_allocator_impl
   :  public array_allocation_impl
         <cached_allocator_impl<T, NodePool, Version>, T, typename NodePool::segment_manager>
{
   cached_allocator_impl & operator=(const cached_allocator_impl& other);
   typedef array_allocation_impl
         < cached_allocator_impl
            <T, NodePool, Version>
         , T
         , typename NodePool::segment_manager> base_t;

   public:
   typedef NodePool                                      node_pool_t;
   typedef typename NodePool::segment_manager            segment_manager;
   typedef typename segment_manager::void_pointer        void_pointer;
   typedef typename boost::intrusive::
      pointer_traits<void_pointer>::template
         rebind_pointer<const void>::type                cvoid_pointer;
   typedef typename base_t::pointer                      pointer;
   typedef typename base_t::size_type                    size_type;
   typedef typename base_t::multiallocation_chain        multiallocation_chain;
   typedef typename base_t::value_type                   value_type;

   public:
   static const std::size_t DEFAULT_MAX_CACHED_NODES = 64;

   cached_allocator_impl(segment_manager *segment_mngr, size_type max_cached_nodes)
      : m_cache(segment_mngr, max_cached_nodes)
   {}

   cached_allocator_impl(const cached_allocator_impl &other)
      : m_cache(other.m_cache)
   {}

   //!Copy constructor from related cached_adaptive_pool_base. If not present, constructs
   //!a node pool. Increments the reference count of the associated node pool.
   //!Can throw boost::interprocess::bad_alloc
   template<class T2, class NodePool2>
   cached_allocator_impl
      (const cached_allocator_impl
         <T2, NodePool2, Version> &other)
      : m_cache(other.get_segment_manager(), other.get_max_cached_nodes())
   {}

   //!Returns a pointer to the node pool.
   //!Never throws
   node_pool_t* get_node_pool() const
   {  return m_cache.get_node_pool();   }

   //!Returns the segment manager.
   //!Never throws
   segment_manager* get_segment_manager()const
   {  return m_cache.get_segment_manager();   }

   //!Sets the new max cached nodes value. This can provoke deallocations
   //!if "newmax" is less than current cached nodes. Never throws
   void set_max_cached_nodes(size_type newmax)
   {  m_cache.set_max_cached_nodes(newmax);   }

   //!Returns the max cached nodes parameter.
   //!Never throws
   size_type get_max_cached_nodes() const
   {  return m_cache.get_max_cached_nodes();   }

   //!Allocate memory for an array of count elements.
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate(size_type count, cvoid_pointer hint = 0)
   {
      (void)hint;
      void * ret;
      if(size_overflows<sizeof(T)>(count)){
         throw bad_alloc();
      }
      else if(Version == 1 && count == 1){
         ret = m_cache.cached_allocation();
      }
      else{
         ret = this->get_segment_manager()->allocate(count*sizeof(T));
      }
      return pointer(static_cast<T*>(ret));
   }

   //!Deallocate allocated memory. Never throws
   void deallocate(const pointer &ptr, size_type count)
   {
      (void)count;
      if(Version == 1 && count == 1){
         m_cache.cached_deallocation(ipcdetail::to_raw_pointer(ptr));
      }
      else{
         this->get_segment_manager()->deallocate((void*)ipcdetail::to_raw_pointer(ptr));
      }
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws boost::interprocess::bad_alloc if there is no enough memory
   pointer allocate_one()
   {  return pointer(static_cast<value_type*>(this->m_cache.cached_allocation()));   }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void allocate_individual(size_type num_elements, multiallocation_chain &chain)
   {  this->m_cache.cached_allocation(num_elements, chain);   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(const pointer &p)
   {  this->m_cache.cached_deallocation(ipcdetail::to_raw_pointer(p)); }

   //!Allocates many elements of size == 1 in a contiguous block
   //!of memory. The minimum number to be allocated is min_elements,
   //!the preferred and maximum number is
   //!preferred_elements. The number of actually allocated elements is
   //!will be assigned to received_size. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   void deallocate_individual(multiallocation_chain &chain)
   {  m_cache.cached_deallocation(chain);  }

   //!Deallocates all free blocks of the pool
   void deallocate_free_blocks()
   {  m_cache.get_node_pool()->deallocate_free_blocks();   }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different shared memory segments, the result is undefined.
   friend void swap(cached_allocator_impl &alloc1, cached_allocator_impl &alloc2)
   {  ::boost::adl_move_swap(alloc1.m_cache, alloc2.m_cache);   }

   void deallocate_cache()
   {  m_cache.deallocate_all_cached_nodes(); }

   //!Deprecated use deallocate_free_blocks.
   void deallocate_free_chunks()
   {  m_cache.get_node_pool()->deallocate_free_blocks();   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   cache_impl<node_pool_t> m_cache;
   #endif   //!defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
};

//!Equality test for same type of
//!cached_allocator_impl
template<class T, class N, unsigned int V> inline
bool operator==(const cached_allocator_impl<T, N, V> &alloc1,
                const cached_allocator_impl<T, N, V> &alloc2)
   {  return alloc1.get_node_pool() == alloc2.get_node_pool(); }

//!Inequality test for same type of
//!cached_allocator_impl
template<class T, class N, unsigned int V> inline
bool operator!=(const cached_allocator_impl<T, N, V> &alloc1,
                const cached_allocator_impl<T, N, V> &alloc2)
   {  return alloc1.get_node_pool() != alloc2.get_node_pool(); }


//!Pooled shared memory allocator using adaptive pool. Includes
//!a reference count but the class does not delete itself, this is
//!responsibility of user classes. Node size (NodeSize) and the number of
//!nodes allocated per block (NodesPerBlock) are known at compile time
template<class private_node_allocator_t>
class shared_pool_impl
   : public private_node_allocator_t
{
 public:
   //!Segment manager typedef
   typedef typename private_node_allocator_t::
      segment_manager                           segment_manager;
   typedef typename private_node_allocator_t::
      multiallocation_chain                     multiallocation_chain;
   typedef typename private_node_allocator_t::
     size_type                                 size_type;

 private:
   typedef typename segment_manager::mutex_family::mutex_type mutex_type;

 public:
   //!Constructor from a segment manager. Never throws
   shared_pool_impl(segment_manager *segment_mngr)
      : private_node_allocator_t(segment_mngr)
   {}

   //!Destructor. Deallocates all allocated blocks. Never throws
   ~shared_pool_impl()
   {}

   //!Allocates array of count elements. Can throw boost::interprocess::bad_alloc
   void *allocate_node()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      return private_node_allocator_t::allocate_node();
   }

   //!Deallocates an array pointed by ptr. Never throws
   void deallocate_node(void *ptr)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_node(ptr);
   }

   //!Allocates n nodes.
   //!Can throw boost::interprocess::bad_alloc
   void allocate_nodes(const size_type n, multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::allocate_nodes(n, chain);
   }

   //!Deallocates a linked list of nodes ending in null pointer. Never throws
   void deallocate_nodes(multiallocation_chain &nodes, size_type num)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_nodes(nodes, num);
   }

   //!Deallocates the nodes pointed by the multiallocation iterator. Never throws
   void deallocate_nodes(multiallocation_chain &chain)
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_nodes(chain);
   }

   //!Deallocates all the free blocks of memory. Never throws
   void deallocate_free_blocks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_free_blocks();
   }

   //!Deallocates all used memory from the common pool.
   //!Precondition: all nodes allocated from this pool should
   //!already be deallocated. Otherwise, undefined behavior. Never throws
   void purge_blocks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::purge_blocks();
   }

   //!Increments internal reference count and returns new count. Never throws
   size_type inc_ref_count()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      return ++m_header.m_usecount;
   }

   //!Decrements internal reference count and returns new count. Never throws
   size_type dec_ref_count()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      BOOST_ASSERT(m_header.m_usecount > 0);
      return --m_header.m_usecount;
   }

   //!Deprecated, use deallocate_free_blocks.
   void deallocate_free_chunks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::deallocate_free_blocks();
   }

   //!Deprecated, use purge_blocks.
   void purge_chunks()
   {
      //-----------------------
      boost::interprocess::scoped_lock<mutex_type> guard(m_header);
      //-----------------------
      private_node_allocator_t::purge_blocks();
   }

   private:
   //!This struct includes needed data and derives from
   //!the mutex type to allow EBO when using null_mutex
   struct header_t : mutex_type
   {
      size_type m_usecount;    //Number of attached allocators

      header_t()
      :  m_usecount(0) {}
   } m_header;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_ALLOCATOR_DETAIL_ALLOCATOR_COMMON_HPP

/* allocator_common.hpp
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
*/