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
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
*/