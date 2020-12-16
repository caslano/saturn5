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
IG5q0oTT5+lVI848T0+/HbFwfcOvDhJKMfMphtGwrq+9E2nCTKSaG3DRXu/Ldj9zUwJ7kXEBbfkXJbubW4KOVLRTe5dGg88o2Q2/u6ZjK2HgCr+o10r6+Y3eMk4WvNsuHWI03NTxbeE+/g69t3yhfGbpdgR96b2MXm2qsi7wIOYvQ3o9jUT+jfcjrZKHvMyhbBCXVOBAOKz71gfI79gm9F/7IKFXCQYluvshSudDEun/Rnp1yeB7mIg/cUShr8F374vyL35YoneXIab3+YV+V/TN/o8gnaviRJuvS7ReR5L5o/Lv9eogeP5C0CtxpbLfPypoICn/VBLvY0gH2gJ87A1wGD+P3+u2oHPHf/hQg3XodCa6NM6OcxwezATt5Wmk4XKBPnczSJMPaEifOCHoMA65/IL3+Emko14V8+idKmnwlRdegH4rQfCz4P1sTYe/zhoHoB4PiJwuxigmqsK8JByD5RkvPmZQx/pxhqlG0zMdKT/MafydsxW0uU8ibb0La5hMu4402ceA6z7PMBpT4fGRK/O0GI0f4qrRibRXbJnWh1t1V9BahMa6SOTacTmt4gdUSRaP01AUQSt8SoOCSLtT0nrYo5018c1+0Wa0Opyp7r96I2B06UDJuxbnZ6jQ+1CzJNfpiNGZRpflJVo+D2cXMfdLGmgf3HB2br7IIeYOia9yONbomq/gywzzEP/FiUTF6P6L368xuo5Z6I1TIwZlwjWT49COQJFnKFPpqKoVOfJUjCLvWC7TzbYImyaMwuc+wXDrtLUBGVtfKwhmY02ivSHTlDYkn5JpqNkX6xjS9fxa42dlGvSP1L+bKq2qF8vep3RQbQvaYFamVQsBlpNpSj9tzgFN15SR8XHXjMHx8QTHrZ1jONgp5Xgu5W94sOL7vJDtu88p9PVlpE19WtD4Bi58EUqaUc2Neu5loudOLN9OnTwPHzsPi2zr+vHqDIVOvoqpq7DRGdaxiqkrYudGdCy/Q/cGvUUaS8CIRZNTxFlbdJxs6orvsSZc31y3O2rC6nW/bsZh3einshVwUh5n2D6Jj6C7TdDrKQwQpP9BonNdBbGlLbbrdP6hEPNvAwZtkTEnlhmDXSTneN6hY9V8Q3cYRvcX500UuM5OI05797ttxnFTUilH7i4jzvg2+QcNq/u9B7vNGMwZU8fH3CfNw2dS301bYZRaqy9wmyy/trGScQ5LSuCmgZcH1sZKf627WN7kz8xIrgNnZmBxKP8NXASfm4RPy4r9KHczPwM+8JYCpWByz8C3OTNTnSkIT0meN2U+rdxywrzlRm2NjyJTHYoG+UyM03ieSctttbIgJHw6XbbsKLxO9c/MCD4J4eNAu7zCdQvfzAfEKMvX5p+Cz4Dwca0492I3yjU+4PgguqgKQn1m5gXB54fjtH98Fhw9ydoW6Q40P60ewkS+jaFP1jlaCZ+2VcReO2l7LYs1obl8t5bjDimfWZGfBL7dtqkcPeiLlVXomK+wL1Ym86gYoRyjb5H5hFYQhE6WZA7ls7QAjEAr2lvnsY+w/BQp71tpCNGbUi+o2tFYP9pKnyblbStK4bWzbRdVea1e/A7FW5R30nYbhlfQti6srl9cQBPrmd6KNrpAIsHnCuGTWVkROJnb9h+Xz3XCJ7Byr21ntpvqfMQoFTbFgs89hY8bRywIhPMgPsLm2MJ+nXqCxKRqZZnTSrzMWt0AHqsXzsxc7F5cXf8K2qDX3/PoE3Q8FGCpGsZ+aDFtRzUwlQWJfpfkCdqfbaewYVwmzeWlvpXWocuET2BlrSDJisjR16EyBqSyrAl5XlX4FE6eRBGd9tVpC/69xOZbb70/EPK06vhhpF8SC/IpRy07dek8KQ8=
*/