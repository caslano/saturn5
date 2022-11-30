/*
 *
 * Copyright (c) 1998-2002
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_raw_buffer.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Raw character buffer for regex code.
  *                Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_RAW_BUFFER_HPP
#define BOOST_REGEX_RAW_BUFFER_HPP

#ifndef BOOST_REGEX_CONFIG_HPP
#include <boost/regex/config.hpp>
#endif

#include <algorithm>
#include <cstddef>

namespace boost{
   namespace BOOST_REGEX_DETAIL_NS{

struct empty_padding{};

union padding
{
   void* p;
   unsigned int i;
};

template <int N>
struct padding3
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<2>
{
   enum{
      padding_size = 2,
      padding_mask = 1
   };
};

template<>
struct padding3<4>
{
   enum{
      padding_size = 4,
      padding_mask = 3
   };
};

template<>
struct padding3<8>
{
   enum{
      padding_size = 8,
      padding_mask = 7
   };
};

template<>
struct padding3<16>
{
   enum{
      padding_size = 16,
      padding_mask = 15
   };
};

enum{
   padding_size = padding3<sizeof(padding)>::padding_size,
   padding_mask = padding3<sizeof(padding)>::padding_mask
};

//
// class raw_storage
// basically this is a simplified vector<unsigned char>
// this is used by basic_regex for expression storage
//

class raw_storage
{
public:
   typedef std::size_t           size_type;
   typedef unsigned char*        pointer;
private:
   pointer last, start, end;
public:

   raw_storage();
   raw_storage(size_type n);

   ~raw_storage()
   {
      ::operator delete(start);
   }

   void  resize(size_type n)
   {
      size_type newsize = start ? last - start : 1024;
      while (newsize < n)
         newsize *= 2;
      size_type datasize = end - start;
      // extend newsize to WORD/DWORD boundary:
      newsize = (newsize + padding_mask) & ~(padding_mask);

      // allocate and copy data:
      pointer ptr = static_cast<pointer>(::operator new(newsize));
      BOOST_REGEX_NOEH_ASSERT(ptr)
         if (start)
            std::memcpy(ptr, start, datasize);

      // get rid of old buffer:
      ::operator delete(start);

      // and set up pointers:
      start = ptr;
      end = ptr + datasize;
      last = ptr + newsize;
   }

   void*  extend(size_type n)
   {
      if(size_type(last - end) < n)
         resize(n + (end - start));
      pointer result = end;
      end += n;
      return result;
   }

   void*  insert(size_type pos, size_type n)
   {
      BOOST_REGEX_ASSERT(pos <= size_type(end - start));
      if (size_type(last - end) < n)
         resize(n + (end - start));
      void* result = start + pos;
      std::memmove(start + pos + n, start + pos, (end - start) - pos);
      end += n;
      return result;
   }

   size_type  size()
   {
      return size_type(end - start);
   }

   size_type  capacity()
   {
      return size_type(last - start);
   }

   void*  data()const
   {
      return start;
   }

   size_type  index(void* ptr)
   {
      return size_type(static_cast<pointer>(ptr) - static_cast<pointer>(data()));
   }

   void  clear()
   {
      end = start;
   }

   void  align()
   {
      // move end up to a boundary:
      end = start + (((end - start) + padding_mask) & ~padding_mask);
   }
   void swap(raw_storage& that)
   {
      std::swap(start, that.start);
      std::swap(end, that.end);
      std::swap(last, that.last);
  }
};

inline raw_storage::raw_storage()
{
   last = start = end = 0;
}

inline raw_storage::raw_storage(size_type n)
{
   start = end = static_cast<pointer>(::operator new(n));
   BOOST_REGEX_NOEH_ASSERT(start)
   last = start + n;
}

} // namespace BOOST_REGEX_DETAIL_NS
} // namespace boost

#endif


/* regex_raw_buffer.hpp
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
*/