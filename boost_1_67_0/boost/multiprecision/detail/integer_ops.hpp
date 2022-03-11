///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_INT_FUNC_HPP
#define BOOST_MP_INT_FUNC_HPP

#include <boost/multiprecision/number.hpp>

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
   typedef typename boost::multiprecision::detail::canonical<Integer, Backend>::type int_type;
   Backend                                                                           t;
   eval_modulus(t, x, static_cast<int_type>(val));
   Integer result(0);
   eval_convert_to(&result, t);
   return abs(result);
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127)
#endif

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR void eval_gcd(B& result, const B& a, const B& b)
{
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_lsb;

   int shift(0);

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

   unsigned us = eval_lsb(u);
   unsigned vs = eval_lsb(v);
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

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR void eval_lcm(B& result, const B& a, const B& b)
{
   typedef typename mpl::front<typename B::unsigned_types>::type ui_type;
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const number<Backend, ExpressionTemplates>& x, const number<Backend, ExpressionTemplates>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   using default_ops::eval_qr;
   eval_qr(x.backend(), y.backend(), q.backend(), r.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const number<Backend, ExpressionTemplates>& x, const multiprecision::detail::expression<tag, A1, A2, A3, A4>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(x, number<Backend, ExpressionTemplates>(y), q, r);
}

template <class tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, const number<Backend, ExpressionTemplates>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(number<Backend, ExpressionTemplates>(x), y, q, r);
}

template <class tag, class A1, class A2, class A3, class A4, class tagb, class A1b, class A2b, class A3b, class A4b, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer>::type
divide_qr(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, const multiprecision::detail::expression<tagb, A1b, A2b, A3b, A4b>& y,
          number<Backend, ExpressionTemplates>& q, number<Backend, ExpressionTemplates>& r)
{
   divide_qr(number<Backend, ExpressionTemplates>(x), number<Backend, ExpressionTemplates>(y), q, r);
}

template <class Backend, expression_template_option ExpressionTemplates, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<mpl::and_<is_integral<Integer>, mpl::bool_<number_category<Backend>::value == number_kind_integer> >, Integer>::type
integer_modulus(const number<Backend, ExpressionTemplates>& x, Integer val)
{
   using default_ops::eval_integer_modulus;
   return eval_integer_modulus(x.backend(), val);
}

template <class tag, class A1, class A2, class A3, class A4, class Integer>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<mpl::and_<is_integral<Integer>, mpl::bool_<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer> >, Integer>::type
integer_modulus(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, Integer val)
{
   typedef typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type result_type;
   return integer_modulus(result_type(x), val);
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, unsigned>::type
lsb(const number<Backend, ExpressionTemplates>& x)
{
   using default_ops::eval_lsb;
   return eval_lsb(x.backend());
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, unsigned>::type
lsb(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x)
{
   typedef typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type number_type;
   number_type                                                                           n(x);
   using default_ops::eval_lsb;
   return eval_lsb(n.backend());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, unsigned>::type
msb(const number<Backend, ExpressionTemplates>& x)
{
   using default_ops::eval_msb;
   return eval_msb(x.backend());
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, unsigned>::type
msb(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x)
{
   typedef typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type number_type;
   number_type                                                                           n(x);
   using default_ops::eval_msb;
   return eval_msb(n.backend());
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, bool>::type
bit_test(const number<Backend, ExpressionTemplates>& x, unsigned index)
{
   using default_ops::eval_bit_test;
   return eval_bit_test(x.backend(), index);
}

template <class tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type>::value == number_kind_integer, bool>::type
bit_test(const multiprecision::detail::expression<tag, A1, A2, A3, A4>& x, unsigned index)
{
   typedef typename multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type number_type;
   number_type                                                                           n(x);
   using default_ops::eval_bit_test;
   return eval_bit_test(n.backend(), index);
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_set(number<Backend, ExpressionTemplates>& x, unsigned index)
{
   using default_ops::eval_bit_set;
   eval_bit_set(x.backend(), index);
   return x;
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_unset(number<Backend, ExpressionTemplates>& x, unsigned index)
{
   using default_ops::eval_bit_unset;
   eval_bit_unset(x.backend(), index);
   return x;
}

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<Backend>::value == number_kind_integer, number<Backend, ExpressionTemplates>&>::type
bit_flip(number<Backend, ExpressionTemplates>& x, unsigned index)
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
   typedef Backend type;
};

//
// If the exponent is a signed integer type, then we need to
// check the value is positive:
//
template <class Backend>
inline BOOST_MP_CXX14_CONSTEXPR void check_sign_of_backend(const Backend& v, const mpl::true_)
{
   if (eval_get_sign(v) < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
}
template <class Backend>
inline BOOST_MP_CXX14_CONSTEXPR void check_sign_of_backend(const Backend&, const mpl::false_) {}
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

   typedef typename double_precision_type<Backend>::type                                       double_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type ui_type;

   check_sign_of_backend(p, mpl::bool_<std::numeric_limits<number<Backend> >::is_signed>());

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
   typedef typename double_precision_type<Backend>::type                                       double_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type ui_type;
   typedef typename boost::multiprecision::detail::canonical<Integer, double_type>::type       i1_type;
   typedef typename boost::multiprecision::detail::canonical<Integer, Backend>::type           i2_type;

   using default_ops::eval_bit_test;
   using default_ops::eval_get_sign;
   using default_ops::eval_modulus;
   using default_ops::eval_multiply;
   using default_ops::eval_right_shift;

   check_sign_of_backend(p, mpl::bool_<std::numeric_limits<number<Backend> >::is_signed>());

   if (eval_get_sign(p) < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
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
BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_unsigned<Integer> >::type eval_powm(Backend& result, const Backend& a, Integer b, const Backend& c)
{
   typedef typename double_precision_type<Backend>::type                                       double_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type ui_type;

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
BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_signed<Integer> >::type eval_powm(Backend& result, const Backend& a, Integer b, const Backend& c)
{
   if (b < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   eval_powm(result, a, static_cast<typename make_unsigned<Integer>::type>(b), c);
}

template <class Backend, class Integer1, class Integer2>
BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_unsigned<Integer1> >::type eval_powm(Backend& result, const Backend& a, Integer1 b, Integer2 c)
{
   typedef typename double_precision_type<Backend>::type                                       double_type;
   typedef typename boost::multiprecision::detail::canonical<unsigned char, double_type>::type ui_type;
   typedef typename boost::multiprecision::detail::canonical<Integer1, double_type>::type      i1_type;
   typedef typename boost::multiprecision::detail::canonical<Integer2, Backend>::type          i2_type;

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
BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_signed<Integer1> >::type eval_powm(Backend& result, const Backend& a, Integer1 b, Integer2 c)
{
   if (b < 0)
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("powm requires a positive exponent."));
   }
   eval_powm(result, a, static_cast<typename make_unsigned<Integer1>::type>(b), c);
}

struct powm_func
{
   template <class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR void operator()(T& result, const T& b, const U& p, const V& m) const
   {
      eval_powm(result, b, p, m);
   }
};

} // namespace default_ops

template <class T, class U, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<
    mpl::and_<
        mpl::bool_<number_category<T>::value == number_kind_integer>,
        mpl::or_<
            is_number<T>,
            is_number_expression<T> >,
        mpl::or_<
            is_number<U>,
            is_number_expression<U>,
            is_integral<U> >,
        mpl::or_<
            is_number<V>,
            is_number_expression<V>,
            is_integral<V> > >,
    typename mpl::if_<
        is_no_et_number<T>,
        T,
        typename mpl::if_<
            is_no_et_number<U>,
            U,
            typename mpl::if_<
                is_no_et_number<V>,
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