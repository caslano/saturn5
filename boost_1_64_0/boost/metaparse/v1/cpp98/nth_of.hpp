#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        class K,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of :
        nth_of_c<
          K::type::value,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* nth_of.hpp
9KPke9f5mzd3vAh31VA60LaBWMY7O7z44AMP92vxj9PMadTmG+rA1CvCcqvAZR9JwG8qjCD2xQ0ZGckIfHtcq2eKoBfa14C/lUQ8/PNL2euS3Znh5NWOyAhOQWPmJBGjBrc/z1m7tNnccx0bLzYlWGIbnyv+u/E1FvKWV1kKZ1PbHrEkfyc44ygrPm83uyoTVK0srIXyPi1/2/l/cm31NunAWnOarvXkpIyJjuupzKPjDk9i6ZQ36nktQrwwReH2t9Ls3rXwh51dx5bK2Uf5kee7Ct1JP17pjLK3t+pXGQ9xvmTrtZRlaoTNq/FbkEHPae83jnipsvj5ksGwrN4HfbLc2S9yrKfCMIl1SeKNWxE0wPSucs+ulGOboPitgV7nb6EnjZj+6mZYPbIGLPtm2NiptyML/HIGF6WXS8yqal1AQcp63LcuCoN0PaDxyl1/Wd04RZZy7c3suDVFVR/GuzTal46JAmzITb27KOEsFFSrltWl4+fUqLDKuHRfIpX/Y1seb36YPyInjFQpSCXD7SKNx6K+d+DR2TA5MrS8IG1socerR6bT5ZF2Zw==
*/