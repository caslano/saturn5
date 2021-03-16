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
qJYdZ3Jh5YTNKJ3pVSqiA9OoqalcjVDUTH0g1otyqKyULIsFmufHRpRbe3LYau+5PngMhh8Ykh2Xge8G2VTZFENlubMsfldQbFIqhyk8LE4uqqaIjT3eBwdQpR3T9tQYlcD+8pZqXB7pqhfkz5EP4M3m4flj1BYTYHzSQs8LPA3VZG/W7ekukDMOm4hl2RpqgOWQSg1ZaDnwW68ILRaK0YfnsDGGnqvKZ+8m26oPqBma6voqr4jei1GgPjtG6Ho=
*/