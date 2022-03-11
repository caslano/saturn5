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
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
*/