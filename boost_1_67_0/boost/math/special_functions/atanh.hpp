//    boost atanh.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  (C) Copyright John Maddock 2008.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_ATANH_HPP
#define BOOST_ATANH_HPP

#ifdef _MSC_VER
#pragma once
#endif


#include <boost/config/no_tr1/cmath.hpp>
#include <boost/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>

// This is the inverse of the hyperbolic tangent function.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        // This is the main fare
        
        template<typename T, typename Policy>
        inline T    atanh_imp(const T x, const Policy& pol)
        {
            BOOST_MATH_STD_USING
            static const char* function = "boost::math::atanh<%1%>(%1%)";
            
            if(x < -1)
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires x >= -1, but got x = %1%.", x, pol);
            }
            else if(x > 1)
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires x <= 1, but got x = %1%.", x, pol);
            }
            else if((boost::math::isnan)(x))
            {
               return policies::raise_domain_error<T>(
                  function,
                  "atanh requires -1 <= x <= 1, but got x = %1%.", x, pol);
            }
            else if(x < -1 + tools::epsilon<T>())
            {
               // -Infinity:
               return -policies::raise_overflow_error<T>(function, 0, pol);
            }
            else if(x > 1 - tools::epsilon<T>())
            {
               // Infinity:
               return policies::raise_overflow_error<T>(function, 0, pol);
            }
            else if(abs(x) >= tools::forth_root_epsilon<T>())
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/02/
                if(abs(x) < 0.5f)
                   return (boost::math::log1p(x, pol) - boost::math::log1p(-x, pol)) / 2;
                return(log( (1 + x) / (1 - x) ) / 2);
            }
            else
            {
                // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/06/01/03/01/
                // approximation by taylor series in x at 0 up to order 2
                T    result = x;
                
                if    (abs(x) >= tools::root_epsilon<T>())
                {
                    T    x3 = x*x*x;
                    
                    // approximation by taylor series in x at 0 up to order 4
                    result += x3/static_cast<T>(3);
                }
                
                return(result);
            }
        }
       }

        template<typename T, typename Policy>
        inline typename tools::promote_args<T>::type atanh(T x, const Policy&)
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
              detail::atanh_imp(static_cast<value_type>(x), forwarding_policy()),
              "boost::math::atanh<%1%>(%1%)");
        }
        template<typename T>
        inline typename tools::promote_args<T>::type atanh(T x)
        {
           return boost::math::atanh(x, policies::policy<>());
        }

    }
}

#endif /* BOOST_ATANH_HPP */




/* atanh.hpp
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
*/