//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
// This file comes from SGI's sstream file. Modified by Ion Gaztanaga 2005-2012.
// Changed internal SGI string to a buffer. Added efficient
// internal buffer get/set/swap functions, so that we can obtain/establish the
// internal buffer without any reallocation or copy. Kill those temporaries!
///////////////////////////////////////////////////////////////////////////////
/*
 * Copyright (c) 1998
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

//!\file
//!This file defines basic_bufferbuf, basic_ibufferstream,
//!basic_obufferstream, and basic_bufferstream classes. These classes
//!represent streamsbufs and streams whose sources or destinations
//!are fixed size character buffers.

#ifndef BOOST_INTERPROCESS_BUFFERSTREAM_HPP
#define BOOST_INTERPROCESS_BUFFERSTREAM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <string>    // char traits
#include <cstddef>   // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/interprocess/interprocess_fwd.hpp>

namespace boost {  namespace interprocess {

//!A streambuf class that controls the transmission of elements to and from
//!a basic_xbufferstream. The elements are transmitted from a to a fixed
//!size buffer
template <class CharT, class CharTraits>
class basic_bufferbuf
   : public std::basic_streambuf<CharT, CharTraits>
{
   public:
   typedef CharT                                         char_type;
   typedef typename CharTraits::int_type                 int_type;
   typedef typename CharTraits::pos_type                 pos_type;
   typedef typename CharTraits::off_type                 off_type;
   typedef CharTraits                                    traits_type;
   typedef std::basic_streambuf<char_type, traits_type>  basic_streambuf_t;

   public:
   //!Constructor.
   //!Does not throw.
   explicit basic_bufferbuf(std::ios_base::openmode mode
                            = std::ios_base::in | std::ios_base::out)
      :  basic_streambuf_t(), m_mode(mode), m_buffer(0), m_length(0)
      {}

   //!Constructor. Assigns formatting buffer.
   //!Does not throw.
   explicit basic_bufferbuf(CharT *buf, std::size_t length,
                            std::ios_base::openmode mode
                              = std::ios_base::in | std::ios_base::out)
      :  basic_streambuf_t(), m_mode(mode), m_buffer(buf), m_length(length)
      {  this->set_pointers();   }

   virtual ~basic_bufferbuf(){}

   public:
   //!Returns the pointer and size of the internal buffer.
   //!Does not throw.
   std::pair<CharT *, std::size_t> buffer() const
      { return std::pair<CharT *, std::size_t>(m_buffer, m_length); }

   //!Sets the underlying buffer to a new value
   //!Does not throw.
   void buffer(CharT *buf, std::size_t length)
      {  m_buffer = buf;   m_length = length;   this->set_pointers();   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   void set_pointers()
   {
      // The initial read position is the beginning of the buffer.
      if(m_mode & std::ios_base::in)
         this->setg(m_buffer, m_buffer, m_buffer + m_length);

      // The initial write position is the beginning of the buffer.
      if(m_mode & std::ios_base::out)
         this->setp(m_buffer, m_buffer + m_length);
   }

   protected:
   virtual int_type underflow()
   {
      // Precondition: gptr() >= egptr(). Returns a character, if available.
      return this->gptr() != this->egptr() ?
         CharTraits::to_int_type(*this->gptr()) : CharTraits::eof();
   }

   virtual int_type pbackfail(int_type c = CharTraits::eof())
   {
      if(this->gptr() != this->eback()) {
         if(!CharTraits::eq_int_type(c, CharTraits::eof())) {
            if(CharTraits::eq(CharTraits::to_char_type(c), this->gptr()[-1])) {
               this->gbump(-1);
               return c;
            }
            else if(m_mode & std::ios_base::out) {
               this->gbump(-1);
               *this->gptr() = c;
               return c;
            }
            else
               return CharTraits::eof();
         }
         else {
            this->gbump(-1);
            return CharTraits::not_eof(c);
         }
      }
      else
         return CharTraits::eof();
   }

   virtual int_type overflow(int_type c = CharTraits::eof())
   {
      if(m_mode & std::ios_base::out) {
         if(!CharTraits::eq_int_type(c, CharTraits::eof())) {
//            if(!(m_mode & std::ios_base::in)) {
//               if(this->pptr() != this->epptr()) {
//                  *this->pptr() = CharTraits::to_char_type(c);
//                  this->pbump(1);
//                  return c;
//               }
//               else
//                  return CharTraits::eof();
//            }
//            else {
               if(this->pptr() == this->epptr()) {
                  //We can't append to a static buffer
                  return CharTraits::eof();
               }
               else {
                  *this->pptr() = CharTraits::to_char_type(c);
                  this->pbump(1);
                  return c;
               }
//            }
         }
         else  // c is EOF, so we don't have to do anything
            return CharTraits::not_eof(c);
      }
      else     // Overflow always fails if it's read-only.
         return CharTraits::eof();
   }

   virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir,
                              std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
   {
      bool in  = false;
      bool out = false;

      const std::ios_base::openmode inout =
         std::ios_base::in | std::ios_base::out;

      if((mode & inout) == inout) {
         if(dir == std::ios_base::beg || dir == std::ios_base::end)
            in = out = true;
      }
      else if(mode & std::ios_base::in)
         in = true;
      else if(mode & std::ios_base::out)
         out = true;

      if(!in && !out)
         return pos_type(off_type(-1));
      else if((in  && (!(m_mode & std::ios_base::in) || (off != 0 && this->gptr() == 0) )) ||
               (out && (!(m_mode & std::ios_base::out) || (off != 0 && this->pptr() == 0))))
         return pos_type(off_type(-1));

      std::streamoff newoff;
      switch(dir) {
         case std::ios_base::beg:
            newoff = 0;
         break;
         case std::ios_base::end:
            newoff = static_cast<std::streamoff>(m_length);
         break;
         case std::ios_base::cur:
            newoff = in ? static_cast<std::streamoff>(this->gptr() - this->eback())
                        : static_cast<std::streamoff>(this->pptr() - this->pbase());
         break;
         default:
            return pos_type(off_type(-1));
      }

      off += newoff;

      if(in) {
         std::ptrdiff_t n = this->egptr() - this->eback();

         if(off < 0 || off > n)
            return pos_type(off_type(-1));
         else
            this->setg(this->eback(), this->eback() + off, this->eback() + n);
      }

      if(out) {
         std::ptrdiff_t n = this->epptr() - this->pbase();

         if(off < 0 || off > n)
            return pos_type(off_type(-1));
         else {
            this->setp(this->pbase(), this->pbase() + n);
            this->pbump(static_cast<int>(off));
         }
      }

      return pos_type(off);
   }

   virtual pos_type seekpos(pos_type pos, std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
   {  return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);  }

   private:
   std::ios_base::openmode m_mode;
   CharT *                 m_buffer;
   std::size_t             m_length;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!A basic_istream class that uses a fixed size character buffer
//!as its formatting buffer.
template <class CharT, class CharTraits>
class basic_ibufferstream :
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private basic_bufferbuf<CharT, CharTraits>,
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public std::basic_istream<CharT, CharTraits>
{
   public:                         // Typedefs
   typedef typename std::basic_ios
      <CharT, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_bufferbuf<CharT, CharTraits>         bufferbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_istream<char_type, CharTraits>  basic_streambuf_t;
   bufferbuf_t &       get_buf()      {  return *this;  }
   const bufferbuf_t & get_buf() const{  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor.
   //!Does not throw.
   basic_ibufferstream(std::ios_base::openmode mode = std::ios_base::in)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
        bufferbuf_t(mode | std::ios_base::in)
      , basic_streambuf_t(this)
      {}

   //!Constructor. Assigns formatting buffer.
   //!Does not throw.
   basic_ibufferstream(const CharT *buf, std::size_t length,
                       std::ios_base::openmode mode = std::ios_base::in)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
        bufferbuf_t(const_cast<CharT*>(buf), length, mode | std::ios_base::in)
      , basic_streambuf_t(this)
      {}

   ~basic_ibufferstream(){}

   public:
   //!Returns the address of the stored
   //!stream buffer.
   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&get_buf()); }

   //!Returns the pointer and size of the internal buffer.
   //!Does not throw.
   std::pair<const CharT *, std::size_t> buffer() const
      { return get_buf().buffer(); }

   //!Sets the underlying buffer to a new value. Resets
   //!stream position. Does not throw.
   void buffer(const CharT *buf, std::size_t length)
      {  get_buf().buffer(const_cast<CharT*>(buf), length);  }
};

//!A basic_ostream class that uses a fixed size character buffer
//!as its formatting buffer.
template <class CharT, class CharTraits>
class basic_obufferstream :
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private basic_bufferbuf<CharT, CharTraits>,
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public std::basic_ostream<CharT, CharTraits>
{
   public:
   typedef typename std::basic_ios
      <CharT, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_bufferbuf<CharT, CharTraits>         bufferbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_ostream<char_type, CharTraits>  basic_ostream_t;
   bufferbuf_t &       get_buf()      {  return *this;  }
   const bufferbuf_t & get_buf() const{  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor.
   //!Does not throw.
   basic_obufferstream(std::ios_base::openmode mode = std::ios_base::out)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
         bufferbuf_t(mode | std::ios_base::out)
      ,  basic_ostream_t(this)
      {}

   //!Constructor. Assigns formatting buffer.
   //!Does not throw.
   basic_obufferstream(CharT *buf, std::size_t length,
                       std::ios_base::openmode mode = std::ios_base::out)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
         bufferbuf_t(buf, length, mode | std::ios_base::out)
      ,  basic_ostream_t(this)
      {}

   ~basic_obufferstream(){}

   public:
   //!Returns the address of the stored
   //!stream buffer.
   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&get_buf()); }

   //!Returns the pointer and size of the internal buffer.
   //!Does not throw.
   std::pair<CharT *, std::size_t> buffer() const
      { return get_buf().buffer(); }

   //!Sets the underlying buffer to a new value. Resets
   //!stream position. Does not throw.
   void buffer(CharT *buf, std::size_t length)
      {  get_buf().buffer(buf, length);  }
};


//!A basic_iostream class that uses a fixed size character buffer
//!as its formatting buffer.
template <class CharT, class CharTraits>
class basic_bufferstream :
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private basic_bufferbuf<CharT, CharTraits>,
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
   public std::basic_iostream<CharT, CharTraits>
{
   public:                         // Typedefs
   typedef typename std::basic_ios
      <CharT, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_bufferbuf<CharT, CharTraits>         bufferbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_iostream<char_type, CharTraits> basic_iostream_t;
   bufferbuf_t &       get_buf()      {  return *this;  }
   const bufferbuf_t & get_buf() const{  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor.
   //!Does not throw.
   basic_bufferstream(std::ios_base::openmode mode
                      = std::ios_base::in | std::ios_base::out)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
         bufferbuf_t(mode)
      ,  basic_iostream_t(this)
      {}

   //!Constructor. Assigns formatting buffer.
   //!Does not throw.
   basic_bufferstream(CharT *buf, std::size_t length,
                      std::ios_base::openmode mode
                        = std::ios_base::in | std::ios_base::out)
      :  //basic_ios_t() is called first (lefting it uninitialized) as it's a
         //virtual base of basic_istream. The class will be initialized when
         //basic_istream is constructed calling basic_ios_t::init().
         //As bufferbuf_t's constructor does not throw there is no risk of
         //calling the basic_ios_t's destructor without calling basic_ios_t::init()
         bufferbuf_t(buf, length, mode)
      ,  basic_iostream_t(this)
      {}

   ~basic_bufferstream(){}

   public:
   //!Returns the address of the stored
   //!stream buffer.
   basic_bufferbuf<CharT, CharTraits>* rdbuf() const
      { return const_cast<basic_bufferbuf<CharT, CharTraits>*>(&get_buf()); }

   //!Returns the pointer and size of the internal buffer.
   //!Does not throw.
   std::pair<CharT *, std::size_t> buffer() const
      { return get_buf().buffer(); }

   //!Sets the underlying buffer to a new value. Resets
   //!stream position. Does not throw.
   void buffer(CharT *buf, std::size_t length)
      {  get_buf().buffer(buf, length);  }
};

//Some typedefs to simplify usage
typedef basic_bufferbuf<char>        bufferbuf;
typedef basic_bufferstream<char>     bufferstream;
typedef basic_ibufferstream<char>    ibufferstream;
typedef basic_obufferstream<char>    obufferstream;

typedef basic_bufferbuf<wchar_t>     wbufferbuf;
typedef basic_bufferstream<wchar_t>  wbufferstream;
typedef basic_ibufferstream<wchar_t> wibufferstream;
typedef basic_obufferstream<wchar_t> wobufferstream;


}} //namespace boost {  namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif /* BOOST_INTERPROCESS_BUFFERSTREAM_HPP */

/* bufferstream.hpp
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
*/