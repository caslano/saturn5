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
  *   FILE         u32regex_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides u32regex_iterator implementation.
  */

#ifndef BOOST_REGEX_V4_U32REGEX_ITERATOR_HPP
#define BOOST_REGEX_V4_U32REGEX_ITERATOR_HPP

namespace boost{

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

template <class BidirectionalIterator>
class u32regex_iterator_implementation 
{
   typedef u32regex regex_type;

   match_results<BidirectionalIterator> what;  // current match
   BidirectionalIterator                base;  // start of sequence
   BidirectionalIterator                end;   // end of sequence
   const regex_type                     re;   // the expression
   match_flag_type                      flags; // flags for matching

public:
   u32regex_iterator_implementation(const regex_type* p, BidirectionalIterator last, match_flag_type f)
      : base(), end(last), re(*p), flags(f){}
   bool init(BidirectionalIterator first)
   {
      base = first;
      return u32regex_search(first, end, what, re, flags, base);
   }
   bool compare(const u32regex_iterator_implementation& that)
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
      if(!what.length())
         f |= regex_constants::match_not_initial_null;
      //if(base != next_start)
      //   f |= regex_constants::match_not_bob;
      bool result = u32regex_search(next_start, end, what, re, f, base);
      if(result)
         what.set_base(base);
      return result;
   }
private:
   u32regex_iterator_implementation& operator=(const u32regex_iterator_implementation&);
};

template <class BidirectionalIterator>
class u32regex_iterator 
{
private:
   typedef u32regex_iterator_implementation<BidirectionalIterator> impl;
   typedef shared_ptr<impl> pimpl;
public:
   typedef          u32regex                                                regex_type;
   typedef          match_results<BidirectionalIterator>                    value_type;
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidirectionalIterator>::difference_type 
                                                                            difference_type;
   typedef          const value_type*                                       pointer;
   typedef          const value_type&                                       reference; 
   typedef          std::forward_iterator_tag                               iterator_category;
   
   u32regex_iterator(){}
   u32regex_iterator(BidirectionalIterator a, BidirectionalIterator b, 
                  const regex_type& re, 
                  match_flag_type m = match_default)
                  : pdata(new impl(&re, b, m))
   {
      if(!pdata->init(a))
      {
         pdata.reset();
      }
   }
   u32regex_iterator(const u32regex_iterator& that)
      : pdata(that.pdata) {}
   u32regex_iterator& operator=(const u32regex_iterator& that)
   {
      pdata = that.pdata;
      return *this;
   }
   bool operator==(const u32regex_iterator& that)const
   { 
      if((pdata.get() == 0) || (that.pdata.get() == 0))
         return pdata.get() == that.pdata.get();
      return pdata->compare(*(that.pdata.get())); 
   }
   bool operator!=(const u32regex_iterator& that)const
   { return !(*this == that); }
   const value_type& operator*()const
   { return pdata->get(); }
   const value_type* operator->()const
   { return &(pdata->get()); }
   u32regex_iterator& operator++()
   {
      cow();
      if(0 == pdata->next())
      {
         pdata.reset();
      }
      return *this;
   }
   u32regex_iterator operator++(int)
   {
      u32regex_iterator result(*this);
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

typedef u32regex_iterator<const char*> utf8regex_iterator;
typedef u32regex_iterator<const UChar*> utf16regex_iterator;
typedef u32regex_iterator<const UChar32*> utf32regex_iterator;

inline u32regex_iterator<const char*> make_u32regex_iterator(const char* p, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_iterator<const char*>(p, p+std::strlen(p), e, m);
}
#ifndef BOOST_NO_WREGEX
inline u32regex_iterator<const wchar_t*> make_u32regex_iterator(const wchar_t* p, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_iterator<const wchar_t*>(p, p+std::wcslen(p), e, m);
}
#endif
#if !defined(BOOST_REGEX_UCHAR_IS_WCHAR_T)
inline u32regex_iterator<const UChar*> make_u32regex_iterator(const UChar* p, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_iterator<const UChar*>(p, p+u_strlen(p), e, m);
}
#endif
template <class charT, class Traits, class Alloc>
inline u32regex_iterator<typename std::basic_string<charT, Traits, Alloc>::const_iterator> make_u32regex_iterator(const std::basic_string<charT, Traits, Alloc>& p, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   typedef typename std::basic_string<charT, Traits, Alloc>::const_iterator iter_type;
   return u32regex_iterator<iter_type>(p.begin(), p.end(), e, m);
}
inline u32regex_iterator<const UChar*> make_u32regex_iterator(const U_NAMESPACE_QUALIFIER UnicodeString& s, const u32regex& e, regex_constants::match_flag_type m = regex_constants::match_default)
{
   return u32regex_iterator<const UChar*>(s.getBuffer(), s.getBuffer() + s.length(), e, m);
}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

} // namespace boost

#endif // BOOST_REGEX_V4_REGEX_ITERATOR_HPP


/* u32regex_iterator.hpp
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
*/