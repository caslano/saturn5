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
gnk2TqLGT18XRNCeplfWYv+UqmzSlfhdr0lfMXPaykPlOUydvTiv7yvfKUlk8k31MvUaNQW15WF9F918HvqJx0ZfJt4H4nEfVrL3RuHxdbi/TZwryFdd4ku+IfJFKWIGv0Gd75U+o+Mul+/A0w35iY+hnNZGs0jSp+iz2ZCf1b/QZbD7TmMp5xcG8CSXwrP3UFcXkHSZDYb3ZTdeZK+398JijtkRUq4dnDHOs1T2Rmcf2ZFD
*/