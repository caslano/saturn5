/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_MSVC

   #pragma warning (push)
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4996) // "function": was declared deprecated
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4521) ////Disable "multiple copy constructors specified"
   #pragma warning (disable : 4127) //conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4267) //conversion from 'X' to 'Y', possible loss of data
   #pragma warning (disable : 4541) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4512) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4706) //assignment within conditional expression
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4714) // "function": marked as __forceinline not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
#endif

//#define BOOST_INTRUSIVE_USE_ITERATOR_FACADE
//#define BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE

/* config_begin.hpp
H+fUZ4QhpdCEuk5F3TzuhqaC/kiFt5yJ53XsB/iDlbMoJ9Ty7VomyEeDLji0XY1c6klDgi8sZyJfmSalxhP2qDAloEMTXEziADBOWuzY7wG4ubEPl0tf8DtgBcfKidSu+TVQ8/zOOULvSrtdz9dgSdVqaUuu2lLYt5+LZh/9DsaB8JVWsLNvhQVpbYVIo5m0WkXVXN6inCeSD9Q4JYsHG+J3ASaYbHwmnuLlYMHBqtm5E9DO3yHqxltJFMrOV+54a/RPAtZUyK0iuYXgargCKktUUWTArx375iUCdgCoiDCCsmb7izYbKvH9fyGp18r8hVXb8FinJBnIHDUe1DQAHpuD8YBVIfY1Ui7FVi8p7B9TNMo+N8YsGUJYTC19sVBXZYZ5uYywNYsSKIbhruROAOdV4kbfAibmJtxmxZiro+Klm5WGKbA620DPFRXfPZj0mxdIaYOdAiASSVA4sUOY1DA12H0rMnE64S3u4mnePrUTmZ8j8RrA8bePA7oNyr4POHzjuvYkbjv2JWU4fttOWuHqO8kUvzUIRVHXGpLF2wbiN+NCItN84RjoHg==
*/