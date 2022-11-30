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

#ifndef BOOST_REGEX_V4_REGEX_REPLACE_HPP
#define BOOST_REGEX_V4_REGEX_REPLACE_HPP


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

#endif  // BOOST_REGEX_V4_REGEX_REPLACE_HPP



/* regex_replace.hpp
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
*/