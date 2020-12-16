#ifndef BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_CHAR_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp98/impl/is_none.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_char_except_not_used.hpp>
#include <boost/metaparse/v1/one_char.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/mul.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
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
          class C,
          impl::one_char_except_not_used
        )
      >
      struct one_char_except;

      #ifdef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
      #  error MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE already defined
      #endif
      #define MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class T)> \
        struct one_char_except< \
          BOOST_PP_ENUM_PARAMS(n, T) \
          BOOST_PP_COMMA_IF( \
            BOOST_PP_MUL( \
              n, \
              BOOST_PP_SUB( \
                BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
                n \
              ) \
            ) \
          ) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB( \
              BOOST_PP_DEC(BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE), \
              n \
            ), \
            impl::one_char_except_not_used BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > :\
          accept_when< \
            one_char, \
            impl::BOOST_PP_CAT(is_none, n)<BOOST_PP_ENUM_PARAMS(n, T)>, \
            error::unexpected_character \
          > \
        {};

      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
        MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE,
        ~
      )

      #undef MPLLBIS_METAPARSE_ONE_CHAR_EXCEPT_CASE
    }
  }
}

#endif


/* one_char_except.hpp
pxltqDfXVIGpTdXSIRycVa884gOKm7/Av4PqJHyyuVrwGWJz5974bsEJvTeLLohrLlEVz1zAnb5XmQ5dx7u+joL3y9Kck3jKgfRwFGdW7jdtlDXB56ZmXKuLBjxnIXc8x5DmrqFut9yBi2LZbyZfeVKP4YLAB56Yho1uv7kLwMkF5i56OTXt2fed9Q1xRmJt0Yc4A/W18OTqEB9k5BnPFVMPN9XIArOE2/Y3AL/FCXg2HW5tcV3atZV6PmkWVgkWB5zjb9WHPcWke2MY15JHTqCGU8FjeZ/aVa/FoK/XqkdYFpd2rwDzFlfHH2Y74x7QVDdpJHgSLyNd8l5fPnKuigOGqO0s3Xkxmm+Vz2eJy1k11A4Pr6QfEjQLeh+12YTurMsPjuUBu4jBCpzAO+U2LOg/Ul6WqWfXGKFOUXygSxX3t7fjk12DdivxWGza8Ya1nU2q13HmX3/yqqXUTSK+umMp9ftWv+ZT63F4ubLq9oh8PFMr9nHbdarM5rku8SriP6CZmKuTAuZlLafqm9jOUGrAiO50yDbXrQ13/nSvsfQBvuqF5wp+SxO0gB1P1GtDuB0T7uL8LyfhW2saSd//fUZtFKKFo/N/tNE0mD6mF300x3yOv2ocIp/zcbRzi4c4r2ZzOKhP896Hn7FcX2+tWE/r0Ct91WLmP+gmPBnXOd2zd2JIA0RE9bFycH/q9Ja54SUaYghex0WD6YV2B9XrOtyh/zz37vfl0a3HYLb9XJ4Kt7bzJu63zdq60rrDCjnrnEfrmNPC5EBRNbEkLz6HFXXsdw8uSLoEBuLS1ynCPLOG59qo+dzOUXBTLH0VoA1qwZ9+tfC/9UYvbF50Gi8EzzP60cWTnZnSMYP30D5zaCU1ga4Ci9bwd0PpPTOaXGo3xL3DcUgz9dBJ/a/z8xbZnJl2xi8bxS92BjP6BPiJbuqcnP4Vyxa4sK7rjTEDXFHBM2gf+QD5KsOr57P27M/o1YmwLWPA74LnU2nx2rTmk/TyssL8sL37DNfXYZ71Pc97RMjvavtvFuC/YJve6oc/Fnhf+vV6cyauPyB/r3igG3CjjV4183nBq73tSxvQSg/piRIv+bYa9t2XH6L5auTHCfCu4gXY1k0t05M/heuxf/AKLM5yOpQuwv3qf3JJ76dl5jzjv3H3pZ7ioz6yw7wUPp8Y/J2SvwXMjei1aTD4GU7or5bMYzr+7OwsDu8oNnPk/xM9EjkDti0Wmys0NT/+cbhc2nsZOHdxKhwcz5tux4OnaHR80z4cz+yD6QPE2POEM9OZM+D7qvn1L5x7OQVP4rmz05wl8zIZMuPbZAF/rwb3HjKbCqOF9VTvGCE0K56pAcOq06v004/06Wu4vBu3xaNlZtEgPaKpATUTUYG3S6tOH9lvFbPO4N8Fsr/x1eQkvdzv5qcbmDusprH7OSuhOQrAlINl1OFea7lsrhEBK3cF5Nr6c9AYsObpPdgJxy+ug2HDYBUuiRcfp+Apfx+Tj4FJcO6TISF6hCa8a/66Ui987iwkFKZlN5cT73U0d65VvOwp2tPamvIORwuoi8t4fRD8K6SPs9FJ+Or3tjDhOX0lVt2WOBM1B6yaxvxiMl6j4zPBoYy07CJ66s+T4v0oYFZqRlzAdfRF1K76ZZR+OA+/K8ofLKoBezf39z38t0d+lhWAJTD7qWtt/01NXlfnteXP7Ov9XDzaKpQOpB1nmkPSuZfhy8iDuDPoSTep2zqwpbI+/Ekf5FVrPG3EH/g9ozUehP0wsmdFOMJHZRhN8+/Aq0XxqRliFJh0/4DPd+CR6DTaLzRuRRobx6/dZ03WPvVvnoWOKk5PrEuod5z7j8+ESxfzpvJx7r7ngM1KBzk=
*/