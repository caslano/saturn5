///////////////////////////////////////////////////////////////////////////////
//  Copyright 2017 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_SCALED_SERIES_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_SCALED_SERIES_HPP

#include <boost/array.hpp>

  namespace boost{ namespace math{ namespace detail{

     template <class T, class Policy>
     T hypergeometric_1F1_scaled_series(const T& a, const T& b, T z, const Policy& pol, const char* function)
     {
        BOOST_MATH_STD_USING
        //
        // Result is returned scaled by e^-z.
        // Whenever the terms start becoming too large, we scale by some factor e^-n
        // and keep track of the integer scaling factor n.  At the end we can perform
        // an exact subtraction of n from z and scale the result:
        //
        T sum(0), term(1), upper_limit(sqrt(boost::math::tools::max_value<T>())), diff;
        unsigned n = 0;
        boost::intmax_t log_scaling_factor = 1 - itrunc(boost::math::tools::log_max_value<T>());
        T scaling_factor = exp(T(log_scaling_factor));
        boost::intmax_t current_scaling = 0;

        do
        {
           sum += term;
           if (sum >= upper_limit)
           {
              sum *= scaling_factor;
              term *= scaling_factor;
              current_scaling += log_scaling_factor;
           }
           term *= (((a + n) / ((b + n) * (n + 1))) * z);
           if (n > boost::math::policies::get_max_series_iterations<Policy>())
              return boost::math::policies::raise_evaluation_error(function, "Series did not converge, best value is %1%", sum, pol);
           ++n;
           diff = fabs(term / sum);
        } while (diff > boost::math::policies::get_epsilon<T, Policy>());

        z = -z - current_scaling;
        while (z < log_scaling_factor)
        {
           z -= log_scaling_factor;
           sum *= scaling_factor;
        }
        return sum * exp(z);
     }



  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_SCALED_SERIES_HPP

/* hypergeometric_1F1_scaled_series.hpp
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
*/