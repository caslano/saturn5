#ifndef BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_UCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_ucase_letter : in_range_c<char, 'A', 'Z'>::apply<C> {};

        template <>
        struct is_ucase_letter<boost::mpl::na>
        {
          typedef is_ucase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_ucase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_ucase_letter.hpp
jkvRhMtxAa7FJfg+foHr8QpuxHu4Cd0ox2YpX1OC8m4lVpDly0ogTwa2R1m+45gTT2BxPIkl8RRKPcm7ktShg3o6S7pceA4L4EUsjqloO57LO4xYzcHx/IpMfx0r4XeYhpRZ3iuk3DJdFoL6zvotKf8d3frwl/RXCcb18SPpPPA+lseHWBV/wdr4G3bAJ9gVf8cA5BxwzDB0wWnoijMxB76POXEHvoJfYi78CvPgScyLUo/y
*/