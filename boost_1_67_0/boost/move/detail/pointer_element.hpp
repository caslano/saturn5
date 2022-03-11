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