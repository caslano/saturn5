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

#ifndef BOOST_MATH_ELLINT_D_HPP
#define BOOST_MATH_ELLINT_D_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>
#include <boost/math/special_functions/round.hpp>

// Elliptic integrals (complete and incomplete) of the second kind
// Carlson, Numerische Mathematik, vol 33, 1 (1979)

namespace boost { namespace math { 
   
template <class T1, class T2, class Policy>
typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const Policy& pol);
   
namespace detail{

template <typename T, typename Policy>
T ellint_d_imp(T k, const Policy& pol);

// Elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_d_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    bool invert = false;
    if(phi < 0)
    {
       phi = fabs(phi);
       invert = true;
    }

    T result;

    if(phi >= tools::max_value<T>())
    {
       // Need to handle infinity as a special case:
       result = policies::raise_overflow_error<T>("boost::math::ellint_d<%1%>(%1%,%1%)", 0, pol);
    }
    else if(phi > 1 / tools::epsilon<T>())
    {
       // Phi is so large that phi%pi is necessarily zero (or garbage),
       // just return the second part of the duplication formula:
       result = 2 * phi * ellint_d_imp(k, pol) / constants::pi<T>();
    }
    else
    {
       // Carlson's algorithm works only for |phi| <= pi/2,
       // use the integrand's periodicity to normalize phi
       //
       T rphi = boost::math::tools::fmod_workaround(phi, T(constants::half_pi<T>()));
       T m = boost::math::round((phi - rphi) / constants::half_pi<T>());
       int s = 1;
       if(boost::math::tools::fmod_workaround(m, T(2)) > 0.5)
       {
          m += 1;
          s = -1;
          rphi = constants::half_pi<T>() - rphi;
       }
       BOOST_MATH_INSTRUMENT_VARIABLE(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(m);
       T sinp = sin(rphi);
       T cosp = cos(rphi);
       BOOST_MATH_INSTRUMENT_VARIABLE(sinp);
       BOOST_MATH_INSTRUMENT_VARIABLE(cosp);
       T c = 1 / (sinp * sinp);
       T cm1 = cosp * cosp / (sinp * sinp);  // c - 1
       T k2 = k * k;
       if(k2 * sinp * sinp > 1)
       {
          return policies::raise_domain_error<T>("boost::math::ellint_d<%1%>(%1%, %1%)", "The parameter k is out of range, got k = %1%", k, pol);
       }
       else if(rphi == 0)
       {
          result = 0;
       }
       else
       {
          // http://dlmf.nist.gov/19.25#E10
          result = s * ellint_rd_imp(cm1, T(c - k2), c, pol) / 3;
          BOOST_MATH_INSTRUMENT_VARIABLE(result);
       }
       if(m != 0)
          result += m * ellint_d_imp(k, pol);
    }
    return invert ? T(-result) : result;
}

// Complete elliptic integral (Legendre form) of the second kind
template <typename T, typename Policy>
T ellint_d_imp(T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;

    if (abs(k) >= 1)
    {
       return policies::raise_domain_error<T>("boost::math::ellint_d<%1%>(%1%)",
            "Got k = %1%, function requires |k| <= 1", k, pol);
    }
    if(fabs(k) <= tools::root_epsilon<T>())
       return constants::pi<T>() / 4;

    T x = 0;
    T t = k * k;
    T y = 1 - t;
    T z = 1;
    T value = ellint_rd_imp(x, y, z, pol) / 3;

    return value;
}

template <typename T, typename Policy>
inline typename tools::promote_args<T>::type ellint_d(T k, const Policy& pol, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_d_imp(static_cast<value_type>(k), pol), "boost::math::ellint_d<%1%>(%1%)");
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const boost::false_type&)
{
   return boost::math::ellint_d(k, phi, policies::policy<>());
}

} // detail

// Complete elliptic integral (Legendre form) of the second kind
template <typename T>
inline typename tools::promote_args<T>::type ellint_d(T k)
{
   return ellint_d(k, policies::policy<>());
}

// Elliptic integral (Legendre form) of the second kind
template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::ellint_d(k, phi, tag_type());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::ellint_d_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::ellint_2<%1%>(%1%,%1%)");
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* ellint_d.hpp
/mr+ysStRuM7uC18DuOPFxggPsZxxnr9xunqGvgsWx025jb2HHBy+BzF0WDnidvZNzvNC/xB2OqHlK8yjgusL7yAXaarg1exv438C/5NLDd+S4zD+/CU98a1zpX36G6mBF4i7D8avxZ0JGH/OSHfRtdtXVWt/NvzJj7nMPN9kH7SM+F74f/y4LV0FaGuCvvnqZPomJtewo9NoZOyjqYK79H8dvL7Hbfqv9yrn/Wc+5yv3k+hhzqULpC+obFC/al/WknnmyJ+52yGH76jP3CSfEe3trAFHmAHe8S5ofjIrlnqaXm8vZq91IgXtfRt7foQ1cn8VHyPOGW+mp0/j32WvEW3+kX8fs/9kvMzIRmPK/jNmFjH8AIePhwnnF+8y3s6TZ6O19fa+rzjzvAerLBOXr+rG+6bK09cAm/HfdIr5C28UAJeLfIei13VcE5nzCeKN3BGITuqmYo/1XeYah5K3uZHbfwbbzfsaDqhZ+Ed634b3uN/X/hdpMNIDd/XJxmiDlwRxb+w7XX/7Te6X+Mwtb/6ho6jJNU8Hpj8PFqfJkU93PoWPvdZ+qyb4bl6fh78KGzpSJqn8YM7xfc71APxOsLXxO2lYX/gdfjvKxl0Ruz1t+L1TLob8Xu4OidF/bZMPK5aGPlTGI+d8PAC8cT1FLzGDqzj30DXMxXOKTgjxodxH1/8vU79uDEa33D9m2P7h9cW4wMvUQ+H8Qj75fHuId6nSnc8bA4+YIB5Ew8K7sBb4m0qXzR/xmHNi3i8wGeHz/3UYyfiDYvoB26B6x5QR8/G498On9KHjvlcP/Al4x35YXo476/VYw8l9/fyx0+vgK/VIdXqz2Vz6Lz+K979j75jUdL/U/jRskPwPoEvCseDP3tcR+6t4r5+zIZj4Eh8bYU+0tp9cEKteu73nhOcwb4+UAd9npyvMvYxONZR8fcs+oFscai8zWd1cOGr7udJ+TSBb3pdnb+Xn8DrWfuScXT40Ay6Z/kC79cQr1N9VTyI+Ql2ufbngU+Izu/3Q/U5dsyG2+4yXvjmCjrvzib2dxd9jHq+vJw/zaBf/LXrhC/qo+d6HRZ+d5r9E6N6J4zrSPPwuDrWOOfMw2/16Ou7v+pe9ap1S0We41Pm+RKF4frDeaa6r53i7iP4jl+oR0/HP59ovPboK90tv6q/ei4I28B36C/FeG2BegS/V/oG/uhOdXg9P16JB2ZXw/8Ez/fFuk91inqi4nrxrhDeH4G3iuJUWtiPd6seoB9NNzi+AD8jrrdNjY4Xzn+lPNqfXx5lvcy74uy8NP1TfBb/bp7N/nPZV1TnHh9+Jy/Ui8fD8uGdHeZntf60Orb57+z2PXGxSx2kHlsmPjR+YHwmiEsDwjbEETrHV/nBDH2r30W/Dn3+kfDC+lTrCvlfnO/OMT/XiQvqtRz63GJxoG6eeRlMZ32uemoDe/hY3Eyz3uQiOqtL4PoD5NU4robjh+0L7HoL+7jB8bbD59a1dFyqbov8NhH8gd5gzSHqZPdTF+XR8P/R29Xpn/NPdtJqvV5KBvs4VD/tNt8fCg92JuvDUexyTBV+aRy/u4jd6lvUL8UrTlIX4v+XDXa84uR8ZIb5Cvvxv7Wz8Cr8fkocr8TvXTPE1efZgffYde/VZ/0NPXbQZYf9H8Al0Xwm74vO+1t5yrg2h3EN5/uOfP063I/XLntO3LHeqsB5moda33ALP7rMuog1eA321V3rvqzvbHG9C3fKF/vg66+Tdj5+JNwqz+3o5Tfr1YFfWdc/m71+zF5e4Kf/cv+HwlFb1Zn6fYlVeGO4tzWuM1Phpdvl0++Yh0/x2Q388/74fch4nzuM10l+f70+xat4KPF8DF5hQ5v6aqY=
*/