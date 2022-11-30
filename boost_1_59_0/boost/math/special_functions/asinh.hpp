//    boost asinh.hpp header file

//  (C) Copyright Eric Ford & Hubert Holin 2001.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ASINH_HPP
#define BOOST_ASINH_HPP

#ifdef _MSC_VER
#pragma once
#endif


#include <cmath>
#include <boost/math/tools/precision.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

// This is the inverse of the hyperbolic sine function.

namespace boost
{
    namespace math
    {
       namespace detail{
        template<typename T, class Policy>
        inline T    asinh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            
            if((boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  "boost::math::asinh<%1%>(%1%)",
                  "asinh requires a finite argument, but got x = %1%.", x, pol);
            }
            if        (x >= tools::forth_root_epsilon<T>())
            {
               if        (x > 1 / tools::root_epsilon<T>())
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/06/01/06/01/0001/
                    // approximation by laurent series in 1/x at 0+ order from -1 to 1
                    return constants::ln_two<T>() + log(x) + 1/ (4 * x * x);
                }
                else if(x < 0.5f)
                {
                   // As below, but rearranged to preserve digits:
                   return boost::math::log1p(x + boost::math::sqrt1pm1(x * x, pol), pol);
                }
                else
                {
                    // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/02/
                    return( log( x + sqrt(x*x+1) ) );
                }
            }
            else if    (x <= -tools::forth_root_epsilon<T>())
            {
                return(-asinh(-x, pol));
            }
            else
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcSinh/06/01/03/01/0001/
                // approximation by taylor series in x at 0 up to order 2
                T    result = x;
                
                if    (abs(x) >= tools::root_epsilon<T>())
                {
                    T    x3 = x*x*x;
                    
                    // approximation by taylor series in x at 0 up to order 4
                    result -= x3/static_cast<T>(6);
                }
                
                return(result);
            }
        }
       }

        template<typename T>
        inline typename tools::promote_args<T>::type asinh(T x)
        {
           return boost::math::asinh(x, policies::policy<>());
        }
        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type asinh(T x, const Policy&)
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
              detail::asinh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::asinh<%1%>(%1%)");
        }

    }
}

#endif /* BOOST_ASINH_HPP */


/* asinh.hpp
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
*/