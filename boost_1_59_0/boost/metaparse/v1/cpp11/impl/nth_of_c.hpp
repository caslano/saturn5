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
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
*/