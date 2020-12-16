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
   //!Throws std::bad_alloc if there is no enough memory
   //!If Version is 2, this allocated memory can only be deallocated
   //!with deallocate() or (for Version == 2) deallocate_many()
   pointer allocate(size_type count, const void * hint= 0)
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
   friend bool operator==(const allocator &, const allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const allocator &, const allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   //!An advanced function that offers in-place expansion shrink to fit and new allocation
   //!capabilities. Memory allocated with this function can only be deallocated with deallocate()
   //!or deallocate_many().
   //!This function is available only with Version == 2
   pointer allocation_command(allocation_type command,
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
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return dlmalloc_size(p);
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   //!This function is available only with Version == 2
   BOOST_CONTAINER_FORCEINLINE pointer allocate_one()
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
   BOOST_CONTAINER_FORCEINLINE void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
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
      if(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch)){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );
/*
      if(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain))){
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
      if(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch)){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );
      /*
      if(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain))){
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
      //dlmalloc_multidealloc(reinterpret_cast<dlmalloc_memchain *>(&chain));
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
NWHtDjI3mow7fy/bZDKvwvwKCyosrLCowmC2sTnj7MLANe24PrSCwvqN21KdzBcXl/5+4yNkAYWFFBZRWExhjoCxuRTmibOaD82fcX1osvbUea2H8RzFxT3qf+sxz5HCogqDOcbmVJhbYV6F+ePsr5Klkrg+NFn74W+mz+Y5iovLvz48n+dIYY65xuZSmEdhPoUFFBZCmyus86T3anGb82zQW9gee8o1rg8th7DeFYvU5Prm41qssB/ebbiSDBbYYLCwfo1XHeY80a5I6/K0Hue5MG0Nx44eK8DzgPahSbd2y/de4rldjJ/TwtrWiiVw3Ofa/lMz3n+ixRTmWGJsLoV5DA3Ah/a5Zivxha+v3X5N5lpqA4+w3TuDZ8iCaOmE8X1j8C8UF9dqXI9nZM5lNkgVdrZzPbYIWiBRt1xbRmQk83xhg4ki7u7IbP8hgy9t8Iew+lOS+3INq2xQQVivq4WukfnR3jbp1sB8shBZdHXauActWi7kNtfY4LywNTWvziNzr8W1LmGNF7VvQOZFyy1MrkMH0Mok6Jatz7PqXPt6/VgqiC/83HaTvp6MNtykW/E5333B/W3A7xhEXM4Krx+TOTbaoLuw9uuqLOBc0D4U1i5d7v5k8A1+n5qg24WW39vfGD57JqR/p/gFfo8+tNrPy8gCW22QKUm3JwX27iML7rRBSdBtVJlsuciicXY4x4laZM5daW3A4+bdyLxoBYQFKzXszrmgPRX2LLXgcbLIbnyvCOP3ClpMYY49xuZSmEdhPkNL7hVAu6bZl/i8rOHni64iC+3F60OE3fnzj35k/n02qCXs0uZ1ncmiaD2EfVL5WDoy73c2SDbpVneydTKZ64ANlgnr0D46nsx90Aa1QbcfM2UoTBZESxLG5zJoIbTMwgZd6TePLIyWU1jO4mX/yzUoDL7Ha4aE7bhxaDhZBC2rMDnWMYU5fjA2l8I8CvMpLKCwkKHhfV/RCiS+sVX/v36i6tyyZOHDuM6eoFu2aQtLknmP2aAD6PZONUcXbhPtvDBn/62dyaLHtesnNGuZ6dASMt9J7XxTM+/Lx9PJnD/jd7vCYt/kCJN5Ttmgr2izTa2cf3LcaRvMFHGVP87an/NEyypMjktMYY4zxuZSmEdhPoUFFBYytu4RtMrauKzGa2pO71p7jMz7iw16gW7POv05gywaZ9VORJZy3DnsT5jsz4/WTNjj7McycJtoG4S93W1PK7LweeM2o2j9hf1Ya/dRMt8FG6QXhr8tY/OjGbUZRHOIcVndKPqQDC4ZxzkNrVdPN1pRzdbgPNSq3KInmR+tvLCJL1+MJIsozHnZ2HxoRv2FFHFwxdg8CgsqLIZmlIvrV+M4v8IiCnNeVYwLmuG4KOLgmmJcFBZEM+ovqohz/aYYF4VFFOaMGufijRrHhRQG1xXjorAgWj1hhX9MqUEGN4zNi9ZB2INWBfZy7Yo4101jCygshmbUn/eWcVxYYc7bxuZXWBTNKBfPHeO4kMIcvxubT2ERhbnuKsZaYbG7irG+pxhrhTnvK8Yazai/mCLO80Ax1gpzPFSMNZpRLlFFnPsPYwsqDB4Zm1dhYbRRwiYtHnmK4x4bG8SMDK8tRKuj2Vq8Zk9f38X/PLHBVs3W4fU2d7JeSiWLog1Op9uNhSv6k4X+sUGNBN3Kng2kJ/P/q51PaybPp0NoWdnirl9SWExhjv8am0thHrRDmn2FL1Tb/s3fbC9t8FjYh/UrWrm+VzYokaTb2oSex8nCiXZ4btLtvWMFDpG509uhlLBnvy+oynEZ7JBB2ItBtRdxfZnscC5Bt0OBbc/JghY7XBd2yrfgIffnsMNU0C191pTKPJ5oe4S95Z81gec=
*/