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
hNVtgeVL84yIzRhPg6PQpNVyMdrXsLhkMaLl4ZVSMvXDihz9lBBGw6LK2mVwipg2/iBK0My0yWt/pLHV/ty0VR/UZ6GydbpAxRmh5gJFOV00KrAKxqIUx23B74aWL8HLRiKtF7K+6oRi+RZ7BmGL7p+OZK0Q/EtbUV8H72sbZdGBw1YGAuFEG2GnBnUnVOl3KWJGs2tHIhHLVHdEUzE1gjQsYLxNtZaiNX+Ik0nzj0gGv67VKeHMTOS+hX2ukJIAHYxmTKv3WBwcaOa0mxmx2Es9YtWKfYrYa4tQDLSaOb1haX9+rGmy2tajDh3uFJTSJ+qsblAkFXv8FZ4+eP0s/rx2oHonrSoRL8eMTD9ix9480n3GQfxoubWmhgWoCoksP+4wvjIKYcUwSz4+oUbLj77dJV180Kk1/PXKlzxDj+7+EaSzdvVIFPnysfDItTPB7XPw+dGXxyc1g7hrESmDoOvRpIvNZ7EcfHVyZLTjenQc/Zr7EvxznmOxD7WPIzm4k0urTF74ldYpmLz5PHorfTQDSlwFsmQKjAbPiHUkCaMhcexX9BCU2MGN5Qj18+goR4FGTliN8aTZ2/GV98PoKDmhA568MrCf97ED3+evCduCE6MUkMzQFD/Y1Ri0qlSIbW5T4GJ+SAWImpMS7bxwFmQrE9EVDi2wmMma4/JBYZ94Q6Hc93QlzulCPYLxNT9az7WZK/AnORBujkey
*/