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
HeVlL5VmafQ86B2EscQKmLEBpdR/LikcJ+OBRRAb5jhQw7ijF7lwvM7HArQkek1DkDO7Npigq7svJHSW/F8KltdlC+QJ6Ob75t+l8QGWXpHyBhR+be7Se4xptAAArADegHJBbF9SONrG86qEyY2Ifrhxc0BMbrIor6QtNGW2luyB+MuUYSWg7sBDcNTkdyCnGACDYJMMpAX4lZNJgTHk6v57rwpsNCgP1D6XWrfQ2rtXlJ8VXBOJtEhawppRhifoyrwrz1hTels9CMP7NeIh04dGwkmpyhBOA8lcMvBNhr7YJRQRSJnkItzPQ3fLT/dc1zkEf7mNX7m5S5CyprsuDgsw8iqIh2nsPZHZ5Vmv+hRUFPyt68VtYCHgdk1GucVuj+C7kUTvjt4PfNbqLlvOjimZQOwWf4ks6HY0fqZEgwPRBqpj5eLzU7E6UeXJ/edZNKEX4sxOv+hsT7FJqY0E3IDNqXf5rEgnIe9iHViVhjkPDgOBxT2xro+Y+BrfKdfHcDLarHKWFXMSG6dygF7/vc5/apyrn6jsBLnUOIG/fvlssrXCaQIG5SyQvw==
*/