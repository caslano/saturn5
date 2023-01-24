//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP
#define BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

// MSVC-12 ICEs when variadic templates are enabled.
#if    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && (!defined(BOOST_MSVC) || BOOST_MSVC >= 1900)
   #define BOOST_INTRUSIVE_VARIADIC_TEMPLATES
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_INTRUSIVE_PERFECT_FORWARDING
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_INTRUSIVE_IMPDEF(TYPE) TYPE
#define BOOST_INTRUSIVE_SEEDOC(TYPE) TYPE
#define BOOST_INTRUSIVE_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_INTRUSIVE_I ,
#define BOOST_INTRUSIVE_DOCIGN(T1) T1

//#define BOOST_INTRUSIVE_DISABLE_FORCEINLINE

#if defined(BOOST_INTRUSIVE_DISABLE_FORCEINLINE)
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(BOOST_INTRUSIVE_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#else
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

/* workaround.hpp
gknVzDCn/JwhfeFTgiepONpzQkr0do6zz+t1NnN7WFvYE9GeH4ZCMifLLRS20zbp6l2Wu0dH3ERMW+4tpBifxzFmS5F2/CQsVT35R78h4kz/wj+KeOWozCcRUOcF+dw/ewlW/zbxZf062XkY5MJVq15jQ2lFk7tu+NGdGyJKZ9qQODV/1dBYuQ565wAcdoDlOJigc13od/2ErPpKjha/gG90ryfrJ6bb9+Wtx0POIoKVSZvNe+6pP6K0avQR0UG/dYchxsFXLtuiWDSW/TempzZRB0MYaKmYZnum0nW7y4/a8sWvhdZtjp+rIg9cRi7SC0qu+qjiHps7CZ/w/VQNcYS1t9NZruP0ooRYQAD+7awbn9XYVDHpw7x8d0a2CDrHfDLeDWWobGOoR6+d+/FcEMcGc+wz3WkIw6M3i/0NPTz6NWYzRFXsTQIOU3jA1lD252N/r9Y0Efkp6r18Bh3cBygpuoaz6npyI8OYmqaxoH2CRi9lC0PrZq4S3Zz3KdNeJIPgFyLFZV8JopaQt3dDZ75neOVFuYuGqrOrYynleeh76r0uy6ElDPL5iX7mCD9OHmIa1ZRoJtOIDLrDSJe6L98jKwaYOUmcSJxApTTsBrJ0jHFEJgp9DkFrSM+u23M607Q73EGm1KaKpXKxeMuYpuG/v5B/ihCfBG/oONWE0ZI80lQRnPWTfsE9xE+LlBwPQrG8uP5Q+vScKuGk
*/