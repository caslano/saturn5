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
eDbV+v3ASLPk31FOymXf/yjSLDdtOU2RlnilSLUZdt5aHiknq21SnCFGne91GZ950HIxzOmbsuyJkZaujeUKP/O1Djst6TMS6dvqtEDGs53vofGU37nr1FQ49aS8R77D9VvaWep6siFB6lUdP4Pxgxi2/4bmOJf5O7ZXJTrKcvCrYavID0uRphjmT7q/WpeD7SdQ/VGJSEiOM9rucQktxncIa5TS3qdSWdfvpesv8ND256v9
*/