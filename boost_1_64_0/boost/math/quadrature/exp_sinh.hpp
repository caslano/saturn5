// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * This class performs exp-sinh quadrature on half infinite intervals.
 *
 * References:
 *
 * 1) Tanaka, Ken'ichiro, et al. "Function classes for double exponential integration formulas." Numerische Mathematik 111.4 (2009): 631-655.
 */

#ifndef BOOST_MATH_QUADRATURE_EXP_SINH_HPP
#define BOOST_MATH_QUADRATURE_EXP_SINH_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <boost/math/quadrature/detail/exp_sinh_detail.hpp>

namespace boost{ namespace math{ namespace quadrature {

template<class Real, class Policy = policies::policy<> >
class exp_sinh
{
public:
   exp_sinh(size_t max_refinements = 9)
      : m_imp(std::make_shared<detail::exp_sinh_detail<Real, Policy>>(max_refinements)) {}

    template<class F>
    auto integrate(const F& f, Real a, Real b, Real tol = boost::math::tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))  const;
    template<class F>
    auto integrate(const F& f, Real tol = boost::math::tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr)->decltype(std::declval<F>()(std::declval<Real>()))  const;

private:
    std::shared_ptr<detail::exp_sinh_detail<Real, Policy>> m_imp;
};

template<class Real, class Policy>
template<class F>
auto exp_sinh<Real, Policy>::integrate(const F& f, Real a, Real b, Real tolerance, Real* error, Real* L1, std::size_t* levels)->decltype(std::declval<F>()(std::declval<Real>()))  const
{
    typedef decltype(f(a)) K;
    using std::abs;
    using boost::math::constants::half;
    using boost::math::quadrature::detail::exp_sinh_detail;

    static const char* function = "boost::math::quadrature::exp_sinh<%1%>::integrate";

    // Neither limit may be a NaN:
    if((boost::math::isnan)(a) || (boost::math::isnan)(b))
    {
       return static_cast<K>(policies::raise_domain_error(function, "NaN supplied as one limit of integration - sorry I don't know what to do", a, Policy()));
     }
    // Right limit is infinite:
    if ((boost::math::isfinite)(a) && (b >= boost::math::tools::max_value<Real>()))
    {
        // If a = 0, don't use an additional level of indirection:
        if (a == (Real) 0)
        {
            return m_imp->integrate(f, error, L1, function, tolerance, levels);
        }
        const auto u = [&](Real t)->K { return f(t + a); };
        return m_imp->integrate(u, error, L1, function, tolerance, levels);
    }

    if ((boost::math::isfinite)(b) && a <= -boost::math::tools::max_value<Real>())
    {
        const auto u = [&](Real t)->K { return f(b-t);};
        return m_imp->integrate(u, error, L1, function, tolerance, levels);
    }

    // Infinite limits:
    if ((a <= -boost::math::tools::max_value<Real>()) && (b >= boost::math::tools::max_value<Real>()))
    {
        return static_cast<K>(policies::raise_domain_error(function, "Use sinh_sinh quadrature for integration over the whole real line; exp_sinh is for half infinite integrals.", a, Policy()));
    }
    // If we get to here then both ends must necessarily be finite:
    return static_cast<K>(policies::raise_domain_error(function, "Use tanh_sinh quadrature for integration over finite domains; exp_sinh is for half infinite integrals.", a, Policy()));
}

template<class Real, class Policy>
template<class F>
auto exp_sinh<Real, Policy>::integrate(const F& f, Real tolerance, Real* error, Real* L1, std::size_t* levels)->decltype(std::declval<F>()(std::declval<Real>())) const
{
    static const char* function = "boost::math::quadrature::exp_sinh<%1%>::integrate";
    return m_imp->integrate(f, error, L1, function, tolerance, levels);
}


}}}
#endif

/* exp_sinh.hpp
cYsMJyGEEEL+jjZZxuFavTO5fceWTHtHat7Cub/N3w+f2m9yrTb4OYQQQgghhBBCCDHL7/r///p7/YRezwDkNfZ1LFer+V7wO70V31usfUR9IrPhm6SxEOTd7475vFzBk5eMO7WNT+Dc/sMpSvNtVN9C5Nyn1Vd2yjLymXGfbNOf5iPYF/OV3W7H5jYdizesjzlz1bo131m8oRrz2fgONUdmMHLsu9WH0eL2N1LevYUym4Bs5IqNbaw591dQh5NRHWRyg/x+X1KDwnENZZA22ZPd+v6SJHUylkcIIYQQQog12mSZgXv+bLU4u1ybLaOCz5ahk2fnguw+KUvzZs+bHXYCtA8QjuOvDELZpA9g+bMJIYQQQgghhBDyd/xT/7+FGKDGdk9j7Yux2LXvHi0h7mi1Doi9RnPrZC7E61DqM/9p+DeqP+u7RcY7CSGEEEIIIYT0AW2yzGne93WiofT+M05v+/MJIYQQQgghhBBiqf//L/FvrD1W49+HHV8kjH8TQgghhBBCCCGW+UP//5BMxFULp76Md///IT5v+/MJIYQQQgghhBBiqf/fQvx/ko59jrVvafxfhgHP+osXFhfMD3IArNdjKuoxEs/h34jqcSiqiLzcJ3XRnIirqMu1qC65QtnNMyeCEEIIIYQQQohR2mSZ2ryvW3Cy1Vgvt/W4vK3PJYQQQgghhBBCSGu03P9vIcatcf9TWPuQxrg9J1squTnE2q35Ncb+FWvPUH851PeJuwfx/cnqPuQ5Dsf8J4QQQgghhBDSx/yh/1/O+oX/itPb+lxCCCGEEEIIIYS0Rsv9/xZi4L3j/4+iZ9ydnpxT9ecxDk4IIYQQ8p29aw+QeorCs7XVVlu2JK/KyCvpMb02UiyFimpRIWlnd2d2dzQ7M83MbhvJyitUNiXk0eZZhEXIo6zyCNGklEdly6MkrJQeHjnf+s223/EsZv7gHiw+997vnO+ce+f3u/eONWbMmDFjxuJiifJX299//w8W+MKefPc/+938sRzbmDFjxowZM2bMmDFjxowZM/b3bL/e//fjDkD0d/8nTbbuAITdwXyPLzPsrroDEBcfkqzv4hdF7yGEwkF3MOgPZoRi7kOr6O9AsHx4rNoHT64v0xs3/qRatio7PcofzPSE4pCD6vgt/jcnWvyBqgzEnL+txd/M6vDa3t9B4c7LkF/rIPWYUTV07LXobPky2+qwrtqXoDvXE4Infp+7yBPOyCnwZYc9fl/sfYr+bgxHok1M+CZHffL4PGFM1gx3PLSJztV5lh8/TtJ+xN6HaH761rFV2fvkgyfT67nMHc1QODPL646DLqmWTxWWT+/+nk++TJlLozPcvkJP0O/Ld/vCMfcrOq+d1jUuR7VfkCf2unSw+Cst/k9r8LuzC8KUqDiucwFrE7vuXn+CQZ8/5vzRebzT4t9czS8UGZlhaBGPedw2+rmfZKuySuVHxqgCT/ZIFEnsazRaI83q26ps6V5f/L4cT25BsHrqZAZzC2PuT7RGpln+fL/XH+hh7kQaM2bMmLGY25/c/w+FXR5/jU+6fT6fj9W4xowZM2bMmDFjxowZM2bMmLF9s31+/9+Pfe6xVuvp1Wfe7nBWQQ72uWPOvdNqPSF63pwzOugJu+PCHU6wmk+KcofdMlxcuCst7t3VcYfc7pHx4fZaZ/zbqrmD7kxXfLg3WdyvVHMHCsKh+HC7rA7B6nz7A25ffLgrrA6bquPOdccr7uHWWf2Gau4cb0EoLy7c71vca6q5q+6TxIV7sHUWv2ovtz/HFh/NIxZ3pJo72+sPxXZda21xp1vHk97qc8vRv1Z6jGOP8kcs/uQad3jC+X6XO0786dZG9ddR7XF/yO0=
*/