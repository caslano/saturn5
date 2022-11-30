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

#include <cmath>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

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
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
*/