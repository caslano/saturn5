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
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
*/