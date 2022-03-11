//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POLICY_HPP
#define BOOST_MATH_POLICY_HPP

#include <boost/mpl/list.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/math/tools/config.hpp>
#include <limits>
// Sadly we do need the .h versions of these to be sure of getting
// FLT_MANT_DIG etc.
#include <limits.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

namespace boost{ namespace math{ 

namespace tools{

template <class T>
BOOST_MATH_CONSTEXPR int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_NOEXCEPT;
template <class T>
BOOST_MATH_CONSTEXPR T epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T);

}

namespace policies{

//
// Define macros for our default policies, if they're not defined already:
//
// Special cases for exceptions disabled first:
//
#ifdef BOOST_NO_EXCEPTIONS
#  ifndef BOOST_MATH_DOMAIN_ERROR_POLICY
#    define BOOST_MATH_DOMAIN_ERROR_POLICY errno_on_error
#  endif
#  ifndef BOOST_MATH_POLE_ERROR_POLICY
#     define BOOST_MATH_POLE_ERROR_POLICY errno_on_error
#  endif
#  ifndef BOOST_MATH_OVERFLOW_ERROR_POLICY
#     define BOOST_MATH_OVERFLOW_ERROR_POLICY errno_on_error
#  endif
#  ifndef BOOST_MATH_EVALUATION_ERROR_POLICY
#     define BOOST_MATH_EVALUATION_ERROR_POLICY errno_on_error
#  endif
#  ifndef BOOST_MATH_ROUNDING_ERROR_POLICY
#     define BOOST_MATH_ROUNDING_ERROR_POLICY errno_on_error
#  endif
#endif
//
// Then the regular cases:
//
#ifndef BOOST_MATH_DOMAIN_ERROR_POLICY
#define BOOST_MATH_DOMAIN_ERROR_POLICY throw_on_error
#endif
#ifndef BOOST_MATH_POLE_ERROR_POLICY
#define BOOST_MATH_POLE_ERROR_POLICY throw_on_error
#endif
#ifndef BOOST_MATH_OVERFLOW_ERROR_POLICY
#define BOOST_MATH_OVERFLOW_ERROR_POLICY throw_on_error
#endif
#ifndef BOOST_MATH_EVALUATION_ERROR_POLICY
#define BOOST_MATH_EVALUATION_ERROR_POLICY throw_on_error
#endif
#ifndef BOOST_MATH_ROUNDING_ERROR_POLICY
#define BOOST_MATH_ROUNDING_ERROR_POLICY throw_on_error
#endif
#ifndef BOOST_MATH_UNDERFLOW_ERROR_POLICY
#define BOOST_MATH_UNDERFLOW_ERROR_POLICY ignore_error
#endif
#ifndef BOOST_MATH_DENORM_ERROR_POLICY
#define BOOST_MATH_DENORM_ERROR_POLICY ignore_error
#endif
#ifndef BOOST_MATH_INDETERMINATE_RESULT_ERROR_POLICY
#define BOOST_MATH_INDETERMINATE_RESULT_ERROR_POLICY ignore_error
#endif
#ifndef BOOST_MATH_DIGITS10_POLICY
#define BOOST_MATH_DIGITS10_POLICY 0
#endif
#ifndef BOOST_MATH_PROMOTE_FLOAT_POLICY
#define BOOST_MATH_PROMOTE_FLOAT_POLICY true
#endif
#ifndef BOOST_MATH_PROMOTE_DOUBLE_POLICY
#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#define BOOST_MATH_PROMOTE_DOUBLE_POLICY false
#else
#define BOOST_MATH_PROMOTE_DOUBLE_POLICY true
#endif
#endif
#ifndef BOOST_MATH_DISCRETE_QUANTILE_POLICY
#define BOOST_MATH_DISCRETE_QUANTILE_POLICY integer_round_outwards
#endif
#ifndef BOOST_MATH_ASSERT_UNDEFINED_POLICY
#define BOOST_MATH_ASSERT_UNDEFINED_POLICY true
#endif
#ifndef BOOST_MATH_MAX_SERIES_ITERATION_POLICY
#define BOOST_MATH_MAX_SERIES_ITERATION_POLICY 1000000
#endif
#ifndef BOOST_MATH_MAX_ROOT_ITERATION_POLICY
#define BOOST_MATH_MAX_ROOT_ITERATION_POLICY 200
#endif

#if !defined(__BORLANDC__)
#define BOOST_MATH_META_INT(type, name, Default)\
   template <type N = Default> struct name : public boost::integral_constant<int, N>{};\
   namespace detail{\
   template <type N>\
   char test_is_valid_arg(const name<N>*);\
   char test_is_default_arg(const name<Default>*);\
   template <class T> struct is_##name##_imp\
   {\
      template <type N> static char test(const name<N>*);\
      static double test(...);\
      BOOST_STATIC_CONSTANT(bool, value = sizeof(test(static_cast<T*>(0))) == 1);\
   };\
   }\
   template <class T> struct is_##name : public boost::integral_constant<bool, ::boost::math::policies::detail::is_##name##_imp<T>::value>{};

#define BOOST_MATH_META_BOOL(name, Default)\
   template <bool N = Default> struct name : public boost::integral_constant<bool, N>{};\
   namespace detail{\
   template <bool N>\
   char test_is_valid_arg(const name<N>*);\
   char test_is_default_arg(const name<Default>*);\
   template <class T> struct is_##name##_imp\
   {\
      template <bool N> static char test(const name<N>*);\
      static double test(...);\
      BOOST_STATIC_CONSTANT(bool, value = sizeof(test(static_cast<T*>(0))) == 1);\
   };\
   }\
   template <class T> struct is_##name : public boost::integral_constant<bool, ::boost::math::policies::detail::is_##name##_imp<T>::value>{};
#else
#define BOOST_MATH_META_INT(Type, name, Default)\
   template <Type N = Default> struct name : public boost::integral_constant<int, N>{};\
   namespace detail{\
   template <Type N>\
   char test_is_valid_arg(const name<N>*);\
   char test_is_default_arg(const name<Default>*);\
   template <class T> struct is_##name##_tester\
   {\
      template <Type N> static char test(const name<N>&);\
      static double test(...);\
   };\
   template <class T> struct is_##name##_imp\
   {\
      static T inst;\
      BOOST_STATIC_CONSTANT(bool, value = sizeof( ::boost::math::policies::detail::is_##name##_tester<T>::test(inst)) == 1);\
   };\
   }\
   template <class T> struct is_##name : public boost::integral_constant<bool, ::boost::math::policies::detail::is_##name##_imp<T>::value>\
   {\
      template <class U> struct apply{ typedef is_##name<U> type; };\
   };

#define BOOST_MATH_META_BOOL(name, Default)\
   template <bool N = Default> struct name : public boost::integral_constant<bool, N>{};\
   namespace detail{\
   template <bool N>\
   char test_is_valid_arg(const name<N>*);\
   char test_is_default_arg(const name<Default>*);\
   template <class T> struct is_##name##_tester\
   {\
      template <bool N> static char test(const name<N>&);\
      static double test(...);\
   };\
   template <class T> struct is_##name##_imp\
   {\
      static T inst;\
      BOOST_STATIC_CONSTANT(bool, value = sizeof( ::boost::math::policies::detail::is_##name##_tester<T>::test(inst)) == 1);\
   };\
   }\
   template <class T> struct is_##name : public boost::integral_constant<bool, ::boost::math::policies::detail::is_##name##_imp<T>::value>\
   {\
      template <class U> struct apply{ typedef is_##name<U> type;  };\
   };
#endif
//
// Begin by defining policy types for error handling:
//
enum error_policy_type
{
   throw_on_error = 0,
   errno_on_error = 1,
   ignore_error = 2,
   user_error = 3
};

BOOST_MATH_META_INT(error_policy_type, domain_error, BOOST_MATH_DOMAIN_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, pole_error, BOOST_MATH_POLE_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, overflow_error, BOOST_MATH_OVERFLOW_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, underflow_error, BOOST_MATH_UNDERFLOW_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, denorm_error, BOOST_MATH_DENORM_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, evaluation_error, BOOST_MATH_EVALUATION_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, rounding_error, BOOST_MATH_ROUNDING_ERROR_POLICY)
BOOST_MATH_META_INT(error_policy_type, indeterminate_result_error, BOOST_MATH_INDETERMINATE_RESULT_ERROR_POLICY)

//
// Policy types for internal promotion:
//
BOOST_MATH_META_BOOL(promote_float, BOOST_MATH_PROMOTE_FLOAT_POLICY)
BOOST_MATH_META_BOOL(promote_double, BOOST_MATH_PROMOTE_DOUBLE_POLICY)
BOOST_MATH_META_BOOL(assert_undefined, BOOST_MATH_ASSERT_UNDEFINED_POLICY)
//
// Policy types for discrete quantiles:
//
enum discrete_quantile_policy_type
{
   real,
   integer_round_outwards,
   integer_round_inwards,
   integer_round_down,
   integer_round_up,
   integer_round_nearest
};

BOOST_MATH_META_INT(discrete_quantile_policy_type, discrete_quantile, BOOST_MATH_DISCRETE_QUANTILE_POLICY)
//
// Precision:
//
BOOST_MATH_META_INT(int, digits10, BOOST_MATH_DIGITS10_POLICY)
BOOST_MATH_META_INT(int, digits2, 0)
//
// Iterations:
//
BOOST_MATH_META_INT(unsigned long, max_series_iterations, BOOST_MATH_MAX_SERIES_ITERATION_POLICY)
BOOST_MATH_META_INT(unsigned long, max_root_iterations, BOOST_MATH_MAX_ROOT_ITERATION_POLICY)
//
// Define the names for each possible policy:
//
#define BOOST_MATH_PARAMETER(name)\
   BOOST_PARAMETER_TEMPLATE_KEYWORD(name##_name)\
   BOOST_PARAMETER_NAME(name##_name)

struct default_policy{};

namespace detail{
//
// Trait to work out bits precision from digits10 and digits2:
//
template <class Digits10, class Digits2>
struct precision
{
   //
   // Now work out the precision:
   //
   typedef typename mpl::if_c<
      (Digits10::value == 0),
      digits2<0>,
      digits2<((Digits10::value + 1) * 1000L) / 301L>
   >::type digits2_type;
public:
#ifdef __BORLANDC__
   typedef typename mpl::if_c<
      (Digits2::value > ::boost::math::policies::detail::precision<Digits10,Digits2>::digits2_type::value),
      Digits2, digits2_type>::type type;
#else
   typedef typename mpl::if_c<
      (Digits2::value > digits2_type::value),
      Digits2, digits2_type>::type type;
#endif
};

template <class A, class B, bool b>
struct select_result
{
   typedef A type;
};
template <class A, class B>
struct select_result<A, B, false>
{
   typedef typename mpl::deref<B>::type type;
};

template <class Seq, class Pred, class DefaultType>
struct find_arg
{
private:
   typedef typename mpl::find_if<Seq, Pred>::type iter;
   typedef typename mpl::end<Seq>::type end_type;
public:
   typedef typename select_result<
      DefaultType, iter,
      ::boost::is_same<iter, end_type>::value>::type type;
};

double test_is_valid_arg(...);
double test_is_default_arg(...);
char test_is_valid_arg(const default_policy*);
char test_is_default_arg(const default_policy*);

template <class T>
struct is_valid_policy_imp 
{
   BOOST_STATIC_CONSTANT(bool, value = sizeof(::boost::math::policies::detail::test_is_valid_arg(static_cast<T*>(0))) == 1);
};

template <class T>
struct is_default_policy_imp
{
   BOOST_STATIC_CONSTANT(bool, value = sizeof(::boost::math::policies::detail::test_is_default_arg(static_cast<T*>(0))) == 1);
};

template <class T> struct is_valid_policy 
: public boost::integral_constant<bool, ::boost::math::policies::detail::is_valid_policy_imp<T>::value>
{};

template <class T> struct is_default_policy 
: public boost::integral_constant<bool, ::boost::math::policies::detail::is_default_policy_imp<T>::value>
{
   template <class U>
   struct apply
   {
      typedef is_default_policy<U> type;
   };
};

template <class Seq, class T, int N>
struct append_N
{
   typedef typename mpl::push_back<Seq, T>::type new_seq;
   typedef typename append_N<new_seq, T, N-1>::type type;
};

template <class Seq, class T>
struct append_N<Seq, T, 0>
{
   typedef Seq type;
};

//
// Traits class to work out what template parameters our default
// policy<> class will have when modified for forwarding:
//
template <bool f, bool d>
struct default_args
{
   typedef promote_float<false> arg1;
   typedef promote_double<false> arg2;
};

template <>
struct default_args<false, false>
{
   typedef default_policy arg1;
   typedef default_policy arg2;
};

template <>
struct default_args<true, false>
{
   typedef promote_float<false> arg1;
   typedef default_policy arg2;
};

template <>
struct default_args<false, true>
{
   typedef promote_double<false> arg1;
   typedef default_policy arg2;
};

typedef default_args<BOOST_MATH_PROMOTE_FLOAT_POLICY, BOOST_MATH_PROMOTE_DOUBLE_POLICY>::arg1 forwarding_arg1;
typedef default_args<BOOST_MATH_PROMOTE_FLOAT_POLICY, BOOST_MATH_PROMOTE_DOUBLE_POLICY>::arg2 forwarding_arg2;

} // detail
//
// Now define the policy type with enough arguments to handle all
// the policies:
//
template <class A1 = default_policy, 
          class A2 = default_policy, 
          class A3 = default_policy,
          class A4 = default_policy,
          class A5 = default_policy,
          class A6 = default_policy,
          class A7 = default_policy,
          class A8 = default_policy,
          class A9 = default_policy,
          class A10 = default_policy,
          class A11 = default_policy,
          class A12 = default_policy,
          class A13 = default_policy>
struct policy
{
private:
   //
   // Validate all our arguments:
   //
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A1>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A2>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A3>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A4>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A5>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A6>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A7>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A8>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A9>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A10>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A11>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A12>::value);
   BOOST_STATIC_ASSERT(::boost::math::policies::detail::is_valid_policy<A13>::value);
   //
   // Typelist of the arguments:
   //
   typedef mpl::list<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13> arg_list;

public:
   typedef typename detail::find_arg<arg_list, is_domain_error<mpl::_1>, domain_error<> >::type domain_error_type;
   typedef typename detail::find_arg<arg_list, is_pole_error<mpl::_1>, pole_error<> >::type pole_error_type;
   typedef typename detail::find_arg<arg_list, is_overflow_error<mpl::_1>, overflow_error<> >::type overflow_error_type;
   typedef typename detail::find_arg<arg_list, is_underflow_error<mpl::_1>, underflow_error<> >::type underflow_error_type;
   typedef typename detail::find_arg<arg_list, is_denorm_error<mpl::_1>, denorm_error<> >::type denorm_error_type;
   typedef typename detail::find_arg<arg_list, is_evaluation_error<mpl::_1>, evaluation_error<> >::type evaluation_error_type;
   typedef typename detail::find_arg<arg_list, is_rounding_error<mpl::_1>, rounding_error<> >::type rounding_error_type;
   typedef typename detail::find_arg<arg_list, is_indeterminate_result_error<mpl::_1>, indeterminate_result_error<> >::type indeterminate_result_error_type;
private:
   //
   // Now work out the precision:
   //
   typedef typename detail::find_arg<arg_list, is_digits10<mpl::_1>, digits10<> >::type digits10_type;
   typedef typename detail::find_arg<arg_list, is_digits2<mpl::_1>, digits2<> >::type bits_precision_type;
public:
   typedef typename detail::precision<digits10_type, bits_precision_type>::type precision_type;
   //
   // Internal promotion:
   //
   typedef typename detail::find_arg<arg_list, is_promote_float<mpl::_1>, promote_float<> >::type promote_float_type;
   typedef typename detail::find_arg<arg_list, is_promote_double<mpl::_1>, promote_double<> >::type promote_double_type;
   //
   // Discrete quantiles:
   //
   typedef typename detail::find_arg<arg_list, is_discrete_quantile<mpl::_1>, discrete_quantile<> >::type discrete_quantile_type;
   //
   // Mathematically undefined properties:
   //
   typedef typename detail::find_arg<arg_list, is_assert_undefined<mpl::_1>, assert_undefined<> >::type assert_undefined_type;
   //
   // Max iterations:
   //
   typedef typename detail::find_arg<arg_list, is_max_series_iterations<mpl::_1>, max_series_iterations<> >::type max_series_iterations_type;
   typedef typename detail::find_arg<arg_list, is_max_root_iterations<mpl::_1>, max_root_iterations<> >::type max_root_iterations_type;
};
//
// These full specializations are defined to reduce the amount of
// template instantiations that have to take place when using the default
// policies, they have quite a large impact on compile times:
//
template <>
struct policy<default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy>
{
public:
   typedef domain_error<> domain_error_type;
   typedef pole_error<> pole_error_type;
   typedef overflow_error<> overflow_error_type;
   typedef underflow_error<> underflow_error_type;
   typedef denorm_error<> denorm_error_type;
   typedef evaluation_error<> evaluation_error_type;
   typedef rounding_error<> rounding_error_type;
   typedef indeterminate_result_error<> indeterminate_result_error_type;
#if BOOST_MATH_DIGITS10_POLICY == 0
   typedef digits2<> precision_type;
#else
   typedef detail::precision<digits10<>, digits2<> >::type precision_type;
#endif
   typedef promote_float<> promote_float_type;
   typedef promote_double<> promote_double_type;
   typedef discrete_quantile<> discrete_quantile_type;
   typedef assert_undefined<> assert_undefined_type;
   typedef max_series_iterations<> max_series_iterations_type;
   typedef max_root_iterations<> max_root_iterations_type;
};

template <>
struct policy<detail::forwarding_arg1, detail::forwarding_arg2, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy>
{
public:
   typedef domain_error<> domain_error_type;
   typedef pole_error<> pole_error_type;
   typedef overflow_error<> overflow_error_type;
   typedef underflow_error<> underflow_error_type;
   typedef denorm_error<> denorm_error_type;
   typedef evaluation_error<> evaluation_error_type;
   typedef rounding_error<> rounding_error_type;
   typedef indeterminate_result_error<> indeterminate_result_error_type;
#if BOOST_MATH_DIGITS10_POLICY == 0
   typedef digits2<> precision_type;
#else
   typedef detail::precision<digits10<>, digits2<> >::type precision_type;
#endif
   typedef promote_float<false> promote_float_type;
   typedef promote_double<false> promote_double_type;
   typedef discrete_quantile<> discrete_quantile_type;
   typedef assert_undefined<> assert_undefined_type;
   typedef max_series_iterations<> max_series_iterations_type;
   typedef max_root_iterations<> max_root_iterations_type;
};

template <class Policy, 
          class A1 = default_policy, 
          class A2 = default_policy, 
          class A3 = default_policy,
          class A4 = default_policy,
          class A5 = default_policy,
          class A6 = default_policy,
          class A7 = default_policy,
          class A8 = default_policy,
          class A9 = default_policy,
          class A10 = default_policy,
          class A11 = default_policy,
          class A12 = default_policy,
          class A13 = default_policy>
struct normalise
{
private:
   typedef mpl::list<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13> arg_list;
   typedef typename detail::find_arg<arg_list, is_domain_error<mpl::_1>, typename Policy::domain_error_type >::type domain_error_type;
   typedef typename detail::find_arg<arg_list, is_pole_error<mpl::_1>, typename Policy::pole_error_type >::type pole_error_type;
   typedef typename detail::find_arg<arg_list, is_overflow_error<mpl::_1>, typename Policy::overflow_error_type >::type overflow_error_type;
   typedef typename detail::find_arg<arg_list, is_underflow_error<mpl::_1>, typename Policy::underflow_error_type >::type underflow_error_type;
   typedef typename detail::find_arg<arg_list, is_denorm_error<mpl::_1>, typename Policy::denorm_error_type >::type denorm_error_type;
   typedef typename detail::find_arg<arg_list, is_evaluation_error<mpl::_1>, typename Policy::evaluation_error_type >::type evaluation_error_type;
   typedef typename detail::find_arg<arg_list, is_rounding_error<mpl::_1>, typename Policy::rounding_error_type >::type rounding_error_type;
   typedef typename detail::find_arg<arg_list, is_indeterminate_result_error<mpl::_1>, typename Policy::indeterminate_result_error_type >::type indeterminate_result_error_type;
   //
   // Now work out the precision:
   //
   typedef typename detail::find_arg<arg_list, is_digits10<mpl::_1>, digits10<> >::type digits10_type;
   typedef typename detail::find_arg<arg_list, is_digits2<mpl::_1>, typename Policy::precision_type >::type bits_precision_type;
   typedef typename detail::precision<digits10_type, bits_precision_type>::type precision_type;
   //
   // Internal promotion:
   //
   typedef typename detail::find_arg<arg_list, is_promote_float<mpl::_1>, typename Policy::promote_float_type >::type promote_float_type;
   typedef typename detail::find_arg<arg_list, is_promote_double<mpl::_1>, typename Policy::promote_double_type >::type promote_double_type;
   //
   // Discrete quantiles:
   //
   typedef typename detail::find_arg<arg_list, is_discrete_quantile<mpl::_1>, typename Policy::discrete_quantile_type >::type discrete_quantile_type;
   //
   // Mathematically undefined properties:
   //
   typedef typename detail::find_arg<arg_list, is_assert_undefined<mpl::_1>, typename Policy::assert_undefined_type >::type assert_undefined_type;
   //
   // Max iterations:
   //
   typedef typename detail::find_arg<arg_list, is_max_series_iterations<mpl::_1>, typename Policy::max_series_iterations_type>::type max_series_iterations_type;
   typedef typename detail::find_arg<arg_list, is_max_root_iterations<mpl::_1>, typename Policy::max_root_iterations_type>::type max_root_iterations_type;
   //
   // Define a typelist of the policies:
   //
   typedef mpl::vector<
      domain_error_type,
      pole_error_type,
      overflow_error_type,
      underflow_error_type,
      denorm_error_type,
      evaluation_error_type,
      rounding_error_type,
      indeterminate_result_error_type,
      precision_type,
      promote_float_type,
      promote_double_type,
      discrete_quantile_type,
      assert_undefined_type,
      max_series_iterations_type,
      max_root_iterations_type> result_list;
   //
   // Remove all the policies that are the same as the default:
   //
   typedef typename mpl::remove_if<result_list, detail::is_default_policy<mpl::_> >::type reduced_list;
   //
   // Pad out the list with defaults:
   //
   typedef typename detail::append_N<reduced_list, default_policy, (14 - ::boost::mpl::size<reduced_list>::value)>::type result_type;
public:
   typedef policy<
      typename mpl::at<result_type, boost::integral_constant<int, 0> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 1> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 2> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 3> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 4> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 5> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 6> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 7> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 8> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 9> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 10> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 11> >::type,
      typename mpl::at<result_type, boost::integral_constant<int, 12> >::type > type;
};
//
// Full specialisation to speed up compilation of the common case:
//
template <>
struct normalise<policy<>, 
          promote_float<false>, 
          promote_double<false>, 
          discrete_quantile<>,
          assert_undefined<>,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy>
{
   typedef policy<detail::forwarding_arg1, detail::forwarding_arg2> type;
};

template <>
struct normalise<policy<detail::forwarding_arg1, detail::forwarding_arg2>,
          promote_float<false>,
          promote_double<false>,
          discrete_quantile<>,
          assert_undefined<>,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy,
          default_policy>
{
   typedef policy<detail::forwarding_arg1, detail::forwarding_arg2> type;
};

inline BOOST_MATH_CONSTEXPR policy<> make_policy() BOOST_NOEXCEPT
{ return policy<>(); }

template <class A1>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1>::type make_policy(const A1&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1>::type result_type;
   return result_type(); 
}

template <class A1, class A2>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2>::type make_policy(const A1&, const A2&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3>::type make_policy(const A1&, const A2&, const A3&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4>::type make_policy(const A1&, const A2&, const A3&, const A4&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&, const A10&) BOOST_NOEXCEPT
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline BOOST_MATH_CONSTEXPR typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&, const A10&, const A11&) BOOST_NOEXCEPT
{
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::type result_type;
   return result_type();
}

//
// Traits class to handle internal promotion:
//
template <class Real, class Policy>
struct evaluation
{
   typedef Real type;
};

template <class Policy>
struct evaluation<float, Policy>
{
   typedef typename mpl::if_<typename Policy::promote_float_type, double, float>::type type;
};

template <class Policy>
struct evaluation<double, Policy>
{
   typedef typename mpl::if_<typename Policy::promote_double_type, long double, double>::type type;
};

#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS

template <class Real>
struct basic_digits : public boost::integral_constant<int, 0>{ };
template <>
struct basic_digits<float> : public boost::integral_constant<int, FLT_MANT_DIG>{ };
template <>
struct basic_digits<double> : public boost::integral_constant<int, DBL_MANT_DIG>{ };
template <>
struct basic_digits<long double> : public boost::integral_constant<int, LDBL_MANT_DIG>{ };

template <class Real, class Policy>
struct precision
{
   BOOST_STATIC_ASSERT( ::std::numeric_limits<Real>::radix == 2);
   typedef typename Policy::precision_type precision_type;
   typedef basic_digits<Real> digits_t;
   typedef typename mpl::if_<
      mpl::equal_to<digits_t, boost::integral_constant<int, 0> >,
      // Possibly unknown precision:
      precision_type,
      typename mpl::if_<
         mpl::or_<mpl::less_equal<digits_t, precision_type>, mpl::less_equal<precision_type, boost::integral_constant<int, 0> > >,
         // Default case, full precision for RealType:
         digits2< ::std::numeric_limits<Real>::digits>,
         // User customised precision:
         precision_type
      >::type
   >::type type;
};

template <class Policy>
struct precision<float, Policy>
{
   typedef digits2<FLT_MANT_DIG> type;
};
template <class Policy>
struct precision<double, Policy>
{
   typedef digits2<DBL_MANT_DIG> type;
};
template <class Policy>
struct precision<long double, Policy>
{
   typedef digits2<LDBL_MANT_DIG> type;
};

#else

template <class Real, class Policy>
struct precision
{
   BOOST_STATIC_ASSERT((::std::numeric_limits<Real>::radix == 2) || ((::std::numeric_limits<Real>::is_specialized == 0) || (::std::numeric_limits<Real>::digits == 0)));
#ifndef __BORLANDC__
   typedef typename Policy::precision_type precision_type;
   typedef typename mpl::if_c<
      ((::std::numeric_limits<Real>::is_specialized == 0) || (::std::numeric_limits<Real>::digits == 0)),
      // Possibly unknown precision:
      precision_type,
      typename mpl::if_c<
         ((::std::numeric_limits<Real>::digits <= precision_type::value) 
         || (Policy::precision_type::value <= 0)),
         // Default case, full precision for RealType:
         digits2< ::std::numeric_limits<Real>::digits>,
         // User customised precision:
         precision_type
      >::type
   >::type type;
#else
   typedef typename Policy::precision_type precision_type;
   typedef boost::integral_constant<int, ::std::numeric_limits<Real>::digits> digits_t;
   typedef boost::integral_constant<bool, ::std::numeric_limits<Real>::is_specialized> spec_t;
   typedef typename mpl::if_<
      mpl::or_<mpl::equal_to<spec_t, boost::true_type>, mpl::equal_to<digits_t, boost::integral_constant<int, 0> > >,
      // Possibly unknown precision:
      precision_type,
      typename mpl::if_<
         mpl::or_<mpl::less_equal<digits_t, precision_type>, mpl::less_equal<precision_type, boost::integral_constant<int, 0> > >,
         // Default case, full precision for RealType:
         digits2< ::std::numeric_limits<Real>::digits>,
         // User customised precision:
         precision_type
      >::type
   >::type type;
#endif
};

#endif

#ifdef BOOST_MATH_USE_FLOAT128

template <class Policy>
struct precision<BOOST_MATH_FLOAT128_TYPE, Policy>
{
   typedef boost::integral_constant<int, 113> type;
};

#endif

namespace detail{

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR int digits_imp(boost::true_type const&) BOOST_NOEXCEPT
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::is_specialized);
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
#endif
   typedef typename boost::math::policies::precision<T, Policy>::type p_t;
   return p_t::value;
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR int digits_imp(boost::false_type const&) BOOST_NOEXCEPT
{
   return tools::digits<T>();
}

} // namespace detail

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_NOEXCEPT
{
   typedef boost::integral_constant<bool, std::numeric_limits<T>::is_specialized > tag_type;
   return detail::digits_imp<T, Policy>(tag_type());
}
template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR int digits_base10(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_NOEXCEPT
{
   return boost::math::policies::digits<T, Policy>() * 301 / 1000L;
}

template <class Policy>
inline BOOST_MATH_CONSTEXPR unsigned long get_max_series_iterations() BOOST_NOEXCEPT
{
   typedef typename Policy::max_series_iterations_type iter_type;
   return iter_type::value;
}

template <class Policy>
inline BOOST_MATH_CONSTEXPR unsigned long get_max_root_iterations() BOOST_NOEXCEPT
{
   typedef typename Policy::max_root_iterations_type iter_type;
   return iter_type::value;
}

namespace detail{

template <class T, class Digits, class Small, class Default>
struct series_factor_calc
{
   static T get() BOOST_MATH_NOEXCEPT(T)
   {
      return ldexp(T(1.0), 1 - Digits::value);
   }
};

template <class T, class Digits>
struct series_factor_calc<T, Digits, boost::true_type, boost::true_type>
{
   static BOOST_MATH_CONSTEXPR T get() BOOST_MATH_NOEXCEPT(T)
   {
      return boost::math::tools::epsilon<T>();
   }
};
template <class T, class Digits>
struct series_factor_calc<T, Digits, boost::true_type, boost::false_type>
{
   static BOOST_MATH_CONSTEXPR T get() BOOST_MATH_NOEXCEPT(T)
   {
      return 1 / static_cast<T>(static_cast<boost::uintmax_t>(1u) << (Digits::value - 1));
   }
};
template <class T, class Digits>
struct series_factor_calc<T, Digits, boost::false_type, boost::true_type>
{
   static BOOST_MATH_CONSTEXPR T get() BOOST_MATH_NOEXCEPT(T)
   {
      return boost::math::tools::epsilon<T>();
   }
};

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T get_epsilon_imp(boost::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::radix == 2);
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_ASSERT(::std::numeric_limits<T>::radix == 2);
#endif
   typedef typename boost::math::policies::precision<T, Policy>::type p_t;
   typedef boost::integral_constant<bool, p_t::value <= std::numeric_limits<boost::uintmax_t>::digits> is_small_int;
   typedef boost::integral_constant<bool, p_t::value >= std::numeric_limits<T>::digits> is_default_value;
   return series_factor_calc<T, p_t, is_small_int, is_default_value>::get();
}

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T get_epsilon_imp(boost::false_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return tools::epsilon<T>();
}

} // namespace detail

template <class T, class Policy>
inline BOOST_MATH_CONSTEXPR T get_epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   typedef boost::integral_constant<bool, (std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::radix == 2)) > tag_type;
   return detail::get_epsilon_imp<T, Policy>(tag_type());
}

namespace detail{

template <class A1, 
          class A2, 
          class A3,
          class A4,
          class A5,
          class A6,
          class A7,
          class A8,
          class A9,
          class A10,
          class A11>
char test_is_policy(const policy<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11>*);
double test_is_policy(...);

template <class P>
struct is_policy_imp
{
   BOOST_STATIC_CONSTANT(bool, value = (sizeof(::boost::math::policies::detail::test_is_policy(static_cast<P*>(0))) == 1));
};

}

template <class P>
struct is_policy : public boost::integral_constant<bool, ::boost::math::policies::detail::is_policy_imp<P>::value> {};

//
// Helper traits class for distribution error handling:
//
template <class Policy>
struct constructor_error_check
{
   typedef typename Policy::domain_error_type domain_error_type;
   typedef typename mpl::if_c<
      (domain_error_type::value == throw_on_error) || (domain_error_type::value == user_error) || (domain_error_type::value == errno_on_error),
      boost::true_type,
      boost::false_type>::type type;
};

template <class Policy>
struct method_error_check
{
   typedef typename Policy::domain_error_type domain_error_type;
   typedef typename mpl::if_c<
      (domain_error_type::value == throw_on_error) && (domain_error_type::value != user_error),
      boost::false_type,
      boost::true_type>::type type;
};
//
// Does the Policy ever throw on error?
//
template <class Policy>
struct is_noexcept_error_policy
{
   typedef typename Policy::domain_error_type               t1;
   typedef typename Policy::pole_error_type                 t2;
   typedef typename Policy::overflow_error_type             t3;
   typedef typename Policy::underflow_error_type            t4;
   typedef typename Policy::denorm_error_type               t5;
   typedef typename Policy::evaluation_error_type           t6;
   typedef typename Policy::rounding_error_type             t7;
   typedef typename Policy::indeterminate_result_error_type t8;

   BOOST_STATIC_CONSTANT(bool, value = 
      ((t1::value != throw_on_error) && (t1::value != user_error)
      && (t2::value != throw_on_error) && (t2::value != user_error)
      && (t3::value != throw_on_error) && (t3::value != user_error)
      && (t4::value != throw_on_error) && (t4::value != user_error)
      && (t5::value != throw_on_error) && (t5::value != user_error)
      && (t6::value != throw_on_error) && (t6::value != user_error)
      && (t7::value != throw_on_error) && (t7::value != user_error)
      && (t8::value != throw_on_error) && (t8::value != user_error)));
};

}}} // namespaces

#endif // BOOST_MATH_POLICY_HPP


/* policy.hpp
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
*/