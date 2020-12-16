//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JN_HPP
#define BOOST_MATH_BESSEL_JN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_j0.hpp>
#include <boost/math/special_functions/detail/bessel_j1.hpp>
#include <boost/math/special_functions/detail/bessel_jy.hpp>
#include <boost/math/special_functions/detail/bessel_jy_asym.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>

// Bessel function of the first kind of integer order
// J_n(z) is the minimal solution
// n < abs(z), forward recurrence stable and usable
// n >= abs(z), forward recurrence unstable, use Miller's algorithm

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_jn(int n, T x, const Policy& pol)
{
    T value(0), factor, current, prev, next;

    BOOST_MATH_STD_USING

    //
    // Reflection has to come first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // J_{-n}(z) = (-1)^n J_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < 0)
    {
        factor *= (n & 0x1) ? -1 : 1;  // J_{n}(-z) = (-1)^n J_n(z)
        x = -x;
    }
    //
    // Special cases:
    //
    if(asymptotic_bessel_large_x_limit(T(n), x))
       return factor * asymptotic_bessel_j_large_x_2<T>(T(n), x);
    if (n == 0)
    {
        return factor * bessel_j0(x);
    }
    if (n == 1)
    {
        return factor * bessel_j1(x);
    }

    if (x == 0)                             // n >= 2
    {
        return static_cast<T>(0);
    }

    BOOST_ASSERT(n > 1);
    T scale = 1;
    if (n < abs(x))                         // forward recurrence
    {
        prev = bessel_j0(x);
        current = bessel_j1(x);
        policies::check_series_iterations<T>("boost::math::bessel_j_n<%1%>(%1%,%1%)", n, pol);
        for (int k = 1; k < n; k++)
        {
            T fact = 2 * k / x;
            //
            // rescale if we would overflow or underflow:
            //
            if((fabs(fact) > 1) && ((tools::max_value<T>() - fabs(prev)) / fabs(fact) < fabs(current)))
            {
               scale /= current;
               prev /= current;
               current = 1;
            }
            value = fact * current - prev;
            prev = current;
            current = value;
        }
    }
    else if((x < 1) || (n > x * x / 4) || (x < 5))
    {
       return factor * bessel_j_small_z_series(T(n), x, pol);
    }
    else                                    // backward recurrence
    {
        T fn; int s;                        // fn = J_(n+1) / J_n
        // |x| <= n, fast convergence for continued fraction CF1
        boost::math::detail::CF1_jy(static_cast<T>(n), x, &fn, &s, pol);
        prev = fn;
        current = 1;
        // Check recursion won't go on too far:
        policies::check_series_iterations<T>("boost::math::bessel_j_n<%1%>(%1%,%1%)", n, pol);
        for (int k = n; k > 0; k--)
        {
            T fact = 2 * k / x;
            if((fabs(fact) > 1) && ((tools::max_value<T>() - fabs(prev)) / fabs(fact) < fabs(current)))
            {
               prev /= current;
               scale /= current;
               current = 1;
            }
            next = fact * current - prev;
            prev = current;
            current = next;
        }
        value = bessel_j0(x) / current;       // normalization
        scale = 1 / scale;
    }
    value *= factor;

    if(tools::max_value<T>() * scale < fabs(value))
       return policies::raise_overflow_error<T>("boost::math::bessel_jn<%1%>(%1%,%1%)", 0, pol);

    return value / scale;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_JN_HPP


/* bessel_jn.hpp
C54n1jN45d6xOkCMbC9un8bZr7oXGCFudtCX7yjX3pKb3xMDxsBau7Yn8bl7jqQCv2l84767drIcv8TzEv2XLoOL5yU5HKzDtZSBOTziM3uHcWIu8H3dWPbkFbj5keN/4Kcp7PadlcZr2rfPScV9XjD/S+ha1V+YiztyUvxV9pbF3XUw/C6eaiPLt7lJsPwhu27j/9liZDd4jZevjsHN842tA+n1L/UWy18wLA3mv1nmRj+Qi8R01hhV8gyyYm29TPdqN5/rKe30sO6TCk9ejbNxxvet2D3IOwLf4N8mcSxGG3vj94Ns/p0xzbnCIWLDPDzpo91n8RtP62NheRMbzTlKL4q3v8GwpdkzbrEIr0J35xdE1vPliJ/DwLOfam8+3DkjLxi/6JJdzN7hctXh7PBcOl5r/oer+cvYfhacl2jr93Ca2Rqmifv8K+LgurT1Flxbru89cQOWxdBkPxD9bAih6nzlPm39kO5vw2sVv/s+gE2TxS873LfG8EjO9j/ON/5Bl77ufTfLVUX27cVPSeR5h9h3rPaRe5b/jNvwWMx3h+BlE+7tKh7/JuZXGF++oc+D6Lwf/o1utj8/LDojew2xYX4kFvT3cBBH/PYOfvn+QTJN7m3hy7E9xY8x7x51j4XrCscm6Vfea+Br8TewG+Aa/xdWif2v0R/XG9YXoz/wK7/n1ohvXMleJ1/gV5XelTbzlwO0yT/h096+K8QGcdHoo43jtbVa+yNwy9po+Ca+bodf5lWx9gLditr5Pl5WrG829qQ/iUaaHyjzL8PL+FCaxe4p+tlF3Fxk3nUNn8srdfm+6Jll6SRrP1PE2jptWxOe8XM+fAEevteVpVt9NP2vZN8yWL0ix8OhfC0ff59+3o+MxU9U7s02eLTzT9kzu7xjfXDE899kGO5cIx/BozyvBdflxK52scxmuNV3hs2++nvU/LWId2n8Vrcy0XrY/eLNmm1lH2IsiVrFh/WSnDZrPdj/KJ57ZlcToyX3N/fiX8HYGRujG+a95TXynnfZsym8myJevIu1kX31XrAqyj/mXfXVOCSvB9hn4bryBjE3kk+q+D4tZX5Hn8n0eVo+GYFXYjQp8N+B7JrHT53GOffN9ZQY/VGTvEp+JN/UcO5Cdv3Eus1mfBvr/K70/CvMvLeaHSpG3uXT2bA1prrnDLVgzjQtbQ/brT5t9gw5JXbh4NrsM2JTzsmac1a/B3vzjeJz7BsG8+/yu/E/+rJ56sE4Jt5y3fFxbXf34DC+VexpuzYfvi3ammVs7RIb9G7oO/tDcbqGP5bj/mH4zeby43L1Nfo5l07+L10Io0Qs7uZa67fJYhhbD6m6r6injQXmcZHnG4k28rfDybu8lV54Zm3Hhnfem86Yp8hDsCx24rr2amKzMkJ8XgijieLlInpO0T7dy+KwG39GZT6+FEYD9bkRhuP43vtaezhX63D8Lnwej28trvkFzhl36q/g+1f56Pf6We76pXh8Ij++LE7cr+U3iSv3XDm6lc0Jw6F82Kkt90Nhurn9bJjtg493sfGn2jwSNuZ+lbu1+zfrwB+Kl8XOu9+LPvB/LO/Odc/1pPvaJ/ncPLqoj1o3fY+hw2lsc1399J78Codf4b86kXXJ6g1ww5cK3+X4puZYeQOur8HztyLvgtPXvUauv3nRzLQ94vjmbbbSoSyHhxsiaxf6x+nSfepO4KNJMBaHxcONO2Iqj+fZQezTZ8ym8hmOi4eyNcFGf7YdAtN8izbFyWRYvcSGS7T7As7NF7u/lad7a/Nx5ThcGC2/0LOgn5pnMjU5r8w/9WfVxd/qG643zyrKP9VF/NZs7Hs07bmDOpfAvUX95fLmaD4p6W+COFtvLDc=
*/