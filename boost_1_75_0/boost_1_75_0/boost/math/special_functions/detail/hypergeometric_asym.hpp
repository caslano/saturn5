///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP
#define BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP

#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/hypergeometric_2F0.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif

  namespace boost { namespace math {

  namespace detail {

     //
     // Asymptotic series based on https://dlmf.nist.gov/13.7#E1
     //
     // Note that a and b must not be negative integers, in addition
     // we require z > 0 and so apply Kummer's relation for z < 0.
     //
     template <class T, class Policy>
     inline T hypergeometric_1F1_asym_large_z_series(T a, const T& b, T z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        static const char* function = "boost::math::hypergeometric_1F1_asym_large_z_series<%1%>(%1%, %1%, %1%)";
        T prefix;
        int e, s;
        if (z < 0)
        {
           a = b - a;
           z = -z;
           prefix = 1;
        }
        else
        {
           e = z > INT_MAX ? INT_MAX : itrunc(z, pol);
           log_scaling += e;
           prefix = exp(z - e);
        }
        if ((fabs(a) < 10) && (fabs(b) < 10))
        {
           prefix *= pow(z, a) * pow(z, -b) * boost::math::tgamma(b, pol) / boost::math::tgamma(a, pol);
        }
        else
        {
           T t = log(z) * (a - b);
           e = itrunc(t, pol);
           log_scaling += e;
           prefix *= exp(t - e);

           t = boost::math::lgamma(b, &s, pol);
           e = itrunc(t, pol);
           log_scaling += e;
           prefix *= s * exp(t - e);

           t = boost::math::lgamma(a, &s, pol);
           e = itrunc(t, pol);
           log_scaling -= e;
           prefix /= s * exp(t - e);
        }
        //
        // Checked 2F0:
        //
        unsigned k = 0;
        T a1_poch(1 - a);
        T a2_poch(b - a);
        T z_mult(1 / z);
        T sum = 0;
        T abs_sum = 0;
        T term = 1;
        T last_term = 0;
        do
        {
           sum += term;
           last_term = term;
           abs_sum += fabs(sum);
           term *= a1_poch * a2_poch * z_mult;
           term /= ++k;
           a1_poch += 1;
           a2_poch += 1;
           if (fabs(sum) * boost::math::policies::get_epsilon<T, Policy>() > fabs(term))
              break;
           if(fabs(sum) / abs_sum < boost::math::policies::get_epsilon<T, Policy>())
              return boost::math::policies::raise_evaluation_error<T>(function, "Large-z asymptotic approximation to 1F1 has destroyed all the digits in the result due to cancellation.  Current best guess is %1%", 
                 prefix * sum, Policy());
           if(k > boost::math::policies::get_max_series_iterations<Policy>())
              return boost::math::policies::raise_evaluation_error<T>(function, "1F1: Unable to locate solution in a reasonable time:"
                 " large-z asymptotic approximation.  Current best guess is %1%", prefix * sum, Policy());
           if((k > 10) && (fabs(term) > fabs(last_term)))
              return boost::math::policies::raise_evaluation_error<T>(function, "Large-z asymptotic approximation to 1F1 is divergent.  Current best guess is %1%", prefix * sum, Policy());
        } while (true);

        return prefix * sum;
     }


  // experimental range
  template <class T, class Policy>
  inline bool hypergeometric_1F1_asym_region(const T& a, const T& b, const T& z, const Policy&)
  {
    BOOST_MATH_STD_USING
    int half_digits = policies::digits<T, Policy>() / 2;
    bool in_region = false;

    if (fabs(a) < 0.001f)
       return false; // Haven't been able to make this work, why not?  TODO!

    //
    // We use the following heuristic, if after we have had half_digits terms
    // of the 2F0 series, we require terms to be decreasing in size by a factor
    // of at least 0.7.  Assuming the earlier terms were converging much faster
    // than this, then this should be enough to achieve convergence before the
    // series shoots off to infinity.
    //
    if (z > 0)
    {
       T one_minus_a = 1 - a;
       T b_minus_a = b - a;
       if (fabs((one_minus_a + half_digits) * (b_minus_a + half_digits) / (half_digits * z)) < 0.7)
       {
          in_region = true;
          //
          // double check that we are not divergent at the start if a,b < 0:
          //
          if ((one_minus_a < 0) || (b_minus_a < 0))
          {
             if (fabs(one_minus_a * b_minus_a / z) > 0.5)
                in_region = false;
          }
       }
    }
    else if (fabs((1 - (b - a) + half_digits) * (a + half_digits) / (half_digits * z)) < 0.7)
    {
       if ((floor(b - a) == (b - a)) && (b - a < 0))
          return false;  // Can't have a negative integer b-a.
       in_region = true;
       //
       // double check that we are not divergent at the start if a,b < 0:
       //
       T a1 = 1 - (b - a);
       if ((a1 < 0) || (a < 0))
       {
          if (fabs(a1 * a / z) > 0.5)
             in_region = false;
       }
    }
    //
    // Check for a and b negative integers as these aren't supported by the approximation:
    //
    if (in_region)
    {
       if ((a < 0) && (floor(a) == a))
          in_region = false;
       if ((b < 0) && (floor(b) == b))
          in_region = false;
       if (fabs(z) < 40)
          in_region = false;
    }
    return in_region;
  }

  } } } // namespaces

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_MATH_HYPERGEOMETRIC_ASYM_HPP

/* hypergeometric_asym.hpp
Tz5/X4rTydUxSMJj92rtWQ+vUWQm3yIrl6OrA0aWI59JkezIbV/9wM+bVDPbU1e3oKHCNYjvGbVdiV1qp2lo2/yyWBRCK2RktKb1edFAd0FNbVLbwJqd1ZaL1RYCOT084Zi0qyOLiCkqEkvWp6HBAJP1F7zxc3XVlzbz1hH47FOopM8Yr/Ucazdop7bgjSJ6lTRTzErL3Jzft1fPXc01vvCVvSDVwEKvNnu+3PvB273+4OJ37yMykZieLPT7x55usj/+CLnoeTsTPYctkzz12ZZP6+WrAr1P74zbvjJGj4wtHHMbtaWxkhoJBUjwyiaxJ+fEsSf/8Yd2H3PyO0VKXMjm0cOb5ykFHy48Fl0bnd2Ax39gSjkxUdfyRJJdMZXO5k25p6Qsj+5Fhb0r11AvUkv6pVPKoTnIuJ6WuqKl5eX0JXcxbt5QE+TxtaSjbfVNsr6bawWLZoNCNiOZDiVFymABRXiTUpZGChMbJe5Iwv3mxe7Qwx3ditGaGqZUXGY8U3qFsGgrl7g4r0g3U+Jn8lqN8KYhBydWNgd29uOKsqOK0sOaJZ/llZG6Wh8R0QkiQqM2r5ryPh1trSwuMu3UpDQggrZ5lSOVctCi78sVT6k2GyRO4VX3CnRm7lSGBLOZilWdzUCJ5cKDF4C2d8ov4ghVWVHXmf9zrUBlNZ1Qx9x8jKjHh2Y3WVvbL+ecQGBDSL9+JLP8z8GkCAPq
*/