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
47tf49um8T0OG8LdNn0qqtBnmoa/UsNPV31mqD5XqT5c63keOg8DdtX47Od5LND48jW+hapPAZT1/bAxXATbwqUwTe0vgKXwYr3uDJfDLnqt6dH5FM7puU3vf7ve/w5Nz52ano2aHq6t+IqqiO9Gje8mjW+dxvc9jW89bKDXVn2qIr5cjc+n8c3R+OZpfHM1Pq61/HV+AGzlUP59dW1FP1gH9oct5X6htRlHNHycw9qMFRp+pYZfZV/bouGaOoTrqeF6wSawtxVOx61hD4dwdUlXPZgAu8JETWeROU4Lh2m4eCTX/GjX+42ACXAkTIKjYAs4DabAsbAtHAf7wsvgIHUfDK+AQ/Va96fWsVrSoPe17099od63E5RzkWEz2Bl2gemwG+wOM2A32EuvNT90/JR8cMiP1lof2kMv7KD5sc0aUyQNGk7mvWi4NarXOlhf1wwlwu/BxvBm2BR+X/PnFtgK3qr5sxl2gFthZ10L1Bver/m1DQ6BD8BR8EE4Gm6B4/T6JJQzeFTPUtWzCfKQ6jlT9ZwD68K5qmeeltd8XRu1AHaE+ZqfC2FPuEzzswj2g9dq+ZXAK6EfzoCLYA5cDOfDUlii4f26Vgk3rvVcIHNsCrZQve3nAj2iej+q9e0x1fsprQePa/17EjZXey1vHR+CDuXdROt/EkyHKdAMV6ThajmE66z1JB3Gwi62cCurCNdbw12q4fpouCE6BmGt9dLwPc25HBpuGJT5D/oeHwllHETjudvsL4dvaTyJSBmi3Z+Sf8tge7geDoHfgyP03KYx8C6uJ8OHYDF8GJbCx6GcGwB3wB/DF/Tcpxc1/CvwWexfU/s3xF7X2nm0f1L7dPfCbrpnVsD8Vt+778CO8F04AB6GQ+D7cCT8A5wMj8CpsC73mwfj4Q2wAbwbNoTbYEfV90L4FPwj4X4Mj8Hn4QdwP/wLfAMehwfhh/Av8DP4EUz1BtdGtoMNYSfYCH6BezP4JWwBv4Lt4NewPTwFe8B/wT7wGzgAnoYToEE8U6AHXgm9cAGsDW+CHeAmmAbvgQlwO2wCn4TN4B7YHL4FW8DfwY7wT/BC+BeYBCtgG/i56q/n4Gg/lOQh5RJ+Ds7P9X26V5/7F/X9XRv9F8I3uf4RPAjL4SH4DXwX1iLSozABHoOj4HE4Dn4Ic+Bf4Vz4EVwJv4C3wy/hJvgVfBx+DXfCf8Fd8Bu4D56Gb0AP+nwIvfBjWAuehLWt8x20v0D7Z/baz3fQc288sA9Mhf1gb9gfDoKD4SQ4BF4Bh8LZcBj0weGwAE6AW+EkuE2vH9DrR/T6B3q9C14On4dT4SvwCvgmnAbfhVfCI3A6PApnwmNwBvyrXut7RNvb/IY5vEdm6/kLmbABzIJNYDZsB6/ReEi7tqOpQxqPfnuIuVr99THbp/rNT9mEfQ+9pPd7Vd835fBC+BuY7w2uOT3153rGmGbxVa49nYf7ibh4YyNMw23Se/WMIiTuj/W+tfWoew7WOydrUnegc1XrUvfgbl+bWt4s/qzWpx5uFl/jNarb3qt3ztapHifftsFJv4k1lvD3Xv6e93z4utUKdGyaFG/0QaYjS5CtyF7kBJKYHG9kIJOQfGQjshN5HalAmjaPN3oiU5FlyFbkZeQEEtci3khHxiC5yDpkZwt3HaxrXOMa17jGNa5xjWtc45r/D/Ntr/+fw7/MkgW+pedg/X8SY9bFdArGLQp0ixGvzhUIrOVvlWZYc60D5+IKZexb+pakszqrODg3dBSrD/yZ6KTj7Mtx8xh6rXNLrhW/v3Eedy922DfWcS5ZuN+Pmtj2LdV5PDeK+wsOc2vCw8Z3kR26uI3O75K1CxInJteax7pBwmRZc0s=
*/