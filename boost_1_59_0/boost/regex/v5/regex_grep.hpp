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
  *   FILE         regex_grep.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_grep implementation.
  */

#ifndef BOOST_REGEX_V5_REGEX_GREP_HPP
#define BOOST_REGEX_V5_REGEX_GREP_HPP


namespace boost{

//
// regex_grep:
// find all non-overlapping matches within the sequence first last:
//
template <class Predicate, class BidiIterator, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, 
                               BidiIterator first, 
                               BidiIterator last, 
                               const basic_regex<charT, traits>& e, 
                               match_flag_type flags = match_default)
{
   if(e.flags() & regex_constants::failbit)
      return false;

   typedef typename match_results<BidiIterator>::allocator_type match_allocator_type;

   match_results<BidiIterator> m;
   BOOST_REGEX_DETAIL_NS::perl_matcher<BidiIterator, match_allocator_type, traits> matcher(first, last, m, e, flags, first);
   unsigned int count = 0;
   while(matcher.find())
   {
      ++count;
      if(0 == foo(m))
         return count; // caller doesn't want to go on
      if(m[0].second == last)
         return count; // we've reached the end, don't try and find an extra null match.
      if(m.length() == 0)
      {
         if(m[0].second == last)
            return count;
         // we found a NULL-match, now try to find
         // a non-NULL one at the same position:
         match_results<BidiIterator, match_allocator_type> m2(m);
         matcher.setf(match_not_null | match_continuous);
         if(matcher.find())
         {
            ++count;
            if(0 == foo(m))
               return count;
         }
         else
         {
            // reset match back to where it was:
            m = m2;
         }
         matcher.unsetf((match_not_null | match_continuous) & ~flags);
      }
   }
   return count;
}

//
// regex_grep convenience interfaces:
//
template <class Predicate, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, const charT* str, 
                        const basic_regex<charT, traits>& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + traits::length(str), e, flags);
}

template <class Predicate, class ST, class SA, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, const std::basic_string<charT, ST, SA>& s, 
                 const basic_regex<charT, traits>& e, 
                 match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}

} // namespace boost

#endif  // BOOST_REGEX_V5_REGEX_GREP_HPP


/* regex_grep.hpp
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
*/