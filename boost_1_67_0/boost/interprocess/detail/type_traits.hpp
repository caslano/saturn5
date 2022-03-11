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