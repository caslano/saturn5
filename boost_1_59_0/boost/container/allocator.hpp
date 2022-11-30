//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_ALLOCATOR_HPP
#define BOOST_CONTAINER_ALLOCATOR_HPP

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
#include <boost/container/detail/dlmalloc.hpp>
#include <boost/container/detail/multiallocation_chain.hpp>
#include <boost/static_assert.hpp>

#include <boost/move/detail/force_ptr.hpp>

#include <cstddef>
#include <cassert>

//!\file

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

template<unsigned Version, unsigned int AllocationDisableMask>
class allocator<void, Version, AllocationDisableMask>
{
   typedef allocator<void, Version, AllocationDisableMask>   self_t;
   public:
   typedef void                                 value_type;
   typedef void *                               pointer;
   typedef const void*                          const_pointer;
   typedef int &                                reference;
   typedef const int &                          const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;
   typedef boost::container::dtl::
      version_type<self_t, Version>             version;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef boost::container::dtl::
         basic_multiallocation_chain<void*>        multiallocation_chain;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //!Obtains an allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef allocator< T2
                       #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
                       , Version, AllocationDisableMask
                       #endif
                       > other;
   };

   //!Default constructor
   //!Never throws
   allocator()
   {}

   //!Constructor from other allocator.
   //!Never throws
   allocator(const allocator &)
   {}

   //!Constructor from related allocator.
   //!Never throws
   template<class T2>
      allocator(const allocator<T2, Version, AllocationDisableMask> &)
   {}
};

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! This class is an extended STL-compatible that offers advanced allocation mechanism
//!(in-place expansion, shrinking, burst-allocation...)
//!
//! This allocator is a wrapper around a modified DLmalloc.
//! If Version is 1, the allocator is a STL conforming allocator. If Version is 2,
//! the allocator offers advanced expand in place and burst allocation capabilities.
//!
//! AllocationDisableMask works only if Version is 2 and it can be an inclusive OR
//! of allocation types the user wants to disable.
template< class T
        , unsigned Version BOOST_CONTAINER_DOCONLY(=2)
        , unsigned int AllocationDisableMask BOOST_CONTAINER_DOCONLY(=0)>
class allocator
{
   typedef unsigned int allocation_type;
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   //Self type
   typedef allocator<T, Version, AllocationDisableMask>   self_t;

   //Not assignable from related allocator
   template<class T2, unsigned int Version2, unsigned int AllocationDisableMask2>
   allocator& operator=(const allocator<T2, Version2, AllocationDisableMask2>&);

   static const unsigned int ForbiddenMask =
      BOOST_CONTAINER_ALLOCATE_NEW | BOOST_CONTAINER_EXPAND_BWD | BOOST_CONTAINER_EXPAND_FWD ;

   //The mask can't disable all the allocation types
   BOOST_STATIC_ASSERT((  (AllocationDisableMask & ForbiddenMask) != ForbiddenMask  ));

   //The mask is only valid for version 2 allocators
   BOOST_STATIC_ASSERT((  Version != 1 || (AllocationDisableMask == 0)  ));

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef T &                                  reference;
   typedef const T &                            const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;

   typedef boost::container::dtl::
      version_type<self_t, Version>                version;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef boost::container::dtl::
         basic_multiallocation_chain<void*>        void_multiallocation_chain;

   typedef boost::container::dtl::
      transform_multiallocation_chain
         <void_multiallocation_chain, T>           multiallocation_chain;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //!Obtains an allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef allocator<T2, Version, AllocationDisableMask> other;
   };

   //!Default constructor
   //!Never throws
   allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other allocator.
   //!Never throws
   allocator(const allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from related allocator.
   //!Never throws
   template<class T2>
   allocator(const allocator<T2
            #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
            , Version, AllocationDisableMask
            #endif
            > &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Allocates memory for an array of count elements.
   //!Throws bad_alloc if there is no enough memory
   //!If Version is 2, this allocated memory can only be deallocated
   //!with deallocate() or (for Version == 2) deallocate_many()
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD pointer allocate(size_type count, const void * hint= 0)
   {
      (void)hint;
      if(count > size_type(-1)/(2u*sizeof(T)))
         boost::container::throw_bad_alloc();
      void *ret = dlmalloc_malloc(count*sizeof(T));
      if(!ret)
         boost::container::throw_bad_alloc();
      return static_cast<pointer>(ret);
   }

   //!Deallocates previously allocated memory.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE void deallocate(pointer ptr, size_type) BOOST_NOEXCEPT_OR_NOTHROW
   {  dlmalloc_free(ptr);  }

   //!Returns the maximum number of elements that could be allocated.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return size_type(-1)/(2u*sizeof(T));   }

   //!Swaps two allocators, does nothing
   //!because this allocator is stateless
   BOOST_CONTAINER_FORCEINLINE friend void swap(self_t &, self_t &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD
      friend bool operator==(const allocator &, const allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator!=(const allocator &, const allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   //!An advanced function that offers in-place expansion shrink to fit and new allocation
   //!capabilities. Memory allocated with this function can only be deallocated with deallocate()
   //!or deallocate_many().
   //!This function is available only with Version == 2
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD pointer allocation_command(allocation_type command,
                         size_type limit_size,
                         size_type &prefer_in_recvd_out_size,
                         pointer &reuse)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      const allocation_type mask(AllocationDisableMask);
      command &= ~mask;
      pointer ret = this->priv_allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);
      if(!ret && !(command & BOOST_CONTAINER_NOTHROW_ALLOCATION))
         boost::container::throw_bad_alloc();
      return ret;
   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   //!Memory must not have been allocated with
   //!allocate_one or allocate_individual.
   //!This function is available only with Version == 2
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return dlmalloc_size(p);
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   //!This function is available only with Version == 2
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE pointer allocate_one()
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->allocate(1);
   }

   //!Allocates many elements of size == 1.
   //!Elements must be individually deallocated with deallocate_one()
   //!This function is available only with Version == 2
   BOOST_CONTAINER_FORCEINLINE void allocate_individual(std::size_t num_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      this->allocate_many(1, num_elements, chain);
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one() or allocate_individual.
   //Never throws
   void deallocate_one(pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->deallocate(p, 1);
   }

   //!Deallocates memory allocated with allocate_one() or allocate_individual().
   //!This function is available only with Version == 2
   BOOST_CONTAINER_FORCEINLINE
      void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->deallocate_many(chain);
   }

   //!Allocates many elements of size elem_size.
   //!Elements must be individually deallocated with deallocate()
   //!This function is available only with Version == 2
   void allocate_many(size_type elem_size, std::size_t n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      if(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch)){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );
/*
      if(!dlmalloc_multialloc_nodes( n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
                                   , move_detail::force_ptr<dlmalloc_memchain *>(&chain))){
         boost::container::throw_bad_alloc();
      }*/
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   //!This function is available only with Version == 2
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      if(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch)){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );
      /*
      if(!dlmalloc_multialloc_arrays( n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS
                                    , move_detail::force_ptr<dlmalloc_memchain *>(&chain))){
         boost::container::throw_bad_alloc();
      }*/
   }

   //!Deallocates several elements allocated by
   //!allocate_many(), allocate(), or allocation_command().
   //!This function is available only with Version == 2
   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      void *beg(&*chain.begin()), *last(&*chain.last());
      size_t size(chain.size());
      BOOST_CONTAINER_MEMCHAIN_INIT_FROM(&ch, beg, last, size);
      dlmalloc_multidealloc(&ch);
      //dlmalloc_multidealloc(move_detail::force_ptr<dlmalloc_memchain *>(&chain));
   }

   private:

   pointer priv_allocation_command
      (allocation_type command,    std::size_t limit_size
      ,size_type &prefer_in_recvd_out_size
      ,pointer &reuse_ptr)
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

#endif   //BOOST_CONTAINER_ALLOCATOR_HPP


/* allocator.hpp
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
*/