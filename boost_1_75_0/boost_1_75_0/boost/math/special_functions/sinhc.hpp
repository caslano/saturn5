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
dai89jNeyzpwnhy8rhMHRKHrOtN0fPrF93ZDGxxmbSDv81ucxmFvT9fxGFW+x9L1ug+Kb1R0XHxvI3x/a4rgVVWGnr9WfNcr9Fhj2jjbZNJkzpqWHKaxvSFzenvb04x420iGlreWtmK2KUPjWb/Iu0fBc7/yfUw5SKvKC+5LAv659MXZTOxhx1iEcxrY94q9nlszdNnBHULYdwK9C/nencLvPbca5Ad9Tr+X56TgeX+KjoPsG9YEsiTLoV6cTcI+8mLCZVAvp8oP4KVq5epSjH3VStS+aOy3xUq/xdiBNtX7Im/TehLfb3HWErzYFtNv6xmeTkO/3ZLCzzB5lH5rEm2QJfh/9kN+jg7jB85pYS8xdHSnIMoqeA9dcRQRgudT8b0qJbmuw7MnRW9X2f/rSXz/j8UfuEq8DrL82GuQxnBIpZKZIq7yRrtV0ZCalirSTrK0VENamrwCHGdJaUhNM4m0CpZmMqSli7QalpZuSMsQaVaWlmFIyxRpdk4LRBpXLNSn8Wv36sX1/PXY94ozPjgL97q4y8UszvIRQT/awSnaaLtop9AUvBlKTc6bbanJeTMyBW/2JKADe4awlxhnhg4mwHf7FDgengLH56bA8fUpcDw9RftlpSVuB+zjw/4pnMHDvsS18g6mGL6rcoz02hg5hjBMEL1/490lBgyMOTai9iU/60tSvx5ON+owtV+x9kyoz4y2x9R68L9D
*/