#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        #ifdef BOOST_METAPARSE_STRING_CASE
        #  error BOOST_METAPARSE_STRING_CASE
        #endif
        #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, int C)> \
          struct \
            size< \
              string< \
                BOOST_PP_ENUM_PARAMS(n, C) BOOST_PP_COMMA_IF(n) \
                BOOST_PP_ENUM( \
                  BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_STRING_SIZE, n), \
                  BOOST_NO_CHAR BOOST_PP_TUPLE_EAT(3), \
                  ~ \
                ) \
              > \
            > : \
            boost::mpl::int_<n> \
          {};
  
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_STRING_SIZE,
          BOOST_METAPARSE_STRING_CASE,
          ~
        )
  
        #undef BOOST_METAPARSE_STRING_CASE
      }
    }
  }
}

#endif


/* size.hpp
UdqtmI/+LWSpGifA77+M1I7nJmnKPVkmt9R2r9/fUhOGy1km/B5fcv3+s7zz1+9XfxlE4/1nmX5PQSmAQdrfIvT7/l0w+Fg4p34f0h/PV4fh4FDjGbvrkDHreIccGn/+HbJrXRCTA2CwBi4gSwWXzKmWuWJ2vxjRIxPXReKzv2eXHtnSZV13y1f/1V5c/G9uL6aPP397MTkEg9RnQuzF956LsBef/nck4Khjdmsveg+nB/cIjiMF7o/n0NXbcQb3YmIOQxYPPrwUq0tSqsmDF2h5JUPjr//z5fnEXz+6luKvK2yR8deJ64Lx1wQJKYpPrmIiGuEZR/AMDwnH/sdaFVE1IHtMoq5rQDYDexiCLd/jVfM2It7Tq6smENKx3SI92qshfdTM8ubfFILxgXURGO9ge4e6IO2vIhVk/Tg+8jSkU/6NSNcS3gQJceLfng0iPZrgGUavsXc+q4pEekJCENnbbuHojkaA5YWPUpKMEHwLCd++q7rD1/Wohu+Z5K74Hv/3eeL7yhrCd+fYSHzT14bgW6ji+89nzoXvhjWR+N4c3w2+LgRYlpaF4cv4mhkmac92h/LNyzSU45O75es/1p4PX/+zkvj6B2skX4+sCuHrEpWvK54+F1/vqIxEeWbcWfl6Sh9E/OmSCL5eRkhf9Ux3SM8o0ZC+oE/Xfo6LxPhs/fx5BfXzIUtkP1vWhPTzMrWf1z91rn7+riIS
*/