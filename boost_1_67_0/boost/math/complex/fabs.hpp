//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_FABS_INCLUDED
#define BOOST_MATH_COMPLEX_FABS_INCLUDED

#ifndef BOOST_MATH_HYPOT_INCLUDED
#  include <boost/math/special_functions/hypot.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline T fabs(const std::complex<T>& z)
{
   return ::boost::math::hypot(z.real(), z.imag());
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_FABS_INCLUDED

/* fabs.hpp
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
*/