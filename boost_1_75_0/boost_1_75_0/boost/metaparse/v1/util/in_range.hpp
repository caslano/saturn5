#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <
          class LowerBound = boost::mpl::na,
          class UpperBound = boost::mpl::na,
          class Item = boost::mpl::na
        >
        struct in_range :
          boost::mpl::bool_<
            boost::mpl::less_equal<LowerBound, Item>::type::value
            && boost::mpl::less_equal<Item, UpperBound>::type::value
          >
        {};

        template <class LowerBound, class UpperBound>
        struct in_range<LowerBound, UpperBound, boost::mpl::na>
        {
          typedef in_range type;

          template <class Item = boost::mpl::na>
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };

        template <class LowerBound>
        struct in_range<LowerBound, boost::mpl::na, boost::mpl::na>
        {
          typedef in_range type;

          template <
            class UpperBound = boost::mpl::na,
            class Item = boost::mpl::na
          >
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };

        template <>
        struct in_range<boost::mpl::na, boost::mpl::na, boost::mpl::na>
        {
          typedef in_range type;

          template <
            class LowerBound = boost::mpl::na,
            class UpperBound = boost::mpl::na,
            class Item = boost::mpl::na
          >
          struct apply : in_range<LowerBound, UpperBound, Item> {};
        };
      }
    }
  }
}

#endif


/* in_range.hpp
hqf+oFKJr1YGLl+t5CqMCIHJ9DdjLfQ3qYf+OuwTmCi5etpYZIjXwajROSBei7Fx6SzWMD/g5jEKMSIyRkW8yA5BB7M0Sj1v1NXYMXXD3/jsjdItFbnJHt5M5jmBKppzPyoF2PT0I4W0goO6+tJIwYfzxX7qzyCFoM700+eqGlmUx/4anun29v7Wv3mtWB+UTunoaupOJwwGhTxTMGAfEZ0IlajVzPxvT5KMVrq98683yQpaEnycUtKywtI0X4YN5DYBc9xOnsxWUULBb8qkq0DIlTNN26pOyRxOlb6LWR7dPkKeoz1MWYKgIenT3zLun9+URYm3AXwXEdMt1oxNz5/5Rc8Xr6EZqzNVIP5HSPxkqiOnWZafzepJ+geN/noHFcyoVZkFaspucQ7I4baLjS3EePAKQhQgwtcBpzc2chmA+OZkDEqjE/TnPM3s1AEXDxyDHgHpg2WhxQSjHEjoF5R5M0GQYHuFR67qD+0QuLT4mr89c1NED9PgIa5o0FlpJZJIDg9zoHrir6z0cfqdHV+D9v3g9Ku/nq4TSDgocvLNKzzbc+M632lEamcA0McBedLRQEsQVMJSXSNXN2Yvqvr7ArNYb9yGgej2QJdh861OTIAb+A+z33V8F6k0aYR/zRlBIgh9QyTnwOBe919gD1/s+PlsLrWXI6TxoaI5iBHrZmhoi0eOleJQP9uu6KHA6yuencK2YPbz+xDQ
*/