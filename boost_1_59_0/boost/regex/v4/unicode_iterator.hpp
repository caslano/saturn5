/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         unicode_iterator.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Iterator adapters for converting between different Unicode encodings.
  */

/****************************************************************************

Contents:
~~~~~~~~~

1) Read Only, Input Adapters:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class BaseIterator, class U8Type = ::boost::uint8_t>
class u32_to_u8_iterator;

Adapts sequence of UTF-32 code points to "look like" a sequence of UTF-8.

template <class BaseIterator, class U32Type = ::boost::uint32_t>
class u8_to_u32_iterator;

Adapts sequence of UTF-8 code points to "look like" a sequence of UTF-32.

template <class BaseIterator, class U16Type = ::boost::uint16_t>
class u32_to_u16_iterator;

Adapts sequence of UTF-32 code points to "look like" a sequence of UTF-16.

template <class BaseIterator, class U32Type = ::boost::uint32_t>
class u16_to_u32_iterator;

Adapts sequence of UTF-16 code points to "look like" a sequence of UTF-32.

2) Single pass output iterator adapters:

template <class BaseIterator>
class utf8_output_iterator;

Accepts UTF-32 code points and forwards them on as UTF-8 code points.

template <class BaseIterator>
class utf16_output_iterator;

Accepts UTF-32 code points and forwards them on as UTF-16 code points.

****************************************************************************/

#ifndef BOOST_REGEX_V4_UNICODE_ITERATOR_HPP
#define BOOST_REGEX_V4_UNICODE_ITERATOR_HPP
#include <boost/cstdint.hpp>
#include <boost/regex/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#ifndef BOOST_NO_STD_LOCALE
#include <sstream>
#include <ios>
#endif
#include <limits.h> // CHAR_BIT

#ifdef BOOST_REGEX_CXX03

#else
#endif

namespace boost{

namespace detail{

static const ::boost::uint16_t high_surrogate_base = 0xD7C0u;
static const ::boost::uint16_t low_surrogate_base = 0xDC00u;
static const ::boost::uint32_t ten_bit_mask = 0x3FFu;

inline bool is_high_surrogate(::boost::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xd800u;
}
inline bool is_low_surrogate(::boost::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xdc00u;
}
template <class T>
inline bool is_surrogate(T v)
{
   return (v & 0xFFFFF800u) == 0xd800;
}

inline unsigned utf8_byte_count(boost::uint8_t c)
{
   // if the most significant bit with a zero in it is in position
   // 8-N then there are N bytes in this UTF-8 sequence:
   boost::uint8_t mask = 0x80u;
   unsigned result = 0;
   while(c & mask)
   {
      ++result;
      mask >>= 1;
   }
   return (result == 0) ? 1 : ((result > 4) ? 4 : result);
}

inline unsigned utf8_trailing_byte_count(boost::uint8_t c)
{
   return utf8_byte_count(c) - 1;
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4100)
#endif
#ifndef BOOST_NO_EXCEPTIONS
BOOST_NORETURN
#endif
inline void invalid_utf32_code_point(::boost::uint32_t val)
{
#ifndef BOOST_NO_STD_LOCALE
   std::stringstream ss;
   ss << "Invalid UTF-32 code point U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-16 sequence";
   std::out_of_range e(ss.str());
#else
   std::out_of_range e("Invalid UTF-32 code point encountered while trying to encode UTF-16 sequence");
#endif
   boost::throw_exception(e);
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


} // namespace detail

template <class BaseIterator, class U16Type = ::boost::uint16_t>
class u32_to_u16_iterator
{
#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 32);
   BOOST_STATIC_ASSERT(sizeof(U16Type)*CHAR_BIT == 16);
#endif

public:
   typedef std::ptrdiff_t     difference_type;
   typedef U16Type            value_type;
   typedef value_type const*  pointer;
   typedef value_type const   reference;
   typedef std::bidirectional_iterator_tag iterator_category;

   reference operator*()const
   {
      if(m_current == 2)
         extract_current();
      return m_values[m_current];
   }
   bool operator==(const u32_to_u16_iterator& that)const
   {
      if(m_position == that.m_position)
      {
         // Both m_currents must be equal, or both even
         // this is the same as saying their sum must be even:
         return (m_current + that.m_current) & 1u ? false : true;
      }
      return false;
   }
   bool operator!=(const u32_to_u16_iterator& that)const
   {
      return !(*this == that);
   }
   u32_to_u16_iterator& operator++()
   {
      // if we have a pending read then read now, so that we know whether
      // to skip a position, or move to a low-surrogate:
      if(m_current == 2)
      {
         // pending read:
         extract_current();
      }
      // move to the next surrogate position:
      ++m_current;
      // if we've reached the end skip a position:
      if(m_values[m_current] == 0)
      {
         m_current = 2;
         ++m_position;
      }
      return *this;
   }
   u32_to_u16_iterator operator++(int)
   {
      u32_to_u16_iterator r(*this);
      ++(*this);
      return r;
   }
   u32_to_u16_iterator& operator--()
   {
      if(m_current != 1)
      {
         // decrementing an iterator always leads to a valid position:
         --m_position;
         extract_current();
         m_current = m_values[1] ? 1 : 0;
      }
      else
      {
         m_current = 0;
      }
      return *this;
   }
   u32_to_u16_iterator operator--(int)
   {
      u32_to_u16_iterator r(*this);
      --(*this);
      return r;
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u32_to_u16_iterator() : m_position(), m_current(0)
   {
      m_values[0] = 0;
      m_values[1] = 0;
      m_values[2] = 0;
   }
   u32_to_u16_iterator(BaseIterator b) : m_position(b), m_current(2)
   {
      m_values[0] = 0;
      m_values[1] = 0;
      m_values[2] = 0;
   }
private:

   void extract_current()const
   {
      // begin by checking for a code point out of range:
      ::boost::uint32_t v = *m_position;
      if(v >= 0x10000u)
      {
         if(v > 0x10FFFFu)
            detail::invalid_utf32_code_point(*m_position);
         // split into two surrogates:
         m_values[0] = static_cast<U16Type>(v >> 10) + detail::high_surrogate_base;
         m_values[1] = static_cast<U16Type>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
         m_current = 0;
         BOOST_REGEX_ASSERT(detail::is_high_surrogate(m_values[0]));
         BOOST_REGEX_ASSERT(detail::is_low_surrogate(m_values[1]));
      }
      else
      {
         // 16-bit code point:
         m_values[0] = static_cast<U16Type>(*m_position);
         m_values[1] = 0;
         m_current = 0;
         // value must not be a surrogate:
         if(detail::is_surrogate(m_values[0]))
            detail::invalid_utf32_code_point(*m_position);
      }
   }
   BaseIterator m_position;
   mutable U16Type m_values[3];
   mutable unsigned m_current;
};

template <class BaseIterator, class U32Type = ::boost::uint32_t>
class u16_to_u32_iterator
{
   // special values for pending iterator reads:
   BOOST_STATIC_CONSTANT(U32Type, pending_read = 0xffffffffu);

#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 16);
   BOOST_STATIC_ASSERT(sizeof(U32Type)*CHAR_BIT == 32);
#endif

public:
   typedef std::ptrdiff_t     difference_type;
   typedef U32Type            value_type;
   typedef value_type const*  pointer;
   typedef value_type const   reference;
   typedef std::bidirectional_iterator_tag iterator_category;

   reference operator*()const
   {
      if(m_value == pending_read)
         extract_current();
      return m_value;
   }
   bool operator==(const u16_to_u32_iterator& that)const
   {
      return m_position == that.m_position;
   }
   bool operator!=(const u16_to_u32_iterator& that)const
   {
      return !(*this == that);
   }
   u16_to_u32_iterator& operator++()
   {
      // skip high surrogate first if there is one:
      if(detail::is_high_surrogate(*m_position)) ++m_position;
      ++m_position;
      m_value = pending_read;
      return *this;
   }
   u16_to_u32_iterator operator++(int)
   {
      u16_to_u32_iterator r(*this);
      ++(*this);
      return r;
   }
   u16_to_u32_iterator& operator--()
   {
      --m_position;
      // if we have a low surrogate then go back one more:
      if(detail::is_low_surrogate(*m_position)) 
         --m_position;
      m_value = pending_read;
      return *this;
   }
   u16_to_u32_iterator operator--(int)
   {
      u16_to_u32_iterator r(*this);
      --(*this);
      return r;
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u16_to_u32_iterator() : m_position()
   {
      m_value = pending_read;
   }
   u16_to_u32_iterator(BaseIterator b) : m_position(b)
   {
      m_value = pending_read;
   }
   //
   // Range checked version:
   //
   u16_to_u32_iterator(BaseIterator b, BaseIterator start, BaseIterator end) : m_position(b)
   {
      m_value = pending_read;
      //
      // The range must not start with a low surrogate, or end in a high surrogate,
      // otherwise we run the risk of running outside the underlying input range.
      // Likewise b must not be located at a low surrogate.
      //
      boost::uint16_t val;
      if(start != end)
      {
         if((b != start) && (b != end))
         {
            val = *b;
            if(detail::is_surrogate(val) && ((val & 0xFC00u) == 0xDC00u))
               invalid_code_point(val);
         }
         val = *start;
         if(detail::is_surrogate(val) && ((val & 0xFC00u) == 0xDC00u))
            invalid_code_point(val);
         val = *--end;
         if(detail::is_high_surrogate(val))
            invalid_code_point(val);
      }
   }
private:
   static void invalid_code_point(::boost::uint16_t val)
   {
#ifndef BOOST_NO_STD_LOCALE
      std::stringstream ss;
      ss << "Misplaced UTF-16 surrogate U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-32 sequence";
      std::out_of_range e(ss.str());
#else
      std::out_of_range e("Misplaced UTF-16 surrogate encountered while trying to encode UTF-32 sequence");
#endif
      boost::throw_exception(e);
   }
   void extract_current()const
   {
      m_value = static_cast<U32Type>(static_cast< ::boost::uint16_t>(*m_position));
      // if the last value is a high surrogate then adjust m_position and m_value as needed:
      if(detail::is_high_surrogate(*m_position))
      {
         // precondition; next value must have be a low-surrogate:
         BaseIterator next(m_position);
         ::boost::uint16_t t = *++next;
         if((t & 0xFC00u) != 0xDC00u)
            invalid_code_point(t);
         m_value = (m_value - detail::high_surrogate_base) << 10;
         m_value |= (static_cast<U32Type>(static_cast< ::boost::uint16_t>(t)) & detail::ten_bit_mask);
      }
      // postcondition; result must not be a surrogate:
      if(detail::is_surrogate(m_value))
         invalid_code_point(static_cast< ::boost::uint16_t>(m_value));
   }
   BaseIterator m_position;
   mutable U32Type m_value;
};

template <class BaseIterator, class U8Type = ::boost::uint8_t>
class u32_to_u8_iterator
{
#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 32);
   BOOST_STATIC_ASSERT(sizeof(U8Type)*CHAR_BIT == 8);
#endif

public:
   typedef std::ptrdiff_t     difference_type;
   typedef U8Type             value_type;
   typedef value_type const*  pointer;
   typedef value_type const   reference;
   typedef std::bidirectional_iterator_tag iterator_category;

   reference operator*()const
   {
      if(m_current == 4)
         extract_current();
      return m_values[m_current];
   }
   bool operator==(const u32_to_u8_iterator& that)const
   {
      if(m_position == that.m_position)
      {
         // either the m_current's must be equal, or one must be 0 and 
         // the other 4: which means neither must have bits 1 or 2 set:
         return (m_current == that.m_current)
            || (((m_current | that.m_current) & 3) == 0);
      }
      return false;
   }
   bool operator!=(const u32_to_u8_iterator& that)const
   {
      return !(*this == that);
   }
   u32_to_u8_iterator& operator++()
   {
      // if we have a pending read then read now, so that we know whether
      // to skip a position, or move to a low-surrogate:
      if(m_current == 4)
      {
         // pending read:
         extract_current();
      }
      // move to the next surrogate position:
      ++m_current;
      // if we've reached the end skip a position:
      if(m_values[m_current] == 0)
      {
         m_current = 4;
         ++m_position;
      }
      return *this;
   }
   u32_to_u8_iterator operator++(int)
   {
      u32_to_u8_iterator r(*this);
      ++(*this);
      return r;
   }
   u32_to_u8_iterator& operator--()
   {
      if((m_current & 3) == 0)
      {
         --m_position;
         extract_current();
         m_current = 3;
         while(m_current && (m_values[m_current] == 0))
            --m_current;
      }
      else
         --m_current;
      return *this;
   }
   u32_to_u8_iterator operator--(int)
   {
      u32_to_u8_iterator r(*this);
      --(*this);
      return r;
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u32_to_u8_iterator() : m_position(), m_current(0)
   {
      m_values[0] = 0;
      m_values[1] = 0;
      m_values[2] = 0;
      m_values[3] = 0;
      m_values[4] = 0;
   }
   u32_to_u8_iterator(BaseIterator b) : m_position(b), m_current(4)
   {
      m_values[0] = 0;
      m_values[1] = 0;
      m_values[2] = 0;
      m_values[3] = 0;
      m_values[4] = 0;
   }
private:

   void extract_current()const
   {
      boost::uint32_t c = *m_position;
      if(c > 0x10FFFFu)
         detail::invalid_utf32_code_point(c);
      if(c < 0x80u)
      {
         m_values[0] = static_cast<unsigned char>(c);
         m_values[1] = static_cast<unsigned char>(0u);
         m_values[2] = static_cast<unsigned char>(0u);
         m_values[3] = static_cast<unsigned char>(0u);
      }
      else if(c < 0x800u)
      {
         m_values[0] = static_cast<unsigned char>(0xC0u + (c >> 6));
         m_values[1] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
         m_values[2] = static_cast<unsigned char>(0u);
         m_values[3] = static_cast<unsigned char>(0u);
      }
      else if(c < 0x10000u)
      {
         m_values[0] = static_cast<unsigned char>(0xE0u + (c >> 12));
         m_values[1] = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         m_values[2] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
         m_values[3] = static_cast<unsigned char>(0u);
      }
      else
      {
         m_values[0] = static_cast<unsigned char>(0xF0u + (c >> 18));
         m_values[1] = static_cast<unsigned char>(0x80u + ((c >> 12) & 0x3Fu));
         m_values[2] = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         m_values[3] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
      m_current= 0;
   }
   BaseIterator m_position;
   mutable U8Type m_values[5];
   mutable unsigned m_current;
};

template <class BaseIterator, class U32Type = ::boost::uint32_t>
class u8_to_u32_iterator
{
   // special values for pending iterator reads:
   BOOST_STATIC_CONSTANT(U32Type, pending_read = 0xffffffffu);

#if !defined(BOOST_NO_STD_ITERATOR_TRAITS)
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 8);
   BOOST_STATIC_ASSERT(sizeof(U32Type)*CHAR_BIT == 32);
#endif

public:
   typedef std::ptrdiff_t     difference_type;
   typedef U32Type            value_type;
   typedef value_type const*  pointer;
   typedef value_type const   reference;
   typedef std::bidirectional_iterator_tag iterator_category;

   reference operator*()const
   {
      if(m_value == pending_read)
         extract_current();
      return m_value;
   }
   bool operator==(const u8_to_u32_iterator& that)const
   {
      return m_position == that.m_position;
   }
   bool operator!=(const u8_to_u32_iterator& that)const
   {
      return !(*this == that);
   }
   u8_to_u32_iterator& operator++()
   {
      // We must not start with a continuation character:
      if((static_cast<boost::uint8_t>(*m_position) & 0xC0) == 0x80)
         invalid_sequence();
      // skip high surrogate first if there is one:
      unsigned c = detail::utf8_byte_count(*m_position);
      if(m_value == pending_read)
      {
         // Since we haven't read in a value, we need to validate the code points:
         for(unsigned i = 0; i < c; ++i)
         {
            ++m_position;
            // We must have a continuation byte:
            if((i != c - 1) && ((static_cast<boost::uint8_t>(*m_position) & 0xC0) != 0x80))
               invalid_sequence();
         }
      }
      else
      {
         std::advance(m_position, c);
      }
      m_value = pending_read;
      return *this;
   }
   u8_to_u32_iterator operator++(int)
   {
      u8_to_u32_iterator r(*this);
      ++(*this);
      return r;
   }
   u8_to_u32_iterator& operator--()
   {
      // Keep backtracking until we don't have a trailing character:
      unsigned count = 0;
      while((*--m_position & 0xC0u) == 0x80u) ++count;
      // now check that the sequence was valid:
      if(count != detail::utf8_trailing_byte_count(*m_position))
         invalid_sequence();
      m_value = pending_read;
      return *this;
   }
   u8_to_u32_iterator operator--(int)
   {
      u8_to_u32_iterator r(*this);
      --(*this);
      return r;
   }
   BaseIterator base()const
   {
      return m_position;
   }
   // construct:
   u8_to_u32_iterator() : m_position()
   {
      m_value = pending_read;
   }
   u8_to_u32_iterator(BaseIterator b) : m_position(b)
   {
      m_value = pending_read;
   }
   //
   // Checked constructor:
   //
   u8_to_u32_iterator(BaseIterator b, BaseIterator start, BaseIterator end) : m_position(b)
   {
      m_value = pending_read;
      //
      // We must not start with a continuation character, or end with a 
      // truncated UTF-8 sequence otherwise we run the risk of going past
      // the start/end of the underlying sequence:
      //
      if(start != end)
      {
         unsigned char v = *start;
         if((v & 0xC0u) == 0x80u)
            invalid_sequence();
         if((b != start) && (b != end) && ((*b & 0xC0u) == 0x80u))
            invalid_sequence();
         BaseIterator pos = end;
         do
         {
            v = *--pos;
         }
         while((start != pos) && ((v & 0xC0u) == 0x80u));
         std::ptrdiff_t extra = detail::utf8_byte_count(v);
         if(std::distance(pos, end) < extra)
            invalid_sequence();
      }
   }
private:
   static void invalid_sequence()
   {
      std::out_of_range e("Invalid UTF-8 sequence encountered while trying to encode UTF-32 character");
      boost::throw_exception(e);
   }
   void extract_current()const
   {
      m_value = static_cast<U32Type>(static_cast< ::boost::uint8_t>(*m_position));
      // we must not have a continuation character:
      if((m_value & 0xC0u) == 0x80u)
         invalid_sequence();
      // see how many extra bytes we have:
      unsigned extra = detail::utf8_trailing_byte_count(*m_position);
      // extract the extra bits, 6 from each extra byte:
      BaseIterator next(m_position);
      for(unsigned c = 0; c < extra; ++c)
      {
         ++next;
         m_value <<= 6;
         // We must have a continuation byte:
         if((static_cast<boost::uint8_t>(*next) & 0xC0) != 0x80)
            invalid_sequence();
         m_value += static_cast<boost::uint8_t>(*next) & 0x3Fu;
      }
      // we now need to remove a few of the leftmost bits, but how many depends
      // upon how many extra bytes we've extracted:
      static const boost::uint32_t masks[4] = 
      {
         0x7Fu,
         0x7FFu,
         0xFFFFu,
         0x1FFFFFu,
      };
      m_value &= masks[extra];
      // check the result is in range:
      if(m_value > static_cast<U32Type>(0x10FFFFu))
         invalid_sequence();
      // The result must not be a surrogate:
      if((m_value >= static_cast<U32Type>(0xD800)) && (m_value <= static_cast<U32Type>(0xDFFF)))
         invalid_sequence();
      // We should not have had an invalidly encoded UTF8 sequence:
      if((extra > 0) && (m_value <= static_cast<U32Type>(masks[extra - 1])))
         invalid_sequence();
   }
   BaseIterator m_position;
   mutable U32Type m_value;
};

template <class BaseIterator>
class utf16_output_iterator
{
public:
   typedef void                                   difference_type;
   typedef void                                   value_type;
   typedef boost::uint32_t*                       pointer;
   typedef boost::uint32_t&                       reference;
   typedef std::output_iterator_tag               iterator_category;

   utf16_output_iterator(const BaseIterator& b)
      : m_position(b){}
   utf16_output_iterator(const utf16_output_iterator& that)
      : m_position(that.m_position){}
   utf16_output_iterator& operator=(const utf16_output_iterator& that)
   {
      m_position = that.m_position;
      return *this;
   }
   const utf16_output_iterator& operator*()const
   {
      return *this;
   }
   void operator=(boost::uint32_t val)const
   {
      push(val);
   }
   utf16_output_iterator& operator++()
   {
      return *this;
   }
   utf16_output_iterator& operator++(int)
   {
      return *this;
   }
   BaseIterator base()const
   {
      return m_position;
   }
private:
   void push(boost::uint32_t v)const
   {
      if(v >= 0x10000u)
      {
         // begin by checking for a code point out of range:
         if(v > 0x10FFFFu)
            detail::invalid_utf32_code_point(v);
         // split into two surrogates:
         *m_position++ = static_cast<boost::uint16_t>(v >> 10) + detail::high_surrogate_base;
         *m_position++ = static_cast<boost::uint16_t>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
      }
      else
      {
         // 16-bit code point:
         // value must not be a surrogate:
         if(detail::is_surrogate(v))
            detail::invalid_utf32_code_point(v);
         *m_position++ = static_cast<boost::uint16_t>(v);
      }
   }
   mutable BaseIterator m_position;
};

template <class BaseIterator>
class utf8_output_iterator
{
public:
   typedef void                                   difference_type;
   typedef void                                   value_type;
   typedef boost::uint32_t*                       pointer;
   typedef boost::uint32_t&                       reference;
   typedef std::output_iterator_tag               iterator_category;

   utf8_output_iterator(const BaseIterator& b)
      : m_position(b){}
   utf8_output_iterator(const utf8_output_iterator& that)
      : m_position(that.m_position){}
   utf8_output_iterator& operator=(const utf8_output_iterator& that)
   {
      m_position = that.m_position;
      return *this;
   }
   const utf8_output_iterator& operator*()const
   {
      return *this;
   }
   void operator=(boost::uint32_t val)const
   {
      push(val);
   }
   utf8_output_iterator& operator++()
   {
      return *this;
   }
   utf8_output_iterator& operator++(int)
   {
      return *this;
   }
   BaseIterator base()const
   {
      return m_position;
   }
private:
   void push(boost::uint32_t c)const
   {
      if(c > 0x10FFFFu)
         detail::invalid_utf32_code_point(c);
      if(c < 0x80u)
      {
         *m_position++ = static_cast<unsigned char>(c);
      }
      else if(c < 0x800u)
      {
         *m_position++ = static_cast<unsigned char>(0xC0u + (c >> 6));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
      else if(c < 0x10000u)
      {
         *m_position++ = static_cast<unsigned char>(0xE0u + (c >> 12));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
      else
      {
         *m_position++ = static_cast<unsigned char>(0xF0u + (c >> 18));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 12) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
         *m_position++ = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
      }
   }
   mutable BaseIterator m_position;
};

} // namespace boost

#endif // BOOST_REGEX_UNICODE_ITERATOR_HPP


/* unicode_iterator.hpp
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
*/