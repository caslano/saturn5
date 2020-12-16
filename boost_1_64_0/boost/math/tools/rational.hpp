//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_RATIONAL_HPP
#define BOOST_MATH_TOOLS_RATIONAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/array.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/mpl/int.hpp>

#if BOOST_MATH_POLY_METHOD == 1
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/polynomial_horner1_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#elif BOOST_MATH_POLY_METHOD == 2
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/polynomial_horner2_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#elif BOOST_MATH_POLY_METHOD == 3
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/polynomial_horner3_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#endif
#if BOOST_MATH_RATIONAL_METHOD == 1
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/rational_horner1_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#elif BOOST_MATH_RATIONAL_METHOD == 2
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/rational_horner2_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#elif BOOST_MATH_RATIONAL_METHOD == 3
#  define BOOST_HEADER() <BOOST_JOIN(boost/math/tools/detail/rational_horner3_, BOOST_MATH_MAX_POLY_ORDER).hpp>
#  include BOOST_HEADER()
#  undef BOOST_HEADER
#endif

#if 0
//
// This just allows dependency trackers to find the headers
// used in the above PP-magic.
//
#include <boost/math/tools/detail/polynomial_horner1_2.hpp>
#include <boost/math/tools/detail/polynomial_horner1_3.hpp>
#include <boost/math/tools/detail/polynomial_horner1_4.hpp>
#include <boost/math/tools/detail/polynomial_horner1_5.hpp>
#include <boost/math/tools/detail/polynomial_horner1_6.hpp>
#include <boost/math/tools/detail/polynomial_horner1_7.hpp>
#include <boost/math/tools/detail/polynomial_horner1_8.hpp>
#include <boost/math/tools/detail/polynomial_horner1_9.hpp>
#include <boost/math/tools/detail/polynomial_horner1_10.hpp>
#include <boost/math/tools/detail/polynomial_horner1_11.hpp>
#include <boost/math/tools/detail/polynomial_horner1_12.hpp>
#include <boost/math/tools/detail/polynomial_horner1_13.hpp>
#include <boost/math/tools/detail/polynomial_horner1_14.hpp>
#include <boost/math/tools/detail/polynomial_horner1_15.hpp>
#include <boost/math/tools/detail/polynomial_horner1_16.hpp>
#include <boost/math/tools/detail/polynomial_horner1_17.hpp>
#include <boost/math/tools/detail/polynomial_horner1_18.hpp>
#include <boost/math/tools/detail/polynomial_horner1_19.hpp>
#include <boost/math/tools/detail/polynomial_horner1_20.hpp>
#include <boost/math/tools/detail/polynomial_horner2_2.hpp>
#include <boost/math/tools/detail/polynomial_horner2_3.hpp>
#include <boost/math/tools/detail/polynomial_horner2_4.hpp>
#include <boost/math/tools/detail/polynomial_horner2_5.hpp>
#include <boost/math/tools/detail/polynomial_horner2_6.hpp>
#include <boost/math/tools/detail/polynomial_horner2_7.hpp>
#include <boost/math/tools/detail/polynomial_horner2_8.hpp>
#include <boost/math/tools/detail/polynomial_horner2_9.hpp>
#include <boost/math/tools/detail/polynomial_horner2_10.hpp>
#include <boost/math/tools/detail/polynomial_horner2_11.hpp>
#include <boost/math/tools/detail/polynomial_horner2_12.hpp>
#include <boost/math/tools/detail/polynomial_horner2_13.hpp>
#include <boost/math/tools/detail/polynomial_horner2_14.hpp>
#include <boost/math/tools/detail/polynomial_horner2_15.hpp>
#include <boost/math/tools/detail/polynomial_horner2_16.hpp>
#include <boost/math/tools/detail/polynomial_horner2_17.hpp>
#include <boost/math/tools/detail/polynomial_horner2_18.hpp>
#include <boost/math/tools/detail/polynomial_horner2_19.hpp>
#include <boost/math/tools/detail/polynomial_horner2_20.hpp>
#include <boost/math/tools/detail/polynomial_horner3_2.hpp>
#include <boost/math/tools/detail/polynomial_horner3_3.hpp>
#include <boost/math/tools/detail/polynomial_horner3_4.hpp>
#include <boost/math/tools/detail/polynomial_horner3_5.hpp>
#include <boost/math/tools/detail/polynomial_horner3_6.hpp>
#include <boost/math/tools/detail/polynomial_horner3_7.hpp>
#include <boost/math/tools/detail/polynomial_horner3_8.hpp>
#include <boost/math/tools/detail/polynomial_horner3_9.hpp>
#include <boost/math/tools/detail/polynomial_horner3_10.hpp>
#include <boost/math/tools/detail/polynomial_horner3_11.hpp>
#include <boost/math/tools/detail/polynomial_horner3_12.hpp>
#include <boost/math/tools/detail/polynomial_horner3_13.hpp>
#include <boost/math/tools/detail/polynomial_horner3_14.hpp>
#include <boost/math/tools/detail/polynomial_horner3_15.hpp>
#include <boost/math/tools/detail/polynomial_horner3_16.hpp>
#include <boost/math/tools/detail/polynomial_horner3_17.hpp>
#include <boost/math/tools/detail/polynomial_horner3_18.hpp>
#include <boost/math/tools/detail/polynomial_horner3_19.hpp>
#include <boost/math/tools/detail/polynomial_horner3_20.hpp>
#include <boost/math/tools/detail/rational_horner1_2.hpp>
#include <boost/math/tools/detail/rational_horner1_3.hpp>
#include <boost/math/tools/detail/rational_horner1_4.hpp>
#include <boost/math/tools/detail/rational_horner1_5.hpp>
#include <boost/math/tools/detail/rational_horner1_6.hpp>
#include <boost/math/tools/detail/rational_horner1_7.hpp>
#include <boost/math/tools/detail/rational_horner1_8.hpp>
#include <boost/math/tools/detail/rational_horner1_9.hpp>
#include <boost/math/tools/detail/rational_horner1_10.hpp>
#include <boost/math/tools/detail/rational_horner1_11.hpp>
#include <boost/math/tools/detail/rational_horner1_12.hpp>
#include <boost/math/tools/detail/rational_horner1_13.hpp>
#include <boost/math/tools/detail/rational_horner1_14.hpp>
#include <boost/math/tools/detail/rational_horner1_15.hpp>
#include <boost/math/tools/detail/rational_horner1_16.hpp>
#include <boost/math/tools/detail/rational_horner1_17.hpp>
#include <boost/math/tools/detail/rational_horner1_18.hpp>
#include <boost/math/tools/detail/rational_horner1_19.hpp>
#include <boost/math/tools/detail/rational_horner1_20.hpp>
#include <boost/math/tools/detail/rational_horner2_2.hpp>
#include <boost/math/tools/detail/rational_horner2_3.hpp>
#include <boost/math/tools/detail/rational_horner2_4.hpp>
#include <boost/math/tools/detail/rational_horner2_5.hpp>
#include <boost/math/tools/detail/rational_horner2_6.hpp>
#include <boost/math/tools/detail/rational_horner2_7.hpp>
#include <boost/math/tools/detail/rational_horner2_8.hpp>
#include <boost/math/tools/detail/rational_horner2_9.hpp>
#include <boost/math/tools/detail/rational_horner2_10.hpp>
#include <boost/math/tools/detail/rational_horner2_11.hpp>
#include <boost/math/tools/detail/rational_horner2_12.hpp>
#include <boost/math/tools/detail/rational_horner2_13.hpp>
#include <boost/math/tools/detail/rational_horner2_14.hpp>
#include <boost/math/tools/detail/rational_horner2_15.hpp>
#include <boost/math/tools/detail/rational_horner2_16.hpp>
#include <boost/math/tools/detail/rational_horner2_17.hpp>
#include <boost/math/tools/detail/rational_horner2_18.hpp>
#include <boost/math/tools/detail/rational_horner2_19.hpp>
#include <boost/math/tools/detail/rational_horner2_20.hpp>
#include <boost/math/tools/detail/rational_horner3_2.hpp>
#include <boost/math/tools/detail/rational_horner3_3.hpp>
#include <boost/math/tools/detail/rational_horner3_4.hpp>
#include <boost/math/tools/detail/rational_horner3_5.hpp>
#include <boost/math/tools/detail/rational_horner3_6.hpp>
#include <boost/math/tools/detail/rational_horner3_7.hpp>
#include <boost/math/tools/detail/rational_horner3_8.hpp>
#include <boost/math/tools/detail/rational_horner3_9.hpp>
#include <boost/math/tools/detail/rational_horner3_10.hpp>
#include <boost/math/tools/detail/rational_horner3_11.hpp>
#include <boost/math/tools/detail/rational_horner3_12.hpp>
#include <boost/math/tools/detail/rational_horner3_13.hpp>
#include <boost/math/tools/detail/rational_horner3_14.hpp>
#include <boost/math/tools/detail/rational_horner3_15.hpp>
#include <boost/math/tools/detail/rational_horner3_16.hpp>
#include <boost/math/tools/detail/rational_horner3_17.hpp>
#include <boost/math/tools/detail/rational_horner3_18.hpp>
#include <boost/math/tools/detail/rational_horner3_19.hpp>
#include <boost/math/tools/detail/rational_horner3_20.hpp>
#endif

namespace boost{ namespace math{ namespace tools{

//
// Forward declaration to keep two phase lookup happy:
//
template <class T, class U>
U evaluate_polynomial(const T* poly, U const& z, std::size_t count) BOOST_MATH_NOEXCEPT(U);

namespace detail{

template <class T, class V, class Tag>
inline V evaluate_polynomial_c_imp(const T* a, const V& val, const Tag*) BOOST_MATH_NOEXCEPT(V)
{
   return evaluate_polynomial(a, val, Tag::value);
}

} // namespace detail

//
// Polynomial evaluation with runtime size.
// This requires a for-loop which may be more expensive than
// the loop expanded versions above:
//
template <class T, class U>
inline U evaluate_polynomial(const T* poly, U const& z, std::size_t count) BOOST_MATH_NOEXCEPT(U)
{
   BOOST_ASSERT(count > 0);
   U sum = static_cast<U>(poly[count - 1]);
   for(int i = static_cast<int>(count) - 2; i >= 0; --i)
   {
      sum *= z;
      sum += static_cast<U>(poly[i]);
   }
   return sum;
}
//
// Compile time sized polynomials, just inline forwarders to the
// implementations above:
//
template <std::size_t N, class T, class V>
inline V evaluate_polynomial(const T(&a)[N], const V& val) BOOST_MATH_NOEXCEPT(V)
{
   typedef boost::integral_constant<int, N> tag_type;
   return detail::evaluate_polynomial_c_imp(static_cast<const T*>(a), val, static_cast<tag_type const*>(0));
}

template <std::size_t N, class T, class V>
inline V evaluate_polynomial(const boost::array<T,N>& a, const V& val) BOOST_MATH_NOEXCEPT(V)
{
   typedef boost::integral_constant<int, N> tag_type;
   return detail::evaluate_polynomial_c_imp(static_cast<const T*>(a.data()), val, static_cast<tag_type const*>(0));
}
//
// Even polynomials are trivial: just square the argument!
//
template <class T, class U>
inline U evaluate_even_polynomial(const T* poly, U z, std::size_t count) BOOST_MATH_NOEXCEPT(U)
{
   return evaluate_polynomial(poly, U(z*z), count);
}

template <std::size_t N, class T, class V>
inline V evaluate_even_polynomial(const T(&a)[N], const V& z) BOOST_MATH_NOEXCEPT(V)
{
   return evaluate_polynomial(a, V(z*z));
}

template <std::size_t N, class T, class V>
inline V evaluate_even_polynomial(const boost::array<T,N>& a, const V& z) BOOST_MATH_NOEXCEPT(V)
{
   return evaluate_polynomial(a, V(z*z));
}
//
// Odd polynomials come next:
//
template <class T, class U>
inline U evaluate_odd_polynomial(const T* poly, U z, std::size_t count) BOOST_MATH_NOEXCEPT(U)
{
   return poly[0] + z * evaluate_polynomial(poly+1, U(z*z), count-1);
}

template <std::size_t N, class T, class V>
inline V evaluate_odd_polynomial(const T(&a)[N], const V& z) BOOST_MATH_NOEXCEPT(V)
{
   typedef boost::integral_constant<int, N-1> tag_type;
   return a[0] + z * detail::evaluate_polynomial_c_imp(static_cast<const T*>(a) + 1, V(z*z), static_cast<tag_type const*>(0));
}

template <std::size_t N, class T, class V>
inline V evaluate_odd_polynomial(const boost::array<T,N>& a, const V& z) BOOST_MATH_NOEXCEPT(V)
{
   typedef boost::integral_constant<int, N-1> tag_type;
   return a[0] + z * detail::evaluate_polynomial_c_imp(static_cast<const T*>(a.data()) + 1, V(z*z), static_cast<tag_type const*>(0));
}

template <class T, class U, class V>
V evaluate_rational(const T* num, const U* denom, const V& z_, std::size_t count) BOOST_MATH_NOEXCEPT(V);

namespace detail{

template <class T, class U, class V, class Tag>
inline V evaluate_rational_c_imp(const T* num, const U* denom, const V& z, const Tag*) BOOST_MATH_NOEXCEPT(V)
{
   return boost::math::tools::evaluate_rational(num, denom, z, Tag::value);
}

}
//
// Rational functions: numerator and denominator must be
// equal in size.  These always have a for-loop and so may be less
// efficient than evaluating a pair of polynomials. However, there
// are some tricks we can use to prevent overflow that might otherwise
// occur in polynomial evaluation, if z is large.  This is important
// in our Lanczos code for example.
//
template <class T, class U, class V>
V evaluate_rational(const T* num, const U* denom, const V& z_, std::size_t count) BOOST_MATH_NOEXCEPT(V)
{
   V z(z_);
   V s1, s2;
   if(z <= 1)
   {
      s1 = static_cast<V>(num[count-1]);
      s2 = static_cast<V>(denom[count-1]);
      for(int i = (int)count - 2; i >= 0; --i)
      {
         s1 *= z;
         s2 *= z;
         s1 += num[i];
         s2 += denom[i];
      }
   }
   else
   {
      z = 1 / z;
      s1 = static_cast<V>(num[0]);
      s2 = static_cast<V>(denom[0]);
      for(unsigned i = 1; i < count; ++i)
      {
         s1 *= z;
         s2 *= z;
         s1 += num[i];
         s2 += denom[i];
      }
   }
   return s1 / s2;
}

template <std::size_t N, class T, class U, class V>
inline V evaluate_rational(const T(&a)[N], const U(&b)[N], const V& z) BOOST_MATH_NOEXCEPT(V)
{
   return detail::evaluate_rational_c_imp(a, b, z, static_cast<const boost::integral_constant<int, N>*>(0));
}

template <std::size_t N, class T, class U, class V>
inline V evaluate_rational(const boost::array<T,N>& a, const boost::array<U,N>& b, const V& z) BOOST_MATH_NOEXCEPT(V)
{
   return detail::evaluate_rational_c_imp(a.data(), b.data(), z, static_cast<boost::integral_constant<int, N>*>(0));
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_RATIONAL_HPP





/* rational.hpp
H/pdrz4TVE8n9R7wZpD1Rf1dseF7W4xRpejfgHJ9lb8HhjzpNZLh/ybxq+/Irfl1PV8kuiKZWCMPB/pAjSOaDusrDhk+bVmHYRT9xv4A8qJSR4eupg5fCnX4Dk1RrxWo3v+8yXxXd3PZOej2CUNTh2Am86sLlt8dwqz1eycgg1qMSXdiq6Erd7YUL3gbfUfZWLHWGd92wjjp0ztaC6N7vzVXPn0noHXrzPjamLyK6J06tezhPzXOVRmyh1P2GCqFjJJYvT4SVKv8HlmIePPeMgkLWXuxaA5VCV5WUZWF10O0jvxaxQzV59pYVjq4NvQ1otsH3+TnQr0PpXNtBTQH27tQT2/WMhZOLC+/yJRv0rHJh1/Uh3XlDPQrrx/D0KD+Bkb3he3Z9x+PUx87/sLZk7C4HFTt2f5p5+5gVaZBoEKqX+H/HH8zZ067vqYyXybyiuMLqEzae8A/seVFmQjKXEZpJsXTV09A00CrDC/LQuXC3/SlGrNTHXtP1m8XWht7PbexU46N7YHN0Tb15ItUnSv1HUZquQ9+f6n1HU6ueyfRz/lvlL0hmv6m4nBd0N+Ga20l+7eAuxW/zeo798Pvnpo/6u9gaNd1ODmd5kD1Gf190QTf1PskqBvvVDSyUYpHfz9D3wfLa5pm7NpZpLl27Vos4zlNH7bGEKGwmq7jQf7iZYquCOoawkCH5lxc0HnStk48gdlVYy8/9qIrs5cPUptc0Jth+aLY9Lff6XEtzmQ0k5WRqhs6J3v3sH9hm1t7Ioq2sa2BzBC9kx9r3DqjcRqEdhr5t5vvaKeJNnm1oXV8KJ4jGnRFbYLJJ/hdNY26qR0Hdqehrawyy05l/g9hbIQpy1/uZugqYZOn3+1qv5PN3oW0X91d0dSYDXlBe3L7IW1PmtWlF+07MDmttlNwp5B8X/+x4RjcI+i19K8+mdFx/U/0xuHHPYjeVTjvOQFLK6Ub/3oIYGv5dAVqY6pdUrYXGYcbB/3ZYzjn+YdN6y1Dix8z48oX4c97xpwktUya9xCd+9Y/vploVBwrjuEWpPMqM21zXtOfcmD/TH3QPsc7tVV/PzhTA43aWo/X73FLSToIE0SkU0kN7Tl3t2la781dr5ve6Jy51aXv5bEnFla184bH6q3NHvSGAYxUR836LG7n7Yy/EbVM/KJoaqEeVz1W9aFJZNWCtBFZXO7eSb+VySlEWpd1nIcVyTFiloF/fm6N78ufY/yJCMuklk1dWvzzvXV12xJcsmLyxhevzVuLoFHnYnlos7b+Ieba/P7gjc4ZRh0URZlIi2kd/bQOwzc797P/yvgjkQZ1ESeZXV7n2dWY185fJt7Ez3WCvPGzxgsc3t66c/d+N+OLRZlVVdWUHvJBIGvNi1c7+VurKcYroX0iP5KlL7SSaN+wcB9qsT+AFkYJnXeAM7YMKbKgjIJUFpg8OeFoy7nglLPy0zBv8hwZ1OZgaD2PvKXlO8n4PBFVYVzWRWLx6b7e+uk255E2H6hyXSUZ8FlsygTwPJ5z8ijLoEiLIrSYnkpvHCmtz9t8tYhlkeRBhk1Ij+z52wmWViTKKs6zIi+xDZBpdp3UzbpPznhDkaSyyf0qRF5012Kz0rvWf/K8gnWQ0LuwOtmDfuKZOMXuGIVZFXmhqctjVP3WGfw1p/jZWpzVGTS4R0yknHbffyTjC0Vd5WUSSuyL2skSdoh+5559yHhjUSdeldZNibyHoiBrhjHc+722jOYMkfH6ovTLOCxTZAX8LBiA4711t/8OnHIWUapepEQ24yps4qw4unbKSa9Iay9LooD4WPUY+3buFH/jqG7Gh5m02Oji8KNb/bR5pEiyrAyBC3noqbDRTZY30I0Smrs=
*/