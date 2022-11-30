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
#include <string>
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
    static_assert(!std::is_integral<K>::value,
                  "The return type cannot be integral, it must be either a real or complex floating point type.");
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
        if (a == static_cast<Real>(0))
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
    using std::abs;
    if (abs(tolerance) > 1) {
        std::string msg = std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":" + std::string(function) + ": The tolerance provided is unusually large; did you confuse it with a domain bound?";
        throw std::domain_error(msg);
    }
    return m_imp->integrate(f, error, L1, function, tolerance, levels);
}


}}}
#endif

/* exp_sinh.hpp
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
*/