#ifndef BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_char_except_size.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp98/impl/is_none.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/mpl/char.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          int C,
          1024
        )
      >
      struct one_char_except_c;

      #ifdef BOOST_METAPARSE_WRAP
      #  error BOOST_METAPARSE_WRAP already defined
      #endif
      #define BOOST_METAPARSE_WRAP(z, n, unused) \
        boost::mpl::char_<BOOST_PP_CAT(C, n)>

      #ifdef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #  error MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE already defined
      #endif
      #define MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, int C)> \
        struct one_char_except_c< \
          BOOST_PP_ENUM_PARAMS(n, C) \
          BOOST_PP_COMMA_IF( \
            BOOST_PP_MUL( \
              n, \
              BOOST_PP_SUB( \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
                n \
              )\
            ) \
          ) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB( \
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
              n \
            ), \
            1024 BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          accept_when< \
            one_char, \
            impl::BOOST_PP_CAT(is_none, n)< \
              BOOST_PP_ENUM(n, BOOST_METAPARSE_WRAP, ~) \
            >, \
            error::unexpected_character \
          > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
        MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE,
        ~
      )

      #undef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #undef BOOST_METAPARSE_WRAP
    }
  }
}

#endif


/* one_char_except_c.hpp
fPjeofFR7fCeUjyxzh7AswEzhm/jM/+5mDBv4THmZQ0Uso6FWtxAO6rHROQrU3O0Ay+MIIEkDIWeI5EDsqUEL1lArKw8jpfyUcqsRj9LEWWbRVoWIS11Ki1PnOS0nFFNcAy4CM8xtCsfKff5g8SIRXruvGArueek2dOpXWkm+WUi2edtjHK0EYNJ3bJGkLtIMpS9nIia6LXStKgRMn4gEdLy93MQUrro/0BIqayFnTn/fyDp6+3hJG0cEEbSOx/ojqSYD/FtNt8/3I/P9ynqWJ/SfRWG9ItDU8wTax6zU34jFsGAySPzaf0SR8WGR1jgTRGto21IM+gc3i2KI3eDUHo3bauh6r4Nivmh4zqdLWdxiSfelrMobZFQOkEfls0VayTx8gd1uB6VKH6l18nSu7zWKFVVy6a83Tjb+M394DYWDWTXQ6qq7RXK03nTIosulPRU7Y9XDEzc/qWeh/pQnbwFcwkAVvmOtZ+NcU5fYvuUMZOmev6Va3hr+Vi2s/rhe/jyPkxBGPiNfICvoCu2GPHM9Ijaq/H8Owhlsc03Rqu1l8Bh1auJwS3a4xZeKLUukAavXNZtW1bpZOBTbBADSLVM/DfcF5aJH8CbKwaLo7C4iXmKslLaLN9Gvw3yIwvRKchiHEILzlwwUAuzzGeZlbKOULlqDPou0elM6N1mUcKNVeiatvntesU88xKq66bxA3mUqTDMfRRSg4vQ
*/