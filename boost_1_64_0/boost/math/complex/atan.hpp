//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ATAN_INCLUDED
#define BOOST_MATH_COMPLEX_ATAN_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#  include <boost/math/complex/atanh.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
std::complex<T> atan(const std::complex<T>& x)
{
   //
   // We're using the C99 definition here; atan(z) = -i atanh(iz):
   //
   if(x.real() == 0)
   {
      if(x.imag() == 1)
         return std::complex<T>(0, std::numeric_limits<T>::has_infinity ? std::numeric_limits<T>::infinity() : static_cast<T>(HUGE_VAL));
      if(x.imag() == -1)
         return std::complex<T>(0, std::numeric_limits<T>::has_infinity ? -std::numeric_limits<T>::infinity() : -static_cast<T>(HUGE_VAL));
   }
   return ::boost::math::detail::mult_minus_i(::boost::math::atanh(::boost::math::detail::mult_i(x)));
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ATAN_INCLUDED

/* atan.hpp
lC7QkSHWAQkBpqjn8Nw3oOLjPFdr1AQCeWGpjiML9wByPWSyP5KMlG7dyWyG917DKlTNIAEiI1H9i0cga+y3BjHsaM2m7SNuHkSJG1uUZWKaC8b41jy2ZTMwEiGzKtknohFLDnDEc6hGX2FdkOpd/HvenT1IQVVK7RK/y97LHB56wXe8/CcLsZ3va6Sd9LAN3tFMxvVQ8RE5k2jP3waqtSDeLCyQuBTCFOmgrxZTqJMv7qfWsBrfzrIaJ10uI5Fx3epXNBT6Bp/e9kZS3DBbsS7L5U9gRvjSKZHVtGkzYxnZBD/jMw7wAdqJVq2LBLwg79BTbrqGUwGDjP7KS/N0ZgbiNyofCBlMSEH/KdoUxhRjzYF3gnDuG/2jyPMhjdz9kwOu1Z1FiSiNsKE5IuKvbmpTDtmnRC0aKXK7ADL696mM81EGXLoExYQrdM+wkmDfM1cUB9NX8or7VTZwlSlk7QbEYfn4dLVouIWWF3x9KU0rzBT1HnrUGmuI+cEPaRcevCmNeodeIJxKxbkjUkMbYLpYzaJPeh6M1dhjo1iQ8p3EO8CdNj5OQfDGeA==
*/