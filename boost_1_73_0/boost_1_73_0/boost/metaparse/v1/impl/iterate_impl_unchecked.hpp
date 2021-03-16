#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/fwd/iterate_impl.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum, class S, class Pos>
        struct iterate_impl_unchecked :
          iterate_impl<
            N - 1,
            P,
            typename boost::mpl::push_back<
              Accum,
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type
          >::template apply<
            typename get_remaining<typename P::template apply<S, Pos> >::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >
        {};
      }
    }
  }
}

#endif


/* iterate_impl_unchecked.hpp
Q5Q4hFhHoQkSzo0VQlQo9RbSRZUiNEvTZR4YfKoPlHRxEsJjIcImaj7Imgw0h3VOq4Xkrg5A++6gymLwdZVG7sJ/6QU/S10HMH/JBoOr/s0fDnd0itR2AVzXkxhwMmj4IuGQEjaRnJAYChuRmJkarFTaJO6t1XmLWMg1OxZyqVqG3qWXgVc824WYWsQF9n/m3IuTmmAfYhP2XETuGgN5s6K6FHmiJNYnWi2aQsIX8RZZE75tiIu3dcn87+xEJIk=
*/