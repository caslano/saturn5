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
XDhZJmVFi32sdFehsqC4ecEXAeE3E7SBOUWtWz/gPynuUNzTqI+z27GX4RYXe7cIe3wWWdfyZOIYyprRkr/XDsuWXk9yGMQV5e9G/ATkyigkamIOgD869MeCptZb4gjIpfUyvXVtRPNQXylqsI+VE4o4mlwG5YT+WeuYNxVw2RlsuFDuwNb7Vkb1bTxdh2etbFAx46dP3RmOVI6UsbM8d/YDKp3iQavutK0ebPnN7jqPb8xfD3VNuB9ag+aWE41rWC51XHQP0lA3YkhCvgduq4c61fXz3LCcar79/RBgedpmbZOjV4EvgnZsZAosx++uhFZX1aBLkBZzhwSJAXm/vGIUcxITl0oqkLj+to8+i8oZF5aeYPRG9DPectZOwle1AiF6o9w6tfJatpNMhq4UR4hcBpTA2n/ia+ODeZq8l6WYOY7JzBo2zC1D5KwHXlSE/g0xG/g4Iv0P2hX0dzhDiT7z1GQguDs2PD3qIEZRV6UQST9KOF9Y7g/tjq3xVKlKvQZOo4GiGgDCfvahvtH3j54zHDLh5CIeRjQ6NXHxtvJR6FDIcE+EGh24z6p1euocYMXTf0rjfzcn4cdJR99eJn8Z454k9vVrKKOl/d+f3sYjSLf83tHG1AZXPM4WaBa7xi1+8jEJskp8yN4eIgtKL2w0Te6Y+ixDJ1rh85px4Mbh8+ZT4JeLCuDYev2WKsJZ4kE7UVUmxvdBSHxe
*/