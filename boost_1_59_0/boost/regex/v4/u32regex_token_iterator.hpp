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

#ifndef BOOST_REGEX_V4_U32REGEX_TOKEN_ITERATOR_HPP
#define BOOST_REGEX_V4_U32REGEX_TOKEN_ITERATOR_HPP

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

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif
#ifdef BOOST_MSVC
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
#if (BOOST_WORKAROUND(__BORLANDC__, >= 0x560) && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570)))\
      || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) \
      || BOOST_WORKAROUND(__HP_aCC, < 60700)
   template <class T>
   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const T& submatches, match_flag_type f)
      : end(last), re(*p), flags(f)
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
   u32regex_token_iterator_implementation(const regex_type* p, BidirectionalIterator last, const int (&submatches)[CN], match_flag_type f)
      : end(last), re(*p), flags(f)
   {
      for(std::size_t i = 0; i < CN; ++i)
      {
         subs.push_back(submatches[i]);
      }
   }
#endif

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
   typedef shared_ptr<impl> pimpl;
public:
   typedef          u32regex                                                regex_type;
   typedef          sub_match<BidirectionalIterator>                        value_type;
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::difference_type 
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
#if (BOOST_WORKAROUND(__BORLANDC__, >= 0x560) && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570)))\
      || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3003)) \
      || BOOST_WORKAROUND(__HP_aCC, < 60700)
   template <class T>
   u32regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const T& submatches, match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#else
   template <std::size_t N>
   u32regex_token_iterator(BidirectionalIterator a, BidirectionalIterator b, const regex_type& re,
                        const int (&submatches)[N], match_flag_type m = match_default)
                        : pdata(new impl(&re, b, submatches, m))
   {
      if(!pdata->init(a))
         pdata.reset();
   }
#endif
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
      if(pdata.get() && !pdata.unique())
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

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

} // namespace boost

#endif // BOOST_REGEX_V4_REGEX_TOKEN_ITERATOR_HPP





/* u32regex_token_iterator.hpp
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
*/