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