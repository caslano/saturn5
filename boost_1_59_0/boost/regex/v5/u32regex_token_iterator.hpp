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
  *   FILE         u32regex_token_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides u32regex_token_iterator implementation.
  */

#ifndef BOOST_REGEX_V5_U32REGEX_TOKEN_ITERATOR_HPP
#define BOOST_REGEX_V5_U32REGEX_TOKEN_ITERATOR_HPP

namespace boost{

#ifdef BOOST_REGEX_MSVC
#  pragma warning(push)
#  pragma warning(disable:4700)
#endif

template <class BidirectionalIterator>
class u32regex_token_iterator_implementation 
{
   typedef u32regex                              regex_type;
   typedef sub_match<BidirectionalIterator>      value_type;

   match_results<BidirectionalIterator> what;   // current match
   BidirectionalIterator                end;    // end of search area
   BidirectionalIterator                base;   // start of search area
   const regex_type                     re;     // the expression
   match_flag_type                      flags;  // match flags
   value_type                           result; // the current string result
   int                                  N;      // the current sub-expression being enumerated
   std::vector<int>                     subs;   // the sub-expressions to enumerate

public:
   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, int sub, match_flag_type f)
      : end(last), re(*p), flags(f){ subs.push_back(sub); }
   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const std::vector<int>& v, match_flag_type f)
      : end(last), re(*p), flags(f), subs(v){}
   template <std::size_t CN>
   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const int (&submatches)[CN], match_flag_type f)
      : end(last), re(*p), flags(f)
   {
      for(std::size_t i = 0; i < CN; ++i)
      {
         subs.push_back(submatches[i]);
      }
   }

   bool init(BidirectionalIterator first)
   {
      base = first;
      N = 0;
      if(u32regex_search(first, end, what, re, flags, base) == true)
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
   bool compare(const u32regex_token_iterator_implementation& that)
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
      //   flags |= match_prev_avail | regex_constants::match_not_bob;
      BidirectionalIterator last_end(what[0].second);
      if(u32regex_search(last_end, end, what, re, ((what[0].first == what[0].second) ? flags | regex_constants::match_not_initial_null : flags), base))
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
   u32regex_token_iterator_implementation& operator=(const u32regex_token_iterator_implementation&);
};

template <class BidirectionalIterator>
class u32regex_token_iterator 
{
private:
   typedef u32regex_token_iterator_implementation<BidirectionalIterator> impl;
   typedef std::shared_ptr<impl> pimpl;
public:
   typedef          u32regex                                                regex_type;
   typedef          sub_match<BidirectionalIterator>                        value_type;
   typedef typename std::iterator_traits<BidirectionalIterator>::difference_type 
                                                                            difference_type;
   typedef          const value_type*                                       pointer;
   typedef          const value_type&                                       reference; 
   typedef          std::forward_iterator_tag                               iterator_category;
   
   u32regex_token_iterator(){}
   u32regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        int submatch = 0, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatch, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   u32regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re, 
                        const std::vector<int>& submatches, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   template <std::size_t N>
   u32regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const int (&submatches)[N], match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
   u32regex_token_iterator(const u32regex_token_iterator& that)
      : pdata(that.pdata) {}
   u32regex_token_iterator& operator=(const u32regex_token_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }
   bool operator==(const u32regex_token_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }
   bool operator!=(const u32regex_token_iterator& that)const
   { return !(*this == that); }
   const value_type& operator*()const
   { return pdata->get(); }
   const value_type* operator->()const
   { return &(pdata->get()); }
   u32regex_token_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }
   u32regex_token_iterator operator++(int)
   {
      u32regex_token_iterator result(*this);
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

typedef u32regex_token_iterator<const char*> utf8regex_token_iterator;
typedef u32regex_token_iterator<const UChar*> utf16regex_token_iterator;
typedef u32regex_token_iterator<const UChar32*> utf32regex_token_iterator;

// construction from an integral sub_match state_id:
inline u32regex_token_iterator<const char*> make_u32regex_token_iterator(const char* p, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const char*>(p, p+std::strlen(p), e, submatch, m);
}
#ifndef BOOST_NO_WREGEX
inline u32regex_token_iterator<const wchar_t*> make_u32regex_token_iterator(const wchar_t* p, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const wchar_t*>(p, p+std::wcslen(p), e, submatch, m);
}
#endif
#if !defined(BOOST_REGEX_UCHAR_IS_WCHAR_T)
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const UChar* p, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(p, p+u_strlen(p), e, submatch, m);
}
#endif
template <class charT, class Traits, class Alloc>
inline u32regex_token_iterator<typename std::basic_string<charT, Traits, Alloc>::const_iterator> make_u32regex_token_iterator(const std::basic_string<charT, Traits, Alloc>& p, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   typedef typename std::basic_string<charT, Traits, Alloc>::const_iterator iter_type;
   return u32regex_token_iterator<iter_type>(p.begin(), p.end(), e, submatch, m);
}
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const U_NAMESPACE_QUALIFIER UnicodeString& s, const u32regex& e, int submatch = 0, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(s.getBuffer(), s.getBuffer() + s.length(), e, submatch, m);
}

// construction from a reference to an array:
template <std::size_t N>
inline u32regex_token_iterator<const char*> make_u32regex_token_iterator(const char* p, const u32regex& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const char*>(p, p+std::strlen(p), e, submatch, m);
}
#ifndef BOOST_NO_WREGEX
template <std::size_t N>
inline u32regex_token_iterator<const wchar_t*> make_u32regex_token_iterator(const wchar_t* p, const u32regex& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const wchar_t*>(p, p+std::wcslen(p), e, submatch, m);
}
#endif
#if !defined(BOOST_REGEX_UCHAR_IS_WCHAR_T)
template <std::size_t N>
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const UChar* p, const u32regex& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(p, p+u_strlen(p), e, submatch, m);
}
#endif
template <class charT, class Traits, class Alloc, std::size_t N>
inline u32regex_token_iterator<typename std::basic_string<charT, Traits, Alloc>::const_iterator> make_u32regex_token_iterator(const std::basic_string<charT, Traits, Alloc>& p, const u32regex& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   typedef typename std::basic_string<charT, Traits, Alloc>::const_iterator iter_type;
   return u32regex_token_iterator<iter_type>(p.begin(), p.end(), e, submatch, m);
}
template <std::size_t N>
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const U_NAMESPACE_QUALIFIER UnicodeString& s, const u32regex& e, const int (&submatch)[N], regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(s.getBuffer(), s.getBuffer() + s.length(), e, submatch, m);
}

// construction from a vector of sub_match state_id's:
inline u32regex_token_iterator<const char*> make_u32regex_token_iterator(const char* p, const u32regex& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const char*>(p, p+std::strlen(p), e, submatch, m);
}
#ifndef BOOST_NO_WREGEX
inline u32regex_token_iterator<const wchar_t*> make_u32regex_token_iterator(const wchar_t* p, const u32regex& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const wchar_t*>(p, p+std::wcslen(p), e, submatch, m);
}
#endif
#if !defined(U_WCHAR_IS_UTF16) && (U_SIZEOF_WCHAR_T != 2)
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const UChar* p, const u32regex& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(p, p+u_strlen(p), e, submatch, m);
}
#endif
template <class charT, class Traits, class Alloc>
inline u32regex_token_iterator<typename std::basic_string<charT, Traits, Alloc>::const_iterator> make_u32regex_token_iterator(const std::basic_string<charT, Traits, Alloc>& p, const u32regex& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   typedef typename std::basic_string<charT, Traits, Alloc>::const_iterator iter_type;
   return u32regex_token_iterator<iter_type>(p.begin(), p.end(), e, submatch, m);
}
inline u32regex_token_iterator<const UChar*> make_u32regex_token_iterator(const U_NAMESPACE_QUALIFIER UnicodeString& s, const u32regex& e, const std::vector<int>& submatch, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_token_iterator<const UChar*>(s.getBuffer(), s.getBuffer() + s.length(), e, submatch, m);
}

#ifdef BOOST_REGEX_MSVC
#  pragma warning(pop)
#endif

} // namespace boost

#endif // BOOST_REGEX_V5_REGEX_TOKEN_ITERATOR_HPP





/* u32regex_token_iterator.hpp
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
*/