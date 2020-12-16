//    boost asinh.hpp header file

//  (C) Copyright Eric Ford 2001 & Hubert Holin.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ACOSH_HPP
#define BOOST_ACOSH_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>

// This is the inverse of the hyperbolic cosine function.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        template<typename T, typename Policy>
        inline T    acosh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            
            if((x < 1) || (boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  "boost::math::acosh<%1%>(%1%)",
                  "acosh requires x >= 1, but got x = %1%.", x, pol);
            }
            else if    ((x - 1) >= tools::root_epsilon<T>())
            {
                if    (x > 1 / tools::root_epsilon<T>())
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcCosh/06/01/06/01/0001/
                    // approximation by laurent series in 1/x at 0+ order from -1 to 0
                    return log(x) + constants::ln_two<T>();
                }
                else if(x < 1.5f)
                {
                   // This is just a rearrangement of the standard form below
                   // devised to minimise loss of precision when x ~ 1:
                   T y = x - 1;
                   return boost::math::log1p(y + sqrt(y * y + 2 * y), pol);
                }
                else
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcCosh/02/
                    return( log( x + sqrt(x * x - 1) ) );
                }
            }
            else
            {
                // see http://functions.wolfram.com/ElementaryFunctions/ArcCosh/06/01/04/01/0001/
                T y = x - 1;
                
                // approximation by taylor series in y at 0 up to order 2
                T result = sqrt(2 * y) * (1 - y /12 + 3 * y * y / 160);
                return result;
            }
        }
       }

        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type acosh(T x, const Policy&)
        {
            typedef typename tools::promote_args<T>::type result_type;
            typedef typename policies::evaluation<result_type, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
           return policies::checked_narrowing_cast<result_type, forwarding_policy>(
              detail::acosh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::acosh<%1%>(%1%)");
        }
        template<typename T>
        inline typename tools::promote_args<T>::type acosh(T x)
        {
           return boost::math::acosh(x, policies::policy<>());
        }

    }
}

#endif /* BOOST_ACOSH_HPP */



/* acosh.hpp
rscMY7F1CcTmoG4y9gvkIXuMS1CjbaxBCD6m8LVkOeqh5/+Q2wBmP2NsiNla5CbncjcYc8vvd2/F2I7MdkLTP/lashf5jmZ2CLF05N44Bv1WcQ+dhi4teexfGCv7nZfhdzDncQN2wu6ilks55jhya86aPsZ88j7gBfLoz/O9RY22cXxJqhqTa2xKY8GmzNIZ8xfifN815pHz91mN+eQ+J6cxV4z1y2ss0pxZQWOBMRxfMdjJ3kMpY2HRqrwx5235/hd2AWYeY9Ed7KMW8v2EWX3E7MlArIkx94fMmiPfwqx9a2Nx2ffpgLESXxdj3qvpiPU0FnvFuvTDfDXZxyDokpVrNByxJGU2Bhps59wmQIPcfM3+FPUtL+f/ELO8JwlCq+J8LVmA+U5xfF9CvwucxzL0mpyJ+Q5jE7iWP6KWsp+4Brqk5Fh+MxYKsd/16Mnu7HcL5rvPOu+A32Zstwc+VrHdQeQr/XcUWsk5slPQ/g3X9zz0k2eSGHzI363rmO8V53sHvSHX0/uIpT3X7V9j7WUP5Tl0lnu9N/ArZz8Sf+hwHB7NY1MYC1zn+qY1FlzDsWQw5uzMMWcxFt3OueUwFj8q+38Y24d78n1j4T0cc1FjDvn+w20spL//YSwi/fIBxs5g9hHGyh53TeSWm+erZ0y/UWyMmCfztfhjY54aPF8rMNG0PeaTe6nOxtyy39nDWEzOqPeF3VzOY6Ax75hkxIYh30ys82iw5nL+D/WozetoCuLrzXl8Dq1krc425pez2PMR3wpeg4uhlZt9fI2xcmbxf+i1EXL+D7l9nEBsNeKTPbJfwS7K+T/4KMpjN6OvBvPY7fAra3U3ekjObh3AfFHZ//tPZ14fJ2HXnu3OYW2N5z64BB8B1uUa9JN3CbehfS728Q96oyCzR6il7Hc+g53sGb2GXR7u3UQfWcw/cW8kN+b7nu3SGPNKLOnByrB+mY0F5DvN7MZCb1hTlzHXTvn9X8wnz1FFjMUaslYljQWny/e/xqJyhrQSctvPfj805r7BY2vAh5z3ros82jBrZCws1/tmiPkha98S8S3i3NrB72DWpZMxz+ds192YsyLP18dY5GUKYn7Ekop1GQoNBnK+o2AnvTse2q/guk1GLGXl+1+wShzLLOSRi/tqHvI9wX4XGYvLs9VXmG+4fP8L7TvI+T/UbRVrvwp5rGS7X9BXQ2T/z9gw2dfbBL+HOZYI4pvMbBe0f8jx7Yemsh9xBCy7nP9DfPK35yzWUZznuwitUnHMVxHfRQexW6i5xPc3fCxn7R9ivras1VP0pHxv+gr57uX5EjxWywmcRzJjjms8X2pjrhc81mksUIDHZjIWlOvpe8ZCXZjlxthOcv7Pgz1V7qHCxsIpEoiVMOa5Jft/xmKy71MRMedknasityCvt+oY24tzq2PMJz4aGote51iagiWV/T/kdpa1b4v5VjDzGYuU4Zi7Yexjvob1Ro3eYZ0HYOwNzm0ItJez0yOhaUHObRw0LSm//wsNCrP208Bqyv//h7Ffcd3mwk7ONi6E3RK2W2rML3uH3yCPVWz3PfrlF14LPxnzSv+FYafn/4w5h7LOG2HXnWu5DX0g7wP+RL80ZLt90H4W1+MwarSMYz6O3OrJ/h90kXpcgI+O7OMKekjea9xE3eR56x566Fs5/4d85TuHJ2Ay9iX028s+HNUslrzcV0mNBeXZNJWxeBHO9x1jzjXMMhqL5GeWzZj7oOz/GfPLvW0+xDKZWSFjgZLMisOHrMvSxsJv2W8FxFeUWRX4lfuDasYc97kPahuLyb53A8Qiz91e6CLvET9BHg2YtTHmle+8OmJseY6vK+yGs1a9EF8J2f9Dbok5vsE=
*/