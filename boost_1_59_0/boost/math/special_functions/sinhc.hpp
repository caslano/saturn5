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

#include <boost/math/tools/precision.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <limits>
#include <string>
#include <stdexcept>
#include <cmath>

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
            using    ::std::abs;
            using    ::std::sinh;
            using    ::std::sqrt;

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

        template<typename T, template<typename> class U>
        inline U<T>    sinhc_pi(const U<T> x)
        {
            using std::abs;
            using std::sinh;
            using std::sqrt;

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
    }
}

#endif /* BOOST_SINHC_HPP */


/* sinhc.hpp
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
*/