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
rUa92vc7Ltq+fw9khuDaORSXTX+87yLvi+cB6LvotC3jq1qtQV4cE+KAIIwLTdusEDJAfjdc/iG2WdLnXDefA8CPPredO3DW1CaMt9kleM4rzbIRc5fZg1REmcVdM5i8Qg3V6E89tXfD0g1CFf1SCbR6BQjlU9WIUqslvTF9hc/Qp/oieq2/PDBeCVYF6gwjsNEb06qhW0JAPki3NAY0pUjT9CJ69DA0/sfn9vgfn6f9q58y9UGwd4/tGIPGtgTRWJANxsJ+YMYWo/b/X5j2/wA0f0HuYsp8x+Ek5+WGtlnEichyXNhPrsmBaovVwJ3OVoJqEtpZoFWrMYUcqug45o3K9LpD6oE2uC07v7Ddd/gMZH7zBeOfnv/Ccksm9x3ejyX4ELvwMIOuauALfo5P7wuBzMi/MDxZf3GaBzA8jWgZx0N0Z2dHodEdPuB3nLqzqr9w+el7AMz+ixlfrLtY+KcsrrVnC6hfW4RLheluMUmvCCpAcwXGU3+b+sJm4qm7AZ3XReKfAFBwyfR14f16xn6DK9clCeV7i/hlhsvZDYyDA3LY2aeSN0yqn/a6oyi7v/nG/AfnxThX0t2wG88VP5RC8iZ1BQzhWr3U14I7gwnjo9BOQw82Be6NJKIXYjujeqQpXOjfr4e0CD14jYlhwUCtis/nJSZOXm8oZGhBLRaKahGUE5Bgr9Jgr1JRYP3I/pw2je6Fm0mTd8Dj
*/