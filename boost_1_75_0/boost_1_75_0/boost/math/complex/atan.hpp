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
xVPQAK5Wt6A/21+6hFzP70ETV/i68S4Xvk5wfF51gIwDXWW3tuJfXhmN2O44HfiQUzw55CIdUMzBJr+if7VpsZfnhT+FR+03oD7pWAAmHt15YX8BPZ6pYjVq4wqlYZVDUoVWjQUhNMXuDDfNAmCa4pvizgUfjVxT0ya4YkHwnbBcmCCr8iZfbtFbMFrQs7787qW04KolXCJaIzpGO0U71fXwZoISrmGu4a/hwsubJR7mxF17er83f55+RHAw4jCgM2AzYN5gMKIxGCAeEvLQbjA1MaCSNt2AIc+5t6431CFaV+8lkmIy0ccihsIfhxTVQBKZEox/Jv3LVRq3P5M+IOLvpF+Mi09vFrw5xdU0JoWZDjeGTYqux1mbhCiD1eAZVDkMs5+TmkU/j8elN1PQ3hjx9zMcifxUHg8KYmEQtJ541yKZLRH/9Vi3VOr5q+eYqc5Eom4BThtBHpWLnyeCscFxSmb6uHOrvVokBBnTpNfmG4LQ6ssNbLVXjKd3CYwKI2ag/DlbUS1B6WpwPbkGktUiVyhpuq8CGkGYocX6KXhTvsee/d19LSmtBk3/niXX5t0WlRm25o07lBhbV4ouenWQi7Q5zNod8iXlRSSNdeeHNA3GZ8TfYg2t/kigOElE4EnUaO6d8dppwXeJOjpTcihhpKt/oaAz6m/U1/IGLjl8y72BezFKvzg+Oj05kfQ+Pu/GJCRkpXikpXkg
*/