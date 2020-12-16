///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_ET_OPS_HPP
#define BOOST_MP_ET_OPS_HPP

namespace boost { namespace multiprecision {

//
// Non-member operators for number:
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
inline BOOST_CONSTEXPR const number<B, ExpressionTemplates> operator+(const number<B, ExpressionTemplates>& v) { return v; }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_CONSTEXPR const detail::expression<tag, Arg1, Arg2, Arg3, Arg4> operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v) { return v; }
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, number<B, et_on> > operator-(const number<B, et_on>& v)
{
   BOOST_STATIC_ASSERT_MSG(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
   return detail::expression<detail::negate, number<B, et_on> >(v);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on> operator-(number<B, et_on>&& v)
{
   BOOST_STATIC_ASSERT_MSG(is_signed_number<B>::value, "Negating an unsigned type results in ill-defined behavior.");
   return detail::expression<detail::negate, number<B, et_on> >(v);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& v)
{
   BOOST_STATIC_ASSERT_MSG((is_signed_number<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value), "Negating an unsigned type results in ill-defined behavior.");
   return detail::expression<detail::negate, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(v);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::complement_immediates, number<B, et_on> > >::type
operator~(const number<B, et_on>& v) { return detail::expression<detail::complement_immediates, number<B, et_on> >(v); }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            number<B, et_on> >::type
operator~(number<B, et_on>&& v) { return detail::expression<detail::complement_immediates, number<B, et_on> >(v); }
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator+(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::add_immediates, number<B, et_on>, V> >::type
operator+(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator+(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::add_immediates, V, number<B, et_on> > >::type
operator+(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::add_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator+(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::add_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator+(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type
operator+(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator+(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::plus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator+(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Fused multiply add:
//
template <class V, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>,
                          detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >::type
operator+(const V& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(b.left(), b.right(), a);
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>,
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type
operator+(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a);
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type
operator+(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiply_add, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}
#endif
//
// Fused multiply subtract:
//
template <class V, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>,
                          detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> > >::type
operator-(const V& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V> >(detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, V>(b.left(), b.right(), a));
}
template <class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::result_type>,
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >::result_type
operator-(number<B, ET>&& a, const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> > >(detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(b.left(), b.right(), a));
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >
operator-(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >::result_type
operator-(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiply_subtract, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::left_type, typename detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>::right_type, number<B, ET> >(a.left(), a.right(), b);
}
#endif
//
// Repeat operator for negated arguments: propagate the negation to the top level to avoid temporaries:
//
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, Arg1>
operator+(const number<B, ET>& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(a, b.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type
operator+(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(a, b.left_ref());
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, Arg1>
operator+(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(b, a.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::minus, number<B, ET>, Arg1>::result_type
operator+(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::minus, number<B, ET>, Arg1>(b, a.left_ref());
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >
operator+(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator+(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref());
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::subtract_immediates, V, number<B, et_on> > >::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, et_on> >(b, a.left_ref());
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> > >::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(b, a.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator+(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(b, a.left_ref());
}
#endif
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> > >::type
operator+(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator+(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::subtract_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}
#endif
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator-(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::subtract_immediates, number<B, et_on>, V> >::type
operator-(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator-(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::subtract_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::subtract_immediates, V, number<B, et_on> > >::type
operator-(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator-(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::subtract_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator-(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type
operator-(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::minus, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator-(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::minus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::minus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::plus, number<B, ET>, Arg1>::result_type
operator-(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::plus, number<B, ET>, Arg1>(a, b.left_ref());
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >
operator-(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >(
       detail::expression<detail::plus, number<B, ET>, Arg1>(b, a.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >::result_type
operator-(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::plus, number<B, ET>, Arg1> >(
       detail::expression<detail::plus, number<B, ET>, Arg1>(b, a.left_ref()));
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >
operator-(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >::result_type
operator-(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref());
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::add_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, V> > >::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, V> >(detail::expression<detail::add_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >(detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator-(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> > >(detail::expression<detail::add_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::add_immediates, V, number<B, et_on> > >::type
operator-(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, V, number<B, et_on> >(a, b.left_ref());
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> > >::type
operator-(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >::result_type>::type
operator-(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::add_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref());
}
#endif
//
// Multiplication:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >
operator*(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator*(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >::type
operator*(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator*(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::multiply_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::multiply_immediates, V, number<B, et_on> > >::type
operator*(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::multiply_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator*(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::multiply_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator*(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type
operator*(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::multiplies, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator*(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::multiplies, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::multiplies, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >::result_type
operator*(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(a, b.left_ref()));
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >
operator*(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(b, a.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >::result_type
operator*(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiplies, number<B, ET>, Arg1> >(
       detail::expression<detail::multiplies, number<B, ET>, Arg1>(b, a.left_ref()));
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >
operator*(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator*(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B, et_on> >(b, a.left_ref()));
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> > >::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >::result_type >::type
operator*(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> > >::type
operator*(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, V> >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, V>(b.left_ref(), a));
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator*(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(b.left_ref(), a));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator*(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::multiply_immediates, number<B, et_on>, number<B2, ET> >(b.left_ref(), a));
}
#endif
//
// Division:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >
operator/(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR number<B, et_on>
operator/(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b);
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
   return detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::divide_immediates, number<B, et_on>, V> >::type
operator/(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator/(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::divide_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::divide_immediates, V, number<B, et_on> > >::type
operator/(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, number<B, et_on> >::type
operator/(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
operator/(const number<B, ET>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type
operator/(number<B, ET>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::divides, number<B, ET>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::result_type
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator/(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::divides, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>, detail::expression<detail::divides, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, expression_template_option ET, class Arg1, class Arg2, class Arg3, class Arg4>
inline typename detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >::result_type
operator/(number<B, ET>&& a, const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, number<B, ET>, Arg1> >(
       detail::expression<detail::divides, number<B, ET>, Arg1>(a, b.left_ref()));
}
#endif
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >
operator/(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, const number<B, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >(
       detail::expression<detail::divides, Arg1, number<B, ET> >(a.left_ref(), b));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >::result_type
operator/(const detail::expression<detail::negate, Arg1, Arg2, Arg3, Arg4>& a, number<B, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divides, Arg1, number<B, ET> > >(
       detail::expression<detail::divides, Arg1, number<B, ET> >(a.left_ref(), b));
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >
operator/(const number<B, et_on>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator/(number<B, et_on>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a, b.left_ref()));
}
#endif
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B, et_on>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a.left_ref(), b));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >::result_type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, number<B, et_on>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B, et_on> >(a.left_ref(), b));
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, V> > >::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const V& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, V> >(
       detail::expression<detail::divide_immediates, number<B, et_on>, V>(a.left_ref(), b));
}
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > > >::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, const number<B2, ET>& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class B2, expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >::result_type>::type
operator/(const detail::expression<detail::negate, number<B, et_on> >& a, number<B2, ET>&& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> > >(
       detail::expression<detail::divide_immediates, number<B, et_on>, number<B2, ET> >(a.left_ref(), b));
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<V, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, et_on> > > >::type
operator/(const V& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, V, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, V, number<B, et_on> >(a, b.left_ref()));
}
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, number<B, et_on> >, detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > > >::type
operator/(const number<B2, ET>& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref()));
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B2, expression_template_option ET, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_compatible_arithmetic_type<number<B2, ET>, typename detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >::result_type >, number<B, et_on> >::type
operator/(number<B2, ET>&& a, const detail::expression<detail::negate, number<B, et_on> >& b)
{
   return detail::expression<detail::negate, detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> > >(
       detail::expression<detail::divide_immediates, number<B2, ET>, number<B, et_on> >(a, b.left_ref()));
}
#endif
//
// Modulus:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> > >::type
operator%(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::modulus_immediates, number<B, et_on>, V> >::type
operator%(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator%(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::modulus_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::modulus_immediates, V, number<B, et_on> > >::type
operator%(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator%(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator%(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator%(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator%(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::modulus, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator%(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::modulus, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Left shift:
//
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), detail::expression<detail::shift_left, number<B, et_on>, I> >::type
operator<<(const number<B, et_on>& a, const I& b)
{
   return detail::expression<detail::shift_left, number<B, et_on>, I>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer), number<B, et_on> >::type
operator<<(number<B, et_on>&& a, const I& b)
{
   return detail::expression<detail::shift_left, number<B, et_on>, I>(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
operator<<(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_left, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Right shift:
//
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::shift_right, number<B, et_on>, I> >::type
operator>>(const number<B, et_on>& a, const I& b)
{
   return detail::expression<detail::shift_right, number<B, et_on>, I>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator>>(number<B, et_on>&& a, const I& b)
{
   return detail::expression<detail::shift_right, number<B, et_on>, I>(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class I>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_integral<I>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I> >::type
operator>>(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const I& b)
{
   return detail::expression<detail::shift_right, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, I>(a, b);
}
//
// Bitwise AND:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> > >::type
operator&(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and_immediates, number<B, et_on>, V> >::type
operator&(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator&(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::bitwise_and_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and_immediates, V, number<B, et_on> > >::type
operator&(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator&(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_and_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator&(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type >::type
operator&(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator&(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_and, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator&(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_and, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise OR:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> > >::type
operator|(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or_immediates, number<B, et_on>, V> >::type
operator|(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator|(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::bitwise_or_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or_immediates, V, number<B, et_on> > >::type
operator|(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator|(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_or_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator|(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator|(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator|(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_or, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator|(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_or, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
//
// Bitwise XOR:
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> > >::type
operator^(const number<B, et_on>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(const number<B, et_on>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, number<B, et_on> >(a, b);
}
#endif
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, V> >::type
operator^(const number<B, et_on>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, V>(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator^(number<B, et_on>&& a, const V& b)
{
   return detail::expression<detail::bitwise_xor_immediates, number<B, et_on>, V>(a, b);
}
#endif
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor_immediates, V, number<B, et_on> > >::type
operator^(const V& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor_immediates, V, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class V, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, number<B, et_on> >::value && (number_category<B>::value == number_kind_integer),
   number<B, et_on> >::type
operator^(const V& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_xor_immediates, V, number<B, et_on> >(a, b);
}
#endif
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator^(const number<B, et_on>& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class B, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >::result_type>::type
operator^(number<B, et_on>&& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, number<B, et_on>, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> > >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const number<B, et_on>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<B>::value == number_kind_integer,
   typename detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >::result_type>::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, number<B, et_on>&& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, et_on> >(a, b);
}
#endif
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tag2, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer,
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> > >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b>& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, detail::expression<tag2, Arg1b, Arg2b, Arg3b, Arg4b> >(a, b);
}
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class V>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer),
                            detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V> >::type
operator^(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& a, const V& b)
{
   return detail::expression<detail::bitwise_xor, detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, V>(a, b);
}
template <class V, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_compatible_arithmetic_type<V, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value && (number_category<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value == number_kind_integer), detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > >::type
operator^(const V& a, const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& b)
{
   return detail::expression<detail::bitwise_xor, V, detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >(a, b);
}

}} // namespace boost::multiprecision

#endif

/* et_ops.hpp
oLKekg/kmYCjdxEV7JewV9jr12ZLi/rET+tqjrnSdpbz1kaWnigelHnDWNGuFsa+qetxz1xck8+3y7nwCoLTTGkhQAQtuw3OFS/d3wFP2Mlui28bc+xV40IXYb9ly8eze9vzyVmc0MsO9mUFnLz16sVXvFmfnMWLPnVWe1GpJuOwBnnykzoOvEY/JYLlzActOqtUjr1xsIXfGfiOh+AMs040ylTJVzQxS6Fm4CtjZ2MX6sif4lTD+Y/gG5BD+lyNI3zvZPd4J9VBKiC+ub8ndSgmuTI6BAburbOjxSKRVBMlQmLHnb87ydHQeZWyTzJ4fniydbD/tuFj7OagY4+6O8lj0CovNV968kKuMXqP8qS70xxxrbIprYleehmA2VYlU+7RwX5y2Ls+vgmYF3pjSBtVEyvbNMmanNwyMafceE6+ntMHBnrtPJcN69+IL/PQFXvK1t1pnL50X6Vss2SyN78FLlaTNeX47mW+Ciud6wLD1Hmz8rHA5tCnd+fYq0Gn0Bi271Myjpe+Ju+n7XM8zW3hl4ClfXTi+3Anx/g0/JWUIkGWr3OyPs1Rn+9O9TnKaFUdORuTX67q1z7mPSGyakyQdezCkucNEHF/4riNd+JUVqrlsa66LgEWjrC8k5M8mb/OMRHGIt1M+JBhssdkub/OPQivqBshWu4yXNjfLfyXH5ZjOlYbx2vpxYAJvYMv0dcLOeaq79L7BoWQaMs3vRcpj1iL2sagEdDzoOcKwJB3FFLX2uuGgl66nyfvxPyk96DjF6u2tRWOA8jM7h+eHE/u5Q4LnkobV7cBeS4CMM3m1catW7hMYZwVgrVMKs9111LoW+DVB0Gf2cf76AIvOgdLpfZFBSX7fbyPJniR7iR0ywXixcbhQmnW8Zlp9laXYCWrYUakV9HjWO/vHAPnTEwc/coK/bEpCkvVZMqwdr1ap/I5e5bIp6ulilVlEIOsivvIR52lOYSCbm0nY0fH6M0Tfs8ucE2sreVNgZsjDnWQ4ASLXknNhZ7iXjEZ01cQrGTCRSVqQ3RpIRDkOmIPC2yla2U660pZ5vLA/N5Fm6WSwoaOEyxhO2I/SLCaOR543SqDbd58s9g42krmED+/RcfqU4Cl77t0CKbW0wkwckbf/YJvgFU8mlBOHlQL4qNc8O1cE5ziJV8UL8ktdc8iH7HgoRZtPmfy9qIePo7gKtZ2LU/bwAT3CqqHFwscbPNdZxyBzVeshZLgJAvKSVjQCI6O7Ih9DcEqFmwHg9txCibNHff/AqtUbL3SNcWSNmNf31301UnupZAWsRB5IG8y6iDBCabbZNeJfIp7xaSvHy+wsY6ttaYmWNLaLA9n0deWhxQGWRHsKfr7s3sW+hu8kzpIgqWDjNiz96JYJYJIUXQJ9hTdfxJg6TubrvadHndisXyijMisv1fvVXy3aSNgsDjBklkzvkWKBGuZb1vZmhplW6UM+3xrb2efMMe9brfAg4gcr2u5Cj9fgb+L4GsWvLEmxjjgF4sU7Fm0/SP+QwVe2qppbIMTys/4m1fh8Tv9XoWuBO0aF7H/12a3NHjT5WiG3+nFuGutOsG7Ud5TkTE8FxJsxbyolatlS7HTOXX23pRnZa22VRcobk54om3h3uX6IW3jBGmv3X9zzhbbeznHRiadaY2XuAWqlGgcUZn90NybyqcBxa4ir7Oz38nyYgGuUCs1kc9W0WZbBR6dlCMezo2Ipm1+B8FWLDYSVFO0kzOGomv7ewqchTVLalXg5ohDW3Ahm6CCtTGYKQ7Xu/Ed+r2L+W9q38g2TM4YyHXEfrvgKyxMYsfN9JygJnx/XvANXoRgvVqBfUXpu3D2XJG3lzthuXOrzxjIfR/XPII=
*/