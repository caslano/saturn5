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
  *   FILE:        primary_transform.hpp
  *   VERSION:     see <boost/version.hpp>
  *   DESCRIPTION: Heuristically determines the sort string format in use
  *                by the current locale.
  */

#ifndef BOOST_REGEX_PRIMARY_TRANSFORM
#define BOOST_REGEX_PRIMARY_TRANSFORM

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


enum{
   sort_C,
   sort_fixed,
   sort_delim,
   sort_unknown
};

template <class S, class charT>
unsigned count_chars(const S& s, charT c)
{
   //
   // Count how many occurrences of character c occur
   // in string s: if c is a delimeter between collation
   // fields, then this should be the same value for all
   // sort keys:
   //
   unsigned int count = 0;
   for(unsigned pos = 0; pos < s.size(); ++pos)
   {
      if(s[pos] == c) ++count;
   }
   return count;
}


template <class traits, class charT>
unsigned find_sort_syntax(const traits* pt, charT* delim)
{
   //
   // compare 'a' with 'A' to see how similar they are,
   // should really use a-accute but we can't portably do that,
   //
   typedef typename traits::string_type string_type;
   typedef typename traits::char_type char_type;

   // Suppress incorrect warning for MSVC
   (void)pt;

   char_type a[2] = {'a', '\0', };
   string_type sa(pt->transform(a, a+1));
   if(sa == a)
   {
      *delim = 0;
      return sort_C;
   }
   char_type A[2] = { 'A', '\0', };
   string_type sA(pt->transform(A, A+1));
   char_type c[2] = { ';', '\0', };
   string_type sc(pt->transform(c, c+1));

   int pos = 0;
   while((pos <= static_cast<int>(sa.size())) && (pos <= static_cast<int>(sA.size())) && (sa[pos] == sA[pos])) ++pos;
   --pos;
   if(pos < 0)
   {
      *delim = 0;
      return sort_unknown;
   }
   //
   // at this point sa[pos] is either the end of a fixed width field
   // or the character that acts as a delimiter:
   //
   charT maybe_delim = sa[pos];
   if((pos != 0) && (count_chars(sa, maybe_delim) == count_chars(sA, maybe_delim)) && (count_chars(sa, maybe_delim) == count_chars(sc, maybe_delim)))
   {
      *delim = maybe_delim;
      return sort_delim;
   }
   //
   // OK doen't look like a delimiter, try for fixed width field:
   //
   if((sa.size() == sA.size()) && (sa.size() == sc.size()))
   {
      // note assumes that the fixed width field is less than
      // (numeric_limits<charT>::max)(), should be true for all types
      // I can't imagine 127 character fields...
      *delim = static_cast<charT>(++pos);
      return sort_fixed;
   }
   //
   // don't know what it is:
   //
   *delim = 0;
   return sort_unknown;
}


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








/* primary_transform.hpp
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
*/