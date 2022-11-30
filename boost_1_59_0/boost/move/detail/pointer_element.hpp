//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2017. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_POINTER_ELEMENT_HPP
#define BOOST_MOVE_DETAIL_POINTER_ELEMENT_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#ifndef BOOST_MOVE_DETAIL_WORKAROUND_HPP
#include <boost/move/detail/workaround.hpp>
#endif   //BOOST_MOVE_DETAIL_WORKAROUND_HPP

namespace boost {
namespace movelib {
namespace detail{

//////////////////////
//struct first_param
//////////////////////

template <typename T> struct first_param
{  typedef void type;   };

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   template <template <typename, typename...> class TemplateClass, typename T, typename... Args>
   struct first_param< TemplateClass<T, Args...> >
   {
      typedef T type;
   };

#else //C++03 compilers

   template < template  //0arg
               <class
               > class TemplateClass, class T
            >
   struct first_param
      < TemplateClass<T> >
   {  typedef T type;   };

   template < template  //1arg
               <class,class
               > class TemplateClass, class T
            , class P0>
   struct first_param
      < TemplateClass<T, P0> >
   {  typedef T type;   };

   template < template  //2arg
               <class,class,class
               > class TemplateClass, class T
            , class P0, class P1>
   struct first_param
      < TemplateClass<T, P0, P1> >
   {  typedef T type;   };

   template < template  //3arg
               <class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2>
   struct first_param
      < TemplateClass<T, P0, P1, P2> >
   {  typedef T type;   };

   template < template  //4arg
               <class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3> >
   {  typedef T type;   };

   template < template  //5arg
               <class,class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3, class P4>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3, P4> >
   {  typedef T type;   };

   template < template  //6arg
               <class,class,class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3, class P4, class P5>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3, P4, P5> >
   {  typedef T type;   };

   template < template  //7arg
               <class,class,class,class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3, class P4, class P5, class P6>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3, P4, P5, P6> >
   {  typedef T type;   };

   template < template  //8arg
               <class,class,class,class,class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3, P4, P5, P6, P7> >
   {  typedef T type;   };

   template < template  //9arg
               <class,class,class,class,class,class,class,class,class,class
               > class TemplateClass, class T
            , class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
   struct first_param
      < TemplateClass<T, P0, P1, P2, P3, P4, P5, P6, P7, P8> >
   {  typedef T type;   };

#endif   //!defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template <typename T>
struct has_internal_pointer_element
{
   template <typename X>
   static char test(int, typename X::element_type*);

   template <typename X>
   static int test(...);

   static const bool value = (1 == sizeof(test<T>(0, 0)));
};

template<class Ptr, bool = has_internal_pointer_element<Ptr>::value>
struct pointer_element_impl
{
   typedef typename Ptr::element_type type;
};

template<class Ptr>
struct pointer_element_impl<Ptr, false>
{
   typedef typename boost::movelib::detail::first_param<Ptr>::type type;
};

}  //namespace detail{

template <typename Ptr>
struct pointer_element
{
   typedef typename ::boost::movelib::detail::pointer_element_impl<Ptr>::type type;
};

template <typename T>
struct pointer_element<T*>
{  typedef T type; };

}  //namespace movelib {
}  //namespace boost {

#endif // defined(BOOST_MOVE_DETAIL_POINTER_ELEMENT_HPP)

/* pointer_element.hpp
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
*/