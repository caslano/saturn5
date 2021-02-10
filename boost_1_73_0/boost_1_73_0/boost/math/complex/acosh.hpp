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
lGdCcTjvnf7ePY/Prq+6f8eXV53e8MLzoiZVDnRpQM8UFEYolwUNzKVKSDUW1qhJF/fE+sJbkt2RhLaszIxwXJcu/oLl+8Z6Fao31SIFsryh6QGmX90FF53uOTSxFpxNSGPKOkhyZqApVMP76sH6HHzA49N+OatijmKiJdgH5JJcBQhve2iYaRO0QcAJ1Gb4vr/fAGIGsDPhkjxoiuVEwjBhb0ejt8de3TyyonQ28Ec4/BDqOBvtxeIYv/5trwL9LUB/F+B4EzjeBZdt4rJdcGoTp3bBmU2c2QXnNnHumzgUNiulW6JEBlgmrOJPR8ta1WS1qJcC8ssfD3++R2Is6ZJ0vnhyiZGsQkuXIOdGEPPNYGhq7s0XGsYDVUm4X7o/B/3eVg3jV4lX5fIETFGnE1YUKHn7z+fwKYi1scBgN4ydYcpm2F6a+BUCnetE47miNWw3mJj6cODmQdQ6r9P6dTWpC/nTqTlsP/sXn1uKTTj88AF6193u2okQWbBqV8VP/QL29pZBb11/qsDeynIIVfTPQYeAW+SNxroUwnUhzCnuqFldaZg3Qc3HVnea1cbVFyiTRc7G3ImESWy9dA9gL6c7koEteCJwmpRXO6LOFk/xksGmB0F11dIdoDQiElcyKR8Qd3BQ7eYAy/Xk
*/