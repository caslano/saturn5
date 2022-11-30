/*
 *
 * Copyright (c) 1998-2005
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_workarounds.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares Misc workarounds.
  */

#ifndef BOOST_REGEX_WORKAROUND_HPP
#define BOOST_REGEX_WORKAROUND_HPP

#include <boost/regex/config.hpp>
#include <algorithm>
#include <stdexcept>
#include <cstring>

#ifndef BOOST_REGEX_STANDALONE
#include <boost/detail/workaround.hpp>
#include <boost/throw_exception.hpp>
#endif

#ifdef BOOST_REGEX_NO_BOOL
#  define BOOST_REGEX_MAKE_BOOL(x) static_cast<bool>((x) ? true : false)
#else
#  define BOOST_REGEX_MAKE_BOOL(x) static_cast<bool>(x)
#endif

/*****************************************************************************
 *
 *  helper functions pointer_construct/pointer_destroy:
 *
 ****************************************************************************/

#ifdef __cplusplus
namespace boost{ namespace BOOST_REGEX_DETAIL_NS{

#ifdef BOOST_REGEX_MSVC
#pragma warning (push)
#pragma warning (disable : 4100)
#endif

template <class T>
inline void pointer_destroy(T* p)
{ p->~T(); (void)p; }

#ifdef BOOST_REGEX_MSVC
#pragma warning (pop)
#endif

template <class T>
inline void pointer_construct(T* p, const T& t)
{ new (p) T(t); }

}} // namespaces
#endif

/*****************************************************************************
 *
 *  helper function copy:
 *
 ****************************************************************************/

#if defined(BOOST_WORKAROUND)
#if BOOST_WORKAROUND(BOOST_REGEX_MSVC, >= 1400) && defined(__STDC_WANT_SECURE_LIB__) && __STDC_WANT_SECURE_LIB__
#define BOOST_REGEX_HAS_STRCPY_S
#endif
#endif

#ifdef __cplusplus
namespace boost{ namespace BOOST_REGEX_DETAIL_NS{

#if defined(BOOST_REGEX_MSVC) && (BOOST_REGEX_MSVC < 1910)
   //
   // MSVC 10 will either emit warnings or else refuse to compile
   // code that makes perfectly legitimate use of std::copy, when
   // the OutputIterator type is a user-defined class (apparently all user 
   // defined iterators are "unsafe").  What's more Microsoft have removed their
   // non-standard "unchecked" versions, even though they are still in the MS
   // documentation!! Work around this as best we can: 
   //
   template<class InputIterator, class OutputIterator>
   inline OutputIterator copy(
      InputIterator first,
      InputIterator last,
      OutputIterator dest
   )
   {
      while (first != last)
         *dest++ = *first++;
      return dest;
   }
#else 
   using std::copy;
#endif 


#if defined(BOOST_REGEX_HAS_STRCPY_S)

   // use safe versions of strcpy etc:
   using ::strcpy_s;
   using ::strcat_s;
#else
   inline std::size_t strcpy_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
	  std::size_t lenSourceWithNull = std::strlen(strSource) + 1;
	  if (lenSourceWithNull > sizeInBytes)
         return 1;
	  std::memcpy(strDestination, strSource, lenSourceWithNull);
      return 0;
   }
   inline std::size_t strcat_s(
      char *strDestination,
      std::size_t sizeInBytes,
      const char *strSource 
   )
   {
	  std::size_t lenSourceWithNull = std::strlen(strSource) + 1;
	  std::size_t lenDestination = std::strlen(strDestination);
	  if (lenSourceWithNull + lenDestination > sizeInBytes)
         return 1;
	  std::memcpy(strDestination + lenDestination, strSource, lenSourceWithNull);
      return 0;
   }

#endif

   inline void overflow_error_if_not_zero(std::size_t i)
   {
      if(i)
      {
         std::overflow_error e("String buffer too small");
#ifndef BOOST_REGEX_STANDALONE
         boost::throw_exception(e);
#else
         throw e;
#endif
      }
   }

}} // namespaces

#endif // __cplusplus

#endif // include guard


/* regex_workaround.hpp
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
*/