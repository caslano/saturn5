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

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#if BOOST_REGEX_MSVC < 1910
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

#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

} // namespace boost

#endif



/* regex_split.hpp
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
*/