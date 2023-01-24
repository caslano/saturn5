//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Modena C++ standard library (comes with KAI C++)

#if !defined(MSIPL_COMPILE_H)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__MSIPL_COMPILE_H)
#      error "This is not the Modena C++ library!"
#  endif
#endif

#ifndef MSIPL_NL_TYPES
#define BOOST_NO_STD_MESSAGES
#endif

#ifndef MSIPL_WCHART
#define BOOST_NO_STD_WSTRING
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "Modena C++ standard library"






/* modena.hpp
NOsfHyfBpCo+6wg8hDGgi3ALdrLxvxxz9pDG42SDPu//t7MR0c6rMLvI50MlM9/qcw08p9KXw3t+7XDEzvl6KUnWbSLVyu1R1nEX74nznndCBHFjXQ4O27edWjnE4LYRTmTkzu18juShL24nmVSnUYeWCth+udMQv9A2xNmo2VdarT41V/CeLUWNGsYCsXmV7DDa/o9JrEBwDgfFuk/YMe944btqj9r0X10/xj1u0W1QJFL8tqkoaS2UDkSCc+APKYDfP87PldyLx3rssbrJm5tIyUfw5j1HQAcJiNw/2yhhi3V5Ry4VnTz9XalLPz0Trl8ICe6i+/urfIJw0pD5PFSzCoBfPTGFUt8VrSndVm/CqK95WDE26p7lkJ/lQdSu7zr/YYLX9sCeP28zow8tLeD2cVhh5+kwDNCX0jA659nR9x3JcYHnn6xkdMi/nkq1GalUUXKEK34aSF0qJ9il3xxyVEdmjKUGjvlVOvhjxlIV2/8Kqn2zzsRk9PAijSIBzQkqSVa5SCdnd6LcjCtlCWdnoRn2JyKdvB52SC4ctnOyUX57INM4MrLB/CVcmUteMppMjaY7OHiCQ8+4CHWtvW910xMPeEM5fEuefqIJnkrFheYLSHfbFVoTe7sDTbWigem6NysWdcVRxFkr5+v28d0tKyaHMkPk3t7Vzqfv3yU3O00+tdnoPJtEqBei+FLM3fBC8O8pEMmM90Vk
*/