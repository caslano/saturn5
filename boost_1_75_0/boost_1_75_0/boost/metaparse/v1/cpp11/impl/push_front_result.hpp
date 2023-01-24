#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Value>
        struct push_front_result
        {
          typedef push_front_result type;

          template <class Seq>
          struct apply :
            boost::mpl::push_front<Seq, typename get_result<Value>::type>
          {};
        };
      }
    }
  }
}

#endif

/* push_front_result.hpp
Pu2UN5nyLZAPMrqsicSXUSpKtIw9uqOYMBm1xIYeYqQlhTPe6ztiQVS6hch9BN/EJjFPPiVc4JI72C5nhD5uE67GkSAp2UUUCakvWdtYOqsxqHx2qSBa4RmmL2ZpIFLWSmy2EnAWYTTtBkqhTmk2o5fuwEqK8NmCsn8T7sFCVOqW+NnRlYaGLmsBZZeYWstxx5U7EnMtUHrWwr6hvmRU+W4EXqNiPsSVR23Kek4xCgu+4Ule6GuwTkGc8K5+vj9IqR9+Jo5lVJUo9mcvNnQkpf3RS1Gw2/uAa0C2UI5e7oQrWcFoUQGIu6Uo584DJi6fnJsOslS6bQDSDLWUPBr8WaShsKuzHLFr4Oa/E2/m8M20txweOG0mwO3HE2/3Nt4tGRhDYrQ48eb3I0k1UHc7dKqW9A8og7KldX0ibb2l2kvsIruWTF9sUu1F+KVzoFR7AQ2RBo5cwKo0djzDy5GjDqn2jVT80l+q1VLwC7yBjy4+igOU6r5OtRgDiHNLcABZw0dQx4DsVhmsTOgs9Hhqko8cAiplle4+iq8t7kRad/sArE+qFhVr6Zi1SZlZHAMKM7MEGLDi2GA46ajZmcVBZTYwa7c6g0p1FlE+TM0WVP+NXXsK3saPUDF5WE7IBt51ab+azmvDg2sK8sL9PfVupv/Z5DYYO6W+L9zXXa+NIPIlyXojkC/v0l7ArWXU2wKYj6jRW3BheGU5yasz
*/