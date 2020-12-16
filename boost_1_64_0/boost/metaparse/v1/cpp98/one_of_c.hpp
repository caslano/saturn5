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
4GVM3LZTDDN9YU+P7f8OrF+jr9+aNdBJz9RpDhjyEz07MxveokFzP6T3UllDPv2XPWCuI5dye+0zuqw7n2Am1JmvSqu/Uo2BYYdC+Gv9dhPO3qLxxOEP+iosGsxdEnz+gMZUw6E0ZDn91uaYeBf3uTg30c9xVuGKNOa+PHxWtTHxBz//SUfXGg4z7WNtAnPOezAQp/WiJauYk+6G7dXOwuZtzl7cv/oYuv06jMmCn+7ZRwQNX4++mCDPsXC22VW2PbjJdTv95Nz4LzXoNWdrwL0r1nxI3ruE6l36Itn/z/biPnE/OFEs4Hyvjnxmxkt052bz2pVvzWG9N+QlLIRDCS/JaUu9Zw61WC39Jufd9HPiOfBhkJ6nB/qr64a0wZniZs+l3Q+XppkrvvzP5jfyuVpNq7UNf6knOJkDHzyqiPsW01685AO8NSaLGOGWnj31qryu2hHwc0H0AM1eN7198W63/gNPB4rzAbPxxvpXj3efi+udqa4yU9nVky+aih9wVlVcGx7hPAGmblePOWDo/qP63QzrTko9qsdiVobh/HW3NTD6CbyqSN/K9Rb6IZAQHpgXvsIVn5Wns+aYNxeEbWnpw510u6/32yxPMOlhHH1kLUvMCwaVVA+z6WyYMo8HSL6NNm8Ij+j7H6LCDPXW9iiNkI/+W+MMsI4ZdHkf+/IRZcxS+Yt29NPJRjiPH7vUix5fIk9b1Shv8RHudsCdH+m5grx4WEw+Ut11mgmP8fa61WphLn0UoedaB/z8BxzAeUUG89/VaNiqMGxHqPNGa8zuXnJjFhJ4W9SshXbNABdO9Hb2+1I/x8aPai7u5VB9Jb9hfJV9xI0vby/karOP/GM+3JIsg/jON1NTM0V3hfHatHgQH9LSCQPszxpXdnOWUB02toBZ5tuT8O4X8rW7E8wJhSG49Ai8jGfOlqOUc/xo+tpM51InfDeVbhuiFx6r5UX6pj1/lVn8t9AO+qfTPLMh/fZLTPnQS91qmEfSkHeX4PJ1uCE7Xk+BK+HBL+LWj59I9IT+x91ZO8m/uN8+zBfw89cLqbEszmLUTMY8cmCu8SDgWTgYPaoS7Pa1IgVgt975kN+6Q+UkptzClHBxWWWGWXG8GqEl62Qyw+2tpkbxiwHzfnl9oGaS1adHa7h/Wfh4CN/R1+/kty9NtfYwv/HMuvn9U33gNW23Ziet2QEu0tdfpwyYhdAFuH96ioBn+/Gz2emkgZ6zLQrbErp2iN+hghcKNoIb1+h5uF9Gr1ZIYF88zqMuntuS14/qpQzN3e8D7aLO58hP+DSxoBm67adhYdXYETRFFXgSBnubWOdQ18XlI3D+8GXqbywePi4v6vlQAX4i4NmG4upwiGdXZuO8BvQrTdIDDuX+hTbLwb/XwtV6rgc+mRys1Qr0ld4Pf2jva+HLYBg82hrEe3Vxc4nL+FIe8unzkfLbpqX30e1nNuoJuP0PzTg+RH/LQWzPP10pSYf6uFEsOvRx9pPOTLEU/RCfp30E5zrBATw22triZ+Bn+vFXvj4vjZo9H8pzeq1crpGzcb52B69/uAarzAnS4bnHJWlks7vXQ+RcrubSHOEbYUhamsUzJIOOqc1l+MFMIrNe38mXfDOPnhDHI3TviB6eP1GfB1rojeBzwCfMkuDvqq/46cuwybVb3ecVxbs0PRJ/rutWpYX6q5Vk+vMKfxTpPICeTBSQ07Z6GmfsCNAhg/TpTTVRC9fx9POWWAO+eFmHDr9s72auqeHzcPqnPH5+OhzOleHnnYuv6A4D/rRG8+cDUdS82Wn1avjUXDLbRbGw71j/8HZVafs/xNXz2ZE/q4e15r5R5c+a0j83d+qm7/Fj4Vrq0ay+gx4=
*/