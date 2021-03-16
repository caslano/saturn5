#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EMPTY_STRING_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Ignore = int>
        struct empty_string
        {
          typedef empty_string type;

          static constexpr char value[1] = {0};
        };

        template <class Ignore>
        constexpr char empty_string<Ignore>::value[1];
      }
    }
  }
}

#endif


/* empty_string.hpp
6k0eSbVHyh/bxBY2YCPYpD7kkVQHpPx+efjmpQ8Tld6HPJI6R5TGZ6+1eJuosj7kkVRHQTV9LuMToh7pQx5JdRL31fLzzZ8SdaQPeSTVOcDbjftW9mDtRlxf8kiqC1L+POWlmzeyeji8L3kk1TXA6+Ggexeyme/svuSRVDdxX0sOv7mCqH/1JY+kUsW1Hplc4zhRb/Qlj6S6I+XPYSdlvnKCqNg08kiqh7jW5f1fjmd1I408kuqJVG3Pt/TqWzI=
*/