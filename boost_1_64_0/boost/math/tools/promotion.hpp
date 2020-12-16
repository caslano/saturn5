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
81a3WV1JUZQ+dIukFMOmzCoIewjhtKbVBY5p3R2jmejQYaaLZi/HqfemLMNUFqlI5/qwJ0FTFNATzPyM2bt8l3OuE3mlLGKhPPMMs4J3YFXKmpl4J97N000Vb9CARsHkYIN0W93abfPe4GdhIrMih9KreOsGPrbctvt1Nv6xYVWHMilKgfXk3HFBrDnrBEWMKhkKvc2OKVymgG35JJPjqXVqHgdBLg7rPR+cxkHhJk+2+T1h+oLNW4kgkXWTSLFv6v+kucbSDITaDi68tBAzuPU8raeCdqonzJ4sTzOOszRP40L4QSdRk1/lc+5JD2ntODfjzJcn/Hnt2MJqexd2ZUA0WC8CDW/XOvGD/mjTnDXYayYUbcQF2zHC/HlLB9NbQYx5J7ZVYZxLpdbY9YVtSMd1snmfvh2/25c1LbkLd7botACld9hX23T9ZIH8p+60aOa5AtFfczdDH5xUOV7rs/r+xd01HS+E8nfkt9/TphnhFJtqN9KhGpRoXSsW/cK9GR2fRxL91H2RrinYJha92WPTTXVT/u6n6MbTBPJT2cT9gU5+Jtjb/tsegDSuD4Z+3YOIPkoXFvYyOmoq0X/xYEPv90k86BvFsCW63jlDIZbfg4chxrp1Y7fdxKMM/cRR5bjd4v2dTTPpE10+xqJT8cgv4aRN1zmjsu1HGn87YXhvPYB0pU7Iq9YWa2ptkTVRGe67YXLoRg++k2+w1xF1rPWps/aWu6j9r/XFtd7yAhA6Xtwc32ivJxnoYI7o12/i9GyFrwt+wOnkbM6O/7eZYYzDuYe3edii6JfNLsVkf4c9T0qT1E9kIMX6/JSyoosrZEFp/Xqr5pmdPbm8LCaH/xzAf+/Hf++bxH9aX+svV/UeTCl3dmyP6Db9dVXvQfetdx87xpFGLt6Yr7w3KBrKPjGmZIOLxmpG//frdVr7VVpsj/ON+uvqMfAkbCycTX+Tps/bdO236u0gT7xdlVl1Ye1En/khPaX4KJ9M5psVzXa159DfoujMjR7zm4h0stfkrx1pTC7ef5qw4oTA8zzYWF5VPqLu086hiA5kFUFlbLWlXWQ0HcFkrKX9wKb1e8odh6Gd2mynOX8cFgfky+0rd1b9B5cvs8fUX1R+HtiO5Yz3mAote8PU4oH9itZi/jNr7c3tz8MmEetHtV7S3tgv3jZhYZJSxr5fiRciDHQCcb+ycPv0e5Qkb4I6Fgp4SP146qdSP6H6idVPpn6k+onUj3Pn+5It88a0LnLpB76WmKqfWv2UDjesmY625WN5ytTlxVw2qRbwFPVzGHkxh435W71xDvGNyrPbeejb7TQSUdWyzj2oIiP/6eZvM0ZMyVOqkUryRVv/U2+36z9OS1lKrxKBu645aOOmyrgMZO6rE4P1FfM+xranbx075FWhVmR8t8pimSJdH3BoEItXuNXQtTIjwOwRPnLc0r0nn4DjzKa3ruztHAQL0nG5eutiyoq7MT4yzlazvjoP92J0oK31Vmf3OtiZxfnnaZEAMjGfx2zM0urRuaWyt7y6/qLDOsCySnrd7Hfb2EB1etiVPDS3srC6LMCrrfg24o7YuhSXIpJekGZhJYyS6JskA/XTUz9LujmnjbLOqR99gqbb44X8W4/QgfmoL4+tGbGr6ucWQ50zVL0VvKh+5knMYSN23d5nP/5G7cNcnXotiQPHjk3a/0D1triLUF6Dm5qcdnFXY8wtqdeWNGY8Df9bzQs++xBFL6OyPvT0YUi74ffPqO/eoSRSo0uURIdw7/Jz8J2j0Tajzp4e6lzvBaAc9hnNpXFDW4Pjb4qPutl878/DqmLFmtNPTCiastPKtcW6sau3Lg3nJaABJk7Y4spwzHr43SE=
*/