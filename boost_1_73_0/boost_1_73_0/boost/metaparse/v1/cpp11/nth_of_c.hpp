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
Ai4UWehh1Xir/zwcj/uP9/d/vFLbK7W9Utv+ldr4mBdNbQ/HP+//Ou4/3d/ePR0f9v0/9p9uvny8v3m/90jXxEeXjuSXKdNIgEKbBq5xRIQTYQYyrE8mQyLCOn9MIMHsXQIBsusD+QksBNLLLglk1wSSDgxWpYcFymKgCkSVsXKgJzHnQEoAQYGJACqIfoTqE+d0tDiBaEz+iEAwrbqkzgiJ+ES8W+ARJo+GG7BX/iiNeOWPwjDIH27mDy8uzB90+cghSitGHgFqEbikz5Ut8EmmkIFTOG8M7cHK+zupdcQvOX88g7NFnKMuD7zTJQwG7uF048We002r6aZRdEMcBJwTYqECTgIPAR8jMFFfYKLERUBagY2EtAIfqTcNjJSzlrFchIGVJooKnCSof5mTiI+UCgQ2EiILXJTdJ7DQaA8CtUSnPVCJme9tcrNCTNGklw3EwGQZeEDwaYB9rr5OSreFtsSLXOkRknhAaK8AOjAD3/clgEZ4dvKVK6uFGKCZCXHIhTBYZvcDKGs+uGTsCYZsvQP85tuY0Q0gVE32uk+LHnciPyiWEpoApROiSvetwc6CkAV9i4Au5Vs0WqxNJZy5gDRAgFZycEKcuB/0AhLywJYyoE+7Bz1DKeEwE2BtFEkTJgEOjKRewqcS
*/