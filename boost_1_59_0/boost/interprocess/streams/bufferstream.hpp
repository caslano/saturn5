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

   virtual ~basic_bufferbuf() BOOST_OVERRIDE {}

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
   virtual int_type underflow() BOOST_OVERRIDE
   {
      // Precondition: gptr() >= egptr(). Returns a character, if available.
      return this->gptr() != this->egptr() ?
         CharTraits::to_int_type(*this->gptr()) : CharTraits::eof();
   }

   virtual int_type pbackfail(int_type c = CharTraits::eof()) BOOST_OVERRIDE
   {
      if(this->gptr() != this->eback()) {
         if(!CharTraits::eq_int_type(c, CharTraits::eof())) {
            if(CharTraits::eq(CharTraits::to_char_type(c), this->gptr()[-1])) {
               this->gbump(-1);
               return c;
            }
            else if(m_mode & std::ios_base::out) {
               this->gbump(-1);
               *this->gptr() = CharTraits::to_char_type(c);
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

   virtual int_type overflow(int_type c = CharTraits::eof()) BOOST_OVERRIDE
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
                                 = std::ios_base::in | std::ios_base::out) BOOST_OVERRIDE
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
                                 = std::ios_base::in | std::ios_base::out) BOOST_OVERRIDE
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