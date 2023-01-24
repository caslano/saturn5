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
4puJjFmV2TrUyMc2XmPBwd6G9hHFs2RrMjuH7nnjmPjmc2maPclIQZMA4bwumC5bbYxXis1lKjYrzMC0cBgwyy8d7s4eIbD9SicpMC/BC/PwsI0QqElgwXRCCbGJ5+T9cfRDDCh3Bi6TZqVtX1T3sRe2ZF8PMvVJUK80MH1v5S3akwYq0FaiciyTZSYq2eXZMpnIWtHsuGJWLKL1SWAasxUF1z7lCE3BLpNnIVuof49hAegJPc4lWdqBFYvsCkqFH9L8q6O2QKmfA3U5I+N1IWbEBEZ8vbnUbeOL77kMgElkIzXPEZYvfzPmj5mvGuYSa0Je+kJ+CwwjU5QNJSap/iZqa6FSqfN3lZQPxcVAv34hXqE62idfOT1c+RA4sOY2I+bvm1Xudgh8pbz4vtDFUv2FWXqfYlr8i8t380k8LpLLrtn0mKA+j2+TujVNRG8vFb0TwAjlaZWyyZvPgtVFza9H5uWrX5ag+cyJw/ZVkYuusVezRPHr08wLXXaPcH0VC/HmUWeb1fOrpcTqC4+3VmylEPSwR7IDt3N+a3NON/3uPKBoQVah/m7tJc3hIU0Vmwo74OehOLd2owo75X/5ZjAA6Oj1Kxv798NWROWVQZroKg3idy6MFJnIV1PtsS+rjUZNpJteRaISlbyHL4Z607jn6LGy0ewTRtkGAMWU+v29SZyJbgJWldgXEwpJZtz9MTqmOulpo8WE6ex1
*/