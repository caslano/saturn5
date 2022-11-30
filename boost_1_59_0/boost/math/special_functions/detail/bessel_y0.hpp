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
#include <boost/math/tools/assert.hpp>

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