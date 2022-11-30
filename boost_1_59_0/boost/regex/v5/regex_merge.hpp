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

#ifndef BOOST_REGEX_V5_REGEX_MERGE_HPP
#define BOOST_REGEX_V5_REGEX_MERGE_HPP


namespace boost{

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

} // namespace boost

#endif  // BOOST_REGEX_V5_REGEX_MERGE_HPP



/* regex_merge.hpp
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
*/