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
Rvq5QCycgUJiOUvqir2wD4tJskx7wDZ/1NgioodwuTaUWzRU2soSiA51nJbgF0eyLLp8Rqdu+MsUWcCIfEXmy2NptcYgKUfcY3vROtCOcd1YeKAVD0jCzQi6UDDksEicio0X47OidABorvaz0qwIWvtOPwPdN4q6ED54VGB7o6jsypf8w/TVkIuYx6cM5gTTQrmsAX7gDwC7VLN0MXRNaXTJfs04vp5qY/Wrp1pj5sfevAJ0a0gepJwVceKh4U2SeBkB47eh59YF+hboIiMXgWPhMy5aoKfVaYexi+JcEo2AvFcwmA3Jni9u7Xy+DZg+ZNMMJbKmrIor/tZlO37hXqdZ8VWUebhjBkXQUY9p196Jo+5d1hRs8d5PU4W0F1Yvfyy64lSTEwCLuIb47yRrcMyJxhHJIfi0zXboWeu69BDVMWLkvjNL74YQLZh0PdQyIiBipUMWWLkL5ko/MFOQz8sY1CupY/RjY2iog2sQLB80E5O4haMLfV1oVNTWYgbZNf8/JADoVVtYvtDtdliqy91yxikHOT2Z0U3xV84Z4IAQZxxSh3KVDh6/4w==
*/