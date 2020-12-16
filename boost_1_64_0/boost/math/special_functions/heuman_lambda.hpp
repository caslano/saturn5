//  Copyright (c) 2015 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ELLINT_HL_HPP
#define BOOST_MATH_ELLINT_HL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/jacobi_zeta.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/tools/workaround.hpp>

// Elliptic integral the Jacobi Zeta function.

namespace boost { namespace math { 
   
namespace detail{

// Elliptic integral - Jacobi Zeta
template <typename T, typename Policy>
T heuman_lambda_imp(T phi, T k, const Policy& pol)
{
    BOOST_MATH_STD_USING
    using namespace boost::math::tools;
    using namespace boost::math::constants;

    const char* function = "boost::math::heuman_lambda<%1%>(%1%, %1%)";

    if(fabs(k) > 1)
       return policies::raise_domain_error<T>(function, "We require |k| <= 1 but got k = %1%", k, pol);

    T result;
    T sinp = sin(phi);
    T cosp = cos(phi);
    T s2 = sinp * sinp;
    T k2 = k * k;
    T kp = 1 - k2;
    T delta = sqrt(1 - (kp * s2));
    if(fabs(phi) <= constants::half_pi<T>())
    {
       result = kp * sinp * cosp / (delta * constants::half_pi<T>());
       result *= ellint_rf_imp(T(0), kp, T(1), pol) + k2 * ellint_rj(T(0), kp, T(1), T(1 - k2 / (delta * delta)), pol) / (3 * delta * delta);
    }
    else
    {
       T rkp = sqrt(kp);
       T ratio;
       if(rkp == 1)
       {
          return policies::raise_domain_error<T>(function, "When 1-k^2 == 1 then phi must be < Pi/2, but got phi = %1%", phi, pol);
       }
       else
          ratio = ellint_f_imp(phi, rkp, pol) / ellint_k_imp(rkp, pol);
       result = ratio + ellint_k_imp(k, pol) * jacobi_zeta_imp(phi, rkp, pol) / constants::half_pi<T>();
    }
    return result;
}

} // detail

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::heuman_lambda_imp(static_cast<value_type>(phi), static_cast<value_type>(k), pol), "boost::math::heuman_lambda<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi)
{
   return boost::math::heuman_lambda(k, phi, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ELLINT_D_HPP


/* heuman_lambda.hpp
DQc0z33Y/D7l/inm/XepH7tE/f0GjQt1P9h8rsbjmsfd7FH7GVI4p9r7ZXrO9VvN97SePeUR3Scv1rrTIZXvF3VeP9K47O363oueN50/dZKJv0qvQdXn85W/j55hfs/qudQ3zfE1Rer/Fk9We9N44mJd/44p5vOa1+zZrfUk3X+fOEP5+rXmi99XfzJHzw3UP61r0fMXPdc4fJPS+YzKbaXGAeepv9P1OvQ7jXeCmifv0fOC8eeRP9C897Oq91p/2ft2zcPO1Tzpm0pf9em8rMZH5ar3v9J4Wuk9WaX75Xalr3HP/j+on71V49EXtKe+5smTz9A89TMaR71fzwmWmPAv7la//hGtZ12pcfu39H2fczQ/O6L1Ks3ri/bqucMWPSedrPWJCzTO/YTu2/erXUzT/W2bxsM/U70Zz+cl5v3Je63mfa2j3a/+c5bmBRt+YuJZ8j3Nc8K6v2vevEX5fvJMPa9aepopn8c0PtD9b/7VUzR+N5/bkVb4r+p7SGofU8/R/Mur51AP63s3ah+zdH1m3ajye1HfgytRPFv0vZQv6Tq220y5Ttb694c1f3lM6y2vqN+9Vt9/mqR+Q/Vi+7eUTt5q4h3Uc7Olqscb9D2Pel2vnNZlNK/d/DWNEzWOnnxIz+/UTnbreeCC083xDf9Qu5hqfp8R0jj5fn3vRPOmw3reOqNW6/Lj3wfS98j236PxXOMZ5vd367m11nsXXKHz6NJzKc2XNv3pNNM+Fuv9qVrXj2jc9KTWSX9q3l/zPq1L7dK60U90/fq1/vOs1qH13HXWr3U/2KD1/8FJ5nyeUH+2TvNIre+vuUnjyx0a5zk0T/iw4t2g+qf0d7fr+U+tviej9YwFi7VOOF/tfbL6nTdq3DVT888ZRUpH96v7VH8f17hZ3zs7PFn98Vq9r3WcO3dO1rq25lX+Is1ndL85T/VS6/EvaT3+7FmaX8S0HvuC+plf6n4yX/1bn57/PKv72N9MPp+Yqvqv56tPaz6w5VNFeh6r63tU96Xx/vSnJv2HdqhdfVnXpUTPrWt1fp9TeSzQ9z/cWmfYpPuL1rM2fVbjsZ9qfPprrVfre047njHvb3+znve837z/nE3rod/W+HS7+tN+rYv9SN+f0feDZmv9dbrm7Q89rHmO1lk33aF52qD67Sv0fZ5faF1Y86mHvq51vUM6T42PNmk9bXdG7UDz2sk3aLzyMX3P5Yi+H6vvm236keYdKdULjW+3xjW+0PdWN6of3a/55Fb1H/tVzzeqnexu0jjuAX0/Us+zZuh7ifdmNP78N013H5/l+IYBfE89T9tqpVEqKkZTU+sFo1VLq6ZGo7dhGEWjIURhFEZR6Ee0GEZDiIZQCqMhjEI0DFNDNLUyLA3p5/O5v88f3J+2e/fLdZ0vx3Gc531d9JkG/GOmvqXtZ+l/mKZfpUc4sIenxa0WegFdoqQTHRAPm18c/HzQp8Y7gR6mDrA5EZ49j151l/e/Q33wYvZWgRddwr/ejAvi5bP0vSPpyFE8MtB7dzDeU+HbAcF4bnqB/y/AM9TP8g/FD6L9eGF4VZ/C7Av1RY2KU3+k4x2HPy6XD86mz/0UrW8G199gXlro3EnwfXMr+scl/PdJ9cZt6hHvBddbeDwemytujoCrOsIrn6ujDYALythxljgyDD/5Gt9Rn2sWp+JL4PKN7PoDeTdV33V/vEgfe+bL9LMH5KFD6FcL5cFyceg4z19KR5uMn+XgU7X4zcPqaaPFjVWe+0b+q+5W6n7NcGXNeHHzl7C+xeDvS45vpf4Hx/Ri7wvYyzLXmyJ+62+ufMQ45Zn3QeL4GeJmvHg6SJ4+A06/PiIewZGV4kcLHk2HKruff7I=
*/