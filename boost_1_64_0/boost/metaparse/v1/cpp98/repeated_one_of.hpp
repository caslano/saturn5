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
jEn6oeKeMthV7f2C2HTry4SwqWjbgfOJ9e/M3dq0UfoevcwOt+xjfrDyqBOL9mSycfghSQHy+BfoNSon2EsSIacn00AB7BqAFPnVRP6ZZ0yIKOWsCLZp7RlBgTLZ/7v+Z+vnitgEHgChtsQ5rJLMz+kbNjaxs2gFr0nHmOEyEpO2vu4M5k0NClVN+WAY/YTPRRbrecmrV3ZHIVtYACBSPy7UNAaO0k7NiglpuP/8whxL9tI4p3kCJHOjO0xgAZkNvx+X6EVQAtA5oQ7C1KB8LAbEpXG1EWTChUVC3aHb2TRX4xOxRwg4t97f9aet8XLlW7N9K5IP30/Kp7sfd09NEbC5GYBZIBUfv5baHbT48Bm4k6QyFGWedB7qtiqjgRiliItWC5ppCTQ8eHteTp/eH5/wnqPWN9T3673PhL7F0loRqDOaiDA2/qipeUIzDXj696sht+aN2IRv7YOnPDTJuGgo89cGAyQwWtYHrW5PhykEJDjew0nIuc3t4QaylHCM1BJBZrDl5ILe8XLFt8n1vN81S93/F9MykaWXG5tZnIwKQSSjS0Gd+fLxwQ==
*/