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
I9TfTmDrQv39iByzQ/52A+sZ9ku1hpcqASxHsLzot38OEKxnRONAwUq6hrCags06Kcr/CVY0Ivr9X8EK90T1f4JVjeQ9Gv56R/k/xka/hXiSYGOj+0JNgeWG9j0dfFE9V3PwRfn2c+BlQ8hLa8FKW4ewQsEKPg910AlYSdjvIniJfmumB7wsC21+GXSnhvj6Atsewq6Cl73h2KsFK47OEUdgy+je7GjB8qM93Q3w8qcQ3630i76Dd0Ajuqs1iX6tQtjf4G9odP9XsPlR7eUsdBWdw87BX6I116Po78+hnz4Jz1F9xDPAolrnF4CtDWV7BRrbo/o//Dn+/Q/kuCCq/8Nfqka//wu+00N8G8G3KJTtA+QtDft9hGzdo3//D51GvvYlsdUohO2g35kh7AfkrRLKuwu60TnJb/B3ZUg3+3zN46mo/k+wojFR/o9+UV1VDcHmR3FUW7CxEd1DBdvRN6R7hGD5t0W//yFYYdNQtuMEq3pSCGsEL6Oi+j/BUheFsD8Di3KHBYKVfp0VwFoKdsGw0L7noYP1qQDWTrCSqAaoI7JFvHRFB7NDv79EsOLofm1v5B0X6qoPOp0S5f+QY0HYb4hgBc9E+T9gP4Y8/xVeon9L9Hp4iXKvtzC2WRhv4+Fld5T/Q/fRb1VMFSyvXMjfPdA9LITNBF+7KP+HDiIac7FRtJd8An/ZHf3+L2OjPOY/4CX6XZSF6O+pKP+HXx0Y3f9lbHRGv4p+0X5rrWCz6of8bUC2xSHsfXwjuk9XCs+7Qth25I1+T+kL+k0OYd+g0+iOzvfYcl0YR7/gp41D2fbSL1pLZbXRNz76DeRcwQqi+wuVBSvuGdq8umBjS8OxBwtWsiyMrXqM/Tm6/8vYetHvf9AvuqN9rGCF0Z2GfMFmNY7u/wpWtSC0+Z8Euye6h3umYIu7h3TPRt7ID1rRL7qb2xZeZkT5P+hG+cku8JcbytFdsPwKIexSYNE370r0tzXU6QBsFNljsGB5FTMC2HDBdkyK7v/SL6rfHStY6cth7N8sWFFUc3w7Y68K+01E3htDP7gLXW0KdTUdXXWI6v8YWzGEPQgvUa7+Efzg0pDGPPwluvv/lGCp6H7e88DmRb//gU43h/wtQafR79gtQwdR/eRK+Nsc4itBz41DntcLNj+qJdmEDiL+PsQ3ng/xbWNsVAf1OXKMifJ/4Ivi4zv6RTX+PyNbcdhvDzZ6JdRfZlt+pzCkUV6woohuJcHGfhLV/wm2I7JRLcFSfUJYXcGqFoay5QlWEt//BV+UDzuGftF34UR4bhv2OwUaL0T1f4LNnxPG5RmCFWyNfv+DsdFZ27mC9dwQ0m2DXqaGOu0gWPHHqQB2Ify9GfpaN3iJ9pe9BJvVPqr/E2xxVBvaH7oLQnxFghW+F+pvGDaK9uejkLdXiG8MNKJvwE3IsT3Uyzhgk0L+7hSsdE0Im4K8kX2nQSO6q38f/QaE/D0ArE90/xc5onPEx4GtivJ/+EZUO/Mcdoti9SXsG/3m+GL08kVo86XYKPpNuBXoORq7Bh1Eecd10I3mg/egOy3K/2HzhWG/j6ERyfYZNu8Z2vxrYivS87fETBQfP8FLVG/xK7xE6+KMdpI3OusoJ1jeT1H9n2CF14T4qgpWcnkIO0iwHdHZ2CH0+ywrgB0uWNHKqP5PsNJor9FQsPxofXoCsOhu/cnwvCCEnSrY4mjt2AxeojqPFujgbyHsL/D3VQg7X7CC7BDWXrD4PLQzcuwN7XGxYGMrhmN7Qjeqq7pcsOLo/kc/dB/BBjF2dggbKljP6LcaRwo2q3cIuw4a20J/vlGwEWNCOW6Dxobo93+xb37oL5PRS2YIuxsa0fnRDMY=
*/