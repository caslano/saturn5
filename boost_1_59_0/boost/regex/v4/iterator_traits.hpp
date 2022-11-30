/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         iterator_traits.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares iterator traits workarounds.
  */

#ifndef BOOST_REGEX_V4_ITERATOR_TRAITS_HPP
#define BOOST_REGEX_V4_ITERATOR_TRAITS_HPP

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

namespace boost{
namespace BOOST_REGEX_DETAIL_NS{

#if defined(BOOST_NO_STD_ITERATOR_TRAITS)

template <class T>
struct regex_iterator_traits 
{
  typedef typename T::iterator_category iterator_category;
  typedef typename T::value_type        value_type;
#if !defined(BOOST_NO_STD_ITERATOR)
  typedef typename T::difference_type   difference_type;
  typedef typename T::pointer           pointer;
  typedef typename T::reference         reference;
#else
  typedef std::ptrdiff_t                difference_type;
  typedef value_type*                   pointer;
  typedef value_type&                   reference;
#endif
};

template <class T>
struct pointer_iterator_traits
{
   typedef std::ptrdiff_t difference_type;
   typedef T value_type;
   typedef T* pointer;
   typedef T& reference;
   typedef std::random_access_iterator_tag iterator_category;
};
template <class T>
struct const_pointer_iterator_traits
{
   typedef std::ptrdiff_t difference_type;
   typedef T value_type;
   typedef const T* pointer;
   typedef const T& reference;
   typedef std::random_access_iterator_tag iterator_category;
};

template<>
struct regex_iterator_traits<char*> : pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<const char*> : const_pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<wchar_t*> : pointer_iterator_traits<wchar_t>{};
template<>
struct regex_iterator_traits<const wchar_t*> : const_pointer_iterator_traits<wchar_t>{};
//
// the follwoing are needed for ICU support:
//
template<>
struct regex_iterator_traits<unsigned char*> : pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<const unsigned char*> : const_pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<int*> : pointer_iterator_traits<int>{};
template<>
struct regex_iterator_traits<const int*> : const_pointer_iterator_traits<int>{};

#ifdef BOOST_REGEX_HAS_OTHER_WCHAR_T
template<>
struct regex_iterator_traits<unsigned short*> : pointer_iterator_traits<unsigned short>{};
template<>
struct regex_iterator_traits<const unsigned short*> : const_pointer_iterator_traits<unsigned short>{};
#endif

#if defined(__SGI_STL_PORT) && defined(__STL_DEBUG)
template<>
struct regex_iterator_traits<std::string::iterator> : pointer_iterator_traits<char>{};
template<>
struct regex_iterator_traits<std::string::const_iterator> : const_pointer_iterator_traits<char>{};
#ifndef BOOST_NO_STD_WSTRING
template<>
struct regex_iterator_traits<std::wstring::iterator> : pointer_iterator_traits<wchar_t>{};
template<>
struct regex_iterator_traits<std::wstring::const_iterator> : const_pointer_iterator_traits<wchar_t>{};
#endif // BOOST_NO_WSTRING
#endif // stport

#else

template <class T>
struct regex_iterator_traits : public std::iterator_traits<T> {};

#endif

} // namespace BOOST_REGEX_DETAIL_NS
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4103)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif


/* iterator_traits.hpp
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
*/