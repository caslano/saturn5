#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class T, T LowerBound, T UpperBound>
        struct in_range_c
        {
          typedef in_range_c type;
        
          template <class Item>
          struct apply :
            boost::mpl::bool_<(
              LowerBound <= Item::type::value
              && Item::type::value <= UpperBound
            )>
          {};
        };
      }
    }
  }
}

#endif


/* in_range_c.hpp
ykAe8bn4ayBrhvixIA3b/OKvgbRNQpjl5ubv2rTvlY2/N790S13GkJ5p73Wkn813hdTfQgZ8k0OtLezQ1x2QNEWCUxg+JQtGSpR/5dhfpQwQRPASkyJG/8P9zyHB7Zgb9BMcFVIZ38Q9FPa3MX5ch6w7rUNpVHar7+zo8PuieH/YH+lqp8M2ZfiPbsLmxPD8TEvmUXawN4kzOtojTPxQhZnpwINEEOIoBBUQDwqAVv6PZLZUu9RTuti/ufsS+Co=
*/