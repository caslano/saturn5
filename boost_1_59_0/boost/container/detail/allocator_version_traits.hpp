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
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
*/