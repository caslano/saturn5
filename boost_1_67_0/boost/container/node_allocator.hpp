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
ZJQF6weG7nbq6g1mfxgGh95hV/eZxAk3UIiWYb/12hz+vysWnyMYp2EYxjifGFmzGBZHuG5hyE2Pk8thHPABHvRvHvkQpNshHN+jLoPhr9dw93goTcZLd8gPUMp0UMxLUM4gTtQg0OLwYHxUaEt06A+ISKy3RuJRkcv1cTPUyOX6yLNWITbsrxXkyJYxaYQr6RbcyJp4abgNabk33p0V6Y9viMFbjKc2hP54FNe3SURcaT30ST4Iap+3Arwc6Xls6fp46l5TEWQuGCYTtYQqdaUz9UUi0UYyNUc6NSkEtUcqNWoyNWgT+4gq9Uki9cqqVUu6NyyTlQyyFS02j477VU/31c/mVXDe1VDmFXHulVH2FXL+ldJ7djN39pNmdjRe9hRmNjVuthV2NjZ/fOzNt8zOrszPjczQnMxRzOan8syUKYWCl/hTpjRDDl52XIzpDO1ZTO1aXO1X2czbDQytWm2xKe1x502oF22FX4r6VK1c7E3LsU0AbGeIHlyWdUy4x7/WuDHUJkCaBSVAFzMYlylbt2rSdsI3SQOMsWBWV/BEF02EBSqb92VKd2am2y7T0ytzN43/lQP0NahLgdP5RZT6dYj7tZj91RSxHYT/FRP0FZVeccgZToX6dZkbvokN3rlgDYUPngIEHsZZYckZTpYKfooLvpoN3sZE84kfnhEEHtc5TtYlxkcNr8MZz90az51RYcMXjxAC7/0cpqYSv/DkzTbUGU/cGk/cff/TB08YAm/UGw78MittUdZAPLvILsfEJ8eeIJdkMofEE9dUDe/fv5wU15wU5LyTi6yjyywU2xwUuxw2j2zWfzmAtnKHEDMHbzMLLjNav1T1x4n/5lP/zYedgiaL/y3OvuKpYvKpYuJpc+pp41/NZNaAHs+GHq+IrpuMnvmXE4WlIsKkIjakGrOlgvzaNaqNYlGvZFy9iEFrfTWEErW7yPNEe4exfzv0l94VZ1b+9yHU9O06XNrJzk3YtAnrI4ns796eipvkDQzhWkELoSML024tDNvu3esYY2P7pkwB64OvWoqN69eXtAGzS/aUObvcrdnZUl1/RhE6+czFcHea4xPaMXTb1A2V4Uis9qKHYOnVsXEDDX7RwruJ5ToXK34p5+LalWxkL9T/1q/6cZOM1Gon6+Li/k9983pYC3qBP+bcrQ+kyn2wEd/ukzjAux9OQJl1ExKmBW5srr0Qah2SDKpgIhnJGcicK9ty6TJ++4D2OYgBVula1ECP4zXcBNllMkPFxTf7xfhb+BqE3VgN2Cvu9XhKSn/oVybQ4sxzIGLIUDjLFsROuEI6B4fk3B028d1U/kiSLBM1BUXrWBja7jF1mEKqMrHkSVB4a3nz/aHN+FWxpEtNIRN0hR+mBALMhysDMoRJYuJUELpj+Cg0DyP9mHwhKD2zZKIk5cifOgoPvZ9yi4o6KA8yyGgoM/7NT6EV+D8xBb/FhKYVR/hwxuF5h9Il0fW675Th7Iq60+DwGTS1Zt5c/clK8IKtmcoRyZkFy3+qxXRYZG8zVRfcJptnGWguWtRaL46LZ9oxMPbU2PJaxROZ34EHTskZyAc+a72BFjou/l75nTchfU0dN/4lNL03waccv/z5ro5vRL/FrqpGFsRPv3gNvqpmWU7ft4SdWl+6GXv8oVf47IsJvwrcICWcw75QAAQs+9PF+CLQGb8oUvwMKTA/9Wr382o0P81qmqDpIz9alTlXVr+8Jrlvz7HNVKzq98/4VqhokPem/HrTI6xkcq92+U/Kp3e5QucIRZu7FnXKw1Hjq8x1vIgDvnDrnOIm4784Db26hlkEPfqNusfzrs/KtqQVp7XSlP2Sh9bqoJFkJLL/eQ1kyOzG/iQou0QvQ2+0vAZXszdN9gDgPwOcDkg8I8nULjhjJOgNBDN9uD/dS8If8ho/0gEINa8Lt0AA2O8TXWasqSjP/xc3xt8newcII2BrBB+ugmo6dnRawHYu41bR0phXfliYG0fYV+TgaFB8AOQ96akLqlPonCaANK8OuJTHASAKs8BnPVxJAFhJSZLn51HEMSQblkJfDxIvQEh0L1tWQiDglYUCeTDye9nhSyfWT7M21YTLyP9vrLEqHj5xWjboRXoWWkoARg+UmTpUAU9P1iazNxHvcPgRvUzJV6ghPNN8Eg8QQ90wArMEyR6MDIHBdI6Pq25TYwTbXIGLV0HDnZfBgA3i7Ifn0AdIJQtPasgYZ/0Ms1GSB4WVsyvivYxIUkBouRVYivSCMXl4I2gjDEiLdNVtavYW6CMPhZku4k6Hu9vgGc6gTWTs7mPOvbdwz/CcRKmIxtEq/OQBHgOLxcTaOelq9QP+PFvd5CpQYRE+KJaDSNOElvzfonxUTBtc3XHF6CkT/gb0Wa2Un6NWcplmn5MU3d1SuJyzsZn5GBDh1Pw5wc0njoBJPUPxkUzaiTfdikg9xWiZ0JeTKh6iUHjb/raM9YU3X3JjUtDCmbURNRZt9b/wpvIjHTlfb8JTkfCq+kGdkUvveAHhhDPKFS+6GWHGAchnfMtU2UUFInx3qmzRRoWK86zaLcWKjSM25Zs7hZJ/ulUr5O0a3Jb6tkTKJefYDWtzHwr1hpKVLiTlLXwPoRuaOXopFaBCy+r51kE8IP00rwc8aqF3NRcFLeOvNGDLQyIp2Iodq3AUP1ERFRrMJxiLHH91yviahLjzM/HBKTOSjEievlp3OFsGHK0Z//gy4QRyCMAKNlPBC/69lSn0FCNEaIrHgSDNZmmlxTgy75VoQPL5aJQ3N0nQMwJhY+VjMDNVEA41ZMOz/iEPF2p/ryMiMdy18M/AqoiKNuPYIbifpkKLcZfHDxCshUCPDfoWGb3pN287R/hiSVqwukbfIyEdln8q5AcuE1I6MdxnSn9U5Z7R+OlwrB34Rliont8ONZODaZ5RLiIYUxZKow8zVi38UQmB9immO9C+ZcR6ssvb6U294GEp4ao0BEjTyBbdTHIyef+0fwEA7cT84APCLC6nstD1Hihkiyyrc61mHj6dyMDyWO3d5ltA6l235R3j+8dkHZ7bvktumkThCG4ZBj7RhJC6wR75vA7WqvIGDx6SZlse/D93iLEXk0het3//sejaro24E/CtPKmiCSk/AP6DZgROjkYOkaFGXEfmcorjSKgxaCoVqkBuM69Fbz/111k/YiFLzCfglni6mbVGM08OQRqhtwpwodztTw/cj/EOR7nAQX+cwAJx3UzUIaqwl5EKr7QJVP6PWhfitgN0sEWrakV6q8/hdtitJnlIUyrPoMYbpK6gucqKzuS8zkngjt+KLruQMKPWy0tgH7SHm2RfC3HJz69vxE9KCLov//NNmO4BDTBph+19kyDIVRJQcA/YQP/Yu6+sxlBAx4NxvFxAELChV5C8oCJ7AIcHlM7OiPLxFdIPZq4QCSR8XvMaHMVosLADpvXeKi70KmjwcETxv48CLJGESM7FjwjN9r7byR8uHBoB7zm72916kGVfSFWW4X8IL7lCz00xHZNcZNvN+AveDvpMT441TzsczCNe2pjjzjXUA711ap7a2ufOtpgDvc54HpltY1/LHsXew9+XNoeBfcXIaQ42gQf1x2N99Xw2jNXOQ+7BEo9MH4ePbO4V33HGF6YL379vcdl5S5OR/6kjjezPEno+KjjUHKoiHyidKLMrnT4nbT7PpI6XCrbPbJJsdh/XfrEN7mS/ijriW6Fn15bse8XKKuOndqTWZvap7Bnnbp3aYPVes/HbG9ZdPNbDvuXTDv/msL69/+0vQOWd24ql7ink33xXGjscPi+pHQXfctyCBPiuD/Wzf/gocvpNJlAiLvpcKvpVZvpdpvpG4PpADmg4NPxMLvwRhkBE6PwBtT4svvDruMbfaUJp5xy/nCbi/yRfxBUffl9e43TzRvTN08LleQV4OAUeNH3zKAFWGQXUst5xcGqQECS+khFawdWa129XdiwaKBHCk075yBXk/24xT8c4SO08KQeEEl8CBYKxkMT1VrD2d645xexxApAZwnf65k+nsRqDYcwC/qlTCzSgapQqZRwg8CpoOF648EOY50MRR3SYYNWFIdIWGb6R2qZBZwsxQR8RKV8xRD040zN/VT04A0M4agVwFdhH3ogJFPbCan1iU1hidtRCpGUrz12DHd6II3btoWmCG27gipxBrLz5jSHg2UeFQqRxIoHn7SdAdX+R2hA/at64Vou6aGOGmYuwStwrJsG+QCig0ZqWeiKAONo7NVqpLLt+XqvrlkAWKVRV90ANTwPeJ5gaLjulFYqM3Cr1VwC5sYjbSaQXr6jDagMtMKzpCEBEFBEW8opJWwIsN7upe+XRJ8SWYsKSCrAlJrzyXM6WGFgEQvoZD3g6CIRt1HnuJ3KAi2A2djFm5UNcQF9xJMVCUD7iwx3ia+5DAUCDPB0HPwCM/su2fVwdjZUzULm+zUYBD2Y9ZaIeaVmWpJz0YmQLG+CEH2+gWegKXDUKqDIEqkofmkQ+8sQeeOg8YwBMMZRTZ/ITP2agVE65pT4Ma7L+TT6tXGjWAdK0OrAkQ+yqVoxdZE0WE9BMY+4HOBDnMZqJSchPnR0gxxEUNjV5DdS+CNoj2eywQZwiETLolkSV6wStOyPJEBoPiS9u6EwvGw6VXUicYr4meK76iIymGNkHCkJZW3VslxfuD0msVRhRZrU6F9iGxHaJWjcu+VicXh+qDVijTilncIeRI2ioIh65GGiqS+mrCM4RrDvSAS5MWHRSy1IQYmle5a7RBCbSxTaywQ5OGSGGkwwupzAsg6eADf2w9JOM50COyRJ2ZQnCfCl4xCBs4CoW6QMwdTK6T24oEbBmNr8QmAMQC2FicEEKyFKS00p8xRFDOGX63Z1VZyQNpFWkKU8/uhbtv7Y7PJOX4snCFoHizLuFbRmWYwj6qlRAzx72bA724AGSgBYExBLF4oBkdgcdfQD155OSQI1eW0deo4ZlV4afWp6ISa+XAIWzPAkL8z8uNOZdIdOmPhFCSGH+TsvNIZLktmlO5xkdu2+wGDkggy4t8yiYeRH/oATgSK4I30OdI6aI/pgAGNLw7WFNHU5kfmjnYDupvp5OsFdq2pYVdu5rMIVUIzXYkGErI872jIDLSDg2I6TaFOvAk/saS8bg/WTXUjRH43B4Q2/7dOXmNOS0U7X+gwF2IzPhgBRNc8Pz4aYgw2X7S2FGQlkyIlOnVLvjPr0ajcNTp5hBpCnyw6Q09Ol+JGfApttcQ8ZrCX9K1OrylXjSMN1KVOjFPJzVcQAAmCeWbTo4s3LI/gjI8ZEKFyS5ZBrGkSHmBELEvPCIsmjk4x0cxIyxlHwsSKfMBktsxaDmI1Wk5mtu60QAiI1maZ9WMnS5c28vKoDWkGAMYkiDXqRAAE1Y2SGQmMoTzULIvFQghgeANAtA/e3sOD8ol6wbl61/AGwcT2REABJsJGtssBh70GEAFFUWHSzgAC8Q0VZVMf9gCcQ38xjAFBqsFSyAy5JZzZMAfbJYzUsBnS2wnwcBQ1KiRywy0IxJq+H5qxaOYl4ZbTaxrIYy9iyZdHbiVsoAb5rMzQkIzjbj+jDG7N0RCqxIejAgyVpKwvBl4y0m5ptkFXloGZVoHfi1Era1lWaxkEe1lGa0FiYA+B20M8e1Zr6BSZMDSyOKr1JIqUe0JotIKs03LSdMLmg2sWhMMyc2tPZMNos4IgYYZ0mAbtUVRmEFEwGCpGQQTIDiIpYhsKTbr4YEz+1sWsVwYwFxRd9xiy2qW5ltpAXaZlA3ZljLZ2A3VqobYw7uZhobVwabZh7rYy4bZ5Q3aqDbWkJbZ8jLW1Kba7Bf1WyqbsS2lhzLb7Qmbe07blbubNsebmbqbYseb0jb8FQ6clDLcwgtD4FOaPRlWPpz5QYH8mAJ7Oc3x2TnMNfpETeNCTGucTVOu58Ou5vctvUnPcklPzmKPtuqPgjuP9pWP9eKuHuyXr0/V+jfdiYhd2eFV+EP5+l5dmLtd2rXdnIXkdRs0a8Ej8sOmOIuL76IjfamvQRqvfpynBTErRS4tzXZveNKLBQGjRUuveeIjOYMvecg7ebEuBQja7p7bQSecYtly2fyRiADx8xx5/SSoowAcPC/MLlNgtiPDhhRbFjPIPgfPL3SPs3X5DyOSpcltIYgOKYlUlYUSLbNB94k+t8lEL/KfGYk0p/MI5bNxYbMZd/Nt9/MOb40YpY1wp80Nt81QLfTtLORFbENe1feVOEO77hX1z7ejj7fWHaGrlrD3avDRWPDj5/Cl1/Cn5/Dp1/DbbrGt+0SP7USQ/ESR88TS68TTy8TU28TV92Ut5h77XjnaJ/nWJZK21KBv6VKlgSE+e9L+t1KCZtUb5pLUNOQ85lLds+59ngUBflKFN3+zTX9a0KPI6QxWwMWtmea85IvuTeVcJQaCWv+R8nzr5zPrcdkymcyvWQzTfQtzbSAnAR4Ybbec8bBbAoWdNb+392ezVT9zhTE3myiq4n3axb6bFpqlUHxdRq5V1ZiNgRHbqZSmYDgip7CrMbclUZfbubqAlvCrwZCfxrzWx3ivB7LpEbTmcbSrm5dgbjZm4YIcc5/e7pMy3qO4xqOlxpcm5pPd0fLvxodmtD3hXZGzTnwUxpwlxoxeeKvGxotuxpiCXphn3VdymnSYxqS1xqSv2m3mvrrUPLyqZpSjzpjLzq0Mxq03X1fIXVYmfUJ+vVKa/Vatd0rYXVq9fVKxd1KgXUvk07X8M2TGhE5GraF+udpGpcH39LXROhgXCmhCGpRTeqjfCt/7e1He3rEMSfY5TPoR3NxTDT/Uo2xB7Gxe6SP8akR7ZrTI5bvJZrvhYjn+5XRYYHRd8XAoe+uEAg4IGA/uPg7v6gEEaF5+O0PMATG8f4vdZDIvDTLk6bip35QEL2mPk8iOZ5NQ8/UFz8hSdu2u2XfgkK7nv5aL0R4/L5x0jV+0NM/3Z7YsRNkR7GJAsvCSXCcGIGOdIsmgCtgqWNcNQlzgjAVKuWO4pW12eN9NoTb/7LhONJq6AHVfrpjuvL8DO4PVQfSNwilkDxfl4Vah7W9C1Ipw+TaTjfzJSqdPR+nd+pwIAUf7QoOOP5zZowhDflQAxGsBhABYddeH45g8ibYe99kmD0YqL69eCqWAg7ZM5RDM+sZY5zfb4j4FGh6Wf+AIFlugQcRTAhJJP/5mXil1FvE8DXpR3D/XVortuhV2B1lkB/LHeXuF3GgKm+4NC8DjDNfAOqJe7/1Rm4IAp4ei9BoQKgziO5J4/hSBxz1nAdSQLoHWz6/IDhiyWAc9xEiSkPo6nskfpYgVH0MBHGBif/SuJei+doN4BTcXll9GAenNAsmDVXiZ7mOOnB2CBovhhb5YrO4fc74/yN48jFB1dzyUcCs7AQC7nYc64dZIOVq6hb8u5L/NRyo0k41evlmQJeAx6SktRtKUNV2NOPwSD+4RHfmJKWwD5xcorUAkJIQzBsFhQyYPqkCoinS8n8CQYN4B01XVPjOHqsrJWWvWlIwCZ7DAUhN+hj7DOaz0RPs7ExUWs6EVG/CFXTLpAehplTZlQxA5bXrq0XXd4VRcFr9OL3RROcKMco6mTBqEAmeaRoRUixsRGGFOAVQ66T79sMaAAB8F2uAVP88WoX1QyJMe63P4BlDqhpxYAJRr/RSvPRoul4edlad0hu4lRHFHEALIIsbincmY4PHWG1D2uM07943Tml6Zx/1cPdmIhY0m2WjiS/05AIFThlk7x+vuuakqn6E6SmwdBtor/xcvDPY/VUaoaLSKOggAyV5FAB073rkJF/QcLQYIFMwbtShwOfx2NLpkG2tG1/hKHMwpMNLlCBw71XVIOcgU9CYxkxXBtmp9VVeGguOp5/u1idny23WOSbbHRnPmTvXTRUVDy6MxJIv1yQ2Vg/PbYSx/d9dLlDz1xWglBvfNL/Re5vPe6hGm8MgW6iv3zi0hLfbQGYro4i0SKCMRQltJEyjI7loRglCbGe58dj0nuuzXTM/X1+ts7GnxHtGEjbSERRug9YruYOnDVacYv3WgDhqybYUN1a7tzoeJ+aDQHO+cLnVQoQKmZ3jUb84fKdhdZHQRMG64AqSp2sqlU8FqTrgTJC3QQr+EH7L6IvMsacESB0m8ln64NBTdpwA+POfkva2PG77wV8FIZ+UBTTCHNmO8xEZ0uMYRoNLo5INDan3Z9u2A8uW/3V2DoNrQgQMyhY92hOMg61r2REhg0rexwwNe1xYFeiMwDa/RIa+6V2f+3SfInrHC5wKt0dDGiaTCOFionlfxYZHjJEv1uCmzHVFE7+SFu5hxCNw+KGw8MyWIhWexIIchZ5Ko89JbEkiqO2QJU0lzqdnxErM7JCNjCQyfzmi/jp4Zh6xy8+g4FCVRDqmXoWJ9SckEVmOOaYaFcn0a6FQGVW4pVZgyPfvFBFan9unjvDL93M+EZlg/5cqR0qzzcrLFI5PHkQCWzjj9ERU5IYT/45TN2iMBVD17Nb96OtFj/RGd5PIIoQKT2f88nBFc6rOJ57+L55GpDz9+p9iWagzAWDdxiBiJsbibD/mDH41cNbY7in1BTp0QxKUlI4ApEqTiJnPjh89HTjiSykYN10hGozQmZNegYiUJKxJuPCT39eAYJyMlCg0uUDij6jXxCmpJh2cb1HeBmN8Kn5s8k3eQAg7I4k5e22TycvxZXs2Vi66RwmWFyJ+2i16MTF0E0iUH5C5hCTuXsyAzRBDpolgek45AnQQEaKb5YsQIQokJVuACKL9uzRtUpJY9Lw5wJYlpsqykGXihbFuAaPuAhum9xl5OtcnaEg6Vk0JfUaQ5U9QcpbJ7gF4HIV4lVeAXrZ/qGWwdpTitMeAqEa9RC57FIJHxxZZeZRXSWu9pA8B0IyhXrT03Z30vTRBq7NwjG1YwygHUKEZkYamQXT9kGNW1nHX9+26idLwwKJtJyDl9o1b+Vy69iUPYfHYtzxCHWiCyE1/LXUtx2S2cq2R7qnlMMRjaEjG22AcmwffAeJCx/wUes8/nnYzWpWMW4OphIxXkn7b8aHPsrk4FZmfncP1O33OfsF/wKS1lB/dL9/gVBAHRFE6IjA9UmTDby2X0vXfKMEnHS7BmEnExCh4/vcuYdJW7A/IvpiKMY4SNA8MRntuhB5p2JCKqFXXsqwFQdTdqB+UIEI1c7Aiqmi3PwcAQIPbNgKceXCYDyG2fTw=
*/