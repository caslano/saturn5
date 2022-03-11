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
yzxn+ENik+05854TqfiuRHYwmGRQS2C/Pd6JmjP5pi1m2IAj9ar2ryuFVHYdqZo17AqI8Ubwum3LBg7NYfaOe6T6kTBqOWwzVPYc5axVb3jEJCN6eRvWDW+X7IjicRSlvTIZG4NFmFrEExV46nATy3VFu5iypKU9VR1lWtCu1tymNX3fhnpZgv2mYhW5nrd12UKpV+G1teee8V6Et0BfyfBdjFgQ77h4zr6vM3zGxHdjmZTslhAsmUvP64kOPw/DWnPnQISRNxDTZajwlx+B5t2HIvTcviOG7f6SY4trDXtqXx48gUdOBqMWIh7/HQz8MNgaM931G8On5ICeDYXkF9fshDm9XyYjJ99gDkhWRZy8AQGP4yDpdrkzYWXqZzB9VtQQfawDpTzdDPIFDw1JDiZaF42AEwhF1Y6vEW6vhRjOSv6LOFuThLv3TpW9MgsDl2b1HqAD360UmldJ7U/BJW9gA0zpZymNffozRoDHxflJFnx9VQ/oTIzwFOMMHqTsnzFTKRDrle2aV2LCFic8q9yQCPgvEZ2rlwOImSuLh06IxlZpZ3Qonq1tWdD1NBicV/svBzbqs3gUHGXLqBZ4XKDwvMnVux9q+E8Qwg8k4Tey0Cd50JscxH0uwgE/4ZCfUNj/LYMfhvD7B0ANF3kPjf+/P1xcbb3yL0f/jN47cThfOeE4x3jEyI4QYproJhcaTE7Rje7Ey4yXGYUM1g/WixvPOh2NUWQWzREpiCdorCTPLsfu9u5/+H6hxm5euvbyAgZBEIgAEAJBIAqEAQiBIBD9Rfj/TPIn/d/L/I9Jbz/YhAHf3CzM9Iu7AFHB37tyBjhXSTu7AF0ZBPaDbYLIL6YEqD6cCuqt5dYUwhNVI7Zl5d4kWt92ABkGhjR3cCRbBKmb6vGmNJ1hupO7AFN966G5WljSjBTL1HNW1ekehstX//qdBl269oTMCsJ8ta61Gz+cYdEDu4rSL5pZtPN2v5+AWZ+U36bmnlYnR+78chvraE2Rzgx+QPfMxQuVgmfDkSOR2lssDOt4l8Tt5F+ODci8JIOC84HFd6PojWc23mRrmXMWtf61Mi0xxjfQQzBmWa9cGTi141K6qMH8gImZK6tjxy58D73LUyzkdVq9es3dpm2TxJhHqz0fVI+i57smmbCU/8Q3tOJ6aomjSGfzaqK+3zv/aMUWYkPE/gxkWaSDmc5JU0L9U0t/WDoS+oiC6ESbpoCQAeGeGKx8hSXL3I0+W1U/Uz1CJHxqICmvJ8JW5FTnrCcKeNuY9cgg13ldC1RRq0hRlNY0CyqgaPqrm5ytWnypvqCLg0a0GoAQi8CVwD4SEzMc0bG/2gLN8mKReqquwj2Xlpb+pi5PVq9imZDcvI9yglfpppxBXZ/J+d6PIeWMNJpsVsunN1WrGjKMzB0tfui6NpB+C0um1mbZDj1SQF8ebSMlUFBwOwXO5O8wnK8QsBoUEb4APkjoe1hBsQ79Dajo27w8OijVTGvH02u1U/VxfD5Zq5KOtqwQrFV2iX6naeX97wKqUxvzCUoi43ZrxKqQcdHE9ZZwtRdCQRl/KOBvSX1Dmk1DTNa0Xs7HfPPKi8/2N7KC0TaQan3vNzvAJS0b8vPxFMu3DHJlO+PuSyM6lQa13d1tG5i2pMipCVU6f9UUshf3g02TZuLWxgm081aGw2492hCU1+2h0AEAfgjfzcRH1yw+W+ZZN2/Je4yT8acP/+IiXrxSXHyCns5+Ih+rl8+AMWsyPvfiKiIKkhTtZbBJ+q37ewo09TSwBySYhfXCzdDHZ4ZTatI26yHJUoSHrVqx3GGuJvrnO8J780xTy/0/hx+qmN2S4umU2tUCmcb8C06Uhm2iWFqSmwKGOKHIUr3Uxi3Fl9RB4ZHV9Wer43DtHnPwZyX5CDt8RTJJ2WwFBUq3Nk10N8YsBU7GnefuL1HJVapnXLchrq9r/OfnkkTkUGzhUhb4Vl282t1td4e3pI716Dbn/dWyb0Ybo4sVcpmk6Hr3Jb7FwwIz8KiFcP7QS3rPHFxGqkj8upQl8e0f17cvszdGijtgbtvA6MiqYRymP6e84qWNVLZboZCvjGZyYozxduJE3Xb1dC2H8J/kxOgZ0K1xFRcwiKZ1xlK1YX9jUuThrvbbaP019CIiyhjIcto7x0x0QNFoMMmpvClPOMmcn/I7sMIeTobrlrr5rk5DOICriK8UVHKfoGj2qaYR52Fw+/YlwlVpY8g/Kmq8pe4i7X2+7t1kjptVUt8ZajuLe3dnXf3oQ0tBHNFsLKZ1tcz68Lev6VEz5+bTMB6fiLGSwnOrUnoL2kQlpb4VwaHihfpY07tb9Q4s8VY6HOmM5Tkmi2XNqc5ObOL9ljAWNRcMF6pJp9P6gBVtPzpWT2//bojL5TpIYvR41LkUnlC02l021sDOP/Wq0qoNzZLuOuaB96Qt8yRiltgVakveYFbLowliBLk8TDQlTqAquozeVGUk0M8LVsWD2EKDB7XN4UVqJoyWzX66GiAUFpCLX7oP8CswuoE5akqu03MOZeoS9OJHJ4rHhq5bo1+RqumUU6cT8FBTfzspl5c4MjzdnTfdFVO4LUqsPYsHSxrfB1DxSuFwMjZoZAm59ZYg2V5MTI7SgDzMNRpLonjpKbCEyMpHZmU4y64rprBWMT6H7es3LBgjV+Tgn37wZE8tPbQtCyQ8HyYpnOR4oH1TKaMX822jpNPVLPJ6tkivTlnw1m3cziNnE4tYnH4zYH3YNd10Aus0p1N/Smrv3ge23ZNPSMEOoKs2664XhR/ThFNsSGWF93XjtowjzcqOtCtXDSyEMjsit8lyExG7n1PKoE6bNMiiRc8T5k1FvFWaJWG5nBrFYjdcUGgrXpBL70bjbLljcTCg/LXKEKnMaFUydimGfdxtht0l2EWsGBa1LXGupWjxKSzWbZ7v1c1oW+6Zu77W3DaVgbWk/mCou7i32PEcNu8QXJuLnqKuYa/C0VY5aqy5U+HXqTLoHEyt5JtQnIvJeD55UD+JpS4gvnXb6UITCyi6h8O7rfYDZekPsLxPPaUxjPzAjrewAiQnK+V3vH0mh17NjHUoamW65m2lW71nWmr1I7j5dDdy+1rYMuA6TFdJHGgeYWG8DB4WPD14r+xRNGixt0haiHRIIdtcCXPmz3wcLD6hSXcopGu6gMswrcm6LSVnH2ecCUyC3s2ucZviyWnlSiHY7hSe+QQ3FtQS8tyGHvv+6lHiIRClavYi/g5F539As3RnkR8wd3u6bP6sRoQlBx2UeJ9iuVcb4QeylpXaMbJMsKGYN5kVOG+2K5FaRCZ8CR+C6UymZ5+0LNBapdZ4ijJCPdVz40mmVZKaMKY4XerMiSdkxlCqHnKy0wPLrcT0sLWbRr4H+zilyiGP3beWyi4wbVavWu4JPnMr0Pfb0rqEXb2155itxmh2+2f8DVGA5yu/qJjvw9rFOyf01cZeY/hTfGN2ZBB0dct//YQc/xkfVgh6RsrLZegdOMZT15e9MW+33hR/pwdgWKgCrjLCfjhtIWWeIzsoQQ6u+D2PPnbfc1F33PZTeFJosrNLxgcntvlHN9lsVi7oubOoDA2HT1d5HzM9LPGROsv9SebUbMxY+0R2ONGNpFD52dZPqAob23XEWag7UeFQCX2e13DHV37J6GmSLs9r2ofI/GV8cButYuxvZgSra6Vchd0DD1nvpEjpVZJ5dFcnRW5C780R+p+D+eDoTcLQRzOwbi6x9NnaBuZwmJpByz8i+adzGM1PfU2TCzO2wYMOGfiQCuKNKvyCbFzQN/3c0Wjae3r5wNoT0HfhSvBsA3aCx58QSbBYk2z0lKR/6U/q9M4WuJD34zdH4FYZT1mpx3yd96YpbwBuDRBPLgSTeUzhwtyGAZMZ3KryVehezGaBthlSQ3/C9m8+kCq7Ks3zvh0Q+dAtzTFWiK/KpGutxVXCwlT73iUIYwuDr6ftC94ksmnDe9qYxRMswffKMFo7O67zLbt1YxaFPMj7qhKl/WPGmKF5fpD0u0vqQjOJSBDaJhCLJPdUGcVu3wKPKcxVkJvBr3nA1uvUgdzunfA4wW0xmddSJxa7VNNQjWyJ8B4tlQ7M43mB4RAzjigHgxrlhqlMCJBYhE0pkBbXzU92wnQC7BdLICbNbvDhCDSJ3V0ImXS1NeHABG0ltnYOxWwQ/zkDbfVAzaPE86UwcC12Ixh3KeTmUekiCkUs25Ko7uxbJ0bJcc7Ek2rer6YMIRf2l+dDWiiCmU3yFgtIkvw7wzEuoLIL6OklEYsf1WWqFxMvgoG8fZsmBEi5txHD/RfMAymD5Z0M8Yj+KSKhbjBPLiroWkBoZihUeZio2yMiRkBYL+n6qmyQyobiIUXyZhQ3B2odQMw+LOds/jI/qzYud0AjynbDKuLfa2ykPl9q1F9RpL8c60WJnxbAUdD/MXLGQk7CAtZdTEshhB6quBYOAc+ToRQQTizMBFth2s+G8g6U8a4Y+sWDFF8s0IEPsCs0QNlNKQWirmzN4xYgqZt7RUwtJW3L0aIkk4VIrkJL6U90LFs6eVQySsh8VL0ox7jgFDPNVFTBPBNikgU9ac/A6TcDQlqXNBAO7lFcz7mYjj+o/s1IDK0d44dA5T2BlT8Vhh2fUC/7dz2k/0oh3hKEyZg5ETT3eCil3IdIqpJr0YciUh73nCnVhDzbR4l9U4lLyp4NGD2lnCUJdmci7GyqbWxsxPJUQtVsN3EmXHas/Ta+0LKazA7X3jFXxLQt7XncpZHE1PWkYQB/KIPy+dHzh9Ps0Z1CzRZd48LRKOBZ9Zxz96EuSPI8UaRAySBlm2pFqWM5UWsg2IKzlo+9SSHjJ+Sv2mdef0S9Q2wuuma/r0k/uHb8ZiH2VuRBpYH7XzfG3X+y/JdH1Z0XXIhBGVCRmXxi93QvXp/ns4V3/2pAPXOB0e0PePmqUN7o0OmYgFIw6pI5YyvSL91Fcyl9gwbOu05w3bsGoh1MukEviV5f9KsOPaqg+y9CvuWaalsaWLF3LKnz4/7tkSj3+zZuWDRFOVLDOdcjk0mw1Ds7qGh3YWJY961YBRZ59ZhQGkBxjQazZ0MWnEkl3WmBJssovn3a8FOd8hM81JihLapJijxdoT7DmE1mW7FF7HXzaaDO2H1ILTdL2ePZL9d8liyWug1EmPBC38zYk1Eiy5LtcPXbfj+za8vnvS02pKu84cr2ozwdVDNa0J91PZZoamyz8raJHEOCNlZyYHzQvX57dOeEAK0x9kfzV151eZJ2NGhb5AIk2k/5GglJOPs8boSwr41f5jUcGVAw3qec89TiWJEW91Lp8J4ReaXz9Mto1S4thKwK1QrZ88n1rFKFNHeMdVXIbsd6x1WzqODtqGiQAfjRqD86aqQe7LEpmB5hawcCZrJ4uZ8FrdbDLT2d/AObLg3/OugpVYvoJsxL1HA2G/42xn5DjRFIq/0o1I6E3aemof96iqOf6I0xSLxFO1rpV/W7d8tuD/Chqikr7qWzWL8imGVtqDwTFUp2VKWVoDCfHHkA21n6sz4fzQ+1sdaXrqcmToNBwkZgHJDGAsKBl3K0gSJx+KTMNL1SlclUjS06+NYcA58FAs9Awwwimq/5Jz2RDckFbpCNniWSXqSpbj/TpYy2QmsaLJSWeZh2BKt6PJL2BLHaIE2V2tKKIH/5pm658vdMXjjtUr/MWTCNuHgia9NI1OSB35KO3vrPoumSvgVUrMnKaEO4/Foz6KUz9Po0crOQhesIO5C2mfsAHpG+kTvBhpsuxI0H6YJncS3edpPyzxlBp8sJ5H1CeXawLokgsmj1brYJln0ZWTtPL3VXWpLBgrbTWrIXahGfaEVrcQM7Var3rWXjdUXUWAGeosYnIkswHVfyRpngdWtxM5lC+p+m/cGaG7emYOANYEys+qSJpcnvfZunfPxHXhvUEiNkA4fERvpP4yjpdr5zt1eQeX0YrEkyN/3itR5giSYSVVrNAEbMg5RvmB1swxhEziLub+s4Irv+R73wF7aCvuZZd3BzagzuUpC4NbzOLFOQRhZvpyKH/T80mRUMnoxSVnQAwsQy+8Pue22ruwj9HgzqXG6WMNbvoLiIS6xMm8+6utIi0Ct16TTKMuxWouMkgyfibT3e3bNmq4/G8U9wE/HAt+cw/tM9KLjYkM70/fb+4bMkBnUseKhcaiEtd3L2bEPGex3Wu/SntjnEHcOIq0fKd+5IlmZK9d9+Ltsq8jjSm3kGWQb2bqF7CXv9gbA3SFvbv4G3rbOzEwySydzeDR7QdPf1w/Jno3qD93rxxrPiY69nIy7IOi7uJufk2pQiiEogC2q6B3BQHT2wNRSHYfYZCssu6ETgL8dgylU+9rcgNRXJafYowT8hzdB9Ym4ctW0OTUBh8oqhlxDppDXhlEePhS3Ve6GWTraQKzd/fNnoVgQyJAyeG0kpR1FB03WBF+ZxYn4kYVuIad0hp1ifOYEq/EKziaLQOVwYYIYSD17//WIS3+ioFTMyzvUzyPnnI58PkN2oe6iCTgRAIB8d+DOGDhEeRLC/OZEMe5HjsFoBtLvl34GALmsk6IltiJuIrrOI84D6OciMm3yaVMm1ZGi5PVScdwENgMDnzYbaLuYdpSaSqjQhaQMqVYF3RHGtAkmLWhM/1YDZXUDVwbZbwelKLHGsoxDBV5FIvgf2SXRftad3SKRAACQcWTAujKGO9YLG90iN/DDAM2KRhlkBvOLKjxEWMfCdq/2WsvOJ0nu0yrbDw1GAxMNA0+YYh5tUh+bATUNeuOnmBQRE9zeAyS6LYYNY8UsmraQIrYMYhyuQRjzxUHFl97DlRSA5eQkA8NSm4zzGVZqp0OSVjR/MzOIPEbeqNkYzY8hQbRlQ1mSwcPfAwoSHqVt1Imh9t+iwXw+MoKCvZJv/ZOGHTc0OGs4cTrpqLVJHJfzIKNYAvx/Ua+4iyyMG/4WAFLUSt9mTdJJtMOytx2GKoLoGub49tJPTlczCjQrQIcjYNc45KRUgepYZmp6IX82+dvmRZUZh/MP+UW1eSWERSemiTTRG4j93H+YXx5QxdbU6MK7szkbAB66kcnipVUhCHXzQsHkK3rFj45W7kImSidrl3/nrJb907Ns7yuRLzp3P0QfimGSkzY3E6S08ilDu2bxpAc7cIil4KFAuXEeGIMorKB8unlvOLDqPnzRvH+XmVgxphW7E+idMk+gYGivfTmQs9TQf3glDxOrFUe51S2YOTb3syUw+dm3+VmSsng+lzfQFX+7Vv7OPlTvgGlfZlikH715lPRcc2lsjTNZ/Dr+vPjP4Q0CdVbxhuk8l4Zz0+joQBkzatKmORLgs1oNlSHcgIRIAAYXLdRfRWBor0D67mjHbD1sYHZZ52dwWbmH/OkfahcPn831ISMQ1g8Y5o8Iv48YvYwEc7l6uefE02GpoioSbGomLWPFvBPrAEHPQSL49udBw6KZC5buHKSP25pxbyqSHbq7bSkv0eqLzzpmfrIfDzte+UqnfjogrY4jrfKbbfKHf/LEf45cDo4vLfK/PfeMZTJWfpkprp79ryx/XDlHXZmLnZGnXmNZC1wM/lxQ3l3k3F1N4mSDAwr+A1KUgSonurhZ+jKlurlexTS8OkC4+kIOuoNXuwJG+zeZ+6wtuKgUsqwzOwVj2AXxugWgCAQb20JVdIYOukat+m10OXkKuUjl+kfxuUk4+VtviItTe7Ou+o/J+Uun2k0B/2gbJen9IvGd53UbT/Jgdh3kafWKt7SkHXBlr7Tm7fMhY3OCJ/OIkOdBv/BDQe5JMveQDeCiW+CniSuGjb1TOFc+F3Xte+S7y+BmZ+DmrGDOW+TU/fVnEwTdX+NcT+TlneLmwSTiP+dup+byE8GgfR7tQcufYP3qwvkxtQUb1uMrZnEhYYHRcpRJrGOEvr+J2+T4EVR2iZQaDQ5nmwRtP3xqAvo+mvyjbyGZC39CgHj/lvWkd3asl3WnRdmoyvWwkJNC1fWwY7elYCWyR+W7P/K6Rvi8DvhPoPpNcvziAPCRl3B+r/bDZ3XN6fDOv/XTbfHOMvFoF/fSm/SR1uWlDIZpDbXq1Pn12EW03J83QXKtgT97D7A43jFdTWfXJFhV4Mhvf0IK1xycC0NsynETtI2MAM6NFBi/bgFEjgv4BqmftokYOFalQzGuuJYaRHjXwA9BfSZEqSg4teuvxxMmayNcy62jxJM0JCStOFOUJwE7ufcy4171MyrOYo4FKfGxIqyHCORqxaulxqVTL06lQLOvyKcV+SX82jkB3ajY39XHrHhyjP3o3Lg8sbr5PFMuGLu7PKmYvd6BC6XR2o61zR9x6rEye38Wq7dkuVei/sBM3be4GAgXJFXdYuZkya2jDQShkPGfwM4ru7jsl265kBq3/+c5Y94tX7n2ZTSLxcQhUt3Xt0MG3seGJnHXg2zw89+6ep4PLIMXNebXVlA77yBqr/nm6cq1fubDv+hpWapytTlBX34ktAGIlylvw2vRIo6WBXO3e2nsN3dVy4+cynph/faLDe2EwwqjEbq5Uvo7FvPJkuvfYxFapOGQnWAwcKNWJT6qo8QnGCBV4uBYsm/0bbY4GsOHbWAiSE3N5fcZdamcCLotkjZoN3Xk8u4JpKzdU8kyMT46gAlMawTCRZ7mEAVf1F5aG8oXBnmH8p8TBndF3XCOluTPU4UrsDFUnKC2pSDCoamGpA1T8BbuwTSpPwOWfktxkd0DfF6gAHV9iiS5dG9hHyhIoDlHiy/oISoA0sFmCkpYw4c+kqGhIeXIibHKP/0Gi6mgeTfJkWpT1sGdLQ9ASY/qETziKDRZA6PkjbAvNwVF68TsH4sQCFNrmYWEJYbW7f4XQGLQZYkWLToFm/EenRm1PJKMAycbaFXqjRyOPmUFVyPafIFATLC1CD8SLxAAFLPrTmstaDe7qsTeOvzdSXJRGZibpnwNgwZpz25720JPr6oxfc1SkXWsfPLXYLSGnNyh/CUDERA8bvRzsE8I/hMKd7DeKkG/iTm6VCDdbIkjglZMKCCbO2r7S7qOlC6UTnfnE0ui1pDQjvGdYce8TJ0vDBqJTvVnjOSh2W6EFIPRvQHaX9Eo8Ts53VlQqRBBujA6z4KWLvbftLMG/Rx04giEBNaCgABtyj0plW9g1ZbQrFn2uOoVgcil53TMSROc7UWVtshTvvGVUSK58qUQP3xY=
*/