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
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
*/