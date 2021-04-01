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
Ta4jxAXrsa/uB5NxicWNzlyM9PSqkcyxaESHnH/kNRFHwZcwgrhQRPAAgK65s6Jq6zIliL5Ivm8o9q70UCPsGjhHdKSJnJM77eVhNombzBh3Qduxmz7APHJfAK7y2KFUjPiDNKK8oiWzW+Kr5SdW1pIHeEKlqN10ROJlAgHk2Q7w0u3R+YKLDSOelQYmHr65xpWnjKcorErm1/aMwneaAYTcDIUie/hc8K5+uk7Xr6bWAkdS2+HFGXmLoU3txPRoqdC9MvyBjMAWSsaD0Do0X09ZcJhFIuHpJ9kVF00Gg7fePuQyKEevs0YLjrbTxchHeglQCGNliXojNBLxxx4vJbWc+ZMZ2g6aczbOFsPapWDZc9yydEAIQI/0xHdxY2jUwpfP/FkBAN9M73KHGD9t+ayRD6wcwvI7y7Je04KCITOPvSVeNlXXwIA2T8l2awNdDwhj/cSdkq0QpKr5IVuH2VuMD8KdedV1nIPXeXS9UK14jBai3+XsqIELTUQ83wkPulmK+1YrNsj1lar35L9sHu7nV1Xhe9PAt5o4gSkobIgChA9x+gv23bAS/A==
*/