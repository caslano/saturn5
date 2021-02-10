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
vdTOvM3jy8uhZm88YAbiYtioCnOuQcvMXMSKAT4XPGFCsxRiDSnTieJzfOECTM4g4wWD8fHJ2eH0Fw8ucp7kpORK1qBzWRcp5PE5A8USxs+djipWBmSG4qg85dqgwtpwKYZom4FhqtSkg8zHhZYQn8e8iOdoKDaQG1PpHd9PalWg934qE+0nbfjD3JRdJGfoRBlfgawMGAm1Zh7QTg9KmfKM/jEhOFnV84Lr3Ft6g6ZE6ksFmhUF6UI5zrRzm0HQpMejbVChx9zQn5ZCk6mLXJa3NmIeSUtWK4GGMA+4KZWYZg9qkTJlN9vIWxNNTm2C7y3N0t8UpEBnYGMUwGGwAfNYc+3B+8Pw3fFpCO9Hs9loGp7B8QGMpmek7NfD6T6WnqMxBeyyUkyjcQW8rArO0sbm9xt+7zEXSVGnDDaMlEWkmamrYb7Rw4UsZRm8G/0+iQ6CSfhhFIaz3mOAVmBPX2n/MjZGDfM34G9CzmLKWqYwzwWfJx4IabpX2ghkEBCwGRcMToNJ1GhlBc+a6RQ78UAx9nOwH51j9RCDA3jyBNan4Q282KIxWHPLXFVMo1trC+zSNB7f44hAEPbuZqWJcmN1oWRlyub1Aqcp+M+MVa57sJuORkHY2cWY22QuDfVQpIyriosFGNtGCDFq
*/