#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_IS_NONE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_char_except_size.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Stub = int>
        struct is_none0
        {
          template <class C>
          struct apply : boost::mpl::true_ {};
        };

        #ifdef BOOST_METAPARSE_DEFINE_IS_NONE
        #  error BOOST_METAPARSE_DEFINE_IS_NONE already defined
        #endif
        #define BOOST_METAPARSE_DEFINE_IS_NONE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class T)> \
          struct BOOST_PP_CAT(is_none, n) \
          { \
            template <class C> \
            struct apply : \
              boost::mpl::eval_if< \
                boost::mpl::bool_< \
                  C::type::value \
                  == BOOST_PP_CAT(T, BOOST_PP_DEC(n))::type::value \
                >, \
                boost::mpl::false_, \
                typename BOOST_PP_CAT(is_none, BOOST_PP_DEC(n))< \
                  BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n), T) \
                >::template apply<C> \
              > \
            {}; \
          };

        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_ONE_CHAR_EXCEPT_SIZE,
          BOOST_METAPARSE_DEFINE_IS_NONE,
          ~
        )

        #undef BOOST_METAPARSE_DEFINE_IS_NONE
      }
    }
  }
}

#endif


/* is_none.hpp
ob8kUC20dWrz/in0l22dyTZBo1w2Q/igYm4J1w2mTqe/Rj5ZwfW1PS30yoyJIlo9K2BmLBXR9/nQTlN51sd7cZCKgyn5GXb6HxK2NAhKIhq8GtBOhRZwRd/DaxZcUl/FunpcQuqU1ezCvyNfasZ2e6IHBI+4bQRXw98zivMDPunjBCQIenjwyVxYkxXbingvJxOW8nXVHtpyK7KFzKLl7GPp5EVLJ9OFAoRVf9h0O1V/ULbhPdbGXMVcMJhKhtGyBvIx8KN3IF6JEU/Lti9k265a22aMJtpmaW1byrbjtbZtZdsKrW2AbBultQ0ajB7S9lE/1TZE4g3S8EbRVrMNeU1f1TaGthe3Jo7V8LaXfdu0th1k3936qLZyiXeWhrcXbS9sRR6ptU2VfbfT+u43GHpadNlf4j2itR1A20zWd5DWViHn3VtrmyH7vqXt7WCJ97XE65VcxHsKXQiGKRdjlFxotqOJ3+gNJ+kzxDF9S6BYCt7iwIViqfrVfH4rvUK8MQKF3Ip464p4YbkW6y5yxhGmXOUFh9nwyFyrMRbKueZNFhOF9lWttY3fqfJ8vKKpblKck/XqmZydafAkv3WYyOun18VUjMhvkS+my4mDNBpk+Z0nH7LGjdaed/eWyQrToNngHn5r9h0EM/9bym+hkNl4PkuBwqjpHM1vads4E2pmEM7n1RAR3rH8Bm9mdV11Y0VtwBGwnJj3eyHPuPIgjXoBeRKHpNF6TlC0Fhikg2qeU/T+bi4Y0fNUfheH706kujR/fwa/2zPx5ZHL0vqcx+8EtE5lYbHqQzu8zS6dwmYy3aIa48L2UjBFu5/zG5qEpOeWRk3dTA9/LuW35gOLO9Z5cCW/GaeisrK6qYkj+abKxpqGZvgg9EWb76qSeEJcla/4Fb+5zRLPtB5RnqZyGrZfw+9ENiuqGanE3orm1/G7oqV5Vni1aka9nMOSga/Q7nicGkuiCwPfTn6bb0ukO0hNC/BX1YduDHWhvrK5ujmkCzqn+Yzfe3EIIhQOh9c+HLEmpdu3+nmA/q8PRwSSsVKxoABG+7nd25/9aHJyB7/NeFCNfaHkfyCspm7ew29VJ0uLQpmK+SSNwhkxKS3NM6ZGcct9Hp1EYqJ1r3bhUVwZxaP8Rl+KqhJ67cjmEVvonW15eNCwzwh3kNsK+1xXU6X28bCNF9jxyM7/SYPL20uBYSAY1OO3R4r7wYxlc1wLWR7JdS2/k0dyN4HQiNiUvdnt6QwQIxb8K7+L1yLZdCKn+jzG72Wprva2RK49CIaRI8vGs8SWOVCFG0vSzKv62xP8zgu10Gpez4T2pZPEX4tV/85vYdi5PZDLJ4vV1Ij2z2vyRLc2LniUE7RGe/4nv/EngIL6o9WOkzHbXy22E+XHj0rmtJrWa/ymnW3oHkitfRW/40vZkVB0/KWIH96i7epvsVfils1lTPEebS/RtkdMtX0p8ar6Bm1TehVnFLryHQQaa+0zsHYt1lC03GSI5A2lt24hp5ocbG7AUE3N/24LDB3RN2/o0HYu3MnNyoZYvh/h1X1iwhNbxGGm7gM2deeJohQdb6CL5/XDg314WEU9ZrmR3/aEOnyYtS/MM2sOeMt3kIkrkVPwtug1b/PL08mC53wzt53vfHM35mpaUIcLYIFa+x5hu8XvPgNke02VkwvvGdAlBAuSRDq1wxDVj5kiGZgQzQNjOaPwxWm7RjiwGBxPjIg/M+lp14H3MdeGGGq1ZwPmxqfTbF6Rhur7rjJ0gABEm3e2AUuVt2uyPXeI6YOKqbMGn2TtmxAJne21PFC08en6Cd68Yt4QZRtbezrKMYJ4Li2W1+ABrBw0ZccXABcxtxNbxDSdHSJ9UkM=
*/