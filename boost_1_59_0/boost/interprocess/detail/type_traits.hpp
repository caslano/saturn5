//////////////////////////////////////////////////////////////////////////////
// (C) Copyright John Maddock 2000.
// (C) Copyright Ion Gaztanaga 2005-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP
#define BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct nat{};

template<class T>
struct remove_reference
{
   typedef T type;
};

template<class T>
struct remove_reference<T&>
{
   typedef T type;
};

template<class T>
struct is_reference
{
   static const bool value = false;
};

template<class T>
struct is_reference<T&>
{
   static const bool value = true;
};

template<class T>
struct is_pointer
{
   static const bool value = false;
};

template<class T>
struct is_pointer<T*>
{
   static const bool value = true;
};

template <typename T>
struct add_reference
{
    typedef T& type;
};

template<class T>
struct add_reference<T&>
{
    typedef T& type;
};

template<>
struct add_reference<void>
{
    typedef nat &type;
};

template<>
struct add_reference<const void>
{
    typedef const nat &type;
};

template <class T>
struct add_const_reference
{  typedef const T &type;   };

template <class T>
struct add_const_reference<T&>
{  typedef T& type;   };

template<class T>
struct remove_const
{
   typedef T type;
};

template<class T>
struct remove_const<const T>
{
   typedef T type;
};

template<class T>
struct remove_volatile
{
   typedef T type;
};

template<class T>
struct remove_volatile<volatile T>
{
   typedef T type;
};

template<class T>
struct remove_const_volatile
{
   typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

template <typename T, typename U>
struct is_same
{
   typedef char yes_type;
   struct no_type
   {
      char padding[8];
   };

   template <typename V>
   static yes_type is_same_tester(V*, V*);
   static no_type is_same_tester(...);

   static T *t;
   static U *u;

   static const bool value = sizeof(yes_type) == sizeof(is_same_tester(t,u));
};

template<class T, class U>
struct is_cv_same
{
   static const bool value = is_same< typename remove_const_volatile<T>::type
                                    , typename remove_const_volatile<U>::type >::value;
};

} // namespace ipcdetail
}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
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
*/