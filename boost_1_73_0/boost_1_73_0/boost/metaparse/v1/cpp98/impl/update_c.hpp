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
cL4kET55olbgmBXWVnRzNCMnR/w5fvgQtnB1AwGpzOEfUvZ9DPGCYEZAbT7BU9w+ZufUJr3Fzxkv1dbXa++jTO12DvmgdleqoO2xTychs7LOsdvSDDnvPc5XydMi7DmCi/ky4W50jl0wJ9QDGMESO+t3MmYV6hJ6q+WUKPBSrN1+caloQYSx5qoqgSjx4xoQylkuQR5G6Yf8hlpsGvA7n24sai+/A4QiNbBGlNA1hbJdFu19rKOilVWZKmPmBG0JH7+QDnukYiH81VeHvdJIgrstFacNr3XJe2/3y9XT/KXD7rIMK3Jf8ku3lsT4swRNnRZ7CH61u64xV+8/+CZ928f+R2f9G5vTQh1UaONGLo5/Doif/oZ/AFBLAwQKAAAACAAtZ0pSXuVNNe8BAABLAwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNDhVVAUAAbZIJGBdU8GO2jAQvVvKP4xScYNG3fZQrULUCqiKVIk0CYvaS2WSCbE2eKLYgfL3HTuwoF7AM/P85r0ZJ7ZobCkNJiJWuib+e8XLmfrKJOJbkYpsVWQiju7JOBpx4h3k2J+wnxlVoYh77NoLlytpJWgqGyxf5+EFTZiImojE0f3Ekas7liueaRatQm2vNKUPEk7b
*/