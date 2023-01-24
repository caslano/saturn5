// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * References:
 * Ooura, Takuya, and Masatake Mori. "A robust double exponential formula for Fourier-type integrals." Journal of computational and applied mathematics 112.1-2 (1999): 229-241.
 * http://www.kurims.kyoto-u.ac.jp/~ooura/intde.html
 */
#ifndef BOOST_MATH_QUADRATURE_OOURA_FOURIER_INTEGRALS_HPP
#define BOOST_MATH_QUADRATURE_OOURA_FOURIER_INTEGRALS_HPP
#include <memory>
#include <boost/math/quadrature/detail/ooura_fourier_integrals_detail.hpp>

namespace boost { namespace math { namespace quadrature {

template<class Real>
class ooura_fourier_sin {
public:
    ooura_fourier_sin(const Real relative_error_tolerance = tools::root_epsilon<Real>(), size_t levels = sizeof(Real)) : impl_(std::make_shared<detail::ooura_fourier_sin_detail<Real>>(relative_error_tolerance, levels))
    {}

    template<class F>
    std::pair<Real, Real> integrate(F const & f, Real omega) {
        return impl_->integrate(f, omega);
    }

    // These are just for debugging/unit tests:
    std::vector<std::vector<Real>> const & big_nodes() const {
        return impl_->big_nodes();
    }

    std::vector<std::vector<Real>> const & weights_for_big_nodes() const {
        return impl_->weights_for_big_nodes();
    }

    std::vector<std::vector<Real>> const & little_nodes() const {
        return impl_->little_nodes();
    }

    std::vector<std::vector<Real>> const & weights_for_little_nodes() const {
        return impl_->weights_for_little_nodes();
    }

private:
    std::shared_ptr<detail::ooura_fourier_sin_detail<Real>> impl_;
};


template<class Real>
class ooura_fourier_cos {
public:
    ooura_fourier_cos(const Real relative_error_tolerance = tools::root_epsilon<Real>(), size_t levels = sizeof(Real)) : impl_(std::make_shared<detail::ooura_fourier_cos_detail<Real>>(relative_error_tolerance, levels))
    {}

    template<class F>
    std::pair<Real, Real> integrate(F const & f, Real omega) {
        return impl_->integrate(f, omega);
    }
private:
    std::shared_ptr<detail::ooura_fourier_cos_detail<Real>> impl_;
};


}}}
#endif

/* ooura_fourier_integrals.hpp
yT35RoxS3MMRut1P1ZabrKw8sdYGgxrzP20+wwYEMCorcjW5BCxoECtxwigGVMiU+abEI1wTw7WhbS698xSyssPJhWHQH7ATp0PvCqYenzKWKLzyZi6ZHwoOcgB+U2qbplSm1WxX6ALnAdtEh7Q+b+1QgfdPt19CA/cfHV23Z/HK3VWD+qQsTySU5iKrnKV3V3kh7hYIhqOuJqNUlnOY8hsbj1XRoNhpS3AQPf5G1F5UVlNMFHS0fWXwV9eLLJoM0flCq7Lzz1SwnRbn+jqqDM3KOCWw27h3x18UC9jgQbg6/4KcOZKpKEBZUoUD4FLHWf7+HbchB/ZNoHgwUASgpegDfCawGqWUC5QNTDRJHNKAFfFJCnLc0fpAam8QZQI7wEBWT6gqdzwAPwoXiL1zIfibJuZvuGUA41NU5mNR2mwWnuU79Igsv4SNefk1Sr3NJ4oCH4h9CIDGRAbI1/tTMcJ0Apupznx6p002xeHxykrlYsrPHHqJTg7FPGfaB/SuBFP/f/HSayOcHiVIvToi3u0hmnN02A6QChS8Ha3+BnzmRE4EfBYDf9YpIfZ7L8sX6qfnPNSRoq9HQFzJQ7nKZ2dCJ+Rps7cIxn3uiI6sX0PrbRevQ4yCDktn8Ds9Pw2w1ope93M5Hbs1MhUR3ERqm7y1GfVdc/YM7u223Ay69KooQCJK1GtGSusbc1dgf7tL0tsNhN+0IU+niad8
*/