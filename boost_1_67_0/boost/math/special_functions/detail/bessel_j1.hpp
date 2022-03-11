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
        BOOST_ASSERT(sizeof(P1) == sizeof(Q1));
        r = evaluate_rational(P1, Q1, y);
        factor = w * (w + x1) * ((w - x11/256) - x12);
        value = factor * r;
    }
    else if (w <= 8)                  // w in (4, 8]
    {
        T y = x * x;
        BOOST_ASSERT(sizeof(P2) == sizeof(Q2));
        r = evaluate_rational(P2, Q2, y);
        factor = w * (w + x2) * ((w - x21/256) - x22);
        value = factor * r;
    }
    else                                // w in (8, \infty)
    {
        T y = 8 / w;
        T y2 = y * y;
        BOOST_ASSERT(sizeof(PC) == sizeof(QC));
        BOOST_ASSERT(sizeof(PS) == sizeof(QS));
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
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
*/