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
q5gXv0X39PeM5VwBNxOM7xkfl+c7vsaieBJL4Sn0xW+wJZ7BPngWR+A5HI3n8U28iJMwFRPxEq7Eyyj9Xsg5AOucYOz34pqU4zssijexCt7Clngbg/EODsC7GI73MAZ/QAum4VT8UZcvx/Vn9rfxi+T7GIviEyyNv2MDZELe2wXsjFmwK7ri65gVAzEbjsLs6f29yPEaGzro7+UVaY92w7KYG2thHq09W47FlM1Be3YxaX8u
*/