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

#ifndef BOOST_REGEX_V5_SUB_MATCH_HPP
#define BOOST_REGEX_V5_SUB_MATCH_HPP

namespace boost{

template <class BidiIterator>
struct sub_match : public std::pair<BidiIterator, BidiIterator>
{
   typedef typename std::iterator_traits<BidiIterator>::value_type       value_type;
   typedef typename std::iterator_traits<BidiIterator>::difference_type  difference_type;
   typedef          BidiIterator                                                     iterator_type;
   typedef          BidiIterator                                                     iterator;
   typedef          BidiIterator                                                     const_iterator;

   bool matched;

   sub_match() : std::pair<BidiIterator, BidiIterator>(), matched(false) {}
   sub_match(BidiIterator i) : std::pair<BidiIterator, BidiIterator>(i, i), matched(false) {}
   template <class T, class A>
   operator std::basic_string<value_type, T, A> ()const
   {
      return matched ? std::basic_string<value_type, T, A>(this->first, this->second) : std::basic_string<value_type, T, A>();
   }
   difference_type  length()const
   {
      difference_type n = matched ? std::distance((BidiIterator)this->first, (BidiIterator)this->second) : 0;
      return n;
   }
   std::basic_string<value_type> str()const
   {
      std::basic_string<value_type> result;
      if(matched)
      {
         std::size_t len = std::distance((BidiIterator)this->first, (BidiIterator)this->second);
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
   bool  operator !=(const sub_match& that)const
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
   mutable std::unique_ptr<capture_sequence_type> m_captures;
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
};

typedef sub_match<const char*> csub_match;
typedef sub_match<std::string::const_iterator> ssub_match;
#ifndef BOOST_NO_WREGEX
typedef sub_match<const wchar_t*> wcsub_match;
typedef sub_match<std::wstring::const_iterator> wssub_match;
#endif

// comparison to std::basic_string<> part 1:
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator == (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator != (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator < (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator <= (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator >= (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) >= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator > (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) > 0; }
// comparison to std::basic_string<> part 2:
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) >= 0; }
// comparison to const charT* part 1:
template <class RandomAccessIterator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
inline bool operator == (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
inline bool operator != (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) <= 0; }

// comparison to const charT& part 1:
template <class RandomAccessIterator>
inline bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
inline bool operator == (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
inline bool operator != (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
inline bool operator < (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
inline bool operator > (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
inline bool operator <= (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
inline bool operator >= (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }

// addition operators:
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator, class traits, class Allocator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> 
operator + (const sub_match<RandomAccessIterator>& m,
            const std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type, traits, Allocator> result;
   result.reserve(s.size() + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
template <class RandomAccessIterator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename std::iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename std::iterator_traits<RandomAccessIterator>::value_type const * s)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(std::char_traits<typename std::iterator_traits<RandomAccessIterator>::value_type>::length(s) + m.length() + 1);
   return result.append(m.first, m.second).append(s);
}
template <class RandomAccessIterator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> 
operator + (typename std::iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(1, s).append(m.first, m.second);
}
template <class RandomAccessIterator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m,
            typename std::iterator_traits<RandomAccessIterator>::value_type const& s)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m.length() + 2);
   return result.append(m.first, m.second).append(1, s);
}
template <class RandomAccessIterator>
inline std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> 
operator + (const sub_match<RandomAccessIterator>& m1,
            const sub_match<RandomAccessIterator>& m2)
{
   std::basic_string<typename std::iterator_traits<RandomAccessIterator>::value_type> result;
   result.reserve(m1.length() + m2.length() + 1);
   return result.append(m1.first, m1.second).append(m2.first, m2.second);
}
template <class charT, class traits, class RandomAccessIterator>
std::basic_ostream<charT, traits>&
   operator << (std::basic_ostream<charT, traits>& os,
                const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}

} // namespace boost

#endif


/* sub_match.hpp
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
*/