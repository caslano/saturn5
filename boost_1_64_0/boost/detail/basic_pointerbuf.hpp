//-----------------------------------------------------------------------------
// boost detail/templated_streams.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2013 John Maddock, Antony Polukhin
// 
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_BASIC_POINTERBUF_HPP
#define BOOST_DETAIL_BASIC_POINTERBUF_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

#include "boost/config.hpp"
#include <streambuf>

namespace boost { namespace detail {

//
// class basic_pointerbuf:
// acts as a stream buffer which wraps around a pair of pointers:
//
template <class charT, class BufferT >
class basic_pointerbuf : public BufferT {
protected:
   typedef BufferT base_type;
   typedef basic_pointerbuf<charT, BufferT> this_type;
   typedef typename base_type::int_type int_type;
   typedef typename base_type::char_type char_type;
   typedef typename base_type::pos_type pos_type;
   typedef ::std::streamsize streamsize;
   typedef typename base_type::off_type off_type;

public:
   basic_pointerbuf() : base_type() { this_type::setbuf(0, 0); }
   const charT* getnext() { return this->gptr(); }

#ifndef BOOST_NO_USING_TEMPLATE
    using base_type::pptr;
    using base_type::pbase;
#else
    charT* pptr() const { return base_type::pptr(); }
    charT* pbase() const { return base_type::pbase(); }
#endif

protected:
   // VC mistakenly assumes that `setbuf` and other functions are not referenced.
   // Marking those functions with `inline` suppresses the warnings.
   // There must be no harm from marking virtual functions as inline: inline virtual
   // call can be inlined ONLY when the compiler knows the "exact class".
   inline base_type* setbuf(char_type* s, streamsize n);
   inline typename this_type::pos_type seekpos(pos_type sp, ::std::ios_base::openmode which);
   inline typename this_type::pos_type seekoff(off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which);

private:
   basic_pointerbuf& operator=(const basic_pointerbuf&);
   basic_pointerbuf(const basic_pointerbuf&);
};

template<class charT, class BufferT>
BufferT*
basic_pointerbuf<charT, BufferT>::setbuf(char_type* s, streamsize n)
{
   this->setg(s, s, s + n);
   return this;
}

template<class charT, class BufferT>
typename basic_pointerbuf<charT, BufferT>::pos_type
basic_pointerbuf<charT, BufferT>::seekoff(off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which)
{
   typedef typename boost::int_t<sizeof(way) * CHAR_BIT>::least cast_type;

   if(which & ::std::ios_base::out)
      return pos_type(off_type(-1));
   std::ptrdiff_t size = this->egptr() - this->eback();
   std::ptrdiff_t pos = this->gptr() - this->eback();
   charT* g = this->eback();
   switch(static_cast<cast_type>(way))
   {
   case ::std::ios_base::beg:
      if((off < 0) || (off > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + off, g + size);
      break;
   case ::std::ios_base::end:
      if((off < 0) || (off > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + size - off, g + size);
      break;
   case ::std::ios_base::cur:
   {
      std::ptrdiff_t newpos = static_cast<std::ptrdiff_t>(pos + off);
      if((newpos < 0) || (newpos > size))
         return pos_type(off_type(-1));
      else
         this->setg(g, g + newpos, g + size);
      break;
   }
   default: ;
   }
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4244)
#endif
   return static_cast<pos_type>(this->gptr() - this->eback());
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template<class charT, class BufferT>
typename basic_pointerbuf<charT, BufferT>::pos_type
basic_pointerbuf<charT, BufferT>::seekpos(pos_type sp, ::std::ios_base::openmode which)
{
   if(which & ::std::ios_base::out)
      return pos_type(off_type(-1));
   off_type size = static_cast<off_type>(this->egptr() - this->eback());
   charT* g = this->eback();
   if(off_type(sp) <= size)
   {
      this->setg(g, g + off_type(sp), g + size);
   }
   return pos_type(off_type(-1));
}

}} // namespace boost::detail

#endif // BOOST_DETAIL_BASIC_POINTERBUF_HPP


/* basic_pointerbuf.hpp
YG20Dk5VD7YICHRXyA64yQKmxzBUUZ0qOQyLZZ0rrKgjsmeqbMCDLsBluw7vkcB7EBShOhFJUAfVYTxlPTBASIisDe+aL6qYL6pkt3zERoWk3A7HWVRMsUEoc6obsYmKSBaiwu8VlZpk1+3eLVA2WcdlimAJgmIERVy2PG4B0qP/p1CdKbL/I7JO3Iq4VnbKcBvwoBtwKf/aJfAeBNVSnVpJ0IPtVjxlPTC0wj9RG941Q0xhhpgiu+V9Niok5XY4boJihA1GmVPtWpugqO0pKFKKKfCeD3BGBNXG0/OetHUStFgnPsEzReMVFKt91VpU0LpEZagbrDqTY9v8NRKZE8cUqjzJs1wmR+DxQyHZCkcGlsR4BDEBQYyZDMnml6DJsoW9zYqAA+kMyrFnmFLH5nB/gFeoM2FsTj5EB1cx66ygMEdtWQHO8oksNmtzeKOueJdq/+ZSb6u/0hFRbYEfsgQiW5ZEJLMcMJVWbl7ihTYVuaAKQJ7EZc9zQRZwbFaRwga1/C7YiiBPYrPnuWArcsTmV9iK1DGBzaeOCZz6nfqd+r3xP5vrOYHBU389jLv90r15zMWdfMzVnXzM1Z3MOdNpcRNoICoclv4tpV4behev8jEXr7LMcqKAvcp2lcKQ4HcjIeBGQsCdhIA7CSpdqgY+QULAjYQiNxKK3EkociehaLrUQHIMBaWVioANeytfhNvGoOymX/s8HkeKgm4UBd0pCrpTFLSyRiAb1ih1I6HUnYRSdxJKrayRb2MN6pYO2AqaD2rH0QNyGAtswwiqgiqR7uVCay/Dfrdzz5a5NavMvVll7s0qs7JbQTbsNsqNhFHuJIxyJ2GUIsG1I3pIAxdV2CvynawDn8h3tAxkvtTCjbHm+9ZIG/KIxf67X1hNEWF2sRXABffsGWkjslZacHda4PSwI4NUJyjtyBWyTq3NySJNuzk24EF34IbeAgvw7FwvP7vPiqesBwYwkmRteNeGbZAN26Dslk0SYq2NchscZ0/HXBsEV++L9HRU2T0dL4BR25Z7RNnIxixsrQ0ERL2oxf91r8Bq21UrVYAeEIC8AIgQ2rfVNgk4DttqpVSnVI5CTNapszlaZNecYQMedAEuG/bPeyTw7Bww35F1zLaaxNAK/0RteNdsUcpsUSq75cM2KiTldjhu/o6JNhjOXhgpdOjd5u/4o2KNN1ZcKX5ausvKmEHGbt/am/5l9629MgVoiADkJUB+p929F+6WgLLb8N0l6yzpZcO3zQI8uw3fiy3As9vwnWDB0x8bvge/JKk4ng3fWy0QjnfDN6EFVu0jVr4o43r2vb3yL7nv7Y1SgP79DStfMPH2zb2DX5Rwstv0/byss7SXTd/VFuDZbfrOtQDPbtN3kAVPf2z67v2CpOL4Nn1bLDCOf9MXBJZU52+ak+/xsITx23RsTs+Viq9IHyA1R5GeZ9XntEeuBPYE8PFQMdDVmSwpZEL9Oi2AaezQhLSiSk4KKB+iSilUQIjPm+9hfEUudA90oXuQC93FbnTH+4PueA+6gy50l7jQPdiF7iFudLf0B90tPeguc6F7hKTbQsia/iBkTQ9CRrkQMtqlA8e4dOBYWweiU3cMHaPUZPo0mWMkmT4kc4wgE0oVYZKiVbfZV6jBQIuR+rsYa5ULlRNdqJzkbCZNlp1gqC9W1G8y1Jdo6osl9SVIfbGgvkRTXyyoLykEME7Uh1yof4sL9Wc5Uz9dUu9i/LlpUW7ak5vWxK1KlNCZqhPnSg2HGfMuN2+FmwvBzQZ3sYw19T5F/VZD/RhNvU9Qj2kBSmPqxyD1PkH9mEKA40B9qQv1Q12oH+ZC/XBHuQTn1fqp77c5UT/ShZpyB2pwmmw=
*/