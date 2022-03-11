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

   template <typename V, std::size_t N, typename A, class U>
   struct container_rebind<small_vector<V, N, A>, U>
   {
      typedef small_vector<U, N, typename allocator_traits<typename real_allocator<V, A>::type>::template portable_rebind_alloc<U>::type> type;
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