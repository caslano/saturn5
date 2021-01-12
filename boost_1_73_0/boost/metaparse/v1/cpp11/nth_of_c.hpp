#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int N, class... Ps>
      struct nth_of_c
      {
        typedef nth_of_c type;

        template <class S, class Pos>
        struct apply :
          std::conditional<
            (0 <= N && N < sizeof...(Ps)),
            impl::nth_of_c<N, S, Pos, Ps...>,
            typename fail<error::index_out_of_range<0, sizeof...(Ps) - 1, N>>
              ::template apply<S, Pos>
          >::type
        {};
      };

      template <int N>
      struct nth_of_c<N> : fail<error::index_out_of_range<0, -1, N>> {};
    }
  }
}

#endif


/* nth_of_c.hpp
lOP5DKfxWc7kc5zH57mQL/BOvsgNtKzwbNI+GdJZXjSK2h8yXXm+zDr8E4va8Qrf6y+S2/H6c/jea6zCN9iPb9L3fSc8I+TY8P2Kolf4/lshf1azJt/hAXyXbfgee3ENU/kBh/PDhPkv2sr814X5f8qa/IwHcD3b8HP24gamciOH80tuYMoOhc/d4DexYdYXzgc+zjdhvj9wb5bb0fGAHdiS5dmPO/FU7swM7sJcVuR5rMyZ
*/