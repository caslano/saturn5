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
ix7RVR/+pPKU5pXGRdbxkNGMCDYnTy8X6Q+krjQ5rbu5afhB9hx/BRMrEe2PRx41/GXKl32o9xK9No2PUn+Zbo9/aNxDnAQlv6gqJcJ3DcmL0fXI9PSG78eRO9+zC8utdmgBW/fVFxb51erQeI5zRcrVn2yiDbsk36Smg58kmiAp7GUgmT0E3qpoJCTg9KrzRlZOcsJHzawnJs0F3sUMEfX+mrjnDt3cH5MyS0etj37gehL2Tjm81KSsaGp/s1TAvD+UEdPQ17x/QvjNnMWkTtYS3vnWEgH8rOw5BsQqjmEo8p6MHnY/NHJSMEx7nuLpn1pAL3QPalaFeP2+5REfXthgmiViGIWtk2cjkyhM3ZbRcLrPYO9+XTy0ZgDDOv3Pcz9mLU7jVH+bIXzvmic1v8OZOrpJ/KaIjXrvXU/pVUjnh7LKa8lyRCnZlCErFU6vVn9cRTJ+OOZugf3DHbVpzRi6j5sE7eWh2wEKz5KSjLfMesLeAsoqXpDuGvFLKN3laelUDAulbMfrI2ecU2AEEb/ADc8fSmyNCB1xrSjAvNs2AvU60RPDcmH2Yw==
*/