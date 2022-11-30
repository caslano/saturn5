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
  *   FILE         regex_match.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Regular expression matching algorithms.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */


#ifndef BOOST_REGEX_MATCH_HPP
#define BOOST_REGEX_MATCH_HPP

namespace boost{

//
// proc regex_match
// returns true if the specified regular expression matches
// the whole of the input.  Fills in what matched in m.
//
template <class BidiIterator, class Allocator, class charT, class traits>
bool regex_match(BidiIterator first, BidiIterator last, 
                 match_results<BidiIterator, Allocator>& m, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   BOOST_REGEX_DETAIL_NS::perl_matcher<BidiIterator, Allocator, traits> matcher(first, last, m, e, flags, first);
   return matcher.match();
}
template <class iterator, class charT, class traits>
bool regex_match(iterator first, iterator last, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   match_results<iterator> m;
   return regex_match(first, last, m, e, flags | regex_constants::match_any);
}
//
// query_match convenience interfaces:
//
template <class charT, class Allocator, class traits>
inline bool regex_match(const charT* str, 
                        match_results<const charT*, Allocator>& m, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   return regex_match(str, str + traits::length(str), m, e, flags);
}

template <class ST, class SA, class Allocator, class charT, class traits>
inline bool regex_match(const std::basic_string<charT, ST, SA>& s, 
                 match_results<typename std::basic_string<charT, ST, SA>::const_iterator, Allocator>& m, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   return regex_match(s.begin(), s.end(), m, e, flags);
}
template <class charT, class traits>
inline bool regex_match(const charT* str, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   match_results<const charT*> m;
   return regex_match(str, str + traits::length(str), m, e, flags | regex_constants::match_any);
}

template <class ST, class SA, class charT, class traits>
inline bool regex_match(const std::basic_string<charT, ST, SA>& s, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   typedef typename std::basic_string<charT, ST, SA>::const_iterator iterator;
   match_results<iterator> m;
   return regex_match(s.begin(), s.end(), m, e, flags | regex_constants::match_any);
}


} // namespace boost

#endif   // BOOST_REGEX_MATCH_HPP


/* regex_match.hpp
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
*/