#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, char C>
        struct push_front_c;

        template <char... Cs, char C>
        struct push_front_c<string<Cs...>, C> : string<C, Cs...> {};
      }
    }
  }
}

#endif


/* push_front_c.hpp
znjTdq4Y2tVPzduudqZL6vPsGuO0Z180r2ru2ydYxqBY29NjUm3Tbd6jrNstLEzE1jGcqxZV3Pz4Hp6aU6o28Et7TSv5mI1f5yaFvgmOC3nYOZY2Vto8bTJhnP6Lcn9unm7rmpsS9uRLQj6dGV2DSkjLeIXu9JwyRHJ+dl4l9be2ze04z7QxQ/p+F9JX/zclpE9/Pr/mdix2nt0jaovQsslYOpaUkI5UQ1E6+m9nudLsKsXL
*/