/*
 *
 * Copyright (c) 1998-2009
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

#ifndef BOOST_REGEX_V5_REGEX_REPLACE_HPP
#define BOOST_REGEX_V5_REGEX_REPLACE_HPP


namespace boost{

template <class OutputIterator, class BidirectionalIterator, class traits, class charT, class Formatter>
OutputIterator regex_replace(OutputIterator out,
                         BidirectionalIterator first,
                         BidirectionalIterator last,
                         const basic_regex<charT, traits>& e, 
                         Formatter fmt, 
                         match_flag_type flags = match_default)
{
   regex_iterator<BidirectionalIterator, charT, traits> i(first, last, e, flags);
   regex_iterator<BidirectionalIterator, charT, traits> j;
   if(i == j)
   {
      if(!(flags & regex_constants::format_no_copy))
         out = BOOST_REGEX_DETAIL_NS::copy(first, last, out);
   }
   else
   {
      BidirectionalIterator last_m(first);
      while(i != j)
      {
         if(!(flags & regex_constants::format_no_copy))
            out = BOOST_REGEX_DETAIL_NS::copy(i->prefix().first, i->prefix().second, out);
         out = i->format(out, fmt, flags, e);
         last_m = (*i)[0].second;
         if(flags & regex_constants::format_first_only)
            break;
         ++i;
      }
      if(!(flags & regex_constants::format_no_copy))
         out = BOOST_REGEX_DETAIL_NS::copy(last_m, last, out);
   }
   return out;
}

template <class traits, class charT, class Formatter>
std::basic_string<charT> regex_replace(const std::basic_string<charT>& s,
                         const basic_regex<charT, traits>& e, 
                         Formatter fmt,
                         match_flag_type flags = match_default)
{
   std::basic_string<charT> result;
   BOOST_REGEX_DETAIL_NS::string_out_iterator<std::basic_string<charT> > i(result);
   regex_replace(i, s.begin(), s.end(), e, fmt, flags);
   return result;
}

} // namespace boost

#endif  // BOOST_REGEX_V5_REGEX_REPLACE_HPP



/* regex_replace.hpp
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
*/