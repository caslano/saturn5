//  Copyright (c) 2006 Xiaogang Zhang
//  Copyright (c) 2006 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  History:
//  XZ wrote the original of this file as part of the Google
//  Summer of Code 2006.  JM modified it to fit into the
//  Boost.Math conceptual framework better, and to ensure
//  that the code continues to work no matter how many digits
//  type T has.

#ifndef BOOST_MATH_ELLINT_1_HPP
#define BOOST_MATH_ELLINT_1_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the first kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math {

template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const Policy& pol);

namespace detail{

template <typename T, typename Policy>
T ellint_k_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the first kind
template <typename T, typename Policy>
T ellint_f_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    static const char* function = "boost::math::ellint_f<%1%>(%1%,%1%)";
    BOOST_MATH_INSTRUMENT_VARIABLE(phi);
    BOOST_MATH_INSTRUMENT_VARIABLE(k);
    BOOST_MATH_INSTRUMENT_VARIABLE(function);

    bool invert = false;
    if(phi < 0)
    {
       BOOST_MATH_INSTRUMENT_VARIABLE(phi);
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>(function, 0, pol);
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_k_imp(k, pol) / constants::pi<T>();
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
       //
       // Xiaogang's original code used a cast to long long here
       // but that fails if T has more digits than a long long,
       // so rewritten to use fmod instead:
       //
       BOOST_MATH_INSTRUMENT_CODE("pi/2 = " << constants::pi<T>() / 2);
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       BOOST_MATH_INSTRUMENT_VARIABLE(m);
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
          BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       }
       T sinp = sin(rphi);
       sinp *= sinp;
       if (sinp * k * k >= 1)
       {
          return policies::raise_domain_error<T>(function,
             "Got k^2 * sin^2(phi) = %1%, but the function requires this < 1", sinp * k * k, pol);
       }
       T cosp = cos(rphi);
       cosp *= cosp;
       BOOST_MATH_INSTRUMENT_VARIABLE(sinp);
       BOOST_MATH_INSTRUMENT_VARIABLE(cosp);
       if(sinp > tools::min_value<T>())
       {
          BOOST_ASSERT(rphi != 0); // precondition, can't be true if sin(rphi) != 0.
          //
          // Use http://dlmf.nist.gov/19.25#E5, note that
          // c-1 simplifies to cot^2(rphi) which avoid cancellation:
          //
          T c = 1 / sinp;
          result = static_cast<T>(s * ellint_rf_imp(T(cosp / sinp), T(c - k * k), c, pol));
       }
       else
          result = s * sin(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(result);
       if(m != 0)
       {
          result += m * ellint_k_imp(k, pol);
          BOOST_MATH_INSTRUMENT_VARIABLE(result);
       }
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the first kind
template <typename T, typename Policy>
T ellint_k_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    static const char* function = "boost::math::ellint_k<%1%>(%1%)";

    if (abs(k) > 1)
    {
       return policies::raise_domain_error<T>(function,
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if (abs(k) == 1)
    {
       return policies::raise_overflow_error<T>(function, 0, pol);
    }

    T x = 0;
    T y = 1 - k * k;
    T z = 1;
    T value = ellint_rf_imp(x, y, z, pol);

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_1(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_k_imp(static_cast<value_type>(k), pol), "boost::math::ellint_1<%1%>(%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const boost::false_type&)
{
   return boost::math::ellint_1(k, phi, policies::policy<>());
}

}

// Complete elliptic integral (Legendre form) of the first kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_1(T k)
{
   return ellint_1(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the first kind
template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_f_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_1(k, phi, tag_type());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_1_HPP


/* ellint_1.hpp
8yfi6kz16cXpdF7OPxFue1o/+255vT+ecbP7mW8dyj0xn4C/uNVzYUPeDNtN+ojq7KIrXG+5fKO+7fkiky4b/k51P+3qh2PpVB93H+JsDf6q9jL5OuCJ8PuIr0wPfhq/H0P90POh/mu8Dl19l1hiXEexJ/hw/Bz3cbX19nPp4M7R755Jn9eDL7+KnY5gZ3Ttc9dl0APgkeaJJ8avZoS+4WzXq4+/Ovh52JbSdxygTm8yHw3sfpvjXaIuiPiU1DDOb+oHxOvPr8NXxLopetnRi9SRX+ibrXd/lXiLFfK+9XJ7vknFT7GjLUn9d4f1GYm16rxFYRv4Xr//Vl07Q70bcE3Y/4C8Zf1+7tBoG8aL/nmY9T2ZR+hX3A7/lCXoVvWD38erLIWvV4gT7LHgg/7iCV5oTdiGviG+Ch/W+j9+fxb+H//QfJ7xfdd9vO566B3aBhm3EfL1A3iRd/GgY9WRpyZxVmXgp8J+OtHcJ9QN+MXCRvj03rAN/CWcP4PfHSKulLiP4/Ao9PMVi/Q1StWZCTyw61uwBH4vhg9PEr/h1Zot4nuuOjPYY/jdCP7xoX6HbfXX6lb3lWu+s68U/59gt2E9XNiaj8Y38HzD1WUT1DH6dcX387+3xf95eGLvSeg6T9zotp6QX+x+BZ/Lr1r68KP30dvIBwvMS1aka0qE7xvXZuO1+rZMPAF/fMx6KXiqHI/WkeJ+WszjwXBgPV7gauvr3sUfjFEXqzvr6M0SreLEJPGF37dUJOAy/dqXjMs0/OUP+PMHfreY/Vr3Wvghfe2DcNvH+L578e1f402etY6oRb6L9f17+fUb+hx1eLb4fX/msetL/rKcHexITY6XvnnH0/DgVnZz0H7J+ztcnv4+f76Mvtu8jlq/v7ozQz0o7k2H68qNW7n6r1Wf6n754W36vcnq3vB+/bClw00Yx8ZB5t95CyrEzb1wy9XymfjQsh6feDC/guc6bxf/r4YHdvEj8avmDv2tjdYTsNPmVfiULfD4F3jCfPbmuYZ559OPeT5VC1zcvgrOCnEpbPfiC6bTc5jHikg/t3+4jvj9aIfAd5uT81SFN586BY7T/8ubSM+fov4Yyf/y4HbrBhoHJs9fmGW8htFv7cIz/DMd3sL/HajPPyhsQ92qf/qRuAzn74Grso4XZz3/pIwdTmmXJ2fLXwfDVWHdfzj/JuNsXpexo92bjS87aor8KzVsjxPnfwnn/w5PrU+1ugvPU26cnoWrUlxfvL6iTR/COqiKE+Q7PP74d9S/UV/2qaD7/WusD5EHCvGmC/TH6fIS/1KfbjJevezN+5RWrFdnLjbeg/jbJnWieUqhTy83X2PW4S/cZ7d1KmtvgCeuF8fXq08+4TcRj9AY1rPx62FTHW+a+oRdZQe9StgvPqV0yYdfGr9aeQGu7MB/ttBhZh6Hd7uN/cg3bfeIw4/oO8BTlb8MfZ/ouHQPXdvwFvH7VQJeCfvL2OlAOiF8VPkpcMN2/U95uP1W9kJfs+uzBJ4O/mpWj5m/Jji3fusA+FqfpZKOqpP9e05x2T145lHiRA0+XF1YSlc/emsa3lF/dLk+xkT45zL97Bfk1SPVg/lw9QY8RYpxCeMdPl+BB/yZ+32FbmJkmv6P+60Td77hJwP1Q+jdRr0Ebwxm/4fgs+lk2/lZ5wvw6WZ55Qp53XqTHn5fu5z9PEtPepM64ljxs9w6hT/TZ+1UrxvPnDPxBerQXV367vPi9xaqs7e5nkHG1e9TFsI3vw77Q99VPyS6zuT38CZd4uQn/OlBOsPl8mWt/onra32fPvld/dk55vm4BJxIhzvX/QR/Dp/Va1UhL4T9F4Rt0L9Zbz9Z/UJn2blHff0wPfU=
*/