#ifndef BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP
#define BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int Len, class S>
        struct assert_string_length : S
        {
          BOOST_STATIC_ASSERT((Len <= BOOST_METAPARSE_LIMIT_STRING_SIZE));
        };
      }
    }
  }
}

#endif



/* assert_string_length.hpp
YGdAB8AaDcXLkO8BqMdpwOuAesBqwL0Q/0fAvwEdIdyL5QdgEGAUYALgXMAswDIo1xvgdkkE+Yf2mQ+4EnAaYDSgCnAQYGdAF0ABYBXQvQpYCrgXcCvgG4BZgBmASYBRgCMA/QB9AIOAL17g9k3gyllrnh2xMJa6JTCuRoB7AKAYUAeYBHqkHbi3wLhdDHgO8EvAO4COEL87b/xeGcN1XwX7pQTwQ8A1gFWAC3l2zlWgm8mjXwHu6Mlc/6PgvgzlOgAo4MULgfSHAM/y6GfEgb4DLAU61wFrAHsB3e2AewHPAX4JeBvQDuj5AMoBY+K4+a+B8kQBtuaVXw7+avBPAhwE/lmAGeC/FHA3+M8CzAf/WdD+G3j5ZIB+9oD+bQc4BPAuhF8HPAuohvAD4N4KOBn8V4I7FdxLAVcDbgHcB1gGeB3QV8Mtp/cYhux2Y5FxFhEU85C9IgbReJmAOkDGhaIYMNOd4mU3igXglnShWNydYv6zFOP9KHoMpOgHKAVUAUYBxgNqAecDZgGuASwA3AlYBFgKWA54HVAPWA3IQP0cAT0AvQElgEMAlSw/eJfqekuz/g29MiPsab7nuXTqeJf6tAMJrwKsgXQiWxuCZwG1keb9J8fGi2OTklLiYnWJKcmIjoV4Pj6Bl/xll0P33P5qfduJH77MlkfBhKF/oegnRqwTM5FMMhPLTGaSGA1y6ZgU9DcR+SWi+0QU
*/