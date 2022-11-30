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
  *   FILE         sub_match.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class sub_match.
  */

#ifndef BOOST_REGEX_V4_SUB_MATCH_HPP
#define BOOST_REGEX_V4_SUB_MATCH_HPP

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

namespace boost{

template <class BidiIterator>
struct sub_match : public std::pair<BidiIterator, BidiIterator>
{
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidiIterator>::value_type       value_type;
#if defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef          std::ptrdiff_t                                                   difference_type;
#else
   typedef typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<BidiIterator>::difference_type  difference_type;
#endif
   typedef          BidiIterator                                                     iterator_type;
   typedef          BidiIterator                                                     iterator;
   typedef          BidiIterator                                                     const_iterator;

   bool matched;

   sub_match() : std::pair<BidiIterator, BidiIterator>(), matched(false) {}
   sub_match(BidiIterator i) : std::pair<BidiIterator, BidiIterator>(i, i), matched(false) {}
#if !defined(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS)\
               && !BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x0551)\
               && !BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
   template <class T, class A>
   operator std::basic_string<value_type, T, A> ()const
   {
      return matched ? std::basic_string<value_type, T, A>(this->first, this->second) : std::basic_string<value_type, T, A>();
   }
#else
   operator std::basic_string<value_type> ()const
   {
      return str();
   }
#endif
   difference_type BOOST_REGEX_CALL length()const
   {
      difference_type n = matched ? ::boost::BOOST_REGEX_DETAIL_NS::distance((BidiIterator)this->first, (BidiIterator)this->second) : 0;
      return n;
   }
   std::basic_string<value_type> str()const
   {
      std::basic_string<value_type> result;
      if(matched)
      {
         std::size_t len = ::boost::BOOST_REGEX_DETAIL_NS::distance((BidiIterator)this->first, (BidiIterator)this->second);
         result.reserve(len);
         BidiIterator i = this->first;
         while(i != this->second)
         {
            result.append(1, *i);
            ++i;
         }
      }
      return result;
   }
   int compare(const sub_match& s)const
   {
      if(matched != s.matched)
         return static_cast<int>(matched) - static_cast<int>(s.matched);
      return str().compare(s.str());
   }
   int compare(const std::basic_string<value_type>& s)const
   {
      return str().compare(s);
   }
   int compare(const value_type* p)const
   {
      return str().compare(p);
   }

   bool operator==(const sub_match& that)const
   { return compare(that) == 0; }
   bool BOOST_REGEX_CALL operator !=(const sub_match& that)const
   { return compare(that) != 0; }
   bool operator<(const sub_match& that)const
   { return compare(that) < 0; }
   bool operator>(const sub_match& that)const
   { return compare(that) > 0; }
   bool operator<=(const sub_match& that)const
   { return compare(that) <= 0; }
   bool operator>=(const sub_match& that)const
   { return compare(that) >= 0; }

#ifdef BOOST_REGEX_MATCH_EXTRA
   typedef std::vector<sub_match<BidiIterator> > capture_sequence_type;

   const capture_sequence_type& captures()const
   {
      if(!m_captures) 
         m_captures.reset(new capture_sequence_type());
      return *m_captures;
   }
   //
   // Private implementation API: DO NOT USE!
   //
   capture_sequence_type& get_captures()const
   {
      if(!m_captures) 
         m_captures.reset(new capture_sequence_type());
      return *m_captures;
   }

private:
   mutable boost::scoped_ptr<capture_sequence_type> m_captures;
public:

#endif
   sub_match(const sub_match& that, bool 
#ifdef BOOST_REGEX_MATCH_EXTRA
      deep_copy
#endif
      = true
      ) 
      : std::pair<BidiIterator, BidiIterator>(that), 
        matched(that.matched) 
   {
#ifdef BOOST_REGEX_MATCH_EXTRA
      if(that.m_captures)
         if(deep_copy)
            m_captures.reset(new capture_sequence_type(*(that.m_captures)));
#endif
   }
   sub_match& operator=(const sub_match& that)
   {
      this->first = that.first;
      this->second = that.second;
      matched = that.matched;
#ifdef BOOST_REGEX_MATCH_EXTRA
      if(that.m_captures)
         get_captures() = *(that.m_captures);
#endif
      return *this;
   }
   //
   // Make this type a range, for both Boost.Range, and C++11:
   //
   BidiIterator begin()const { return this->first; }
   BidiIterator end()const { return this->second; }


#ifdef BOOST_OLD_REGEX_H
   //
   // the following are deprecated, do not use!!
   //
   operator int()const;
   operator unsigned int()const;
   operator short()const
   {
      return (short)(int)(*this);
   }
   operator unsigned short()const
   {
      return (unsigned short)(unsigned int)(*this);
   }
#endif
};

typedef sub_match<const char*> csub_match;
typedef sub_match<std::string::const_iterator> ssub_match;
#ifndef BOOST_NO_WREGEX
typedef sub_match<const wchar_t*> wcsub_match;
typedef sub_match<std::wstring::const_iterator> wssub_match;
#endif

// comparison to std::basic_string<> part 1:
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator == (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator != (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator < (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator <= (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator >= (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) >= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator > (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) > 0; }
// comparison to std::basic_string<> part 2:
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) >= 0; }
// comparison to const charT* part 1:
template <class RandomAccessIterator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
inline bool operator == (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
inline bool operator != (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) <= 0; }

// comparison to const charT& part 1:
template <class RandomAccessIterator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
inline bool operator == (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }

// addition operators:
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const sub_match<RandomAccessIterator>& m,
            const std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
#if !(defined(__GNUC__) && defined(BOOST_NO_STD_LOCALE))
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const * s)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
#else
// worwaround versions:
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{
   return s + m.str();
}
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const * s)
{
   return m.str() + s;
}
#endif
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(1, s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(m.first, m.second).append(1, s);
}
template <class RandomAccessIterator>
inline std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m1,
            const sub_match<RandomAccessIterator>& m2)
{
   std::basic_string<typename BOOST_REGEX_DETAIL_NS::regex_iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m1.length() + m2.length() + 1);
   return result.append(m1.first, m1.second).append(m2.first, m2.second);
}
#ifndef BOOST_NO_STD_LOCALE
template <class charT, class traits, class RandomAccessIterator>
std::basic_ostream<charT, traits>&
   operator << (std::basic_ostream<charT, traits>& os,
                const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#else
template <class RandomAccessIterator>
std::ostream& operator << (std::ostream& os,
                           const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#endif

#ifdef BOOST_OLD_REGEX_H
namespace BOOST_REGEX_DETAIL_NS{
template <class BidiIterator, class charT>
int do_toi(BidiIterator i, BidiIterator j, char c, int radix)
{
   std::string s(i, j);
   char* p;
   int result = std::strtol(s.c_str(), &p, radix);
   if(*p)raise_regex_exception("Bad sub-expression");
   return result;
}

//
// helper:
template <class I, class charT>
int do_toi(I& i, I j, charT c)
{
   int result = 0;
   while((i != j) && (isdigit(*i)))
   {
      result = result*10 + (*i - '0');
      ++i;
   }
   return result;
}
}


template <class BidiIterator>
sub_match<BidiIterator>::operator int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)raise_regex_exception("Bad sub-expression");
   int neg = 1;
   if((i != j) && (*i == '-'))
   {
      neg = -1;
      ++i;
   }
   neg *= BOOST_REGEX_DETAIL_NS::do_toi(i, j, *i);
   if(i != j)raise_regex_exception("Bad sub-expression");
   return neg;
}
template <class BidiIterator>
sub_match<BidiIterator>::operator unsigned int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)
      raise_regex_exception("Bad sub-expression");
   return BOOST_REGEX_DETAIL_NS::do_toi(i, j, *first);
}
#endif

} // namespace boost

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

#endif


/* sub_match.hpp
vGZI3f/AxTSEZxeRRbMJ8vpi9uxiXlERv6hYUFQsnA1GULNRcZQIz4adqRIR4YWFrppDEMZCulTNqNIz6kxkowkNtWsxo2HvQMrtVk6bjd9s4zdaeM02QW9AurBcf0OPc89E4N6VAOHkw5vTj9wA+E0eXh8/tDZ6YEXkjonYzqHkls7Uxpbk+sbY2jr/iir74pxxMqNdVKpbUWVY12Ra32JYWaddlJdNpIUTcfaCCDnHT3Q4ZgWuH7nxtg8/mTp9/uvXP/7tu1d+9+7l35278Nu3P/7mzY+QnXr/lyfe+PT46asnz1568fRHBx87u2nnkRWb7lmw6s6VWx/YcdtT6248snTL4Q13Pp1vnme2Rc+/cWbq47fMdaHvt9lMY7nwgproglpza1yQUhIxilVi4ObtRVGNOGE25DyOGm2yte9n7LO19b9xeq5U9BwqX5b9kV3wE7fgFxnVLMMPdhy+k9709thrLxX7ZD/UMItd8lnq2ffcsWPqj78HlTWL+rdkS0Pd4FhF74i9vPLnNubPrb9goJ1z6S5afBuD60TvxhLEu1QEJLQxghIm6uKRsEJStBlZ3ihudMp6goqhqGJOTD4nJh2OSgYj4r4w1ennNbpYFWZAMXpBNGeDT9CZHZSZkrJALZSoqVKtrEynrjTq6yzmZrulzWlsdSobHMJKM7NER0SVqKvXhXckR4VYZKGCCFUDEigiLWOhfkMLPU5HhMyL8WvD4AUZT0/duRbCDkGBoC14eAvOYuO+P7xeuXDXMKwVCrwTn2i6PAmFsEj0CgExKy7nlajV1Q5KjfNHMxCmA1k0fmeSNXR2SUoPEimQL8PCZeK9ltC9bcbz1QsNrTgShS8EKyjhRRVUUi3N6OSlBmlGL4ip8HgxvL8YXXQhwO+LRkzwAL+MiISdkHPTCm5WxS1VcfAYUmYWDwMHBoyIUPcTGhLFRvpWhP16VtE/T/7+UyDPxkBGWMZWPFOTjJeRmVaIGRTPFK7Dtw0LY1ROplSFPRlLlWROgUbrlCvJCjWjQssCq9KxGszcHr9oIq9e327eOdd1x2TgnuXR+9cC8yYPbwT8Jg6tiR1YEb0T8Dscv6ED3N7wqlrfsgr7wlLjgpRmQUoNFLy63rS5w3JDp3l1g24RUHBKMBFnjUfIkQCjxzUrWuQebHjp3B9fOffN2Q++efPCt+9c+t25i9+eu/DNOxe+efvCN6998KuTb37+wqkrL7xy4ZkTHzzyzOvrbzzUPrpz0bqD23c/tfamJ1btOLJ8++Gt+59zhCqjsbLfffbxV2dfFPjkP2i2qCdy0eUNuQ1dmfWd/okqbW9U1hEUdQUZtTZGQiMvMXM9coWfGW9uZtg3GfMrypeUqVucxTHtT3wi4N/rS9Xhkeolu9cvun19fE4t0yNn2cQsv+b7BtbJh+/54vwbs53if1X/bJb8/81Sfm+W9l+/b/qP2S4WE7EqXvnDUkZczkoowYFipxSspAJQBrcrmm4RkYKxsXeGG+vkwqSKyukktVZZu0cxEFLOjanmJVXz00qweSn5nISkLyxs87KBRtNoIB7GBZvQsMCRRKIabxrIDMu4MYUopZLntJoqI2pCrLWKy02clBaQS9A9+Ea8NZIcF2Ty6czUdNcARSIi1mOHnd4ucIZ8jTw0xlaHxytdO3WHro6mN2Uw41lqZrrSDEMbVbnzUH5ZzijwqQRTCbiZIIPNbPQWQTEzKkP7d2sEhbtURhSk8rXzlummvJlOARmOvBkKXVRM+3QXMx2RRsWWeKOHwo5pKPjADkoFEQUFjmdCLYyq2H4pWgCBx8VF06vKdH86aGN8Yiy4QADhFKyNCk5Gyckq2VklM6NA8y6SEjR9IoQHcdtxgTq9Wyjd40kj9H9F8QyWaV5mTI/FoKvOVHjumQx/JzQLy3D7Hh3wBAqgh/oG8LYCQQEZEqA68IQETbbJYXZutLB6fYL5JdKV9ZpN3aYbh+y7x7z7FoUAswdXxw+tSRxcGbtnafSO8chNQ5FNHaFV9b4llfbxrHE0qZkbU44m1BOl2hW1hvUtpnXNxqWVmnlp6dwYfzTKGA0Rg16yw/HzSsXP0uJdj73y+gd/eeW9X5/54DdvX/z23cvfnrv4m7c++vqtD795/fyvT77x+fOvXH3i6EcPP/vuXYdPTK7as3jZ3pt2Pb7lliObdj++btej6259bPmOQxyRtbNzYOqvX5969L7/uO7ff5KUcIYj5vF8ckVb9Ya+6vW9ySVNjqGMYyRnHc1JW3zSGrskpf/B7P/gOopKb0k7tsWJTruwI8CusPwsIv1JQs6vcYkqHL+IS/+fj/1DB5cKaMUB3c+dYsIq+PyVF5575qFZmuuLUBUfHgERws10iLD4qDQdT1RmpZTcDNrKgV8Kj2p+Vs0DfyqtRLdEUs5Loj1whSWg65TijEqc04orDdJGm6zLqxwKq+clNeMl2vEMPKrG0oq5cWl/CFxjVqWFiKO5Omg0tAxvaaQE0IFrLCAcFIAUFhBeSAoolpSilj1eXMPwyVAwHHxeel8Mei4HPQeJbpCZ6e4vNP7g7X5s3IKhYlceqcN/jiCMg11o/LuwEOyiJXTBQZ7e5tiGUQ+EDspcjqPo9LYFhX1XcQMFSFC3gPCLRGkDZaCQnpfhrJkG76pMD9GiO+JnbuOZCZDKQgk3MC/L8fd7LZkwfukyDzvuecS1qSw8doDjlzDduJ5Kj+shaZqjY90KekobG8/kRAWZGMIyTgoRMadEwS5RMEswftNSPLEW90hG5URAipZH+LxwVlRRISL9f1HU16KYOa0B6DA7PYZOzSgMQKNVB/wSPibtiNE1NjY8NgcVpLHQBK2gCHiZUWFiNTnZ3T4AGCzn086cCH9BRrSkSraySbm+Q3sDoHjQsWvEe8d46K5Fkf1LInctCu+ZH945FNjQ4V1Wax/PmeYmNQNhRX9QMRhRjabUE3nNokrtRJl6OCnrDFDtXnaPj+j1og3Rmi1krX6W5ydDO25898rUy+/98swH34CKfvvCt9gAwt+cfvfXL7/5xYmznxw59vGBR99cf9NDQ6M7Vq+6e+vOw5tvfXj9rY9u2P3o7kNHW4fW/Px6yZq1m6em/nhw97ZZs2YVCa8vKlXwBsPWpXWpNR0VqzqrVnWVL2svX9ySXdTk6EsLszrCzL6++MewytnHS9y3tmt3NMjWl/MWRGd3OTiDQduiSu9klaYvxi+zUhG9JGwkbZJZgp/LnYqpS+dv33/zLPl/XO+YPdt1XZGfKA6zikNswo+/QzcOFUalzJSSl9UIctMTWfNaYU4jhN9kVIKMUpBRCLMKqlQpLlWJ4TGnFpdrJbUmGYjevgAsgLr5Kd2CEu2CtHpeSjkSlw5GRF1+XoODUaonfFJElBLsfInhDmehABSgWM9FU9/tfBSJDcnYYTnTJyXApYVbC4GXhWiC7kKa6Z2h+Xemd4+6ZtCWHmtUI8asFiiGjfamBD4FLIOnbMUZpUKwS4h94elglx0Xfhim8atgoj8sdCLgSrPvVC6CMJXUUmYRDqbRE6o5BTWux3sdoi2WpneBoYFGbwRT6GJGXZBgTLSM4Bk7aMQfPbWSjdvS6R2dcCGNG602aH/GmUrIGYle6E/HzXR2fBHRxCQxOy7jJLGQRviVswC/JXKyREZk0BA5RpmWVabn5PSspAbpIjQpZTpYd23/wv+K5eLphlw6jUWX1NI5RLTk4lIfem0B0U4PTPDg+KeJHjjJQBO04PP6RESJnt3o4w8kqQWloiXl4mVV4hV14pWNklXN0jXNinXNmo2t5q1dzp2Dvtvmhe5YELp9fvDmYd+mDueyGvNYRjsQUXT75d1eRa9fAUAejMkH4tKusLjBLaywcMrNZK2VaLSjLRhq9Ixy3Sz7j6Nz21758G8n3v7l2Q+/fuPib9+6+C2w8JsXfoOySO+Dfv7y2KtXHzv2wW0HX+4cvSlTs6Z3bM/E2gOrtj+49fZHb7rrqY23P2oPNbL5xj237QP8bl05Cfglf3Ydwbu+yEuxcnph3qyt90cX1JSv6ihf1lKzojM5WkWlNdfrWbMVJPhB9r5o6daOyM1d+m0N7GXJ2WMB7Yaa7J7h6LZ2xXCCX+0Q5a3shPZ6NWsW84fOEvfUb365+obls4pmzdaLmQYzQ28uNmsJs67YpCqysgknE93SQTHoZ05ahaqFcxoUZQLLgWlEpWAqUamSyilFOUAukC96lJRppNUGRbNN3e3TDkX085L6sZR2Xko1klAMR4F/KcBvk5OZNxIhPFFNivGLplrB3cglNRhloKjNaOMDhodioCWaQlkhI1a/GgxAOvJMb25Io3gmsjSz6U+hxwGXS6GNjfAfIhnMQO8FkITlwkRvg0hvc0ZPlRcUwIvk9DR+lWwEfC27MHdlhqbp6kc0BkdAxbWUXVLop6BHGdOlm5bpqkU0k5aJFh8lo7BRGmpNKuzywHYKOW4h2y1Eu4TTey3Z2IUay5m9WnBVBuGa3oCbnoyNBuDQo2+mD3RkYbIWGs4jIMMiZlzKRvyr5JQoQUWzMwpmVskoBeRqWFV6Xp2ZarBJ6h1UlYWT0hAuEZK4YlwZMjN2jNY5dEfStVi+FrwEnYamNQCNX7zjmwHP+6I7ONDIPg5Sd0HUb4ViaHa6Zg/TNF3O7aKItJHbFpNO1GrWdei29Gi39qhv6JJv7JKsbxevaRKtqJEsq1Asr9StbbBv7fbeMiewe17g1jneLV32FbXGsYy6P6To9Mo63GDSTlS/RzW5+dU2TlbPjqsYcfC4dWSZgSzTo4G9Jcr/cJOCjOneFz86/u5/vvrhrwG25658+/aVb1+/+JszH3x96r1fvnLui+fPXD701LnlWw+nqhdXt23sHds1tvzudTsP77jzsR17Hu0a3ykx5ayu9JOPPjY19Zv5fR0Iv8UE+bPZxM9+XvSLn/6M/KkgoQtMVieW1GUXNzWs7kvMreSEZdc5+MJSm6knbZ+bdizMO5ZVmVZWcZekru91SoajpgUZcbsHpAhRYSou1xZn5LDozXKR5XOrp/7wdXdXDymLpOv3uOI3Wf1rzO5Jg2O+Uj/IV5QRJjHhRPkRMihhx8CBUvJLMIpLaeRqJDmNFJlakr/GytSycq2i2qhutOk6vYaBsHEkYZiX0o0kVHNgDQyLewLCNg+n3sbI6Qv4leOOVOBfJQtxIuCloGxRSz7DRaFHADKahcUrcKga7+INYKQ3DQQGFxEofiUkvrvl6LtuJpqkwAFqKYmeiTxQAm1IqsCbGNoK43RQsMtDl1xOzyKGFQOeAPhFlM3C+J3enxT5zng7pOm9RKmolnJI8Eg9PCLPRZdxigr7ls4ExxCQ8VIAd6wWD0rFGy0x8UZpbC/eLBgN4KIHV063zMwEsrxCtBU4HFtx5Qxd/6alB1oSqAQLAQfDxIL7mxBSUOETMylnA34zKhTLyqm5eQ23QserNgrrrRIQSx0+Vbtf0eSmys3MsByRu4Io9BpfW1EmLi74LNd29M9gmRbPtEhGQ3fxmFw4EyNOk+mZ02fFRS1XQTw7yIcFD9wGGiyr6Hl6Jh4RVrMbw4pFTabtc+17Jhx3TFpum6+/ZUR145B8S7dkbZNoWYV4YaliSZlhTYMDQXjId8uge1uXbVWtcX6JBpRzh0fa6hS3OERNdkEdcK6RWaJFI90CEiIkJeNKNP85pUbbKoUlRW7ev2t/um7/o2cuTp06/6s3Pv7NO5e+ffvyt29d+u2ZD3/98rmvTp377OmXPr7r4dd6Jm7xlwwNz9uxcMntqzbes3nnobXb7+tfeGtp5wajp9rpKXn60Uempn7d0Fg663uzyOtQpL6YV0TMvu56xi8U1a7osvr4wrrsstbsijZje/g6j5ARU5s7kp6hCkVXjGz3EuVmVsbAaLARFbriOhOr081qd4HaZw76i7rt13eaZ3faZpUJh1b0T3368ci8dRMrn9648/X2+Y+Xtx/INdyRqdkVSGy22leJjfnZFhKPmhExQgBhNFSZh1EszKhFGbWkVCPLaxVlOmW5TlEBpkePlTpVlUFbazI02U0dXnN/2DQcN8xN6ubE1UNRWW9Q1Onlg1NTZSYzGiIgQdykYhR6iACbFkFhBw0XuvMReB1Chl3AsOE4kolXQJMas7B62hGW0xsEAzZJ/HgNI9MoLric0/4yzdGoxZ5EfjcAyo4DRHSwi5bNRroyil2Q3DTdK+lCazw93kQPm6V35ZjBrxj9IV3rUigRmd5oiY6PWXCRmBmvUUbcRk0LcjyVi+lCG6UV8IuG3V271xIOx/nQhC4GGF5q0KBdOl6NCA6Ppf0ONbhX3crEexryUdE+grACbQ5VquGV6wRVBqrWLG6wy1pdqg6ftieo7wlp2/2yWgc3qUHpMy3OK6mwI492LcQvTrerXAvkmTZDJv6RHtCqwaehx3qYHnltZBQicjR+0bB3ATIfbo1Bo2zwJh10kFDFIBxiRplLOlZj3jHquWuZ796VnnuW2fctMt0xrt89qrmxT7GhWbaiWr60QruyxrKh2bm9y31jt3NLm3VVjRH8NeDfdrek2U7VWwXVRjbwbImaiMkJejv7oBglwZPXpsJ5s9izuteue+PTqZPnfvnax795E8QzGMLv1yff+fLYa1cfeu78jn0nGoY2edO99R2r507snFi5Z8m6fYNLdlUPbqsd2OYKNf5/2HsLeLmqc2389LYfbSlFknNm73HZY3t8j7vLcXd31+TEE4JEkBAPgUCEhBCCQ3EppbhDILh78QChpVDO/11rzUwOltD2/n/3+3qzWWuYMxndez3r9ee12WO3XrV36qsPUhXhnN/n5IlnCJ0yXYlFwolniE9UVDkDJ9elTmmJLm3mZhWLKswzIkppvcc+UOQeKNF1JujWQF6ZjZcyU6XmvCabYmGx68xm58pGy+nV+lPKtUvLDKdWGZZX5zRpz1i7ZOqt1zZtu3XbJfv3XLpv9bkPTi79Y//4zd0Df6hruaSo7Hx3cAFl1fDABPOhhA2AMPI2gyAu0smK9YpSg6rMCPg11HCmepulwW5utANsYViaHbYWl6PD6+wNOgdjjtGkbTxlmUgZRxPsQETVHZC1uMW1sBkaUEDKh+uIiTfJg2uHw2p+iKx5JcqEJHXWpDMgGMtmDFsDHkZiC2cgrMUoRrc0si6zEM4yS2Q91cTZRdRsFTZCOeyJIsFfIigBWSb85oBceFsltrVVuCjDkOGstgrT+iGmXEb49XwXv+FMO3jUkGtaoyWUCYb7wtuI3YdZEVCSKmmLnG6chPtDZXst4R5tEaUgoUEZWUmNMK7mR3FTYx+WxXZsPyLCeSL7sDhGbSPoNGRwNAEgLK0wK2qtqiantt2r6woYe8OWgSg3nLAPJ7mBmB5EcKWVH9UgEYwkuyDdPoZ4xeE+6j3KS6OY+P+J/zBL+UWyJYkLPQteOxmZqklQ7EExCGEGPxLds2HXIoIwOsmUVUIVWhVD5dyqEf9Fp0QuWxG5fHlo72n+Pad4di9x7Vhg3zLLsr7ftKrDclar/ew21+oO99pO56o222l1lnklhqGYttOvbHHLGhzCGo4uN1LFOkSLB0sOBtwp0tLwSIEWub79aJkBfuOdtQ+/+u2f93/62KufPfnawSde
*/