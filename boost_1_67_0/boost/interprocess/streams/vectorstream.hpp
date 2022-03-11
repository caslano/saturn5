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
         m_vect.resize(mp_high_water - (m_vect.size() ? &m_vect[0] : 0));
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
            int old_pos = base_t::pptr() - base_t::pbase();
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
   virtual int_type underflow()
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
                                 = std::ios_base::in | std::ios_base::out)
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
         base_t::pbump(newoff);
      }
      return pos_type(newoff);
   }

   virtual pos_type seekpos(pos_type pos, std::ios_base::openmode mode
                                 = std::ios_base::in | std::ios_base::out)
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