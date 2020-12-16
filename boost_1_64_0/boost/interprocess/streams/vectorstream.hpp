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
5vS2Kew74p7XwfLAySwPPJzlgS8CPsL6SbtYP2k3sJTlgMv4eTnLAVcA9wBXAB8G3ieecz5K/HvEwGWcjzjgAs7HtzkfdwPdLO/8BfbnsdzzpcDvcDm3cLr3cLrf4XQmaLyXCszkdCKBIzidx5i/j3N597HeSqNBTyWHw99B4c16Ii+x/tYrwNGsZzUJ+Bowh/W0CoEtwMuAP2G5258CV7Je1S3svxV4FHg7+WX+Wzn9LEX+v8753wxMA94F7KlJfZ2t/v0q4A0c3k30+n6Ztxvr5yQCbwT2At7E7fQObndfBQ4B3gwcwf7JrHc0DejF/1ymzweu53Z3G8ufb+D2sRFYJeg4f0McvE/BezmxDqBo70CN9SMixDNgd6L3lXMocDDrUQwHXgTMBo5k+f4K4HjWp/g8cDTL+48B5rG+xGzWlyhh+lLWj6gCXgr8GvCLrHdRAKwFFrE8/wKW518IfAR4GbAReDnwZY7vCPAq4HHg1cA3+f5vgMXAf7D/feBU4IfAcmCEkJMGZgCvBfYDCjrfOMNr6MBoxTjzHLeHQ8AoYLPG4UCXw+H+zOEGiHDM5z9yf3sH6BI0wBTgadZL/AuwP/Bdtvf6V+AItg95EfA9Ho+QFvH7DLeLfwLnAc8Cr2Q7lR7WB6xm/b+1wEihl8P0d7I+4L0CWN8vGbiL09vNeoQPsn3LPcAY1qeIA34X2A34HDAe+AqHO8ry9S1AN/DnwESulyTgHzmdd5ie+c3roaBV8Hso83sYj1PDNRmuRoYL+j5ws5/7O6/lqcer73K4A9xvv8fj1feBur4Chye9sTb6FFcZ9Q5t0mmN9ujcNumybNJlSzqLXuR8A12OTboim3QlNuk8Num8IehERz34T8gUw52Giz0LOeGTkBN+GfK/uJ4AVwTngUt/BfK4wHq4ZrgTcOfE/X9B5hguH64CbgNcPdxhuJNw2geQVYYTdkUz3kAcv48gXYoc3CuBWwtXA9cAt/UFhAOe+MCejsUBb2gdi7Ad0s7rUZwPG6Rh+6Nt7Y923vZo2O5o5+yOnv0AaX6I9gS3GM4LVw93GO4tuNhziAtuEdxauBq4JrhjcOfgBn6EssKthauHOwp3Fi7jY6QPV/FxaH2G8yb/jzMdu0L+X8jyZyZh3utfT3ZY919fSBcfZr61MJxFVVq1apRIXu5xkHymcv0L4eyfP2WkTXQHl4XS2sjxD0ts7z4m5TnouT8iDyzb8omsn6nXyQKtq3361s96XCLu7xtx09Xv1bsdKz68tDA/7tXru279TL1O9tk/2+e/tX5G3xvcd5TfG7wuJLA/f28MAG5Ffut5/phjc64Xnud98vO882VvPjzX6/q5XtjOfOfnezU25mPhX/gX/oV/4V/4dz5+5/H7/5pKsQDQye9/v11/bYawuzp1+vS8+fOLc/PmT583q2iBkHVhy/7DQHc6DWXy0S2EkOC8WQuuKJ5VMKOwmIMtqy5fCVpaU8hK0nS7to0Oq13b9VjYLtpDawqKREnalOTrbgwsp47w7bJra5K9F/GyXVs9nyMi1HZtcwLlkyzUhtZJ9Nu2HTLDYttWT7s2wmrb9kUhsxUobZIm1tpt33Yap5fvtNbJ48JWBaenqmCuFqqXXUHsDdd0ol4Qr6VeDjvV9aLt5ryqG2NIfvjrZZGlXiSfJkRa6+WwsK0ThE9UNfbrBuU3t4WSKJbpYIJecC8jzRZfmmVYg7O2B66Xl9ID1wvCy7P+k302Q9X6D2Za0UYcZGtFLbvX0qa+b7FRXn99I7+ivqVNANEvOV+4x2nhHqVvrpvN0VY+/UjI4Es+KetHY14dCcKr1nbwqrUdvGrtBK+OdIBX/jZVHeOLMN0=
*/