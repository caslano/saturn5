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
MdnljCmUW9egx2tRpM73i1e6BNN57PBePvITvbwaUAsqZd0zcPKNX68UBY5TJb03D4PJUTsauFZw/7UghmvyvfiYdjbSwq0KCLffAZ2+eve75gU/RuP+gF5/2VFq+5ppHEslnXTLXxyNvpZ3AORBazpMgzBxCO7cFvU4zRsmbrUsisNtbNErhzCJFWpjA3MkbIXcwg7vb6tjB8cf7d0o43gNrjpdCVePyYsBcFg7qu/hdgVYcDzATFamefsD3MY7s5Gqo8rky21TOiUYzGXxtDYU2oPmFPm1yObaJZy4ljashGUYhPJWjzBoOS3SeW++DOGa8FD3aDgD/RDC+zasZ848S8Os9DZ6/fFsBZ+IdVrk4z6l4qTW4zPcz+XywDV8fgjRXmkiSz2ltdMVLpdj/JrcbZ7yvKLSdpGoyNdZ6k9IewWGZrJyDDtzSuNAxbTSyDu2ClfCOSGtKbmMXD7HCWldU0TPpq8pYXwuZ8tTu1CJuT+1YGF4quG+cZ5bjFP3hy5o+fGUROP2/Woa6O1S/amcB9OxIDQ3FGKgEMo4WQjUcojjnU5Ac6ZGo74b05x+98vn9KCM3IJOMnoPhZ42UvZDKOvEQwqGEUy/p0rnbmH5XGC60SUkYyaGu4P3FT6gYLi527T2UtPQm5vnmufZGLXPz5++OtF9sIJWVo9pNtT6769K9FYru5Zau9NWp4et1lqwArPCSuhFqvyd1nHQKzGMJ5kexzW/gssirlf04fyxKO5ay6sGDttezqsJp9p9vG4tpreAVKX99GsRBmoNy7nedIrGDmHOFWAqne3+4GLGXCjAoHHFtuC1bUyGUNburA9EG0LbaHqjRWcLvkh6PQ5WW2UvDWQj0oStzBNL0SUtbCtteGXHuT/ZmMWY0AEMyRDr/+ztnJWg4ii6LP37lZAOpkorzSYT8ZyvksZYx2QTic/ycaqAnr1qy2mcMTErESSh2PMGPYmhpPdn+gWDDkQxw/K4/odFX4NZnPWbRW+lJdD7LbU9CzC+t+o5alsUYKAiHrVFAR1m5sBR8jljYPC8vqwPya+BgVF5BHovSsrKnR8mBgYmtPpKoK5l/mlgQDqjQHYw27w85pLVWrAiB6TDevvMN0hu01KwLGPqBJ32ss+p9IxM/aryNvwKchPv2Q9dmeiNcuuuy46zQvrNpIF0VltOQPPih0160yu3ZY+xPrEwLa8SQDrqPWb/MjCZIvZo7rTooISBTrHll7iKSr+HOqc5l9RpoBmqqlwumnTQAyvH0lUgse/Mxkh7D9Qs4NhuXLdxR0BihAG+Svs9Jga1vhf7qPlZB502sWBPhWlbG3dnDYwUwsDntVshfSVLxGHb0rlUAY4qwLZZCnOiisM5M6b9epO+OeY56glaPx7Sp3cuS/pEG8dTPOPWf3gJDScWaEfErCdrx+uDU1ymApzM+wT5P/fHQv4cB3XBxEJK6rhcfL5BV9viK1cnGs3T7RQkIPHV+EuX5g+8ClBWjcfgukm//5oXZRif7qj4ImNWkqPH0BIBEF/FrPozUgOPKfP7qmRbkWEVES/XWTWq2A626Jtjzeb6EPdp0d7QGeY3xIfb5DxjDNFhnXr2w5wP7x+xrZt+hsbDirF+CMh38oIFC8PF4TXRkoWz1w9jLT8uEpWH02C6YRePCzCYDdvXWj7txAvSLEi7pbSxjklbLYJweT+o5kVy0KR8lLLMW8+ctTD2embxPpfNMS24bzMCu45o6/+6OtGOggWm8u0ZNLARWGeyPb3aEnsEayseiDe/Ia3Rm61qO2zKvR/1bsc/zMFkdYxpnM/FQT0BR3XRcGA9QVvSmDFpmAfZBxZdT/u8QW+lyvz4R5MmEue0l2w=
*/