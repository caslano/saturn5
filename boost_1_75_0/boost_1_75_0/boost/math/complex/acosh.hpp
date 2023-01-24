//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ACOSH_INCLUDED
#define BOOST_MATH_COMPLEX_ACOSH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#  include <boost/math/complex/acos.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline std::complex<T> acosh(const std::complex<T>& z)
{
   //
   // We use the relation acosh(z) = +-i acos(z)
   // Choosing the sign of multiplier to give real(acosh(z)) >= 0
   // as well as compatibility with C99.
   //
   std::complex<T> result = boost::math::acos(z);
   if(!(boost::math::isnan)(result.imag()) && signbit(result.imag()))
      return detail::mult_i(result);
   return detail::mult_minus_i(result);
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ACOSH_INCLUDED

/* acosh.hpp
8yl6JekYVo8zdVuisTGaELPTMtUXii8ziTOJUGXJvAfZw5E5xhIniSyd7dLdhZBXjBYS1/vDrUApscvuuanhqQjiyeJECKlPd/lcCZrel6Lzb9i+wiULRTQ6UxEDAinM9QnpFXxu9PpWylIw79iu+FPFQU27xzeW/tGtmpUk6lslnuEcVKjQddciw1f61mdQ7hvLolMwDU//gynvoiO2/j5b5YaeYVX0wNefvdsi+VTxi5fbGXuI9LSrDMXU4QjrB4S1cJAeJ4QVkZGBKO/FbXZODvROlDsrkQYv998r+JPZOgo59MgC3hn9gKf19vysmVnc4AfJgaLbw/fP9r3mgnLest0FPLAhMAOju9Wh+SD5Md7sN+E7w9u+JmquU1IrmtCis81Ot32cwLygd9KFoHxQEYjrLQw61NaDz46yilknENPsg+X2TxhjHtFjKQnBJRBsNwVbrIFqjFcx/tW+1R9nV/Qkc7C/DRkLvMrWrceBUS9+bjs3EklV7/hhtismtWj3fXK1uI9cdPZbcq1y3M/48/eny0nVtNsNxAWCXmqaWnsegj6ZC7GjDVezOtspy3m3l9zdc0y7bYhjJUexAOrJyXJIQf60k6KtMp+t4A9fnoo9Z5rfKuYmvYyNKS4jHwUTqEvavZXTdF9f1tuyfK9WHnuo0zVWDhD9HnTsfuieus07nEof6PRG6PDQUTZ5Q0TwZcsofwiRaL11
*/