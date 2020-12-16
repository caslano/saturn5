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
T/cW88mzaZLclq9cE1Mai3bk+dIZc1/m+N415svIY7Mac7TneuQ0FpDfVMlrzOXjNVPQmFPOGBaD30VsV8qYp5Sc/4Od7HFXNuavyVp5kFtftqtlLD6K860PJro0AVvIsTSHD9mfbG0sJvp1QL6SRxfkIdfOnvCRmFk/6CJjB0FnYcPBjrEuY+DjGffQBGPe+1yjT+HDxzFPR91q83xB2Mk5vAXQQJ4Hv0S+V1n7ZZhPrrvfIeYXvGZ+xHzidw167Q7n+xt0Hse1XG8s8iOP3WIs3IPz3YE8HjmI7UHMEt9BxHyL/R6FXW72cQp9NY7X+XnELNrH0KflWOfriHkAr607iE/O3dw3Fnyf5/sX7C3333PoIt/1vkEf/MVaJXZZzM/l/J+x8CXON60xx9esSwZjEflbm8VYUO7vc7hwRj0DsTzG4rI+3jfm/4PXflFj7hSssxtjD3K+5RBLatn/MxbaI/t/8NGKda5pLDaPY64HXbqw9o2Rm1xPP4bfbhxLK2NOeRfd3lhA9jY7Y75t7LeHsfTy7r0vtO/LPgZCl7Cc/4PfnHL+D/nK/nMAusg5rSnGfKU5vs+hgTxbzTbmGsjraL4x7wnWeTHim8398jVikXvR/2GsvDtegX6Ra9hq6NeJNfgV2ss5qHXQVN4Tb0a/hHmdb4cGsh+7Gxq04PkOII+bnEcUPuRe6iS0es3sHHJbKt//wk7OGF5DvnJO5jZyK8S1/AexPOG1/wi5zWDtn2HsDjn/B7/5mCXKY/WQ8wzJweRdURpjHnmOSg8m9/eZjcV68XUju7FolHVxGXPN5lgKYL61rH0RsNVy/s+YuzJfI8oai8/k+SoZC+fl+n6IWDKzXQ3EMpz7ua4xnzx/NEIs53lsM9gVkO9/YfeMY24HlpXHdkIeN7jm3Y15h/Da74P4KnAefmMhyWMo7Hqw9qPA5H5oPMbu4bpNRt3GsY/PoNVg2f+DXWrug3nGnIX4GrYIucn9wVeYr7P8/gd0KZWc2A+o5SH2sQpjJ7Kmv0D75LL/h5p/xrltgp389mjEmEPYLmi1TM7/IbdezI4gvkncGyegS1rW/ux/fcX9fBGx5GOtrmKsV87/IY/FXN+/sS7PcCwPkccUHvsUmnbnWF7B7y72m5DX7DpyPZIZ88vzUWpj4XOcr9OYV36rIpOxgJzNe89YRM4K5TbmXMq1zG/MdYLzLWzMLe91SxgLyV5kGcQiZzUqGgvuZh9VwbqxftURXxPZ/8N8UY6loTH9Dcam0ErO+Lcw5mjM8bWFndTShzzkXUw36Cd7Qb2hvewtDTAWvcc6DzEWC7GPkbC7zLmNQyz3uTcmQeehXKNpiKUd+52J+Qrz2pprzFee2UL4yMRjl0L7A+z3G2PxK3L+D/oFeL6f4FfOBIah37dc39/B7sv+H8bKWZJt8FFMvv8Fk72MfehT/f//oFVjju84NOjKfXUG9difmNgF2EnNr4CdTSB2E+vyXdbvHjT9nWv+ALnJ/u4TMDnr/BK1lG89HPlsvdVhDZIac37H8aWCnZyle8eYZyHbZTTmTinf/xrzyn1YLmMxOR+Rz1i8uOz/GQvq//8HO3n/VhqxTGO/FYyF5BudKpgvA2taDXY7OZbaxgJS3wbQ4E+28yK3lqz9J/Dh5/jaGPPJd70dkUcbjq8r5nvNY3uhHnLWoD/YHa7HYGgvfy9HGIu+Zf3Gwq4U+50IloH9TkV8VdluBuxkr2oO7IayBl+gHnK2Ygliec41ChkLl2K75dBvNbOVqEdTzuNn+JWzEGtRyydy/s9YZCzrshX69eQ+2Ak2kO32GnN0kv//Dz68PPYYcjvGvXEaNZdv+/7CWHlmv4x87/M=
*/