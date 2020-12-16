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
TyDjtozYOJoc6vluI+LMGGIMpTN85xfWWkAY8s3W+qt2fNBS1Xn+0PaEdN6VsmpVzq7Ow4lAzb0+whh7KVNybG60cJh/FtfzTRYdepb5/7WF6bzGsazf2dpGFy+MogzEbGOMFJD8gvBOvx3oa8SsG9sB9AeIWXd0p4Wz1rt9T0OMud4Z+9yWXUNwhs/RjwXuAe8KP9gN2AfYi28+wrj2OwXaAms2Y16RpmkCxrL91Yu9vmkzdk3FvjqtqwgmfuGszoMtGoI5X7lWrkiR7Qv/P1g0Z3oIZezr1qkydMOsmyT1wPbTjGvxNbXcysnTJKmSriNaKSNkijwukgf1YN98DugUDgoeDULaMtJ1wN/LdYzlJ3V5nYXR/KT+ZtPll34x5WEmOhw7H50edNz0srTlU+ZlPaLjxMdgGNUH+zPhZL/K3UChj2826DCrHsV6MI4c0iWnLk+PcR/dquE0eXpKfYe2EU7aHJryjGzX6SgP27PuIDqKMrs4P7NK9P5OoksRkEznttGn6fR5Jd/CjyUNEv8IoZQ6P7oLfpd6BO27Ef0bu4Eu3u11Ot83HwH6A+wr/xa4B8gt+4+n2zic2hz/S7UVL50KrKiizE/ReFM4sNv5+o/0OmrMhAKmTRpHTs8IsORSTPuDqg1/14+FyUTtSB0QXFARzvEbpw6o9ihpWQqrjMpBQ1XdfvzMyxX5jye+iKqQRsJO1cg5ocpwMksSt3DDEG3i35QEpsxTKj530iKK88zNGyGIo8EHP9XypSa+79c5GF1SyLWejp/T5MlFXCDX83DtgZ3C7PMVDV9mQS1CTclMpbC5nVtGPK/Fz9LshzwwsYm7qfhGMH/fLdEcb+2ZiuxjZSH8paOBLAOgGp9UlcPPnDL3om7iPXS+zjc3dpFaeYVTe0GQJ/EQP+iVleFu0MJtu7NuP+YAuyrHEHWnSNMlfZZ/AGv4DZ3GfsbI+9HnEh3YYE1AG+Tr/Duy8Nw/DOv1USrTjuN9W6PrcbzH1ms0uc7vbXTdRJMaJPp9bAP9rtkHPCl/5/WVJqXqm7BRxYCeVh6CeI3+l0bnIjAMJ8lwYxPhoDn8+47N9Lt2dlvk33tcL/Nd2wJ0Wj+VXPNb1d/Fksm0kR1Mw/6j8g7vBBqtt8zzb/rdLu/0bqRxebwHPtLQVucH5P5Z9W0qeHpDv4RjhzTbdD47vAcwa+rVeJ859EyBlWXNnlXm9v3VjhrjJPPdOkgCZ+XiWVr2aN0AXZYR3zGts9J1Zpocgz3d5+5dB/QYbDEY9qU+Lkwihiylq2F5VlSe8TTJ0yztwlHufbwykTyXDWzteZlXUPFse4tzcfQ5Aq/VLjpWnsd+B3M5tuk0OZu14JaGkeyU4+9nGo1YaT6Nwbx9hV6+dZa7a2O0s1y+3qJrPu9PaHQ5z4k2tUGlyaqJ9g+NJqsEGt/HmCaqY9odQeM5A3TlvXIj0VR5iXfLZqDj/LB4iabx0ni+s0XQV2FQ4HjG3xe3we90v3CnIOaZ96YpVRvAY60z3VH9UlI/DF24N8CetmydU/6wX88zlfpumYahmChw9RPnRn3s31fxhZOUcC3JgngwOOs3eeA/YO2H/96v719FJvwm0+Jh98NmvC/K8pQajbyVHzXpPGQHeSnB/yh8cw0LVx2HE8AHvx2F36B3xc81cGCIakq9IfnGANMAOp0B38lWPk75sRcwTyc+Akje17fyyvFLdf7lOR21JbK8v8JvxARxa2GkyN9fq9Yjo3zwuPu3+OZqScZ7zvV1Bt04tz+1voU+quT/3mDQ6Tlw5oIqx52NBs6IF3Jqk0E33vO/RnT+tupdbnGLTWc5GHdtG+GkoIONYfosGJr1V9U73XY=
*/