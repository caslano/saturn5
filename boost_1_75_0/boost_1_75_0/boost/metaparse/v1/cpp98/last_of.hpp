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
u7ECX6n6lPLDpDj9RTCymkFVKPtRKH0VL+741X+9AVnPTrq5E7O7Ze0stvpGpCnmp3swxnMbtE6y5oywedpJEUT1GOw5CsIhUsFk2IMmQZgMaR58rZuoiwt/7Txn1EX7+pB5MCww6W6Ditc9Pdk8ONbpS8cJUGTiOYvCLbJ2UsAFDiOaBmH2s5dfCQPJyXJxv21ic6DiGHwGQy7+tH6F4cBWgG3JUYKtF48yJhisUkzgQh5mfDxRm38zQ757LQvz8Bvf6MQkVcF4D4QBvu3URvJQEw8udg3eFjC4pK0oEXNxu941FHAEXAr2ixp1LV9zEtPqtInSaeSTbaJ0jWIuJhjaPb+2fkXGRMitidqtlf+nrll65Nxdc0vN2bpmmxYztj3h/6Fr4mLP2jUHD5+7a6YmnLtrYjv+S9c8EdNN14x0sW33WtfYoIFU+dXfu/bLtnhO/MDlYde/UK9bSZ3BG9tFaYxifoVuKDyuVNmlKFbQFsaqg3tJvCoPSC/AZ/bCM1JtMDL1FvURursO7kZGpj5cojtXZGrdY1pkquEIGi902HFYOzyCh63vsAJnLN4ra2/2wEAp2HxXK+ZTUZSN8QK2HWXLaSSxYv6OrrqjPtWXD6wuRUuvqhQtvZjHB34MB4+rdV4jYlmtaIJhHTr5GczHKyWuiEK5neifhHEWNlbjRrBjgWKnL3HMNYbIbSQOZX93PtZMyg3YIR2X
*/