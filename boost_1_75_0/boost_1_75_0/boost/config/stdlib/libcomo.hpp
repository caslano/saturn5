//  (C) Copyright John Maddock 2002 - 2003. 
//  (C) Copyright Jens Maurer 2002 - 2003. 
//  (C) Copyright Beman Dawes 2002 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Comeau STL:

#if !defined(__LIBCOMO__)
#  include <boost/config/no_tr1/utility.hpp>
#  if !defined(__LIBCOMO__)
#      error "This is not the Comeau STL!"
#  endif
#endif

//
// std::streambuf<wchar_t> is non-standard
// NOTE: versions of libcomo prior to beta28 have octal version numbering,
// e.g. version 25 is 21 (dec)
#if __LIBCOMO_VERSION__ <= 22
#  define BOOST_NO_STD_WSTREAMBUF
#endif

#if (__LIBCOMO_VERSION__ <= 31) && defined(_WIN32)
#define BOOST_NO_SWPRINTF
#endif

#if __LIBCOMO_VERSION__ >= 31
#  define BOOST_HAS_HASH
#  define BOOST_HAS_SLIST
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_EXCEPTION
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

//
// Intrinsic type_traits support.
// The SGI STL has it's own __type_traits class, which
// has intrinsic compiler support with SGI's compilers.
// Whatever map SGI style type traits to boost equivalents:
//
#define BOOST_HAS_SGI_TYPE_TRAITS

#define BOOST_STDLIB "Comeau standard library " BOOST_STRINGIZE(__LIBCOMO_VERSION__)

/* libcomo.hpp
PzTAjliOxsBZJ/fXeTYPUxr+37htuOAQXwGzo52AeQZP0jnW/HOoVoCWu2InqdVxlgGHggyBnu1iUfxyfeomuivPbfs0OrUm2IXBwvPYebuKDXHuTHvenrhhRfmMsc7S7JSc2MW4tRHPTsHn+Nfe+PJnQaNOWOWl68CxAnHl384WnxvnV8r3TxHjwrp6Dv1qwwQgvEeDiwzNxIrbFi5WiJUbxi8szPOPqTROn4Xc+2B9beH0u0rHev8v7Q+SJs40/0yPNpZMbuVDtQnuGfH8On3Y9chY8kmshsOoV0rCmyAK2P0VV3cdmg2MNIu3BCVuHOF35RD37jGOju7guPsoLHq/VXnZ2d0p/FL4KtXX7u1dR9zvdL/i4uceumffyug+wP1MuZWg89hT54XXhw8fCj/oeFr5en/g/0Ddbx93lUhMDW6IWd+NQR+Nl9uC1/vjdib9I8cI/boSwsMb5h1N0Lsiur4UdehQl9aKFHPj+LvrzdezBAm8lZFX0q9Wb7iek4tzvL91TZ5089nWEiNdSAd1bjv4uyE/NGXol108r82k20lRS1wf3WEiKjXT2l4HdXlpKkQZBX+7E0Mcx/mjnRz2gKsNiTztFUo3mMlEkcGXib/OTIIi3MvoVyM3/LtkYKJrecZH9d1gn74Hh4WQ3P5ypbEiiFGBtcVAiXsu70vT3mtraCoPUFGCgYrVkU9CMfsxwarcDEUpKmOj
*/