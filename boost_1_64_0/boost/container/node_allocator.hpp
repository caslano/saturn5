//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_POOLED_NODE_ALLOCATOR_HPP
#define BOOST_CONTAINER_POOLED_NODE_ALLOCATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/throw_exception.hpp>
#include <boost/container/detail/node_pool.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/container/detail/dlmalloc.hpp>
#include <boost/container/detail/singleton.hpp>

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>

namespace boost {
namespace container {

//!An STL node allocator that uses a modified DlMalloc as memory
//!source.
//!
//!This node allocator shares a segregated storage between all instances
//!of node_allocator with equal sizeof(T).
//!
//!NodesPerBlock is the number of nodes allocated at once when the allocator
//!runs out of nodes
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template
   < class T
   , std::size_t NodesPerBlock = NodeAlloc_nodes_per_block>
#else
template
   < class T
   , std::size_t NodesPerBlock
   , std::size_t Version>
#endif
class node_allocator
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   //! If Version is 1, the allocator is a STL conforming allocator. If Version is 2,
   //! the allocator offers advanced expand in place and burst allocation capabilities.
   public:
   typedef unsigned int allocation_type;
   typedef node_allocator<T, NodesPerBlock, Version>   self_t;

   static const std::size_t nodes_per_block = NodesPerBlock;

   BOOST_STATIC_ASSERT((Version <=2));
   #endif

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

   //!Obtains node_allocator from
   //!node_allocator
   template<class T2>
   struct rebind
   {
      typedef node_allocator< T2, NodesPerBlock
                            #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
                            , Version
                            #endif
                            > other;
   };

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   //!Not assignable from related node_allocator
   template<class T2, std::size_t N2>
   node_allocator& operator=
      (const node_allocator<T2, N2>&);
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:

   //!Default constructor
   node_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from other node_allocator.
   node_allocator(const node_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy constructor from related node_allocator.
   template<class T2>
   node_allocator
      (const node_allocator<T2, NodesPerBlock
            #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
            , Version
            #endif
            > &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Destructor
   ~node_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Returns the number of elements that could be allocated.
   //!Never throws
   size_type max_size() const
   {  return size_type(-1)/sizeof(T);   }

   //!Allocate memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   pointer allocate(size_type count, const void * = 0)
   {
      if(BOOST_UNLIKELY(count > this->max_size()))
         boost::container::throw_bad_alloc();

      if(Version == 1 && count == 1){
         typedef dtl::shared_node_pool
            <sizeof(T), NodesPerBlock> shared_pool_t;
         typedef dtl::singleton_default<shared_pool_t> singleton_t;
         return pointer(static_cast<T*>(singleton_t::instance().allocate_node()));
      }
      else{
         void *ret = dlmalloc_malloc(count*sizeof(T));
         if(BOOST_UNLIKELY(!ret))
            boost::container::throw_bad_alloc();
         return static_cast<pointer>(ret);
      }
   }

   //!Deallocate allocated memory.
   //!Never throws
   void deallocate(const pointer &ptr, size_type count) BOOST_NOEXCEPT_OR_NOTHROW
   {
      (void)count;
      if(Version == 1 && count == 1){
         typedef dtl::shared_node_pool
            <sizeof(T), NodesPerBlock> shared_pool_t;
         typedef dtl::singleton_default<shared_pool_t> singleton_t;
         singleton_t::instance().deallocate_node(ptr);
      }
      else{
         dlmalloc_free(ptr);
      }
   }

   //!Deallocates all free blocks of the pool
   static void deallocate_free_blocks() BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef dtl::shared_node_pool
         <sizeof(T), NodesPerBlock> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      singleton_t::instance().deallocate_free_blocks();
   }

   pointer allocation_command
      (allocation_type command, size_type limit_size, size_type &prefer_in_recvd_out_size, pointer &reuse)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      pointer ret = this->priv_allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);
      if(BOOST_UNLIKELY(!ret && !(command & BOOST_CONTAINER_NOTHROW_ALLOCATION)))
         boost::container::throw_bad_alloc();
      return ret;
   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return dlmalloc_size(p);
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   pointer allocate_one()
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      typedef dtl::shared_node_pool
         <sizeof(T), NodesPerBlock> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      return (pointer)singleton_t::instance().allocate_node();
   }

   //!Allocates many elements of size == 1.
   //!Elements must be individually deallocated with deallocate_one()
   void allocate_individual(std::size_t num_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      typedef dtl::shared_node_pool
         <sizeof(T), NodesPerBlock> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      typename shared_pool_t::multiallocation_chain ch;
      singleton_t::instance().allocate_nodes(num_elements, ch);
      chain.incorporate_after(chain.before_begin(), (T*)&*ch.begin(), (T*)&*ch.last(), ch.size());
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one(). Never throws
   void deallocate_one(pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      typedef dtl::shared_node_pool
         <sizeof(T), NodesPerBlock> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      singleton_t::instance().deallocate_node(p);
   }

   void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      typedef dtl::shared_node_pool
         <sizeof(T), NodesPerBlock> shared_pool_t;
      typedef dtl::singleton_default<shared_pool_t> singleton_t;
      typename shared_pool_t::multiallocation_chain ch(&*chain.begin(), &*chain.last(), chain.size());
      singleton_t::instance().deallocate_nodes(ch);
   }

   //!Allocates many elements of size elem_size.
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(size_type elem_size, std::size_t n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after( chain.before_begin()
                             , (T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             , (T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             , BOOST_CONTAINER_MEMCHAIN_SIZE(&ch));
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch);
      if(BOOST_UNLIKELY(BOOST_CONTAINER_MEMCHAIN_EMPTY(&ch))){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after( chain.before_begin()
                             , (T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             , (T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             , BOOST_CONTAINER_MEMCHAIN_SIZE(&ch));
   }

   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      void *first = &*chain.begin();
      void *last  = &*chain.last();
      size_t num  = chain.size();
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT_FROM(&ch, first, last, num);
      dlmalloc_multidealloc(&ch);
   }

   //!Swaps allocators. Does not throw. If each allocator is placed in a
   //!different memory segment, the result is undefined.
   friend void swap(self_t &, self_t &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const node_allocator &, const node_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const node_allocator &, const node_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   private:
   pointer priv_allocation_command
      (allocation_type command,   std::size_t limit_size
      ,size_type &prefer_in_recvd_out_size
      ,pointer &reuse)
   {
      std::size_t const preferred_size = prefer_in_recvd_out_size;
      dlmalloc_command_ret_t ret = {0 , 0};
      if((limit_size > this->max_size()) | (preferred_size > this->max_size())){
         return pointer();
      }
      std::size_t l_size = limit_size*sizeof(T);
      std::size_t p_size = preferred_size*sizeof(T);
      std::size_t r_size;
      {
         void* reuse_ptr_void = reuse;
         ret = dlmalloc_allocation_command(command, sizeof(T), l_size, p_size, &r_size, reuse_ptr_void);
         reuse = static_cast<T*>(reuse_ptr_void);
      }
      prefer_in_recvd_out_size = r_size/sizeof(T);
      return (pointer)ret.first;
   }
};

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_POOLED_NODE_ALLOCATOR_HPP

/* node_allocator.hpp
bHyNe0ArL6zt6olfkUXR0oQ96x3WlyyOlkOYXNsLr5rX4lKYR2E+hQXQUoRdHLi3NFkQbb2w3gcrLyPzjzbvPYQmx8P5ELYImuxdrnmOGuKKVnnmEVkcTdbJ6wvQYIwDrBaxb/evPELmzUxcyxOWe8v5XPz5h0a1lDbchwSlGe6XQtIM92Bhg9WsZnmXLIKWJqz6xAu3yWIyznDPF0crK6zrO676ZK7XsufkNc9oHjSzHrxoZj340PrIWhznuYeYwRqOd1g4biweE8KmTX+UQRY02O0pxd4hi6DVEVak+5S/ybRx2eMutHh5G/eHNlrYzaUFKpFF0ZoLs9QpzeO5X3dAR2Ef+LLy8zs+NDpeyljHQ48fLm8nixjs1IRbg8jiaM8JK9vzz+Zk3vEOSLfollbunQKc8w0H1LDqNqr+qQBZIAufO0C349b5f3EcWhtha2Iz9pK5JuG+FSb/PokbraOwG4PbduTe0aoLq5c19zZZFC1Z2M6ApRpZDC1JGD/DosXR5gpbnNe+lCw02QEFhXUo75jL/aGVFNusUVaRMtzDm/rnEVr294YK8yssqLCwwqIKiytMm2JubrQCwrocu1ae+0N7QVi5POUTc/cDIIL2XtJ/VhaP609iBQ/Q7y57ZuhzseXQBi7vcIEMF7DDLWFT+674icw9E2sR1v9Sve1kXrT8wgpPn3GTzIeWTxi//0Pzo7mEna3S+jRZCK2esBffHJKDLI7WXRi//0Pz4Z9+eSis5dftenPO2fjOTRi/c0ODOebmQ3tOGL+PQ4ugzRbG7+PQ/HMdME9Y01sNWpC533FAaWHtFz9O4/HQUoXxMYEWUFhIYRGFxRQG88xsBLjQHiWOs/LWfrB6ScNlbO8l3oElbGRJW2eyOFpdYee8lSNknoV4zRLG8yhoXrQUYfz9cDSfwRoH504i8xvs0bHHncgChvH4HgwtaIj7PtcrJclCBtuw7uAfZGFDTr7uokXQKgkrN+pILjJYlD2O70PQNIPxnA6ay2A8/4LmNhjPo6B5DMb3GmheNNkff08fzWewm/6MGWR+tFzChp/p9hxZwGAXFre5QBZEKyHsrXtfdSOLGOIqNtlTgixq6IHnz9BiBuP7HrS4wXiuCw3ez97fpqkFUsk0NFnL+uGp48lcaDInz3WhuQ3G91loHrTPrLqd6TxsOlloiQO8Iu7O+kmtuZalDrgurHal37pyzmWG43r10UJkXjTZ3+x1OaqQ+dBqCvPUS0viWtCKCbsY7rOeLGoY71yNpBNkMbQmwrr3KrSMzL3csM02F8ngHtBknZ7+qQ7uAa2usEv/ZhXhOtGKCuN3NmgRNLn//rpR8i/uwWA9ZxeYyD2gmR2f2ofm47nRSgq7XOoM7wcfmsyZMnlYI7KgIe7xHz+04R7QxDYTc2vYg8F4XhEthlZEGP99QzRY4YCcSbqNXrGlAedc6YBaFt1WDg7PJfN+7ICFoFuXPdOnk2mrs/eQf7q+JtiDtkHY0PE1h5G5PsHnTTHeyGp/j+a4NbiPUnTrdGhFFa5lowO2g25bXj03keO+wvtrYQvm7p1KFkCbKsbbMbPtC2T+TQ54R5i75oX7bJvxPsuqW/UNoZZk4W0O2Chs2neFSpJp3zmgn7yelcy7mSyIlkuMt7FdHh9Z7Hs8XoQtHpK3Bff+PwfMAd2ShufknPAD7ncRt2/EgXQy304H7BVxa5/Z2pNtlwO+FvZRi0aVeLzdDugqcnZ7OrovGexxgE/Erflk5EWyAFoBEffljSoZ3N9PDsBotkXayntk/r0OeFdYsay39M+4fbg9xbbO89ey+2z78dwU9uc739jIogcT618S9sLY9z1cSxSvdSJu3bo=
*/