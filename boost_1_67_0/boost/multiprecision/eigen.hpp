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
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
*/