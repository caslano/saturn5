/*
 * Copyright Nick Thompson, 2020
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef BOOST_MATH_QUADRATURE_WAVELET_TRANSFORMS_HPP
#define BOOST_MATH_QUADRATURE_WAVELET_TRANSFORMS_HPP
#include <boost/math/special_functions/daubechies_wavelet.hpp>
#include <boost/math/quadrature/trapezoidal.hpp>

namespace boost::math::quadrature {

template<class F, typename Real, int p>
class daubechies_wavelet_transform
{
public:
    daubechies_wavelet_transform(F f, int grid_refinements = -1, Real tol = 100*std::numeric_limits<Real>::epsilon(),
    int max_refinements = 12) : f_{f}, psi_(grid_refinements), tol_{tol}, max_refinements_{max_refinements}
    {}

    daubechies_wavelet_transform(F f, boost::math::daubechies_wavelet<Real, p> wavelet, Real tol = 100*std::numeric_limits<Real>::epsilon(),
    int max_refinements = 12) : f_{f}, psi_{wavelet}, tol_{tol}, max_refinements_{max_refinements}
    {}

    auto operator()(Real s, Real t)->decltype(std::declval<F>()(std::declval<Real>())) const
    {
        using std::sqrt;
        using std::abs;
        using boost::math::quadrature::trapezoidal;
        auto g = [&] (Real u) {
            return f_(s*u+t)*psi_(u);
        };
        auto [a,b] = psi_.support();
        return sqrt(abs(s))*trapezoidal(g, a, b, tol_, max_refinements_);
    }

private:
    F f_;
    boost::math::daubechies_wavelet<Real, p> psi_;
    Real tol_;
    int max_refinements_;
};


}
#endif
/* wavelet_transforms.hpp
KcH9oMZKY0+yvcmursrtsN5s9OVisXSGzTFtZKOsr7fdUDWWz/LmHq7myKWteCv2QUDkw6E4WylJbrjzzfT8vHPD2niMtNVoe0iPuWBK3OFEtsbZ9U1GuvXGLT1V/MTNjrAFs7tHlLF5uzHG/aQaj6Y+FN59qQfXZzxvk7VsTfPFfJ0481o5BPN9G0nS+nE6sDe2Js38dNxIFmGPq1NyqWZtzminwzAp5qN8OLef63k8HCarMSe44s0xxrIjK3INwXZUlew3s3PY+WW32hM8/6A8SSHtuvCLZJkZ65Waz6vZcn02zkVYBsOG3W/ul3l0P90843y+c0vjbNb05Plc6IlJTLbNVm/PJ2PRjB5ZMeTo5UxcBHqyeGaP5lJsQoW8jy9RcT7y7jVJdJJyTfomJkE9JDfOioj68X1x98eTzYU9yKtmHF7kUufDqeB7kTW+pbyxi0bhyVzsikdKWjLtLIe7FR+PbwKTbyOCebi8PkwvhVTmxxmvJk+6cOvIFQ57+eZ2m/2GF0d+cJwveLaeP9RcKVt/3Sgrx+ZKyZKI0DV3nEKmJL0cXq0JNx1q8pi52JzBC2S2PjDhcOIq55AJZNprVrpbbPd2qeo6A6E6bNdEr/dU4U9SudYVeanzZhruZW/KjG3plJ459gyD
*/