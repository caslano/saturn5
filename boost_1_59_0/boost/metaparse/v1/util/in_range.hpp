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
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
*/