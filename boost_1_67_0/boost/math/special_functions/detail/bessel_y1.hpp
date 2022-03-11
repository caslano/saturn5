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