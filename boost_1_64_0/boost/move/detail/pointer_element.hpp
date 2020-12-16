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
wx0roc7W5k7afaJfT/Ro+vVFa5Ifc6KNdiHSd8VDq+JNDyTrEqFK9s9bSSkS06zwkykdtq0JyRRVR+riVYn6NGIOy58DamLZvOlpiJCd/gP0tip3XM4Yg3E50RiXf/NRGz9KPzxGKjFGMCCmYkCAn3TQPh03pYOb0uGLTk7OYsh8Allg3VQL5JlZpFHzJCLCDyTfV7AtYzPa0pCu2RJvWhUPPSDU/UVwmW0KSOko4TsxhOwsNYhrp8rUszMe2oYbbcgyj9rZQ+3c1lC4/eUZ7fei/fRDumpvLOiE868BdWrqr4Gy0ErCOBqmcMMQPl3CI8Z9OX1UW0+jzOaDpLumFKGVlMJXBQmjPTxgSwkvjnDWHkPtTxLNMqepJE7zlsBw54Ixb/9gfCYDjD97CIzp/zIYnlwwXi3eLxh7FCcYnwcY2HvJIqPcPqwvds4tJyFfK/JZdAkqS9MWIfO4sayZHiFz4oKkYRER6jNBFbA3NpjOCC37g+sPQzWVRjU7cZtMBarJT7KMPMUiwgjJuA/Q26rGnGZvLXM2+0qUu42wxdslR+aw1/WJ8Po5NDuTjUjyYkrjiVVkQRBvor3cNXzjQnIapfDFjs5BxWoqAfY4q+NlZAeSHJeT4KFE00PwNeJJ1mLw5WLj9z4n0h/FECzLmSdyAgpKKqaM0quR8MZSyBTuGNIrfTA0cC025k0N3xbOCkd8W2AnE5R7jKCzlis8I64cFJ9oAQt7GZVwQ8sg+MAutVYXgaNcwWlkq0Df6ule9R76PkPfho941ZEzvOrPKPwl+v6Avl+mr5fijqKvq6jIXSQfT5G3qMhH5bxEeebT9yv0fZq+g/R1+Qp/3PT14ME7Z9kbdeSH5UyvOkDfv1C9N37Uq55K/6/Fe8ir7qP/V1OaFIWNo/8/pvgJZ1Ea+rpG7//jHu3JDvLaj76i4hJldBEeR5SOHD3aP7p09KjSXe9+3v38F3zs+89cMscomIVSfNP6SXQJYBmHBc4rqk8frnLUs7LIGuq88xlUnnGz0LHMlyq148y1qTaZfvTgr53bO7yIMxbQxGES7lrPdbCwMraG3mvljSJv168kr9iHoPzAolRG5kCbzu/lCz84+MbggmvBbaspMaI9RXKsrdzcew+0YftaO8WsBBdu0wS5VTTK2EGC22e0BcX0SEV0oeS1Z8mdlZgW+w1IT7UgXQVITxFITVk8pFLB7KwfUwI2hlqWm7aHsjGUrNFOlyLMrUK5kFif9TdWdzrvKJhNoGEN7LHbfc0Mmttx1+VRPA/wpQRLyGOhX+whaWXBu6PJI4xof97ot0d59DZ8QE8PsP3vvrRzPyW0SubDNfJvvWVIh38b5d8y+bdSdHxVvEyrwnLEoO4gpsdVrGGn+Xtia7cnioBqUYKHJ7Y+RxanFFDJ+ScRScEQAgMiOCdwYlEHddA3/7Ftxg2U6R7uuUsorqibgq3S72HSnoXaYwEj50lFKo2la45DYAtZzFQ16nMCfK3Ts3dfRFO5mawNL1dbhZQYteCSz0nx0D0EERH9FhMijM3FObDdeD5AcqUFpMXXHoEUlOyTDAPnSYRXsuvSlclOjjQBtNJ+2pG2aSXLI5QWCIm9nxsGtMowvMcVo4vgVzIVVVXvjIerrseAKSmW+8irWNCoonTuWCmXjlKDwoD86bQ0nYVc/WLYLWxTnr1bE5S04T9gqwRsKPWHtHI0I/Q3HkvT1u0KgmdEC+AZwYOtql4fOZpRK3U8QIcnnq2o0s9FIKyLbiI4G/SXRhnoP9+oC/8TTSviTYv+GnhveFEitGirftRfA+f7f3oyo0JdLlBduJtQ+biUPYvKFtBTXJzCwuwDteGbrj6EymK8rUg=
*/