//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HYPOT_INCLUDED
#define BOOST_MATH_HYPOT_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <algorithm> // for swap

#ifdef BOOST_NO_STDC_NAMESPACE
namespace std{ using ::sqrt; using ::fabs; }
#endif

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T hypot_imp(T x, T y, const Policy& pol)
{
   //
   // Normalize x and y, so that both are positive and x >= y:
   //
   using std::fabs; using std::sqrt; // ADL of std names

   x = fabs(x);
   y = fabs(y);

#ifdef BOOST_MSVC
#pragma warning(push) 
#pragma warning(disable: 4127)
#endif
   // special case, see C99 Annex F:
   if(std::numeric_limits<T>::has_infinity
      && ((x == std::numeric_limits<T>::infinity())
      || (y == std::numeric_limits<T>::infinity())))
      return policies::raise_overflow_error<T>("boost::math::hypot<%1%>(%1%,%1%)", 0, pol);
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

   if(y > x)
      (std::swap)(x, y);

   if(x * tools::epsilon<T>() >= y)
      return x;

   T rat = y / x;
   return x * sqrt(1 + rat*rat);
} // template <class T> T hypot(T x, T y)

}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   hypot(T1 x, T2 y)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::hypot_imp(
      static_cast<result_type>(x), static_cast<result_type>(y), policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   hypot(T1 x, T2 y, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::hypot_imp(
      static_cast<result_type>(x), static_cast<result_type>(y), pol);
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_HYPOT_INCLUDED




/* hypot.hpp
TAycNxpn6i+Nw3mx3RRP6ot6GloaH0SMBW8OguOMo7qJfYXuFNwiYulOBnkNBYVxhju5hqMb3M7CVgm/50fpAf1sWZJ16fI5JTwexnUwwkXcYa+efiD6frX/2uzcdZ7ytXo26zRkcBAYv6vC+V35llRA3kpR8GIRz9MmgnPSPNMcK6vTOot3Wvv8Ac5i8V6kW7MQbJH8te956rW2fB6LpjF1A5GjBf5hFct82+eW1Ao/jyC2VBe79kpW2SFDnIfK6873utFqH9StDtqvH6wJ9Lz8UlOkqRwIMz5ReXD+0wPeju9mzOFealgKW9IQSoUDGug0agy6KyAfdW67ZXqw/esXzojBvbqVQyeaTE9m2ZUotXRvx09iQMO2am0E7lWLjyvUxoEgiGkkxCSV3gZRX6ND6l9aM5X0VK2wbo1dk7A8sSdgakd/Q9J8eDT1pXi3WOmO/862pRESlhQQdjboW/Atbm5/FW3qW2kJ1+Fin2pkiV7Us0yqqz7qIy8TBT+NcYxfYorhYKd9mmcQ7OvbCi1unUm49Ri/4nEF6tje9udel9I67mHMSbfcHNVilcdZrQLFT54U0GDFnzOiGdv3rNSvvCT7GelySlUV72Fkz0CU+9jXb+do6N/ufSNhjp5iYUqXZaFJTawcO5Nzr33xvD3oGOih4U6cGHJuf4GKVQMY18AE+5Bx+bbPuKW6oOwCWOovHjX87TPP4gBc
*/