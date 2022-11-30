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
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
*/