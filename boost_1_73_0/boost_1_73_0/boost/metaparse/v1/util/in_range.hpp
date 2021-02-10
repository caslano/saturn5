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
2kSOlW4SsSF8h/nD+9EDqWB6NmocNSA5bmBSlYZDlRmyMLUPCunaiFihdU0Jp2doSKOzyOBJyI0JvBISkcFfKu6DNwWlM7nXBNTlh6nc7Uz8sVRXSI/89V736VaKtNpn6HbsAee92WIdz5dBz/AuF6uYm74NJ/FXcsMp18jSWafgEdGRgbioEG2nHLEamwp669VkOl/xqvwwE+NCkuSl0uquriyahTGXk8IEdwVC2EeVrH7v2JR5C3adklxjA7pAuwtQJAo+EAW4qpDaZeHBxpqaGqllKquIGRU7xtPyOWxGZAH80bXDvtMcvOcNkdPy7JuK995fVuv54s1hz2mKNZlv+a2ZOFV8pmChFQfs1ri/6fUfbL1t9STD8EqGbiv/cRW6/oemf37eP375j/4CUEsDBAoAAAAIAC1nSlI3evEW8QEAAOADAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM3NlVUBQABtkgkYM1T0W7iMBB8t5R/WKXipSI1oVxPjUKkCqqC7q4gyPU9TTbEwthRbGj5+1snQNHdD9xLEq/HM7OzTmzR2DwzmLBYqFLTa4vHD90UJmGzNF22D3h5TlnMv3Zi3oHZDYsbrOWRSkVmM1A6rzDfjv0jGr9j4OFdCMPB
*/