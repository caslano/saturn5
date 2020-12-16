#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/config.hpp>
#include <boost/metaparse/v1/cpp98/fwd/string.hpp>

#include <boost/mpl/char.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        #ifdef BOOST_METAPARSE_STRING_CASE
        #  error BOOST_METAPARSE_STRING_CASE is already defined
        #endif
        #define BOOST_METAPARSE_STRING_CASE(z, n, unused) \
          template < \
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, int C) \
          > \
          struct \
            at_c< \
              string< \
                BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_STRING_SIZE, C) \
              >, \
              n \
            > : \
            boost::mpl::char_<BOOST_PP_CAT(C, n)> \
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


/* at_c.hpp
c0CvjdaJX9VU2RBvrpgp9owNWCdukTjxGbUVM5ug80L2j2yyf+wY+19Hz6BPQIv1ogm6nOmjS029lyxFmqwLr6kZelTU1tdVx+fV17bMqZb8NfuU3ip0Z6/0CPa6CXs1em7IVsHy7pSxd+8X7rWyfk7NnIqZ1QE0XsOSaw8J9mfDJpdPr2lurJ7bUtNYLeV1I7d/vLZmemNFYzDGZja8iZXUzayrmFPdVDOzjmEC+epv49VVoK3V8WpWfkhDfQ3SH8xHDOmsubkREa+qnt4ys6qiuSIm8UqsH+2fUd3IBqI9NsbnVTc21dTXIccHi3+VM5cfRh/8t9legxEI90p7VXVtdXN1VVxsMV5bXTcTjWCPEXxesxCgmRUNBkbAC7np5kMaqos6VTk91L+vRV+IO6e6eVZ9VbxJsLcJ0xPonth2U83C6tD2BpumB6ubFQ/6NM6rCO2UBa+epWCbWbDpjFs5vba+cnY4ttpDQM+IVqp9yl5R+0Z6+4zG+jnxlro5FXVMAf3FfKXh8cbq5oqaunhFQ0NV/Rz+L6RFf70PFg4a1Dc1Q/hGiCflcqy2j+qK5oPjzbNa6mbHi0QCjvEo0re2oglRgw9ibNXegDzRW0CgaSN6iCtFD8mD+uNTk9muRFsyX5nJzWrP1fV0J3OptqpkRyqdzAc6uC6MQP94rxsniOQsGLNtGJWZ+eGdAIy/BZZ9S/E3Mhzi9bPwtpZ42yi8/hyfAWFs2vvL9nuwaVuzL8JlfuYk2jpZAziyDb6xutZkrr6jKYknzqTzsSKMkB7eNae6k1WJQrKpkOjOxsL2zfDHqXQhmWvONK3obs10NSdau5Kq31bRmAE4r+aDd02po5L1HfVZMVmia1Yy0Z7MxSJ4WayyM5EjKIBi+UKqjb74vI0HbcpSy9hT+DMwFpeaXYMQzKqugPuC9i1u80EHMcZ46CDXx8+8VK7Qk+iqaG8nMMnDD23PYn3EF8zZlzkHanNuFs4p1C1eVdOIEtZj58S0Xggzwxd4pvgy2OQr9aOAr8zND7Ga5OuwAA9Yv0HwlbXhA0hH9H/z95p5cl/bxfjhqZJ4R6I71bUCXlG7YQyy5Tit2UT7JNqIWcU+gjYCqcXpcO8j+8ObCLc8Bs2LfnaUtv/jYvlM25IERIvnC5lcYnEyvjxb3L2nnb2LMegFGbWfXo6xexSfzamsaMKl1VXWtlQFOtxHtlUvCNoOQE/7Sj0d258eLbXNNQID+1AVWNVAPT0ApirSdkx/aCv2Cm2PMGRmcUe8KPQdKHYgr+BCS9oX5zI9WSnDtP1AtHV0Z9o1nThdtKV7uvO5tkCPwDtbtOW7kPPYminQSsR1O2j07t+nOHC8I9XFvEUi6Q1Crg152IY1727oez6hy8NORXmgrT1RSAidkDK+sz5nxB+dKcFcN8mxoS8/he54PtkWyg9t6A5t3am01gZ9aOvM9ORiqm2rIl57YoVqY17RltH7ouO0rUgm9L5DRdsys+/IIp7Rhv2nLZVvF7Qdxz43Z5+7avvcEXhxh4Vu9qbZzBP5w//vHuofegqN+DY/f6SuMj4/nCdIXd1T4h7glXfCcPxMdUVdS0N8ZmN9S0NxWqeVVYixJsixpktajw34GOcZ9DXy38g9/y6P/s1K+Pdk9e9+4t97IVNShyepfcOj/XvS6UR3sn3PQmLxAcW1GC2sY5wpQ/FlzK38Bf8uZ2wpO5N7OfYBcuxy+nHSFu9Jx1tDnu+l2pbpNlm0CSGkDZndRFiDTfbu752v2Z6vTM43JRobHWHtfVj7PsbaU+l4JPby/9dvw1LpKZBjST47qdjP0y75uq/ka7l3vFk1deQLpKTxeHEc7d+y/zTZf3c=
*/