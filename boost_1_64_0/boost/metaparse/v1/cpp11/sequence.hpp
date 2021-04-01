#ifndef BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP11_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/push_front_result.hpp>

#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct sequence;

      template <>
      struct sequence<> : return_<boost::mpl::vector<>> {};

      template <class P, class... Ps>
      struct sequence<P, Ps...>
      {
      private:
        template <class Res>
        struct apply_unchecked :
          transform<
            sequence<Ps...>,
            impl::push_front_result<Res>
          >::template apply<
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef sequence type;

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos>>::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos>>
          >
        {};
      };
    }
  }
}

#endif

/* sequence.hpp
tEAfd2syO25XVCRAjlMDlHTKwh3CjqVJgpOMByUIVX04AKTBSdf/K5SBicv/cX8/kHM2rb5dtERutnjgnwvaEB73YpKAsPkrrbtjuuNeu8nF0mJXVEUnI9h/YC2x4K8zB0lJJXRy2gDgw1fHagte/krw6VEUbUkNELp5ma2ycWvgevS+Y3lZopqima+oqInEuMRk2C1qNGiDZKXZ7R2/tjYC/L7dKnnwivajcdEgTfZAO1a4NlElX0jCwURTRiPUIzsuZWTX/6J2CddbTAgocss3XL09M7jfKgQerjCK/2w/xfFg8/h3czEFQu7Dq1odsEKZ2z38L7URrp2L9hBEb9fL007+uUQR7XfcTSaynrXQhY4cyKxVYUJQl+vc55T4nryg8Hy850KGgOULXLbPEMfSKgZ6b/+CmdxSFxFsyLTKnsVTlGtciy+3dRhultsh7OfY5OXGNPmM3h8ogYaVtKSKsaCjEhZ6r0TXlyDfw5d1vC55MO+rWjaODTpif01PhvKpYXRcOyqXSh0d+TKfzpAT/Mq+x5LPyPKeUSO2VAkF/g7AaAp5ALGOFQ==
*/