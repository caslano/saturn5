///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPARE_HPP
#define BOOST_MP_COMPARE_HPP

#include <boost/multiprecision/traits/is_backend.hpp>
#include <boost/multiprecision/detail/fpclassify.hpp>

//
// Comparison operators for number.
//

namespace boost { namespace multiprecision {

namespace default_ops {

//
// The dispatching mechanism used here to deal with differently typed arguments
// could be better replaced with enable_if overloads, but that breaks MSVC-12
// under strange and hard to reproduce circumstances.
//
template <class B>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq(const B& a, const B& b)
{
   return a.compare(b) == 0;
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq_imp(const T& a, const U& b, const std::integral_constant<bool, true>&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_eq(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq_imp(const T& a, const U& b, const std::integral_constant<bool, false>&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_eq(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq(const T& a, const U& b)
{
   using tag_type = std::integral_constant<bool, boost::multiprecision::detail::is_first_backend<T, U>::value>;
   return eval_eq_imp(a, b, tag_type());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt(const B& a, const B& b)
{
   return a.compare(b) < 0;
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt_imp(const T& a, const U& b, const std::integral_constant<bool, true>&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_lt(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt_imp(const T& a, const U& b, const std::integral_constant<bool, false>&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_lt(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt(const T& a, const U& b)
{
   using tag_type = std::integral_constant<bool, boost::multiprecision::detail::is_first_backend<T, U>::value>;
   return eval_lt_imp(a, b, tag_type());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt(const B& a, const B& b)
{
   return a.compare(b) > 0;
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt_imp(const T& a, const U& b, const std::integral_constant<bool, true>&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_gt(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt_imp(const T& a, const U& b, const std::integral_constant<bool, false>&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_gt(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt(const T& a, const U& b)
{
   using tag_type = std::integral_constant<bool, boost::multiprecision::detail::is_first_backend<T, U>::value>;
   return eval_gt_imp(a, b, tag_type());
}

} // namespace default_ops

namespace detail {

template <class Num, class Val>
struct is_valid_mixed_compare : public std::integral_constant<bool, false>
{};

template <class B, expression_template_option ET, class Val>
struct is_valid_mixed_compare<number<B, ET>, Val> : public std::is_convertible<Val, number<B, ET> >
{};

template <class B, expression_template_option ET>
struct is_valid_mixed_compare<number<B, ET>, number<B, ET> > : public std::integral_constant<bool, false>
{};

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct is_valid_mixed_compare<number<B, ET>, expression<tag, Arg1, Arg2, Arg3, Arg4> >
    : public std::is_convertible<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
{};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
struct is_valid_mixed_compare<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
    : public std::is_convertible<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
{};

template <class Backend, expression_template_option ExpressionTemplates>
inline constexpr typename std::enable_if<number_category<Backend>::value != number_kind_floating_point, bool>::type is_unordered_value(const number<Backend, ExpressionTemplates>&)
{
   return false;
}
template <class Backend, expression_template_option ExpressionTemplates>
inline constexpr typename std::enable_if<number_category<Backend>::value == number_kind_floating_point, bool>::type is_unordered_value(const number<Backend, ExpressionTemplates>& a)
{
   using default_ops::eval_fpclassify;
   return eval_fpclassify(a.backend()) == FP_NAN;
}

template <class Arithmetic>
inline constexpr typename std::enable_if<number_category<Arithmetic>::value != number_kind_floating_point, bool>::type is_unordered_value(const Arithmetic&)
{
   return false;
}
template <class Arithmetic>
inline 
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
    BOOST_MP_CXX14_CONSTEXPR 
#endif
   typename std::enable_if < number_category < Arithmetic> ::value == number_kind_floating_point, bool> ::type
    is_unordered_value(const Arithmetic& a)
{
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(a))
   {
      return a != a;
   }
   else
#endif
   {
      return BOOST_MP_ISNAN(a);
   }
}

template <class T, class U>
inline constexpr bool is_unordered_comparison(const T& a, const U& b)
{
   return is_unordered_value(a) || is_unordered_value(b);
}

} // namespace detail

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool operator==(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_eq(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && !is_number_expression<Arithmetic>::value, bool>::type
operator==(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_eq(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && !is_number_expression<Arithmetic>::value, bool>::type
operator==(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_eq(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator==(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return eval_eq(t.backend(), result_type::canonical_value(a));
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator==(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return eval_eq(t.backend(), a.backend());
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator==(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return eval_eq(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator==(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return eval_eq(t.backend(), b.backend());
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
operator==(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_eq;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return false;
   return eval_eq(t.backend(), t2.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool operator!=(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return true;
   return !eval_eq(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && !is_number_expression<Arithmetic>::value, bool>::type
operator!=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return true;
   return !eval_eq(a.backend(), number<Backend, et_on>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && !is_number_expression<Arithmetic>::value, bool>::type
operator!=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return true;
   return !eval_eq(b.backend(), number<Backend, et_on>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator!=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return true;
   return !eval_eq(t.backend(), result_type::canonical_value(a));
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator!=(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return true;
   return !eval_eq(t.backend(), a.backend());
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator!=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return true;
   return !eval_eq(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator!=(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return true;
   return !eval_eq(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
operator!=(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_eq;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return true;
   return !eval_eq(t.backend(), t2.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator<(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator<(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator<(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return eval_gt(t.backend(), result_type::canonical_value(a));
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator<(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(b);
   return a < t;
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return eval_lt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator<(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(a);
   return t < b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_lt;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return false;
   return eval_lt(t.backend(), t2.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator>(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator>(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator>(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(b);
   return a > t;
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator>(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(b);
   return a > t;
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(a);
   return t > b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator>(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(a);
   return t > b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_gt;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   return t > t2;
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator<=(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator<=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator<=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   if (detail::is_unordered_value(a) || detail::is_unordered_value(b))
      return false;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return !eval_lt(t.backend(), result_type::canonical_value(a));
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator<=(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   if (detail::is_unordered_value(a) || detail::is_unordered_value(b))
      return false;
   result_type t(b);
   return a <= t;
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return !eval_gt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator<=(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(a);
   return t <= b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<=(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_gt;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return false;
   return !eval_gt(t.backend(), t2.backend());
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator>=(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator>=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex) && !is_number_expression<Arithmetic>::value, bool>::type
operator>=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return !eval_gt(t.backend(), result_type::canonical_value(a));
}
template <class Backend, expression_template_option ExpressionTemplates, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR bool operator>=(const number<Backend, ExpressionTemplates>& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_gt;
   result_type t(b);
   return a >= t;
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return !eval_lt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR bool operator>=(const detail::expression<Tag, A1, A2, A3, A4>& a, const number<Backend, ExpressionTemplates>& b)
{
   using result_type = typename detail::expression<Tag, A1, A2, A3, A4>::result_type;
   using default_ops::eval_lt;
   result_type t(a);
   return t >= b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>=(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_lt;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return false;
   return !eval_lt(t.backend(), t2.backend());
}

//
// C99 comparison macros as functions:
//
template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isgreater BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a > b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a > b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a > b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a > b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a > b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a > b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isgreaterequal BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a >= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a >= b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a >= b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a >= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a >= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a >= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool islessequal BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a <= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a <= b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a <= b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a <= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a <= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a <= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isless BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a < b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a < b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a < b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a < b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a < b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a < b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool islessgreater BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   if (detail::is_unordered_comparison(a, b))
      return false;
   return a != b;
}

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   if (detail::is_unordered_comparison(a, b))
      return false;
   return a != b;
}

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   if (detail::is_unordered_comparison(a, b))
      return false;
   return a != b;
}

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type b(bb);
   return islessgreater                                          BOOST_PREVENT_MACRO_SUBSTITUTION(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const Arithmetic& b)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type a(aa);
   return islessgreater                                          BOOST_PREVENT_MACRO_SUBSTITUTION(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      a(aa);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type b(bb);
   return islessgreater                                               BOOST_PREVENT_MACRO_SUBSTITUTION(a, b);
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isunordered BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return detail::is_unordered_comparison(a, b); }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return detail::is_unordered_comparison(a, b); }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return detail::is_unordered_comparison(a, b); }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type b(bb);
   return detail::is_unordered_comparison(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const Arithmetic& b)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type a(aa);
   return detail::is_unordered_comparison(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename std::enable_if<is_equivalent_number_type<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      a(aa);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type b(bb);
   return detail::is_unordered_comparison(a, b);
}

}} // namespace boost::multiprecision

#endif // BOOST_MP_COMPARE_HPP

/* number_compare.hpp
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
*/