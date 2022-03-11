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