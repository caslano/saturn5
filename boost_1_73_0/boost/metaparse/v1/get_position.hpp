#ifndef BOOST_METAPARSE_V1_GET_POSITION_HPP
#define BOOST_METAPARSE_V1_GET_POSITION_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_position.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_position_impl;

      template <class T>
      struct get_position : get_position_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_position.hpp
2Iv+GeNtcFisDbI8G8+eIN28E/Wsf5h2yBrkW8eCfWJmB8/cWxqUc6FYbxktKVDO3mmpmRm9BwzKXz7l92L5DAvK0TctWOeCZWErsm2Fz5UwfFl2elbfoYMH5o6cnh0sJ9Mx7qCo/O4lNZxbkGA59fL3XsreN7cMcwqus81N3DqaN59vDR9aIXe5ZQ8bOig1WHWj5VcseO9P5Qq2i2ub8l6d/bF6YDvjTJyTtPyCdknejkvs
*/