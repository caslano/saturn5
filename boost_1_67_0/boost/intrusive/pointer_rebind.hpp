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