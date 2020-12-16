//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ALLOCATOR_VERSION_TRAITS_HPP
#define BOOST_CONTAINER_DETAIL_ALLOCATOR_VERSION_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/allocator_traits.hpp>             //allocator_traits
#include <boost/container/throw_exception.hpp>
#include <boost/container/detail/multiallocation_chain.hpp> //multiallocation_chain
#include <boost/container/detail/version_type.hpp>          //version_type
#include <boost/container/detail/allocation_type.hpp>       //allocation_type
#include <boost/container/detail/mpl.hpp>                   //integral_constant
#include <boost/intrusive/pointer_traits.hpp>               //pointer_traits
#include <boost/core/no_exceptions_support.hpp>             //BOOST_TRY

namespace boost {
namespace container {
namespace dtl {

template<class Allocator, unsigned Version = boost::container::dtl::version<Allocator>::value>
struct allocator_version_traits
{
   typedef ::boost::container::dtl::integral_constant
      <unsigned, Version> alloc_version;

   typedef typename Allocator::multiallocation_chain multiallocation_chain;

   typedef typename boost::container::allocator_traits<Allocator>::pointer    pointer;
   typedef typename boost::container::allocator_traits<Allocator>::size_type  size_type;

   //Node allocation interface
   static pointer allocate_one(Allocator &a)
   {  return a.allocate_one();   }

   static void deallocate_one(Allocator &a, const pointer &p)
   {  a.deallocate_one(p);   }

   static void allocate_individual(Allocator &a, size_type n, multiallocation_chain &m)
   {  return a.allocate_individual(n, m);   }

   static void deallocate_individual(Allocator &a, multiallocation_chain &holder)
   {  a.deallocate_individual(holder);   }

   static pointer allocation_command(Allocator &a, allocation_type command,
                         size_type limit_size, size_type &prefer_in_recvd_out_size, pointer &reuse)
   {  return a.allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);  }
};

template<class Allocator>
struct allocator_version_traits<Allocator, 1>
{
   typedef ::boost::container::dtl::integral_constant
      <unsigned, 1> alloc_version;

   typedef typename boost::container::allocator_traits<Allocator>::pointer    pointer;
   typedef typename boost::container::allocator_traits<Allocator>::size_type  size_type;
   typedef typename boost::container::allocator_traits<Allocator>::value_type value_type;

   typedef typename boost::intrusive::pointer_traits<pointer>::
         template rebind_pointer<void>::type                void_ptr;
   typedef dtl::basic_multiallocation_chain
      <void_ptr>                                            multialloc_cached_counted;
   typedef boost::container::dtl::
      transform_multiallocation_chain
         < multialloc_cached_counted, value_type>           multiallocation_chain;

   //Node allocation interface
   static pointer allocate_one(Allocator &a)
   {  return a.allocate(1);   }

   static void deallocate_one(Allocator &a, const pointer &p)
   {  a.deallocate(p, 1);   }

   static void deallocate_individual(Allocator &a, multiallocation_chain &holder)
   {
      size_type n = holder.size();
      typename multiallocation_chain::iterator it = holder.begin();
      while(n){
         --n;
         pointer p = boost::intrusive::pointer_traits<pointer>::pointer_to(*it);
         ++it;
         a.deallocate(p, 1);
      }
   }

   struct allocate_individual_rollback
   {
      allocate_individual_rollback(Allocator &a, multiallocation_chain &chain)
         : mr_a(a), mp_chain(&chain)
      {}

      ~allocate_individual_rollback()
      {
         if(mp_chain)
            allocator_version_traits::deallocate_individual(mr_a, *mp_chain);
      }

      void release()
      {
         mp_chain = 0;
      }

      Allocator &mr_a;
      multiallocation_chain * mp_chain;
   };

   static void allocate_individual(Allocator &a, size_type n, multiallocation_chain &m)
   {
      allocate_individual_rollback rollback(a, m);
      while(n--){
         m.push_front(a.allocate(1));
      }
      rollback.release();
   }

   static pointer allocation_command(Allocator &a, allocation_type command,
                         size_type, size_type &prefer_in_recvd_out_size, pointer &reuse)
   {
      pointer ret = pointer();
      if(BOOST_UNLIKELY(!(command & allocate_new) && !(command & nothrow_allocation))){
         throw_logic_error("version 1 allocator without allocate_new flag");
      }
      else{
         BOOST_TRY{
            ret = a.allocate(prefer_in_recvd_out_size);
         }
         BOOST_CATCH(...){
            if(!(command & nothrow_allocation)){
               BOOST_RETHROW
            }
         }
         BOOST_CATCH_END
         reuse = pointer();
      }
      return ret;
   }
};

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif // ! defined(BOOST_CONTAINER_DETAIL_ALLOCATOR_VERSION_TRAITS_HPP)

/* allocator_version_traits.hpp
C6Yis2FW6tVDL5iGzJHZoMJGKpgvmQuziN4Nz8MCydyZVUrNPQGLJ6vAbM54171KX8jcmH0rUzUFlknmxKz7mA1rYLlkHsy2jN+3XanvvvH8WuyttRzmTebArIy36RCYjsyN26q8PFiQZPWeB5RX6iPjeU6prd8BSybjPfP4X4XbsAwyNbOR+xo9g+WQ8RnlTarqCssns2XWI6RKS5jZA+PzJeZd2RCYhoyv6fpyTQ2Ylsya2eV8ofRaR+bIzSTCHBZIZsVs8CvPRFgYmTOzUXnrUmEJUp6BtbJuwZLJXJkNb33NGpYh5RJyvPoEmIGM9zP2rl0mrFCK+9Qs4ARM9dA4z3kjXCbCtGQ8z4Jmk5Se+ZGp+Iz+eTEbFkSm5nmmxd6HxUv73btwZ4RSO5kbs7bRUduU2slceH2m7SfBcsjsma2cPeWTUru0X970bSX35Y+M3+Plroi1h+nILJitPjc5BuZP5sisS1X1HlgYmYr3U2NzRKmdzIbZoIPPC2CJkh2NTXkASybj9Zl9CigNSycrz2z8qk8mMAOZFbNxI/46C8sl8y62UmSz5leqC1M/NhUNma2YU/1lkdH/+5cstvh7CaVNosfTPwUsnwy9/mH6C0vjYaonpqIGs9D6bvhd9RA/MuRSxqSedtu0ixGwWDJfZkNSa68ssv7BGWS4DylrEjIi7HsUfp9SX8jWLGcSOuTB/WU3iuMitU9Nle9jmpnExIw++rKLYrlKnj9N7Xl2ECyMzJ5ZxLysabB4MmtmY9Z9VvZLJDNn5uf/uSMsmcyK2e8TJ1yDpUk2bJfGEZZB5sBsR+1qFsrcWQ3mJvTY02RWkUXEqJ6VvNe2NIkOPZvj+qnYBvmR+RSblUloxInWE6YWz2FsPDNrk9hGHUZplPM6na1pY9I/0j3+wCtR/P8hzifDtcCWcpl/ZORwmOo5XeuYOZRpFgHTkjky++xcbjvMj6w6s5Yuu3SweDJrZt6J2cqaiWQqZjf+zNgGS5Hsa/9nh2EZkrVznz8QZiCzYvao+4bysFwyfCeKTNRKedQDlk9WltmifyIqwQola3bq03qYyDMVZmy/owm7GsBUZJbMDKlHVDANGV8z27fdoSLTj9aS4btNKpPIkPEPJp+CiZfKufTT3gzL3lVkMeE6MsTZmYSHKnFkqtdK3E9rlWWn3C/5kWF+zhR/ct6p/2DxZFizPD0qa9J//v+VrEkmPo6bPg3Xl0SylOI4NV1f4v5JdYLNfavM4afZNFt4B5ZEhteVH/bI7dRHWDpZDWYJU6yWwfLJXJl9Dhp+CqZ6R+c8s51PIqxhWjK+X821tqdh/mTlmVWpWa06rnV6slrF5krXupsnClbDUsgsmI1/sP8SLF2y0Md3XGGZZNbMIvb98xxmIDNjNvHFsImwXMlCC1fegb0jw3eiflhUgP4lrJDMnMX9n6v7DGjy3OIAHgQFmWFpQEZUVKiiceOOkyCocccJFpFoRSMunI0LcaM44saNioo7jipuHNW4446jFq8LBxWt1XsU//HkuV/64Xf/zznned4kbwZtc02jNzCHwhKSkix3Pb3BIZgrWSlm77X168B8hFzHW3NbwuRk3qze+Bd/vYBFkPEZPkp1/jAVGe9zpY/7ephGyI2WbuxsfX0gq/7DAug5uW2j2pesr+FkeB8Q+O2zIIcOF2AmMvx347/Z5knzesGcPpSQ1GG5MhV1zWAqMmdmisx5/WAasmbMvAc8uQxbT4bf132z9o37PodlkYWy3MpI950wC1m771bcZ8Ootv1hyiLaM5Zb38MxEqYma89yWvoxACyHzInlglYOteZyyWox+zpc4gWTfCwhqcFsRxf7JrAIsnBmAUs=
*/