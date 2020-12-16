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
Zt1rjXj0Sgpakf5MWcczXMPx/hRnYjh4d6Tc8dNHYFNcdVR0td7dYjaIA3v/And4pWpV7Fss76ek8Z7QGb3xak06igYr6d9ofBVfbx96xnPzaKkmyXtuvfFWn8OWpZnwvvgfe6139cZFGNXK+2aehFu0x4h/YExH92qAx5LhCPq8gLlRnM3ynBevi9mQxGrdPoo2h0WpYFjQU6j1RF2cCw3Wa4V4mLuwA1fu8942zrn7NRIjfqy8mI2+jLdXqTE4e54OPDJQv02kt/BJ6DBaMXco/UCL0fSNvuIjxLV4PfPDsmbJC3jw7/SKnL7kh+/L19IQulhvVKfxM/NN1/FkRZq/VEc4p/82Fvba6HKqp3frrwuvrGcMPaEWSv6tpoZ4PkMO4tAsK+fJnR65cijo4+wjrnN5vjjvbhx+hKeQn6z0+Nxk6j8nLVzZfNo9Wv8Iy4I69nvYWJqv2ATnxtLU53je9WKAS+dFk3MzzvfpaQPcn+k38XknjzRjrZ36ZCg+/N5a4EpTPHunEh6Wiyc0cFd4Hxt3XK4Dr3rqef7hAn002FyyvT6NWRS+ltJjcdRMXnpBz28sA59ornA1WXCwf7TCuwHWlNb8x8zohynq/wbNipd2ZIEXnWmuLrRuErNTeq3fQToZhk/hFQ63dy36OVLcnph79b1PXxbCqzP1DN+Y6zicGYX3vL9zdBwLY5ZE00OwKnsW/KMeK1aWO6+91jsETtGP9pjY+V1tdRyXDpmmZkrSGNkbmtngwyn3cDoNGcEPV6hvDso3/pwY79A0u6LSlVPNHh7A0z9gdAM5Va/nXlnzC3y+x3r46gah6uyW2WILXp7XuMAbLehizfqpDl9Zbj1NiyuO1fY8Iq3yTWzaaC3sd+b4c/Bn+Orqh8r4DV4c5nEi3XcfPfB6t1y/ptU7yDOd/vVZuTxurm6+1lAvJ3gnXzX01lk5vGWNd8T3W9yQiWeOhbOO09jDxCsfLFW77fna30vSBHjjWD9cvBv3/ce945npZrE+vOOMIvDIvROPh1ETYYn9jaGfh8PglPNojHtelxwevoDhq+D5Yj0sD8Vdr20v2EF/+ZsDgeXv1aH6W5JCbn+BhS95Jtdtz1cstu5ha+3rWzrc+cMP8GKMn6PwN1f8fnO9lQiX0bW15DNdT96pG3ykx+7PMR9SP2dogz6J5F2vvG2lV64H4B6eTQDTjuI0OjpSjn6jSaPzui+a8H0JaWhYdbsGvrDmDJvc96papas29aFn9EV4DHMfZ5VnrtHGk1xbjmZHxXfie+Mj7VUWBiaTQ/riRxrtPE46CefG4sGN/egDz1ccCjXDSennU0bBQH6uGn9bw5xnAl7c9g3Pqx9e3A04S4MlY+xXr+akq+fYf0a4MiG9ehDbeuYuNWjYIimcey00JzY7KHYAjyxTl+59oDHdzhPGLQWnonhuEfbp8cBTnLHnlDqgmbat4cFHwVkclz+pXL53/lzOtcfC89H43Nw2PbysXB3vydVgGrB3ZxzRgUb9ki+Ur+pwe2AXPGZusXMvjmml5lryLNaQr4HzyIx04VnnOxPFJBr+hlN93+JMvZCvNhywnp9f4TQx6tZTv+GkIhXVb2WYuCxgdq4+lsHP32kSvH4tkfvhoLOzrJt+C8sprhEwyf+/nGrvnejYivqBHh1U233V1xB89Ry/N7lOr8LL7/R3AZqqSxr8tN1swGsby3Un/R9aGB9VdWYsxyWS8u9NYb+v3Uuj/vp57RznN/I0RI1vqiRmUeDwFXH7Aj7aa8NUzqbUwcGC9tHeOivTHXzVrZH4yV5Sd4a5mTwPKF8xRqu3f2HSKDHdig9hVG09n9U9RlQU97EwKI/aTUAXTqY=
*/