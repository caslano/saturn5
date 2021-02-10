//  Copyright John Maddock 2006, 2007, 2012, 2014.
//  Copyright Paul A. Bristow 2006, 2007, 2012

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file includes *all* the special functions.
// this may be useful if many are used
// - to avoid including each function individually.

#ifndef BOOST_MATH_SPECIAL_FUNCTIONS_HPP
#define BOOST_MATH_SPECIAL_FUNCTIONS_HPP

#include <boost/math/special_functions/airy.hpp>
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/atanh.hpp>
#include <boost/math/special_functions/bernoulli.hpp>
#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/bessel_prime.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/special_functions/chebyshev.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <boost/math/special_functions/ellint_2.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include <boost/math/special_functions/ellint_d.hpp>
#include <boost/math/special_functions/jacobi_zeta.hpp>
#include <boost/math/special_functions/heuman_lambda.hpp>
#include <boost/math/special_functions/ellint_rc.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rj.hpp>
#include <boost/math/special_functions/ellint_rg.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <boost/math/special_functions/expint.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/hermite.hpp>
#include <boost/math/special_functions/hypot.hpp>
#include <boost/math/special_functions/hypergeometric_1F0.hpp>
#include <boost/math/special_functions/hypergeometric_0F1.hpp>
#include <boost/math/special_functions/hypergeometric_2F0.hpp>
#if !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_CXX11_LAMBDAS) && !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && !defined(BOOST_NO_CXX11_HDR_TUPLE)
#include <boost/math/special_functions/hypergeometric_1F1.hpp>
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST) && !defined(BOOST_NO_CXX11_HDR_CHRONO)
#include <boost/math/special_functions/hypergeometric_pFq.hpp>
#endif
#endif
#include <boost/math/special_functions/jacobi_elliptic.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <boost/math/special_functions/lanczos.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/next.hpp>
#include <boost/math/special_functions/owens_t.hpp>
#include <boost/math/special_functions/polygamma.hpp>
#include <boost/math/special_functions/powm1.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/sinc.hpp>
#include <boost/math/special_functions/sinhc.hpp>
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <boost/math/special_functions/sqrt1pm1.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/pow.hpp>
#include <boost/math/special_functions/next.hpp>
#include <boost/math/special_functions/owens_t.hpp>
#include <boost/math/special_functions/hankel.hpp>
#include <boost/math/special_functions/ulp.hpp>
#include <boost/math/special_functions/relative_difference.hpp>
#include <boost/math/special_functions/lambert_w.hpp>

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_HPP

/* special_functions.hpp
BlmHC2+Jn+AQAEbJle+xlZFrA6KCRTeMCaO+j7yAzqMsVZuSuXSPgWgkAo09jh8sDBiKul2F6wIi+BG5LJM4AEHgB0BahOBmgyTBgsYCWViuREifCgc3hibXd0HCAJQhrf6cDOctcuUwjxnk/dB6Ozm3yPv+bNYfWxdkMiD98QUy+3k4PoXQeyAsJvQuiikD4THx1pHv0YWU+XxXd+s7L3D9ZEFJi4ehbzPKk2h/1dr6bkGXXkCJOe7/ODLtk/PZ6IM9nQ3H1mCru4txI2ESk/A2IFHsBXzZ7oAnAxdzhpECY8yKO8GzKMtdXmMC1azcxh6nYcI3LNm/QlxxXUNY0/WCXiXXACag4ydKozShIcFH/blFFCaot8W4wz0XQJwInpa3pu3BcGSSXYgfddaYlwHjBL4lrkQCwTdOTHZvQ/gwtmqLgsSHzLN57ARsCaHchW8GQSe6IcjHNQht4vMGHldgKvpYWNnpVbWdQ4oF18+i7/No/ASdR+EzafyHeHiyXMJm+FN4ONXKXaEeWIrtG6h6sA9/+UiOyWfg1jpoGUAPewLF2W8ta2q/M2fz4WRsjydjEzcEYB02Yx3aBwppH9EakA4l0qtmTq8kyvct0oTyPaI8gH3dXdF9oMF514GDBVX4PCs0qp1dUVGe
*/