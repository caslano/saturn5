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

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_CUBIC_B_SPLINE_HPP

#include <boost/math/interpolators/detail/cardinal_cubic_b_spline_detail.hpp>

namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_cubic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // f[0] = f(a), f[length -1] = b, step_size = (b - a)/(length -1).
    template <class BidiIterator>
    cardinal_cubic_b_spline(const BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
                   Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                   Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());
    cardinal_cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
       Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
       Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN());

    cardinal_cubic_b_spline() = default;
    Real operator()(Real x) const;

    Real prime(Real x) const;

    Real double_prime(Real x) const;

private:
    std::shared_ptr<detail::cardinal_cubic_b_spline_imp<Real>> m_imp;
};

template<class Real>
cardinal_cubic_b_spline<Real>::cardinal_cubic_b_spline(const Real* const f, size_t length, Real left_endpoint, Real step_size,
                                     Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cardinal_cubic_b_spline_imp<Real>>(f, f + length, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template <class Real>
template <class BidiIterator>
cardinal_cubic_b_spline<Real>::cardinal_cubic_b_spline(BidiIterator f, BidiIterator end_p, Real left_endpoint, Real step_size,
   Real left_endpoint_derivative, Real right_endpoint_derivative) : m_imp(std::make_shared<detail::cardinal_cubic_b_spline_imp<Real>>(f, end_p, left_endpoint, step_size, left_endpoint_derivative, right_endpoint_derivative))
{
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}

template<class Real>
Real cardinal_cubic_b_spline<Real>::double_prime(Real x) const
{
    return m_imp->double_prime(x);
}


}}}
#endif

/* cardinal_cubic_b_spline.hpp
4JPw1/CnKjfrZ/Dv8Cn4T7XnJ5wPwMaQd9OvMG6237Om+wF9sIWmb2vYBraBvWAm7A3bwXGwvba/HbT8Z8Ei2AkuhJ01nVvCMn2P3Mu5X8PRzHIv5126b3A7TId3w0vrsX+wLBt5QXA9dO8j3MF7WNbWV7ef8Hl+Y/NQmwyt+u8rzD5U+97Cg9nBeu0vnH3o+O4xXH/oi+8z3IHbxN7B/7r9hpPeCzrlqI2onag9qEOo5ENBJxuVdyi6DzH6RJ/oE32iT/SJPtEn+kSf6BN9os//x/P1nP9fUojAsONy/n+Ta+9/sa4ttNO4ZKJGDuN71EeO2W8tv4wv+UXLytfo3v+ydN3jbF9zVfc+7Oq5c/bC2O8uErt13vuPXc9aLntslq1YYt3/7/G7vdhfUlCx2L7/X+2a9dyzs469Vzyynkt6ePYP6h4Uibd9r3+6e/+gxsO937+96Et4q8kKnKF70tP44WHKS/gj+WNLni2VTPPkGe+6v3eiuHnF7Evf8inv/FrknqOxYv5sYB1f/D9hP8q/fRf7rgp0NPvgbhP7MSqTzec88lnofQDnn1vbygVhtJYLs8e2j5gfDkTkt70r7zFmz9z98nuxvo74v5YVsXSxhwux95STxf6Giwmr7qXT8JyID21sZU/DY5dJmQZ7ivkJtrKobu1lsafu710hdu4PzCU373CGsgbSnXXCfznj/ITfn+PEBE535pOelrKL/9aya/aTFYt5hj+VFc7PfOnusmzcmnJu9rAtKV2q+0Iisuo+FrsFrDs1td61pX65/ShYrX50Uj9mfRLS3ysSNjegbkDdgXqA2vQsynb3ltvfcinRoeMo+VJAW1IenqI8zJb83u1rhQ/l7Mjewm5y7/1Re7FXte+Fcq9ySiNhe0PC9qrP7yQ4jVDNUR3IwUGoqU6spgOhD5UV2X1F+Tb+LS2icXbaa/nbKmF+1B+DL+2I332oJH9HZwp5mV6tzC2RMnciv5Ra7W6rEtMO/lzD3Stbw83WDzWTPfLV3GnBiuz3u1PSpT9hbe2k67mG34fiSUg+IJ06+dMkDgPCrXxJBR4laZ0eI26XU2J4d4WXOkvNbS/hvWeYnGMoXzN/5VLWMMx+8lyJ/58CndjPtdDP+gmV6Jos6kPM2sfjMgKxwV7B4mBhXELAF9cwMT7GtKWPNHfLcGSvmdbvruLf3wK3sbra07fSfx91IVXD+cuQGfrdyZMMrecfiF7PQDvq+QWY/MTp4H/H30vjFsnDdG99NmX9WXF/udMDP0XP+PkBefq6X90ddZ5on9g5E5/znAxt+/aIHld0ojOW8GwjPC87vf1aX3lWFZStLDH5E7Z/QuBCh/3VPr8/lTR8Py68d+baUBr61r4U2gcXUrovXvZbbkJdg3L9LWl+ExxCZequd54NbRrWR5n9vTl13C+X5CSmiJ3PZa+bef9U0pN0YD/njPDfHSdN6ZftqN5Io9d3UESvT5XewIjenz41egMieqd+EtHr3S+i94uPjV6fiN62Kj353ST01hu9gV9bH4xdbRvRM+1oWL+10de2Ufdv7XXdxYY9qfPyW662AH2p77QD6Gs7oHsRezqNJR+GBrXP1wxsgtpBHc3+t/T5VNT8ggoqqukrtOzZ+mDceO+XXbHAJTO1n5gnW/tLdVvncZGkn4ZF80Tv8OQ3PXGcpJsJ26IaoDI0jnlVcSzkPIU3jkZ27TSx18oa57xa4twMzhLzJtY4q1tXv7PcpNU8MWt8zDOPXyQ9ZutZkV6aHj01PdZWpcfKpaWrakyPdWKvuzU91h4jPb4r5h2s6bG2lvTYKGZtv5L0KEuqmqv4UJmaHk+60qNy/sA61YEnjxH/Z8W8mTU=
*/