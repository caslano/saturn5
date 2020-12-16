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
mgiP3cKpELXukr30GB7dYSR+X7iIQfBpRNzDq+4P7Fv4yJbZD1zDwqLTK2LHk3sUNnxbvLBnf07dm27h8dvc8bt6gmcnfBzv6q2xLKTswI6QOcf+JuE56y4scwunz0cCZ3u9NuHDvIcXIKyyXl9HY/a7JZs2hsxz6vOlshbY9nm0Ryr93vE4uLxC3v89x3N/j6cVUcrseTya+eu7V30OmYOcr+17HFtxee8pnefZqLmuzfXutbNxBLYSd7VtrGnLXM70dT3eHk/m2evZHFvmwpt0eLbMpcyix/NlvulxfJl3HE6azHsOb5zM+w6XZM5+uM02AnGrb/x09O9ie+KPs4SnvFcZKZx8yyKPCzYG32IWeQ30WoyFbL/Eti08y/Z5fsu4/+5mRzDLL/BYYeFUNnC5x4RxrKvIc/nkd+uqP6lTMcHpqj/rLrO/XDDCRh04dEb83M4LLQzdJ/3wV+s5/vYf23ruQg9H1SJ9HrW356LgYL8b1yBh3nYy9F2/fphjrRcOwhwokP7OKHHm80cPnlyYvueCfWdTzsdRhjw/6eH23nx7tH8ve/eF2YPHpu225IIcuy3dIMduy5bHiYuRcbL/JBdHEUbwgfc8sgfO6xpPcfCRTUSJP2Nbq4/6eP4gB1pyhvAgY/Mz1KdsIzYGf5yT2M3GUDEjfvqQhaFSOfYnmfsyFvsD6Vf+3QrAIh6LH8B4md5bYFvva0zOQUfcRskbZgNdx7yQbbWQYLaede+d/G77WF57mhbcD7TUO4FHxvHgmHSMyXXRAZn048DGrXdis0Ubg9PkuhY15jtNiYdsHjlNicvaFk7P63ixnOASMHHeFRuDsKGjEtP1BPeDJu2vQrxY4dU+SN/lWAO45DXweTQwC8csexxSTeFkAhxkY30fPBvgoP+gE8LJBThUaVnX8jkjfUJOury8zxtZjfIfxRRObLEbSk6RzyMrk3n1psOBQ5A16RUba6b0bc7n7XH7tuNyUvq25/H8vu17HL9vzarH8fvW4/h9O+lx/L4tupyUvt30eH7fdlxOSt/2PJ70Lc/F2e7t+wm61u/sD6o87pxjnMIOuZNiy8H0tzwnFxPMCR6N6FtbcVxfOFCY6wvbS4KN84Udi+f7wq6Nk9oI3rNw8ZWJTIs8RtrvZfRkLJPuUs9lywpHcMm+WX6X4FL55g7j/j3SA64LdT0wlsNUgkngqdvZPm/j1NNrbGNBHL0NXeBY6onEOY57LvA9v6lCHWFKs1nT9/88kDm4posu10F8zOUITndNw9wRusN7yD35DxIODjyw7IoPTn7HvYL1xfNYtGkY2BLr8UMYJ7HKes4mY3b80H4o/w53KXVhu1N4rb6I3Wf+LIvESpsJB6C+1/9h/DvuUcE9OpAT26pgsEnR562H8+8RPgFHjVTfB3wE401dX9YRxkl/IB/5bu4OA2z68BSv8u2fwO+sQ8sJbq2OSex3fcKhJRKFyvORi0OiOYV3XRwtt87Q3sDBm/bz5sMKp+jS2u8N4PAIUr+PWLj3jdi2ep4y572XgYs5a3S5JG/HI3Bsy20jj6DvA1PPut8JHiTP5Q/OHYTV4bv4JHY1d7y+x7G+PZ+5oY9D9DKPYvyuXikcO10/xEEpRjj5YD4oSc8tPyKcJLwmZyPnfD+ZxoHCqzGxfQXiuSy1pxx9KoWDnIw+27WLeKO7lOkdW1kzYB+4JTy6T49IMg/PfkVzEMsEON3tO4XjFMe+4E6cz9zxE3laSZd35fK1AI7XTJtLuJsRL4tCEIZl5XLlVKnEAWsOZy0S31B3MBx/0u8QDU5buDWnmGzYGOlvg+POpo3TC6jLOO5Tb+j1vhCPZmsgyv3kIV69gXufZZ8=
*/