// Jacobi theta functions
// Copyright Evan Miller 2020
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Four main theta functions with various flavors of parameterization,
// floating-point policies, and bonus "minus 1" versions of functions 3 and 4
// designed to preserve accuracy for small q. Twenty-four C++ functions are
// provided in all.
//
// The functions take a real argument z and a parameter known as q, or its close
// relative tau.
//
// The mathematical functions are best understood in terms of their Fourier
// series. Using the q parameterization, and summing from n = 0 to INF:
//
// theta_1(z,q) = 2 SUM (-1)^n * q^(n+1/2)^2 * sin((2n+1)z)
// theta_2(z,q) = 2 SUM q^(n+1/2)^2 * cos((2n+1)z)
// theta_3(z,q) = 1 + 2 SUM q^n^2 * cos(2nz)
// theta_4(z,q) = 1 + 2 SUM (-1)^n * q^n^2 * cos(2nz)
//
// Appropriately multiplied and divided, these four theta functions can be used
// to implement the famous Jacabi elliptic functions - but this is not really
// recommended, as the existing Boost implementations are likely faster and
// more accurate.  More saliently, setting z = 0 on the fourth theta function
// will produce the limiting CDF of the Kolmogorov-Smirnov distribution, which
// is this particular implementation's raison d'etre.
//
// Separate C++ functions are provided for q and for tau. The main q functions are:
//
// template <class T> inline T jacobi_theta1(T z, T q);
// template <class T> inline T jacobi_theta2(T z, T q);
// template <class T> inline T jacobi_theta3(T z, T q);
// template <class T> inline T jacobi_theta4(T z, T q);
//
// The parameter q, also known as the nome, is restricted to the domain (0, 1),
// and will throw a domain error otherwise.
//
// The equivalent functions that use tau instead of q are:
//
// template <class T> inline T jacobi_theta1tau(T z, T tau);
// template <class T> inline T jacobi_theta2tau(T z, T tau);
// template <class T> inline T jacobi_theta3tau(T z, T tau);
// template <class T> inline T jacobi_theta4tau(T z, T tau);
//
// Mathematically, q and tau are related by:
//
// q = exp(i PI*Tau)
//
// However, the tau in the equation above is *not* identical to the tau in the function
// signature. Instead, `tau` is the imaginary component of tau. Mathematically, tau can
// be complex - but practically, most applications call for a purely imaginary tau.
// Rather than provide a full complex-number API, the author decided to treat the
// parameter `tau` as an imaginary number. So in computational terms, the
// relationship between `q` and `tau` is given by:
//
// q = exp(-constants::pi<T>() * tau)
//
// The tau versions are provided for the sake of accuracy, as well as conformance
// with common notation. If your q is an exponential, you are better off using
// the tau versions, e.g.
//
// jacobi_theta1(z, exp(-a)); // rather poor accuracy
// jacobi_theta1tau(z, a / constants::pi<T>()); // better accuracy
//
// Similarly, if you have a precise (small positive) value for the complement
// of q, you can obtain a more precise answer overall by passing the result of
// `log1p` to the tau parameter:
//
// jacobi_theta1(z, 1-q_complement); // precision lost in subtraction
// jacobi_theta1tau(z, -log1p(-q_complement) / constants::pi<T>()); // better!
//
// A third quartet of functions are provided for improving accuracy in cases
// where q is small, specifically |q| < exp(-PI) = 0.04 (or, equivalently, tau
// greater than unity). In this domain of q values, the third and fourth theta
// functions always return values close to 1. So the following "m1" functions
// are provided, similar in spirit to `expm1`, which return one less than their
// regular counterparts:
//
// template <class T> inline T jacobi_theta3m1(T z, T q);
// template <class T> inline T jacobi_theta4m1(T z, T q);
// template <class T> inline T jacobi_theta3m1tau(T z, T tau);
// template <class T> inline T jacobi_theta4m1tau(T z, T tau);
//
// Note that "m1" versions of the first and second theta would not be useful,
// as their ranges are not confined to a neighborhood around 1 (see the Fourier
// transform representations above).
//
// Finally, the twelve functions above are each available with a third Policy
// argument, which can be used to define a custom epsilon value. These Policy
// versions bring the total number of functions provided by jacobi_theta.hpp
// to twenty-four.
//
// See:
// https://mathworld.wolfram.com/JacobiThetaFunctions.html
// https://dlmf.nist.gov/20

#ifndef BOOST_MATH_JACOBI_THETA_HPP
#define BOOST_MATH_JACOBI_THETA_HPP

#include <boost/math/tools/complex.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost{ namespace math{

// Simple functions - parameterized by q
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta1(T z, U q);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta2(T z, U q);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3(T z, U q);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4(T z, U q);

// Simple functions - parameterized by tau (assumed imaginary)
// q = exp(i*PI*TAU)
// tau = -log(q)/PI
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta1tau(T z, U tau);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta2tau(T z, U tau);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3tau(T z, U tau);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4tau(T z, U tau);

// Minus one versions for small q / large tau
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1(T z, U q);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1(T z, U q);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1tau(T z, U tau);
template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1tau(T z, U tau);

// Policied versions - parameterized by q
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta1(T z, U q, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta2(T z, U q, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3(T z, U q, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4(T z, U q, const Policy& pol);

// Policied versions - parameterized by tau
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta1tau(T z, U tau, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta2tau(T z, U tau, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3tau(T z, U tau, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4tau(T z, U tau, const Policy& pol);

// Policied m1 functions
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1(T z, U q, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1(T z, U q, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1tau(T z, U tau, const Policy& pol);
template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1tau(T z, U tau, const Policy& pol);

// Compare the non-oscillating component of the delta to the previous delta.
// Both are assumed to be non-negative.
template <class RealType>
inline bool
_jacobi_theta_converged(RealType last_delta, RealType delta, RealType eps) {
    return delta == 0.0 || delta < eps*last_delta;
}

template <class RealType>
inline RealType
_jacobi_theta_sum(RealType tau, RealType z_n, RealType z_increment, RealType eps) {
    BOOST_MATH_STD_USING
    RealType delta = 0, partial_result = 0;
    RealType last_delta = 0;

    do {
        last_delta = delta;
        delta = exp(-tau*z_n*z_n/constants::pi<RealType>());
        partial_result += delta;
        z_n += z_increment;
    } while (!_jacobi_theta_converged(last_delta, delta, eps));

    return partial_result;
}

// The following _IMAGINARY theta functions assume imaginary z and are for
// internal use only. They are designed to increase accuracy and reduce the
// number of iterations required for convergence for large |q|. The z argument
// is scaled by tau, and the summations are rewritten to be double-sided
// following DLMF 20.13.4 and 20.13.5. The return values are scaled by
// exp(-tau*z^2/Pi)/sqrt(tau).
//
// These functions are triggered when tau < 1, i.e. |q| > exp(-Pi) = 0.043
//
// Note that jacobi_theta4 uses the imaginary version of jacobi_theta2 (and
// vice-versa). jacobi_theta1 and jacobi_theta3 use the imaginary versions of
// themselves, following DLMF 20.7.30 - 20.7.33.
template <class RealType, class Policy>
inline RealType
_IMAGINARY_jacobi_theta1tau(RealType z, RealType tau, const Policy&) {
    BOOST_MATH_STD_USING
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType result = RealType(0);

    // n>=0 even
    result -= _jacobi_theta_sum(tau, RealType(z + constants::half_pi<RealType>()), constants::two_pi<RealType>(), eps);
    // n>0 odd
    result += _jacobi_theta_sum(tau, RealType(z + constants::half_pi<RealType>() + constants::pi<RealType>()), constants::two_pi<RealType>(), eps);
    // n<0 odd
    result += _jacobi_theta_sum(tau, RealType(z - constants::half_pi<RealType>()), RealType (-constants::two_pi<RealType>()), eps);
    // n<0 even
    result -= _jacobi_theta_sum(tau, RealType(z - constants::half_pi<RealType>() - constants::pi<RealType>()), RealType (-constants::two_pi<RealType>()), eps);

    return result * sqrt(tau);
}

template <class RealType, class Policy>
inline RealType
_IMAGINARY_jacobi_theta2tau(RealType z, RealType tau, const Policy&) {
    BOOST_MATH_STD_USING
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType result = RealType(0);

    // n>=0
    result += _jacobi_theta_sum(tau, RealType(z + constants::half_pi<RealType>()), constants::pi<RealType>(), eps);
    // n<0
    result += _jacobi_theta_sum(tau, RealType(z - constants::half_pi<RealType>()), RealType (-constants::pi<RealType>()), eps);

    return result * sqrt(tau);
}

template <class RealType, class Policy>
inline RealType
_IMAGINARY_jacobi_theta3tau(RealType z, RealType tau, const Policy&) {
    BOOST_MATH_STD_USING
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType result = 0;

    // n=0
    result += exp(-z*z*tau/constants::pi<RealType>());
    // n>0
    result += _jacobi_theta_sum(tau, RealType(z + constants::pi<RealType>()), constants::pi<RealType>(), eps);
    // n<0
    result += _jacobi_theta_sum(tau, RealType(z - constants::pi<RealType>()), RealType(-constants::pi<RealType>()), eps);

    return result * sqrt(tau);
}

template <class RealType, class Policy>
inline RealType
_IMAGINARY_jacobi_theta4tau(RealType z, RealType tau, const Policy&) {
    BOOST_MATH_STD_USING
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType result = 0;

    // n = 0
    result += exp(-z*z*tau/constants::pi<RealType>());

    // n > 0 odd
    result -= _jacobi_theta_sum(tau, RealType(z + constants::pi<RealType>()), constants::two_pi<RealType>(), eps);
    // n < 0 odd
    result -= _jacobi_theta_sum(tau, RealType(z - constants::pi<RealType>()), RealType (-constants::two_pi<RealType>()), eps);
    // n > 0 even
    result += _jacobi_theta_sum(tau, RealType(z + constants::two_pi<RealType>()), constants::two_pi<RealType>(), eps);
    // n < 0 even
    result += _jacobi_theta_sum(tau, RealType(z - constants::two_pi<RealType>()), RealType (-constants::two_pi<RealType>()), eps);

    return result * sqrt(tau);
}

// First Jacobi theta function (Parameterized by tau - assumed imaginary)
// = 2 * SUM (-1)^n * exp(i*Pi*Tau*(n+1/2)^2) * sin((2n+1)z)
template <class RealType, class Policy>
inline RealType
jacobi_theta1tau_imp(RealType z, RealType tau, const Policy& pol, const char *function)
{
    BOOST_MATH_STD_USING
    unsigned n = 0;
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType q_n = 0, last_q_n, delta, result = 0;

    if (tau <= 0.0)
        return policies::raise_domain_error<RealType>(function,
                "tau must be greater than 0 but got %1%.", tau, pol);

    if (abs(z) == 0.0)
        return result;

    if (tau < 1.0) {
        z = fmod(z, constants::two_pi<RealType>());
        while (z > constants::pi<RealType>()) {
            z -= constants::two_pi<RealType>();
        }
        while (z < -constants::pi<RealType>()) {
            z += constants::two_pi<RealType>();
        }

        return _IMAGINARY_jacobi_theta1tau(z, RealType(1/tau), pol);
    }

    do {
        last_q_n = q_n;
        q_n = exp(-tau * constants::pi<RealType>() * RealType(n + 0.5)*RealType(n + 0.5) );
        delta = q_n * sin(RealType(2*n+1)*z);
        if (n%2)
            delta = -delta;

        result += delta + delta;
        n++;
    } while (!_jacobi_theta_converged(last_q_n, q_n, eps));

    return result;
}

// First Jacobi theta function (Parameterized by q)
// = 2 * SUM (-1)^n * q^(n+1/2)^2 * sin((2n+1)z)
template <class RealType, class Policy>
inline RealType
jacobi_theta1_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
                "q must be greater than 0 and less than 1 but got %1%.", q, pol);
    }
    return jacobi_theta1tau_imp(z, RealType (-log(q)/constants::pi<RealType>()), pol, function);
}

// Second Jacobi theta function (Parameterized by tau - assumed imaginary)
// = 2 * SUM exp(i*Pi*Tau*(n+1/2)^2) * cos((2n+1)z)
template <class RealType, class Policy>
inline RealType
jacobi_theta2tau_imp(RealType z, RealType tau, const Policy& pol, const char *function)
{
    BOOST_MATH_STD_USING
    unsigned n = 0;
    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType q_n = 0, last_q_n, delta, result = 0;

    if (tau <= 0.0) {
        return policies::raise_domain_error<RealType>(function,
                "tau must be greater than 0 but got %1%.", tau, pol);
    } else if (tau < 1.0 && abs(z) == 0.0) {
        return jacobi_theta4tau(z, 1/tau, pol) / sqrt(tau);
    } else if (tau < 1.0) { // DLMF 20.7.31
        z = fmod(z, constants::two_pi<RealType>());
        while (z > constants::pi<RealType>()) {
            z -= constants::two_pi<RealType>();
        }
        while (z < -constants::pi<RealType>()) {
            z += constants::two_pi<RealType>();
        }

        return _IMAGINARY_jacobi_theta4tau(z, RealType(1/tau), pol);
    }

    do {
        last_q_n = q_n;
        q_n = exp(-tau * constants::pi<RealType>() * RealType(n + 0.5)*RealType(n + 0.5));
        delta = q_n * cos(RealType(2*n+1)*z);
        result += delta + delta;
        n++;
    } while (!_jacobi_theta_converged(last_q_n, q_n, eps));

    return result;
}

// Second Jacobi theta function, parameterized by q
// = 2 * SUM q^(n+1/2)^2 * cos((2n+1)z)
template <class RealType, class Policy>
inline RealType
jacobi_theta2_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
                "q must be greater than 0 and less than 1 but got %1%.", q, pol);
    }
    return jacobi_theta2tau_imp(z, RealType (-log(q)/constants::pi<RealType>()), pol, function);
}

// Third Jacobi theta function, minus one (Parameterized by tau - assumed imaginary)
// This function preserves accuracy for small values of q (i.e. |q| < exp(-Pi) = 0.043)
// For larger values of q, the minus one version usually won't help.
// = 2 * SUM exp(i*Pi*Tau*(n)^2) * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta3m1tau_imp(RealType z, RealType tau, const Policy& pol)
{
    BOOST_MATH_STD_USING

    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType q_n = 0, last_q_n, delta, result = 0;
    unsigned n = 1;

    if (tau < 1.0)
        return jacobi_theta3tau(z, tau, pol) - RealType(1);

    do {
        last_q_n = q_n;
        q_n = exp(-tau * constants::pi<RealType>() * RealType(n)*RealType(n));
        delta = q_n * cos(RealType(2*n)*z);
        result += delta + delta;
        n++;
    } while (!_jacobi_theta_converged(last_q_n, q_n, eps));

    return result;
}

// Third Jacobi theta function, parameterized by tau
// = 1 + 2 * SUM exp(i*Pi*Tau*(n)^2) * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta3tau_imp(RealType z, RealType tau, const Policy& pol, const char *function)
{
    BOOST_MATH_STD_USING
    if (tau <= 0.0) {
        return policies::raise_domain_error<RealType>(function,
                "tau must be greater than 0 but got %1%.", tau, pol);
    } else if (tau < 1.0 && abs(z) == 0.0) {
        return jacobi_theta3tau(z, RealType(1/tau), pol) / sqrt(tau);
    } else if (tau < 1.0) { // DLMF 20.7.32
        z = fmod(z, constants::pi<RealType>());
        while (z > constants::half_pi<RealType>()) {
            z -= constants::pi<RealType>();
        }
        while (z < -constants::half_pi<RealType>()) {
            z += constants::pi<RealType>();
        }
        return _IMAGINARY_jacobi_theta3tau(z, RealType(1/tau), pol);
    }
    return RealType(1) + jacobi_theta3m1tau_imp(z, tau, pol);
}

// Third Jacobi theta function, minus one (parameterized by q)
// = 2 * SUM q^n^2 * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta3m1_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
                "q must be greater than 0 and less than 1 but got %1%.", q, pol);
    }
    return jacobi_theta3m1tau_imp(z, RealType (-log(q)/constants::pi<RealType>()), pol);
}

// Third Jacobi theta function (parameterized by q)
// = 1 + 2 * SUM q^n^2 * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta3_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
                "q must be greater than 0 and less than 1 but got %1%.", q, pol);
    }
    return jacobi_theta3tau_imp(z, RealType (-log(q)/constants::pi<RealType>()), pol, function);
}

// Fourth Jacobi theta function, minus one (Parameterized by tau)
// This function preserves accuracy for small values of q (i.e. tau > 1)
// = 2 * SUM (-1)^n exp(i*Pi*Tau*(n)^2) * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta4m1tau_imp(RealType z, RealType tau, const Policy& pol)
{
    BOOST_MATH_STD_USING

    RealType eps = policies::get_epsilon<RealType, Policy>();
    RealType q_n = 0, last_q_n, delta, result = 0;
    unsigned n = 1;

    if (tau < 1.0)
        return jacobi_theta4tau(z, tau, pol) - RealType(1);

    do {
        last_q_n = q_n;
        q_n = exp(-tau * constants::pi<RealType>() * RealType(n)*RealType(n));
        delta = q_n * cos(RealType(2*n)*z);
        if (n%2)
            delta = -delta;

        result += delta + delta;
        n++;
    } while (!_jacobi_theta_converged(last_q_n, q_n, eps));

    return result;
}

// Fourth Jacobi theta function (Parameterized by tau)
// = 1 + 2 * SUM (-1)^n exp(i*Pi*Tau*(n)^2) * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta4tau_imp(RealType z, RealType tau, const Policy& pol, const char *function)
{
    BOOST_MATH_STD_USING
    if (tau <= 0.0) {
        return policies::raise_domain_error<RealType>(function,
                "tau must be greater than 0 but got %1%.", tau, pol);
    } else if (tau < 1.0 && abs(z) == 0.0) {
        return jacobi_theta2tau(z, 1/tau, pol) / sqrt(tau);
    } else if (tau < 1.0) { // DLMF 20.7.33
        z = fmod(z, constants::pi<RealType>());
        while (z > constants::half_pi<RealType>()) {
            z -= constants::pi<RealType>();
        }
        while (z < -constants::half_pi<RealType>()) {
            z += constants::pi<RealType>();
        }
        return _IMAGINARY_jacobi_theta2tau(z, RealType(1/tau), pol);
    }

    return RealType(1) + jacobi_theta4m1tau_imp(z, tau, pol);
}

// Fourth Jacobi theta function, minus one (Parameterized by q)
// This function preserves accuracy for small values of q
// = 2 * SUM q^n^2 * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta4m1_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
                "q must be greater than 0 and less than 1 but got %1%.", q, pol);
    }
    return jacobi_theta4m1tau_imp(z, RealType (-log(q)/constants::pi<RealType>()), pol);
}

// Fourth Jacobi theta function, parameterized by q
// = 1 + 2 * SUM q^n^2 * cos(2nz)
template <class RealType, class Policy>
inline RealType
jacobi_theta4_imp(RealType z, RealType q, const Policy& pol, const char *function) {
    BOOST_MATH_STD_USING
    if (q <= 0.0 || q >= 1.0) {
        return policies::raise_domain_error<RealType>(function,
            "|q| must be greater than zero and less than 1, but got %1%.", q, pol);
    }
    return jacobi_theta4tau_imp(z, RealType(-log(q)/constants::pi<RealType>()), pol, function);
}

// Begin public API

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta1tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta1tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta1tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta1tau(T z, U tau) {
    return jacobi_theta1tau(z, tau, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta1(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta1<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta1_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta1(T z, U q) {
    return jacobi_theta1(z, q, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta2tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta2tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta2tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta2tau(T z, U tau) {
    return jacobi_theta2tau(z, tau, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta2(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta2<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta2_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta2(T z, U q) {
    return jacobi_theta2(z, q, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta3m1tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta3m1tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy()), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1tau(T z, U tau) {
    return jacobi_theta3m1tau(z, tau, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta3tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta3tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3tau(T z, U tau) {
    return jacobi_theta3tau(z, tau, policies::policy<>());
}


template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta3m1<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta3m1_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3m1(T z, U q) {
    return jacobi_theta3m1(z, q, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta3(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta3<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta3_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta3(T z, U q) {
    return jacobi_theta3(z, q, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta4m1tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta4m1tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy()), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1tau(T z, U tau) {
    return jacobi_theta4m1tau(z, tau, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4tau(T z, U tau, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta4tau<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta4tau_imp(static_cast<result_type>(z), static_cast<result_type>(tau),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4tau(T z, U tau) {
    return jacobi_theta4tau(z, tau, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta4m1<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta4m1_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4m1(T z, U q) {
    return jacobi_theta4m1(z, q, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_theta4(T z, U q, const Policy&) {
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T, U>::type result_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_theta4<%1%>(%1%)";

   return policies::checked_narrowing_cast<result_type, Policy>(
           jacobi_theta4_imp(static_cast<result_type>(z), static_cast<result_type>(q),
               forwarding_policy(), function), function);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_theta4(T z, U q) {
    return jacobi_theta4(z, q, policies::policy<>());
}

}}

#endif

/* jacobi_theta.hpp
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
*/