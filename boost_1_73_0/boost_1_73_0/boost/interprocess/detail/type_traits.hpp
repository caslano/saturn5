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
yRw7fjkmJu1FcHSmP/T7p3vZZBDZhHSJRA8sg3zYhiVEWkzyUUUiDDKQjDoFZmj9cGr9/lVvfqrXvcgmh9hmpEsmfoAZZMU+PHHSYxeYUjJiFYssSaSEXR7GqQCVgN41MYjmkKwzpMjbpKAbPYANaLN1P2/0GWdKKRpRQDJMsyUeQxMkNUY5qSMZJllIR3+LmVPKhhSQEPPsidcQRUpxG8EpJit28ciTSGr4ZWKdEljBKJ71Pm+78pGqCeHIpxtYgkz4DEuItJjko4pEGGQgGXVG+526GemSYbLd/IYnTnrsAlNKRqxikSgJ7+9UnnvMTVLxX+x8SuizdD1f1Od2zDvKbOFjm5AukeiBZZAP27CESItJPqpIhEEGslBPibM8ZFNhKQG9rVcFUzYiBfktVwV5DU2Q1BjlpI5kmGQhHf0tvApVVwWzDDKTzFTyLVhXBZPvVUxW7OKRKpFMXkbkbZLlkMHTYOt+3ugzehspGlFAMkweB4+hCZIao5zUkQyTLOShnxpvmQinxJQviq3mLMjWP6TXjYntvi6F3X4xrAfNWA20/TLRh+3/do8OTn4++Lz/fvfgaP/9/v6H7vuj7i+77486Px/90v35w8lR9/P/Zs/375m2cm1Z7oU2Is5YG5C2oT8MJrbRai6f
*/