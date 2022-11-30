//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2017-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_REBIND_HPP
#define BOOST_CONTAINER_DETAIL_CONTAINER_REBIND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/allocator_traits.hpp>
#include <boost/container/container_fwd.hpp>


namespace boost {
namespace container {
namespace dtl {

   template <class Cont, class U>
   struct container_rebind;

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <template <class, class, class...> class Cont, typename V, typename A, class... An, class U>
   struct container_rebind<Cont<V, A, An...>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, An...> type;
   };

   //Needed for non-conforming compilers like GCC 4.3
   template <template <class, class> class Cont, typename V, typename A, class U>
   struct container_rebind<Cont<V, A>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type> type;
   };

   template <template <class> class Cont, typename V, class U>
   struct container_rebind<Cont<V>, U>
   {
      typedef Cont<U> type;
   };

#else //C++03 compilers

   template <template <class> class Cont  //0arg
      , typename V
      , class U>
      struct container_rebind<Cont<V>, U>
   {
      typedef Cont<U> type;
   };

   template <template <class, class> class Cont  //0arg
      , typename V, typename A
      , class U>
      struct container_rebind<Cont<V, A>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type> type;
   };

   template <template <class, class, class> class Cont  //1arg
      , typename V, typename A, class P0
      , class U>
      struct container_rebind<Cont<V, A, P0>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0> type;
   };

   template <template <class, class, class, class> class Cont  //2arg
      , typename V, typename A, class P0, class P1
      , class U>
      struct container_rebind<Cont<V, A, P0, P1>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1> type;
   };

   template <template <class, class, class, class, class> class Cont  //3arg
      , typename V, typename A, class P0, class P1, class P2
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2> type;
   };

   template <template <class, class, class, class, class, class> class Cont  //4arg
      , typename V, typename A, class P0, class P1, class P2, class P3
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3> type;
   };

   template <template <class, class, class, class, class, class, class> class Cont  //5arg
      , typename V, typename A, class P0, class P1, class P2, class P3, class P4
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3, P4>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3, P4> type;
   };

   template <template <class, class, class, class, class, class, class, class> class Cont  //6arg
      , typename V, typename A, class P0, class P1, class P2, class P3, class P4, class P5
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3, P4, P5>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3, P4, P5> type;
   };

   template <template <class, class, class, class, class, class, class, class, class> class Cont  //7arg
      , typename V, typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3, P4, P5, P6>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3, P4, P5, P6> type;
   };

   template <template <class, class, class, class, class, class, class, class, class, class> class Cont  //8arg
      , typename V, typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3, P4, P5, P6, P7>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3, P4, P5, P6, P7> type;
   };

   template <template <class, class, class, class, class, class, class, class, class, class, class> class Cont  //9arg
      , typename V, typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8
      , class U>
      struct container_rebind<Cont<V, A, P0, P1, P2, P3, P4, P5, P6, P7, P8>, U>
   {
      typedef Cont<U, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, P0, P1, P2, P3, P4, P5, P6, P7, P8> type;
   };

#endif   //!defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //for small_vector,static_vector

   template <typename V, std::size_t N, typename A, typename O, class U>
   struct container_rebind<small_vector<V, N, A, O>, U>
   {
      typedef small_vector<U, N, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type, O> type;
   };

   template <typename V, std::size_t N, typename O, class U>
   struct container_rebind<static_vector<V, N, O>, U>
   {
      typedef static_vector<U, N, O> type;
   };

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_CONTAINER_REBIND_HPP

/* container_rebind.hpp
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
*/