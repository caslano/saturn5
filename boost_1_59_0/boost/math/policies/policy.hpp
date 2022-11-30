//  Copyright John Maddock 2007.
//  Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POLICY_HPP
#define BOOST_MATH_POLICY_HPP

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/mp.hpp>
#include <limits>
#include <type_traits>
#include <cmath>
#include <cstdint>
#include <cstddef>

namespace boost{ namespace math{ 

namespace mp = tools::meta_programming;

namespace tools{

template <class T>
constexpr int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept;
template <class T>
constexpr T epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value);

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

#define BOOST_MATH_META_INT(Type, name, Default)                                                \
   template <Type N = Default>                                                                  \
   class name : public std::integral_constant<int, N>{};                                        \
                                                                                                \
   namespace detail{                                                                            \
   template <Type N>                                                                            \
   char test_is_valid_arg(const name<N>* = nullptr);                                            \
   char test_is_default_arg(const name<Default>* = nullptr);                                    \
                                                                                                \
   template <typename T>                                                                        \
   class is_##name##_imp                                                                        \
   {                                                                                            \
   private:                                                                                     \
      template <Type N>                                                                         \
      static char test(const name<N>* = nullptr);                                               \
      static double test(...);                                                                  \
   public:                                                                                      \
      static constexpr bool value = sizeof(test(static_cast<T*>(0))) == sizeof(char);           \
   };                                                                                           \
   }                                                                                            \
                                                                                                \
   template <typename T>                                                                        \
   class is_##name                                                                              \
   {                                                                                            \
   public:                                                                                      \
      static constexpr bool value = boost::math::policies::detail::is_##name##_imp<T>::value;   \
      using type = std::integral_constant<bool, value>;                                         \
   };

#define BOOST_MATH_META_BOOL(name, Default)                                                     \
   template <bool N = Default>                                                                  \
   class name : public std::integral_constant<bool, N>{};                                       \
                                                                                                \
   namespace detail{                                                                            \
   template <bool N>                                                                            \
   char test_is_valid_arg(const name<N>* = nullptr);                                            \
   char test_is_default_arg(const name<Default>* = nullptr);                                    \
                                                                                                \
   template <typename T>                                                                        \
   class is_##name##_imp                                                                        \
   {                                                                                            \
   private:                                                                                     \
      template <bool N>                                                                         \
      static char test(const name<N>* = nullptr);                                               \
      static double test(...);                                                                  \
   public:                                                                                      \
      static constexpr bool value = sizeof(test(static_cast<T*>(0))) == sizeof(char);           \
   };                                                                                           \
   }                                                                                            \
                                                                                                \
   template <typename T>                                                                        \
   class is_##name                                                                              \
   {                                                                                            \
   public:                                                                                      \
      static constexpr bool value = boost::math::policies::detail::is_##name##_imp<T>::value;   \
      using type = std::integral_constant<bool, value>;                                         \
   };

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
   using digits2_type = typename std::conditional<
      (Digits10::value == 0),
      digits2<0>,
      digits2<((Digits10::value + 1) * 1000L) / 301L>
   >::type;
public:
#ifdef BOOST_BORLANDC
   using type = typename std::conditional<
      (Digits2::value > ::boost::math::policies::detail::precision<Digits10,Digits2>::digits2_type::value),
      Digits2, digits2_type>::type;
#else
   using type = typename std::conditional<
      (Digits2::value > digits2_type::value),
      Digits2, digits2_type>::type;
#endif
};

double test_is_valid_arg(...);
double test_is_default_arg(...);
char test_is_valid_arg(const default_policy*);
char test_is_default_arg(const default_policy*);

template <typename T>
class is_valid_policy_imp 
{
public:
   static constexpr bool value = sizeof(boost::math::policies::detail::test_is_valid_arg(static_cast<T*>(0))) == sizeof(char);
};

template <typename T> 
class is_valid_policy 
{
public:
   static constexpr bool value = boost::math::policies::detail::is_valid_policy_imp<T>::value;
};

template <typename T>
class is_default_policy_imp
{
public:
   static constexpr bool value = sizeof(boost::math::policies::detail::test_is_default_arg(static_cast<T*>(0))) == sizeof(char);
};

template <typename T>
class is_default_policy
{
public:
   static constexpr bool value = boost::math::policies::detail::is_default_policy_imp<T>::value;
   using type = std::integral_constant<bool, value>;

   template <typename U>
   struct apply
   {
      using type = is_default_policy<U>;
   };
};

template <class Seq, class T, std::size_t N>
struct append_N
{
   using type = typename append_N<mp::mp_push_back<Seq, T>, T, N-1>::type;
};

template <class Seq, class T>
struct append_N<Seq, T, 0>
{
   using type = Seq;
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
template <typename A1  = default_policy, 
          typename A2  = default_policy, 
          typename A3  = default_policy,
          typename A4  = default_policy,
          typename A5  = default_policy,
          typename A6  = default_policy,
          typename A7  = default_policy,
          typename A8  = default_policy,
          typename A9  = default_policy,
          typename A10 = default_policy,
          typename A11 = default_policy,
          typename A12 = default_policy,
          typename A13 = default_policy>
class policy
{
private:
   //
   // Validate all our arguments:
   //
   static_assert(::boost::math::policies::detail::is_valid_policy<A1>::value, "::boost::math::policies::detail::is_valid_policy<A1>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A2>::value, "::boost::math::policies::detail::is_valid_policy<A2>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A3>::value, "::boost::math::policies::detail::is_valid_policy<A3>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A4>::value, "::boost::math::policies::detail::is_valid_policy<A4>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A5>::value, "::boost::math::policies::detail::is_valid_policy<A5>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A6>::value, "::boost::math::policies::detail::is_valid_policy<A6>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A7>::value, "::boost::math::policies::detail::is_valid_policy<A7>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A8>::value, "::boost::math::policies::detail::is_valid_policy<A8>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A9>::value, "::boost::math::policies::detail::is_valid_policy<A9>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A10>::value, "::boost::math::policies::detail::is_valid_policy<A10>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A11>::value, "::boost::math::policies::detail::is_valid_policy<A11>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A12>::value, "::boost::math::policies::detail::is_valid_policy<A12>::value");
   static_assert(::boost::math::policies::detail::is_valid_policy<A13>::value, "::boost::math::policies::detail::is_valid_policy<A13>::value");
   //
   // Typelist of the arguments:
   //
   using arg_list = mp::mp_list<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13>;
   static constexpr std::size_t arg_list_size = mp::mp_size<arg_list>::value;

   template<typename A, typename B, bool b>
   struct pick_arg
   {
      using type = A;
   };

   template<typename A, typename B>
   struct pick_arg<A, B, false>
   {
      using type = mp::mp_at<arg_list, B>;
   };

   template<typename Fn, typename Default>
   class arg_type
   {
   private:
      using index = mp::mp_find_if_q<arg_list, Fn>;
      static constexpr bool end = (index::value >= arg_list_size);
   public:
      using type = typename pick_arg<Default, index, end>::type;
   };

   // Work out the base 2 and 10 precisions to calculate the public precision_type:
   using digits10_type = typename arg_type<mp::mp_quote_trait<is_digits10>, digits10<>>::type;
   using bits_precision_type = typename arg_type<mp::mp_quote_trait<is_digits2>, digits2<>>::type;

public:

   // Error Types:
   using domain_error_type = typename arg_type<mp::mp_quote_trait<is_domain_error>, domain_error<>>::type;
   using pole_error_type = typename arg_type<mp::mp_quote_trait<is_pole_error>, pole_error<>>::type;
   using overflow_error_type = typename arg_type<mp::mp_quote_trait<is_overflow_error>, overflow_error<>>::type;
   using underflow_error_type = typename arg_type<mp::mp_quote_trait<is_underflow_error>, underflow_error<>>::type;
   using denorm_error_type = typename arg_type<mp::mp_quote_trait<is_denorm_error>, denorm_error<>>::type;
   using evaluation_error_type = typename arg_type<mp::mp_quote_trait<is_evaluation_error>, evaluation_error<>>::type;
   using rounding_error_type = typename arg_type<mp::mp_quote_trait<is_rounding_error>, rounding_error<>>::type;
   using indeterminate_result_error_type = typename arg_type<mp::mp_quote_trait<is_indeterminate_result_error>, indeterminate_result_error<>>::type;
   
   // Precision:
   using precision_type = typename detail::precision<digits10_type, bits_precision_type>::type;

   // Internal promotion:
   using promote_float_type = typename arg_type<mp::mp_quote_trait<is_promote_float>, promote_float<>>::type;
   using promote_double_type = typename arg_type<mp::mp_quote_trait<is_promote_double>, promote_double<>>::type;

   // Discrete quantiles:
   using discrete_quantile_type = typename arg_type<mp::mp_quote_trait<is_discrete_quantile>, discrete_quantile<>>::type;
   
   // Mathematically undefined properties:
   using assert_undefined_type = typename arg_type<mp::mp_quote_trait<is_assert_undefined>, assert_undefined<>>::type;

   // Max iterations:
   using max_series_iterations_type = typename arg_type<mp::mp_quote_trait<is_max_series_iterations>, max_series_iterations<>>::type;
   using max_root_iterations_type = typename arg_type<mp::mp_quote_trait<is_max_root_iterations>, max_root_iterations<>>::type;
};

//
// These full specializations are defined to reduce the amount of
// template instantiations that have to take place when using the default
// policies, they have quite a large impact on compile times:
//
template <>
class policy<default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy>
{
public:
   using domain_error_type = domain_error<>;
   using pole_error_type = pole_error<>;
   using overflow_error_type = overflow_error<>;
   using underflow_error_type = underflow_error<>;
   using denorm_error_type = denorm_error<>;
   using evaluation_error_type = evaluation_error<>;
   using rounding_error_type = rounding_error<>;
   using indeterminate_result_error_type = indeterminate_result_error<>;
#if BOOST_MATH_DIGITS10_POLICY == 0
   using precision_type = digits2<>;
#else
   using precision_type = detail::precision<digits10<>, digits2<>>::type;
#endif
   using promote_float_type = promote_float<>;
   using promote_double_type = promote_double<>;
   using discrete_quantile_type = discrete_quantile<>;
   using assert_undefined_type = assert_undefined<>;
   using max_series_iterations_type = max_series_iterations<>;
   using max_root_iterations_type = max_root_iterations<>;
};

template <>
struct policy<detail::forwarding_arg1, detail::forwarding_arg2, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy, default_policy>
{
public:
   using domain_error_type = domain_error<>;
   using pole_error_type = pole_error<>;
   using overflow_error_type = overflow_error<>;
   using underflow_error_type = underflow_error<>;
   using denorm_error_type = denorm_error<>;
   using evaluation_error_type = evaluation_error<>;
   using rounding_error_type = rounding_error<>;
   using indeterminate_result_error_type = indeterminate_result_error<>;
#if BOOST_MATH_DIGITS10_POLICY == 0
   using precision_type = digits2<>;
#else
   using precision_type = detail::precision<digits10<>, digits2<>>::type;
#endif
   using promote_float_type = promote_float<false>;
   using promote_double_type = promote_double<false>;
   using discrete_quantile_type = discrete_quantile<>;
   using assert_undefined_type = assert_undefined<>;
   using max_series_iterations_type = max_series_iterations<>;
   using max_root_iterations_type = max_root_iterations<>;
};

template <typename Policy, 
          typename A1  = default_policy, 
          typename A2  = default_policy, 
          typename A3  = default_policy,
          typename A4  = default_policy,
          typename A5  = default_policy,
          typename A6  = default_policy,
          typename A7  = default_policy,
          typename A8  = default_policy,
          typename A9  = default_policy,
          typename A10 = default_policy,
          typename A11 = default_policy,
          typename A12 = default_policy,
          typename A13 = default_policy>
class normalise
{
private:
   using arg_list = mp::mp_list<A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13>;
   static constexpr std::size_t arg_list_size = mp::mp_size<arg_list>::value;

   template<typename A, typename B, bool b>
   struct pick_arg
   {
      using type = A;
   };

   template<typename A, typename B>
   struct pick_arg<A, B, false>
   {
      using type = mp::mp_at<arg_list, B>;
   };

   template<typename Fn, typename Default>
   class arg_type
   {
   private:
      using index = mp::mp_find_if_q<arg_list, Fn>;
      static constexpr bool end = (index::value >= arg_list_size);
   public:
      using type = typename pick_arg<Default, index, end>::type;
   };

   // Error types:
   using domain_error_type = typename arg_type<mp::mp_quote_trait<is_domain_error>, typename Policy::domain_error_type>::type;
   using pole_error_type = typename arg_type<mp::mp_quote_trait<is_pole_error>, typename Policy::pole_error_type>::type;
   using overflow_error_type = typename arg_type<mp::mp_quote_trait<is_overflow_error>, typename Policy::overflow_error_type>::type;
   using underflow_error_type = typename arg_type<mp::mp_quote_trait<is_underflow_error>, typename Policy::underflow_error_type>::type;
   using denorm_error_type = typename arg_type<mp::mp_quote_trait<is_denorm_error>, typename Policy::denorm_error_type>::type;
   using evaluation_error_type = typename arg_type<mp::mp_quote_trait<is_evaluation_error>, typename Policy::evaluation_error_type>::type;
   using rounding_error_type = typename arg_type<mp::mp_quote_trait<is_rounding_error>, typename Policy::rounding_error_type>::type;
   using indeterminate_result_error_type = typename arg_type<mp::mp_quote_trait<is_indeterminate_result_error>, typename Policy::indeterminate_result_error_type>::type;

   // Precision:
   using digits10_type = typename arg_type<mp::mp_quote_trait<is_digits10>, digits10<>>::type;
   using bits_precision_type = typename arg_type<mp::mp_quote_trait<is_digits2>, typename Policy::precision_type>::type;
   using precision_type = typename detail::precision<digits10_type, bits_precision_type>::type;

   // Internal promotion:
   using promote_float_type = typename arg_type<mp::mp_quote_trait<is_promote_float>, typename Policy::promote_float_type>::type;
   using promote_double_type = typename arg_type<mp::mp_quote_trait<is_promote_double>, typename Policy::promote_double_type>::type;

   // Discrete quantiles:
   using discrete_quantile_type = typename arg_type<mp::mp_quote_trait<is_discrete_quantile>, typename Policy::discrete_quantile_type>::type;

   // Mathematically undefined properties:
   using assert_undefined_type = typename arg_type<mp::mp_quote_trait<is_assert_undefined>, typename Policy::assert_undefined_type>::type;

   // Max iterations:
   using max_series_iterations_type = typename arg_type<mp::mp_quote_trait<is_max_series_iterations>, typename Policy::max_series_iterations_type>::type;
   using max_root_iterations_type = typename arg_type<mp::mp_quote_trait<is_max_root_iterations>, typename Policy::max_root_iterations_type>::type;

   // Define a typelist of the policies:
   using result_list = mp::mp_list<
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
      max_root_iterations_type>;

   // Remove all the policies that are the same as the default:
   using fn = mp::mp_quote_trait<detail::is_default_policy>;
   using reduced_list = mp::mp_remove_if_q<result_list, fn>;
   
   // Pad out the list with defaults:
   using result_type = typename detail::append_N<reduced_list, default_policy, (14UL - mp::mp_size<reduced_list>::value)>::type;

public:
   using type = policy<
      mp::mp_at_c<result_type, 0>,
      mp::mp_at_c<result_type, 1>,
      mp::mp_at_c<result_type, 2>,
      mp::mp_at_c<result_type, 3>,
      mp::mp_at_c<result_type, 4>,
      mp::mp_at_c<result_type, 5>,
      mp::mp_at_c<result_type, 6>,
      mp::mp_at_c<result_type, 7>,
      mp::mp_at_c<result_type, 8>,
      mp::mp_at_c<result_type, 9>,
      mp::mp_at_c<result_type, 10>,
      mp::mp_at_c<result_type, 11>,
      mp::mp_at_c<result_type, 12>
      >;
};

// Full specialisation to speed up compilation of the common case:
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
   using type = policy<detail::forwarding_arg1, detail::forwarding_arg2>;
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
   using type = policy<detail::forwarding_arg1, detail::forwarding_arg2>;
};

inline constexpr policy<> make_policy() noexcept
{ return policy<>(); }

template <class A1>
inline constexpr typename normalise<policy<>, A1>::type make_policy(const A1&) noexcept
{ 
   typedef typename normalise<policy<>, A1>::type result_type;
   return result_type(); 
}

template <class A1, class A2>
inline constexpr typename normalise<policy<>, A1, A2>::type make_policy(const A1&, const A2&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3>
inline constexpr typename normalise<policy<>, A1, A2, A3>::type make_policy(const A1&, const A2&, const A3&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4>::type make_policy(const A1&, const A2&, const A3&, const A4&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&, const A10&) noexcept
{ 
   typedef typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10>::type result_type;
   return result_type(); 
}

template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, class A10, class A11>
inline constexpr typename normalise<policy<>, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11>::type make_policy(const A1&, const A2&, const A3&, const A4&, const A5&, const A6&, const A7&, const A8&, const A9&, const A10&, const A11&) noexcept
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
   using type = typename std::conditional<Policy::promote_float_type::value, double, float>::type;
};

template <class Policy>
struct evaluation<double, Policy>
{
   using type = typename std::conditional<Policy::promote_double_type::value, long double, double>::type;
};

template <class Real, class Policy>
struct precision
{
   static_assert((std::numeric_limits<Real>::radix == 2) || ((std::numeric_limits<Real>::is_specialized == 0) || (std::numeric_limits<Real>::digits == 0)),
   "(std::numeric_limits<Real>::radix == 2) || ((std::numeric_limits<Real>::is_specialized == 0) || (std::numeric_limits<Real>::digits == 0))");
#ifndef BOOST_BORLANDC
   using precision_type = typename Policy::precision_type;
   using type = typename std::conditional<
      ((std::numeric_limits<Real>::is_specialized == 0) || (std::numeric_limits<Real>::digits == 0)),
      // Possibly unknown precision:
      precision_type,
      typename std::conditional<
         ((std::numeric_limits<Real>::digits <= precision_type::value) 
         || (Policy::precision_type::value <= 0)),
         // Default case, full precision for RealType:
         digits2< std::numeric_limits<Real>::digits>,
         // User customised precision:
         precision_type
      >::type
   >::type;
#else
   using precision_type = typename Policy::precision_type;
   using digits_t = std::integral_constant<int, std::numeric_limits<Real>::digits>;
   using spec_t = std::integral_constant<bool, std::numeric_limits<Real>::is_specialized>;
   using type = typename std::conditional<
      (spec_t::value == true std::true_type || digits_t::value == 0),
      // Possibly unknown precision:
      precision_type,
      typename std::conditional<
         (digits_t::value <= precision_type::value || precision_type::value <= 0),
         // Default case, full precision for RealType:
         digits2< std::numeric_limits<Real>::digits>,
         // User customised precision:
         precision_type
      >::type
   >::type;
#endif
};

#ifdef BOOST_MATH_USE_FLOAT128

template <class Policy>
struct precision<BOOST_MATH_FLOAT128_TYPE, Policy>
{
   typedef std::integral_constant<int, 113> type;
};

#endif

namespace detail{

template <class T, class Policy>
inline constexpr int digits_imp(std::true_type const&) noexcept
{
   static_assert( std::numeric_limits<T>::is_specialized, "std::numeric_limits<T>::is_specialized");
   typedef typename boost::math::policies::precision<T, Policy>::type p_t;
   return p_t::value;
}

template <class T, class Policy>
inline constexpr int digits_imp(std::false_type const&) noexcept
{
   return tools::digits<T>();
}

} // namespace detail

template <class T, class Policy>
inline constexpr int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept
{
   typedef std::integral_constant<bool, std::numeric_limits<T>::is_specialized > tag_type;
   return detail::digits_imp<T, Policy>(tag_type());
}
template <class T, class Policy>
inline constexpr int digits_base10(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept
{
   return boost::math::policies::digits<T, Policy>() * 301 / 1000L;
}

template <class Policy>
inline constexpr unsigned long get_max_series_iterations() noexcept
{
   typedef typename Policy::max_series_iterations_type iter_type;
   return iter_type::value;
}

template <class Policy>
inline constexpr unsigned long get_max_root_iterations() noexcept
{
   typedef typename Policy::max_root_iterations_type iter_type;
   return iter_type::value;
}

namespace detail{

template <class T, class Digits, class Small, class Default>
struct series_factor_calc
{
   static T get() noexcept(std::is_floating_point<T>::value)
   {
      return ldexp(T(1.0), 1 - Digits::value);
   }
};

template <class T, class Digits>
struct series_factor_calc<T, Digits, std::true_type, std::true_type>
{
   static constexpr T get() noexcept(std::is_floating_point<T>::value)
   {
      return boost::math::tools::epsilon<T>();
   }
};
template <class T, class Digits>
struct series_factor_calc<T, Digits, std::true_type, std::false_type>
{
   static constexpr T get() noexcept(std::is_floating_point<T>::value)
   {
      return 1 / static_cast<T>(static_cast<std::uintmax_t>(1u) << (Digits::value - 1));
   }
};
template <class T, class Digits>
struct series_factor_calc<T, Digits, std::false_type, std::true_type>
{
   static constexpr T get() noexcept(std::is_floating_point<T>::value)
   {
      return boost::math::tools::epsilon<T>();
   }
};

template <class T, class Policy>
inline constexpr T get_epsilon_imp(std::true_type const&) noexcept(std::is_floating_point<T>::value)
{
   static_assert(std::numeric_limits<T>::is_specialized, "std::numeric_limits<T>::is_specialized");
   static_assert(std::numeric_limits<T>::radix == 2, "std::numeric_limits<T>::radix == 2");

   typedef typename boost::math::policies::precision<T, Policy>::type p_t;
   typedef std::integral_constant<bool, p_t::value <= std::numeric_limits<std::uintmax_t>::digits> is_small_int;
   typedef std::integral_constant<bool, p_t::value >= std::numeric_limits<T>::digits> is_default_value;
   return series_factor_calc<T, p_t, is_small_int, is_default_value>::get();
}

template <class T, class Policy>
inline constexpr T get_epsilon_imp(std::false_type const&) noexcept(std::is_floating_point<T>::value)
{
   return tools::epsilon<T>();
}

} // namespace detail

template <class T, class Policy>
inline constexpr T get_epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   typedef std::integral_constant<bool, (std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::radix == 2)) > tag_type;
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

template <typename P>
class is_policy_imp
{
public:
   static constexpr bool value = (sizeof(::boost::math::policies::detail::test_is_policy(static_cast<P*>(0))) == sizeof(char));
};

}

template <typename P>
class is_policy
{
public:
   static constexpr bool value = boost::math::policies::detail::is_policy_imp<P>::value;
   using type = std::integral_constant<bool, value>;
};

//
// Helper traits class for distribution error handling:
//
template <class Policy>
struct constructor_error_check
{
   using domain_error_type = typename Policy::domain_error_type;
   using type = typename std::conditional<
      (domain_error_type::value == throw_on_error) || (domain_error_type::value == user_error) || (domain_error_type::value == errno_on_error),
      std::true_type,
      std::false_type>::type;
};

template <class Policy>
struct method_error_check
{
   using domain_error_type = typename Policy::domain_error_type;
   using type = typename std::conditional<
      (domain_error_type::value == throw_on_error) && (domain_error_type::value != user_error),
      std::false_type,
      std::true_type>::type;
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

   static constexpr bool value = 
      ((t1::value != throw_on_error) && (t1::value != user_error)
      && (t2::value != throw_on_error) && (t2::value != user_error)
      && (t3::value != throw_on_error) && (t3::value != user_error)
      && (t4::value != throw_on_error) && (t4::value != user_error)
      && (t5::value != throw_on_error) && (t5::value != user_error)
      && (t6::value != throw_on_error) && (t6::value != user_error)
      && (t7::value != throw_on_error) && (t7::value != user_error)
      && (t8::value != throw_on_error) && (t8::value != user_error));
};

}}} // namespaces

#endif // BOOST_MATH_POLICY_HPP


/* policy.hpp
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
*/