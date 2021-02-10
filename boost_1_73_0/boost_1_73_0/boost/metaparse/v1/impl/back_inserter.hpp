#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
TDy2mPw1Po+i58b4avvH0yTwLP5zSCKE1YJjfMWmebL+Hw+qS/GUe/sq95Kvx+zb7WYdjs/KfVf0lGsA76wn4RuUH9It3e+V3oeL/m1Vg3/p36Dq9Kvj+Ve7pjBObw2X1r99+dZmubJLknis02nBMwKnm2DL07SAQuWQqjTFiObxO3LQaZJBQqRBp9MiSQogsmslSfvjT1DxK0BXUZhnGZX3csdYbRMsx06DqPMwRK3jPGlYZA8wpo5kdthnXGuxR3hUEUKVai0sghqznJnATkV2Ihw9aQIsjAOnoxF5aXWg3brzWItifRCSZ8fJCc+8gFhl4Ia4WoMqGcO6IGLVHIZ7+GjvINtcHdOoEVSaEYPescNte+FYOMeN9v+u/jfyZbXW+KG6pFfNf/fa+nZK5N1r+5tvr6YrT7Q9T69/+Sf9B1BLAwQKAAAACAAtZ0pSLJvQaKICAABRBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNjNVVAUAAbZIJGDlVNtu2kAQfV/J/zCi4g1jSKpIIQa1wrRBTQoFJ1H7Ui32GK9idi3vGuK/7+ya2z+UB9i57MyZM2cJDWqTcI0TFgqZKfp5x+agqlRP2Ld4yVazeMXC4OIMgzaPfYI1VnusfC1S
*/