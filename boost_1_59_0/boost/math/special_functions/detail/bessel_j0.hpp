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
    
#ifdef BOOST_MATH_INSTRUMENT
    static bool b = false;
    if (!b)
    {
       std::cout << "bessel_j0 called with " << typeid(x).name() << std::endl;
       std::cout << "double      = " << typeid(double).name() << std::endl;
       std::cout << "long double = " << typeid(long double).name() << std::endl;
       b = true;
    }
#endif

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
        BOOST_MATH_ASSERT(sizeof(P1) == sizeof(Q1));
        r = evaluate_rational(P1, Q1, y);
        factor = (x + x1) * ((x - x11/256) - x12);
        value = factor * r;
    }
    else if (x <= 8.0)                  // x in (4, 8]
    {
        T y = 1 - (x * x)/64;
        BOOST_MATH_ASSERT(sizeof(P2) == sizeof(Q2));
        r = evaluate_rational(P2, Q2, y);
        factor = (x + x2) * ((x - x21/256) - x22);
        value = factor * r;
    }
    else                                // x in (8, \infty)
    {
        T y = 8 / x;
        T y2 = y * y;
        BOOST_MATH_ASSERT(sizeof(PC) == sizeof(QC));
        BOOST_MATH_ASSERT(sizeof(PS) == sizeof(QS));
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
        BOOST_MATH_INSTRUMENT_VARIABLE(rc);
        BOOST_MATH_INSTRUMENT_VARIABLE(rs);
        BOOST_MATH_INSTRUMENT_VARIABLE(factor);
        BOOST_MATH_INSTRUMENT_VARIABLE(sx);
        BOOST_MATH_INSTRUMENT_VARIABLE(cx);
        value = factor * (rc * (cx + sx) - y * rs * (sx - cx));
    }

    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_J0_HPP


/* bessel_j0.hpp
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
*/