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
S5fJg8zUNRHzfxum92S0v/MfXJI9JNv5dSeeoZ5NdW9WtLVywoleIAau/v0UEIquAkz2dg5pWdEzl6e2xsyFJBiwpfIryLQ+ljoGL/jRq7yQ4p6TJIMCK1bI0v0aELQe7mw1pwtaF1hUUmwDb8/ZgfWyc6jYumeDw4VLK4iLlK9QmF51+4px7HXkJxbMp+66AklamflOFK5dzt0SjZ0VD31zM3w6l4nLltTW3s8oO18xlR5j/0l0DED3iEeQvh8HzfMnMXX0+YgOEjef5by2Wi+s+a+Yhb4dmUMqroI0TfyRsMS/65LC074pIrdCm6aw04Lpo4ohQZrcL/335zC5jzZUYSUHRwH/k6E/sPy5IkYPNXmJ5LNY/jbsdfX3Fm8fB3CyofP2Z75VCukKJ4lOKGEJTWXu9Xp3vRarSW1zP8TdVwC6mz+wLS+8poyQ+0ORK4kNJOoHVXONEw86QzUIiGtyjuvH+5IvASXM17f8iKylC251YdYhy1sT9UKrFhFoDn05U7RHJgNrQXcnQRlkawG56U6hxf4G+ZWpiWTYz/l05PxnRbuQ6LCidw==
*/