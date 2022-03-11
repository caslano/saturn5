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