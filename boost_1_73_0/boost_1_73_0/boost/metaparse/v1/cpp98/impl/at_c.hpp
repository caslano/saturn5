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
ePONXPA9ezf2HpAdFzAupeewMkcWZ+GQUNgV0oJBOlvQio4IOS7rNaxQuNogOA2iLPUX1Na/Ez/k0lBr2uxCgF7Q3yOw3hR07aragVRduiDVOiCO3+evv9LHRTp5mcNWGCmWJanYU9DgAiUJPkXixuCEFc5VlDkcY29Hchw/fElXeF6hcviHj13oTYKVBNHcJGAq2ibsXNSoM/s54aVeB6YmH2d6s/Gwe5/bSvea7rr0JlVW1jm2G4ER553n6SJ9mUUdL202nafcD81LIwWEzAsUufUx4thDEwkJdWE3E1ahKaGzmI9JEC/l0u8ZV5oWRVpnr6oywBzWgVDO7hLkfqRh2B9o5GoHYffFyqEJY/CAUAgLS0QFbVto12bxNtR6KUY7nekyYd7YRv7hS2mxZyKL4K8uW+ydRtN7WBM5bXptSt75eJwvXqZvLfaQZVhR+JJf+vUkxUcKmj5NZQBhxdu+Mc9Hdh52OKQPdddndUcf/+MPuWn/+tD+8Kx963Lawn3/Td3Q1/HjHPnpz/MPUEsDBAoAAAAIAC1nSlIjc0FAeAIAABcFAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMzN1VUBQABtkgkYN1UbW/aMBD+bon/cKLiSwU10G5T0xCp
*/