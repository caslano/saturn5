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
g/WnjKZr0UXGb2tZTAu6XqV6/KSqMLQXpK8xjU675TdD0/4ilOn4z90a1ei0iot3Xewmb6PBGab2aa9sXTelyn4J0RvkCZfTMT+xMfr9jkojiWbn+spOiv0DDbdyGhPHmOL+IdbtJLtEuy92aUvSqrTTHkzXQuoOGWgY431CWepsc9fP+i5Ydx5t45+addtwXuRo5o3ZR+9cPwM8zCujR3LpLGag7y0a0A1ndkm7hWRw0yd6Hsitxs2GCaEWzVsG20IsOc9X3g8/me7m7+TsvNsp1NnLVCyw2arJY0tzCFzMSjo7Avpf0l2G+JWYwecxkbUo1meKZ99WnR36os6Dh8a+BuQYBXh8iMeNBYQefVuFVPRx5s0tYbRraKvLpJ8yw2QCt70QKqLvdfezxZjaM7rNyq6DToG0Z/JhMO1RI4jCuVzYLuO6C31j7SGyrlbiNCt6Z6hWSpCAI7my0RTWpEuuSisvw8aFctvyvD3uk+7s/IwX8VJIK8q6OpKKhA2Fs12hzo3Vavzv47sOTDTXlWkL6KHs/EgB64Uk9zzJZr455a3YWMLou0LZ3dYrfJ/qu/AfdEr1WYi5wg+pfpxe9AIHHYd9pSNUwZQxVEt5rolL233+KFZQmU01H0POKqaw1QWVaSWTmdMfMFkv0eJZ57Oe3+TO/4Fv0zNuA1D3nLvvzppP63NusXt/V7tG1o4tX30Aiw8QaTodI9wo
*/