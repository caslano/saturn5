//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_J0_HPP
#define BOOST_MATH_BESSEL_J0_HPP

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

// Bessel function of the first kind of order zero
// x <= 8, minimax rational approximations on root-bracketing intervals
// x > 8, Hankel asymptotic expansion in Hart, Computer Approximations, 1968

namespace boost { namespace math { namespace detail{

template <typename T>
T bessel_j0(T x);

template <class T>
struct bessel_j0_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static void do_init()
      {
         bessel_j0(T(1));
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
const typename bessel_j0_initializer<T>::init bessel_j0_initializer<T>::initializer;

template <typename T>
T bessel_j0(T x)
{
    bessel_j0_initializer<T>::force_instantiate();
    
    static const T P1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -4.1298668500990866786e+11)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.7282507878605942706e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -6.2140700423540120665e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.6302997904833794242e+06)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.6629814655107086448e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0344222815443188943e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2117036164593528341e-01))
    };
    static const T Q1[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.3883787996332290397e+12)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.6328198300859648632e+10)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.3985097372263433271e+08)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.5612696224219938200e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.3614022392337710626e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 0.0))
    };
    static const T P2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.8319397969392084011e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2254078161378989535e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -7.2879702464464618998e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0341910641583726701e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1725046279757103576e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.4176707025325087628e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.4321196680624245801e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.8591703355916499363e+01))
    };
    static const T Q2[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -3.5783478026152301072e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.4599102262586308984e+05)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.4055062591169562211e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.8680990008359188352e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.9458766545509337327e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.3307310774649071172e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.5258076240801555057e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T PC[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2779090197304684302e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1345386639580765797e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1170523380864944322e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.4806486443249270347e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.5376201909008354296e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 8.8961548424210455236e-01))
    };
    static const T QC[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.2779090197304684318e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 4.1370412495510416640e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.1215350561880115730e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 3.5028735138235608207e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.5711159858080893649e+02)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T PS[] = {
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.9226600200800094098e+01)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.8591953644342993800e+02)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.1183429920482737611e+02)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -2.2300261666214198472e+01)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.2441026745835638459e+00)),
        static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -8.8033303048680751817e-03))
    };
    static const T QS[] = {
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.7105024128512061905e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.1951131543434613647e+04)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 7.2642780169211018836e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.4887231232283756582e+03)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 9.0593769594993125859e+01)),
         static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.0))
    };
    static const T x1  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 2.4048255576957727686e+00)),
                   x2  =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.5200781102863106496e+00)),
                   x11 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 6.160e+02)),
                   x12 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, -1.42444230422723137837e-03)),
                   x21 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 1.4130e+03)),
                   x22 =  static_cast<T>(BOOST_MATH_BIG_CONSTANT(T, 64, 5.46860286310649596604e-04));

    T value, factor, r, rc, rs;

    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    if (x < 0)
    {
        x = -x;                         // even function
    }
    if (x == 0)
    {
        return static_cast<T>(1);
    }
    if (x <= 4)                       // x in (0, 4]
    {
        T y = x * x;
        BOOST_ASSERT(sizeof(P1) == sizeof(Q1));
        r = evaluate_rational(P1, Q1, y);
        factor = (x + x1) * ((x - x11/256) - x12);
        value = factor * r;
    }
    else if (x <= 8.0)                  // x in (4, 8]
    {
        T y = 1 - (x * x)/64;
        BOOST_ASSERT(sizeof(P2) == sizeof(Q2));
        r = evaluate_rational(P2, Q2, y);
        factor = (x + x2) * ((x - x21/256) - x22);
        value = factor * r;
    }
    else                                // x in (8, \infty)
    {
        T y = 8 / x;
        T y2 = y * y;
        BOOST_ASSERT(sizeof(PC) == sizeof(QC));
        BOOST_ASSERT(sizeof(PS) == sizeof(QS));
        rc = evaluate_rational(PC, QC, y2);
        rs = evaluate_rational(PS, QS, y2);
        factor = constants::one_div_root_pi<T>() / sqrt(x);
        //
        // What follows is really just:
        //
        // T z = x - pi/4;
        // value = factor * (rc * cos(z) - y * rs * sin(z));
        //
        // But using the addition formulae for sin and cos, plus
        // the special values for sin/cos of pi/4.
        //
        T sx = sin(x);
        T cx = cos(x);
        value = factor * (rc * (cx + sx) - y * rs * (sx - cx));
    }

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_J0_HPP


/* bessel_j0.hpp
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
*/