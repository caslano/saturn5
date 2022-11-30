///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_NO_ET_OPS_HPP
#define BOOST_MP_NO_ET_OPS_HPP

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4714)
#endif

namespace boost {
   namespace multiprecision {

      //
      // Operators for non-expression template enabled number.
      // NOTE: this is not a complete header - really just a suffix to default_ops.hpp.
      // NOTE: these operators have to be defined after the methods in default_ops.hpp.
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(const number<B, et_off>& v)
      {
         static_assert(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(v);
         number<B, et_off>                                                    result(v);
         result.backend().negate();
         return result;
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator~(const number<B, et_off>& v)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(v);
         number<B, et_off>                                                    result;
         eval_complement(result.backend(), v.backend());
         return result;
      }
      //
      // Addition:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_add;
         eval_add(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator+(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_add;
         eval_add(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator+(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b, a);
         number<B, et_off>                                                    result;
         using default_ops::eval_add;
         eval_add(result.backend(), b.backend(), number<B, et_off>::canonical_value(a));
         return result;
      }
      //
      // Subtraction:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_subtract;
         eval_subtract(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator-(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_subtract;
         eval_subtract(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator-(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b, a);
         number<B, et_off>                                                    result;
         using default_ops::eval_subtract;
         eval_subtract(result.backend(), number<B, et_off>::canonical_value(a), b.backend());
         return result;
      }
      //
      // Multiply:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_multiply;
         eval_multiply(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator*(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_multiply;
         eval_multiply(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator*(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b, a);
         number<B, et_off>                                                    result;
         using default_ops::eval_multiply;
         eval_multiply(result.backend(), b.backend(), number<B, et_off>::canonical_value(a));
         return result;
      }
      //
      // divide:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator/(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_divide;
         eval_divide(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator/(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_divide;
         eval_divide(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator/(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b, a);
         number<B, et_off>                                                    result;
         using default_ops::eval_divide;
         eval_divide(result.backend(), number<B, et_off>::canonical_value(a), b.backend());
         return result;
      }
      //
      // modulus:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator%(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_modulus;
         eval_modulus(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator%(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_modulus;
         eval_modulus(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator%(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b);
         number<B, et_off>                                                    result;
         using default_ops::eval_modulus;
         eval_modulus(result.backend(), number<B, et_off>::canonical_value(a), b.backend());
         return result;
      }
      //
      // Bitwise or:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator|(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator|(const V& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(result.backend(), b.backend(), number<B, et_off>::canonical_value(a));
         return result;
      }
      //
      // Bitwise xor:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator^(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator^(const V& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(result.backend(), b.backend(), number<B, et_off>::canonical_value(a));
         return result;
      }
      //
      // Bitwise and:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator&(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator&(const V& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(result.backend(), b.backend(), number<B, et_off>::canonical_value(a));
         return result;
      }
      //
      // shifts:
      //
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator<<(const number<B, et_off>& a, const I& b)
      {
         number<B, et_off> result(a);
         using default_ops::eval_left_shift;
         detail::check_shift_range(b, std::integral_constant<bool, (sizeof(I) > sizeof(std::size_t))>(), std::integral_constant<bool, boost::multiprecision::detail::is_signed<I>::value>());
         eval_left_shift(result.backend(), b);
         return result;
      }
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator>>(const number<B, et_off>& a, const I& b)
      {
         number<B, et_off> result(a);
         using default_ops::eval_right_shift;
         detail::check_shift_range(b, std::integral_constant<bool, (sizeof(I) > sizeof(std::size_t))>(), std::integral_constant<bool, boost::multiprecision::detail::is_signed<I>::value>());
         eval_right_shift(result.backend(), b);
         return result;
      }

      //
      // If we have rvalue references go all over again with rvalue ref overloads and move semantics.
      // Note that while it would be tempting to implement these so they return an rvalue reference
      // (and indeed this would be optimally efficient), this is unsafe due to users propensity to
      // write:
      //
      // const T& t = a * b;
      //
      // which would lead to a dangling reference if we didn't return by value.  Of course move
      // semantics help a great deal in return by value, so performance is still pretty good...
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(number<B, et_off>&& v)
      {
         static_assert(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
         v.backend().negate();
         return std::move(v);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator~(number<B, et_off>&& v)
      {
         eval_complement(v.backend(), v.backend());
         return std::move(v);
      }
      //
      // Addition:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(b.backend(), a.backend());
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator+(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator+(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(b.backend(), number<B, et_off>::canonical_value(a));
         return std::move(b);
      }
      //
      // Subtraction:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_signed_number<B>::value, number<B, et_off> >::type operator-(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(b.backend(), a.backend());
         b.backend().negate();
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator-(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<(is_compatible_arithmetic_type<V, number<B, et_off> >::value && is_signed_number<B>::value) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator-(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(b.backend(), number<B, et_off>::canonical_value(a));
         b.backend().negate();
         return std::move(b);
      }
      //
      // Multiply:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(b.backend(), a.backend());
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator*(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator*(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(b.backend(), number<B, et_off>::canonical_value(a));
         return std::move(b);
      }
      //
      // divide:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator/(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_divide;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_divide(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value, number<B, et_off> >::type
         operator/(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_divide;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_divide(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      //
      // modulus:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator%(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_modulus;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_modulus(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator%(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_modulus;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_modulus(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      //
      // Bitwise or:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(b.backend(), a.backend());
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator|(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator|(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(b.backend(), number<B, et_off>::canonical_value(a));
         return std::move(b);
      }
      //
      // Bitwise xor:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(b.backend(), a.backend());
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator^(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator^(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(b.backend(), number<B, et_off>::canonical_value(a));
         return std::move(b);
      }
      //
      // Bitwise and:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(b.backend(), a.backend());
         return std::move(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), b.backend());
         return std::move(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator&(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), number<B, et_off>::canonical_value(b));
         return std::move(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, B>::value, number<B, et_off> >::type
         operator&(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(b.backend(), number<B, et_off>::canonical_value(a));
         return std::move(b);
      }
      //
      // shifts:
      //
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator<<(number<B, et_off>&& a, const I& b)
      {
         using default_ops::eval_left_shift;
         eval_left_shift(a.backend(), b);
         return std::move(a);
      }
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator>>(number<B, et_off>&& a, const I& b)
      {
         using default_ops::eval_right_shift;
         eval_right_shift(a.backend(), b);
         return std::move(a);
      }


   }
} // namespace boost::multiprecision

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_MP_NO_ET_OPS_HPP

/* no_et_ops.hpp
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
*/