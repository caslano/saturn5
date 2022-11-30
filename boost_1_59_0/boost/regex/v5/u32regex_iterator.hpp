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

#ifndef BOOST_REGEX_V5_U32REGEX_ITERATOR_HPP
#define BOOST_REGEX_V5_U32REGEX_ITERATOR_HPP

namespace boost{

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
   typedef std::shared_ptr<impl> pimpl;
public:
   typedef          u32regex                                                regex_type;
   typedef          match_results<BidirectionalIterator>                    value_type;
   typedef typename std::iterator_traits<BidirectionalIterator>::difference_type 
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
      if(pdata.get() && (pdata.use_count() > 1))
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

} // namespace boost

#endif // BOOST_REGEX_V5_REGEX_ITERATOR_HPP


/* u32regex_iterator.hpp
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
*/