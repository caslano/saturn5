#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_UPDATE_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_UPDATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N, int C>
        struct update_c;

        #ifdef BOOST_METAPARSE_ARGN
        #  error BOOST_METAPARSE_ARGN already defined
        #endif
        #define BOOST_METAPARSE_ARGN(z, n, unused) , BOOST_PP_CAT(C, n)

        #ifdef BOOST_METAPARSE_UPDATE
        #  error BOOST_METAPARSE_UPDATE already defined
        #endif
        #define BOOST_METAPARSE_UPDATE(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C), \
            int Ch \
          > \
          struct update_c< \
            string<BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C)>,\
            n, \
            Ch \
          > : \
            string< \
              BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
              Ch \
              BOOST_PP_REPEAT_FROM_TO( \
                BOOST_PP_INC(n), \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_STRING_SIZE), \
                BOOST_METAPARSE_ARGN, \
                ~ \
              ) \
            > \
          {};

        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_UPDATE,
          ~
        )

        #undef BOOST_METAPARSE_UPDATE
        #undef BOOST_METAPARSE_ARGN
      }
    }
  }
}

#endif


/* update_c.hpp
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
*/