//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POWM1
#define BOOST_MATH_POWM1

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/assert.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline T powm1_imp(const T x, const T y, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::powm1<%1%>(%1%, %1%)";

   if (x > 0)
   {
      if ((fabs(y * (x - 1)) < 0.5) || (fabs(y) < 0.2))
      {
         // We don't have any good/quick approximation for log(x) * y
         // so just try it and see:
         T l = y * log(x);
         if (l < 0.5)
            return boost::math::expm1(l);
         if (l > boost::math::tools::log_max_value<T>())
            return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
         // fall through....
      }
   }
   else
   {
      // y had better be an integer:
      if (boost::math::trunc(y) != y)
         return boost::math::policies::raise_domain_error<T>(function, "For non-integral exponent, expected base > 0 but got %1%", x, pol);
      if (boost::math::trunc(y / 2) == y / 2)
         return powm1_imp(T(-x), y, pol);
   }
   return pow(x, y) - 1;
}

} // detail

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), pol);
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_POWM1






/* powm1.hpp
rn/3vBOMe4333XWGl+VwHfvonjJq8twrfgWSjV4ZU3u22zA6f+6wEpEfOerj7qgWuW6EfXc4eclSd7K8rZrDy/FwDR55fVHjYrmIu67EtsNlvQ6zcDkID+Gi8yB7znkpSr3+hWfRcOYuNW8XTsZB1OO7chqwbn/Ag3Axky+L/mT32O2yPL5W5+HwZlyuatZ5jwrlcSmf35/yp4a9+I9cidcnr8pns+5ky57wrHt4eTsog0shpUr6clkXvWnTiN1jL5mn006lbI5ZvmbB7nWeDR7758ur/5QPbg+DRLv1Fozb04mciVXRNI9yGfYGt+VbaF/0hKV+zZ6OHTd5X+D/O6+r0+xluNDFkzF+Kx/K4WPTfW2Wp0yfL2aPg+t1JL+dX4cj1zvOx9sJk5X+U3U8noedwL/ueoXLn+L1ShxHZTKbPa8umrzvGweWBzZj/iZf5k2+fG26OWZrLI5tZjbusjeIfWvTWc6vZayEIvPzxmnaC0NMi8vylzKwA59Jr2l/NAoCVvqOc/IxjV27wRNbbM86bj6a2/ZoJXblo/tgl8aDXawm7vQQ4wbVdw79Dcuo+p4mgee7bJ7bo8mtOgzG+WSfLstTR2fa63bQTFbRynjffCvVp3HgsQ1j97qRioiN7HDxEo3VzazXOZaT
*/