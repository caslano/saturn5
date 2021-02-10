#ifndef BOOST_METAPARSE_V1_CPP98_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct last_of;

      #ifdef BOOST_METAPARSE_LAST_OF_N
      #  error BOOST_METAPARSE_LAST_OF_N already defined
      #endif
      #define BOOST_METAPARSE_LAST_OF_N(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct last_of< \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          impl::BOOST_PP_CAT(nth_of_c, n)< \
            n - 1 BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, P) \
          > \
        {};
      
      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_LAST_OF_N,
        ~
      )
      
      #undef BOOST_METAPARSE_LAST_OF_N
    }
  }
}

#endif


/* last_of.hpp
LBpn2WZW/596Ykpxl4tp6X9QSwMECgAAAAgALWdKUncsMvBLAQAARQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzI3VVQFAAG2SCRghZJdT8IwFIbvm/AfTka4hIpemJCyxCgREyKLTO/resYaRrt0Z0z+ve02xAsTr/pxnvc9H60grCmTNcZMaJNbvxzw3Fqn6pilq83rKmXvyWb78MQEv0YE72E2ZmPYoTuhm9ZaIRMOq/IcgGHTEY+lRkMDkXUHj9SdLmYFUeUFl6PIUVLj0KchLA2Sj12vQBh5xEttkBWYHcDm0FSllQpaTQXUpGxD4FBphxmh8irey4SPaROzZ6/lem+sQ55bx+d3t/ewTtOEz2c3IzYK9fSkyHWJENTLqLT7jpzRF0WDSYu8lYb+cgjKUHFmj0dpFNiKtDXLyNipr69qgkff4oLzyXq7S1+SxSR4JNu3FKYp/E7oDQejMN7LFLv5fqDT+RmUJAkyJ3RABUJ4WihkDZ+IBqK6sBQxcepYb1E5Szaz5f99XEnBf+T8+nO+AVBLAwQKAAAACAAtZ0pSCiMxfrEBAAC6AwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMjhVVAUAAbZIJGDFU11r
*/