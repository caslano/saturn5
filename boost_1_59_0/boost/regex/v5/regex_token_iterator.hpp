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
  *   FILE         regex_token_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_token_iterator implementation.
  */

#ifndef BOOST_REGEX_V5_REGEX_TOKEN_ITERATOR_HPP
#define BOOST_REGEX_V5_REGEX_TOKEN_ITERATOR_HPP

#include <memory>

namespace boost{

template <class BidirectionalIterator,
          class charT,
          class traits>
class regex_token_iterator_implementation 
{
   typedef basic_regex<charT, traits> regex_type;
   typedef sub_match<BidirectionalIterator>      value_type;

   match_results<BidirectionalIterator> what;   // current match
   BidirectionalIterator                base;    // start of search area
   BidirectionalIterator                end;    // end of search area
   const regex_type                     re;    // the expression
   match_flag_type                      flags;  // match flags
   value_type                           result; // the current string result
   int                                  N;      // the current sub-expression being enumerated
   std::vector<int>                     subs;   // the sub-expressions to enumerate

public:
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), re(*p), flags(f), N(0){ subs.push_back(sub); }
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const std::vector<int>& v, match_flag_type f)
      : end(last), re(*p), flags(f), N(0), subs(v){}
   template <std::size_t CN>
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const int (&submatches)[CN], match_flag_type f)
      : end(last), re(*p), flags(f), N(0)
   {
      for(std::size_t i = 0; i < CN; ++i)
      {
         subs.push_back(submatches[i]);
      }
   }
   regex_token_iterator_implementation(const regex_token_iterator_implementation& other) = default;
   bool init(BidirectionalIterator first)
   {
      N = 0;
      base = first;
      if(regex_search(first, end, what, re, flags, base) == true)
      {
         N = 0;
         result = ((subs[N] == -1) ? what.prefix() : what[(int)subs[N]]);
         return true;
      }
      else if((subs[N] == -1) && (first != end))
      {
         result.first = first;
         result.second = end;
         result.matched = (first != end);
         N = -1;
         return true;
      }
      return false;
   }
   bool compare(const regex_token_iterator_implementation& that)
   {
      if(this == &that) return true;
      return (&re.get_data() == &that.re.get_data()) 
         && (end == that.end) 
         && (flags == that.flags) 
         && (N == that.N) 
         && (what[0].first == that.what[0].first) 
         && (what[0].second == that.what[0].second);
   }
   const value_type& get()
   { return result; }
   bool next()
   {
      if(N == -1)
         return false;
      if(N+1 < (int)subs.size())
      {
         ++N;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      //if(what.prefix().first != what[0].second)
      //   flags |= /*match_prev_avail |*/ regex_constants::match_not_bob;
      BidirectionalIterator last_end(what[0].second);
      if(regex_search(last_end, end, what, re, ((what[0].first == what[0].second) ? flags | regex_constants::match_not_initial_null : flags), base))
      {
         N =0;
         result =((subs[N] == -1) ? what.prefix() : what[subs[N]]);
         return true;
      }
      else if((last_end != end) && (subs[0] == -1))
      {
         N =-1;
         result.first = last_end;
         result.second = end;
         result.matched = (last_end != end);
         return true;
      }
      return false;
   }
private:
   regex_token_iterator_implementation& operator=(const regex_token_iterator_implementation&);
};

template <class BidirectionalIterator, 
          class charT = typename std::iterator_traits<BidirectionalIterator>::value_type,
          class traits = regex_traits<charT> >
class regex_token_iterator 
{
private:
   typedef regex_token_iterator_implementation<BidirectionalIterator, charT, traits> impl;
   typedef std::shared_ptr<impl> pimpl;
public:
   typedef          basic_regex<charT, traits>                   regex_type;
   typedef          sub_match<BidirectionalIterator>                        value_type;
   typedef typename std::iterator_traits<BidirectionalIterator>::difference_type 
                                                                            difference_type;
   typedef          const value_type*                                       pointer;
   typedef          const value_type&                                       reference; 
   typedef          std::forward_iterator_tag                               iterator_category;
   
   regex_token_iterator(){}
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        int submatch = 0, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatch, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        const std::vector<int>& submatches, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   template <std::size_t N>
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const int (&submatches)[N], match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   regex_token_iterator(const regex_token_iterator& that)
      : pdata(that.pdata) {}
   regex_token_iterator& operator=(const regex_token_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }
   bool operator==(const regex_token_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }
   bool operator!=(const regex_token_iterator& that)const
   { return !(*this == that); }
   const value_type& operator*()const
   { return pdata->get(); }
   const value_type* operator->()const
   { return &(pdata->get()); }
   regex_token_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }
   regex_token_iterator operator++(int)
   {
      regex_token_iterator result(*this);
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

typedef regex_token_iterator<const char*> cregex_token_iterator;
typedef regex_token_iterator<std::string::const_iterator> sregex_token_iterator;
#ifndef BOOST_NO_WREGEX
typedef regex_token_iterator<const wchar_t*> wcregex_token_iterator;
typedef regex_token_iterator<std::wstring::const_iterator> wsregex_token_iterator;
#endif

template <class charT, class traits>
inline regex_token_iterator<const charT*, charT, traits> make_regex_token_iterator(const charT* p, const basic_regex<charT, traits>& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<const charT*, charT, traits>(p, p+traits::length(p), e, submatch, m);
}
template <class charT, class traits, class ST, class SA>
inline regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits> make_regex_token_iterator(const std::basic_string<charT, ST, SA>& p, const basic_regex<charT, traits>& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits>(p.begin(), p.end(), e, submatch, m);
}
template <class charT, class traits, std::size_t N>
inline regex_token_iterator<const charT*, charT, traits> make_regex_token_iterator(const charT* p, const basic_regex<charT, traits>& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<const charT*, charT, traits>(p, p+traits::length(p), e, submatch, m);
}
template <class charT, class traits, class ST, class SA, std::size_t N>
inline regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits> make_regex_token_iterator(const std::basic_string<charT, ST, SA>& p, const basic_regex<charT, traits>& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits>(p.begin(), p.end(), e, submatch, m);
}
template <class charT, class traits>
inline regex_token_iterator<const charT*, charT, traits> make_regex_token_iterator(const charT* p, const basic_regex<charT, traits>& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<const charT*, charT, traits>(p, p+traits::length(p), e, submatch, m);
}
template <class charT, class traits, class ST, class SA>
inline regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits> make_regex_token_iterator(const std::basic_string<charT, ST, SA>& p, const basic_regex<charT, traits>& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return regex_token_iterator<typename std::basic_string<charT, ST, SA>::const_iterator, charT, traits>(p.begin(), p.end(), e, submatch, m);
}

} // namespace boost

#endif // BOOST_REGEX_V5_REGEX_TOKEN_ITERATOR_HPP





/* regex_token_iterator.hpp
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
*/