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
RA9bBQ1uyqTTB70N+FAiXXRPDpWwJLqYPMZEF7WKiS7+ZLo4YyW6yDpCM3L3ap0unnjUoIvOY4yvuWpSfaeE/uPMO2lpyumU8cVFPlkZVcgqWf9LaaYVZaYTTWTwus+YYxcJkYC4VEYVY7pUhPA9gfHFBrLDCkAnGiSQqCvAYkxrx+o7ubKZxkJ7bFSlct97DcIc9J+hBOQbhoblS9p8VT2fj4ibjH21x+8z7au1iCTgPm0h4Kq0geveUmUX+2rXrjT21d4dbeyrfXlz2L7at2PC9tVC6Stj6bNzTFfayP5/xFsMsWgA5Okxzdlt2/JuHScQM32NRCfM4B1xG0K24Tf+LmCRcTWB4nSuXcogA1QG6n8BhEZGD/LWZWA8IBEwTtNmrftNFYGR1UNNwrAxJauH5n4tl0AB13bnAcMFfJdSIijk5JGXhkxHtAJUsi7lG32EJRjXSP45fXJcSzFvHDzcgwpcZ/RA/4vbRX1r5P/FNLBIz/pTNNeNjFR/fc4q4U5NwNdJViYUyMrISBiFS7WM1XMnZnUy9l+otkoj+y/pyq5MBd6IlYd2iA2YLJfYf+kJpJKfnuLrBPpxMCtSrZ5Ak1xWDyJjHrCgbfg2TMXHEGBEZl2NGOrxTh0TpFFbdfyEcRWcf8ybzoLiYRmIF36D+BvCI6nE5E+L0qImySwtAIdX32iSFh8tMkmLFMbhrnOkPdxIO8Tump91
*/