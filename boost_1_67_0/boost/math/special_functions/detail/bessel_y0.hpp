//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_Y0_HPP
#define BOOST_MATH_BESSEL_Y0_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/detail/bessel_j0.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/assert.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

// Bessel function of the second kind of order zero
// x <= 8, minimax rational approximations on root-bracketing intervals
// x > 8, Hankel asymptotic expansion in Hart, Computer Approximations, 1968

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_y0(T x, const Policy&);

template <class T, class Policy>
struct bessel_y0_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static void do_init()
      {
         bessel_y0(T(1), Policy());
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T, class Policy>
const typename bessel_y0_initializer<T, Policy>::init bessel_y0_initializer<T, Policy>::initializer;

template <typename T, typename Policy>
T bessel_y0(T x, const Policy& pol)
{
    bessel_y0_initializer<T, Policy>::force_instantiate();

    static const T P1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0723538782003176831e+11)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.3716255451260504098e+09)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.0422274357376619816e+08)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.1287548474401797963e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0102532948020907590e+04)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.8402381979244993524e+01)),
    };
    static const T Q1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.8873865738997033405e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.1617187777290363573e+09)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.5662956624278251596e+07)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.3889393209447253406e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.6475986689240190091e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T P2[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.2213976967566192242e+13)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -5.5107435206722644429e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.3600098638603061642e+10)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.9590439394619619534e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.6905288611678631510e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.4566865832663635920e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7427031242901594547e+01)),
    };
    static const T Q2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.3386146580707264428e+14)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.4266824419412347550e+12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.4015103849971240096e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.3960202770986831075e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0669982352539552018e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.3030857612070288823e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T P3[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.0728726905150210443e+15)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.7016641869173237784e+14)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2829912364088687306e+11)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.9363051266772083678e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1958827170518100757e+09)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0085539923498211426e+07)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1363534169313901632e+04)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.7439661319197499338e+01)),
    };
    static const T Q3[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.4563724628846457519e+17)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.9272425569640309819e+15)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2598377924042897629e+13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.6926121104209825246e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.4727219475672302327e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.3924739209768057030e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.7903362168128450017e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T PC[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2779090197304684302e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1345386639580765797e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1170523380864944322e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.4806486443249270347e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.5376201909008354296e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.8961548424210455236e-01)),
    };
    static const T QC[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2779090197304684318e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1370412495510416640e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1215350561880115730e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.5028735138235608207e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.5711159858080893649e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T PS[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.9226600200800094098e+01)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.8591953644342993800e+02)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.1183429920482737611e+02)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.2300261666214198472e+01)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2441026745835638459e+00)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.8033303048680751817e-03)),
    };
    static const T QS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.7105024128512061905e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1951131543434613647e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.2642780169211018836e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.4887231232283756582e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.0593769594993125859e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T x1  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.9357696627916752158e-01)),
                   x2  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.9576784193148578684e+00)),
                   x3  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.0860510603017726976e+00)),
                   x11 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.280e+02)),
                   x12 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.9519662791675215849e-03)),
                   x21 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0130e+03)),
                   x22 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.4716931485786837568e-04)),
                   x31 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8140e+03)),
                   x32 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1356030177269762362e-04))
    ;
    T value, factor, r, rc, rs;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    static const char* function = "boost::math::bessel_y0<%1%>(%1%,%1%)";

    if (x < 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1% but x must be non-negative, complex result not supported.", x, pol);
    }
    if (x == 0)
    {
       return -policies::raise_overflow_error<T>(function, 0, pol);
    }
    if (x <= 3)                       // x in (0, 3]
    {
        T y = x * x;
        T z = 2 * log(x/x1) * bessel_j0(x) / pi<T>();
        r = evaluate_rational(P1, Q1, y);
        factor = (x + x1) * ((x - x11/256) - x12);
        value = z + factor * r;
    }
    else if (x <= 5.5f)                  // x in (3, 5.5]
    {
        T y = x * x;
        T z = 2 * log(x/x2) * bessel_j0(x) / pi<T>();
        r = evaluate_rational(P2, Q2, y);
        factor = (x + x2) * ((x - x21/256) - x22);
        value = z + factor * r;
    }
    else if (x <= 8)                  // x in (5.5, 8]
    {
        T y = x * x;
        T z = 2 * log(x/x3) * bessel_j0(x) / pi<T>();
        r = evaluate_rational(P3, Q3, y);
        factor = (x + x3) * ((x - x31/256) - x32);
        value = z + factor * r;
    }
    else                                // x in (8, \infty)
    {
        T y = 8 / x;
        T y2 = y * y;
        rc = evaluate_rational(PC, QC, y2);
        rs = evaluate_rational(PS, QS, y2);
        factor = constants::one_div_root_pi<T>() / sqrt(x);
        //
        // The following code is really just:
        //
        // T z = x - 0.25f * pi<T>();
        // value = factor * (rc * sin(z) + y * rs * cos(z));
        //
        // But using the sin/cos addition formulae and constant values for
        // sin/cos of PI/4 which then cancel part of the "factor" term as they're all
        // 1 / sqrt(2):
        //
        T sx = sin(x);
        T cx = cos(x);
        value = factor * (rc * (sx - cx) + y * rs * (cx + sx));
    }

    return value;
}

}}} // namespaces

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_BESSEL_Y0_HPP


/* bessel_y0.hpp
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
*/