#ifndef BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_char_except_size.hpp>
#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp98/impl/is_none.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

#include <boost/mpl/char.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          int C,
          1024
        )
      >
      struct one_char_except_c;

      #ifdef BOOST_METAPARSE_WRAP
      #  error BOOST_METAPARSE_WRAP already defined
      #endif
      #define BOOST_METAPARSE_WRAP(z, n, unused) \
        boost::mpl::char_<BOOST_PP_CAT(C, n)>

      #ifdef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #  error MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE already defined
      #endif
      #define MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, int C)> \
        struct one_char_except_c< \
          BOOST_PP_ENUM_PARAMS(n, C) \
          BOOST_PP_COMMA_IF( \
            BOOST_PP_MUL( \
              n, \
              BOOST_PP_SUB( \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
                n \
              )\
            ) \
          ) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB( \
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
              n \
            ), \
            1024 BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          accept_when< \
            one_char, \
            impl::BOOST_PP_CAT(is_none, n)< \
              BOOST_PP_ENUM(n, BOOST_METAPARSE_WRAP, ~) \
            >, \
            error::unexpected_character \
          > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
        MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE,
        ~
      )

      #undef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #undef BOOST_METAPARSE_WRAP
    }
  }
}

#endif


/* one_char_except_c.hpp
P/S3Xf3eUprdfrvg85JilGEzDTMBVt+i+WHVDtycsQ5MdZbaqweuiwrXfD7+FQjiL4fplYaX1Zu6nGMfbyL4gQj5Okmj2/eBMD0S4nkl+DnMv9Y3eFG+bFdJ9fUmxBrpMXhUKa/1H+Jj+d3+qeD7KDjzEQ/Bu+017TcFfouGW8wfF8OAQvH5ID10t6A93OclRtKBx2noFmYPsMnvM/b3580M4zo7t59JOTwHlM4zN2v0ntqrXMqzlctgx1+4Er5udTbcMvj7o/uYw7XHt12875Ue/AYWBOctZiYLD8Hkp/THK59fU/+F8GURuUxJ45r5/WIN0XFqX1r7az71Tl29vF8NexahEs2aN6390jg18Uhs+NQ3gXoV260w5pLeXPreuu/AzyT6QB7fPtNbn/Iz+OT7qbRkftwbF5YdV7PleSG9dbqMuvlbPPHd3sq0E62+9pn8V7PnmXq3q94Wh6KvxJDfuAbrb+CYMgH63/Me1+HFzttwqQv9Epx3ee3rhnJxBy4/UNOJ8Rztc2QD/61fd+NecQh8lV6/5fM8cA44TZd9Vs+c7rB81FeDZcyZu+EwmuSCmu76rxio4Uz59QX8/RJHrDK7CODm2jiq9BK98Bld0kHet+KV73FRH3OdcHE4joMK01I3nXn9Q7P1MENRJz/Kexk1nTCjZ4bNkQ/A4LcT4Ol3odaH139Qi1HNWfBu/0xhfiZSHTV13pqAjlZLHfTL7Cj+8UYxnpoDHKaZt8NS/uisOF1cqdesIbQ/DfNaDPD7l8V4amdOCeB2b7lc9Amp95KehwkRPWFqTTqcPxndFddZc668NJDvFVELtSrQrurzcELayz7G8VUf8U/jvmK0Vj3TrPXnwuPM5ogt4A0MeFUPD7blPScFPB9HmwZ//t/5ZvpwvT1fPauvYRHqbaSexp0VxPw8fI3/Hn5XhgPyO43/vJWPbmxLg+VRQxXlWl4myH+ggB6h4TbjEH9TJrDtK/MY/fcuvj6NJeYX/PP/+afpu9q8Fb3xg3nWH9aUYicco6+XeTale1mxlbcdaqbF9f/PUTcWha3J5e5P/oJmrw6rQ2bBmvR8oPi+gL+ncH3DKHg8trmN2ffERPjguZio29azeWXz+/m5aLwM9N3PcB7Oxh0KS8Ri0Y/WDUvTmMscHUaLqqEeuWC9fFZxrWEdzIjU5W/Z5D+dc+MEeEgNhHcxc1mL16vArY6eC8H/3T7n9Wivx43V7Ke0mPuUq8p/wec+t/TOZTmkefNt0mv31J56G22Nv47QF6/swzVHDg/lMfjhCfJD14bhrZ6ecZqOt/osgnX8RuLY4jjIGvKKFb1fahWuOi3P0dVWT7pH/TS4JqZb8PQHeRhhttWa3oX93f/SJ9f//3Ph7WDWIPPbl9NpUx6kutf8A1c+nIXhkyyDfxlurT9bc6LxYqgOSoj7qR7wYikN3lMPzZEztbKmHV6YzQvrwylf4rsruKIRH18BnuK3FXBhdY6gTjfLWmamVsUZIoyN4Il67aZdMqpPfXpov3hfgPfuPfAlX13KrNe5TxVesmB9mN2PXjqFd+Xy+AE1kRmfTbRP2q3J5VDzF9grl8cm+vp2Gi7UfB+OJ6Fd2teTg9LOk+BobnG+tQFGnuEjcVXLiXgBZj/HZfG+kTfYmV/cDywSN9z2GF495wuvLOfTC+p9z990NWtvG1due+kbM578rp/4Gq5WI03Mb4tY+9THtCEun3xE7/4qpt4bllDt0BQfaOFdYll1P/zj6YqWMGNcRy/D/cJwIYweTkUPV1Pj3Xdaf2l+SJ+WojUa6PMU+OVxfLUmF+WXwJRd+LKPc0bfD++Mi5/g9pPwTH3SYYFG7vs1rRnVLG0=
*/