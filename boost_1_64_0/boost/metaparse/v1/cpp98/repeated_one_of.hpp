#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct repeated_one_of :
        repeated<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of.hpp
iAoXmpfyLNY/IZ5fwJUz8MRkeadNDqXj+aubr8HoVfjtCxov2Xneid7ZCGMe0tb9zSUO1TbnmAVDzZAn6c/SNPUb1x8ubm1w+8Pl/F55M8zBYkP7bnni/Q2dSWWX36RiUsP6luNz/DP+XzNyGPa3/K6mi0e6xkW4EcO9s2XA4/qt3R247prh5n0t25oPpaCxx7sWn3eFfk6RUc/BhU/FvpN6Sh3fa9XvQutLBau74plaDXHkG7XjGY+vJtkjb1JfvE7TNwNz8O2X6B8euhr/ONT+m1pH07gwZw5/XU+czsLfaDQ7XVeXp+6i3gebn8/p//+fvRqlhjaor+a0R/ObYlyGx2tAX2fiQ9fo30biIs4v8HyeKrh8Ee9/yqy1i159Rmfig7iV1Eq4OZh13MV9xXnlhM5onvSmPXH2OX1aZLpZIoytF88cA2dsUu+5aLYQWr5/IvOfkvQojz+jivjbw94t9vO5mRZcyfQ0FM/DK1q9PW68qN/z65MNdb0PHk8L/u78Y7S7vUahicyhA4Vp0VKwfnIofwqvu+EqzxgG+ozXm2H6RH9n5BHaN6ddx6mfmGLwiEcpBnflYeEz2NTR5/ZVDD7mV7Pb4G66mK5v3jxAz4achllivUtvpH9hNk/bhPzBg68Wy6Jiqd9KtKJzxgbXCnPE7Jq9xodTu2FOInObsk1ompe0+TDPgdGWffbyUPT6wNa4bDqteA8+9aTDF8kTLsydSf/Pgodt3e9P+KiOPjrfKHQebqvJEvAn1STYkct7S+s9fN9ADpOfhRkrnA3zwnN5sL4naZM6agT3/v4I9jyXV+trPYJ2KoH/cvIm8rGetv7V/C/zeFrMcwQn5uPr92IOv9fJczGet+ZJ8wJzo3wl1OTneq0sTL9gv+H8SyUz8jAepTONcsfMnp5+kpS+2WP2YQY1Ux3fL/N/b9NqhrXj/eywdFlf6wmeK62gX1PhHLlMQyve4MUO840/qqHD+mdBFHGuI5eJ8fJVz/zokREv1NZjenkvL6R/HunfodeduwynRz/qqabw7I453EDfVxdT9EQ7vf44oeep8F6NrLi7ip6spmenquectBI8maYvd003tx2MuxfisxRy25hOoH/2R8IEOf9YWmyH8oLbYbznOO54fj3skj7Q+29pkJ94r2ow72wi+HdYHcSlnWFGT3P5DDTi5zi0Ukf6PGkAP9DMvnZ+gnhcDOMF9G9jvbPCOhrhcjn/65j+WUvr9JenfLC7GN51Rt07rzyJ+b3t6uodP7sBZoTz4/JZuJB5Bz19vgAdXoI+vGwPeiip+q94Vkzd40Ae+g3ehlbi736zhq+Dz/n4uvn0V9/RGbGdzz0NmAPC02R0yxU4SG/Op8V7PtP7W+QOHgwZYB7ditYe6p407T93YdlwcXrBT8Pl13X1fF8YN1+O6eJ5V2EiLuhb2FwLz39/gl4b6WyqA45sZb74Fu7DnBxHzct55VmFcYKeqd3ffvHJHp8X2iwG1/WQOGQ2w/b7xDxP4b08eOKPZnZ4tUM2tfIfuTITGKemEpmRhurdda/4vrE8K8yqnMcZxEYzRXj5Au/cgVEBOqv1Az87iFf7lqPdc/ENdFZz/nBvVGuWk3P4seHbMM/ty6O4j6sLn15Y1xs6z/nHF3Ich3ZKYsZcaj29owdHWdsB+nS5PW77nF4Q088O0u28/CVY2k5edteENcG/HzvXvfjwLvnw0xlzJLG8cIZPuq6meYY0r3nHSHsZoCfL4U793Mm+ptI/nzib+F1MmnwrjtlpjzH6dJManwaP3GdnWjhrrnqUfxke3xkCHMqek8ajySP50SY34GxuuikHvOyuhs2Xe8Rw/hCH1rb+2qvESW0=
*/