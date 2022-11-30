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
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
*/