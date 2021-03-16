#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
8kjqDcNrb8GPqWwsOq0teST1puHXSn6ulK0RrWhLHkkdQCrB87V8c9Ywol5oSx5JvYWUv8L5yeI5rNf7oi15JPW24e3hmMQNNxPVrB15JHUQKX/u0HNUGntTRrUjj6TeMfy+zizo9g5RV7Qjj6TeNfy+KvdcwmbZj7Qjj6TeE1SdAWfYytKRduSR1PuGP6+O7c5JJapJe/JI6pDh95XRK2c3Uee3J4+kPjD8WheUP92OqLL25JHUh0j5K9JFZd8=
*/