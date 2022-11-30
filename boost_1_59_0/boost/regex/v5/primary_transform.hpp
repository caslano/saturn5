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

#endif




/* primary_transform.hpp
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
*/