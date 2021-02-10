#ifndef BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp98/impl/is_none.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_char_except_not_used.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
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
          class C,
          impl::one_char_except_not_used
        )
      >
      struct one_char_except;

      #ifdef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #  error MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE already defined
      #endif
      #define MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class T)> \
        struct one_char_except< \
          BOOST_PP_ENUM_PARAMS(n, T) \
          BOOST_PP_COMMA_IF( \
            BOOST_PP_MUL( \
              n, \
              BOOST_PP_SUB( \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
                n \
              ) \
            ) \
          ) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB( \
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
              n \
            ), \
            impl::one_char_except_not_used BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > :\
          accept_when< \
            one_char, \
            impl::BOOST_PP_CAT(is_none, n)<BOOST_PP_ENUM_PARAMS(n, T)>, \
            error::unexpected_character \
          > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
        MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE,
        ~
      )

      #undef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
    }
  }
}

#endif


/* one_char_except.hpp
2pS1gYxr4SVKoIC8cCirj4hIClQuBYsENzzJMLmHBSGPuwYfTDdmRhkuIewxoZsH7dkbAI5geATttX2x1yAI4TIxEIYQ9Ee9A9j737hngeErged8ZQEQDIcUeIE/Z8zT3vomTAC9DTyAp1d/AN9qCcHBOvZqfHJ6PmbSJnb3a8FwCKeYkBwXPIQ72lovhrrSPr2Seu+p+pdJNmXbr0RySKe3bOvepP9X3eGQ5I96+9QOTSEVF3uZWci3Z79QS+j3XPYBoEn+mv1F3RQZ7I/6fSjruz9zDt5aMe0Xdfy2+Wz7r/vcGeCzzLEwawMkbkGQtmdjlpqS8JsVRAVfoDMYvEvUoqxlpfQK9pzHPkI+L5QmD9QU4Je8qhrxHkSuW69MTsiSEPktB0REsOCFiJlH5+o5Ci/NJYJUc98tAyqcFIx8f8H1akSP+0+7Xy+ns7PJaJdETC6vZj7p2zJFLt4mOO4+ZemCdbX1ZaqkVI01tmkU6SqwInNrhEQjN6S9ySyFta8FJbWWbEE7R0BYp7b6qBVtkQG4KmmstC8ieAUcPgeHJN0Ktkey2Xl3Jjeo83QF9syApwb1dqTQpKngDmk6datMmS6Llg5LFKVWRiVKxux6Or5q5XUYbfp0o41Wt6cdNxo7bPZrMoaTjpuR
*/