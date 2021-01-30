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
5TA5Qxr/5Eth8o5kf1cmTO6T6s+8CP6U7X8jTA5KONkdJvuk+mOvhcki2Z9Q36WyvWDfDPn6WRlSrqd2
*/