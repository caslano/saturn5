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
q1gU2/MVb4+eINSwpHPpve1CDyW0UL9+MrOes7V0bNmS/ffv7zhRBuYf12P/2C4IWV/8o4nJv8BfyABAHA/AsazGs47I7mluTRiG5cTtgGi/zY9b8PNIPe1pW8MjF3FfS6/1zTLyYPPxDjUoMlrqs1E8CohtOtS1wft2HZuOFhqZ5Du82OmHcOwEl0iL7K2MSex4q/OTaKDDo4DWhuHyM+ErbjGld6wS7sbtief7sm1ZtgMvabOwYBi3PYR5YN/DHiWbikSYUQXPI8+hFoafmsvVLYh0X5nuk4RHcCGiiwRJk7a0ypBJh65gijIVZ/YD7E33oaTonZYL+z5f0FCp+46Ds+PBtYxJ/zptOd/uSl9rjzWU1tK92tFHLsn1eC0Zxru6hNiJEVXbLvUZAzKFT1fPH21tcbFL4LrXkRbWzdvTKxiuXYGko+fuAIF1WI4df2Y7PI8evjYV32z4ujFEUdfjxXCoOfZZX9tv4Ll8q38025vA1BdDDi9E7J+zXp7d/gLTdJI2mNQRk+7bkmsVkoIlkNepA9aCXO8eJjFbe1q5XFv3+1rm3i849BTmsp9SKtrqWkYfkYrtzzofYdR3XKg8hNM6M0HyZyJh3UUoZnaQqUKhs1dpCHtDgbBEik61wv5qUIPFHBsOXaoS
*/