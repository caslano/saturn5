/*
 * Copyright Nick Thompson, 2019
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_STATISTICS_ANDERSON_DARLING_HPP
#define BOOST_MATH_STATISTICS_ANDERSON_DARLING_HPP

#include <cmath>
#include <algorithm>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/math/special_functions/erf.hpp>

namespace boost { namespace math { namespace statistics {

template<class RandomAccessContainer>
auto anderson_darling_normality_statistic(RandomAccessContainer const & v,
                                          typename RandomAccessContainer::value_type mu = std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN(),
                                          typename RandomAccessContainer::value_type sd = std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN())
{
    using Real = typename RandomAccessContainer::value_type;
    using std::log;
    using std::sqrt;
    using boost::math::erfc;

    if (std::isnan(mu)) {
        mu = boost::math::statistics::mean(v);
    }
    if (std::isnan(sd)) {
        sd = sqrt(boost::math::statistics::sample_variance(v));
    }

    typedef boost::math::policies::policy<
          boost::math::policies::promote_float<false>,
          boost::math::policies::promote_double<false> >
          no_promote_policy;

    // This is where Knuth's literate programming could really come in handy!
    // I need some LaTeX. The idea is that before any observation, the ecdf is identically zero.
    // So we need to compute:
    // \int_{-\infty}^{v_0} \frac{F(x)F'(x)}{1- F(x)} \, \mathrm{d}x, where F(x) := \frac{1}{2}[1+\erf(\frac{x-\mu}{\sigma \sqrt{2}})]
    // Astonishingly, there is an analytic evaluation to this integral, as you can validate with the following Mathematica command:
    // Integrate[(1/2 (1 + Erf[(x - mu)/Sqrt[2*sigma^2]])*Exp[-(x - mu)^2/(2*sigma^2)]*1/Sqrt[2*\[Pi]*sigma^2])/(1 - 1/2 (1 + Erf[(x - mu)/Sqrt[2*sigma^2]])),
    // {x, -Infinity, x0}, Assumptions -> {x0 \[Element] Reals && mu \[Element] Reals && sigma > 0}]
    // This gives (for s = x-mu/sqrt(2sigma^2))
    // -1/2 + erf(s) + log(2/(1+erf(s)))


    Real inv_var_scale = 1/(sd*sqrt(Real(2)));
    Real s0 = (v[0] - mu)*inv_var_scale;
    Real erfcs0 = erfc(s0, no_promote_policy());
    // Note that if erfcs0 == 0, then left_tail = inf (numerically), and hence the entire integral is numerically infinite:
    if (erfcs0 <= 0) {
        return std::numeric_limits<Real>::infinity();
    }

    // Note that we're going to add erfcs0/2 when we compute the integral over [x_0, x_1], so drop it here:
    Real left_tail = -1 + log(Real(2));


    // For the right tail, the ecdf is identically 1.
    // Hence we need the integral:
    // \int_{v_{n-1}}^{\infty} \frac{(1-F(x))F'(x)}{F(x)} \, \mathrm{d}x
    // This also has an analytic evaluation! It can be found via the following Mathematica command:
    // Integrate[(E^(-(z^2/2)) *(1 - 1/2 (1 + Erf[z/Sqrt[2]])))/(Sqrt[2 \[Pi]] (1/2 (1 + Erf[z/Sqrt[2]]))),
    // {z, zn, \[Infinity]}, Assumptions -> {zn \[Element] Reals && mu \[Element] Reals}]
    // This gives (for sf = xf-mu/sqrt(2sigma^2))
    // -1/2 + erf(sf)/2 + 2log(2/(1+erf(sf)))

    Real sf = (v[v.size()-1] - mu)*inv_var_scale;
    //Real erfcsf = erfc<Real>(sf, no_promote_policy());
    // This is the actual value of the tail integral. However, the -erfcsf/2 cancels from the integral over [v_{n-2}, v_{n-1}]:
    //Real right_tail = -erfcsf/2 + log(Real(2)) - log(2-erfcsf);

    // Use erfc(-x) = 2 - erfc(x)
    Real erfcmsf = erfc<Real>(-sf, no_promote_policy());
    // Again if this is precisely zero then the integral is numerically infinite:
    if (erfcmsf == 0) {
        return std::numeric_limits<Real>::infinity();
    }
    Real right_tail = log(2/erfcmsf);

    // Now we need each integral:
    // \int_{v_i}^{v_{i+1}} \frac{(i+1/n - F(x))^2F'(x)}{F(x)(1-F(x))}  \, \mathrm{d}x
    // Again we get an analytical evaluation via the following Mathematica command:
    // Integrate[((E^(-(z^2/2))/Sqrt[2 \[Pi]])*(k1 - F[z])^2)/(F[z]*(1 - F[z])),
    // {z, z1, z2}, Assumptions -> {z1 \[Element] Reals && z2 \[Element] Reals &&k1 \[Element] Reals}] // FullSimplify

    Real integrals = 0;
    int64_t N = v.size();
    for (int64_t i = 0; i < N - 1; ++i) {
        if (v[i] > v[i+1]) {
            throw std::domain_error("Input data must be sorted in increasing order v[0] <= v[1] <= . . .  <= v[n-1]");
        }

        Real k = (i+1)/Real(N);
        Real s1 = (v[i+1]-mu)*inv_var_scale;
        Real erfcs1 = erfc<Real>(s1, no_promote_policy());
        Real term = k*(k*log(erfcs0*(-2 + erfcs1)/(erfcs1*(-2 + erfcs0))) + 2*log(erfcs1/erfcs0));

        integrals += term;
        s0 = s1;
        erfcs0 = erfcs1;
    }
    integrals -= log(erfcs0);
    return v.size()*(left_tail + right_tail + integrals);
}

}}}
#endif

/* anderson_darling.hpp
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
*/