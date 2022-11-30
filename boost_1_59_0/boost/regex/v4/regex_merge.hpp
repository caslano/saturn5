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
  *   FILE         regex_format.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides formatting output routines for search and replace
  *                operations.  Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_V4_REGEX_MERGE_HPP
#define BOOST_REGEX_V4_REGEX_MERGE_HPP


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

template <class OutputIterator, class Iterator, class traits, class charT>
inline OutputIterator regex_merge(OutputIterator out,
                         Iterator first,
                         Iterator last,
                         const basic_regex<charT, traits>& e, 
                         const charT* fmt, 
                         match_flag_type flags = match_default)
{
   return regex_replace(out, first, last, e, fmt, flags);
}

template <class OutputIterator, class Iterator, class traits, class charT>
inline OutputIterator regex_merge(OutputIterator out,
                         Iterator first,
                         Iterator last,
                         const basic_regex<charT, traits>& e, 
                         const std::basic_string<charT>& fmt,
                         match_flag_type flags = match_default)
{
   return regex_merge(out, first, last, e, fmt.c_str(), flags);
}

template <class traits, class charT>
inline std::basic_string<charT> regex_merge(const std::basic_string<charT>& s,
                         const basic_regex<charT, traits>& e, 
                         const charT* fmt,
                         match_flag_type flags = match_default)
{
   return regex_replace(s, e, fmt, flags);
}

template <class traits, class charT>
inline std::basic_string<charT> regex_merge(const std::basic_string<charT>& s,
                         const basic_regex<charT, traits>& e, 
                         const std::basic_string<charT>& fmt,
                         match_flag_type flags = match_default)
{
   return regex_replace(s, e, fmt, flags);
}

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

#endif  // BOOST_REGEX_V4_REGEX_MERGE_HPP



/* regex_merge.hpp
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
*/