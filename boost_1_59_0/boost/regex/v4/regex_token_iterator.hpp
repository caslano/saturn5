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

#ifndef BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP
#define BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/detail/workaround.hpp>
#if (BOOST_WORKAROUND(BOOST_BORLANDC, >= 0x560) && BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x570)))\
      || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003))
//
// Borland C++ Builder 6, and Visual C++ 6,
// can't cope with the array template constructor
// so we have a template member that will accept any type as 
// argument, and then assert that is really is an array:
//
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_array.hpp>
#endif

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
#pragma warning(push)
#pragma warning(disable:4700)
#endif

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
   regex_token_iterator_implementation(const regex_token_iterator_implementation& other)
      : what(other.what), base(other.base), end(other.end), re(other.re), flags(other.flags), result(other.result), N(other.N), subs(other.subs) {}
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), re(*p), flags(f), N(0){ subs.push_back(sub); }
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const std::vector<int>& v, match_flag_type f)
      : end(last), re(*p), flags(f), N(0), subs(v){}
#if !BOOST_WORKAROUND(__HP_aCC, < 60700)
#if (BOOST_WORKAROUND(BOOST_BORLANDC, >= 0x560) && BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x570)))\
      || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) \
      || BOOST_WORKAROUND(__HP_aCC, < 60700)
   template <class T>
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const T& submatches, match_flag_type f)
      : end(last), re(*p), flags(f), N(0)
   {
      // assert that T really is an array:
      BOOST_STATIC_ASSERT(::boost::is_array<T>::value);
      const std::size_t array_size = sizeof(T) / sizeof(submatches[0]);
      for(std::size_t i = 0; i < array_size; ++i)
      {
         subs.push_back(submatches[i]);
      }
   }
#else
   template <std::size_t CN>
   regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const int (&submatches)[CN], match_flag_type f)
      : end(last), re(*p), flags(f), N(0)
   {
      for(std::size_t i = 0; i < CN; ++i)
      {
         subs.push_back(submatches[i]);
      }
   }
#endif
#endif
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
          class charT = BOOST_DEDUCED_TYPENAME BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::value_type,
          class traits = regex_traits<charT> >
class regex_token_iterator 
{
private:
   typedef regex_token_iterator_implementation<BidirectionalIterator, charT, traits> impl;
   typedef shared_ptr<impl> pimpl;
public:
   typedef          basic_regex<charT, traits>                   regex_type;
   typedef          sub_match<BidirectionalIterator>                        value_type;
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::difference_type 
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
#if !BOOST_WORKAROUND(__HP_aCC, < 60700)
#if (BOOST_WORKAROUND(BOOST_BORLANDC, >= 0x560) && BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x570)))\
      || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) \
      || BOOST_WORKAROUND(__HP_aCC, < 60700)
   template <class T>
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const T& submatches, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#else
   template <std::size_t N>
   regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const int (&submatches)[N], match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#endif
#endif
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
      if(pdata.get() && !pdata.unique())
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

#ifdef BOOST_MSVC
#pragma warning(pop)
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

#endif // BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP





/* regex_token_iterator.hpp
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
*/