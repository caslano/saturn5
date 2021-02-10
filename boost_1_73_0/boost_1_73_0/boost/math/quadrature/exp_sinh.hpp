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
cnZlci1sb2NhbGhvc3QtbGFzdFNBTi1zdi5jc3JVVAUAAbZIJGB1U8muqlgA3PMVb09uPCioLM/AcGRQBDnCjhlEmfQyfX37utddq0oqqVRSVT8/XyBFo/YfrFw9qlIMPeXPVXFuiuv9FX84i1LcEIxh4GDowMlfFdOCtQaFm4JKC3u1OFseHFFh+wi2lqH4dcimwtn5S4wR4pKXDSJmFS6b3ym7dikDxe3lryFTl2BbFM52HlPmzKoHvf9MLIto8xhs1XekySuXYuk3fnwTuHQiTnAy2pCWY2JDR0HIgaQolAv8m9Bp8ZcjaG7vpE8/n+ZsAawO3HENwd3p+/NI9vGgJjqywfJKBlpcrt1jeh7E9LInVU6v4LdCdBu2lMB6FdX1hp+eNnM3AMsTPsKjyUOGorkeLl5myuIy9Vdinz73mObO3WKwmaL1GjyXTImLeKvUYH6sjwfgLv02iCZ86s1ByIuKHKVBeJlVLnweunCxdJ1uxhHXTkAXtQLzPjlmeY+tcVZyQaMs4Pglz9jJNrHhv5Z0Ex+xKYYnvvTb172f6Jt1zRIf5MUKYWX1e+3E3t7cmO/dcqBKQRAnrhVoFbyHTMfCQR/z27vTziZv2DiQtNvGI44kUaNbBirPJ+3SntyNuKnWBFS7zdgq
*/