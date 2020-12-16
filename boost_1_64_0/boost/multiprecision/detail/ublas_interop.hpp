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
+CuqY+3AEpmXck6xPTO2nwnhwn3zs0w/f5i3VAXDFrhXh1t3Zuf588GvoBhmlQpkFZOpPy98BPwsDT7baplj0QrljKgnhpnN6lsMftsLMkTJaX38XmGtDS4I2BmbwcZJSaVU7pJHABLoGIwTOHO6GfrsRxtlZUTL/Nz9cTN82/raENSUdcvtHQwOnFfgj4l0JeFSqtrdluzfvdUg66g8OD/4zEm9ggFfQ7AVM2jemsgzLUZ1sO1GEL+Lf8/guA7GyeiC6nLGTr2H7Ud/jLGiTTnXBl3F9bu19ak6C2Z7hxnir2QvIuUR547FJ0s32R+a4S3UUWM9V/M8CA19igDXKrHzmZN6ifCgu1N5pkWcrSjKSxMhr+zAeQfu5SziLLSOoXC55lyf4EbO77CYM/cicOcFtvHczNlYzFkZnp3l9j9zrpXoOMNdG667zsUWlkX/SSHkPh4b38Tt5L0Otfa6G09HfXzqHYhLYAe71tCy7oXxg7niYfsrsOO2eJ1k1msd0pRIqh9ce2DH3evsGs4dzcW1y/PHVx8+/iKsqW46i9shJ5kWziQdxniC142n+/A+XX85/L0YpaORyozu1CFe7k6tziNoNXhzdYhzKsIKkSJw7gbXGZwHep07FZTTKBQ57hjfctN5wA12HNYpIWKe8Z2PJeALZ1yH90AdjPSGc3IdyaoyjY2vI11DhJah+GSHRarB94Pr1sT5+73+dpSRutpzBJyZetuVH7ohJr+kXhfrr8VaJt1ZBlXs5v0fHdo3REpB2maO8hB20gn7yE17cK8jBLG2dg+nT5i73V+SznbG9+dLJlTLRskXLKbYcdtgc+ExZ+ODFT6H/5Lz7QnzCGMab1tO+0Upkzvh5cT11GOuLhapFf+fuIJfox/8qALX3Ka49oFvQS3o4eE6RtF9eB/yqJ8sV0J4yzrqcCi7hPchhJeItIFnRxPp/N/7MBo7CPopt930reHxu4LztdWzcgA+Pe0uDxu311NtDxYzyAUW/s3ZlcZm1VThbkBRVFTUT8RPVNyXQGkVEpW5+75Iq6IxvpS+L7Ra2tq3xbr8UGOiRo388Ac/TNS4ETWRKBoTTSSRH7hvuOOO+4aKOy7nzL1z3jlzbxX8Psoyz3POmTmz3NlHL+NpERdlbnuicKZLqk+xKhspj39cFKmVxlnj7TiyR41YYz93mrKzjn7pOaUcZlX3c9DamrJ9LOVpDrwoSlM3uo00U2M2odqFlPfnLNvxcj+R715z84Nyd9ZIe5mWVuBF1uZppwatcTfhxZSvYdhJnCZ5Jp1uLG8foTv3Ur4GFIdh4Lpa6ucWVuYHbcMBak9SvieojPOodF1py1hMF3R3bmqsb8epl7plqPcp2euh8D1+tPo+Zfq5ScdOs9ILQxFNF3xtbCwz3rSwUi/JfavNBmUq1evBOc393F7mhS6oErDmze1NGvaCwgrKyLVv1x7tA8r4WkmGNb+w1OVeh08sd+trLLV+dmaM43Ir8kI713MPr2iZHVzQcpj6RZkxjxG4lhcGvvToVFZZnbLJKvWLMuOcZFZmYRpmRtvMLLM7GjL2vU8sy7WyyurhZ03zvuMlw7dF7niBk2rpYw6lWlkbZ/cM/Toz7jLNHLeIw7RKL1jmaeb3Nuf8vYwgCL3Si8L/HY8VvM+Y7Vud1HVNFY5TlEWcw3kTkHhqvXckV/0dnes6Isqd2MntTb9JR/Y50aBxcOIjU2s9dAOd2WS2SytOfTt00fZkbVu7qzvnvi/DwPXsyLmDNNM67Adytvc68Es/9S2wS/NDgzRfZHZDkYBRz0uy208zf5fnes7aZDd20qgsQpXoKSdDHW6p2hu628tIf555he149h2kfzY=
*/