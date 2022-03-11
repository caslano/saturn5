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
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>
#include <string>
#include <stdexcept>


#include <boost/config.hpp>


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

#ifndef    BOOST_NO_TEMPLATE_TEMPLATES
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
#endif    /* BOOST_NO_TEMPLATE_TEMPLATES */
    }
}

#endif /* BOOST_SINC_HPP */


/* sinc.hpp
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
*/