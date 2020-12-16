//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_POINTER_REBIND_HPP
#define BOOST_INTRUSIVE_POINTER_REBIND_HPP

#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP
#include <boost/intrusive/detail/workaround.hpp>
#endif   //BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

///////////////////////////
//struct pointer_rebind_mode
///////////////////////////
template <typename Ptr, typename U>
struct pointer_has_rebind
{
   template <typename V> struct any
   {  any(const V&) { } };

   template <typename X>
   static char test(int, typename X::template rebind<U>*);

   template <typename X>
   static int test(any<int>, void*);

   static const bool value = (1 == sizeof(test<Ptr>(0, 0)));
};

template <typename Ptr, typename U>
struct pointer_has_rebind_other
{
   template <typename V> struct any
   {  any(const V&) { } };

   template <typename X>
   static char test(int, typename X::template rebind<U>::other*);

   template <typename X>
   static int test(any<int>, void*);

   static const bool value = (1 == sizeof(test<Ptr>(0, 0)));
};

template <typename Ptr, typename U>
struct pointer_rebind_mode
{
   static const unsigned int rebind =       (unsigned int)pointer_has_rebind<Ptr, U>::value;
   static const unsigned int rebind_other = (unsigned int)pointer_has_rebind_other<Ptr, U>::value;
   static const unsigned int mode =         rebind + rebind*rebind_other;
};

////////////////////////
//struct pointer_rebinder
////////////////////////
template <typename Ptr, typename U, unsigned int RebindMode>
struct pointer_rebinder;

// Implementation of pointer_rebinder<U>::type if Ptr has
// its own rebind<U>::other type (C++03)
template <typename Ptr, typename U>
struct pointer_rebinder< Ptr, U, 2u >
{
   typedef typename Ptr::template rebind<U>::other type;
};

// Implementation of pointer_rebinder<U>::type if Ptr has
// its own rebind template.
template <typename Ptr, typename U>
struct pointer_rebinder< Ptr, U, 1u >
{
   typedef typename Ptr::template rebind<U> type;
};

// Specialization of pointer_rebinder if Ptr does not
// have its own rebind template but has a the form Ptr<A, An...>,
// where An... comprises zero or more type parameters.
// Many types fit this form, hence many pointers will get a
// reasonable default for rebind.
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template <template <class, class...> class Ptr, typename A, class... An, class U>
struct pointer_rebinder<Ptr<A, An...>, U, 0u >
{
   typedef Ptr<U, An...> type;
};

//Needed for non-conforming compilers like GCC 4.3
template <template <class> class Ptr, typename A, class U>
struct pointer_rebinder<Ptr<A>, U, 0u >
{
   typedef Ptr<U> type;
};

#else //C++03 compilers

template <template <class> class Ptr  //0arg
         , typename A
         , class U>
struct pointer_rebinder<Ptr<A>, U, 0u>
{  typedef Ptr<U> type;   };

template <template <class, class> class Ptr  //1arg
         , typename A, class P0
         , class U>
struct pointer_rebinder<Ptr<A, P0>, U, 0u>
{  typedef Ptr<U, P0> type;   };

template <template <class, class, class> class Ptr  //2arg
         , typename A, class P0, class P1
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1>, U, 0u>
{  typedef Ptr<U, P0, P1> type;   };

template <template <class, class, class, class> class Ptr  //3arg
         , typename A, class P0, class P1, class P2
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2>, U, 0u>
{  typedef Ptr<U, P0, P1, P2> type;   };

template <template <class, class, class, class, class> class Ptr  //4arg
         , typename A, class P0, class P1, class P2, class P3
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3> type;   };

template <template <class, class, class, class, class, class> class Ptr  //5arg
         , typename A, class P0, class P1, class P2, class P3, class P4
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3, P4>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3, P4> type;   };

template <template <class, class, class, class, class, class, class> class Ptr  //6arg
         , typename A, class P0, class P1, class P2, class P3, class P4, class P5
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3, P4, P5>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3, P4, P5> type;   };

template <template <class, class, class, class, class, class, class, class> class Ptr  //7arg
         , typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3, P4, P5, P6>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3, P4, P5, P6> type;   };

template <template <class, class, class, class, class, class, class, class, class> class Ptr  //8arg
         , typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3, P4, P5, P6, P7>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3, P4, P5, P6, P7> type;   };

template <template <class, class, class, class, class, class, class, class, class, class> class Ptr  //9arg
         , typename A, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8
         , class U>
struct pointer_rebinder<Ptr<A, P0, P1, P2, P3, P4, P5, P6, P7, P8>, U, 0u>
{  typedef Ptr<U, P0, P1, P2, P3, P4, P5, P6, P7, P8> type;   };

#endif   //!defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template <typename Ptr, typename U>
struct pointer_rebind
   : public pointer_rebinder<Ptr, U, pointer_rebind_mode<Ptr, U>::mode>
{};

template <typename T, typename U>
struct pointer_rebind<T*, U>
{  typedef U* type; };

}  //namespace container {
}  //namespace boost {

#endif // defined(BOOST_INTRUSIVE_POINTER_REBIND_HPP)

/* pointer_rebind.hpp
gb9wKY/6Um8aWMqhpAJ/VcRfVfHnZ21PDT37CxJ/tcRfsPhrqezEn7/487K8p3GKPy9rO6rgOm9KfhRJfrxlbUcV+HtE/G0Rf49a/MVU4G+N+Fsr/tZZ21EF/p4Rf/vE37MWf8kV+Nsv/l4Qfy9a/GVU4O+o+HtX/L1n8Zdbgb+V4i9f/K2ytrsK/C0Vf7eLvzvEX5C654m/dC/DX0/Ex8vw94SU9065TxyEm+Bh+BB8DW5T5QyfVOUMd8PX4XPwbfiySi8sUumF78L34Qn4Afw7PA5PwxPwR/gx/Bf8BHoTuU+hPzwJQ+HnMBx+CRvDUzASfgU7wH/AbvAbeA38Fg6AJXAY/AGOhj/CJPgTHA9/hjfDc3AG/BXeCs/DpfA3eCf8HeZDJ/m4EXrBzdAHboNV4E5YFe6GfnAfrAZfgDXhyzAIvgVD4PswGH4IQ+H3MAz+BOvBX2E4PA8bQ1/KqAmsDpvCOvByGA6bw1awFewO28BesDPsDSPhjbATHA+j4WRlL/ViAFLYOMg8L3u/zAX0kPq0TurFfbCu6p9hfbgBdoEbVf6rflT6iRLluIkR3icSnnL/uYQ3EXe14FQYCjNgQ3izjEsy4dUwG/aGq1W5whkwFs6Ew2EOvAHOhclwHkyF8+EEuABmwMUwBy6B81W7gItUu4B3wWVwJVyu6rVcbye8Bx5Q7RAehPnwqGqH8Bi8F34s7s3+samR7kCbdtlH8rEvDID9TH+I+Ktp4+8bac/fwhrwO8t9P0781bO57/8dd079TGOMS7+CYfBry/gxQ/yH24wfe8h1r4IqvlfDYNgT1lP+rf1RBemeKeHkSDizLPWuQPw1tKl3cyT+t8p158I6otcT/TJV7tb7dQXx6Cn5HyP538s6/q3AXyPxFyH+GkNX/EvEXxOb+H8g6f4QqnBPwCDVJmAt1e/BxqKb9aeZEV6ITTxulPBukueLJOt9spnn+AdI/AMl/tUt6Y6rwF+o+Ksj/upaxg3JzTyPG85XNfz9VtVyf6wgXWMlXeMkXSnWeiX+Qm38DZT4DYN6rx9LugrFX5iNv4lyvTRYF06y1p8KrjdCrpcg1xtlHbdVkI93yfVWSP3Ps1zPcblnfwvE30Lxt8jiL+hyz/3F+1UMf8dgDVUPIf50IUWJvzfk/n8VckbeV5zAnQrjNOyg0gS7wx+gcvcj7Ad/grHwLIyD38MRcCjlPRb+ij5J1QM4RdUDOB3+Dm8V8ztUdHC/BlaFm2A1+KCqU/AJGABVf1wLPg2D4V5YGz4DQ+ABGAqLRD8m+nHoLe9DfOBnsD78O2wEv4ON4VnYBP6u8g86nRQJrAJbwBDYGl4G28Is2B7OgFFwLewAN8COsAB2h5thV1go+kHYBb4p+mewBzwFr1LX86INy/uRPvJ+pC9sD1W+Xg37wRjYHw4U8wQ4EM6Dg+AdYr5WzO8T861i/oOcZ7K/pVEPPpX6UwfZJ/VnKu70uw6ozLNgA1WPYUM4HXaFM1Q84Ew4BM6Bo8V+IlwMM+ASea+1FC6Hy2AeXA7XwTtVuUv4m2EOVHG5Bb4o5i/BXPghvA0WK3NJTxxS3MpIzwJJT1Wkj6TnWtz5w+FQmY2AA0RPEX2i6PNEN/uf1ka4dW3a2XXSz10v+ZRgeV9UKP5W2rwvSpT4JMFgmAwj4FgYDVNgb5gq8RyvyhlOgjfAyTAJToCpcCKcLvY5Yj9H9BVKl3iptpHRxohXY6eOl7x3lX7bYZT7b7AKxKGOnxO2gHVgB+UHdoHtnUY9qAKv0nPcRn2oDgfDEDgNhsOZsCF8SfypdtsEvg+bOo12ejk8BSOdRnzbwn+K+/NyfdUe68L6TiMehIm9jGd8qAc=
*/