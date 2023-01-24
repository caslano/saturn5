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
K29ZE6/JBi+XRIx87LdOx8EUUbQblgDsNfEHBN6NZWjnSnPv962ZLZ3HmYjTE3jH2iKNRRVej1YiyUUyJAi0w69iGKiu8Ur41qf/fWTdLvlOhm1Z34LRUQrgNPzHejAEtSNo44hU1LUxZ3Vhw3nfdWOAu4GZ0dusGqlvqeNDRxRdwuoUf1/chf7kxTMhvqdjQDzPvd8LyXcO/RPHV9+ltknBM+BZQ6Q22og17TG337nOPhx+bJ8ctJ7QPqcBpLkokNy6qTShhYxhd9Q7HFucmyYeLMdqH/rGTdmJkgSB35mY/AyKzYXT2BlQAp0DBVUgTt0aQKaUyP0rBDu0iesU1yV6CzsM4ElAbuQuA/cnoliYuUZDx5p6+L643uFzOi69rCuOUBciSTrnflFJyYLVuHjnt7NVvp4xpw4QvjL8+LeK4Qvw20tlCUpXZoK1WUntSKu5f8NQrUmCd4ewcUdCGYpw4pzg0UjHSD4qWCiONiJivhgXjHnM04gsEB7kMPzsj3jiTeQMHMBuotQFYNq4UfaJjKGyQjhNyGnX5ECH9F769wVmc01Nl8T+MY9mQPK0XqQjOGrOcReUBsz8SgEuvacGnfU1wU3hE0G7dghgjrQXturCmpu9ztuGRNZOcUY1ZUOIkYUVdyadd+ZH9177dPWfaXTVR0pZBEs+EkwNvi0lsxo9+nVpef5HOAE8eFbAloGP4G8stwQny3yH
*/