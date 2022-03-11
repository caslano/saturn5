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

// Boost type traits:
#include <boost/math/tools/config.hpp>
#include <boost/type_traits/is_floating_point.hpp> // for boost::is_floating_point;
#include <boost/type_traits/is_integral.hpp> // for boost::is_integral
#include <boost/type_traits/is_convertible.hpp> // for boost::is_convertible
#include <boost/type_traits/is_same.hpp>// for boost::is_same
#include <boost/type_traits/remove_cv.hpp>// for boost::remove_cv
// Boost Template meta programming:
#include <boost/mpl/if.hpp> // for boost::mpl::if_c.
#include <boost/mpl/and.hpp> // for boost::mpl::if_c.
#include <boost/mpl/or.hpp> // for boost::mpl::if_c.
#include <boost/mpl/not.hpp> // for boost::mpl::if_c.

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
#include <boost/static_assert.hpp>
#endif

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
        typedef typename mpl::if_<is_integral<T>, double, T>::type type;
      };
      // These full specialisations reduce mpl::if_ usage and speed up
      // compilation:
      template <> struct promote_arg<float> { typedef float type; };
      template <> struct promote_arg<double>{ typedef double type; };
      template <> struct promote_arg<long double> { typedef long double type; };
      template <> struct promote_arg<int> {  typedef double type; };

      template <class T1, class T2>
      struct promote_args_2
      { // Promote, if necessary, & pick the wider of the two floating-point types.
        // for both parameter types, if integral promote to double.
        typedef typename promote_arg<T1>::type T1P; // T1 perhaps promoted.
        typedef typename promote_arg<T2>::type T2P; // T2 perhaps promoted.

        typedef typename mpl::if_c<
          is_floating_point<T1P>::value && is_floating_point<T2P>::value, // both T1P and T2P are floating-point?
#ifdef BOOST_MATH_USE_FLOAT128
           typename mpl::if_c<is_same<__float128, T1P>::value || is_same<__float128, T2P>::value, // either long double?
            __float128,
#endif
             typename mpl::if_c<is_same<long double, T1P>::value || is_same<long double, T2P>::value, // either long double?
               long double, // then result type is long double.
               typename mpl::if_c<is_same<double, T1P>::value || is_same<double, T2P>::value, // either double?
                  double, // result type is double.
                  float // else result type is float.
             >::type
#ifdef BOOST_MATH_USE_FLOAT128
             >::type
#endif
             >::type,
          // else one or the other is a user-defined type:
          typename mpl::if_c<!is_floating_point<T2P>::value && ::boost::is_convertible<T1P, T2P>::value, T2P, T1P>::type>::type type;
      }; // promote_arg2
      // These full specialisations reduce mpl::if_ usage and speed up
      // compilation:
      template <> struct promote_args_2<float, float> { typedef float type; };
      template <> struct promote_args_2<double, double>{ typedef double type; };
      template <> struct promote_args_2<long double, long double> { typedef long double type; };
      template <> struct promote_args_2<int, int> {  typedef double type; };
      template <> struct promote_args_2<int, float> {  typedef double type; };
      template <> struct promote_args_2<float, int> {  typedef double type; };
      template <> struct promote_args_2<int, double> {  typedef double type; };
      template <> struct promote_args_2<double, int> {  typedef double type; };
      template <> struct promote_args_2<int, long double> {  typedef long double type; };
      template <> struct promote_args_2<long double, int> {  typedef long double type; };
      template <> struct promote_args_2<float, double> {  typedef double type; };
      template <> struct promote_args_2<double, float> {  typedef double type; };
      template <> struct promote_args_2<float, long double> {  typedef long double type; };
      template <> struct promote_args_2<long double, float> {  typedef long double type; };
      template <> struct promote_args_2<double, long double> {  typedef long double type; };
      template <> struct promote_args_2<long double, double> {  typedef long double type; };

      template <class T1, class T2=float, class T3=float, class T4=float, class T5=float, class T6=float>
      struct promote_args
      {
         typedef typename promote_args_2<
            typename remove_cv<T1>::type,
            typename promote_args_2<
               typename remove_cv<T2>::type,
               typename promote_args_2<
                  typename remove_cv<T3>::type,
                  typename promote_args_2<
                     typename remove_cv<T4>::type,
                     typename promote_args_2<
                        typename remove_cv<T5>::type, typename remove_cv<T6>::type
                     >::type
                  >::type
               >::type
            >::type
         >::type type;

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
         //
         // Guard against use of long double if it's not supported:
         //
         BOOST_STATIC_ASSERT_MSG((0 == ::boost::is_same<type, long double>::value), "Sorry, but this platform does not have sufficient long double support for the special functions to be reliably implemented.");
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
         typedef typename promote_args_2<
            typename remove_cv<T1>::type,
            typename promote_args_2<
               typename remove_cv<T2>::type,
               typename promote_args_2<
                  typename remove_cv<T3>::type,
                  typename promote_args_2<
                     typename remove_cv<T4>::type,
                     typename promote_args_2<
                        typename remove_cv<T5>::type, typename remove_cv<T6>::type
                     >::type
                  >::type
               >::type
            >::type
         >::type type;
      };

    } // namespace tools
  } // namespace math
} // namespace boost

#endif // BOOST_MATH_PROMOTION_HPP


/* promotion.hpp
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
*/