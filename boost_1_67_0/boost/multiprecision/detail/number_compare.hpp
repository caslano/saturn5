///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_COMPARE_HPP
#define BOOST_MP_COMPARE_HPP

#include <boost/multiprecision/traits/is_backend.hpp>

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
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq_imp(const T& a, const U& b, const mpl::true_&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_eq(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq_imp(const T& a, const U& b, const mpl::false_&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_eq(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_eq(const T& a, const U& b)
{
   typedef mpl::bool_<boost::multiprecision::detail::is_first_backend<T, U>::value> tag_type;
   return eval_eq_imp(a, b, tag_type());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt(const B& a, const B& b)
{
   return a.compare(b) < 0;
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt_imp(const T& a, const U& b, const mpl::true_&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_lt(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt_imp(const T& a, const U& b, const mpl::false_&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_lt(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_lt(const T& a, const U& b)
{
   typedef mpl::bool_<boost::multiprecision::detail::is_first_backend<T, U>::value> tag_type;
   return eval_lt_imp(a, b, tag_type());
}

template <class B>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt(const B& a, const B& b)
{
   return a.compare(b) > 0;
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt_imp(const T& a, const U& b, const mpl::true_&)
{
   typename boost::multiprecision::detail::number_from_backend<T, U>::type t(b);
   return eval_gt(a, t.backend());
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt_imp(const T& a, const U& b, const mpl::false_&)
{
   typename boost::multiprecision::detail::number_from_backend<U, T>::type t(a);
   return eval_gt(t.backend(), b);
}
template <class T, class U>
inline BOOST_MP_CXX14_CONSTEXPR bool eval_gt(const T& a, const U& b)
{
   typedef mpl::bool_<boost::multiprecision::detail::is_first_backend<T, U>::value> tag_type;
   return eval_gt_imp(a, b, tag_type());
}

} // namespace default_ops

namespace detail {

template <class Num, class Val>
struct is_valid_mixed_compare : public mpl::false_
{};

template <class B, expression_template_option ET, class Val>
struct is_valid_mixed_compare<number<B, ET>, Val> : public is_convertible<Val, number<B, ET> >
{};

template <class B, expression_template_option ET>
struct is_valid_mixed_compare<number<B, ET>, number<B, ET> > : public mpl::false_
{};

template <class B, expression_template_option ET, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct is_valid_mixed_compare<number<B, ET>, expression<tag, Arg1, Arg2, Arg3, Arg4> >
    : public mpl::bool_<is_convertible<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::value>
{};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class B, expression_template_option ET>
struct is_valid_mixed_compare<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >
    : public mpl::bool_<is_convertible<expression<tag, Arg1, Arg2, Arg3, Arg4>, number<B, ET> >::value>
{};

template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_CONSTEXPR typename boost::enable_if_c<number_category<Backend>::value != number_kind_floating_point, bool>::type is_unordered_value(const number<Backend, ExpressionTemplates>&)
{
   return false;
}
template <class Backend, expression_template_option ExpressionTemplates>
inline
#if !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40700)
    BOOST_CONSTEXPR
#endif
    typename boost::enable_if_c<number_category<Backend>::value == number_kind_floating_point, bool>::type
    is_unordered_value(const number<Backend, ExpressionTemplates>& a)
{
   using default_ops::eval_fpclassify;
   return eval_fpclassify(a.backend()) == FP_NAN;
}

template <class Arithmetic>
inline BOOST_CONSTEXPR typename boost::enable_if_c<number_category<Arithmetic>::value != number_kind_floating_point, bool>::type is_unordered_value(const Arithmetic&)
{
   return false;
}
template <class Arithmetic>
inline 
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
    BOOST_MP_CXX14_CONSTEXPR 
#endif
   typename boost::enable_if_c < number_category < Arithmetic> ::value == number_kind_floating_point, bool> ::type
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
      return (boost::math::isnan)(a);
   }
}

template <class T, class U>
inline BOOST_CONSTEXPR bool is_unordered_comparison(const T& a, const U& b)
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
operator==(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_eq(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
operator==(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_eq(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator==(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return eval_eq(t.backend(), result_type::canonical_value(a));
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator==(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return eval_eq(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
operator!=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return true;
   return !eval_eq(a.backend(), number<Backend, et_on>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
operator!=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_eq;
   if (detail::is_unordered_comparison(a, b))
      return true;
   return !eval_eq(b.backend(), number<Backend, et_on>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator!=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_eq;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return true;
   return !eval_eq(t.backend(), result_type::canonical_value(a));
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
operator!=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_eq;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return true;
   return !eval_eq(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator<(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator<(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator<(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_gt;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return eval_gt(t.backend(), result_type::canonical_value(a));
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_lt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return eval_lt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator>(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator>(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_gt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator>(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return eval_lt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_lt;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return a > t;
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_gt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return t > b;
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b)
{
   using default_ops::eval_gt;
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type      t(a);
   typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type t2(b);
   if (detail::is_unordered_comparison(t, t2))
      return false;
   return t > t2;
}

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator<=(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator<=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator<=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_lt;
   if (detail::is_unordered_value(a) || detail::is_unordered_value(b))
      return false;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return !eval_lt(t.backend(), result_type::canonical_value(a));
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator<=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_gt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return !eval_gt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<(number_category<Backend>::value != number_kind_complex) && (number_category<Backend2>::value != number_kind_complex), bool>::type
operator>=(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(a.backend(), b.backend());
}
template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator>=(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   using default_ops::eval_lt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_lt(a.backend(), number<Backend, ExpressionTemplates>::canonical_value(b));
}
template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value && (number_category<Backend>::value != number_kind_complex), bool>::type
operator>=(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   using default_ops::eval_gt;
   if (detail::is_unordered_comparison(a, b))
      return false;
   return !eval_gt(b.backend(), number<Backend, ExpressionTemplates>::canonical_value(a));
}
template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>=(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_gt;
   result_type t(b);
   if (detail::is_unordered_comparison(a, t))
      return false;
   return !eval_gt(t.backend(), result_type::canonical_value(a));
}
template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
operator>=(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b)
{
   typedef typename detail::expression<Tag, A1, A2, A3, A4>::result_type result_type;
   using default_ops::eval_lt;
   result_type t(a);
   if (detail::is_unordered_comparison(t, b))
      return false;
   return !eval_lt(t.backend(), result_type::canonical_value(b));
}
template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>::value && (number_category<typename detail::expression<Tag, A1, A2, A3, A4>::result_type>::value != number_kind_complex), bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a > b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a > b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a > b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a > b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR  typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
    isgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a > b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isgreaterequal BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a >= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a >= b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a >= b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a >= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a >= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
    isgreaterequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a >= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool islessequal BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a <= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a <= b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a <= b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a <= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a <= b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
    islessequal
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const detail::expression<Tagb, A1b, A2b, A3b, A4b>& b) { return a <= b; }

template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
inline BOOST_MP_CXX14_CONSTEXPR bool isless BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const number<Backend2, ExpressionTemplates2>& b) { return a < b; }

template <class Backend, expression_template_option ExpressionTemplates, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return a < b; }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return a < b; }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& b) { return a < b; }

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isless
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& a, const Arithmetic& b) { return a < b; }

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b)
{
   if (detail::is_unordered_comparison(a, b))
      return false;
   return a != b;
}

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b)
{
   if (detail::is_unordered_comparison(a, b))
      return false;
   return a != b;
}

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type b(bb);
   return islessgreater                                          BOOST_PREVENT_MACRO_SUBSTITUTION(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    islessgreater
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const Arithmetic& b)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type a(aa);
   return islessgreater                                          BOOST_PREVENT_MACRO_SUBSTITUTION(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
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
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const number<Backend, ExpressionTemplates>& a, const Arithmetic& b) { return detail::is_unordered_comparison(a, b); }

template <class Arithmetic, class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<number<Backend, ExpressionTemplates>, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const number<Backend, ExpressionTemplates>& b) { return detail::is_unordered_comparison(a, b); }

template <class Arithmetic, class Tag, class A1, class A2, class A3, class A4>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const Arithmetic& a, const detail::expression<Tag, A1, A2, A3, A4>& bb)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type b(bb);
   return detail::is_unordered_comparison(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Arithmetic>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<detail::is_valid_mixed_compare<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, Arithmetic>::value, bool>::type
    isunordered
    BOOST_PREVENT_MACRO_SUBSTITUTION(const detail::expression<Tag, A1, A2, A3, A4>& aa, const Arithmetic& b)
{
   typename detail::expression<Tag, A1, A2, A3, A4>::result_type a(aa);
   return detail::is_unordered_comparison(a, b);
}

template <class Tag, class A1, class A2, class A3, class A4, class Tagb, class A1b, class A2b, class A3b, class A4b>
inline BOOST_MP_CXX14_CONSTEXPR typename enable_if<is_same<typename detail::expression<Tag, A1, A2, A3, A4>::result_type, typename detail::expression<Tagb, A1b, A2b, A3b, A4b>::result_type>, bool>::type
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