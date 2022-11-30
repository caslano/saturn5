//  boost sinc.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SINC_HPP
#define BOOST_SINC_HPP


#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <limits>
#include <string>
#include <stdexcept>
#include <cmath>

// These are the the "Sinus Cardinal" functions.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        // This is the "Sinus Cardinal" of index Pi.

        template<typename T>
        inline T    sinc_pi_imp(const T x)
        {
            BOOST_MATH_STD_USING

            if    (abs(x) >= 3.3 * tools::forth_root_epsilon<T>())
            {
                return(sin(x)/x);
            }
            else
            {
                // |x| < (eps*120)^(1/4)
                return 1 - x * x / 6;
            }
        }

       } // namespace detail

       template <class T>
       inline typename tools::promote_args<T>::type sinc_pi(T x)
       {
          typedef typename tools::promote_args<T>::type result_type;
          return detail::sinc_pi_imp(static_cast<result_type>(x));
       }

       template <class T, class Policy>
       inline typename tools::promote_args<T>::type sinc_pi(T x, const Policy&)
       {
          typedef typename tools::promote_args<T>::type result_type;
          return detail::sinc_pi_imp(static_cast<result_type>(x));
       }

        template<typename T, template<typename> class U>
        inline U<T>    sinc_pi(const U<T> x)
        {
            BOOST_MATH_STD_USING
            using    ::std::numeric_limits;

            T const    taylor_0_bound = tools::epsilon<T>();
            T const    taylor_2_bound = tools::root_epsilon<T>();
            T const    taylor_n_bound = tools::forth_root_epsilon<T>();

            if    (abs(x) >= taylor_n_bound)
            {
                return(sin(x)/x);
            }
            else
            {
                // approximation by taylor series in x at 0 up to order 0
#ifdef __MWERKS__
                U<T>    result = static_cast<U<T> >(1);
#else
                U<T>    result = U<T>(1);
#endif

                if    (abs(x) >= taylor_0_bound)
                {
                    U<T>    x2 = x*x;

                    // approximation by taylor series in x at 0 up to order 2
                    result -= x2/static_cast<T>(6);

                    if    (abs(x) >= taylor_2_bound)
                    {
                        // approximation by taylor series in x at 0 up to order 4
                        result += (x2*x2)/static_cast<T>(120);
                    }
                }

                return(result);
            }
        }

        template<typename T, template<typename> class U, class Policy>
        inline U<T>    sinc_pi(const U<T> x, const Policy&)
        {
           return sinc_pi(x);
        }
    }
}

#endif /* BOOST_SINC_HPP */


/* sinc.hpp
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
*/