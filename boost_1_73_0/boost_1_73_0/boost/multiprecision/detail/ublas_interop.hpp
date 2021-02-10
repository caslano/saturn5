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
NdfkEuYA/DLg/4qldJWVEGxJk1p1KBHUZIIPmYwJBuNg4ArkLxzAfkRNu4MUvZMK5BErl2BK6nT2dkvpkztb8HnJOk4UQY8ZNS0Bh+4fU5i2+HXFfFpM9FU+shMBy0CSjo6ACqrX6wmMFXQWDMHWA65lDvPdqwQSqCew+nEBQHAUh2EL06iezE6yo8A2aNjVG9y90JCQCnX3o9tzP8ZAg6O3pUq9gHEfiuiFWg2GSAyTxlm1Gumc1XThiTcgK/WkoA2KeHiSAQ1UypYWD0+kn6IYjUCjTPCwPM3Qa+WTR2Ligy90WWXV7Ki+2tbZP+HHzPhjloDW273eYRtHbKd9eFiqzJDzvPol00tgzm8GjjDMhutoU6/Be8UKndbha8W5JOuBL0KkhAnQC8LewHM1klAZtDM0IlCGHZrxX2239o053s6okeMNNhgWNibAJbmaW1YLQEDfMOgONGCN0rPE1KpycX8d7Mhh6LoMGTR6aN1ZTY2sItFDJFGnffh6ARJNk1ubpBNzgw/QFyEZV2vQ2Suj8P0p2q81RrdWp0CdMmoNpT8qump95fm0CsOQI8rzTvrsih+/xmWAjyvtCwetE7VroZniKUFtH3V16CiLpJ2VYxzDBucIrqdJrQ0EmjFLgMiuABa3/K0W/00+
*/