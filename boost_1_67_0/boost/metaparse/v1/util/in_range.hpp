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