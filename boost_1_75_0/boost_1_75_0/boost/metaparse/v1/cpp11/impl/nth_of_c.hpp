#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c_skip_remaining.hpp>

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_result.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class S, class Pos, class... Ps>
        struct nth_of_c;

        template <int N, class S, class Pos, class P, class... Ps>
        struct nth_of_c<N, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c<
              N - 1,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };

        template <class P, class S, class Pos, class... Ps>
        struct nth_of_c<0, S, Pos, P, Ps...>
        {
        private:
          template <class NextResult>
          struct apply_unchecked :
            nth_of_c_skip_remaining<
              typename get_result<NextResult>::type,
              typename get_remaining<NextResult>::type,
              typename get_position<NextResult>::type,
              Ps...
            >
          {};

        public:
          typedef
            typename std::conditional<
              is_error<typename P::template apply<S, Pos>>::type::value,
              typename P::template apply<S, Pos>,
              apply_unchecked<typename P::template apply<S, Pos>>
            >::type::type
            type;
        };
      }
    }
  }
}

#endif


/* nth_of_c.hpp
gPIBKZZbgkqHdiGwDtPUQbBTP5HVaTCSGRUB2x5ZmZEFqB+MFsI3jxwF6ju1JJoJQE0NnYQDDEYLEJSBnbqMPmJTi4HrjOXhpaAyowIXBh4K5G6F1RWPFqmpM4pgyfGChd9wKFMrn7eG+nGaJq12XacOVyItVgBQdGql7rr6QoZR2x6YMACoQQTEzyEbeJZpW9HsBzoNH29YHxDq7av2W0VIONorcC2cKLRmxBdkGuUhBhR2MmLhtUtkIAJyrhN/7eySbbu0A28DzPAiEtcsGPjkAvFZzB9Z4qdHfJbgR6SswhIpqzxm0OObJ8bj75Xduuuv8Lu2AX27++quGyfSeTUQo9LgjISTqz95PaUZkbGJ+flFzoNgYlTZIVqgAXLZJHw5U8ai3ZtQAczB+APlsmmphQuGOsOnw+2hxZyZ1b0lNER37Z3A/lbQLz7hkR5qjtk8q6ye+oUOJF/J9V/iuQAuyaTaFcAhOClkkZkEbf3aTh3ZvMmZacSxTXaWx4Mqu/slB2FR2S+5ikjhdu3ON1i50c0vOcH3Xn2Fj0Qg5r2UrmCZB0/LxhiW5Kp18K1eeNWv1uMvf3SZ40ZKE7e+RvvsVzpj4bT8vVsIpfPdZq4BMtiD+Nj+b3MMTUnhmSI+s/9vLFNOY1KuH4LUbZlUyBirzQfdTXeMQQewyDHHXJusnD4dNmYwepuThNf3tJd+wsDQ8mhqbuxW+a1j
*/