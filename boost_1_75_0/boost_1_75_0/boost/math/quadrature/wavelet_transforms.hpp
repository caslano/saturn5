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
tY550Pmgk9lMsVc7lzRkkU96PCM0SYF90ar8tU/7euX0L5jfKnUAy2ydv0+OTMZmXaHh8V0jgO+T9am3z7Z648ZYBOEPZQWKkQNFKavUaOGmra9alVpaOlaoTH+RRVYs3ba8jjtopCB+U4vZDFIUH7z7cCG1p+eMUuN+n+vCmzhkubeOyC61Eg1vXnycbSzyVwTSLe7E6MZNXUYrXqj+mP7LxgVu3AK3Xz74X9UEtSNlznLwLUP6E9r95x72T0+9jE/p7xIg7d9D7LncJ7YV8/W5VNrfVmLR02Xu+JGlD0J73uMGvyviIh7jUz2keAqEkff845Ss8qrXklA2lvZceOK1fhZVmfVlNYj9Jvtjp8f2rE+mnw497bTb5m6F7D+HjHOUV7IPAdxKlYRaci2+eF8qT/a+MF+o+YJ+z+ABfmXYTDik4VLXa2SLrOOap0TYveER1vpWSZKW8spE/4jNOEIVbwgR3LRbgp8/bn3llwBDt1O9xg0scm3KMYcOjsLRtw0REo+1zK1U1Dhaj7kfUxFpzZkb7JPA2CtSbVMzaj+8uL6uesyXp0Kj5e2ocnDarUFhNlL22LKFg89qmM5sJOexZSY4rmUydTiPBdQB9PmELSiyQsgdBmf6DgMs24G1KRMm815PwBOZLU+ZNDBdHFEgJtm0Cxn/DjOkv3U53hTptSA67odQS9tqk5JWQZXjpyk2zFLUuANnT7jT
*/