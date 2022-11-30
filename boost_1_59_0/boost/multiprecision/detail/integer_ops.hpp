///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INT_FUNC_HPP
#define BOOST_MP_INT_FUNC_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>

namespace boost { namespace multiprecision {

namespace default_ops {

template <class Backend>
inline BOOST_MP_CXX14_CONSTEXPR void eval_qr(const Backend& x, const Backend& y, Backend& q, Backend& r)
{
   eval_divide(q, x, y);
   eval_modulus(r, x, y);
}

template <class Backend, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR Integer eval_integer_modulus(const Backend& x, Integer val)
{
   BOOST_MP_USING_ABS
   using default_ops::eval_convert_to;
   using default_ops::eval_modulus;
   using int_type = typename boost::multiprecision::detail::canonical<Integer, Backend>::type;
   Backend                                                                           t;
   eval_modulus(t, x, static_cast<int_type>(val));
   Integer result(0);
   eval_convert_to(&result, t);
   return abs(result);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR void eval_gcd(B& result, const B& a, const B& b)
{
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_lsb;

   std::ptrdiff_t shift(0);

   B u(a), v(b);

   int s = eval_get_sign(u);

   /* GCD(0,x) := x */
   if (s < 0)
   {
      u.negate();
   }
   else if (s == 0)
   {
      result = v;
      return;
   }
   s = eval_get_sign(v);
   if (s < 0)
   {
      v.negate();
   }
   else if (s == 0)
   {
      result = u;
      return;
   }

   /* Let shift := lg K, where K is the greatest power of 2
   dividing both u and v. */

   std::size_t us = eval_lsb(u);
   std::size_t vs = eval_lsb(v);
   shift       = (std::min)(us, vs);
   eval_right_shift(u, us);
   eval_right_shift(v, vs);

   do
   {
      /* Now u and v are both odd, so diff(u, v) is even.
      Let u = min(u, v), v = diff(u, v)/2. */
      s = u.compare(v);
      if (s > 0)
         u.swap(v);
      if (s == 0)
         break;
      eval_subtract(v, u);
      vs = eval_lsb(v);
      eval_right_shift(v, vs);
   } while (true);

   result = u;
   eval_left_shift(result, shift);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR void eval_lcm(B& result, const B& a, const B& b)
{
   using ui_type = typename std::tuple_element<0, typename B::unsigned_types>::type;
   B                                                             t;
   eval_gcd(t, a, b);

   if (eval_is_zero(t))
   {
      result = static_cast<ui_type>(0);
   }
   else
   {
      eval_divide(result, a, t);
      eval_multiply(result, b);
   }
   if (eval_get_sign(result) < 0)
      result.negate();
}

} // namespace default_ops

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const number<Backend, ExpressionTemplates>& x, const number<Backend, ExpressionTemplates>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   using default_ops::eval_qr;
   eval_qr(x.backend(), y.backend(), q.backend(), r.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const number<Backend, ExpressionTemplates>& x, const multiprecision::detail::expression<tag, A1, A2, A3, A4>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(x, number<Backend, ExpressionTemplates>(y), q, r);
}

template <class tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, const number<Backend, ExpressionTemplates>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(number<Backend, ExpressionTemplates>(x), y, q, r);
}

template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, const multiprecision::detail::expression<tagb, A1b, A2b, A3b, A4b>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(number<Backend, ExpressionTemplates>(x), number<Backend, ExpressionTemplates>(y), q, r);
}

template <class Backend, expression_template_option ExpressionTemplates, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value && (number_category<Backend>::value == number_kind_integer), Integer>::type
integer_modulus(const number<Backend, ExpressionTemplates>& x, Integer val)
{
   using default_ops::eval_integer_modulus;
   return eval_integer_modulus(x.backend(), val);
}

template <class tag, class A1, class A2, class A3, class A4, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<Integer>::value && (number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer), Integer>::type
integer_modulus(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, Integer val)
{
   using result_type = typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
   return integer_modulus(result_type(x), val);
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, std::size_t>::type
lsb(const number<Backend, ExpressionTemplates>& x)
{
   using default_ops::eval_lsb;
   return eval_lsb(x.backend());
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, std::size_t>::type
lsb(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x)
{
   using number_type = typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
   number_type                                                                           n(x);
   using default_ops::eval_lsb;
   return eval_lsb(n.backend());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, std::size_t>::type
msb(const number<Backend, ExpressionTemplates>& x)
{
   using default_ops::eval_msb;
   return eval_msb(x.backend());
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, std::size_t>::type
msb(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x)
{
   using number_type = typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
   number_type                                                                           n(x);
   using default_ops::eval_msb;
   return eval_msb(n.backend());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, bool>::type
bit_test(const number<Backend, ExpressionTemplates>& x, std::size_t index)
{
   using default_ops::eval_bit_test;
   return eval_bit_test(x.backend(), index);
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, bool>::type
bit_test(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, std::size_t index)
{
   using number_type = typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
   number_type                                                                           n(x);
   using default_ops::eval_bit_test;
   return eval_bit_test(n.backend(), index);
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_set(number<Backend, ExpressionTemplates>& x, std::size_t index)
{
   using default_ops::eval_bit_set;
   eval_bit_set(x.backend(), index);
   return x;
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_unset(number<Backend, ExpressionTemplates>& x, std::size_t index)
{
   using default_ops::eval_bit_unset;
   eval_bit_unset(x.backend(), index);
   return x;
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_flip(number<Backend, ExpressionTemplates>& x, std::size_t index)
{
   using default_ops::eval_bit_flip;
   eval_bit_flip(x.backend(), index);
   return x;
}

namespace default_ops {

//
// Within powm, we need a type with twice as many digits as the argument type, define
// a traits class to obtain that type:
//
template <class Backend>
struct double_precision_type
{
   using type = Backend;
};

//
// If the exponent is a signed integer type, then we need to
// check the value is positive:
//
template <class Backend>
inline BOOST_MP_CXX14_CONSTEXPR void check_sign_of_backend(const Backend& v, const std::integral_constant<bool, true>)
{
   if (eval_get_sign(v) < 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
}
template <class Backend>
inline BOOST_MP_CXX14_CONSTEXPR void check_sign_of_backend(const Backend&, const std::integral_constant<bool, false>) {}
//
// Calculate (a^p)%c:
//
template <class Backend>
BOOST_MP_CXX14_CONSTEXPR void eval_powm(Backend& result, const Backend& a, const Backend& p, const Backend& c)
{
   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_modulus;
   using default_ops::eval_multiply;
   using default_ops::eval_right_shift;

   using double_type = typename double_precision_type<Backend>::type                                      ;
   using ui_type = typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type;

   check_sign_of_backend(p, std::integral_constant<bool, std::numeric_limits<number<Backend> >::is_signed>());

   double_type x, y(a), b(p), t;
   x = ui_type(1u);

   while (eval_get_sign(b) > 0)
   {
      if (eval_bit_test(b, 0))
      {
         eval_multiply(t, x, y);
         eval_modulus(x, t, c);
      }
      eval_multiply(t, y, y);
      eval_modulus(y, t, c);
      eval_right_shift(b, ui_type(1));
   }
   Backend x2(x);
   eval_modulus(result, x2, c);
}

template <class Backend, class Integer>
BOOST_MP_CXX14_CONSTEXPR void eval_powm(Backend& result, const Backend& a, const Backend& p, Integer c)
{
   using double_type = typename double_precision_type<Backend>::type                                      ;
   using ui_type = typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type;
   using i1_type = typename boost::multiprecision::detail::canonical<Integer, double_type>::type      ;
   using i2_type = typename boost::multiprecision::detail::canonical<Integer, Backend>::type          ;

   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_modulus;
   using default_ops::eval_multiply;
   using default_ops::eval_right_shift;

   check_sign_of_backend(p, std::integral_constant<bool, std::numeric_limits<number<Backend> >::is_signed>());

   if (eval_get_sign(p) < 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }

   double_type x, y(a), b(p), t;
   x = ui_type(1u);

   while (eval_get_sign(b) > 0)
   {
      if (eval_bit_test(b, 0))
      {
         eval_multiply(t, x, y);
         eval_modulus(x, t, static_cast<i1_type>(c));
      }
      eval_multiply(t, y, y);
      eval_modulus(y, t, static_cast<i1_type>(c));
      eval_right_shift(b, ui_type(1));
   }
   Backend x2(x);
   eval_modulus(result, x2, static_cast<i2_type>(c));
}

template <class Backend, class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_unsigned<Integer>::value >::type eval_powm(Backend& result, const Backend& a, Integer b, const Backend& c)
{
   using double_type = typename double_precision_type<Backend>::type                                      ;
   using ui_type = typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type;

   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_modulus;
   using default_ops::eval_multiply;
   using default_ops::eval_right_shift;

   double_type x, y(a), t;
   x = ui_type(1u);

   while (b > 0)
   {
      if (b & 1)
      {
         eval_multiply(t, x, y);
         eval_modulus(x, t, c);
      }
      eval_multiply(t, y, y);
      eval_modulus(y, t, c);
      b >>= 1;
   }
   Backend x2(x);
   eval_modulus(result, x2, c);
}

template <class Backend, class Integer>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_signed<Integer>::value && boost::multiprecision::detail::is_integral<Integer>::value>::type eval_powm(Backend& result, const Backend& a, Integer b, const Backend& c)
{
   if (b < 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   eval_powm(result, a, static_cast<typename boost::multiprecision::detail::make_unsigned<Integer>::type>(b), c);
}

template <class Backend, class Integer1, class Integer2>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_unsigned<Integer1>::value >::type eval_powm(Backend& result, const Backend& a, Integer1 b, Integer2 c)
{
   using double_type = typename double_precision_type<Backend>::type                                      ;
   using ui_type = typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type;
   using i1_type = typename boost::multiprecision::detail::canonical<Integer1, double_type>::type     ;
   using i2_type = typename boost::multiprecision::detail::canonical<Integer2, Backend>::type         ;

   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_modulus;
   using default_ops::eval_multiply;
   using default_ops::eval_right_shift;

   double_type x, y(a), t;
   x = ui_type(1u);

   while (b > 0)
   {
      if (b & 1)
      {
         eval_multiply(t, x, y);
         eval_modulus(x, t, static_cast<i1_type>(c));
      }
      eval_multiply(t, y, y);
      eval_modulus(y, t, static_cast<i1_type>(c));
      b >>= 1;
   }
   Backend x2(x);
   eval_modulus(result, x2, static_cast<i2_type>(c));
}

template <class Backend, class Integer1, class Integer2>
BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_signed<Integer1>::value && boost::multiprecision::detail::is_integral<Integer1>::value>::type eval_powm(Backend& result, const Backend& a, Integer1 b, Integer2 c)
{
   if (b < 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   eval_powm(result, a, static_cast<typename boost::multiprecision::detail::make_unsigned<Integer1>::type>(b), c);
}

struct powm_func
{
   template <class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR void operator()(T& result, const T& b, const U& p, const V& m) const
   {
      eval_powm(result, b, p, m);
   }
   template <class R, class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR void operator()(R& result, const T& b, const U& p, const V& m) const
   {
      T temp;
      eval_powm(temp, b, p, m);
      result = std::move(temp);
   }
};

} // namespace default_ops

template <class T, class U, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
        (number_category<T>::value == number_kind_integer) &&
        (is_number<T>::value || is_number_expression<T>::value) &&
        (is_number<U>::value || is_number_expression<U>::value || boost::multiprecision::detail::is_integral<U>::value) &&
        (is_number<V>::value || is_number_expression<V>::value || boost::multiprecision::detail::is_integral<V>::value),
    typename std::conditional<
        is_no_et_number<T>::value,
        T,
        typename std::conditional<
            is_no_et_number<U>::value,
            U,
            typename std::conditional<
                is_no_et_number<V>::value,
                V,
                detail::expression<detail::function, default_ops::powm_func, T, U, V> >::type>::type>::type>::type
powm(const T& b, const U& p, const V& mod)
{
   return detail::expression<detail::function, default_ops::powm_func, T, U, V>(
       default_ops::powm_func(), b, p, mod);
}

}} // namespace boost::multiprecision

#endif

/* integer_ops.hpp
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
*/