//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_WORKAROUND_HPP
#define BOOST_CONTAINER_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)\
    && !defined(BOOST_INTERPROCESS_DISABLE_VARIADIC_TMPL)
   #define BOOST_CONTAINER_PERFECT_FORWARDING
#endif

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && defined(__GXX_EXPERIMENTAL_CXX0X__)\
    && (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__ < 40700)
   #define BOOST_CONTAINER_UNIMPLEMENTED_PACK_EXPANSION_TO_FIXED_LIST
#endif

#if defined(BOOST_GCC_VERSION)
#  if (BOOST_GCC_VERSION < 40700) || !defined(BOOST_GCC_CXX11)
#     define BOOST_CONTAINER_NO_CXX11_DELEGATING_CONSTRUCTORS
#  endif
#elif defined(BOOST_MSVC)
#  if _MSC_FULL_VER < 180020827
#     define BOOST_CONTAINER_NO_CXX11_DELEGATING_CONSTRUCTORS
#  endif
#elif defined(BOOST_CLANG)
#  if !__has_feature(cxx_delegating_constructors)
#     define BOOST_CONTAINER_NO_CXX11_DELEGATING_CONSTRUCTORS
#  endif
#endif

#if defined(BOOST_MSVC) && (_MSC_VER < 1400)
   #define BOOST_CONTAINER_TEMPLATED_CONVERSION_OPERATOR_BROKEN
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) || (defined(BOOST_MSVC) && (BOOST_MSVC == 1700 || BOOST_MSVC == 1600))
#define BOOST_CONTAINER_PAIR_TEST_HAS_HEADER_TUPLE
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_CONTAINER_IMPDEF(TYPE) TYPE
#define BOOST_CONTAINER_SEEDOC(TYPE) TYPE

//Macros for memset optimization. In most platforms
//memsetting pointers and floatings is safe and faster.
//
//If your platform does not offer these guarantees
//define these to value zero.
#ifndef BOOST_CONTAINER_MEMZEROED_FLOATING_POINT_IS_NOT_ZERO
#define BOOST_CONTAINER_MEMZEROED_FLOATING_POINT_IS_ZERO 1
#endif

#ifndef BOOST_CONTAINER_MEMZEROED_POINTER_IS_NOT_NULL
#define BOOST_CONTAINER_MEMZEROED_POINTER_IS_NULL
#endif

#define BOOST_CONTAINER_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_CONTAINER_I ,
#define BOOST_CONTAINER_DOCIGN(T) T
#define BOOST_CONTAINER_DOCONLY(T)

/*
   we need to import/export our code only if the user has specifically
   asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
   libraries to be dynamically linked, or BOOST_CONTAINER_DYN_LINK
   if they want just this one to be dynamically liked:
*/
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_CONTAINER_DYN_LINK)

   /* export if this is our own source, otherwise import: */
   #ifdef BOOST_CONTAINER_SOURCE
   #  define BOOST_CONTAINER_DECL BOOST_SYMBOL_EXPORT
   #else
   #  define BOOST_CONTAINER_DECL BOOST_SYMBOL_IMPORT
   
   #endif  /* BOOST_CONTAINER_SOURCE */
#else
   #define BOOST_CONTAINER_DECL
#endif  /* DYN_LINK */

//#define BOOST_CONTAINER_DISABLE_FORCEINLINE

#if defined(BOOST_CONTAINER_DISABLE_FORCEINLINE)
   #define BOOST_CONTAINER_FORCEINLINE inline
#elif defined(BOOST_CONTAINER_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_CONTAINER_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_CONTAINER_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_CONTAINER_FORCEINLINE inline
#else
   #define BOOST_CONTAINER_FORCEINLINE BOOST_FORCEINLINE
#endif

#if !defined(__has_feature)
#define BOOST_CONTAINER_HAS_FEATURE(feature) 0
#else
#define BOOST_CONTAINER_HAS_FEATURE(feature) __has_feature(feature)
#endif

//Detect address sanitizer
#if defined(__SANITIZE_ADDRESS__) || BOOST_CONTAINER_HAS_FEATURE(address_sanitizer)
#define BOOST_CONTAINER_ASAN
#endif


#if (__cplusplus >= 201703L)
   //CTAD supported
   #ifdef __INTEL_COMPILER
      //Intel compilers do not offer this feature yet
      #define BOOST_CONTAINER_NO_CXX17_CTAD
   #endif
#else
   #define BOOST_CONTAINER_NO_CXX17_CTAD
#endif

#endif   //#ifndef BOOST_CONTAINER_DETAIL_WORKAROUND_HPP

/* workaround.hpp
x/b/30ChP0XM1sTEuCZcfXEBrMzkZLa8YuxZsFrHuMNcjWRYtw0xsYPrlqxZsVbF2hXrVKxbsV7F+hWLKOZudzaLzMfMPM8OiyPzMptzQVYLLJnMz22KdR4sJOzNV0ObYIUi5/oR31fCyoR9eH7StRif1czeIOPbWAOZhxl/X7uJzGaWOXn6ElgHmY/Zzb+M3AjrF3F83s36NNrunfXuSFiQjOecumfhIlgKWYDZ9sNnN8NyRM4Tzz9xFqyQzMts0rZX3LAyYfMzLth6yGJc1WRYLm/y9U5Wq1i9Yo2KNSvWqli7Yp2KdZN5mZnfJYUNkPmZhU4sOx7m+yzaLvjLvD2wJDKe03f/zj/B0sl8zMx8MiyXzGKWOmvkHlgBmc2s/63Fl8DKRM6urHeehtUKe9Ez4xRYi6jz8geODMI6Rdzxp1YPxXgZYHWuJduQNv0NmOfzwTobaf/JvzUQcDL6k0SGdfQWO24aSxFmzm1gaUpchmJZSs5sxXIVy1esQLEixUoUK1Osgsxixo+NNYo1kNnMzDwf9q1tZBgTb9P6M9e3sF6Tk5k5n4BFTE5msZtXdcPsjmh7ZWG4ChZP5md2kfvCDbB0YWUPL14AyyPjtZjzEFihYqWKVSpWS+Zhxo+N9czeEcfNRpaziZ8vmX0di3uXLGpfp1inYt2K9SrWr1hEMfcXzmYpZivmVyyoWLxiiYolK5aqWLpimYqFFMtRLE+xsGKFihUrVqpYuWKVilUrVqtYvWKNijUr1qpYu2KdinUr1qtYv2IRxdxbnM1SzFbML8ycJ8OCZBZM7M8SlZzJjnaYK5XZOrH/TCfzwvi5G1m2iDPHRlgumY+ZmQOEFZNZzPh+vlzkNPN8sEoye9DYPW/6fxa3XpyHNCrWrFirYu2KdSrWrVivYv2KRRRzf+lslmK2Yn4yi9ljH80eCYsns5lZ9rx7YKnCqlKrx8BCZH5mob5142GFwva89dcpsEqyALPj5o+/GNYk2ruxZ8TTsA4yL7NPk49eDusl8zE7fvZlp8E8ndE5z3+loAcWIOO1jLv5t2ZYKhlvb++SZ/bAsoTNf2D9W7A8Mh+vs27UE7ASMouZ2Y5gFWQemDhvrWIm122NYnVKzgbFmkSdeZc8eQOsTSzP3ScMbIf1CLv88jErYK6vnHN6yZxyxjGTOVPIfMzMuTcsRObUvxxmcpnlKXFhMi8zs2+FlYg6H8tsGQOrEta7OH0HrEHkNL+BDmvl/cP8IJY1mdNYGlDqtLZGb5ttz2ZdhmNOPBn63hxzWPT5oGLJiqUqlq5YpmIhxXIUy1MsTOZlxuc8SsgsZubaEFYhjB/fa5S4BjKbmbnuh7WR+ZjdHXm6Htar5IwoZm2L7p+Z54MFyHgtM+5Y+issicypf2nMZHtZZB5mZjuCZSu1hJWcxYqVK1bt1Af6W8/6voGtB2OtinWT+QaNbZv0Xxe1x4xvm14yLJeN7LrYmE+xgGJxiiUolqRYimJpimUolqVYNpnNLOG0oxfBCoSdvuu972FlZF5m5tv0sGoR98Rb9iuwRjIfM3O+C+tQrF+0t+Cr/Lkwz/bo9vZ+N2wVLEDGc17Z87IbliziznkwLQ6WScbbywna/4XlkgWYXfDhh6/CSkV7ybeuXAWrIbOYWe3P/wRrELV8VdA2AtYmctpDp/4K6xX2t/3fr4F5vo7uww+vl5XC/GQBvo7e/3c9LIXMaT2EhJn7K7ACMhsm5lTLRC1m3wOrdrTDXA1kGLvv8Wsu+tvEammhOPO+IayTzGLG7yn2ktnMtv/eeRTMvYNqYca/1+wj4+0Nf722CZZI5mc2+NssdEwlQx/eF3P+IWF8f52jxOWZWpjt3bY=
*/