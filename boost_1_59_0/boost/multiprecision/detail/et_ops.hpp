///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_ET_OPS_HPP
#define BOOST_MP_ET_OPS_HPP

namespace boost { namespace multiprecision {

//
// Non-member operators for number which return expression templates.
// 
// Note that operators taking rvalue-references DO NOT return expression templates
// as this can lead to dangling references, see https://github.com/boostorg/multiprecision/issues/175.
//
// Unary operators first.
// Note that these *must* return by value, even though that's somewhat against
// existing practice.  The issue is that in C++11 land one could easily and legitimately
// write:
//    auto x = +1234_my_user_defined_suffix;
// which would result in a dangling-reference-to-temporary if unary + returned a reference
// to it's argument.  While return-by-value is obviously inefficient in other situations
// the reality is that no one ever uses unary operator+ anyway...!
//
template <class B, expression_template_option ExpressionTemplates>
inline constexpr const number<B, ExpressionTemplates> operator+(const number<B, ExpressionTemplates>& v) { return v; }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline constexpr const detail::expression<tag, Arg1, Arg2, Arg3, Arg4> operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return v; }
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, number<B, et_on> > operator-(const number<B, et_on>& v)
{
   static_assert(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
   return detail::expression<detail::negate, number<B, et_on> >(v);
}
// rvalue ops:
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on> operator-(number<B, et_on>&& v)
{
   static_assert(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
   v.backend().negate();
   return std::move(v);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v)
{
   static_assert((is_signed_number<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value), "Negating an unsigned type results in ill-defined behavior.");
   return detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(v);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::complement_immediates, number<B, et_on> > >::type
operator~(const number<B, et_on>& v) { return detail::expression<detail::complement_immediates, number<B, et_on> >(v); }

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            number<B, et_on> >::type
operator~(number<B, et_on>&& v) 
{ 
   using default_ops::eval_complement;
   eval_complement(v.backend(), v.backend());
   return std::move(v);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_complement, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator~(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return detail::expression<detail::bitwise_complement, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(v); }
//
// Then addition:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >
operator+(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_add;
   eval_add(b.backend(), a.backend());
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), b.backend());
   return std::move(a);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, detail::expression<detail::add_immediates, number<B, et_on>, V> >::type
operator+(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, V>(a, b);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator+(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::add_immediates, V, number<B, et_on> > >::type
operator+(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::add_immediates, V, number<B, et_on> >(a, b);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator+(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_add;
   eval_add(b.backend(), number<B, et_on>::canonical_value(a));
   return std::move(b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator+(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if< 
   std::is_same<typename detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET> >::value,
   typename detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a += b;
   return std::move(a);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if< 
   !std::is_same<typename detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET> >::value,
   typename detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if< 
   std::is_same<typename detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b += a;
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if< 
   !std::is_same<typename detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator+(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Fused multiply add:
//
template <class V, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>::value,
                          detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >::type
operator+(const V& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(b.left(), b.right(), a);
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>::value,
                          detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >::type
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(a.left(), a.right(), b);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >
operator+(const number<B, ET>& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a);
}

template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   a += b;
   return std::move(a);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a);
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type>::type
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b += a;
   return std::move(b);
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type>::type
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}

//
// Fused multiply subtract:
//
template <class V, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>::value,
                          detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> > >::type
operator-(const V& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >(detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(b.left(), b.right(), a));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>::value,
                          detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >::type
operator-(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(a.left(), a.right(), b);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >
operator-(const number<B, ET>& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >(detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a));
}

template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   a -= b;
   return std::move(a);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >(detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a));
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >
operator-(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type
operator-(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}

//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, Arg1>
operator+(const number<B, ET>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(a, b.left_ref());
}

template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   a -= b.left_ref();
   return std::move(a);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type>::type
operator+(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(a, b.left_ref());
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, Arg1>
operator+(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(b, a.left_ref());
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type>::type
operator+(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b -= a.left_ref();
   return std::move(b);
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type>::type
operator+(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(b, a.left_ref());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >
operator+(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator+(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), b.left_ref().backend());
   return std::move(a);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(b.backend(), a.left_ref().backend());
   return std::move(b);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::subtract_immediates, V, number<B, et_on> > >::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, et_on> >(b, a.left_ref());
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> > >::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(b, a.left_ref());
}

template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(b, a.left_ref());
}

template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> > >::type
operator+(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}

template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator+(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >(detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a.left_ref(), b.left_ref()));
}
//
// Subtraction:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >
operator-(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(b.backend(), a.backend());
   b.backend().negate();
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), b.backend());
   return std::move(a);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, detail::expression<detail::subtract_immediates, number<B, et_on>, V> >::type
operator-(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, V>(a, b);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator-(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_subtract;
   eval_subtract(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::subtract_immediates, V, number<B, et_on> > >::type
operator-(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, et_on> >(a, b);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator-(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_subtract;
   eval_subtract(b.backend(), number<B, et_on>::canonical_value(a));
   b.backend().negate();
   return std::move(b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator-(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a -= b;
   return std::move(a);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b -= a;
   b.backend().negate();
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::minus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator-(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, number<B, ET>, Arg1>
operator-(const number<B, ET>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, Arg1>(a, b.left_ref());
}

template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::plus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::plus, number<B, ET>, Arg1>::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   a += b.left_ref();
   return std::move(a);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::plus, number<B, ET>, Arg1>::result_type, number<B, ET>>::value,
   typename detail::expression<detail::plus, number<B, ET>, Arg1>::result_type>::type
operator-(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, Arg1>(a, b.left_ref());
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >
operator-(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >(
       detail::expression<detail::plus, number<B, ET>, Arg1>(b, a.left_ref()));
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >::result_type>::type
operator-(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b += a.left_ref();
   b.backend().negate();
   return std::move(b);
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >::result_type>::type
operator-(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >(detail::expression<detail::plus, number<B, ET>, Arg1>(b, a.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >
operator-(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator-(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   using default_ops::eval_add;
   eval_add(a.backend(), b.left_ref().backend());
   return std::move(a);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   using default_ops::eval_add;
   eval_add(b.backend(), a.left_ref().backend());
   b.backend().negate();
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >(
         detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, V> > >::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, V> >(detail::expression<detail::add_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >(detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}

template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >(detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::add_immediates, V, number<B, et_on> > >::type
operator-(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, V, number<B, et_on> >(a, b.left_ref());
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> > >::type
operator-(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}

template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator-(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}

//
// Multiplication:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >
operator*(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_multiply;
   eval_multiply(b.backend(), a.backend());
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), b.backend());
   return std::move(a);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >::type
operator*(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, V>(a, b);
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator*(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_multiply;
   eval_multiply(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::multiply_immediates, V, number<B, et_on> > >::type
operator*(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::multiply_immediates, V, number<B, et_on> >(a, b);
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator*(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_multiply;
   eval_multiply(b.backend(), number<B, et_on>::canonical_value(a));
   return std::move(b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator*(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator*(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a *= b;
   return std::move(a);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator*(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   b *= a;
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type>::type
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::multiplies, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator*(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >
operator*(const number<B, ET>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(a, b.left_ref()));
}

template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >::result_type
operator*(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(a, b.left_ref()));
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >
operator*(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(b, a.left_ref()));
}

template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >::result_type
operator*(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(b, a.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >
operator*(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator*(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   a *= b.left_ref();
   a.backend().negate();
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator*(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
         detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   b *= a.left_ref();
   b.backend().negate();
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type, number<B, et_on>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type>::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
         detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}

template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> > >::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}

template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}

template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> > >::type
operator*(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, V>(b.left_ref(), a));
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator*(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(b.left_ref(), a));
}

template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator*(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(b.left_ref(), a));
}

//
// Division:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >
operator/(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator/(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_divide;
   eval_divide(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator/(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator/(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_divide;
   eval_divide(a.backend(), b.backend());
   return std::move(a);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, detail::expression<detail::divide_immediates, number<B, et_on>, V> >::type
operator/(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, V>(a, b);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && !is_equivalent_number_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator/(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_divide;
   eval_divide(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::divide_immediates, V, number<B, et_on> > >::type
operator/(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, number<B, et_on> >::type
operator/(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator/(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator/(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a /= b;
   return std::move(a);
}
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator/(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value, detail::expression<detail::divides, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator/(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >
operator/(const number<B, ET>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >(
       detail::expression<detail::divides, number<B, ET>, Arg1>(a, b.left_ref()));
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename std::enable_if<
   std::is_same<typename detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >::result_type>::type
operator/(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   a /= b.left_ref();
   a.backend().negate();
   return std::move(a);
}
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename std::enable_if<
   !std::is_same<typename detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >::result_type, number<B, ET>>::value,
   typename detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >::result_type>::type
operator/(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >(
         detail::expression<detail::divides, number<B, ET>, Arg1>(a, b.left_ref()));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >
operator/(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >(
       detail::expression<detail::divides, Arg1, number<B, ET> >(a.left_ref(), b));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >::result_type
operator/(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >(
       detail::expression<detail::divides, Arg1, number<B, ET> >(a.left_ref(), b));
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >
operator/(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator/(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   a /= b.left_ref();
   a.backend().negate();
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a.left_ref(), b));
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a.left_ref(), b));
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, V> > >::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, V> >(
       detail::expression<detail::divide_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, et_on> > > >::type
operator/(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b.left_ref()));
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >::value, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > > >::type
operator/(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref()));
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<number<B2, ET>, typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >::result_type>::value, number<B, et_on> >::type
operator/(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref()));
}
//
// Modulus:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> > >::type
operator%(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_modulus;
   eval_modulus(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_modulus;
   eval_modulus(a.backend(), b.backend());
   return std::move(a);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, number<B, et_on> >::value,
                            detail::expression<detail::modulus_immediates, number<B, et_on>, V> >::type
operator%(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, V>(a, b);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer) && !is_equivalent_number_type<V, number<B, et_on> >::value,
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_modulus;
   eval_modulus(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::modulus_immediates, V, number<B, et_on> > >::type
operator%(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus_immediates, V, number<B, et_on> >(a, b);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator%(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus_immediates, V, number<B, et_on> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator%(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value 
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator%(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a %= b;
   return std::move(a);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value 
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator%(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator%(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Left shift:
//
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), detail::expression<detail::shift_left, number<B, et_on>, I> >::type
operator<<(const number<B, et_on>& a, const I& b)
{
   return detail::expression<detail::shift_left, number<B, et_on>, I>(a, b);
}
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_on> >::type
operator<<(number<B, et_on>&& a, const I& b)
{
   using default_ops::eval_left_shift;
   eval_left_shift(a.backend(), b);
   return std::move(a);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
operator<<(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Right shift:
//
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::shift_right, number<B, et_on>, I> >::type
operator>>(const number<B, et_on>& a, const I& b)
{
   return detail::expression<detail::shift_right, number<B, et_on>, I>(a, b);
}
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator>>(number<B, et_on>&& a, const I& b)
{
   using default_ops::eval_right_shift;
   eval_right_shift(a.backend(), b);
   return std::move(a);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<boost::multiprecision::detail::is_integral<I>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
operator>>(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Bitwise AND:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> > >::type
operator&(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(b.backend(), a.backend());
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), b.backend());
   return std::move(a);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and_immediates, number<B, et_on>, V> >::type
operator&(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, V>(a, b);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and_immediates, V, number<B, et_on> > >::type
operator&(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and_immediates, V, number<B, et_on> >(a, b);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator&(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_and;
   eval_bitwise_and(b.backend(), number<B, et_on>::canonical_value(a));
   return std::move(b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator&(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator&(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a &= b;
   return std::move(a);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator&(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   b &= a;
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator&(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise OR:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> > >::type
operator|(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(b.backend(), a.backend());
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), b.backend());
   return std::move(a);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or_immediates, number<B, et_on>, V> >::type
operator|(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, V>(a, b);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or_immediates, V, number<B, et_on> > >::type
operator|(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or_immediates, V, number<B, et_on> >(a, b);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator|(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_or;
   eval_bitwise_or(b.backend(), number<B, et_on>::canonical_value(a));
   return std::move(b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator|(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator|(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a |= b;
   return std::move(a);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator|(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   b |= a;
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator|(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise XOR:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> > >::type
operator^(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, const number<B, et_on>& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), b.backend());
   return std::move(a);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(const number<B, et_on>& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(b.backend(), a.backend());
   return std::move(b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), b.backend());
   return std::move(a);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, V> >::type
operator^(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, V>(a, b);
}
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, const V& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(a.backend(), number<B, et_on>::canonical_value(b));
   return std::move(a);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor_immediates, V, number<B, et_on> > >::type
operator^(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, V, number<B, et_on> >(a, b);
}
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator^(const V& a, number<B, et_on>&& b)
{
   using default_ops::eval_bitwise_xor;
   eval_bitwise_xor(b.backend(), number<B, et_on>::canonical_value(a));
   return std::move(b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator^(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator^(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   a ^= b;
   return std::move(a);
}
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator^(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   std::is_same<typename detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   b ^= a;
   return std::move(b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<
   !std::is_same<typename detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type, number<B, et_on>>::value
   && number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer), detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator^(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

}} // namespace boost::multiprecision

#endif

/* et_ops.hpp
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
*/