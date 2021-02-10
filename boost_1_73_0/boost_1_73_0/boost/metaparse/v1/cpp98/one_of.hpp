#ifndef BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/limit_one_of_size.hpp>

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
      struct one_of :
        impl::one_of<
          boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
          >
        >
      {};
    }
  }
}

#endif


/* one_of.hpp
SCRg5VVtb9MwEP5uqf/h2LQviNTLXkXIKo0BA8FYYdmAj657Xaw6doiddtmv5xy3FDRAQuIbUlXVvrvHzz330tyj81I4HLFtKOg3hAMo42rV4BQmHfhSOfjakk1ZA/RxXsi5XWAz03aZsW2KLL2vXcb5T6ahtBVfBzqe7u6mx+nRIW8dJlpNZNvoZKl8mUx0i9IKn0hr5wqTurF3HeHmyszsiOVz7Ja2mboRe10U4/4Lzl8W8Ud0jpGO5XzjnPMYT/yusCFSiVNTZHmDte7IPBVeREieDlM42D2GCwRjPcyNXUJnW3BLN7GtkThgL4THDIoWn8DeIQHWsEcJQfo02z/ODg7g/KIYsDNrPBqfFF1Nzh7vPC99pQfsCn1y1nPMIuNI+GSJqpnaZzAWvjzhBCBkiaSD8Y3VwVUt6N0N8Ds0t77M4GhvwMYBJzltfUkWJXt+z4VTEhoUujrZqqwN9aJEtgZswIpQSNcrAb0GQOeZbSD0gDK3IMCpqtYIkVx/3/fDcDgkNaNeUbf0B+FIB3ilDD76Q/4P+AdCJWptV8DpGpnyl/P/qSz/VseVfCQmX/U5tf+ZViEotr/sD9T/sRVGLAwvua+PkBtRYawAJHEYE2E6QRmBMNO+ImFuYT10kPMYAjmNfEU+I5Zc
*/