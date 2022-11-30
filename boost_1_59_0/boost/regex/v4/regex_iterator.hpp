/*
 *
 * Copyright (c) 2003
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_iterator implementation.
  */

#ifndef BOOST_REGEX_V4_REGEX_ITERATOR_HPP
#define BOOST_REGEX_V4_REGEX_ITERATOR_HPP

#include <boost/shared_ptr.hpp>

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

template <class BidirectionalIterator, 
          class charT,
          class traits>
class regex_iterator_implementation 
{
   typedef basic_regex<charT, traits> regex_type;

   match_results<BidirectionalIterator> what;  // current match
   BidirectionalIterator                base;  // start of sequence
   BidirectionalIterator                end;   // end of sequence
   const regex_type                     re;   // the expression
   match_flag_type                      flags; // flags for matching

public:
   regex_iterator_implementation(const regex_type* p, BidirectionalIterator last, match_flag_type f)
      : base(), end(last), re(*p), flags(f){}
   regex_iterator_implementation(const regex_iterator_implementation& other)
      :what(other.what), base(other.base), end(other.end), re(other.re), flags(other.flags){}
   bool init(BidirectionalIterator first)
   {
      base = first;
      return regex_search(first, end, what, re, flags);
   }
   bool compare(const regex_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) && (end == that.end) && (flags == that.flags) && (what[0].first == that.what[0].first) && (what[0].second == that.what[0].second);
   }
   const match_results<BidirectionalIterator>& get()
   { return what; }
   bool next()
   {
      //if(what.prefix().first != what[0].second)
      //   flags |= match_prev_avail;
      BidirectionalIterator next_start = what[0].second;
      match_flag_type f(flags);
      if(!what.length() || (f & regex_constants::match_posix))
         f |= regex_constants::match_not_initial_null;
      //if(base != next_start)
      //   f |= regex_constants::match_not_bob;
      bool result = regex_search(next_start, end, what, re, f, base);
      if(result)
         what.set_base(base);
      return result;
   }
private:
   regex_iterator_implementation& operator=(const regex_iterator_implementation&);
};

template <class BidirectionalIterator, 
          class charT = BOOST_DEDUCED_TYPENAME BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::value_type,
          class traits = regex_traits<charT> >
class regex_iterator 
{
private:
   typedef regex_iterator_implementation<BidirectionalIterator, charT, traits> impl;
   typedef shared_ptr<impl> pimpl;
public:
   typedef          basic_regex<charT, traits>                   regex_type;
   typedef          match_results<BidirectionalIterator>                    value_type;
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::difference_type 
                                                                            difference_type;
   typedef          const value_type*                                       pointer;
   typedef          const value_type&                                       reference; 
   typedef          std::forward_iterator_tag                               iterator_category;
   
   regex_iterator(){}
   regex_iterator(BidirectionalIterator a, BidirectionalIterator b, 
                  const regex_type& re, 
                  match_flag_type m = match_default)
                  : pdata(new impl(&re, b, m))
   {
      if(!pdata->init(a))
      {
         pdata.reset();
      }
   }
   regex_iterator(const regex_iterator& that)
      : pdata(that.pdata) {}
   regex_iterator& operator=(const regex_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }
   bool operator==(const regex_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }
   bool operator!=(const regex_iterator& that)const
   { return !(*this == that); }
   const value_type& operator*()const
   { return pdata->get(); }
   const value_type* operator->()const
   { return &(pdata->get()); }
   regex_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }
   regex_iterator operator++(int)
   {
      regex_iterator result(*this);
      ++(*this);
      return result;
   }
private:

   pimpl pdata;

   void cow()
   {
      // copy-on-write
      if(pdata.get() && !pdata.unique())
      {
         pdata.reset(new impl(*(pdata.get())));
      }
   }
};

typedef regex_iterator<const char*> cregex_iterator;
typedef regex_iterator<std::string::const_iterator> sregex_iterator;
#ifndef BOOST_NO_WREGEX
typedef regex_iterator<const wchar_t*> wcregex_iterator;
typedef regex_iterator<std::wstring::const_iterator> wsregex_iterator;
#endif

// make_regex_iterator:
template <class charT, class traits>
inline regex_iterator<const charT*, charT, traits> make_regex_iterator(const charT* p, const basic_regex<charT, traits>& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_iterator<const charT*, charT, traits>(p, p+traits::length(p), e, m);
}
template <class charT, class traits, class ST, class SA>
inline regex_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits> make_regex_iterator(const std::basic_string<charT, ST, SA>& p, const basic_regex<charT, traits>& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits>(p.begin(), p.end(), e, m);
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

#endif // BOOST_REGEX_V4_REGEX_ITERATOR_HPP


/* regex_iterator.hpp
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
*/