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
TElgSoshdj0VagAMlATUy1qUGqm/wnDOdd50qebvry1F+lpkwbY/YSIFkgkr77zQE7P8sZkYz1umGWp5E4FlixOcmTMtTK3uvS8eIXp1r+qCUzff9S+eAvC627vZ3p5z7rybUe+EE/xYvSAfD74Iku6xi/5jIv2jD1jiRPzJpPYZ5Q1Hs3PmFL64CBZ8KK7TJ/Y5PAuM/fv++tFdJzfYGDiJhjcA+fNApTPgucvkUQTrN8reNXwn6q4rOvkS82/feDOFbW6gb69gdoNLk+imnYYgBe9f6cQeCLvBztoSl+s9DsFw5l3g9r3MrkMSXjecL9RB8y280r/59wYqxGDXXcZQr/XtkxfGV+1gyCKcLVD4w4P+5rcH+wdnqaOvSOPZnQiURh06rw1zcNpoeNJg5ndgDYv6KZZOc+BjfKoRS/Bf2yB1Xi/cYJBLuNHfiDsxm1OY8P8u1v+Xwu0/s+eY3iQDX8D1/LpxNEx1LODeq4F/hM/XdGMTBsmnj5QBaiuOLHNyjpEdSVrThcUC5hfjTXH8BlMtHwZz+XqDfkQrdAeLU6UVYDYUoiKg/YHG5V1Q2CD6N4kbOTUUhUXJ+QWSujSjm2SmAL0PuD4R/LW2tMR7I7w/NupV7nU1o2DkuzFj0yk7M2z49/h5Q0mJklVCYbBobtbG4MGNofNryB5KmTe+lfF60oknc1/mwT/i56zIf4ufK3CtKRa6RbmL
*/