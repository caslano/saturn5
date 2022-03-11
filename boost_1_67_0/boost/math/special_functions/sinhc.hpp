//  boost sinhc.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_SINHC_HPP
#define BOOST_SINHC_HPP


#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>
#include <string>
#include <stdexcept>

#include <boost/config.hpp>


// These are the the "Hyperbolic Sinus Cardinal" functions.

namespace boost
{
    namespace math
    {
       namespace detail
       {
        // This is the "Hyperbolic Sinus Cardinal" of index Pi.

        template<typename T>
        inline T    sinhc_pi_imp(const T x)
        {
#if defined(BOOST_NO_STDC_NAMESPACE) && !defined(__SUNPRO_CC)
            using    ::abs;
            using    ::sinh;
            using    ::sqrt;
#else    /* BOOST_NO_STDC_NAMESPACE */
            using    ::std::abs;
            using    ::std::sinh;
            using    ::std::sqrt;
#endif    /* BOOST_NO_STDC_NAMESPACE */

            static T const    taylor_0_bound = tools::epsilon<T>();
            static T const    taylor_2_bound = sqrt(taylor_0_bound);
            static T const    taylor_n_bound = sqrt(taylor_2_bound);

            if    (abs(x) >= taylor_n_bound)
            {
                return(sinh(x)/x);
            }
            else
            {
                // approximation by taylor series in x at 0 up to order 0
                T    result = static_cast<T>(1);

                if    (abs(x) >= taylor_0_bound)
                {
                    T    x2 = x*x;

                    // approximation by taylor series in x at 0 up to order 2
                    result += x2/static_cast<T>(6);

                    if    (abs(x) >= taylor_2_bound)
                    {
                        // approximation by taylor series in x at 0 up to order 4
                        result += (x2*x2)/static_cast<T>(120);
                    }
                }

                return(result);
            }
        }

       } // namespace detail

       template <class T>
       inline typename tools::promote_args<T>::type sinhc_pi(T x)
       {
          typedef typename tools::promote_args<T>::type result_type;
          return detail::sinhc_pi_imp(static_cast<result_type>(x));
       }

       template <class T, class Policy>
       inline typename tools::promote_args<T>::type sinhc_pi(T x, const Policy&)
       {
          return boost::math::sinhc_pi(x);
       }

#ifdef    BOOST_NO_TEMPLATE_TEMPLATES
#else    /* BOOST_NO_TEMPLATE_TEMPLATES */
        template<typename T, template<typename> class U>
        inline U<T>    sinhc_pi(const U<T> x)
        {
#if defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL) || defined(__GNUC__)
            using namespace std;
#elif    defined(BOOST_NO_STDC_NAMESPACE) && !defined(__SUNPRO_CC)
            using    ::abs;
            using    ::sinh;
            using    ::sqrt;
#else    /* BOOST_NO_STDC_NAMESPACE */
            using    ::std::abs;
            using    ::std::sinh;
            using    ::std::sqrt;
#endif    /* BOOST_NO_STDC_NAMESPACE */

            using    ::std::numeric_limits;

            static T const    taylor_0_bound = tools::epsilon<T>();
            static T const    taylor_2_bound = sqrt(taylor_0_bound);
            static T const    taylor_n_bound = sqrt(taylor_2_bound);

            if    (abs(x) >= taylor_n_bound)
            {
                return(sinh(x)/x);
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
                    result += x2/static_cast<T>(6);

                    if    (abs(x) >= taylor_2_bound)
                    {
                        // approximation by taylor series in x at 0 up to order 4
                        result += (x2*x2)/static_cast<T>(120);
                    }
                }

                return(result);
            }
        }
#endif    /* BOOST_NO_TEMPLATE_TEMPLATES */
    }
}

#endif /* BOOST_SINHC_HPP */


/* sinhc.hpp
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
*/