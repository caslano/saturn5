#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/int_to_digit_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class N = boost::mpl::na>
        struct int_to_digit : int_to_digit_c<N::type::value> {};

        template <>
        struct int_to_digit<boost::mpl::na>
        {
          typedef int_to_digit type;

          template <class N = boost::mpl::na>
          struct apply : int_to_digit<N> {};
        };
      }
    }
  }
}

#endif


/* int_to_digit.hpp
3nt9Wq3nixePPeY5NhS+5bd20ER8kWCx8wOs3WP/H4u+8i11jGf+4RV/d4O+Kn4HPrTg/DJx/vmn+QtQSwMECgAAAAgALWdKUrk18+8oAgAAhAUAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzc0VVQFAAG2SCRg5VRdb5swFH23xH+4ospLFeqQZJtKCVKVVG20rYkS1ncKl4BCbISddPz7XZt8adsv2F4AXx+fc+/xEaFGpdNEYcTCUuSSXltsP2STqYi9xPHSPuD5KWYhv+yEvAOzGxY2WFctlbJEJyBkWmC6nbgtKrdj4P6dD8PBABZfHTZLNAYQ77EPg3t4lQfa8Qfgj4PxfUCY5++xw9bYHLAJwPTmKbvgebJFh02l0Ci09w3FRhcBfLYlgakupQggraS6QsVtjYblp+aF3lWXjVmpaqnK7lBeViiSHU7Mwx99GT9AWiSNQj3J90K0DyBrg5wo3SRiQ/wO84ej8Sdywcxs3Dh6QHbcwLQqjYYqM2RhahcE6caIWKF1TQdOy9CIRmeTwZOQmxJ4JSQig7903AdvZpsmmu50mMrdzqCPjbpCenKv673u01cp0mqfodtpB5z3XhbreL4MekZ1uVjF3ExtFEm9khtOZw1/V53ZUoFJ
*/