#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_STRING_AT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_string_size.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int MaxLen, int Len, class T>
        constexpr T string_at(const T (&s)[Len], int n)
        {
          // "MaxLen + 1" adds the \0 character of the string literal to the
          // limit
          static_assert(Len <= MaxLen + 1, "String literal is too long.");
          return n >= Len - 1 ? T() : s[n];
        }
      }
    }
  }
}

#ifdef BOOST_METAPARSE_V1_STRING_AT
#  error BOOST_METAPARSE_V1_STRING_AT already defined
#endif
#define BOOST_METAPARSE_V1_STRING_AT \
  ::boost::metaparse::v1::impl::string_at<BOOST_METAPARSE_LIMIT_STRING_SIZE>

#endif


/* string_at.hpp
kLVjA2Io62HyXA881ZB65T0bEENZjyhyjWJ/PS1t2f+9ATGU9eOMVd4EPrHmTukW65CNiKGsRxU5U245ZvcGZH16I2Io67GM9YEC92fNQ6W9cvNGxFDW44rcU/59++kS67KNiKGsJ4g1HnvlOikrn9yIGMp6MmOVHfbk2V3S9LV0E2KAhaTsUzaXKn9zSH76N03x/36Xv1ZtkjDZV5Z4Zf/ylcPSZC5d0emK7zydyYmXFJ8z4f/mofzzN+TP2vg=
*/