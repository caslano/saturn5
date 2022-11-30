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

template <class BaseIterator, class U8Type = std::uint8_t>
class u32_to_u8_iterator;

Adapts sequence of UTF-32 code points to "look like" a sequence of UTF-8.

template <class BaseIterator, class U32Type = std::uint32_t>
class u8_to_u32_iterator;

Adapts sequence of UTF-8 code points to "look like" a sequence of UTF-32.

template <class BaseIterator, class U16Type = std::uint16_t>
class u32_to_u16_iterator;

Adapts sequence of UTF-32 code points to "look like" a sequence of UTF-16.

template <class BaseIterator, class U32Type = std::uint32_t>
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

#ifndef BOOST_REGEX_UNICODE_ITERATOR_HPP
#define BOOST_REGEX_UNICODE_ITERATOR_HPP
#include <cstdint>
#include <boost/regex/config.hpp>
#include <stdexcept>
#include <sstream>
#include <ios>
#include <limits.h> // CHAR_BIT

#ifndef BOOST_REGEX_STANDALONE
#include <boost/throw_exception.hpp>
#endif

namespace boost{

namespace detail{

static const std::uint16_t high_surrogate_base = 0xD7C0u;
static const std::uint16_t low_surrogate_base = 0xDC00u;
static const std::uint32_t ten_bit_mask = 0x3FFu;

inline bool is_high_surrogate(std::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xd800u;
}
inline bool is_low_surrogate(std::uint16_t v)
{
   return (v & 0xFFFFFC00u) == 0xdc00u;
}
template <class T>
inline bool is_surrogate(T v)
{
   return (v & 0xFFFFF800u) == 0xd800;
}

inline unsigned utf8_byte_count(std::uint8_t c)
{
   // if the most significant bit with a zero in it is in position
   // 8-N then there are N bytes in this UTF-8 sequence:
   std::uint8_t mask = 0x80u;
   unsigned result = 0;
   while(c & mask)
   {
      ++result;
      mask >>= 1;
   }
   return (result == 0) ? 1 : ((result > 4) ? 4 : result);
}

inline unsigned utf8_trailing_byte_count(std::uint8_t c)
{
   return utf8_byte_count(c) - 1;
}

#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable:4100)
#endif
#ifndef BOOST_NO_EXCEPTIONS
BOOST_REGEX_NORETURN
#endif
inline void invalid_utf32_code_point(std::uint32_t val)
{
   std::stringstream ss;
   ss << "Invalid UTF-32 code point U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-16 sequence";
   std::out_of_range e(ss.str());
#ifndef BOOST_REGEX_STANDALONE
   boost::throw_exception(e);
#else
   throw e;
#endif
}
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif


} // namespace detail

template <class BaseIterator, class U16Type = std::uint16_t>
class u32_to_u16_iterator
{
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   static_assert(sizeof(base_value_type)*CHAR_BIT == 32, "Incorrectly sized template argument");
   static_assert(sizeof(U16Type)*CHAR_BIT == 16, "Incorrectly sized template argument");

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
      std::uint32_t v = *m_position;
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

template <class BaseIterator, class U32Type = std::uint32_t>
class u16_to_u32_iterator
{
   // special values for pending iterator reads:
   static const U32Type pending_read = 0xffffffffu;

   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   static_assert(sizeof(base_value_type)*CHAR_BIT == 16, "Incorrectly sized template argument");
   static_assert(sizeof(U32Type)*CHAR_BIT == 32, "Incorrectly sized template argument");

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
      std::uint16_t val;
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
   static void invalid_code_point(std::uint16_t val)
   {
      std::stringstream ss;
      ss << "Misplaced UTF-16 surrogate U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-32 sequence";
      std::out_of_range e(ss.str());
#ifndef BOOST_REGEX_STANDALONE
      boost::throw_exception(e);
#else
      throw e;
#endif
   }
   void extract_current()const
   {
      m_value = static_cast<U32Type>(static_cast< std::uint16_t>(*m_position));
      // if the last value is a high surrogate then adjust m_position and m_value as needed:
      if(detail::is_high_surrogate(*m_position))
      {
         // precondition; next value must have be a low-surrogate:
         BaseIterator next(m_position);
         std::uint16_t t = *++next;
         if((t & 0xFC00u) != 0xDC00u)
            invalid_code_point(t);
         m_value = (m_value - detail::high_surrogate_base) << 10;
         m_value |= (static_cast<U32Type>(static_cast< std::uint16_t>(t)) & detail::ten_bit_mask);
      }
      // postcondition; result must not be a surrogate:
      if(detail::is_surrogate(m_value))
         invalid_code_point(static_cast< std::uint16_t>(m_value));
   }
   BaseIterator m_position;
   mutable U32Type m_value;
};

template <class BaseIterator, class U8Type = std::uint8_t>
class u32_to_u8_iterator
{
   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   static_assert(sizeof(base_value_type)*CHAR_BIT == 32, "Incorrectly sized template argument");
   static_assert(sizeof(U8Type)*CHAR_BIT == 8, "Incorrectly sized template argument");

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
      std::uint32_t c = *m_position;
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

template <class BaseIterator, class U32Type = std::uint32_t>
class u8_to_u32_iterator
{
   // special values for pending iterator reads:
   static const U32Type pending_read = 0xffffffffu;

   typedef typename std::iterator_traits<BaseIterator>::value_type base_value_type;

   static_assert(sizeof(base_value_type)*CHAR_BIT == 8, "Incorrectly sized template argument");
   static_assert(sizeof(U32Type)*CHAR_BIT == 32, "Incorrectly sized template argument");

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
      if((static_cast<std::uint8_t>(*m_position) & 0xC0) == 0x80)
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
            if((i != c - 1) && ((static_cast<std::uint8_t>(*m_position) & 0xC0) != 0x80))
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
#ifndef BOOST_REGEX_STANDALONE
      boost::throw_exception(e);
#else
      throw e;
#endif
   }
   void extract_current()const
   {
      m_value = static_cast<U32Type>(static_cast< std::uint8_t>(*m_position));
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
         if((static_cast<std::uint8_t>(*next) & 0xC0) != 0x80)
            invalid_sequence();
         m_value += static_cast<std::uint8_t>(*next) & 0x3Fu;
      }
      // we now need to remove a few of the leftmost bits, but how many depends
      // upon how many extra bytes we've extracted:
      static const std::uint32_t masks[4] = 
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
   typedef std::uint32_t*                         pointer;
   typedef std::uint32_t&                         reference;
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
   void operator=(std::uint32_t val)const
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
   void push(std::uint32_t v)const
   {
      if(v >= 0x10000u)
      {
         // begin by checking for a code point out of range:
         if(v > 0x10FFFFu)
            detail::invalid_utf32_code_point(v);
         // split into two surrogates:
         *m_position++ = static_cast<std::uint16_t>(v >> 10) + detail::high_surrogate_base;
         *m_position++ = static_cast<std::uint16_t>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
      }
      else
      {
         // 16-bit code point:
         // value must not be a surrogate:
         if(detail::is_surrogate(v))
            detail::invalid_utf32_code_point(v);
         *m_position++ = static_cast<std::uint16_t>(v);
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
   typedef std::uint32_t*                       pointer;
   typedef std::uint32_t&                       reference;
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
   void operator=(std::uint32_t val)const
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
   void push(std::uint32_t c)const
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