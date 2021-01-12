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
sW6zpLpDScMVm2253Yraxr0d+hAuqMAUncO2dl5YE2+jMFb3JEMeT7Ge9/h7wwPiy1oZnT/ibXwUTb/Q9O/525qE6VckTR/VSckP0ywO7SFccGDhcJ7hxH2v187x/t3Li4ai4LxUv1nxvD4hXY/dfbUTmasqU8Gxmfvz9r3E7VwlbKhVO1pe8Gz7WZ+kZffNjNeJ6biddcQqtEjcrj5JwxubFx9e1zxeF3rpQbF/N+p1XMuD
*/