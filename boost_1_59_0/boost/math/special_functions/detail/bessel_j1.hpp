//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_J1_HPP
#define BOOST_MATH_BESSEL_J1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/rational.hpp>
#include <boost/math/tools/big_constant.hpp>
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

// Bessel function of the first kind of order one
// x <= 8, minimax rational approximations on root-bracketing intervals
// x > 8, Hankel asymptotic expansion in Hart, Computer Approximations, 1968

namespace boost { namespace math{  namespace detail{

template <typename T>
T bessel_j1(T x);

template <class T>
struct bessel_j1_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static void do_init()
      {
         bessel_j1(T(1));
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T>
const typename bessel_j1_initializer<T>::init bessel_j1_initializer<T>::initializer;

template <typename T>
T bessel_j1(T x)
{
    bessel_j1_initializer<T>::force_instantiate();

    static const T P1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.4258509801366645672e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.6781041261492395835e+09)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.1548696764841276794e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.8062904098958257677e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.4615792982775076130e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0650724020080236441e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0767857011487300348e-02))
    };
    static const T Q1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1868604460820175290e+12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.2091902282580133541e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.0228375140097033958e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.9117614494174794095e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0742272239517380498e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0))
    };
    static const T P2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.7527881995806511112e+16)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.6608531731299018674e+15)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.6658018905416665164e+13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.5580665670910619166e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.8113931269860667829e+09)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.0793266148011179143e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -7.5023342220781607561e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.6179191852758252278e+00))
    };
    static const T Q2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7253905888447681194e+18)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7128800897135812012e+16)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.4899346165481429307e+13)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.7622777286244082666e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.4872502899596389593e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1267125065029138050e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.3886978985861357615e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T PC[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.4357578167941278571e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.9422465050776411957e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.6033732483649391093e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.5235293511811373833e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0982405543459346727e+05)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.6116166443246101165e+03)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0))
    };
    static const T QC[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.4357578167941278568e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -9.9341243899345856590e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.5853394797230870728e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.5118095066341608816e+06)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.0726385991103820119e+05)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.4550094401904961825e+03)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T PS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.3220913409857223519e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.5145160675335701966e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.6178836581270835179e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8494262873223866797e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7063754290207680021e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.5265133846636032186e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0))
    };
    static const T QS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.0871281941028743574e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8194580422439972989e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.4194606696037208929e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.0029443582266975117e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.7890229745772202641e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.6383677696049909675e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T x1  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.8317059702075123156e+00)),
                   x2  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.0155866698156187535e+00)),
                   x11 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.810e+02)),
                   x12 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.2527979248768438556e-04)),
                   x21 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.7960e+03)),
                   x22 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.8330184381246462950e-05));

    T value, factor, r, rc, rs, w;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    w = abs(x);
    if (x == 0)
    {
        return static_cast<T>(0);
    }
    if (w <= 4)                       // w in (0, 4]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P1) == sizeof(Q1));
        r = evaluate_rational(P1, Q1, y);
        factor = w * (w + x1) * ((w - x11/256) - x12);
        value = factor * r;
    }
    else if (w <= 8)                  // w in (4, 8]
    {
        T y = x * x;
        BOOST_MATH_ASSERT(sizeof(P2) == sizeof(Q2));
        r = evaluate_rational(P2, Q2, y);
        factor = w * (w + x2) * ((w - x21/256) - x22);
        value = factor * r;
    }
    else                                // w in (8, \infty)
    {
        T y = 8 / w;
        T y2 = y * y;
        BOOST_MATH_ASSERT(sizeof(PC) == sizeof(QC));
        BOOST_MATH_ASSERT(sizeof(PS) == sizeof(QS));
        rc = evaluate_rational(PC, QC, y2);
        rs = evaluate_rational(PS, QS, y2);
        factor = 1 / (sqrt(w) * constants::root_pi<T>());
        //
        // What follows is really just:
        //
        // T z = w - 0.75f * pi<T>();
        // value = factor * (rc * cos(z) - y * rs * sin(z));
        //
        // but using the sin/cos addition rules plus constants
        // for the values of sin/cos of 3PI/4 which then cancel
        // out with corresponding terms in "factor".
        //
        T sx = sin(x);
        T cx = cos(x);
        value = factor * (rc * (sx - cx) + y * rs * (sx + cx));
    }

    if (x < 0)
    {
        value *= -1;                 // odd function
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_J1_HPP


/* bessel_j1.hpp
+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
*/