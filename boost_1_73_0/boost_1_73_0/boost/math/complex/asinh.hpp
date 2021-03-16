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
3V7W0lNdaRmt2D5UoxEz+2wuH3HRHhn+1rx38bdsrmuHajSGrlqh67r9qT9fNFVx/XCoRmPoqhO6rnkL7n7F5np8qEZj6KoXuq6d9bs2lCuufUM1GkOXX+i6Lr79hm6bqyhfozF0LRPO55qkuGbmazSGruVC15W8Z7rP5grkazSGrgah6/rm4+f9ZLLiiuVrNIaugNB1LdhZc5/NtS1fozF0rRDO56pQXNflazSGrpVC13Xjc+8/Z3Pdl6/RGLo=
*/