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

template <class B1, class B2>
struct NumTraitsImp;

template <class B1>
struct NumTraitsImp<B1, B1>
{
   using self_type  = B1;
   using Real       = typename boost::multiprecision::scalar_result_from_possible_complex<self_type>::type;
   using NonInteger = self_type; // Not correct but we can't do much better??
   using Literal    = double;
   using Nested     = self_type;
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
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::epsilon();
   }
   static Real dummy_precision()
   {
      return 1000 * epsilon();
   }
   static Real highest()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return (std::numeric_limits<Real>::max)();
   }
   static Real lowest()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return (std::numeric_limits<Real>::min)();
   }
   static int digits10_imp(const std::integral_constant<bool, true>&)
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::digits10;
   }
   template <bool B>
   static int digits10_imp(const std::integral_constant<bool, B>&)
   {
      return Real::thread_default_precision();
   }
   static int digits10()
   {
      return digits10_imp(std::integral_constant < bool, std::numeric_limits<Real>::digits10 && (std::numeric_limits<Real>::digits10 != INT_MAX) ? true : false > ());
   }
   static int digits()
   {
      // return the number of digits in the component type in case Real is complex
      // and we have no numeric_limits specialization.
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::digits;
   }
   static int min_exponent()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::min_exponent;
   }
   static int max_exponent()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::max_exponent;
   }
   static Real infinity()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::infinity();
   }
   static Real quiet_NaN()
   {
      static_assert(std::numeric_limits<Real>::is_specialized, "Eigen's NumTraits instantiated on a type with no numeric_limits support.  Are you using a variable precision type?");
      return std::numeric_limits<Real>::quiet_NaN();
   }
};   
   
template <class B1, class B2>
struct NumTraitsImp : public NumTraitsImp<B2, B2>
{
   //
   // This version is instantiated when B1 and B2 are different types, this happens for rational/complex/interval
   // types, in which case many methods defer to those of the "component type" B2.
   //
   using self_type  = B1;
   using Real       = typename boost::multiprecision::scalar_result_from_possible_complex<self_type>::type;
   using NonInteger = self_type; // Not correct but we can't do much better??
   using Literal    = double;
   using Nested     = self_type;
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
   static B2 epsilon()
   {
      return NumTraitsImp<B2, B2>::epsilon();
   }
   static B2 dummy_precision()
   {
      return 1000 * epsilon();
   }
   static B2 highest()
   {
      return NumTraitsImp<B2, B2>::highest();
   }
   static B2 lowest()
   {
      return NumTraitsImp<B2, B2>::lowest();
   }
   static int digits10()
   {
      return NumTraitsImp<B2, B2>::digits10();
   }
   static int digits()
   {
      return NumTraitsImp<B2, B2>::digits();
   }
   static int min_exponent()
   {
      return NumTraitsImp<B2, B2>::min_exponent();
   }
   static int max_exponent()
   {
      return NumTraitsImp<B2, B2>::max_exponent();
   }
   static B2 infinity()
   {
      return NumTraitsImp<B2, B2>::infinity();
   }
   static B2 quiet_NaN()
   {
      return NumTraitsImp<B2, B2>::quiet_NaN();
   }
};

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
struct NumTraits<boost::multiprecision::number<Backend, ExpressionTemplates> > : public NumTraitsImp<boost::multiprecision::number<Backend, ExpressionTemplates>, typename boost::multiprecision::number<Backend, ExpressionTemplates>::value_type>
{};
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct NumTraits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > : public NumTraits<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>
{};

#define BOOST_MP_EIGEN_SCALAR_TRAITS_DECL(A)                                                                                                                                                                           \
   template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>                                                                                                  \
   struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, A, BinaryOp>                                                                                                               \
   {                                                                                                                                                                                                                   \
      /*static_assert(boost::multiprecision::is_compatible_arithmetic_type<A, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");*/ \
      using ReturnType = boost::multiprecision::number<Backend, ExpressionTemplates>;                                                                                                                                  \
   };                                                                                                                                                                                                                  \
   template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>                                                                                                  \
   struct ScalarBinaryOpTraits<A, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>                                                                                                               \
   {                                                                                                                                                                                                                   \
      /*static_assert(boost::multiprecision::is_compatible_arithmetic_type<A, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");*/ \
      using ReturnType = boost::multiprecision::number<Backend, ExpressionTemplates>;                                                                                                                                  \
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
      using ReturnType = typename std::conditional<std::is_convertible<boost::multiprecision::number<Backend2, ExpressionTemplates2>, boost::multiprecision::number<Backend, ExpressionTemplates> >::value,
         boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend2, ExpressionTemplates2> >::type;
   };

   template<unsigned D, typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<D>, boost::multiprecision::et_on>, boost::multiprecision::mpfr_float, BinaryOp>
   {
      using ReturnType = boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<D>, boost::multiprecision::et_on>;
   };

   template<typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::mpfr_float, boost::multiprecision::mpc_complex, BinaryOp>
   {
      using ReturnType = boost::multiprecision::number<boost::multiprecision::backends::mpc_complex_backend<0>, boost::multiprecision::et_on>;
   };

   template<class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>
   struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>
   {
      using ReturnType = boost::multiprecision::number<Backend, ExpressionTemplates>;
   };
#endif

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class tag, class Arg1, class Arg2, class Arg3, class Arg4, typename BinaryOp>
struct ScalarBinaryOpTraits<boost::multiprecision::number<Backend, ExpressionTemplates>, boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, BinaryOp>
{
   static_assert(std::is_convertible<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");
   using ReturnType = boost::multiprecision::number<Backend, ExpressionTemplates>;
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, typename BinaryOp>
struct ScalarBinaryOpTraits<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>, boost::multiprecision::number<Backend, ExpressionTemplates>, BinaryOp>
{
   static_assert(std::is_convertible<typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, boost::multiprecision::number<Backend, ExpressionTemplates> >::value, "Interoperability with this arithmetic type is not supported.");
   using ReturnType = boost::multiprecision::number<Backend, ExpressionTemplates>;
};

namespace internal {
template <typename Scalar>
struct conj_retval;

template <typename Scalar, bool IsComplex>
struct conj_impl;

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct conj_retval<boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4> >
{
   using type = typename boost::multiprecision::detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type;
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