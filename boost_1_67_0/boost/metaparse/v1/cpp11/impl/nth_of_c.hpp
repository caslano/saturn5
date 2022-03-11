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