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
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
*/