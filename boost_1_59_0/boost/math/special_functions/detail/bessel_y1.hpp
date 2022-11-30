//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_Y1_HPP
#define BOOST_MATH_BESSEL_Y1_HPP

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/detail/bessel_j1.hpp>
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

// Bessel function of the second kind of order one
// x <= 8, minimax rational approximations on root-bracketing intervals
// x > 8, Hankel asymptotic expansion in Hart, Computer Approximations, 1968

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_y1(T x, const Policy&);

template <class T, class Policy>
struct bessel_y1_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static void do_init()
      {
         bessel_y1(T(1), Policy());
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
const typename bessel_y1_initializer<T, Policy>::init bessel_y1_initializer<T, Policy>::initializer;

template <typename T, typename Policy>
T bessel_y1(T x, const Policy& pol)
{
    bessel_y1_initializer<T, Policy>::force_instantiate();

    static const T P1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0535726612579544093e+13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.4708611716525426053e+12)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.7595974497819597599e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.2144548214502560419e+09)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -5.9157479997408395984e+07)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2157953222280260820e+05)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.1714424660046133456e+02)),
    };
    static const T Q1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.0737873921079286084e+14)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1272286200406461981e+12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.7800352738690585613e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.2250435122182963220e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.8136470753052572164e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.2079908168393867438e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T P2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1514276357909013326e+19)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -5.6808094574724204577e+18)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.3638408497043134724e+16)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0686275289804744814e+15)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -5.9530713129741981618e+13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.7453673962438488783e+11)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.1957961912070617006e+09)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.9153806858264202986e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2337180442012953128e+03)),
    };
    static const T Q2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.3321844313316185697e+20)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.6968198822857178911e+18)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.0837179548112881950e+16)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1187010065856971027e+14)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.0221766852960403645e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.3550318087088919566e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0453748201934079734e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.2855164849321609336e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T PC[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.4357578167941278571e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.9422465050776411957e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.6033732483649391093e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.5235293511811373833e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0982405543459346727e+05)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.6116166443246101165e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0)),
    };
    static const T QC[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.4357578167941278568e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.9341243899345856590e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.5853394797230870728e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.5118095066341608816e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0726385991103820119e+05)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.4550094401904961825e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T PS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.3220913409857223519e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.5145160675335701966e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.6178836581270835179e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8494262873223866797e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7063754290207680021e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.5265133846636032186e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0)),
    };
    static const T QS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.0871281941028743574e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8194580422439972989e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.4194606696037208929e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0029443582266975117e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.7890229745772202641e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.6383677696049909675e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
    };
    static const T x1  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1971413260310170351e+00)),
                   x2  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.4296810407941351328e+00)),
                   x11 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.620e+02)),
                   x12 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8288260310170351490e-03)),
                   x21 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.3900e+03)),
                   x22 = static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.4592058648672279948e-06))
    ;
    T value, factor, r, rc, rs;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    if (x <= 0)
    {
       return policies::raise_domain_error<T>("boost::math::bessel_y1<%1%>(%1%,%1%)",
            "Got x == %1%, but x must be > 0, complex result not supported.", x, pol);
    }
    if (x <= 4)                       // x in (0, 4]
    {
        T y = x * x;
        T z = 2 * log(x/x1) * bessel_j1(x) / pi<T>();
        r = evaluate_rational(P1, Q1, y);
        factor = (x + x1) * ((x - x11/256) - x12) / x;
        value = z + factor * r;
    }
    else if (x <= 8)                  // x in (4, 8]
    {
        T y = x * x;
        T z = 2 * log(x/x2) * bessel_j1(x) / pi<T>();
        r = evaluate_rational(P2, Q2, y);
        factor = (x + x2) * ((x - x21/256) - x22) / x;
        value = z + factor * r;
    }
    else                                // x in (8, \infty)
    {
        T y = 8 / x;
        T y2 = y * y;
        rc = evaluate_rational(PC, QC, y2);
        rs = evaluate_rational(PS, QS, y2);
        factor = 1 / (sqrt(x) * root_pi<T>());
        //
        // This code is really just:
        //
        // T z = x - 0.75f * pi<T>();
        // value = factor * (rc * sin(z) + y * rs * cos(z));
        //
        // But using the sin/cos addition rules, plus constants for sin/cos of 3PI/4
        // which then cancel out with corresponding terms in "factor".
        //
        T sx = sin(x);
        T cx = cos(x);
        value = factor * (y * rs * (sx - cx) - rc * (sx + cx));
    }

    return value;
}

}}} // namespaces

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_BESSEL_Y1_HPP


/* bessel_y1.hpp
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
*/