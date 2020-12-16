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
HDX6zInKcZbxGqav6SfJ5176YNsm8mTXM2113cmoM2mPK+w4/oCZ42Kn5z/NnGYvawzZZkT618FAJaN/TzZGKTllzKMnq9dpvSk/03HEnuVc2ywtFlz/WdrhgBwV2gyZE3622nM2CQ4p02bInHDOMZxNgkPKtJ+jXRbEnquf7P3fuvgUYzLrtfNtJgTtK9EimDc/vS+vM2BJ7PrGnn0OqdBlQugG5iY7pChSZ8ji/+47tMfc54SNlM88pDmmw5SIz0A3JkGBOkMGpz9jJfIln9nZI0eNPgsiD/3vWv0VpReoy3oN/cmpl8i/aExfqt+vNA/YWK8d32ZK/dVywzpun2PPGWgx5szFXWdkKNNlTOAS5wxscnP2OaRChwnDK7ou2djyWnzGtUmVPgsi1xGbOCmK1BkwJ3pdr8Pr+wpU6TElXHA9cMARLSaEXqTG7JOjSp8lm2rQPP1e5fyAWmQZvkGtCL3MeJ0+v77HQJxjWiy5ftG4kaVCjwUxtbw5++Sp0uOs9T0EMpRocWO1DqttW22DL5c/exxSpctsfR+B67NPnjZToq8wTqQo0/u/+wfssnE63qRockJQX+ueG7JkXw55DkryosP11/cEyNMn8hq5sk+BJhMir7WffQo0GBHUn2sQJ8OE8OscS4ICTU4IvF6+1OQwYMnJaa3sy1Cmy3S9/v8Me+Sos1FWA/bJUaHNyLhm3mjMaDMm+CZtsUOKIlV6zIi8Wd/Z45ASbSbrewBcgzgZyrQZE3iL8SVOhmM6TIiu1/zvk6NGnxWbbzM+7HPIMR3GBKryeaM22SV2+noTD/odsrFjSWy93j/6cfs+pu0/yosOs6Z6fVhtvqTm5Cn8UrueC/1ZHTibA9J/1VeO6mpP6L3qQI0BK1Lvcwy5v6kxPebE/m6+c0CeOkOq6zXyDXmc+aR8P+XYT4snhyXBX2mXs38tbzZ/o33O+r1rg+BcTdj9g2uMKj3mtOQ6JrQ0lj+Q84k2Z2r2W/VinwIttvyuar8hN6aUP2jcmKzX2t+YBP0vy4uNr6hn334OOKLDjNYvxJf7QN7B38mZs0lyRJPIx9SOBEWaLLixMdojy1kdeZOmTIcZ4c+oJUlOvu6cgbi0mBAYam/keYo0GbJi63tqRYYKfVZsfd9+MlTos2Rzvba3RJOT9frea7BHniahH9rHvchSoc+SrR+JTZpjOkzIflp+ahn5vFqQoEiLMeEv6BvH/7duPU6WMl1mRHvmL0mKtJhQ+5LjlnK/gc9W5s6IFcGZODS419ycocuUvnk+5/p/sZ8uM6J/1ZeldtrnCoR+bGzYJcURTUas2Bw7jviv+Ju4H3H+R801mpwQb5m3VFm5Djb+5RwSFGhwQvgD2vmaMeCYDjM2vi4Gh9QJrdexR78hDinK9Ams16zvk6fJmOi3HEuaCgOuP5QDRRoMCX7b+dyLHE0mxL7jfNKU6TJjY70ePU2ZLjNiI337lbiMfq9vf5DTUh848zf9+8q5Ap31mu2Nn4hBlgo9Fmz9VB7kqDMi9DN5k6BAizGhif0kKNJmSuznYpOhwmC9HvsM+xQYqXvgg8aZOFnyrv8aSzabxoUzH3YdUGfFwfr+GYX1/Q0m3Our9pG+gfdArus+KzKfUB8ibXmyT4E6I4Kf1DYttrwu7pChQp/h+r4LW6evRxdzzXPEZlSeXn92bFPs7xm/D2i/6Tm5bZMVc981tePcJHXmxuUaf5Dr6fz/q7aJGpcbn9d7MLpM6Ye8x+L65/Mei1TE+y82L2KdG1mOKV7UezJmRC5mPxUmhHz2KtHi7JjPnaQv5WehhC7tZ65kLq9eBK7gMSHvB69BmhI9n1fDfi50Fvcifg3vI6k=
*/