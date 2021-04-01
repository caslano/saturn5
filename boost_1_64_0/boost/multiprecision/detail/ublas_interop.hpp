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
d8ArmnbvHwOU8sWsvNBYlB4n9O2BYwm5grf8Zov80hP7b1KAwUV41DVGr6lkmOD0N84sQmk0H86y0dNf6hEhpyDHSD22njRkDJx3VFP+8o3+2twdbYqMAZOpCeENioQm4nEN0Kf8FLKWnwrahB/qFqwYIUskJM4JMtD91JBSFXyaWoJRNUPefurXw0kWYKj5POWEO36DbPijZr0iYSY6uWx62ywfsPlCCcY4wf2bpi5cSEiA7Cn+tPSkcwx5R1fO0PBsLrAJqPjAqF3shfgn+XJLVAt2kIapvJaa7PqmIKZv1rkuRRB2zKAgNQFgQE1jU6CYpgYRR8Ar5sSZLULlbDC8++7VvMwjRkxU1xH74sFs1oFvfQyKlItLWEa4mTVXVlRt7aGj3dBkvc3brrZwaEffxyTv3Of5ml/2PSC1kZfwMNOY7woaMaOOCoGiRIrb6IpRi1CoF1oXBMovgsYGjYWDTj3yGzyQsNhRWHYPB3cIOQ6Gzy6FSi4vCXwWrr5vDOTTPTEefmkAiMis9qy6Zv4G4NWy1I6m+h6sIP4olW7eZ/cesuoucFWkBA==
*/