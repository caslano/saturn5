#ifndef BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP
#define BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int Len, class S>
        struct assert_string_length : S
        {
          BOOST_STATIC_ASSERT((Len <= BOOST_METAPARSE_LIMIT_STRING_SIZE));
        };
      }
    }
  }
}

#endif



/* assert_string_length.hpp
7/W6bdg/G/fd4FOvAbyjHoVvUH9Qt3a/Z3ofTvq3TQv+pX+DptNv9udfaY1hnJ4M1+SfXj7ZrDe0RInH+v0AHgRwvBJSnucVVLqEXOe5iHEwv0MH/S4aZMgZ4XRGZlkFyHWjFWp//AkafgPwTorKosDqni4b0naBKHaYSVNGkTAmKbMOIbuBKTakoKlfcGPkTsCdjgU0sdSSELQYUWYGWx3TQDh24gAQjBeOR2P0EvShF1x5LMBYH6TixX5woiMtINEFuHlutqCJxvBYIa9aDsM1fKTLiHprEpw0hIojYoW3b3CP7h6Cs98Y/+/mfyNfN1udH5prfLX8d6/Bt0Mi715733y6pc481bzpn/HG2Bivqj1x6vB9svOPQ+6f/nr/AVBLAwQKAAAACAAtZ0pS8M+Wc7MDAABVBwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNjJVVAUAAbZIJGDdVW2P4jYQ/m4p/2FKbyWoFsLLdqvlALUHXA/1tlDI3qoVKjLJBKwNdhQ7cNHu/feOHd5UqX+gQQR7ZjzzzMwzpmdQm5BrHLCekLGinxcsDiqL9IB9DGZsPg7mrOdfhD2/tGPfwwKzPWZ1LSJkvQzTpBiQNBYJtjr3bQiVNCiNbjQarBdx
*/