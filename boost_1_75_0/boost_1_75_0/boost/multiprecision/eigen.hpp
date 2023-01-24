///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_EIGEN_HPP
#define BOOST_MP_EIGEN_HPP

#include <boost/multiprecision/number.hpp>
#include <Eigen/Core>

//
// Generic Eigen support code:
//
namespace Eigen {
template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
struct NumTraits<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<Backend, ExpressionTemplates>                          self_type;
   typedef typename boost::multiprecision::scalar_result_from_possible_complex<self_type>::type Real;
   typedef self_type                                                                            NonInteger; // Not correct but we can't do much better??
   typedef double                                                                               Literal;
   typedef self_type                                                                            Nested;
   enum
   {
      IsComplex             = boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_complex,
      IsInteger             = boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer,
      ReadCost              = 1,
      AddCost               = 4,
      MulCost               = 8,
      IsSigned              = std::numeric_limits<self_type>::is_specialized ? std::numeric_limits<self_type>::is_signed : true,
      RequireInitialization = 1,
   };
   static Real epsilon()
   {
      return std::numeric_limits<Real>::epsilon();
   }
   static Real dummy_precision()
   {
      return 1000 * epsilon();
   }
   static Real highest()
   {
      return (std::numeric_limits<Real>::max)();
   }
   static Real lowest()
   {
      return (std::numeric_limits<Real>::min)();
   }
   static int digits10_imp(const boost::mpl::true_&)
   {
      return std::numeric_limits<Real>::digits10;
   }
   template <bool B>
   static int digits10_imp(const boost::mpl::bool_<B>&)
   {
      return Real::default_precision();
   }
   static int digits10()
   {
      return digits10_imp(boost::mpl::bool_ < std::numeric_limits<Real>::digits10 && (std::numeric_limits<Real>::digits10 != INT_MAX) ? true : false > ());
   }
};
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct NumTraits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > : public NumTraits<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>
{
};

#define BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(A)                                                                                                                                                                           \
   template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>                                                                                                  \
   struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, A, BinaryOp>                                                                                                               \
   {                                                                                                                                                                                                                   \
      /*static_assert(boost::multiprecision::is_compatible_arithmetic_type<A, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");*/ \
      typedef boost::multiprecision::number<Backend, ExpressionTemplates> ReturnType;                                                                                                                                  \
   };                                                                                                                                                                                                                  \
   template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>                                                                                                  \
   struct ScalarBinaryOpTraits<A, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>                                                                                                               \
   {                                                                                                                                                                                                                   \
      /*static_assert(boost::multiprecision::is_compatible_arithmetic_type<A, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");*/ \
      typedef boost::multiprecision::number<Backend, ExpressionTemplates> ReturnType;                                                                                                                                  \
   };

BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(float)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(double)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(long double)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(char)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(unsigned char)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(signed char)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(short)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(unsigned short)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(int)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(unsigned int)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(long)
BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(unsigned long)

#if 0    
      template<class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class Backend2, boost::multiprecision::expression_template_option ExpressionTemplates2, typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend2, ExpressionTemplates2>, BinaryOp>
   {
      static_assert(
         boost::multiprecision::is_compatible_arithmetic_type<boost::multiprecision::number<Backend2, ExpressionTemplates2>, boost::multiprecision::number<Backend, ExpressionTemplates> >::value
         || boost::multiprecision::is_compatible_arithmetic_type<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend2, ExpressionTemplates2> >::value, "Interoperability with this arithmetic type is not supported.");
      typedef typename boost::mpl::if_c<boost::is_convertible<boost::multiprecision::number<Backend2, ExpressionTemplates2>, boost::multiprecision::number<Backend, ExpressionTemplates> >::value,
         boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend2, ExpressionTemplates2> >::type ReturnType;
   };

   template<unsigned D, typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<D>, boost::multiprecision::et_on>, boost::multiprecision::mpfr_float, BinaryOp>
   {
      typedef boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<D>, boost::multiprecision::et_on> ReturnType;
   };

   template<typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::mpfr_float, boost::multiprecision::mpc_complex, BinaryOp>
   {
      typedef boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<0>, boost::multiprecision::et_on> ReturnType;
   };

   template<class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>
   {
      typedef boost::multiprecision::number<Backend, ExpressionTemplates> ReturnType;
   };
#endif

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class tag, class Arg1, class Arg2, class Arg3, class Arg4, typename BinaryOp>
struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, BinaryOp>
{
   static_assert(boost::is_convertible<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");
   typedef boost::multiprecision::number<Backend, ExpressionTemplates> ReturnType;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>
struct ScalarBinaryOpTraits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>
{
   static_assert(boost::is_convertible<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");
   typedef boost::multiprecision::number<Backend, ExpressionTemplates> ReturnType;
};

namespace internal {
template <typename Scalar>
struct conj_retval;

template <typename Scalar, bool IsComplex>
struct conj_impl;

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct conj_retval<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
{
   typedef typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type type;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct conj_impl<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, true>
{
   EIGEN_DEVICE_FUNC
   static inline typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type run(const typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& x)
   {
      return conj(x);
   }
};

} // namespace internal

} // namespace Eigen

#endif

/* eigen.hpp
i7YOhE26Ef3hnqen7rB6Fl15BP++WKVq/DN8bsXYB8YXmPssZHx8pkvbq4ZC+JWQequVqNrm9GC00KOn2SV3Wk25RHdaIZI/Z5xk3dluvmFJ9zkM+O+19gSpkd8KOoEsunkBdw42Y95+t4AZVURdtp29W5hrJmxCfFPbdtquib7Q5dB9V4x4niKoS1FIf6PvSyS5rhmcYZk7p6zjX2s4skcZ9TeMHHtHMwxHAYlCr4ja/1XISEfFVSYIEcituCgj2XTaC7vyJaTETEPp8W//8UuiR3dL0W2Xp8Rn+aG9J4tU7U5ygyf7PKioxRMbr7LxyaMHVkPIJu3dip7OvXwgfiNRSSu+AP2tKEbJBzu3o8rR1yR4fXHS4w0KsPHpxdDmej4AaxtOv1bIflOTaBa59i8N01MY37B4DKPfudG5jC16ZjUumCHekT8U6bBwZHmM5CXg7umSpsknNdC1IniZjRR6vNQa0uuCfmRtrXP8ev6KcgpHMrtnfXkp+MlYiBIptCwZA8kpXE1qT1mxY2kwvGIrqy9tlIffdYYHYTev3gtPFK7ovt+SwBxZFsCBr4ZkQKr2liMXN2ObIxek1V0VrK0rm1V4JvCvx94WYX7Q7pQzp+mAzaNg1fv4bdJ7D59bLMHplt9n2oqKN1M3bJV6lqRVTlKzAd7iBptfuaqsFiJXaH4FiJwQ9dTOeV25fQgKz1nbDd90/gAD+6iP
*/