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