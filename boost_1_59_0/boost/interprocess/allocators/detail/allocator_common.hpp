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
      } BOOST_CATCH_END
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
+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
*/