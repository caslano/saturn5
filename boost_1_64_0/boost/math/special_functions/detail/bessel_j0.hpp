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
D2IxfZTx9wxcndHk+V/K3NF15pWl1bi1nC5P0s/zh3AaGzeHUPuFa17YGlt8vX1bWG0O2ThL3DwCF23Uj4Wn311p2Au1MlQcnOV/eST5Klt/1xumPr8Bt7I4eIxuB4unD/DhLFw7AgbybsGzxWiLOegSNvXDF37MWTMtpeH/F/cdPudcU5SHI1jX+lsP/QDfxEnSZW1lF3Z38qV5cXZPce+7QY0X8Uv+isR17lLxulns7YzXu+DMW3i2C389mbK/EkyvND8QI43nrUfxV+MouLkXa5iLVu7SN67W3xHr58L979q61X3HExkxnjFW8Mt0fe9k7Pop//Nz+UT1mvFlqpgfk+E36z4L5dYyLAc02/8LT43HjYF0ZFvZ/W30krnVMv28D5ta5HsUeHC6cQompfnG1cWRdRLjrLwQYFvFg1wn3so7DfdZyUGZ8MM5sPMcs+Z5bvwzti/A0eXyqjgLz+CfvRGq483jvp/y/WZzB74uprU7ut1aMxuMEfW6/6eJO/vP/so7EdVSq7078WlWT2t/rr+Pnu1yXx+fb4Pps3xwlphZJ2anmkuY52RxJS5oi56NiB6eEcXH8DNdG5e575KXQy9+MncNr5gbPEt/e43G98PtHO1mWt074My/6IFX0TviG8aVv/Pvk7BpN96w0/7D/J9y77f1nixiF/7dBEO5IEffwu3q9tfODm1h7tUdoSYvl2/ImGf4/2Z9mY+FcXAYRDdzwOiX2ki7N96F33qwe32TdVQYiemK76GWN8ujJXw7Xn8vwHkJP5b5bxidi7hUF+/WxsuL4Y6fFfOq8J74GiWWzqKruVTe8/r4PPVOZ9c/rM2K7YoxKDtM3VHWksRVcWdtm9uXvilWjsT/ffHwcp8P99mcrLBYO54TP2g9dol7sORr9LXWHqVxcKMxrmad6z64T6X/c5G4Eyt+17E6S1y6X0uOgKd1+Rx7C/Jstgkvt2Pv52DXJS4eZ88exqX5rnlJfL/GZ1/Hnxtw73K59YC0euYMm+C8f09co9u5/L+Zz4+XrzbD8Bwco3/lW+Qa18EoP0zO6QfjO/R7nLjYIraWy2GvBWO5vtkX9qL3l+C3gc6ZDJ3l/jt9zrLpveAZj5h5m87szVsnKqubL7FzsJw+Rr+3i98pMB/Ex5PlteVifYE2N1jXMk8ptIl1a3g34Xbh3sgaP/y94x+anbdeV9d+aZXx+wF+3IlP7MtZbqfL3XTdnc9OpQfeZu01kYzA71Hy0mTYmw/nSnD1f4Xe0Vdw8bZInnHdlmDfFnxfl7H+AU+xW1WvZI5csh7X7zI8vF1szFc3EltN2qynccs8oUU8wiu+QB4ghTJ+9FOP5AeRi9PwMz65pryBX8R+ZX+5HBdrE/Hlclz5snvst92bGLOTbrA/ypzocuObNbXiP1LWr+QLetRxoFzL4JZ+estzv+e3XfFYvGcn40CKP3rTyT1R7Wx8b8Ob81LmqO4fgzj5MX/cA7+PzN+689m3YO36bIrkxLR72QLuVSuu02fUiSvyWR7f/nAF7vZh+/fkvyfoYP2tqq1ohGvu02ZsLNxO/4fBvzfu8HnW3K8g5ovr6V6DdT9xIy8lPzGXIO7pvIskr4xPuQ809zHfK/ePcNq9Pt9n9VNyfxD/np5N9F/TzVin7qVbn+caQ9bhY5N2czA9XT/zcQ7Pq7hYLNFvibw9iC9/rM4X6Hc0ve7HuQE96WZcKYmNlfpwffyK+cdEuL8qrrQRK6M0nqyA9Xdw7RD9yRNhJZsHa9Nzkaw5S2MmHJ9Jy4V0+LU15rF086513f5epYPx6XnYDOebq3DhUv5/i85+57i+HM+Mt2X7x3TCIZLfahdZMzJXyF1Gx2c=
*/