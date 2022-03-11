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
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
*/