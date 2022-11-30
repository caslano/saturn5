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

#ifndef BOOST_REGEX_V5_REGEX_SEARCH_HPP
#define BOOST_REGEX_V5_REGEX_SEARCH_HPP


namespace boost{

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
//
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

} // namespace boost

#endif  // BOOST_REGEX_V5_REGEX_SEARCH_HPP



/* regex_search.hpp
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
*/