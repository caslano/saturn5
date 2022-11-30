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
// Changed internal SGI string to a generic, templatized vector. Added efficient
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
//!This file defines basic_vectorbuf, basic_ivectorstream,
//!basic_ovectorstream, and basic_vectorstreamclasses.  These classes
//!represent streamsbufs and streams whose sources or destinations are
//!STL-like vectors that can be swapped with external vectors to avoid
//!unnecessary allocations/copies.

#ifndef BOOST_INTERPROCESS_VECTORSTREAM_HPP
#define BOOST_INTERPROCESS_VECTORSTREAM_HPP

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
#include <boost/interprocess/interprocess_fwd.hpp>
#include <boost/assert.hpp>

namespace boost {  namespace interprocess {

//!A streambuf class that controls the transmission of elements to and from
//!a basic_ivectorstream, basic_ovectorstream or basic_vectorstream.
//!It holds a character vector specified by CharVector template parameter
//!as its formatting buffer. The vector must have contiguous storage, like
//!std::vector, boost::interprocess::vector or boost::interprocess::basic_string
template <class CharVector, class CharTraits>
class basic_vectorbuf
   : public std::basic_streambuf<typename CharVector::value_type, CharTraits>
{
   public:
   typedef CharVector                        vector_type;
   typedef typename CharVector::value_type   char_type;
   typedef typename CharTraits::int_type     int_type;
   typedef typename CharTraits::pos_type     pos_type;
   typedef typename CharTraits::off_type     off_type;
   typedef CharTraits                        traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef std::basic_streambuf<char_type, traits_type> base_t;

   basic_vectorbuf(const basic_vectorbuf&);
   basic_vectorbuf & operator =(const basic_vectorbuf&);
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Throws if vector_type default
   //!constructor throws.
   explicit basic_vectorbuf(std::ios_base::openmode mode
                              = std::ios_base::in | std::ios_base::out)
      :  base_t(), m_mode(mode)
   {  this->initialize_pointers();   }

   //!Constructor. Throws if
   //!vector_type(const VectorParameter &param) throws.
   template<class VectorParameter>
   explicit basic_vectorbuf(const VectorParameter &param,
                            std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
      :  base_t(), m_mode(mode), m_vect(param)
   {  this->initialize_pointers();   }

   public:

   //!Swaps the underlying vector with the passed vector.
   //!This function resets the read/write position in the stream.
   //!Does not throw.
   void swap_vector(vector_type &vect)
   {
      if (this->m_mode & std::ios_base::out){
         //Update high water if necessary
         //And resize vector to remove extra size
         if (mp_high_water < base_t::pptr()){
            //Restore the vector's size if necessary
            mp_high_water = base_t::pptr();
         }
         //This does not reallocate
         m_vect.resize(std::size_t(mp_high_water - (m_vect.size() ? &m_vect[0] : 0)));
      }
      //Now swap vector
      m_vect.swap(vect);
      this->initialize_pointers();
   }

   //!Returns a const reference to the internal vector.
   //!Does not throw.
   const vector_type &vector() const
   {
      if (this->m_mode & std::ios_base::out){
         if (mp_high_water < base_t::pptr()){
            //Restore the vector's size if necessary
            mp_high_water = base_t::pptr();
         }
         //This shouldn't reallocate
         typedef typename vector_type::size_type size_type;
         char_type *old_ptr = base_t::pbase();
         size_type high_pos = size_type(mp_high_water-old_ptr);
         if(m_vect.size() > high_pos){
            m_vect.resize(high_pos);
            //But we must update end write pointer because vector size is now shorter
            int old_pos = (int)(base_t::pptr() - base_t::pbase());
            const_cast<basic_vectorbuf*>(this)->base_t::setp(old_ptr, old_ptr + high_pos);
            const_cast<basic_vectorbuf*>(this)->base_t::pbump(old_pos);
         }
      }
      return m_vect;
   }

   //!Preallocates memory from the internal vector.
   //!Resets the stream to the first position.
   //!Throws if the internals vector's memory allocation throws.
   void reserve(typename vector_type::size_type size)
   {
      if (this->m_mode & std::ios_base::out && size > m_vect.size()){
         typename vector_type::difference_type write_pos = base_t::pptr() - base_t::pbase();
         typename vector_type::difference_type read_pos  = base_t::gptr() - base_t::eback();
         //Now update pointer data
         m_vect.reserve(size);
         this->initialize_pointers();
         base_t::pbump((int)write_pos);
         if(this->m_mode & std::ios_base::in){
            base_t::gbump((int)read_pos);
         }
      }
   }

   //!Calls clear() method of the internal vector.
   //!Resets the stream to the first position.
   void clear()
   {  m_vect.clear();   this->initialize_pointers();   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   //Maximizes high watermark to the initial vector size,
   //initializes read and write iostream buffers to the capacity
   //and resets stream positions
   void initialize_pointers()
   {
      // The initial read position is the beginning of the vector.
      if(!(m_mode & std::ios_base::out)){
         if(m_vect.empty()){
            this->setg(0, 0, 0);
         }
         else{
            this->setg(&m_vect[0], &m_vect[0], &m_vect[0] + m_vect.size());
         }
      }

      // The initial write position is the beginning of the vector.
      if(m_mode & std::ios_base::out){
         //First get real size
         int real_size = (int)m_vect.size();
         //Then maximize size for high watermarking
         m_vect.resize(m_vect.capacity());
         BOOST_ASSERT(m_vect.size() == m_vect.capacity());
         //Set high watermarking with the expanded size
         mp_high_water = m_vect.size() ? (&m_vect[0] + real_size) : 0;
         //Now set formatting pointers
         if(m_vect.empty()){
            this->setp(0, 0);
            if(m_mode & std::ios_base::in)
               this->setg(0, 0, 0);
         }
         else{
            char_type *p = &m_vect[0];
            this->setp(p, p + m_vect.size());
            if(m_mode & std::ios_base::in)
               this->setg(p, p, p + real_size);
         }
         if (m_mode & (std::ios_base::app | std::ios_base::ate)){
            base_t::pbump((int)real_size);
         }
      }
   }

   protected:
   virtual int_type underflow() BOOST_OVERRIDE
   {
      if (base_t::gptr() == 0)
         return CharTraits::eof();
      if(m_mode & std::ios_base::out){
         if (mp_high_water < base_t::pptr())
            mp_high_water = base_t::pptr();
         if (base_t::egptr() < mp_high_water)
            base_t::setg(base_t::eback(), base_t::gptr(), mp_high_water);
      }
      if (base_t::gptr() < base_t::egptr())
         return CharTraits::to_int_type(*base_t::gptr());
      return CharTraits::eof();
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
               typedef typename vector_type::difference_type dif_t;
               //The new output position is the previous one plus one
               //because 'overflow' requires putting 'c' on the buffer
               dif_t new_outpos = base_t::pptr() - base_t::pbase() + 1;
               //Adjust high water if necessary
               dif_t hipos = mp_high_water - base_t::pbase();
               if (hipos < new_outpos)
                  hipos = new_outpos;
               //Insert the new data
               m_vect.push_back(CharTraits::to_char_type(c));
               m_vect.resize(m_vect.capacity());
               BOOST_ASSERT(m_vect.size() == m_vect.capacity());
               char_type* p = const_cast<char_type*>(&m_vect[0]);
               //A reallocation might have happened, update pointers
               base_t::setp(p, p + (dif_t)m_vect.size());
               mp_high_water = p + hipos;
               if (m_mode & std::ios_base::in)
                  base_t::setg(p, p + (base_t::gptr() - base_t::eback()), mp_high_water);
               //Update write position to the old position + 1
               base_t::pbump((int)new_outpos);
               return c;
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
      //Get seek mode
      bool in(0 != (mode & std::ios_base::in)), out(0 != (mode & std::ios_base::out));
      //Test for logic errors
      if(!in & !out)
         return pos_type(off_type(-1));
      else if((in && out) && (dir == std::ios_base::cur))
         return pos_type(off_type(-1));
      else if((in  && (!(m_mode & std::ios_base::in) || (off != 0 && this->gptr() == 0) )) ||
               (out && (!(m_mode & std::ios_base::out) || (off != 0 && this->pptr() == 0))))
         return pos_type(off_type(-1));

      off_type newoff;
      //Just calculate the end of the stream. If the stream is read-only
      //the limit is the size of the vector. Otherwise, the high water mark
      //will mark the real size.
      off_type limit;
      if(m_mode & std::ios_base::out){
         //Update high water marking because pptr() is going to change and it might
         //have been updated since last overflow()
         if(mp_high_water < base_t::pptr())
            mp_high_water = base_t::pptr();
         //Update read limits in case high water mark was changed
         if(m_mode & std::ios_base::in){
            if (base_t::egptr() < mp_high_water)
               base_t::setg(base_t::eback(), base_t::gptr(), mp_high_water);
         }
         limit = static_cast<off_type>(mp_high_water - base_t::pbase());
      }
      else{
         limit = static_cast<off_type>(m_vect.size());
      }

      switch(dir) {
         case std::ios_base::beg:
            newoff = 0;
         break;
         case std::ios_base::end:
            newoff = limit;
         break;
         case std::ios_base::cur:
            newoff = in ? static_cast<std::streamoff>(this->gptr() - this->eback())
                        : static_cast<std::streamoff>(this->pptr() - this->pbase());
         break;
         default:
            return pos_type(off_type(-1));
      }

      newoff += off;

      if (newoff < 0 || newoff > limit)
         return pos_type(-1);
      if (m_mode & std::ios_base::app && mode & std::ios_base::out && newoff != limit)
         return pos_type(-1);
      //This can reassign pointers
      //if(m_vect.size() != m_vect.capacity())
         //this->initialize_pointers();
      if (in)
         base_t::setg(base_t::eback(), base_t::eback() + newoff, base_t::egptr());
      if (out){
         base_t::setp(base_t::pbase(), base_t::epptr());
         base_t::pbump(static_cast<int>(newoff));
      }
      return pos_type(newoff);
   }

   virtual pos_type seekpos(pos_type pos, std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out) BOOST_OVERRIDE
   {  return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);  }

   private:
   std::ios_base::openmode m_mode;
   mutable vector_type     m_vect;
   mutable char_type*      mp_high_water;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!A basic_istream class that holds a character vector specified by CharVector
//!template parameter as its formatting buffer. The vector must have
//!contiguous storage, like std::vector, boost::interprocess::vector or
//!boost::interprocess::basic_string
template <class CharVector, class CharTraits>
class basic_ivectorstream
   : public std::basic_istream<typename CharVector::value_type, CharTraits>
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   , private basic_vectorbuf<CharVector, CharTraits>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   public:
   typedef CharVector                                                   vector_type;
   typedef typename std::basic_ios
      <typename CharVector::value_type, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_vectorbuf<CharVector, CharTraits>    vectorbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_istream<char_type, CharTraits>  base_t;

   vectorbuf_t &       get_buf()      {  return *this;  }
   const vectorbuf_t & get_buf() const{  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   //!Constructor. Throws if vector_type default
   //!constructor throws.
   basic_ivectorstream(std::ios_base::openmode mode = std::ios_base::in)
      : base_t(0) //Initializes first the base class to safely init the virtual basic_ios base
                  //(via basic_ios::init() call in base_t's constructor) without the risk of a
                  //previous throwing vectorbuf constructor. Set the streambuf after risk has gone.
      , vectorbuf_t(mode | std::ios_base::in)
   {  this->base_t::rdbuf(&get_buf()); }

   //!Constructor. Throws if vector_type(const VectorParameter &param)
   //!throws.
   template<class VectorParameter>
   basic_ivectorstream(const VectorParameter &param,
                       std::ios_base::openmode mode = std::ios_base::in)
      : vectorbuf_t(param, mode | std::ios_base::in)
         //basic_ios_t() is constructed uninitialized as virtual base
         //and initialized inside base_t calling basic_ios::init()
      , base_t(&get_buf())
   {}

   public:
   //!Returns the address of the stored
   //!stream buffer.
   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&get_buf()); }

   //!Swaps the underlying vector with the passed vector.
   //!This function resets the read position in the stream.
   //!Does not throw.
   void swap_vector(vector_type &vect)
   {  get_buf().swap_vector(vect);   }

   //!Returns a const reference to the internal vector.
   //!Does not throw.
   const vector_type &vector() const
   {  return get_buf().vector();   }

   //!Calls reserve() method of the internal vector.
   //!Resets the stream to the first position.
   //!Throws if the internals vector's reserve throws.
   void reserve(typename vector_type::size_type size)
   {  get_buf().reserve(size);   }

   //!Calls clear() method of the internal vector.
   //!Resets the stream to the first position.
   void clear()
   {  get_buf().clear();   }
};

//!A basic_ostream class that holds a character vector specified by CharVector
//!template parameter as its formatting buffer. The vector must have
//!contiguous storage, like std::vector, boost::interprocess::vector or
//!boost::interprocess::basic_string
template <class CharVector, class CharTraits>
class basic_ovectorstream
   : public std::basic_ostream<typename CharVector::value_type, CharTraits>
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   , private basic_vectorbuf<CharVector, CharTraits>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   public:
   typedef CharVector                                                   vector_type;
   typedef typename std::basic_ios
      <typename CharVector::value_type, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_vectorbuf<CharVector, CharTraits>    vectorbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_ostream<char_type, CharTraits>  base_t;

   vectorbuf_t &       get_buf()      {  return *this;  }
   const vectorbuf_t & get_buf()const {  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Throws if vector_type default
   //!constructor throws.
   basic_ovectorstream(std::ios_base::openmode mode = std::ios_base::out)
      : base_t(0) //Initializes first the base class to safely init the virtual basic_ios base
                  //(via basic_ios::init() call in base_t's constructor) without the risk of a
                  //previous throwing vectorbuf constructor. Set the streambuf after risk has gone.
      , vectorbuf_t(mode | std::ios_base::out)
   {  this->base_t::rdbuf(&get_buf()); }

   //!Constructor. Throws if vector_type(const VectorParameter &param)
   //!throws.
   template<class VectorParameter>
   basic_ovectorstream(const VectorParameter &param,
                        std::ios_base::openmode mode = std::ios_base::out)
      : base_t(0) //Initializes first the base class to safely init the virtual basic_ios base
                  //(via basic_ios::init() call in base_t's constructor) without the risk of a
                  //previous throwing vectorbuf constructor. Set the streambuf after risk has gone.
      , vectorbuf_t(param, mode | std::ios_base::out)
   {  this->base_t::rdbuf(&get_buf()); }

   public:
   //!Returns the address of the stored
   //!stream buffer.
   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&get_buf()); }

   //!Swaps the underlying vector with the passed vector.
   //!This function resets the write position in the stream.
   //!Does not throw.
   void swap_vector(vector_type &vect)
   {  get_buf().swap_vector(vect);   }

   //!Returns a const reference to the internal vector.
   //!Does not throw.
   const vector_type &vector() const
   {  return get_buf().vector();   }

   //!Calls reserve() method of the internal vector.
   //!Resets the stream to the first position.
   //!Throws if the internals vector's reserve throws.
   void reserve(typename vector_type::size_type size)
   {  get_buf().reserve(size);   }
};

//!A basic_iostream class that holds a character vector specified by CharVector
//!template parameter as its formatting buffer. The vector must have
//!contiguous storage, like std::vector, boost::interprocess::vector or
//!boost::interprocess::basic_string
template <class CharVector, class CharTraits>
class basic_vectorstream
   : public std::basic_iostream<typename CharVector::value_type, CharTraits>
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   , private basic_vectorbuf<CharVector, CharTraits>
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
{
   public:
   typedef CharVector                                                   vector_type;
   typedef typename std::basic_ios
      <typename CharVector::value_type, CharTraits>::char_type          char_type;
   typedef typename std::basic_ios<char_type, CharTraits>::int_type     int_type;
   typedef typename std::basic_ios<char_type, CharTraits>::pos_type     pos_type;
   typedef typename std::basic_ios<char_type, CharTraits>::off_type     off_type;
   typedef typename std::basic_ios<char_type, CharTraits>::traits_type  traits_type;

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   typedef basic_vectorbuf<CharVector, CharTraits>    vectorbuf_t;
   typedef std::basic_ios<char_type, CharTraits>      basic_ios_t;
   typedef std::basic_iostream<char_type, CharTraits> base_t;

   vectorbuf_t &       get_buf()      {  return *this;  }
   const vectorbuf_t & get_buf() const{  return *this;  }
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Throws if vector_type default
   //!constructor throws.
   basic_vectorstream(std::ios_base::openmode mode
                      = std::ios_base::in | std::ios_base::out)
      : base_t(0) //Initializes first the base class to safely init the virtual basic_ios base
                  //(via basic_ios::init() call in base_t's constructor) without the risk of a
                  //previous throwing vectorbuf constructor. Set the streambuf after risk has gone.
      , vectorbuf_t(mode)
   {  this->base_t::rdbuf(&get_buf()); }

   //!Constructor. Throws if vector_type(const VectorParameter &param)
   //!throws.
   template<class VectorParameter>
   basic_vectorstream(const VectorParameter &param, std::ios_base::openmode mode
                      = std::ios_base::in | std::ios_base::out)
      : base_t(0) //Initializes first the base class to safely init the virtual basic_ios base
                  //(via basic_ios::init() call in base_t's constructor) without the risk of a
                  //previous throwing vectorbuf constructor. Set the streambuf after risk has gone.
      , vectorbuf_t(param, mode)
   {  this->base_t::rdbuf(&get_buf()); }

   public:
   //Returns the address of the stored stream buffer.
   basic_vectorbuf<CharVector, CharTraits>* rdbuf() const
   { return const_cast<basic_vectorbuf<CharVector, CharTraits>*>(&get_buf()); }

   //!Swaps the underlying vector with the passed vector.
   //!This function resets the read/write position in the stream.
   //!Does not throw.
   void swap_vector(vector_type &vect)
   {  get_buf().swap_vector(vect);   }

   //!Returns a const reference to the internal vector.
   //!Does not throw.
   const vector_type &vector() const
   {  return get_buf().vector();   }

   //!Calls reserve() method of the internal vector.
   //!Resets the stream to the first position.
   //!Throws if the internals vector's reserve throws.
   void reserve(typename vector_type::size_type size)
   {  get_buf().reserve(size);   }

   //!Calls clear() method of the internal vector.
   //!Resets the stream to the first position.
   void clear()
   {  get_buf().clear();   }
};

//Some typedefs to simplify usage
//!
//!typedef basic_vectorbuf<std::vector<char> >        vectorbuf;
//!typedef basic_vectorstream<std::vector<char> >     vectorstream;
//!typedef basic_ivectorstream<std::vector<char> >    ivectorstream;
//!typedef basic_ovectorstream<std::vector<char> >    ovectorstream;
//!
//!typedef basic_vectorbuf<std::vector<wchar_t> >     wvectorbuf;
//!typedef basic_vectorstream<std::vector<wchar_t> >  wvectorstream;
//!typedef basic_ivectorstream<std::vector<wchar_t> > wivectorstream;
//!typedef basic_ovectorstream<std::vector<wchar_t> > wovectorstream;

}} //namespace boost {  namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif /* BOOST_INTERPROCESS_VECTORSTREAM_HPP */

/* vectorstream.hpp
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
*/