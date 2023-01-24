#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_EMPTY_STRING_HPP

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

          static const char value[1];
        };

        template <class Ignore>
        const char empty_string<Ignore>::value[1] = {0};
      }
    }
  }
}

#endif


/* empty_string.hpp
nQheG04WwDnD9E4ekI91dn6hhQvPUDumyrAidz+8kw1VS0h4JQBRSEDchhx7ryEYMxjsQ4ojhu/eUcamuVTFfOlOJIX23dwlOAKXZNK6mXw10gQT4sEIbATNaABYcSZ0YXTs0ADQioDIJ4HEK7uPsy7buS6VBNgxwX7IcHdm7t2Zc7lsHgcYrrsesR+fKTJOBk6XC3DzvXR9kmx2kW4g+m5LEjOuBxkXnSHqrwdV8DYY8uNTfA9kdk1p201ueNyWIkqnFPNIBJ1cuTgZY9lFDAolB0DWTjRlpDYU4rcicXw7KIKCyxTDDsazWufTMDrr3IR7gq24NnXIhgb0uiZsy7rsTOufOp0n2YbrGFoXO9GVdRFWuLRJ2yjaTtqYtZOV5MBPp+yg8gCc+o80ceqjpriIjexgkO1Z50vrVHuW8hXWQALF3intsUu7rYK9k1btcSnIOf0kmH1P/EROlZPeUzAWynYKT3yD58IX/R1KbelelpAH7vnHKoJtvdRUcrpkbh9acn9VR4vaA2a3PqtjFogJLj+xC19/PMMGWg60AJdtYDI8XpvWMqrF47R6OxV3DztA8MS/6Lk+8AyaHWmWkp/GCBW1xTUtMSUHxliEL7YWxzcIX6wvrtkfA0fwoYTZ+DbM7IpVsO0IXIKvXVhy8GJ684vN+CC8tlF7GAwdpQ7TteW2CysuwlxtubsXG+1lO5caMWrJjO8n4jWT
*/