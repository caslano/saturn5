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
Gr9kuyWvXPZw78jZwmJ79o/Onv3BsdUatS5SXfeTjbuKG5uNo7HZDYETgSnArYEZwGygHbgNcBfgtkAncDvt3Cuqc1QX/bpzr8bS2G0qcCxwAnACMA24EzCdwt0stsd+bI/92B77pvbYX4Rx3+Wxsd+Yi7mYi7mYi7m/xSWCWtf59//s5jnYxXVwBGB4YwDqWv9OttZ/MNzgWv9Mur+M3W8YekDnAzRkK0Prn+MM1q8PjhtMrZxevf8+Ftd3r2o1Xm+90iC+rsH4ygYjtLbe+sdW43MCshNpzgkoDnQ4nRPgncLim90qXguk7Wl9FuOrV2bg92CQcC7yFH5NkHx+PfGaWhPknWJ+TZB3irU1Qd4p5tcEaWFjvc3zUKIT33WN2UjjBhtp88bvoLU2E4mnAzxN4EnY0TbNlm2rwsKc9RNsk4OQpI7F9CHvesifGs5tJsaR/s61OXzZylpvaG1gHGgSrU3BtxmVLeG6FG29w9OMz6HYxeUK4Zifx6/x8ro1cSanlbn8qtx+qrw1VH8PVPf5V+uUhbUp8GO4v/84PN+RPbeLZIZfa2tVUqaYX6vC866Pm5gNiOIzlHfp7LkL6UD8tL7sPej83bQg/n1rStQ88m2gne/NXCqtKfGqZdPCehKvhXJIvEPtwgivJ1Hlq9pQm/vIXB6tJ3E6ST4La0mcTvNrSZxO82tJnE5ra0mcTvNrScAbUt8DEzFfemzkPnM015Koe9q32YbG9uNAu1AfrGh5Na+pYf6xTdQVG+9twPh3EOUhwjLfBytO832w4jTfBytOa32w4jTfB4NX64NdKPtPbYR3GV0ffGN6aF86J/uf35eqZaQmWdxe+fbUlRE0W2bPxfFZaLeIl9PlyLZb/5XzDF5gtqTz/T+UXuF9ZOOnxzWeOnCFfQTPf/6/2YxGyjb0M1s3MOgaufMMDqf/VaAm+r8/SFvH5DReB7Q72XqK+XVMEv49iH8K8bep3w7AOYL1L/PJVtUBnAA8Cbgj8GTgXsBTgPvQepxqul9L9+vovgd4GvBwutbWS+xJ61cE6yXcFO/+QBvwQOAmwBrgZsCDgVsADwFuA6wFbkv3d6b7k+g+yUnviwhDIKeH9NIAZPcpvmPIhjYHmA48kmxnLcA84FHAAmArcE9gG/BA8qeu0/CSnBME6zSmUrxlFG85MBU4Q9vXH0T5mS/Y17+T/F8ATANeQum8iNKHawoHjsJxCMJZQPo+C7gR8GyS+xySdyEnj08iz96UniqSZx+SZ19gVzzKZwH2eS+InTEQO2Ng3Z8xUIty1g7qAi0F+UGrQAOgpEkog5Ni9ryYi7mYi7mYi7mYi7mYi7l/shud+f/1LXOOPnbY+/9vAdv3FulIM7N9s+nxpVXTZ+6HYdJj6trblYl43p+Gb33d81mwkDcdBQ6aC9DMrSGYa2CbV0poDr4WSET7/F68fb423D6vxdlN8/6LKN5C0FebYzxFH2ddw1FttG5h13EKs8mPo7NoMxlvLvYGjBfbGNnzOM7vbM2ON4E9y1e2Fp/rD7/6PeuOPU7h1htszZ5vpK03qGDXCZpdJh/x7TIusj1QXRuB9GHso55dJ2nXs0N0VpKgnU3NXPBmAew/njCdNc5XdbYbrfUQ6Af+Qse+Dxwf2Y6kpnc3wVqOdwXp2xMXXn36mH2cT1+92P6oS9/hJuxcoemrD0mfl+z2xeRhMsiXAwpL35ymdsegraFxW2ZrqEe91WzTSxh/iijNCCvMNt1GtlvN/3LGkym2R3Dl7toc5p8ZGFS/L7LnySKbFe+Xyjtrc7S9p5ey57uKbFjwa20vz6BeJpBe0qjMkq2a5B2yHUEO3GdykO2Iyjelj8+jH9c=
*/