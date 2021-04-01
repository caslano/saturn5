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
50u078IUBJJM+8TKVTf2lu/LCQK/tqhWkEKeLCupAojxvhaii/QDFvp9Ic3XAh/Dp8jjVLXUFdPilysf7pTUiqYvoAmYJ10zeP3Y8N3biNU+AZtuAUxvPPXM2xI7EQueMgacqD3ai5bQ3u2zi4c8XLM4KOsfiURdbDarEvbxT1Lmfzk1nizBkl7seyPaaOD4VEsl80tcW+zXSfRaVL8aHf9c82lB9OhluEt9BCSVuRaEsXqLjxQCZVvJqhbda5n/rghdfqWw0N9tFuseA4Ghh1W1aYtLnb8aeudbWNldUDu7ua+3DM7gCeO+GDaHCWtb1Muv4BuZfxOww1WezPd6Yeb8iMiZFxg3OxZq1VvN4cPpUJdqQkQASdOVMyUJtHCy09PXPsnd0w1MUSM0r8SMdZD27HjncC2sRdTDfDq3Xy4MyIN/7dVEtZC95r/56MUReKMpIXNdCu4Ty3J+CY2sftl0uC7+X2e/0Md9w5c+py4/yr3/cNQEc5Aa9dsYxRlHIIT4Jz2me+afGCQM4tW2VsEF79O7QrQmEYywvKnYCv4wg5k6rZCXGa7hBw==
*/