//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_RATIONAL_HPP
#define BOOST_MATH_TOOLS_RATIONAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <array>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/assert.hpp>

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
   BOOST_MATH_ASSERT(count > 0);
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
   typedef std::integral_constant<int, N> tag_type;
   return detail::evaluate_polynomial_c_imp(static_cast<const T*>(a), val, static_cast<tag_type const*>(0));
}

template <std::size_t N, class T, class V>
inline V evaluate_polynomial(const std::array<T,N>& a, const V& val) BOOST_MATH_NOEXCEPT(V)
{
   typedef std::integral_constant<int, N> tag_type;
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
inline V evaluate_even_polynomial(const std::array<T,N>& a, const V& z) BOOST_MATH_NOEXCEPT(V)
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
   typedef std::integral_constant<int, N-1> tag_type;
   return a[0] + z * detail::evaluate_polynomial_c_imp(static_cast<const T*>(a) + 1, V(z*z), static_cast<tag_type const*>(0));
}

template <std::size_t N, class T, class V>
inline V evaluate_odd_polynomial(const std::array<T,N>& a, const V& z) BOOST_MATH_NOEXCEPT(V)
{
   typedef std::integral_constant<int, N-1> tag_type;
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
   return detail::evaluate_rational_c_imp(a, b, z, static_cast<const std::integral_constant<int, N>*>(0));
}

template <std::size_t N, class T, class U, class V>
inline V evaluate_rational(const std::array<T,N>& a, const std::array<U,N>& b, const V& z) BOOST_MATH_NOEXCEPT(V)
{
   return detail::evaluate_rational_c_imp(a.data(), b.data(), z, static_cast<std::integral_constant<int, N>*>(0));
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_RATIONAL_HPP





/* rational.hpp
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
*/