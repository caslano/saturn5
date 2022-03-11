///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_UBLAS_HPP
#define BOOST_MP_UBLAS_HPP

namespace boost { namespace numeric { namespace ublas {

template <class V>
class sparse_vector_element;

template <class V, class Backend, multiprecision::expression_template_option ExpressionTemplates>
inline bool operator==(const sparse_vector_element<V>& a, const ::boost::multiprecision::number<Backend, ExpressionTemplates>& b)
{
   typedef typename sparse_vector_element<V>::const_reference ref_type;
   return static_cast<ref_type>(a) == b;
}

template <class X, class Y>
struct promote_traits;

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class Backend2, boost::multiprecision::expression_template_option ExpressionTemplates2>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, boost::multiprecision::number<Backend2, ExpressionTemplates2> >
{
   typedef boost::multiprecision::number<Backend1, ExpressionTemplates1> number1_t;
   typedef boost::multiprecision::number<Backend2, ExpressionTemplates2> number2_t;
   typedef typename mpl::if_c<
       is_convertible<number1_t, number2_t>::value && !is_convertible<number2_t, number1_t>::value,
       number2_t, number1_t>::type promote_type;
};

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class Arithmetic>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, Arithmetic>
{
   typedef boost::multiprecision::number<Backend1, ExpressionTemplates1> promote_type;
};

template <class Arithmetic, class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1>
struct promote_traits<Arithmetic, boost::multiprecision::number<Backend1, ExpressionTemplates1> >
{
   typedef boost::multiprecision::number<Backend1, ExpressionTemplates1> promote_type;
};

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
{
   typedef boost::multiprecision::number<Backend1, ExpressionTemplates1>          number1_t;
   typedef boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> expression_type;
   typedef typename expression_type::result_type                                  number2_t;
   typedef typename promote_traits<number1_t, number2_t>::promote_type            promote_type;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1>
struct promote_traits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::number<Backend1, ExpressionTemplates1> >
{
   typedef boost::multiprecision::number<Backend1, ExpressionTemplates1>          number1_t;
   typedef boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> expression_type;
   typedef typename expression_type::result_type                                  number2_t;
   typedef typename promote_traits<number1_t, number2_t>::promote_type            promote_type;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tagb, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
struct promote_traits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::detail::expression<tagb, Arg1b, Arg2b, Arg3b, Arg4b> >
{
   typedef boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>      expression1_t;
   typedef typename expression1_t::result_type                                         number1_t;
   typedef boost::multiprecision::detail::expression<tagb, Arg1b, Arg2b, Arg3b, Arg4b> expression2_t;
   typedef typename expression2_t::result_type                                         number2_t;
};

}}} // namespace boost::numeric::ublas

#endif

/* ublas_interop.hpp
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
*/