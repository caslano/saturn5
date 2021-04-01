//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_REAL_CAST_HPP
#define BOOST_MATH_TOOLS_REAL_CAST_HPP

#include <boost/math/tools/config.hpp>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost{ namespace math
{
  namespace tools
  {
    template <class To, class T>
    inline BOOST_MATH_CONSTEXPR To real_cast(T t) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && BOOST_MATH_IS_FLOAT(To))
    {
       return static_cast<To>(t);
    }
  } // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_REAL_CAST_HPP




/* real_cast.hpp
a1fXI0PDP2WeEWCmy81qx4o3qeQMjWJ90X3w6gLO75+K4MsYspTQMleBXqI5mGKn4yj8am9fAvTvQs+lCo7k4hRbeneMofVYWJWhvY1N0awOfr91YMgxiUDUXmPXchrmgJjYqc6d/MF6ExS4+4LUTwP0WA4JG18Uwfo4go60h3z2j9Cq3Ct+GPKq6ufNMg836vBFKaclR7jufagOFSCJzCAZBM8D2094qBQFHq7C7wlioPc/FgYanks5vTWX39hcV0UW9emyIN7g7qvo1mghptxoayQgU4enqtN1u0iBYjWAfjC7Sd3jkuRGcYw7Ma7mH3zaA7AuzhP1vLWlBKKzgJpUCBwl1nqownG1ZJfNyYswaHZQ9F1jmv+bKwB0GcD3NCQtUlq0xeHZelUulOyuObSO8Z+WXAckAqaIxU4fivdnz6ynKD6KQ0+zIGRTMK8Q6mI3cen4xWeiHT1eKUIRjeLsS8VitEO6Nm/DdakEQQhzeXE/r/HIvm8iJ4YfGvcCI/0nq2MFqnODQqQ4HLbTXNroN3yFdEQk/cDQf3e2b9F4Bqo2ka/+0v6cmQ==
*/