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

#ifndef BOOST_REGEX_V5_REGEX_ITERATOR_HPP
#define BOOST_REGEX_V5_REGEX_ITERATOR_HPP

#include <memory>

namespace boost{

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
          class charT = typename std::iterator_traits<BidirectionalIterator>::value_type,
          class traits = regex_traits<charT> >
class regex_iterator 
{
private:
   typedef regex_iterator_implementation<BidirectionalIterator, charT, traits> impl;
   typedef std::shared_ptr<impl> pimpl;
public:
   typedef          basic_regex<charT, traits>                   regex_type;
   typedef          match_results<BidirectionalIterator>                    value_type;
   typedef typename std::iterator_traits<BidirectionalIterator>::difference_type 
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
      if(pdata.get() && (pdata.use_count() > 1))
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

} // namespace boost

#endif // BOOST_REGEX_V5_REGEX_ITERATOR_HPP


/* regex_iterator.hpp
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
*/