//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ASINH_INCLUDED
#define BOOST_MATH_COMPLEX_ASINH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ASIN_INCLUDED
#  include <boost/math/complex/asin.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline std::complex<T> asinh(const std::complex<T>& x)
{
   //
   // We use asinh(z) = i asin(-i z);
   // Note that C99 defines this the other way around (which is
   // to say asin is specified in terms of asinh), this is consistent
   // with C99 though:
   //
   return ::boost::math::detail::mult_i(::boost::math::asin(::boost::math::detail::mult_minus_i(x)));
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ASINH_INCLUDED

/* asinh.hpp
UBgUPiK3CIyaVxfzVSvu+bAKL+VWvMh575OSxF5b1lbIqJu1PG+Zs4ZlOKnA1ldkaZqOupSpjwaD8Ts6xFV7sDz0Pw7nTZG8dpcXGGeQStcgafe3+Q9CGf08mDsI411cqbZIymqP6cOwyNDMmgq+dzCDerRj2GXvLSZXkkctLhtjTqmdDGHIWvpiOl06Tw8ap05wUXXo6P3OPsW+U9CxZbdXj83KxWTt+Xe7bGo4D9Bf25dB8/8OOuLICQ8I7kaGKQmlZFefhl+wfCIsMXba+jgeANy1fjnacx/VFy8a5aa5XZd1To46m8uUlScrGDcRWtLuoqLVxDlJ4YXU0U1oi35RO1auTkVMn+09vHrm72OV7nGXi57jPZhlqv93bUqxg8A84/v8uzV6Ra2Q9TkClmLYEkEDl6EEzncsp0tdMlklxEuiz+zpb5HHlkAtSSVp9FMlWyYmVB6pHLuCztOPML3gSLANbNNR44/hlVCSshWU7hARW8Z2rkUyDnXgRl0gXaGacO2XlpU2U8k6qySqls7b+8jf3uV9D0qY1jhnx1NyPOmfHiBHmVqw3g==
*/