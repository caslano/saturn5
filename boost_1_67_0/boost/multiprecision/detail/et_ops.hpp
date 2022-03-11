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
7Bt6miQ5NI8U4zSv479HB963bERoueQR+8LPwPThW/tlYtZnXA0bniYxI2NkjsyUnJYxMkNiTs7I/C/1+8bAvPH1x/clc+tiFsZMHDYZzc7TsO5QQlsneoRH61k+ZPzucFKn3SXpTomweMiEehaedTAOPrf7a0O1Oe6YrD1+Vo71TxsWkwBvhi1bddP8NNI7hHL/PX7Lcb4D/ParNaHAHTYQb7gU03GW8t7pcECvudbZ7sm9JfZKas6Bjo65o82mOtg11FOv/da4hKzzCE6buBTZhhfB2/sqj30bRyCM7wd9IpMFsKheB1IlaSH2MWOOtC1BCBORIqohDEj6cyfgQDiDkD55321btrk96CZ0RV4URJjk+HBHnix1JspXX8qJl9WoQgQ605gei2ohDWP3wruSehh9tpw+FRp/qwrdyTWIMgPdfVr+Mgxtyxe1JC2tIzlmst+LNNPRamY6BjSWKRm76SCP9ntCrN0ajx6ykNO1xi2tLggzLGhk3BpMDnLDQe2pQPhLnhv42tG9towipwC605/OXoxY18ysparl2krDr1aptsLPL0gfGXlpZg/4gjK3W2D5ishFBKrjLr5ckzfT29ay+zoHSY5Vj7Wv+gb+YNFIGbLTgawPb/WrJoQtn3vg7u0WPGAIPiXoBawPig7FqxJCQ80KuoFzl+L77G7kMQ9+RR9fMprnH8kPc+gxMQk+4QfEhLgEn9AjYlJ8gk/IMfFfUZj+Cz7+BV7g0n4JIcoQ2zBmHQbczmkRqtdpPlbuyUJDlBbzFN3FhexiEpin3ad2qhBt/S9c4D8DdVonnFxiCbKY6Pv2FRQFVSg7+8n7AlAU8TlQysxyQlAsBdvWOEHfpfTzSpqdF3tOTTM7RaG7xT1S5bsV+NvNh+rt0UlrRprXduFRnRp9zroCe94gWveczUrbz6qi8kv+DpQlYXjBdqVnZKHrnKdD1FZOPH+G/ljAVzvTt4MFfuf3lqeFr6mDoEWtMw0QAvcg7H7AgEt0QfFRyT/3/KJ+gP6mJ05OfRS32YCBXwAARjgAhQ9AgPo37yqRz7yjzsO/4Ktx+Q3K3rIyfc2iMC1f4EewkkAyefNsbgDiQMlViC4WN+1EaBinxxUGGoSo+cl9YSxXYz5syAxrVeEM2SoK0AoRk3WEMqTbzSNHVFPar60t8RCmt5fNn9HillVCaTUBo4OTZZUEPE0f+qU6h1QaIpaB9wUsAGG3CTRiqHn2NbvGf1AlQftfYETOBnoC2E6N+oBt2gF4xUNOGMKTTds+0EYK61JYAFmaVeN0gKaxvWQV6PSq/CjZo4lUB+Nk5+tkQOGvIxSbpPNVuJLL3ZJfatVK+D+CDfVoLze7oyM1Xr7rsbfnkxZaHaM0kOfuo1Y3GhcmD6FV0MhlME7oANNcdNV4bcbvtQKmRh4Y6B9ofgCnCctseUttJKfXll3KPS7PYac9mRiUeI7lEjM+mdMBd/Sb6B4JwF0AQocXHuWKVYjJC89odABTpw2h14PHEECK9Prqf3J6enKvJcPn0+Zjuu5eUIj9fvPnIJT80dp1PHgHAOuvYxxrt8OSavMGYKSAvMzib2J1gAwforfb+lvZ/WBU6cYB92VnK3mnp5Tzy3SaYqu69xMzFa/dk2zkgC2x6VtDalHan24NGP+g5BwlBYPzhMp9OKFryz62K4DxJpXzpQk80vCF7dCRiYhOb5r4eCV0T8tJs94sUEuXf7ZjgB3WLH/DxdIyEoErFn7MM+j5jC4Jr1KIWBR258Txq2d329twJZ7C3ueiSUc88231eB0vaTQQYOa+SzkoKJAYx9tpxzr3eIffs2JgIFGiy69Vz/QALTaDJhmS8I7tcHPADxAgWj5A0Ug8GcF0iv0sg3LA6JgFf7CPbEQmANO9BR4g6XxijRh07OOOeDO13xNpm/hGJ9JKQUWgCduCJ6xCaQfpiDLFij49BV/3xTyyEUMyP4PBWEGmKw74rzWGydD0ktAVhn/PkpBc3VRCvd7rV4A7Y8oJFZtyVT7lo6owpig4us5n69DLOM1PAW0AYcUWZx29IeSAPYhSz9z8KHF0FAs78HphBgQKcNY12Pg67aJqsNc9+iLSTdmNjiwfJ+YjykBaRAk31v303I3ZzKCGYd2qox3lEhGZbXErbpM2kpFs7Wzz1wBH1WPv0DV9Ogjn9PB4/YwvXa8YXEK/EaWRh6mmZYsPZkyrv7APDqQw2bg+2eeqHP3e3k1cFi8XMb5WnjnT23EInegXu25V7ffg6I7wzi6uyv5F5SBoM+s1aQTzgOEF2rmgz71423SjHwCV99Lc7N9O35bkoz+WvCDbImaB2va6EHn8UXHMw3V6VaIA2ajHo3v1N4uBRiP0Q1pCnJJ6k3wPfkuJQKUITBkPNpfwfFQh/+R9lOovwS1KhyAi3xLxQ/fPp4hAJEZTiKLIrOGfKcv5LAFvm90ncYPgCcHnJxM7SOTsIk9YcahhV3nCd8xTGNgGYS08VDbV1cfrlIz+yaQwPyCnopii+n6RFmQUc0yE7A17h2DGCoUjyUbGiPwman+Evqo2pjXaNdJd9D87aKp9xRepRFyDwnIfUVPEPYXKlLmYZVZBANNAV/7ABicmBwf7Uv1S7jbYd5OTh3YBkNFnDlBhWtZW2Yx/tL7AveqyZ21C/mnX69xZSvnnmzS+UQvNifrg+pGRKrybVdovzqTcBe2JzsWMQ+mhC0UdQlfanDa0+yWrJv8LagQK2Z2aqglVOawqIliAYk4tipy0Dv0wjfaso5KBxhtY2LywX4tqfLxTA7H80hYzulM9nBaxp0yz60tafBpBg4tG1nannUYwY595zNFWZ6ySZ7qkjabZomEmZ/XNo/iRBwCA+nsR5tXr0ekR91UTFh2SJ5YvFj3KI9NLLsys6FBvknfWk9am1rGuUitfTWnNaU13q3WLfgXGbYwLnsXKBcvV7sTQDbNrvOXbwfaqzwvVK9KL3XX11dhTyq/qk/efB7A1sO1ntmDAYCTB5MI0w2rFiMNciPGJfYzlis3DtsYQx7xjumX+tTAyTDJatHDaUxld3mLZa956dmfmZU7TjN2gdW7s6PoAe6J7Qp96TndMu9F3GwsyOjBvWCkaOwwuTSXda1xx2pQaolqtXLUKETQFYZDCSK9ZWJ1dxa6W1+xraWhGXMdp+5hZnWfbeI24WXa6Ock5iZ0au1m+znB7cSt+dfnS+AJ+LYarhJMJBwsfi7uMsxkjG5Mk1y0nKS+Wm8uVzfmYvZl9omOju9KZ7SCqxasVrQW2Y7IrtFuxi99e2Ube1t4256XhWfXKeRLx/vS4fcR5UHo08mT1nvHS9qx7un0h/AD5UvnieV15Ovly+xrw2/Xr+sGrntcZ0F64gP/u+Xb/4oeZh9NAvjcmIGMgqCe7l0ywVNBT0Gcg5SB7l7i/QjhLWEz4KuQqHJzPY5ioP68/rf9wWLtvvF+AOIpwRVwjQiXqSNRVXK+oryir6Ei1o36rzolojaCLwdMr7aHyXkldgapSVsuPS4wxHM2JEB0LG8OL9J17NmdjODvsPrQ6MtOkq+6pNrcRd+P0zjIeozySGd0aSR+RJ10nvZbLkHORqJbIOeh0qOqgT+JJvkw6Tf5Jhif1l4KUt5QeKR0tyzueuE/y7LGctNywDL74vAi9KLa2Wb3WZJ56O2A3FcCsYuoEUVmYU+lTEG8X5UizzNdM/iCjprkSaXVho+/iF6c39541qfW+bbNWtNa09n5UeWI7ia1x1lLvw9PCb+s1D/4MC4JFxuZlw9sVWU/pvij3Sf5u/FbPHmJ3R6dAtaHB2DtsKC1VKErQ52hccbPeYVtmu20NvDndqmr1pzFC16Vlo6yl8NMfpOr4jL1gT93z2UTsMy5YbnT5k5uW25090IXrgkuXTD9Ji7173dpRlKOnp/JvITebS40yRXX1hvQO9Ran9qXuqmSpdFPrqZOr7tU90llSq9Lo6nHzw/fem/cb+6lxlXIdcb2Dc4Df/vdWcWcxb1XBEcGZ4XkvaaxhvNcWY5+djZIVlc2Hc4iLxYvj0t62UdnxEXGYuIjWLrrO5MvyeR57p9N3ZcVqU2Nf3IKKDzwWMpbnh//1c++Yf8RLjkGu5T//Xdiau6i3DOh67DLtRuYW5ybqBpv3zLexZLu181u8EB8u9y+vkpPWu/MZ5kBmIFPe3HluNlean92Z7+DbQ15m7gcaEd3uBewVTue5w+Mj6asU2lfO15x+S5fPdeR0cqIqpip3jabO9Vn7ue3P5EH5K+BEYMy16kqXvdreBZ4On4f5mMHlt+xqRrqt2063q+fwdd/h/D438TxxgfuaW9ld+ba3Pd3T/uB3FPwcXBS+FE+NR8ln+b7pds62OK24fExn7BMfnL+XfxbL/1V6lP6OHCovIV9FplKGTT5TNjfLLb/3weVkKdL8Yg7NDMo/9bfltWP2Cd/P+bvGn83I7RD0b6R8T1pvso/n2WqjKq8joEO8Tlmffhq9J9Hf+Z32yHav6949GVrzruGOmv/c7/z3/OlhoHxZPv8XFDjj6btz+HwJAAAA0kFC0xkAABrxvwPQ30Q/8T8klouohouyvZmLu6GTKYCCoaWdC52cqAqBGzMdKx0jA8OzUyEAAIKmpIigiofeTfabtoo53siHPBsjdqkEphcqimDlulHkxrAeAGWRUTRtlEZ90UKFpAhpJ2m2nVE0KvRrEAFUxfoI3Og1Xx7vWW4HsJkra9fcbdN0Mv6sR+ZX797dx3ZmB/Pbtjo7gF0tDTB7p4Nzofdm51eftAa0eoLG46mPPgVbW07QzJO+tM7X23HRFPzhqZ7o2SB1jZYRwtSVJKk/evZW9j/SWMgnela3LM3wc8qzhQPff52pl92GCNJGCydiDR0XtBuWbrhE5KpENtuWIbG8K52iYA0RkjZgDGajnCFn+SISt4jpCRrDxyAxWVqBCd1DEDgte6QkaIycgMRk+SIGbpg2xO4dIcNEZOQG5yHE9abXQW/zNXW1hjhffct192T/nSj8CD/I7kvdDeb/JW/F/879zX/lmTdCRAb8rmUEGTR2E/52T3uPcf/yxJowp5wH3OfZC/bw8RemNy+vF6O3r05jhJQNCIOjDFZnuFe8460/+NNTl8UasEX7LCNYFQn4F/qLvI7mqg+yuKgs3fdIHykqU0eKeP9S4gqxj58n7C+gPdjC/LlJh0foLs2TdZsSLgLQ1cv6mPL+arfqvv3rflJxVGH7wvCDg3c89EgaL9f3TPc/K2BXRw7twM8TbiuoDdtqgmpM7F6FKes9/o4gnX3A2hzqcezyvPkHvvidxsobbuP2qmzfdZ133Yj/7obUEy1IY2SV3I1nZ6u0OuRPA/jR65scvOkkpC1nQ96QwW1IAs/2SBBDDiuhN+Rfbz0Mb2HfPFKbqL1vO9xUTep33pNfnmaM88Sypzelt3Vp/JIKPvEfYTcQNHOP/5X2T/YSrL1nIDzAMXyf04gb3EZsayB7wQ6CPz6FW98KHg9WMrlb7F6G2wibsOL5hkXW9DogPqUDuDeTf9A9RddPjPtm0iuw+ieO04zO+l2i+t/mLuaWLP2Lir3nPU7vyoU0Hm3f//i5iK0tBTkO9v819Ij7TnTwyYbbiHITbhvwXWfzgNmbHeCO6W7v8+VKbUDezezaZ7ZCF3Rb+sZ7N70LlJ3cgP7TscxXBix+OzC1wutbW1agXXme2bT1qkj38mpy/3rOHY3mmcgnqXukuTNCiP5rH3r3xQJ8QUjwR8m78PYgcXPYj8+5Jya/NUnUvZfak63YoekNj31tPNBj2xNHNg1Zt0dh+AQAeoIjsojRHTCGf2CxVR9vf/SntM45BZHMqdOqtFxpO0nJzOvV/IoBv5vmHU1eG98ZLT6LyB2t8/lvfLyYb5jbLwgJ/ji6mSYh2qKDWSzhye9OFjbFGVBpjR9+bJwCxN8JsPGLAoV5UNORTxkA34lzQYXH8EXXQ4wh0snwxENKJbf98nC+WNWcB0fxmVmFHjXjWVW1eYEeJ2XlX9LAPR8maJh3jxX1TjR3RwjQGHs2ZiA9kuTxjgN8eZC+ONpjkD9O8h0DHL5Tk0cON6ycMgzEPVLiGz8YsxIIM7kFM5IjcnygEu/yxVBWDCctReR5jdeaoYa/hbxmN/cMJzGZxZ1VhVtUmF2+IQfx2HuWlXtOBtKUZ+NHCY9k8U5WrE0yH275bOoMIfdRQ5EZHIxAN83xA8fGg++nOUJeM0/uZ7lg9nKI76d4obbOjXlu8MT325EhVk1XQPSY5Xhi7yfMLbBas59P+f97P/emR9Qjh7eN9pyJmdl4+r/NbYRxBId51NRtelqGkbkJl5nZeXo6ruPJ98/z9gZvm4/3ivl+H/ecMlUvVWrTu6antUTpr7Zlolv/xfUGiRQpmKL0lhcPmSWW8z1TxPCCbzjGLEi1mtW1vI+zhZP1mJPSz0pHam9/ZpEcYvYpHOnuFVq/RMc3qlfvo3ZgKzjmzZ0PNrjHVLF8NGVaH4lzwP4ezm7EG9HtlNrd+UYZCv1PRPZhBH0kgwB2GKF4Nu07mYC8UIWQzf0KJasUKzNp83ZuGUZLa1Tw5BfS98SE19ZMJKTXvrvKk1xyYt0ma97vXxW3JS6jAWqLPpWrV1Rd7W4Cvc70y1zBNxcJsyp0Z1FzX9m/z1tB3INRLKp/ADVGjLo1V0DZRgArL0B9LAm0Gzvk4J66k09nqXQKgewln1c+FpPuhxpIwIkIurMKm0YTA3q9vZFp830B8d9f2Kikws4i+vO5MXnsKDU+pB1TiWXMxuYOPRsx0U2/2h+2oz/qoJ1Cu81M30o0xubd9uwy/4bHQjXHRJIoLK6RQSbX8otEj6SJaXYPaPiUQc6fM+WOeRtEMTqQbdcYlTnupPPYw/U+p8LL3vv/cTGe/Gk9pWTQJONNF/NXg5/MvmiFY3kTY5JhSmTrECoytX6QXjuOtd4azFnYSrCKbp3wpwvtYU0HxVTPtVEVSafMPWXZSQ+voeWo+TUe1vk5Qkr8bFUNX9mKSp221v3RiKsTm5dkaSuZrW75j53fBX3bRGHlNTpyDF5/OMgFxCc22yGPWpA/JldaXl4l1jArE/+460aogXkn7iK0ZZziHnPcwE4gWratr5IfZoayPpSdR3+bX4ZfZGtmDIV594PlglschXDYP1Ie19ti30iu8GlKTL9VyFX+uMscNdV9nMqrsR5FWgZ/9KEJDb3KndQRdjKUfhk2U3c1THE1zOQ+321+MOpR2OHg+9FIqSmBrYDqp28ok7ItSb4IfPc319hbeSeFbLnXOHR8OrsLf4zJqvb6wKtlewZj3Um3lwwOqyHPlpyk9jvnL+4OOQWhIW/tQTIwqjJZpJ48leOn87ZKTwoMg9DiFX9qZmG7GTCfSrts+X9vSGlonq8Lpo5lR2Iv69cVLfOavwat+CqBsjSeU6Amc115qldxpf3tiOs1S7p2xwsgpXcLiF2MwNwKvhC1JZ83kcZvvG2Wjui8UrQxPr+x70dmhMJMaRe/XrjAp/xFIdtJ2UfojJiIJ4NXd4R5jrtNvZlnZE26P5sZQF/uOGOKlkCy7TL9vOTHLZ2nxJAWGbCPZ5t8am/7686JyrvU1J7xrUN7845qG7I616M3xHzHfly2foftKhfV0QRHYpWmTtT1+s1KR6fs9ZWBNbsTJYYX84tnjna9bRB09pVcOmgNYRiHTvOoRcq3zjX9OPou+V2u6dPv0OH7egnLUM51grU+NcOb31n+mb8TW7fyUtIrhuRu95aNiTmv33tfxYm+Mf/izl5gHJxnVHCs+JJKtFK/76gyepf4gH20pqlzUa8mYMt6ys2sHH1XG4uh0DH+VOuuWDce8h75f7IL/YU8J8X/8KoaArnVFZHfcymay2gqre1raec+nSm2wfaK8sqFve+6Dks8pZj68krViqcrbaYfx1FUKakvCxUfJcWyP+fxXsTuXBzf/nEkpjBWUJUhx5A8Z4g70x9f2UogicICpGVRpLGBlYch42VCXM98qcRqeiuvkcX2c2N4DqRWlSDN4XdsAl5JVfUHryQjqWPV9UEXNUsCPDZ6k/T+PFCZN8sYNMO+3fFvt8eVe0ucvikPefBD6TUdPXxeYL3KQ0LksaJAYggrwNiyEhDvd4NBdHstnQEm+BPtKvq4pyiYcGFEvqNmqYhQcJUR0vP+3LyDXa0BqpK8zWI5dY85WwWHeQ11v/OrUe1HxJB1kpWvxeQpSZdsxz7zIxg9QI9s2sZEsW+762HgGaTuZ2m6W7KSU6zBtQP2Y0CYXQhjmbdyvElExpht7KdPfSA9oI1E0SGUslTlMGMj4n92ik6wUyIsV19t8k+gf4zhkz93fGtv2lz2+R3dZVMOcp2uM3O9isTKAaoH7C1JfhjHImJH9m0o8YWWV3tuZGa8hoDcxqjdkXIGDmTQ/zGFWCHHAjmRR2x+Q06jU7Q4vcXbQH7lsLGxso/iadAkdceQChMj7I5lUySX/RmvCSuTrfxGKNDySDsfj1geovZd4wdbQMiXF3DUoeKyVqX8ZwfHlw1wkq2Fwe8ut3q+DAHn/5rT8I9iU7p8ZZlLUzvnwwRxDG6tKXOAFkfUfdgMTgX1apan9K/5J/wYj67pK18ZJYAzi7FU5HDxQGFgA74ifShjqrWM0IewSxaiKZ/Omn+E+5A3cyiWx4oGH2NJNFMVK02T8/Y7hkZdVLFbFP1rHF0nreryXUluGXS2mmJBdVOIKgPlEFYgggVbsMULxlskKmW1MAN9RmPQ8l1kdoF/NzUM4+WRazlV6gZzLyWCXogFh51dXMKTAMbmy50UW9rYcAu3ZRWp3wLjrca6e9ZS7juW+QXHFqNzSlzmOvpnfC6nXdVgScoJDEpO6GLLC04+uRHzqIVCceSEmzXC502ECE+WFC/503Sv1FJli0+EOnmtcTZd8OE0wD92lOeOBZ/d2i8/l1bq1OCdMYSEcQUiILQGK905jtFZ7JtqPnkSr1a1uZT3uLnUzeoi2FhnFemEbPXgrL19DjxyccSWbyys7iIahbTu68jRKFrSYpppOZ1188zdIF8jOWVPmRtnN1+hDbOQB4VgY2rT8EDjumW5dmVMzqP+7l59L/onWgjqOLQ7T7cepR+S9iO3OR4NI3pKdE9KNjVjBStEhgDrf+TqZwSpwkIua78Taj/ClBazq53TGPZ5WD4=
*/