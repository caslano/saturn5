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
E0XnINRaaTI2rX5DmP9Sz/kAOWeL/wNQSwMECgAAAAgALWdKUgIt/NC3AQAAtAIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDM1VVQFAAG2SCRgTZLRatswFIbv9RQHl9IEpnqlDEKmGErqrgbPCbUz2FVRrePYVJGMrKb1u/WuLzZZdpuBkY7k//uPzpGYxc6WvMOIsEZV2k3P2L9qI7qI3BfF1g/wKy7GoDX6rSfJbUbubpJ09xATFp4AFo4e5IycQY7miIZ2jUDCDLayHwRT4BVr2aCyk6L0CyfpPBcRpZXbDj+XrEJuXwy6NI1QpLa2dX9Pm46zqI4RSdePN2m6GuZ18Xcbr1A97vLLXXFHF95vlLHWYFlj+RyRFo0E+ju5WmTLZcrVfqhiJafg23pzG+dxARThQjQIQYYoOuDgLUHqkksMoKlgJsvZJzabsNl8PgflqBdb0UUw/3nhDnHKDUzxA469Bu0qHVsMr42twWrt7NUeXMOh1p2FQeyYcISAlfpw4EpEvh/LMHQEHQjqCDqIaPnxbiQ1H+8SOyr59AlEKjitpNZPPVXDeOkLCVu+x/Dq+/UPoG9wfr/Ji2S7PM82aZIXcbbdPBTu/F9pXTjdm7/RP2iaqgfBLQdeWVeN
*/