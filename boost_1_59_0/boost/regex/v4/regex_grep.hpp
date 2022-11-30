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

#ifndef BOOST_REGEX_V4_REGEX_GREP_HPP
#define BOOST_REGEX_V4_REGEX_GREP_HPP


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
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
//
// this isn't really a partial specialisation, but template function
// overloading - if the compiler doesn't support partial specialisation
// then it really won't support this either:
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
#else  // partial specialisation
inline unsigned int regex_grep(bool (*foo)(const cmatch&), const char* str, 
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + regex::traits_type::length(str), e, flags);
}
#ifndef BOOST_NO_WREGEX
inline unsigned int regex_grep(bool (*foo)(const wcmatch&), const wchar_t* str, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + wregex::traits_type::length(str), e, flags);
}
#endif
inline unsigned int regex_grep(bool (*foo)(const match_results<std::string::const_iterator>&), const std::string& s,
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}
#if !defined(BOOST_NO_WREGEX)
inline unsigned int regex_grep(bool (*foo)(const match_results<std::basic_string<wchar_t>::const_iterator>&), 
                     const std::basic_string<wchar_t>& s, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}
#endif
#endif

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

#endif  // BOOST_REGEX_V4_REGEX_GREP_HPP


/* regex_grep.hpp
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
*/