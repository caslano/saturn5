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
FZXWFTcq6u8o/dKT9+nz9J/Pc973jHtv7r0J7WNYOTI+94QP8gMwFRnf73e/eD+YliyM2druFzvCkoS4tjtiJTADWSCzztVlo2EmMk9mdbXh12Bmskhmsqkd18FsQly9efvKw+yCPaq0OBfmIPPiNew31oBJbjrPvWd9/76wKDJfZtc6XSiAqcn4fsXPVf4dphXstKnEP7B4wWZtiXgNSxLMo4LvDViKYGfGlHkJSxUstVndPJhJsILjMd4wM5mcWZe518vDrGQyZl6LJs+E2cgCmJXutLsLLI+M93pkpS9LYPmCvdr99keY7Jazxe9vMQ6mEOyLZ+pXmFKwyWnTy8LUgjXf02svTCvYyaqdB8HiBXvWq29tWJJgw08M+huWItgJ682rsFTB+k4KTICZBLv3KNIAMwt243hWMCxTsG7dzpyFZQs2dOStx7AcwV48+as+LE+wH14McIPlC/ag49aFMNltZ0s8s7YDTCFYj6eTTsCUguWMHaeAqckCmT29PGArTEcWzMw/+Ywdphfi5v2vb29YqhA3puYfQTAzWRgzrzrdSsKyyUryNbPcJsMcWBP207VmMPkd5+ecgqZxCljMHeHd2s06VlgtsuLM0hOW14WpBZskVd+FNSBzY7YlUfkIpiXj561Ju+YlLJEsiFn7NkdXwQxkfsymuLX5CjOR8flluT8/BjOTyZnJb50/DLOS8V7vVO7KhdmFNeOCfZvDHIJFlmzZBSa563zNatrn0U8wOZk7s/TmexfAIsj4HLwvLBoFU5L5sriBF3OyYRoyXl9o59aHYPFkHjyXlx2LwZLIApklhJaPhBmENS2ZDbbATGR8Rq2fRRlhmWT+zCYs7roUZhNq/98M3yCYXcjlYGrka1g+GT/O7hxfEAIrICvBrLws5zZMZhfy/N+oC7ByZLzXq9+PHQpTkfnwnmWn3YZpyPgc9uf8nQOLJ/Nk1qbpn+tgSWT8fCjok6mH6cn4jE7qpjeCTRLyLJPx4C9YKhk/zv6OHOgKM5EFMLvTyecezCLUV2/26YYwK5mc2TufekGwHKH2lj/FKWAOMj9m4Tve1oLJ7jnPdtPF5XdhUWS89uitiTqYisybWZlXfa7CNGR8vwsR6VNh8WQ8z6lDTYNhejLesxKNpOEwA1kQs4dbxo2FpZO5M1sn3xUDswhWXaXVwqxCfRE7y3yB2ci8mI3uMvgBzC7U93RR61ewfKG+8WuzfofJ7zuffxVrTGkBU5LxuffaH+cFU5MFM9vSucIAWDwZ74vSJ6cCLIUskK9ZI6wOzCjEZZSNagSzkPHZBiZ1PwWzCnEJyyJ6wOxCnG+JeT4wB5kns6S47kqY5IHz+bD11Jm+MAUZr/3GiBrRMLVgT2RzvGDxZLzX9iPSAzD9A+H+80Z0DMxAxq8FVzodeQBLFda8tel4PVg6Ge/LnbrXP8GsZO7MBoWFF9VnE+zTxUflYHbsB/PL1MDyyeTMng8Nvg2T5+IdJ763H+sGU5GFMmv3oWQETEcWyGylX9XXsCQyD2Y+mozfYaPJ+HV+RtDdbJiBLJLFLT8/sgbMLKwZWmpGZ1gmmQ8zafNqXWHZZJ58zbPzh8NyyAKYtV0wOg3mIOO9viT9owAmeei8ZtyjlHIwOZkXs3WV+y6ERZHxXrdatXkKTEPG6+uav2QeTEfG63v4uFV/WOJD4ZlS+8IESxHiam6/dhOWSubN7NiN+kthJjJee0DNEVdhZiHOVGeHGyyTLIhZlZ927IDlCHm6dKpTtJ9DiFulM3yCyR853++6qpJ7w1SCTVfMGAnTkfkzW23M2AZLIuNzf90uow3MQMbr6//oqQlmJOM1+HorvsDMZH5O3/dnXoE=
*/