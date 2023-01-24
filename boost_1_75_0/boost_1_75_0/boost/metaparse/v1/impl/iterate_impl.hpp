#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl_unchecked.hpp>
#include <boost/metaparse/v1/return_.hpp>
#include <boost/metaparse/v1/is_error.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum>
        struct iterate_impl
        {
          typedef iterate_impl type;
          
          template <class S, class Pos>
          struct apply :
            boost::mpl::eval_if<
              typename is_error<typename P::template apply<S, Pos> >::type,
              typename P::template apply<S, Pos>,
              iterate_impl_unchecked<N, P, Accum, S, Pos>
            >
          {};
        };
        
        template <class P, class Accum>
        struct iterate_impl<0, P, Accum> : return_<Accum> {};
      }
    }
  }
}

#endif


/* iterate_impl.hpp
FJT0RyMxGsmhSHcoKDGl4wdTukcoIEhLCwMpkRjdMDqlO8bozhFjG9s+v+/f779z73nvPe95z32ee5/7nLfN40oqITDdOvbdvv0n9fgQ2vhm9nSyvfxQN5LTvJJZ0owX25ixevNHtaYqc6SCT5Wy9B/tJh895UDRh2JQp7OkXgYgsVWvceDsLKl2yEnh+Khd2fLfaUA4nHI9+4vnzaVyP/c4R4hVyN8Q/IyG/u/ecJxulx4ER56FuRaTj5ruQLT6yeyqhKeTf14o9P5xjxZj4j9uffVpzy76NbIhF0+yXRoALCbIuB49P3qE54o1JTfzjO1rufkizNd248A8OmocpPqdRh502UKzwfu9ZRXMT7TM9Qn/ORb5UBuYOwCFYQ/zCA4+xp4uZDj8rQZ5o2/eP9Nv8X/2FlbUNbzn/4LanZPAvLlB3ju8Wm8PGqHAw8jKdo3hQV5tHa1BdoPsbynOABAVsZqw9Trwi5NgCv84h/jrl9dH8uPtQGXFdgp8YLY13akKGf4k+MlFJM3LxZyQQjYB6dngs0cGTZW2cDNm02R/EpDwN5DI2Kd+2PrKNBvZ/PhZTKGHMUng7elw+InH9qWDx4GrH8c5pnrr8mDqedsRIrI07W2biedAq9XQDcMs8Kkl1VMQYEan+Gh4nwf5dro8hxprR/MZojaxo6AKc4++xyTwDGC4ecCD192fbchD+eAo9rcPeOBQfv+D
*/