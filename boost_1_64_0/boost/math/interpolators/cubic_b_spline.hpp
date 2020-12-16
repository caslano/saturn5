// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This implements the compactly supported cubic b spline algorithm described in
// Kress, Rainer. "Numerical analysis, volume 181 of Graduate Texts in Mathematics." (1998).
// Splines of compact support are faster to evaluate and are better conditioned than classical cubic splines.

// Let f be the function we are trying to interpolate, and s be the interpolating spline.
// The routine constructs the interpolant in O(N) time, and evaluating s at a point takes constant time.
// The order of accuracy depends on the regularity of the f, however, assuming f is
// four-times continuously differentiable, the error is of O(h^4).
// In addition, we can differentiate the spline and obtain a good interpolant for f'.
// The main restriction of this method is that the samples of f must be evenly spaced.
// Look for barycentric rational interpolation for non-evenly sampled data.
// Properties:
// - s(x_j) = f(x_j)
// - All cubic polynomials interpolated exactly

#ifndef BOOST_MATH_INTERPOLATORS_CUBIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CUBIC_B_SPLINE_HPP

#include <boost/math/interpolators/detail/cubic_b_spline_detail.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/math/interpolators/cardinal_cubic_b_spline.hpp>");

namespace boost{ namespace math{

template <class Real>
class cubic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cubic_b_spline(const BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                   Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                   Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());
    cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
       Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
       Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());

    cubic_b_spline() = default;
    Real operator()(Real x) const;

    Real prime(Real x) const;

    Real double_prime(Real x) const;

private:
    std::shared_ptr<detail::cubic_b_spline_imp<Real>> m_imp;
};

template<class Real>
cubic_b_spline<Real>::cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
                                     Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cubic_b_spline_imp<Real>>(f, f + length, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template <class Real>
template <class BidiIterator>
cubic_b_spline<Real>::cubic_b_spline(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
   Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cubic_b_spline_imp<Real>>(f, end_p, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template<class Real>
Real cubic_b_spline<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real cubic_b_spline<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}

template<class Real>
Real cubic_b_spline<Real>::double_prime(Real x) const
{
    return m_imp->double_prime(x);
}


}}
#endif

/* cubic_b_spline.hpp
wES4G7aEz8LW8Jeavy/ArvDXmu574AD4O3gafBHOhr/X8O3Vev4qvAzug1vhAShjH/hD+DZ8BL4DH4V/hL+Af9L6/lf4OzV/Eb4J/wT/At9U87fV/DDcHVlPhM9pfNNRuyL7ibAXhG1hZ9gO9oDDNB86wpNgFhwDO8EJsIvG8wRYAgdp+R2s7dgQLcdD4XXq3/WwF9wBe8MHYB/4I9gP7oL94ZPwRPgUHAB3q/vD8IhZq5I2VeLTWtoPeURWqQ9eDxPgDdpO3wi7wWdgd3gz7AVvgSPg9+FIeCscB2+DeXArnAnvhHPgNlik/hTDHXA5vAeeA++Fa+FDcCN8GN4IyVPJZ+Iq+fs4fAnugn9Q/16FT8G/wJ/Dz+HTMODD3LSDui4C77K0g/n+cPtZBIfCYpgD58PRcIH2ywthCSyDlXARvBQuhptEX2VY+iLf5hlranp3DOe7PBdpPblC68mVWo5+ou3CRq3Hm+BAeI22e9fCInid1uPNcBG8ES6HN2k9vlnbq63wangHvBbeCW+Ej8OH4C74BHwCPg1/DJ/XcOyBd8GX4Xb4Brwb/h3ugO/Ce+CH8D74b7gTNiSOD8C28EHYHj4Eu8CH4QnwEdgTPgr7w8cgZZ/fdY3nP1QZr5ZxyHPaD/4SZsDnNZ8Pme+g+Knu3LI/52AvCRbCTrAYdoUlsB+cDwfBCjgMnglz4Grt10vheLgIngwXw9PV3hlqbxYs03K/HM6HK+By9XclrITnq7sL1N06uAZeBs+C34XnwhvgpSqr+XL4Q3ie1of10MiO1Xiv0Hi7ZaYu84f7nwqYCythPlwJtR/T7yr0XZZ+bIqm91QYC0+FbeBpsB08HQ6E07U9OAPurYesz7LsoLMDrodumZ87eG8N0/ISvjLZn8/zG7XJ/9w2Mva4yAA9mB381skBTewd/K+TBer8M+h0RE1ClaM2o3ah9qE+RbV+H3mgqDLUetSDqH0o51+4Q41DLURditqGeh71Pqr5B0EnBzUPtRa1BfUoai/qCKr5h0EnG5X3YVS+aPSJPtEn+kSf6BN9os/X8cSgln718v/6FOfPLxcRgMdBBuDdWXyr0b0cB3RTy5OoVP2W1DGD7xJ/NbIl5NcLS5fJ2vZnsiaPjv2so7rzid0lye475/VeZzHPs67fq1vXfpHVZo9iuZjNckbZ99nj1io3y5yNPkfMt+K32YNs9kpdLGabRCKXay+h2Sf0OzEfzmnuBi7zRWafbKWY34GNBu79PtX2C5aLXqHZe/g9cXOZ055Ua8kej1inas/f0ylhdVM9zmh/JnsDyBfXfgHSHz1Nf90vQNhUnpfu8TH7QwalnCdhEr/k/SnzrndbRmTN4IaH3Aibz0R1oczk/c2UGS2xTp3KDO5M3u1PM2XGWkawa8pIQMuIrTxgz14eNM9vEXNkomk5JW9Mfs4Vs0l84/GZcxMzmxJfVCh/ZsO3iNOW5LqfibLlD3E9Kn8Cmj/ufcMzVFbdDl232I7qRXrvcad3ZcmSSEU1Z9DC6Y731nRX9/a6mgZ7HJA9tPa9k3XMhz32fDD1+kMxv5AzcX5r3fxczM9m50zAWjf7SxiHOs0wtdXN98T9ZezwjXHVzULjPlbcZ1O3G5r6GqmPa1O89fHY+/DMGTjJb9L+GPUxYK2PhdX227HfQ565Wt/moPqQ/zsPWPJ/fnmd8n7ngbrXuZ0H6pbX2Ku1zvneqrnO/VjcTnXa11Ln3qlnnTN5UI86J/c3fov2Sl0he6V+M3fAj2//zYbmf5yT9ebusVlvfXv2Sv2v7ok6LN+rdVwCn9T3VNRNKEf3yyTCLrA97ApPhN103b47nApPgKfBk+AZMBsugH3hKtg=
*/