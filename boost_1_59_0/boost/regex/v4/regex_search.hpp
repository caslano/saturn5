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
  *   FILE         regex_search.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_search implementation.
  */

#ifndef BOOST_REGEX_V4_REGEX_SEARCH_HPP
#define BOOST_REGEX_V4_REGEX_SEARCH_HPP


namespace boost{

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

template <class BidiIterator, class Allocator, class charT, class traits>
bool regex_search(BidiIterator first, BidiIterator last, 
                  match_results<BidiIterator, Allocator>& m, 
                  const basic_regex<charT, traits>& e, 
                  match_flag_type flags = match_default)
{
   return regex_search(first, last, m, e, flags, first);
}

template <class BidiIterator, class Allocator, class charT, class traits>
bool regex_search(BidiIterator first, BidiIterator last, 
                  match_results<BidiIterator, Allocator>& m, 
                  const basic_regex<charT, traits>& e, 
                  match_flag_type flags,
                  BidiIterator base)
{
   if(e.flags() & regex_constants::failbit)
      return false;

   BOOST_REGEX_DETAIL_NS::perl_matcher<BidiIterator, Allocator, traits> matcher(first, last, m, e, flags, base);
   return matcher.find();
}

//
// regex_search convenience interfaces:
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
//
// this isn't really a partial specialisation, but template function
// overloading - if the compiler doesn't support partial specialisation
// then it really won't support this either:
template <class charT, class Allocator, class traits>
inline bool regex_search(const charT* str, 
                        match_results<const charT*, Allocator>& m, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(str, str + traits::length(str), m, e, flags);
}

template <class ST, class SA, class Allocator, class charT, class traits>
inline bool regex_search(const std::basic_string<charT, ST, SA>& s, 
                 match_results<typename std::basic_string<charT, ST, SA>::const_iterator, Allocator>& m, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   return regex_search(s.begin(), s.end(), m, e, flags);
}
#else  // partial overloads:
inline bool regex_search(const char* str, 
                        cmatch& m, 
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(str, str + regex::traits_type::length(str), m, e, flags);
}
inline bool regex_search(const char* first, const char* last, 
                  const regex& e, 
                  match_flag_type flags = match_default)
{
   cmatch m;
   return regex_search(first, last, m, e, flags | regex_constants::match_any);
}

#ifndef BOOST_NO_WREGEX
inline bool regex_search(const wchar_t* str, 
                        wcmatch& m, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(str, str + wregex::traits_type::length(str), m, e, flags);
}
inline bool regex_search(const wchar_t* first, const wchar_t* last, 
                  const wregex& e, 
                  match_flag_type flags = match_default)
{
   wcmatch m;
   return regex_search(first, last, m, e, flags | regex_constants::match_any);
}
#endif
inline bool regex_search(const std::string& s, 
                        smatch& m,
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(s.begin(), s.end(), m, e, flags);
}
#if !defined(BOOST_NO_WREGEX)
inline bool regex_search(const std::basic_string<wchar_t>& s, 
                        wsmatch& m,
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(s.begin(), s.end(), m, e, flags);
}
#endif

#endif

template <class BidiIterator, class charT, class traits>
bool regex_search(BidiIterator first, BidiIterator last, 
                  const basic_regex<charT, traits>& e, 
                  match_flag_type flags = match_default)
{
   if(e.flags() & regex_constants::failbit)
      return false;

   match_results<BidiIterator> m;
   typedef typename match_results<BidiIterator>::allocator_type match_alloc_type;
   BOOST_REGEX_DETAIL_NS::perl_matcher<BidiIterator, match_alloc_type, traits> matcher(first, last, m, e, flags | regex_constants::match_any, first);
   return matcher.find();
}

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

template <class charT, class traits>
inline bool regex_search(const charT* str, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   return regex_search(str, str + traits::length(str), e, flags);
}

template <class ST, class SA, class charT, class traits>
inline bool regex_search(const std::basic_string<charT, ST, SA>& s, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   return regex_search(s.begin(), s.end(), e, flags);
}
#else  // non-template function overloads
inline bool regex_search(const char* str, 
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   cmatch m;
   return regex_search(str, str + regex::traits_type::length(str), m, e, flags | regex_constants::match_any);
}
#ifndef BOOST_NO_WREGEX
inline bool regex_search(const wchar_t* str, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   wcmatch m;
   return regex_search(str, str + wregex::traits_type::length(str), m, e, flags | regex_constants::match_any);
}
#endif
inline bool regex_search(const std::string& s, 
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   smatch m;
   return regex_search(s.begin(), s.end(), m, e, flags | regex_constants::match_any);
}
#if !defined(BOOST_NO_WREGEX)
inline bool regex_search(const std::basic_string<wchar_t>& s, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   wsmatch m;
   return regex_search(s.begin(), s.end(), m, e, flags | regex_constants::match_any);
}

#endif // BOOST_NO_WREGEX

#endif // partial overload

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

} // namespace boost

#endif  // BOOST_REGEX_V4_REGEX_SEARCH_HPP



/* regex_search.hpp
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
*/