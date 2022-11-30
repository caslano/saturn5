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
   inline base_type* setbuf(char_type* s, streamsize n) BOOST_OVERRIDE;
   inline typename this_type::pos_type seekpos(pos_type sp, ::std::ios_base::openmode which) BOOST_OVERRIDE;
   inline typename this_type::pos_type seekoff(off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which) BOOST_OVERRIDE;

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