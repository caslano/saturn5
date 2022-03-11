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


#include <boost/config/no_tr1/cmath.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/constants/constants.hpp>

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