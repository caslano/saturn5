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
35bs586YhheoSFWDjh7GeG4tJ596H2Jx8KUz7LbULU1vWNoFBOlbnbHC+4oSjmFs1BZ7J+Fd+wJO4wFlMiis8y2iP/tnYH1qnNrtlrAzmqyu9pNPDPihtlWJI0KM5GVbY7lYJbRarJOHJbRSpBD/R4lwHEVU5MROy0MvXZcvWOu8gdYAULnHGnyB3VShUA5eEQ0MXWH9kMX7DksUVW29TW05Y3QToSsBx0s0YPfUrPws+qxmwP6QY/xmQwJoXru6FJcv89X6YfE8OExcwpW4GrABCT2XicWptjj/In8BUEsDBAoAAAAIAC1nSlImgbeHqwAAADABAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMyM1VUBQABtkgkYF2QwQ7CIAyG730Ksp0NL9Ds4iOYeDU4SkaczJRuurcX2BaMp7Z/v/78AYWi9CZSB+iDm1J50Pqe2MYO5uAl76GfefzcZLHeOUBdCdTbEbTQqgvxQnyK3hIg02tcM7A3hTiPnoLsRF+GhMRy10GYQpL1MaIjIzPTbxDUVcRgnin2X7ZNRH24l3evxN6tyhoxyjghVjKQyo5qMFHdiYJq4jBJA7gUNlvUrn7SF1BLAwQKAAAACAAtZ0pS9LVEld4BAAAUAwAAHwAJ
*/