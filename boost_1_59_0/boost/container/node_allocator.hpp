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
      version_type<self_t, (unsigned int) Version>             version;

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
   //!Throws bad_alloc if there is no enough memory
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
      if(BOOST_UNLIKELY(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch))){
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
      dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), BOOST_CONTAINER_DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch);
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
AupNU4YNvRrum8lhh+eWoIyas+wNTUJ2n0B3cR44bleLez4fNLolvdtV9vzRuAD0WDeWHOmu8oipgd/fxeEpVuP/LChI7cmg0gKwmDwef6WRT/FkxS34h4cJ92IVXRF95Pm+/Vkce99d3K6sQ78CMkPJPguOftWR3ftx96eqGSvv1n5Uij9778fC/zmPhcrvcrjohQdCZjx3ZrKHI3Fjuft/a/8q/Tdc+6lW1+XqnviQuHcrxXA6l4G0jGL2nStctZBG09Ga583l52ttds+TW/zAr3UO9dUy6kLaoPti9Rjzrmi/et5amLX7TV9589iz7qTb9g0f9AOtv9m9UobKPVcI5ZtrqAnz4T0Eho5kY0n0+WlHL49FJLmK+nFrXzc79hS1+8RrANjOc2fQugiHzc6gPgP2cfHE28T8H9ic2RVLCsy0TQsfBN4YBpJV7chto3x49poBMRLVRBfRseWoSSqRmnmfDakxJeVSIvhtY0SCTjvclUxO/8ZqhT24yqielW0Qjl4KyWwa8ZHjfxNh1SoHDHiSWzG2Q5AyZIqlfILcgqVss5fv6nFP6NyTmVRLVwuuP5p1+lU0bucYxDi8k6I24PNdnmaE4O+ca0m3s6RXcMjaHaNqhqWFCslRceX+7Z+CJU18fOz0aKDYwUdDbkt39zTrZhWEqVRn7jgiVo4o+d7VxNVoC/9drQfIiuNAee8G+vdYE1v6rwawivR6r/K2fVWdG3fBVRdk0R7rTiEIivouom8l618TrHRyDR/J9x62DrCH577hIIGKT4opRKgfKsCJCR/Nbatdca+sufi0Un5B5VIB7OCako0jAQQgHfUAJhBFEMQLrEUxEyBCq/QnlK3kKrokr4RIoKpsxOCQkIvN0PkMay3n+SbaYBKCNa6YCCSoKJ6DDGm8QoyTpFs++ohRWr0gs1qHMAJIeZZcPkkKfrgnlJ64UtChbF4y7ASM9Iv897CSc7pbHyP/XCZtvG5QrBPJgT5FZWsSDJO5fA2i2TnJl8ZfrlVu5LiHuqYMfObNDCjMN4JByWti/jK4awqyb86g63N73rZsUFY8tc1zbtOj3n71/DOuMfhukAW2xD9he+Td+p9jTrceEF5uneeq+LUrOt1EQlWiopiNFRkeJUlcB7PJWHPMgcKivryRarTvcAdGD4VL31TY0plGvRgFDy6ejPKHINCMAfvWINC/sK/MdSkT8zw+ph70CTzlzj7ohtZm/bGFxoFSY4vkdMv6n6ILLLscx5lBudHyQVzAAKf48l6C2HS15gBLr90rfBfn5o+qozMURzHevVg6g3Ze8neNBXIKV257HnO1OIcUdhLzkf47GhCxPQ+kX6yMAuS/Qoj1A4dB2xs5HJZgWGgmqAJUL3LH0KbUPEyp8ymXFIkYoZEYuHhoJlKFdDceiwfTkaK1xtTrqe/Gyjijud1YYGMtgiML7S+5LG0mQVmbqXmvomJWuUUWQd7T6tSPXB2rVYzijQmaXlArGb5AEsO4tik8mGyP2Hxp1h/134DKwodsYXDm60OwCQ+Dt6yk9lFZOW6ZuvHLVbcJhhLL4A/qip+65zruyAIewFzAwaPEzAXGa9r+Xu7VA3KKBMUC+IPklK9S7we72utmACxE8AOnPcCBPM4+JRKz0H5ZBV+DjWOJOgaT0ytJds0CQJsKhcghVwbg5MBCHcLcJwdkSQpegm9sJZoZ70CikLXWObNB5ORuV6CF90639KJuGJrTF0KiM9U/yrKHJcuN6Ce17AbK1zGltOLi/TEa976oV8xTow6U4XY0qIKDSB4WDy9NRA0tHaWtsoADYFUi1s9CSGaJh7bQua2ZnQ0ianlDyhyyYy36RGfmFsAjVmCWNRcWa+y0hjDaYqi+zeXkAPQVCaZxS+RskNHu+H0b0b2V4sNBQFrKJyZhBOVc043qN8sNYzjRK9RE4Cez3jzpIQCXfoAx5EUp6O+hWynEoqmIEEbakQOI5OFA5q4w14XwACNsxyC06sg3BQ7Hf8bUdH0BDWdV/QcS37sviEOZwE6BRNR3Im5YLI54LxLxomZB0XWTxg3Pa7k4vqhTpM8o6LaMOxSzl8ExT+BkvARcZvxle14z8AlivV7sGmXe/6jyRgZIRzO3GBogt4VytkNITCOHO1swN/KtVTaE0ZGAIbQDcZgeOfT5PtfZnZPFr5O6mXuBEtziIjUV1Z6CTL5pyF2fa57XKHYu4BERObKq9K37rek5vifayC4w6TVH2ZBEmDJxb3b/QbkLCgKZZRkDn52XWzYKkUDijPqfikB5eYVQWDfwWVN6NhnCsg4lAhaBXp2TOlabLCBct9/0v/Sl2mMYv8Fcjzc1Ql2wI/yHTQDehIGW/+G4oOFr11NggILWarWDuDvI1xuScs6M82qKKcJcEUkGGm2xnZCv2ntm32XrVaVcaTNs68QKk6mSk1Ao3avJN8wwp+InqQAOOKT0GJVTRp8ta7tWRLvDP4BwQwvWTudjxBLMLw/jYzISZZ16F9tiqJbkn+4e9BRH17Kim9NVz6kmLkPCNMEm6ubvzBRjkX6/tavrxL8hrK+nRyMtWpaTApz6iq62L6iUjKUKSg1ndifXQulTJ7kL6bWZ9AAL5tfRCOjrcvok1sfXanHg8hmuAzGTcjlg5iMdFYzFIVqriausyz3d4jEzWHX7Xxwt7r2KZkjCcrmS73AaRH5AN4S6USHstKIEXLfpOZJJMShay1WcD9362A4pAOZ76bR8tsYscvixKZR7NCysfmPSeTqoCNhkErczEVLjClF8hYUe2XlAIHtYQ10QQ8Knr07OHf379MDyoEy40yA79C645QVGlJ8i9q4PtcXXptGOuwnXYtOTK237dqTlg+1F+HKPeBov9etYATP+Cl0Z/ae9/tcEUfpeV+Eo98EWQBH0owmfXkWaBB8Ky1N8Ii+EDrr0hhzF6vPs9AkZunolwvKWU2xMBAJ6Mt7ioW05gJAfZl5bIcZmWkK2Th+AWlggsFze7RCcz8rs5NrP+lIA5aI2ALd8il4x/kQMBPrrT8x7Y805no9a5ooxY9OXpoiIGx1a5CnDTmHP/TXaFLrn4M43Iswg6kAEH0OS+vJEuZfo4dYNpoG9Wj28uqxGUDbSnvANAR0KKEZwEQGrh1x6OTgPiggYqJu4oHWABhbKf6BQ9pRQasGFGkKKxwXjXQr/YFFYbVmcZVko4TNvqDIJWTIlybD48GZyI05kYsz0hB51C0i35g88LTIcm3HkY4BsYfrUWAZ5TzDJonoxj1SCjCoHNukAEaIBYE0COkk9HIkIglyM1FW2Xl2M+n4xV9uHyd/UWAPayDkaXgygMfPLQGsdYfXafbNV9bJlKeJwbbtV8e47fLu7uGvLYP5pk83Ss8wmku9HigYRywe9Q8ZpqPGEEv5DpkZ+BYcTIR9dNzqQySSMJL2fozk4zESOgHXkRXjLR/qCqjl6+HfETjSh6jnxzDoBqz6Roj5B8F8yFK0Pjky3u2y3PvMwCNqrEFj6GoxndNAJeSlCUb4fNgcdNgcZEYf9d5IZLYQLLCRVVtHbt7Hrt/6OGnCakHHkoiPx/oQpE+UmEyW/sP71aQ/XldeyGeA/Sf8KXrhQLKFANEulmXa59LTE5nJmraUS7ytboj0+xIAaSWNs+c/VUGgIafDjMuSVUST8YkSP4iGTRUcyPSRPEwUSUwXcYmWt0v8sy5j/lSzqlw3RMmvSLHqQMbXDM4FYMe+v7jAV2hCVniilajKt1dN0fNGE3tCU3GpGXNJU2DmN6Iooor5aYgeu4xy4erplpzfzZhJfXYH2MSIWYw4qTxKP7Vt1TryoLZ2yaqcW2cQNOxAkQgFZgm3nNXD6z93PlJWAWRohgqAXdpiZcxa8dxCa8BV1wSCAMDgC15FwrJZTsfPRzFkSpJlRpyGdCESOSxdPzXWXSr2MQ3aP+4bm5S3n6L/lPLD+MM/Se474P0bR7Kr4lkX8pGojZOnrZen7fpe+Z+qk87AvP/iPuiaQaEu7C9rTrqfl1SmTlbP+J4CLwukPLXj/GiS/HToMzClP2CmBQoiiGsG7b5VNoTNJD5SHJrO6gBU775tJrzU62at74JtFLM13iti9+P3yKaII7zc+CrBsZjvwn6lj05h29Ftb+kK+/260NtxObzsd15B5HwfF6PFUn9TC14IuDrqaUGI2+NkEMGlSnn6aQvjp/qsFcq+3dJMOlpQ6FbWulK3GpI3qSbI+V9bvymSNTAD9ZZVm71JoehmNPWhMVp+K/J1sx6FgftjQb7+1bBESZwfUaSVSAuJxiFtonOrIxquT6QeU7oeU3WoU2qnO4Z1U0nGUetZxxDFSdNYkY4tUzR2Rd1Xl/L7TZRaU9hyVPaep+JwU/sdF/VolnUwJob4rRV7hblZU/fHF+8PknrsqVfhyQ95w7qXKSE/FvnoN3MCLCunu0hHIUvHUcinCUndy1YSfsvSw2qdZR6pnPZivhvaKsvTuUCqjhu7PybZsc+mY/8BK0/A20uglwJEoENeX4RIEgEgznIyYxlpluGbpxVLFkEbk092y4RnkALCrvJwkN8Kz8v4zPsTF9tcl/+PynE8lNmzd56R6vLAi/KzFmodyOLXWquNifZ4MR1D573bBqrMyO2ocf9oWBNbeseeGSCxRWtD9XaQmKy16PbyUcgm1t3Gy6eJA/tmJucF8iP1MZJoAKznkqY3dcZ9sXm0HubtHAwMfm1QNg3DGbUM3MoteLyfIMZFRduVJcl9meV5fw/todFKtTjAcaNJEjXFOyVib6QKs4E3EaPeVeBAMaARakDzIdCkRyBuFErLknBRdJyuzYyQOQC11YDEhRjSjG4BVVb11tU7r+r8W9bCGzURthRSAQ0OORDJboqIDtQeki0CkjU3cF3woj8k1ojXDE+FJlSsrQBM7dX5S3MYNrC9tzl6qJdY2oqNd7qWGhfshDXkVTTm8S95X3O8gcCpVdofS/iISBQEBGVGJcvmLRMGoA1Nd1UYABCz7077FcB+dn4J8nIkIeJlrByNGDsefYv9NZ98qqUagMLTfCXTyq0nVENCYx266OW7eanxz5EFfBDk2q21rlP3stJx7vXW3NpPnpx6m9avozYX7pi/p+x6mNcmMMBf6VlufWQFGU78oFOK3vXrPuPAL/MF4kGr8NLV0Qv2uM8P83eD6IZoyfk4mTceffG4l4HHnM2WAqubBYRJfbhlc+SU0LNxSTuyNlfXWWACXgjugNlkQjIQiYjjgxrlqnBgfSkpnCj1ixYDdMK62cyx+dgFfJK8Iehzedd2TUXz33MYqzc/0qP5BBCrE2vpVbAwjkgL4KNGgS0XKNrfbKKDvu4BkvPVB+v0P3O1L5ER+cjDU0rDe9TDU0k5C6Hy/SIEDRFidduNQEYIxXMqS6ECBoP9igJqModC36tUVAVI9N4G/gz5N1/JeWXkqvhgj+QnA9uS6ts/JjWpDZ/KHGRQi4wdwuCvGrgD9EegMB9S06xtsi14btTNvlBQgB/00oMHsAyCGoxDIlOOJiKQ3wMCI8sRlEXfUA0k58DELtI6pm2BRxUBkWTRzsV7UE0zWstgKrnaqmc5HHfkeL7ppHUxtEE8vDBwwifJOFT7udjrB+N4JcyRw7Iay6BgjJsyomgveKb/eb8fT28ozGBVxSwGZuEG48RcOy5oqHJAsEMeswbr/FSX8C+jxr2u9fMBZNOR+QNcByirNzEbxuEhYBMPBIeM8Q8VuxHPuuRY+m2eJlZrk9mGyJuvV/6b4aKZ9DH4Ois1atNYel8awl9kj8qcrDm3WERrL/oCG0N5Blw09vaGa7Zx6K8HN167cgfOOE+X9JYil54MGMLQZKAtJdjTafTOcZIBnUuTeKtvzg8wx3q7zEdadg0pGjVxSoxrDClDCjkZxdS/emJ3D7t1nsgcI/JnVbPj3pji7ty2ZECwoinAXe87yg46+kCZQhb6AZrI1V1s2IOE9RhQGMmu3hTZYSTmIlcy1JsGvjSiWbiC/RFQ0vmPaA7hC5PbeyU2/X8MV5vm06acggP9SFmKSkIgCph9hV76Sfej6lzgIlZHHNN/ABwbszVcUE3y7le4HndSKzSB0BJmz+jDDyrKHzcwAErbqgRSlqB+ryfJYySUbKOz0T8aq/KGGeVo0WAvVUqGODl1N9t6y4HCG6+P4cjCTpAZ8SMW3X+dTeSCzfcmoL0fZt8lstsAZbZRREQLGU6KqMrlyPJsBL9G39p97/BHIYkJ3ACImM3vPoL+4v7IJAO2LO36zuQyMK1fwN1/ZBeuFM+66kZ4SIRl21ZmIpP9Gd98jh7WoRNPWiq4xnXeZ7ucejhMfKumjckVZ+od0wkRQDQxeMB7YGxfRaDsxXwLCTwbcHwFP+IHIHCX5pWnfjsCUJSw2GIiPt3oxe3ZRzd7OM/s+MW7L/Abl21p0T0YM5sJ1b8X5oXP8P6i/nwx2vE+6TpfbzcueGiRoGUSujROG+b5c6OM88UN9m3+7DfO2PPlH3A+2h39gbgXBJgYCXgRrbwOFBgUFDwPf0bw/yYGIOeA25Zx5gQG9zINnRUqIxZMrrv+F6iYnKVQfA3oc0vfS79wCgVkD9WeXUqmXC4sh04s5nkX9/DdLZYIj+gQIsBxFmiCO8CqprZfu67bN6qa/9oXf0APoA/rGhkS5Y1ra2PFojVtYGslhZ0tiCsNjp81zQkOQDxMyTBnhZEY9jEq19F9ABgUbRpPIpj5uYzY7/akURiDxK+c47RoF+9gagjGeNXKXolDZ7FZJQSvNgs/Af2Pg3ttlLbD2Gj/R7NZlFCfMceW+tQdGZsfMfF3MgfHNQfn5UlfO6eVMJe34Mgs3OJmOdLbgyhJVqnRhhPy50Wk50mu6FEbALRL0LqH0T7B0w2Z0MT866Qk/KVJVx9ymi3Ql8qSFkJm+hqvDprRgi1npcED1VomqMixNm3A/0RbHLAr5LpkTeBTfp9/3+gEPSQFGkw5dTqbeSNHcC3GrV2nkxZbKw+JAIqQObh+DLXtqszbIueEWUiGH6gln/HcADTQfWjVag/l3UsLaqZsYqbZCIN+GQDmGl2v9bVdmj0SqydTah/jZFCoBM6fVc6o17iWoL9W7buhDzf91P7rEtAuseMY6cz3gpBx0NTQ/VsQzbG5we17hAq5/n/KfPuLfstzd9Bmn3Kpf3fgXb9ewb89hqhB41qicNcJH48fx8eHU8Wcb4JeX1I9ysmOLgSjP+9N/1mcIYCAJOblT8tTCHJw27ElWbyrIkhz6qBjem0rzpsgtuJuf9zX/N1v5EzXkZCfOnfXqWPT42qG7zaOYdq6RsZ6Hj6+eAA3pQvrLQiE4+p+D1swttqpFH5qT5qxZnSvJI+GpAEe+IlIyYrB2exL4yQwccR1HDXo8zSYvjore1HeLfnkTjb+65ff1m6T92u7hdqcN/vfrP7Axqf9e/XHCkspDdNXT5GB3P/dle+vf/U6YUujPTzu/2t6wuYDNq52KMpZte18cky7j8Ro2xqo+C0g+fpDWZF0mkvj5/at1PmwJgvooO7AHQzEItPwjV9TqgF/7RGCPz+pCuITrpYumhfjt8nJs4pa+X3zh4Ndwz70mG3vdfr8uljba2wX5AMwedbVXND1wsUEBkFmpRcgrE3s/
*/