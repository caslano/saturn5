// boost\math\tools\promotion.hpp

// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Promote arguments functions to allow math functions to have arguments
// provided as integer OR real (floating-point, built-in or UDT)
// (called ArithmeticType in functions that use promotion)
// that help to reduce the risk of creating multiple instantiations.
// Allows creation of an inline wrapper that forwards to a foo(RT, RT) function,
// so you never get to instantiate any mixed foo(RT, IT) functions.

#ifndef BOOST_MATH_PROMOTION_HPP
#define BOOST_MATH_PROMOTION_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <type_traits>

namespace boost
{
  namespace math
  {
    namespace tools
    {
      // If either T1 or T2 is an integer type,
      // pretend it was a double (for the purposes of further analysis).
      // Then pick the wider of the two floating-point types
      // as the actual signature to forward to.
      // For example:
      // foo(int, short) -> double foo(double, double);
      // foo(int, float) -> double foo(double, double);
      // Note: NOT float foo(float, float)
      // foo(int, double) -> foo(double, double);
      // foo(double, float) -> double foo(double, double);
      // foo(double, float) -> double foo(double, double);
      // foo(any-int-or-float-type, long double) -> foo(long double, long double);
      // but ONLY float foo(float, float) is unchanged.
      // So the only way to get an entirely float version is to call foo(1.F, 2.F),
      // But since most (all?) the math functions convert to double internally,
      // probably there would not be the hoped-for gain by using float here.

      // This follows the C-compatible conversion rules of pow, etc
      // where pow(int, float) is converted to pow(double, double).

      template <class T>
      struct promote_arg
      { // If T is integral type, then promote to double.
        using type = typename std::conditional<std::is_integral<T>::value, double, T>::type;
      };
      // These full specialisations reduce std::conditional usage and speed up
      // compilation:
      template <> struct promote_arg<float> { using type = float; };
      template <> struct promote_arg<double>{ using type = double; };
      template <> struct promote_arg<long double> { using type = long double; };
      template <> struct promote_arg<int> {  using type = double; };

      template <class T1, class T2>
      struct promote_args_2
      { // Promote, if necessary, & pick the wider of the two floating-point types.
        // for both parameter types, if integral promote to double.
        using T1P = typename promote_arg<T1>::type; // T1 perhaps promoted.
        using T2P = typename promote_arg<T2>::type; // T2 perhaps promoted.

        using type = typename std::conditional<
          std::is_floating_point<T1P>::value && std::is_floating_point<T2P>::value, // both T1P and T2P are floating-point?
#ifdef BOOST_MATH_USE_FLOAT128
           typename std::conditional<std::is_same<__float128, T1P>::value || std::is_same<__float128, T2P>::value, // either long double?
            __float128,
#endif
             typename std::conditional<std::is_same<long double, T1P>::value || std::is_same<long double, T2P>::value, // either long double?
               long double, // then result type is long double.
               typename std::conditional<std::is_same<double, T1P>::value || std::is_same<double, T2P>::value, // either double?
                  double, // result type is double.
                  float // else result type is float.
             >::type
#ifdef BOOST_MATH_USE_FLOAT128
             >::type
#endif
             >::type,
          // else one or the other is a user-defined type:
          typename std::conditional<!std::is_floating_point<T2P>::value && std::is_convertible<T1P, T2P>::value, T2P, T1P>::type>::type;
      }; // promote_arg2
      // These full specialisations reduce std::conditional usage and speed up
      // compilation:
      template <> struct promote_args_2<float, float> { using type = float; };
      template <> struct promote_args_2<double, double>{ using type = double; };
      template <> struct promote_args_2<long double, long double> { using type = long double; };
      template <> struct promote_args_2<int, int> {  using type = double; };
      template <> struct promote_args_2<int, float> {  using type = double; };
      template <> struct promote_args_2<float, int> {  using type = double; };
      template <> struct promote_args_2<int, double> {  using type = double; };
      template <> struct promote_args_2<double, int> {  using type = double; };
      template <> struct promote_args_2<int, long double> {  using type = long double; };
      template <> struct promote_args_2<long double, int> {  using type = long double; };
      template <> struct promote_args_2<float, double> {  using type = double; };
      template <> struct promote_args_2<double, float> {  using type = double; };
      template <> struct promote_args_2<float, long double> {  using type = long double; };
      template <> struct promote_args_2<long double, float> {  using type = long double; };
      template <> struct promote_args_2<double, long double> {  using type = long double; };
      template <> struct promote_args_2<long double, double> {  using type = long double; };

      template <class T1, class T2=float, class T3=float, class T4=float, class T5=float, class T6=float>
      struct promote_args
      {
         using type = typename promote_args_2<
            typename std::remove_cv<T1>::type,
            typename promote_args_2<
               typename std::remove_cv<T2>::type,
               typename promote_args_2<
                  typename std::remove_cv<T3>::type,
                  typename promote_args_2<
                     typename std::remove_cv<T4>::type,
                     typename promote_args_2<
                        typename std::remove_cv<T5>::type, typename std::remove_cv<T6>::type
                     >::type
                  >::type
               >::type
            >::type
         >::type;

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
         //
         // Guard against use of long double if it's not supported:
         //
         static_assert((0 == std::is_same<type, long double>::value), "Sorry, but this platform does not have sufficient long double support for the special functions to be reliably implemented.");
#endif
      };

      //
      // This struct is the same as above, but has no static assert on long double usage,
      // it should be used only on functions that can be implemented for long double
      // even when std lib support is missing or broken for that type.
      //
      template <class T1, class T2=float, class T3=float, class T4=float, class T5=float, class T6=float>
      struct promote_args_permissive
      {
         using type = typename promote_args_2<
            typename std::remove_cv<T1>::type,
            typename promote_args_2<
               typename std::remove_cv<T2>::type,
               typename promote_args_2<
                  typename std::remove_cv<T3>::type,
                  typename promote_args_2<
                     typename std::remove_cv<T4>::type,
                     typename promote_args_2<
                        typename std::remove_cv<T5>::type, typename std::remove_cv<T6>::type
                     >::type
                  >::type
               >::type
            >::type
         >::type;
      };

    } // namespace tools
  } // namespace math
} // namespace boost

#endif // BOOST_MATH_PROMOTION_HPP


/* promotion.hpp
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
*/