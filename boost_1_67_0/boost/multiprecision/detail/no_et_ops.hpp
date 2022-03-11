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
         BOOST_STATIC_ASSERT_MSG(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator+(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_add;
         eval_add(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator+(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b);
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator-(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_subtract;
         eval_subtract(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator-(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b);
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator*(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_multiply;
         eval_multiply(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator*(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b);
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator/(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_divide;
         eval_divide(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator/(const V& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(b);
         number<B, et_off>                                                    result;
         using default_ops::eval_divide;
         eval_divide(result.backend(), number<B, et_off>::canonical_value(a), b.backend());
         return result;
      }
      //
      // modulus:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator%(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         number<B, et_off>                                                    result;
         using default_ops::eval_modulus;
         eval_modulus(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator%(const number<B, et_off>& a, const V& b)
      {
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a);
         number<B, et_off>                                                    result;
         using default_ops::eval_modulus;
         eval_modulus(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator|(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator^(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(const number<B, et_off>& a, const number<B, et_off>& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(result.backend(), a.backend(), b.backend());
         return result;
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator&(const number<B, et_off>& a, const V& b)
      {
         number<B, et_off> result;
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(result.backend(), a.backend(), number<B, et_off>::canonical_value(b));
         return result;
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
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
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator<<(const number<B, et_off>& a, const I& b)
      {
         number<B, et_off> result(a);
         using default_ops::eval_left_shift;
         detail::check_shift_range(b, mpl::bool_<(sizeof(I) > sizeof(std::size_t))>(), mpl::bool_<is_signed<I>::value>());
         eval_left_shift(result.backend(), b);
         return result;
      }
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator>>(const number<B, et_off>& a, const I& b)
      {
         number<B, et_off> result(a);
         using default_ops::eval_right_shift;
         detail::check_shift_range(b, mpl::bool_<(sizeof(I) > sizeof(std::size_t))>(), mpl::bool_<is_signed<I>::value>());
         eval_right_shift(result.backend(), b);
         return result;
      }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !(defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ < 5)))
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
         BOOST_STATIC_ASSERT_MSG(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
         v.backend().negate();
         return static_cast<number<B, et_off>&&>(v);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator~(number<B, et_off>&& v)
      {
         eval_complement(v.backend(), v.backend());
         return static_cast<number<B, et_off>&&>(v);
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
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(b.backend(), a.backend());
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator+(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator+(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator+(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_add;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_add(b.backend(), number<B, et_off>::canonical_value(a));
         return static_cast<number<B, et_off>&&>(b);
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
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_signed_number<B>, number<B, et_off> >::type operator-(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(b.backend(), a.backend());
         b.backend().negate();
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator-(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator-(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<(is_compatible_arithmetic_type<V, number<B, et_off> >::value && is_signed_number<B>::value), number<B, et_off> >::type
         operator-(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_subtract;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_subtract(b.backend(), number<B, et_off>::canonical_value(a));
         b.backend().negate();
         return static_cast<number<B, et_off>&&>(b);
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
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(b.backend(), a.backend());
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<B, et_off> operator*(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator*(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator*(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_multiply;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_multiply(b.backend(), number<B, et_off>::canonical_value(a));
         return static_cast<number<B, et_off>&&>(b);
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
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_off> >, number<B, et_off> >::type
         operator/(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_divide;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_divide(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      //
      // modulus:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator%(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_modulus;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_modulus(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator%(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_modulus;
         detail::scoped_default_precision<multiprecision::number<B, et_off> > precision_guard(a, b);
         eval_modulus(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      //
      // Bitwise or:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(b.backend(), a.backend());
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator|(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator|(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator|(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_or;
         eval_bitwise_or(b.backend(), number<B, et_off>::canonical_value(a));
         return static_cast<number<B, et_off>&&>(b);
      }
      //
      // Bitwise xor:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(b.backend(), a.backend());
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator^(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator^(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator^(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_xor;
         eval_bitwise_xor(b.backend(), number<B, et_off>::canonical_value(a));
         return static_cast<number<B, et_off>&&>(b);
      }
      //
      // Bitwise and:
      //
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(number<B, et_off>&& a, const number<B, et_off>& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(const number<B, et_off>& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(b.backend(), a.backend());
         return static_cast<number<B, et_off>&&>(b);
      }
      template <class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer, number<B, et_off> >::type operator&(number<B, et_off>&& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), b.backend());
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class V>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator&(number<B, et_off>&& a, const V& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(a.backend(), number<B, et_off>::canonical_value(b));
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class V, class B>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_off> >::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator&(const V& a, number<B, et_off>&& b)
      {
         using default_ops::eval_bitwise_and;
         eval_bitwise_and(b.backend(), number<B, et_off>::canonical_value(a));
         return static_cast<number<B, et_off>&&>(b);
      }
      //
      // shifts:
      //
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator<<(number<B, et_off>&& a, const I& b)
      {
         using default_ops::eval_left_shift;
         eval_left_shift(a.backend(), b);
         return static_cast<number<B, et_off>&&>(a);
      }
      template <class B, class I>
      BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_off> >::type
         operator>>(number<B, et_off>&& a, const I& b)
      {
         using default_ops::eval_right_shift;
         eval_right_shift(a.backend(), b);
         return static_cast<number<B, et_off>&&>(a);
      }

#endif

   }
} // namespace boost::multiprecision

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_MP_NO_ET_OPS_HPP

/* no_et_ops.hpp
V+/V2jtNF/8pfxwbqYAffTP5GHVZMEbDoRt8Ir6EDPMhGUXui6RCUMb3uUaATxW7MJe6HCCFeY3CHo58VGrM25XBPcffdzBKeUKpelP1H84MtRWc5/7JavzjffxnAPjkFL4u5/yWZ58m2bop8S6oqRUvhlqWZPl6Et2C1ctJVc+IXyTkzv3lioVvoyXub+mtNOCmJAC4Xh5z3aa7hwk6i0uD8BChvWVaIHLZ5Ox8WJzCEah0KXve7JUz8cn3BHG6pqFuX7/9UUe3B5BPo6eU28q1Y5HxQqhfHlzb4pFY8Rxn8AG6le6x26jke/oXWb1z/SZ0E/GqADw3u/l5gNcEAemR7OwvTyDAHx3dvD/McqNxbhq71z/Glh++QJ6MUcIVZP/9DytVOSTrgt47EEJpDXiR8ERwfydwEeBERHxIcvy8YFL4OFplQTElePi/8DDS7amzhZBzKdH4eRIp0aHzRS9ekx/ZGUyOJt0brsdGLtlrFV1ra97PLzlZJ3mr2Qae4VcUzSX/M3z/JF0JsP3UeUNVwyWUjBZ2PYefPfBy9PHnrbs2SNnoxDa+K8Zi9OWZoGGTLIa5B9/dq79Uc9L/UbDLBY0nKodNkfUiCxwAwNcj5IHGwWZDkXAmAiRaJ0AOFSyglt/0k4GCLCIQi1fbp61mPKe53+MyMyFZWNGUzRjC07FCbeZXFgPNOw88LbZvYofaXcHwScyHjy6tWJ6k4wSCJfHX7HYhYGinKe5C6+Xei4c3+kl6CVCUxU6iZLSfsd84GvXz40ShmHKennQukMtn4pBAGz7YDa7g6coXgNmPEe8DYUjUd7f/18vSC8OE0WE0aXMmocdlxrWri9/BSAyXdhUm5PK3r2U4UPWPLz54Efht4MbfKwqVRSFvQoz+oEBbiCTW/hub5QgTmCLYgoXlKTmyGrv5VPxgvrZ7Kr8oOyB0K0NmyBPYqxFOhZYQqa6NtIR8ZWvilIBdB3iIUXSxaC+epew5TtNW558sB8qTzxDz5Br2P9KG7C263GEQ62eDWoyVHaZYaSTCTFECmCXiFBqey2uMjxBtUBQAnF+Ck36PVSHkfSGkF1hmcPonY0zShJ5Lzi70GKNYm/2PEazHtyuM3L0bdfNCGe/p7Sz6HY1NG0dzK7W2of0XubXVjA8n4LFN/bIg2Kw4WIXJxdmtzht2lz4huhAMBNRrCyi2266w7RSsgOcWs4P4AuYd3HvFlmeW8594Et0EiM4vbGWDiHFtR3ZereqX3Z/kYmuEBUuzcNh1J243R8XwaRSIlsIPTAl7qNs34t0rT5uCBMTgLjqTTmx2PS/wjDRu/TAeAAAs/9OqVVPRsoiMnHzM1UeB9atJI8NJcCA7VYSmPkQ01aeRp9c1iQ9Ig+CzvYI5AL7UelZeXEt590WAjyj5vWM1N2a30Dteq3h/0lX6KTZ1TvcN6ongVswXUY7XibuypJpaQegYmuJDnyptFrcc8TqvnC5ezs+mJM6RdrSVXyXbZ2YKCYK1gyFN9swU7Q1Zk6Mers8UKYvKekzNhyGV/x0SlzFGd2T7tEkVXan/sTQsgoSxTTwQtHgXBM2yMOxKxYGiO3eaZ9uzomqnx17ZSTNlaCTf1IsZfxVgmbJ6MVm0RPu7uPB8wu1ZsPHgLLS/i/N3JOrG9THeKOcxHPVFaXznfqSyTpZJ1vNqGf6Cq81UpUf8fWrT7AH61k6UZG/Ylc57W7nVVVYa5PrfX9/PW1Jz9apV3KfM0ZsSk66458qtvdEfTU7NVsc6/EaJv5FQlcbUjOEr64n58xwJde3pEdSSWM603cx4EFMEHfTAJSEwOUQCNyofnaRjzWkaGM+xUid3Jrhp/AKXz2bdO9Ur1ZUSyl8hCRN9Ce4g1RHTHvMJgW0+nYfCEtOZ3TA6BAdSrtbK9rPBJ6vYP5+k9p+l/JrWY2AbiF+gcYA/EowmaAPO4DGfpRrcUvgP1xvXCWl/7geQgaCOJM5+6nd4p874v796Imqn0wXWbHPmBxNJi5kZisIopKXMDSSQFNNT5wd/sklBBb/N9z8OlqoP6TXkO4gY30w8HCXZ/4qpU7VzxBO58DMklQ9wBH0eGAxw/pRyV9UJ2BCjUNMbZGMHS3HMVe2X3t1pWHH7OsoKemaki4ZTiSVUi1YE3InzrEVYelufH9+rPiCLb6SeIVDRChbcX15S/zTa/diVVdXz2A5Q7Dh55LCJF/xcvJMdLwD8bCzG5+m3ISsqSkkzsAwt/m/h64aB5emQrxhXtu3CYzq0oIkMPly6+tk1tEg3KdSrwgY9An4JuEcH55arWr/jLdJng7ViwdA/T+3uLOkfwQQN5tw/6H+fLy0iDx3NvHRbPxSRXUHxXCneLufhXa6nGh6xM4nZ5IVZodzCR3iTVrLZzOeGnbiexm/tnjP3AMG1i8H/+mQqNLu2Za4P4rB3ZZdHoUy3lpOlyzDXqwc3HeER4rwuA3wIVF68SzyTOD89Xp+iF4iwu17K8nunL8GhWfVuCqTvjdEWefNotPT/yRmu5tc10GzOpaTcQ6ZAmD82kWR41Kbckg6RKdmmJtrCKVx9iYPgjtQCDI19LQV8a8EaOot06aIOOKrZrSEyixzhaW6HNw4xTleF3zkzPO+I0ay3esWP/i7kR/YFigq1ZQInj9iF8ytO3Y3yImUSOMusOMSh/LHLO3iqQU/9fFfz8wzHETkHWgX6EcVoZNRHLR6WL3BbNUGdmJvDo7wXTcSrpY7QauFQQhZoR+s+3CF91ahUr2bp/OnzP8jDY9emP0dxmo+5sW8eT2ZkjohhLMXazU+zTB81zbqONx6UgAMHHYVU63Ns+pbQZFlGTXIVMSMiwQJyVXx1Kadqqg2270hePLNk9TgwPSnppKiN/sc5fLEKIPBwjRp0uFHAI17TPjNtu+LtaUjWJ5gab6O+RKKu0cemabh3IBufUrPPHxl5N1Jnkpm0pU8Lh/JJT+2qFrlrtF6iGKf0ih+AD2+dgoRdqHb+3q1ivRdUfGYX1Y2Tj92yWpMH4aEdsN3ZeGACRm3N9/RGyt/2lE5Ls+PDBiy+FXAj3mGpkbKLYw48ECqT3XykYy8T9zKW6gAho9ja2pDPZfbvcGnb5Xt4mp7bGFxlR1W8jr7o9ta3xdkTkBtebcegsiVbijNRWA7DPUIPjDMtk6zzUkDvCAvyK1jhEfFo+VainZLOMK+3NcdJP/UiEdCSprPFAVhu0Nk49qY0aZrxhufmf7ZVafyfj0Bwf6jWv2NMAnJgz3oypLPYaHPmrRJNCpixitbIp0TNWSUa5NOj/qv6eGHeUE//UX8xfNvS1Eo7ctB3BkmTcurFrje38NrobXMu89iNg7OEJUgHjEmARuA6fM+u3etKefog6xnhGSMbKvCUgCsXNF9V89M97LXphOKbyqbBebM5+6jlK/DcQQ4+u+z8o6Fl3bX2pptWPdRQ/0fgUuoOJ+Zo6coVIWt2aAUQKGrBNcSU3VMDucXMyCiX592PE/rPoRept9vZABz/450JXzB1iy/V1t9RRqFPUJwh0wTfssGQWWS7KYLjPjwP+BN7+ZPFfxta7ufasFHnTuD8DFSDuy/HSXa2L6nT+u2b9DkF3SpciTAGCl8MgvExJjhJoSxuYkEzJqxdRtH8sthVVgX2g1OF6ULLLPt36/F+mg2NN+qcTOJtzyXjaey89AQGAYHAYYK85n7VBMVmi+8ycrbR/bkk7ERxzteDwFzz+pLDyLnFOz+lP9E8O/kUEmRzyPJS90EaONg6sUi5jGLG0XxGQfzanhcFuIzbps/pBojxAkpPg+WhLNDnkmBScbTvcCnHqQ+16y/t6MmxsdokMuT9Lp6zTByliNNpAerCiymSzYg3gEFVBP0bMChWEidegEX4XJAjKtBWuRtInw3kshQ4Q4SIiJ8CNgvG4BDLt5QEUaZP2pyLsFLehfT0ArvjCfAPQBtsFOdiWh+hU8Q67RsdNedskx7TIaYrNVtiKOn6LU2zOX6OcPZhJTeyCzkwOxuhqKm3i/o9wzBsm4L5CqVbcjfOas7XSkTwqKVKButiFXxndLDCZiR5KrtiOdYSPdTWK2PWpHuIZr6P7pejSoOsxOZ/GuTZ+qWJdwYxdFy2PXiDXqja8ii37yoZJg5POPF0+QvHyTGNQ/3552+IEEz/haEQAZvp38lBtnMEdpiZ1zSXXaaEsGX7aXIDIkrOt0sR1WEVHh1qNZqwTEzqR4/JLsCrCNr4EeZ9Sbdrahu/19S73RYy8/emxPr/Q4BAAzB5EuSZ67MmtNcP+XvxLp8hX5FJpQwTye/XO2K0zhU6HOaZYE7l37ekpONwdI3E0J+HNcbCCNEob+gY3ZLSniGeVpp1yNIAGb95/EyDqbvoSePqDbzvUi//xD81+FFJZZtXAUWg3umbaA+dAGH5dI+SXC0DtS1QHn2ZMpLWoMbrmHjHDQDpGluKE4tmw9xSjqO9646f2jivzELvX++un8D2vZwOVEG/NlviMocNpETa1a9+De6tD9+6yWz1lt1o22/ZQcJxSE4A88jbRfSPFYObqWtUPd17WdakJOiAvwlh25X3oWOLNauTG8GwXVFpaQMJgL0W70XUuAy4P9CBhpKbvYN9ZpHn9V2iiuLJ3Y70QY52eoUgjldTbPBsWyYAMZczE0nCcHa0YRcvl+FbZPRFJxXsGkHqOKDZOgp13dmo7zVs8AtmTqN5k2D9ZdleIbLeDQkhwRNMYO5x/4V9PSuD74DFPF/oTL3baWqOVSeFoiMzyVkPY0LO32RhQh+XfrQhva5WnoRGsQZtT6RfUlyscq+EjFujrs1sSofyjHHQT+X4lIPaGQN2B0C9EYUzl3kVPOL7HVA/CS2ktvNGblnS6gBJST6pb2kwxCvJQyemHHTIIx+aDk7VLLeML/oRC1aE775xMZ4DfYk9iQV4K/AtvoB0NGsrkdOFHv2yGeXEl/pdqdwm35ygH/EQsEa3e/bvjBOTWNFJkWFMj0IbN9XCipWxGOdVLBmQpSmXoINwtb/w0RDIYk4b9wuKQrcG4/L8t+U464h3bB62cTFAB3/UmRa5XIE4XdfdEXze0rfgvWI04sHVeW6nGUOEu65POZpo/mZuDCUmPK60fQ+no/Yg0JyrNY6cgIOfopppdj8UiCqxZ4JCvFgyr+ELyaazYfNjJRTkn38cpI9tUAMBiYTBFV7N0XPYtpbIK8lvH4z40qojDKCOSUdrNl/09M4tdSncZzrbVDAu+o5kpTZg2Qy5OrBUt8wYUmaRVy41qKb0kQ1AYX1qzbxvQRZG2lZFMc8RvVhYJQ68ia5qXNeqsZCzQd7MWxcSZJkLmO2+wjI6U59lrWblIV7j3jYqiuLDgywWSkEFojeOxoLV2zixJrHbJSmWqViQ/f359YXXc+mceaNJpjl/KybRtKFTPDjKWsV4Kkxy8aaf/70VAiH+7YvhDcSjljqazHXB542uSRegt7z68sye2yiF3/KTjf93d/U4S6Y6CxK0bby8PWqrXXiUttQhtIIWJXQ9b8hSsF3tT0s8keFTdJUN0vdJ+ETDv4U04EqF6bMWiRGJPiRQPCzVaIDlPKoCqQhkUkKX5HuV15dwZ+gPMunCXifs64TBzTMbPph6qwnYk/SgX5gux4HPuu7Z0gR5nUh+4KB/OuXE9fL6UkdE7LVZH9SOuVHZ5aNnq0JA2ciIvUlZ885KsnG22nQRruwtuz2Qs32922rjetAK0L3CsKDYPbSKe3GzPKAsuWMgBAW0Rq3XsaguZfaadHDoAt3wR5VEvF9hpnC2vcxllJtLh+QAdaATlyzwGlPf4DNyLDzYCM/IdP6GksdoIGGMvePatV8FWWx7LdgWyXbrn+NT11VAmRX+54tGHSrpsCWQR3g4vambeEH+BHDxlhOGyvbM2XdXKd0xYToseamECcMy+kIyuD+KJpr1Zzcd+J50V50PBBOifyEGZgcSG8aKJJ+XeEfWHTXCYkeFMJ+7tvvLJ9bCV1go3kpnNwQyGxplW9FiObyhVQwvbndyABvFxVCGffdcydTV2QUiuNRmdVWKbFd71VVxoloKpYpRDonkBGIYGpoW68IHXMczyjToz4s9t0qRhWXVMiVEuJzIpbKrgZJkhahGfilihehQZSqOiiUqC6VLBXmdgoh1HCaDxdI2sWhk+oz3V87Jp+87Nvtrlk+MD1jNhbd37cUuwydS7cKi8cWSUZo+HgxsyiCOerQoMrskQSdQ/36ERRA45fjxdOYjNGeUEwS33qF7IfLr3iWsk0qRxk7fu9TVrRq1orQxaj8l8JpzuZu5GlY9WvRn8Wz9G0ubi26cFK2jLpYQvLDpRLsfHXT/J8JlgD+LVBLDHnPbk6JyyqSaSqp05Ul24n62zIkNquemLvgji66h658SykgvCGvjmpoODItIS08edLkk1RY1REJ8LzyLR6+oVq+szekB145efMe4TJbh2+jPMr88GtGn5BJTr8/3pmRpT9JzwDT3EjKlW6PbJCGybm8V3s7MxG94K2rLT6yk/koEZVe1Hd5k0difofyflXVIyU4KIBqMmtb3DRJbpTHKmygcTdn1pfDLvj6e67PIy6wYJbK9PPihCtEteYjMmVQVpMTllSpjFdZxz66V5ycqWndCpB35UV22eArMmrpMupEd1OlVuzM0PGga6hAMbfyF+Bsd5S13NTkF+4J3Ty8r+KfCYmbkCjbO5I6+ugkuCH8muGZp5la4Mk8mTW0Y4kBqoj/+aePgpwA2pDm2J5LtzjCmn0ZtLWxXo7NA9MXRhp2QRvgADaI19j+Q37dB+wPdFiMMBWVG3zVioEdlUOGPIYtydYmaCpI4vLg3E3SaXDgy3F/UX+K07RwBxtPH64PiVRnGQJ9UMMEGZkkGry5PVOBAyNT4mbN/mQzsKALRZ5pDSzsYUdAWtMGazQ08xBpizu2NuQp3EyA/eHE/bvWZ+/6ddwPrnMB9M9GPpXS1dEVmlN45Opi5rWvRvdulnnalZPccvlft2UzNSWhFKdtiYmyzlbb4CSh9BbQaXP1gKSgueBOV6wh+itSYDg/f4P/ccdfd5kyfLkw/w7TtM+w0x8jQMb43MDIFQ67IdKuNjMhQZGh5Hm2cTzqjf0BZPgZPPWasHg1HhUAMq+b2LcwUNig+GQXPSaCWV0r3RESG8mQoMv+h3u6iIEqiue253DD/8eb+OWsnLFKfPNF+6bzIdt16qPbcdp7puHZf4blp/0/5zbfewve2U52B7JkAUTAlBedcvLJn9mWu0z1k5zHcUg5KobTX/ijL0XFyQhbZzRYGrKNNdrSiHP+G91NHRQXgvFjPmW6LUiks5XO3DVdA4U6k//MKscuhwQNUVnWSp+LolusBwP8jOBxic/T3vsdm9ecIe/eVz6Z4TNGB1/WhLWNmy+v62JEtp+Ntc+rE5j/Vz09rWtajrye4pUFmaZ1npLWAd67hW1BulomUS8KIVKNcT+VC3LpuCKOTwCO0tuoMmpL9Ln2NU5iWeSL9tJTkeyJvZ0kIEvMDic7Fox6su8sm+n2LlEoz26CQO16EbkdpVdDMv2KLuUUTQinoXGf1FyOSdnwqlReKoNlgIrGR9JRu4k50jQrSEQ78viY7YcCBcHfWeingOWm0+9QttKqJzHxYO33yICu9P/HFy+1h4Z0pWaCpuXDlnhkBzKPz2GmAoGXMh3/qcfFmZWrkVuhgb4kzsTPqv9w2pYKCnzT+QKmpQlDR7gZi7lfDAUFkzVrOnRB/r5xIIxTg8RoE7REhXpxaNgYAG1nfKEDtLk7pCnY86dfWl4TMyShDHXTnNcBn6LwIPThFBSehqToZmdZGD1R0XGCOgAhgvqKgRmvvDOTH+WYrHrHhKJkBAf5tQUcVQ4ERSnGjBZK7EFusTey0+k5QeDdi2HV0og/nnJ80vhgNQNhp7xY/2rDOzL2vhZPxZ41hw8Gm2cbdJspai1v+uyiaxo5VNzoQAiYyY84M0+IsvWbFj4ef2XEA5yiLMnSXxuotSFczuN6o2LOFxDlHb9NoU0wqp0p0r3UM53ngwq2w0n9gvb7LNQbhuuQ2Hf1MMdqAVLWQdTl8c24qameyVFUY+hb9anoa7CpQ4efEXRYyXiTecvWPFbdmuRdPbBorb2771IPla+3bup+grQ8mqIYu3XN5roJFdG1ra+qWvShr+gUdD9TqXb92/e5xxHzuX+ImnxgrkJz4gSiQAYx8wsLe4aP3Ym1GkMhWvNeIqBbYxL7XKJVk21TYGCg37iBHnWSvBZ1fEyUbrJh0SZ2LbzRFibBnn+KNNxsa3VBVvZhqzJOvqe6lVeYWIhv/cyUaHo2gKncBoBEYOqlYX2+nNWDnLvXUxi793F/U2KARIQYsVnFdlhcpaQse//djMCkmcsKsJ2ptY9L50qQX84CUlde5aGpmzWQ1X/fH+czB26XT7a8vu5i5tEjs7ECd4ACYKBLpRSuOiVFQoZxvIxBSG/cHb6xbsI6c0dOelYOAccA+SqlvdJm+clIIAspKF7ZDsBmJ3ZLhvpwcAg5QGcIaYP0IbFakjzODKTHDIE/mXKSVt8i5wc56EKvK7YIvvLKefSeuxgyLibwFiQ9qwbqWNK3CpY6C4+rXNXHHKg0y9Mi5TEbOhj/JY45ktyhtnnzAcVYLEz4lGArHiotvnedP8KUMxJdviEEwgsm3F+UujKga4KXYoGUl/Yz3Xt7Rc5XSz1XIvpGmiCEh47I+ogRLWLaDZ0uu1teZYXzwgj2YXxlSA7DjyV5QMUyMjXOXKlTrgSgnZrNJUPWORZ1SCns++VLjhnyMD+ufDmlhIvmS8mr1636k0g9ySBSXOa2s60ixmF/X0zO6M37trKh/rsyffBbsZ72EERba8dIkNeGvb8rnvFsIw0Ag0U12QSTs5+2y/f/xykmNpwX9tdKZnXEFQnqCU1OIA/ZXzQ2KUAXqLSMAd05gX8OY/Iag3d8x/7YTatiInJWfcZtRk93EmEDORLa8ti4J34yw+oJ1a0xLXE6OT6DaiFSmEhOakGfUunmm4TzYBidlqJAtyORqw4sU9uAogHViMrxPTvShICzREW7uuyIZCaGpByr5mHXS+fIM8W0NK1gpcpfgOQPjjI/IDr5gSc06M6UXXQud0T05KoZoUnp3WrPUXdDgiroXhLUgEPBjel7w2unIrNU98iVb4sPjPTg=
*/