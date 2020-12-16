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
1mt6+8yJeP4Mexyy65g0JQLiZtbr9mv0mD7Z65PtkuiFXS/sErV/Yl/ywuJwTJPxaf/V4uQp5vLjzbG02ttXzKop209TX+0EMsbPMWc91TwjwzFd5mxmjSvLx/r6cV4TSFGiw5So+Ddmnxw1BmxrM0mJNlMicsprs8GY8JPX99ok8kTjyAFHNBmxYkvuO9z8yfpFgQYjAvLfYocURzRJPEZb1OkT0+fhNX1PJHherwvc/MbnDjSN4XZGrNN+cqAuqfU66KSffWZPx5cWew85byC4XjO9w2x9z4Kz2CFNkToD5pxZ37sgT4WzLulYDshRpsWQOeGY5zkgR+te5w3Uuvrm3C4RTtb3PTgrJrfLG/vL2ndp82XL2F9W3lcQ78r6dRl5XPG/6/43LuX78/reBm1WbFxGOxSo0WN/Q05itAms70nQuZy4ZP7vXgJbYu5QZ0Mb2ySosSAml5uTIE8fa/797YEY/m5iTCB8zsAWZ3NAnio9ZoT93dIZ7kWWMssr+duKK/vbJxLkqNBhTPAqfqbGDimOaDKipP36WWp1VX27mpxYcPOr6zeHVOn+33r+G5OnTuGazjm9zmNqxZxtdU1RosuCs9R2qpYRtbw+h1TpsWBTbeNsqu0uadpMCV9Om6zv9+B+/uor77NpMyVyOrakqbJxFWNBieL6vgdzztI39xrwt3DaIU2ZDmOC63tF7LK8hjG7plqwT1kfzhIjxfWvauxp44853QNCe2fJ46raOq2LOdBnQVoObSbEPX9MXB5ZqiSuod2ztKW+tZs5nwWxm+sTSYq0OesW2qdEm61bapcBK7ZuJXeyVOkT2PaYGbFbqxstxpx9G/Ep0mTEiq3bikOaCqmz1Y0Rgds5hyIN0rfXJzrMiK7Xsicp0WbOakdOd5QrK9J3ch4dFuZQ9KbGmQRn1vcoKFHwuE6fKSG1OUOclD6HTvO+nRhvO7d7G5jLNxefLf3doSP/MeH1ev5teRxQokct4u9RyV3dz+QZsCIv/s4tPK+Nsjhdimebo3LfIU3rJtpmwfh0bG6t3duhTwHnHZ3W2GPr7n0O8fN+BiyInsPvYi7jb8qIU4+LfQ/1u6c8SRC8l/lInNKd1fGu+m47Ey+yXqufpsXmrvlxF+ffTY3Fat5dbuLd/EJ+5kmWMtmzXPc0GZG5i7o7J0edEVtx4393sek9VE3FX5HwXPD0OVIUGazX3lfle2y7o80URxTsm8XV/u7y8bjr8YTsvdTM45nY4YepHWev7y9QpseCXblV6LNkS/93yVCmxzXujvO3riNH35M2bqTPdPR1zEofN656zkDs894zXc/3/T153d8cuJ82qN5Xzfb+uyZ+eB+18DiSMH/vo380WBC1f49Desy58Z5jmBARq8CAqPjXp86WuBkaDzJXH2yMxD6bwIXlxc1JUKDOiBUbEd8HuPlVjR9ZynSZEr2av2FkjywVytrps2BrX32113+Iusgj7vE1HihXgnLZ4mzy7KzX4B9TlFv0IerCjfWlzv76HgKZ9X0A2owJibVHlio9umIciNFgwIJtsRZEd4zPc7TDVL4H2u4zY8t5ifVa/uubF9vGq367cwdSFNnhxo80D7bPHUh67l6PlDNdtpLaJEeVHqVbnDtQ8Fxovc6+ul57P0nq/6PsI88BXbaoMGZB5NGOIUmBOqvrnztwDds+cyKPcT0SJ8MxY4Ip48y9Lma8uEbUNU7+Wq599q/t9YbIY51PK6VWzEl7nHuKfOkxYyMrV6qeO9L3rm2cIlPCjzO27JLkiAY3fpLjiDxVTdkjS4k2J6wor9exDx6nPcKPdzx75KjSY/Z/6/j3yVOjz5zoE/SHPQ6p0mNG5InOY48=
*/