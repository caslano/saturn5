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
   using ref_type = typename sparse_vector_element<V>::const_reference;
   return static_cast<ref_type>(a) == b;
}

template <class X, class Y>
struct promote_traits;

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class Backend2, boost::multiprecision::expression_template_option ExpressionTemplates2>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, boost::multiprecision::number<Backend2, ExpressionTemplates2> >
{
   using number1_t = boost::multiprecision::number<Backend1, ExpressionTemplates1>;
   using number2_t = boost::multiprecision::number<Backend2, ExpressionTemplates2>;
   using promote_type = typename std::conditional<
       std::is_convertible<number1_t, number2_t>::value && !std::is_convertible<number2_t, number1_t>::value,
       number2_t, number1_t>::type;
};

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class Arithmetic>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, Arithmetic>
{
   using promote_type = boost::multiprecision::number<Backend1, ExpressionTemplates1>;
};

template <class Arithmetic, class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1>
struct promote_traits<Arithmetic, boost::multiprecision::number<Backend1, ExpressionTemplates1> >
{
   using promote_type = boost::multiprecision::number<Backend1, ExpressionTemplates1>;
};

template <class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1, class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct promote_traits<boost::multiprecision::number<Backend1, ExpressionTemplates1>, boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
{
   using number1_t = boost::multiprecision::number<Backend1, ExpressionTemplates1>         ;
   using expression_type = boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>;
   using number2_t = typename expression_type::result_type                                 ;
   using promote_type = typename promote_traits<number1_t, number2_t>::promote_type           ;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Backend1, boost::multiprecision::expression_template_option ExpressionTemplates1>
struct promote_traits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::number<Backend1, ExpressionTemplates1> >
{
   using number1_t = boost::multiprecision::number<Backend1, ExpressionTemplates1>         ;
   using expression_type = boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>;
   using number2_t = typename expression_type::result_type                                 ;
   using promote_type = typename promote_traits<number1_t, number2_t>::promote_type           ;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class tagb, class Arg1b, class Arg2b, class Arg3b, class Arg4b>
struct promote_traits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::detail::expression<tagb, Arg1b, Arg2b, Arg3b, Arg4b> >
{
   using expression1_t = boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>     ;
   using number1_t = typename expression1_t::result_type                                        ;
   using expression2_t = boost::multiprecision::detail::expression<tagb, Arg1b, Arg2b, Arg3b, Arg4b>;
   using number2_t = typename expression2_t::result_type                                        ;
};

}}} // namespace boost::numeric::ublas

#endif

/* ublas_interop.hpp
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
*/