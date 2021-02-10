#ifndef BOOST_METAPARSE_V1_CPP98_ONE_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/lit_c.hpp>
#include <boost/metaparse/limit_one_of_size.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#include <climits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      #ifdef BOOST_NO_SCALAR_VALUE
      #  error BOOST_NO_SCALAR_VALUE already defined
      #endif
      #define BOOST_NO_SCALAR_VALUE LONG_MAX

      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          long C,
          BOOST_NO_SCALAR_VALUE
        )
      >
      struct one_of_c;

      #ifdef BOOST_METAPARSE_ONE_OF_C_LIT
      #  error BOOST_METAPARSE_ONE_OF_C_LIT already defined
      #endif
      #define BOOST_METAPARSE_ONE_OF_C_LIT(z, n, unused) lit_c<BOOST_PP_CAT(C, n)>

      #ifdef BOOST_METAPARSE_ONE_OF_C_CASE
      #  error BOOST_METAPARSE_ONE_OF_C_CASE already defined
      #endif
      #define BOOST_METAPARSE_ONE_OF_C_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, long C)> \
        struct \
          one_of_c< \
            BOOST_PP_ENUM_PARAMS(n, C) \
            BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM( \
              BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, n), \
              BOOST_NO_SCALAR_VALUE BOOST_PP_TUPLE_EAT(3), \
              ~ \
            ) \
          > : \
          one_of< BOOST_PP_ENUM(n, BOOST_METAPARSE_ONE_OF_C_LIT, ~) > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
        BOOST_METAPARSE_ONE_OF_C_CASE,
        ~
      )

      #undef BOOST_METAPARSE_ONE_OF_C_CASE
      #undef BOOST_METAPARSE_ONE_OF_C_LIT
      #undef BOOST_NO_SCALAR_VALUE
    }
  }
}

#endif


/* one_of_c.hpp
Q9WF26zqauFcmElI7mDn9eVV8Wac7QT48eXHot8dtDruh3f9wkj399MHzyYStL3l07aqg53Yfn8on6HwbYM08HEV5HxzQ36rbEmFG2zUrIOgEoiZpymgEsUmL4WDCaKBLVdav8XyRe9LAITprbR6xGjj/JLrun5USet8BivjgF2TosnpLT2fQVh2fOfm5cerN5fvB+xUSqzp+jF/vG4YqqxBGVZlBm8R6+RUqwWG8v71w5sOtI26FxEztuDks26/fEr1ZZUeyvNX93J/upDVh5N/xfb3wxQyyflGzpx/15hv/oS+AVBLAwQKAAAACAAtZ0pSK4fbKhwCAABdBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMzJVVAUAAbZIJGDNVMtu2zAQvBPwPywUuIegCmU7aBFBERCkRR3UjY1YzV0m15YQihREOor+vquHH0DRHnpJLwIfy9nZ2VlFDq0TqcWYXUC7hnYDQhmNEraVKWASfP4EqZbgMtQwC6ZQpxYqLFUqKKbOXUanMxblemtiFr1gU5tK2pjNk2TVfWC1XCdsa5QytTIidbnRLOKnyIj3jy+IxRqrV6x8m0tkUZumoXuZurQH5JOrSZsPlt/B1paYWmSLATSEwpirzBXqw6Gw
*/