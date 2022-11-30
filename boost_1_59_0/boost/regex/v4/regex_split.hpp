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
  *   FILE         regex_split.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Implements regex_split and associated functions.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_SPLIT_HPP
#define BOOST_REGEX_SPLIT_HPP

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

#ifdef BOOST_MSVC
#  pragma warning(push)
#if BOOST_MSVC < 1910
#pragma warning(disable:4800)
#endif
#endif

namespace BOOST_REGEX_DETAIL_NS{

template <class charT>
const basic_regex<charT>& get_default_expression(charT)
{
   static const charT expression_text[4] = { '\\', 's', '+', '\00', };
   static const basic_regex<charT> e(expression_text);
   return e;
}

template <class OutputIterator, class charT, class Traits1, class Alloc1>
class split_pred
{
   typedef std::basic_string<charT, Traits1, Alloc1> string_type;
   typedef typename string_type::const_iterator iterator_type;
   iterator_type* p_last;
   OutputIterator* p_out;
   std::size_t* p_max;
   std::size_t initial_max;
public:
   split_pred(iterator_type* a, OutputIterator* b, std::size_t* c)
      : p_last(a), p_out(b), p_max(c), initial_max(*c) {}

   bool operator()(const match_results<iterator_type>& what);
};

template <class OutputIterator, class charT, class Traits1, class Alloc1>
bool split_pred<OutputIterator, charT, Traits1, Alloc1>::operator()
   (const match_results<iterator_type>& what)
{
   *p_last = what[0].second;
   if(what.size() > 1)
   {
      // output sub-expressions only:
      for(unsigned i = 1; i < what.size(); ++i)
      {
         *(*p_out) = what.str(i);
         ++(*p_out);
         if(0 == --*p_max) return false;
      }
      return *p_max != 0;
   }
   else
   {
      // output $` only if it's not-null or not at the start of the input:
      const sub_match<iterator_type>& sub = what[-1];
      if((sub.first != sub.second) || (*p_max != initial_max))
      {
         *(*p_out) = sub.str();
         ++(*p_out);
         return --*p_max;
      }
   }
   //
   // initial null, do nothing:
   return true;
}

} // namespace BOOST_REGEX_DETAIL_NS

template <class OutputIterator, class charT, class Traits1, class Alloc1, class Traits2>
std::size_t regex_split(OutputIterator out,
                   std::basic_string<charT, Traits1, Alloc1>& s, 
                   const basic_regex<charT, Traits2>& e,
                   match_flag_type flags,
                   std::size_t max_split)
{
   typedef typename std::basic_string<charT, Traits1, Alloc1>::const_iterator  ci_t;
   //typedef typename match_results<ci_t>::allocator_type                        match_allocator;
   ci_t last = s.begin();
   std::size_t init_size = max_split;
   BOOST_REGEX_DETAIL_NS::split_pred<OutputIterator, charT, Traits1, Alloc1> pred(&last, &out, &max_split);
   ci_t i, j;
   i = s.begin();
   j = s.end();
   regex_grep(pred, i, j, e, flags);
   //
   // if there is still input left, do a final push as long as max_split
   // is not exhausted, and we're not splitting sub-expressions rather 
   // than whitespace:
   if(max_split && (last != s.end()) && (e.mark_count() == 0))
   {
      *out = std::basic_string<charT, Traits1, Alloc1>((ci_t)last, (ci_t)s.end());
      ++out;
      last = s.end();
      --max_split;
   }
   //
   // delete from the string everything that has been processed so far:
   s.erase(0, last - s.begin());
   //
   // return the number of new records pushed:
   return init_size - max_split;
}

template <class OutputIterator, class charT, class Traits1, class Alloc1, class Traits2>
inline std::size_t regex_split(OutputIterator out,
                   std::basic_string<charT, Traits1, Alloc1>& s, 
                   const basic_regex<charT, Traits2>& e,
                   match_flag_type flags = match_default)
{
   return regex_split(out, s, e, flags, UINT_MAX);
}

template <class OutputIterator, class charT, class Traits1, class Alloc1>
inline std::size_t regex_split(OutputIterator out,
                   std::basic_string<charT, Traits1, Alloc1>& s)
{
   return regex_split(out, s, BOOST_REGEX_DETAIL_NS::get_default_expression(charT(0)), match_default, UINT_MAX);
}

#ifdef BOOST_MSVC
#  pragma warning(pop)
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

#endif



/* regex_split.hpp
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
*/