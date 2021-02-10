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
rFHB5GsVsxW7eaRaJJeXEXmZZDvk8DTYml+2+ozeRoZCFLAMk8fBo2uCrMZoJ3Usw2QLeepn1lumwhk15atip71Ksl18pOfNiO0+hdJuPxrWrWZsJ9p+nOuT7n9fn5y8Pf+ld/7y3cnxm5enJycfXr57ff7m5Wt69PX5Sb//7+P+/1b1L65ZlnJlWe5nbUqcmTYm3fHcNjrt8LFnfsPXDVocGkxnlu02/BLPms8PvvX8bORLzX04/H6xSjDuzWYtP1+5NaMFOc1GO6KbVJWJ7ily1nzx/CCk0eE/zw8CLQ9fnJ29yPJk8qIZKBcqK9AvdPD6aUa672YzQx8vPm+Zd/H18rKvDvlyd3E37t5RW9BhsPrsl/qg2drYJfaIuN2vpj62Jt5Y2Tz6LDRQFhnb9OiP49Pj9YAJjsaIX5ZwEQ/mUDFGxeSgO2TLKRuGHusNnBCNgoIZRiH04zQCoVneMQfFMo6yFF8bCqaMOejHcQRCs7xjDorFKpbrNwdQMEZBPM/xHIFwZzkIB4e24AQIzTJPebhhC8uG27UQbaFYumLQKPOoCmU1QLEkTwsaZfZGMapyxDygUo7IEEZWjsd8qJTDGcLIKpgL8vjmFLIVzASBhtmW9TDwuGaBQMGst27sj3agH3MGCNTLOfqg
*/