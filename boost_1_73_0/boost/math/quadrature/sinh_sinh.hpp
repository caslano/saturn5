// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * This class performs sinh-sinh quadrature over the entire real line.
 *
 * References:
 *
 * 1) Tanaka, Ken'ichiro, et al. "Function classes for double exponential integration formulas." Numerische Mathematik 111.4 (2009): 631-655.
 */

#ifndef BOOST_MATH_QUADRATURE_SINH_SINH_HPP
#define BOOST_MATH_QUADRATURE_SINH_SINH_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <boost/math/quadrature/detail/sinh_sinh_detail.hpp>

namespace boost{ namespace math{ namespace quadrature {

template<class Real, class Policy = boost::math::policies::policy<> >
class sinh_sinh
{
public:
    sinh_sinh(size_t max_refinements = 9)
        : m_imp(std::make_shared<detail::sinh_sinh_detail<Real, Policy> >(max_refinements)) {}

    template<class F>
    auto integrate(const F f, Real tol = boost::math::tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr)->decltype(std::declval<F>()(std::declval<Real>())) const
    {
        return m_imp->integrate(f, tol, error, L1, levels);
    }

private:
    std::shared_ptr<detail::sinh_sinh_detail<Real, Policy>> m_imp;
};

}}}
#endif

/* sinh_sinh.hpp
CA/h4RjYDI4X/eGlsAWU62wJpc63g/Fk0gnWg51hOuwKz4Bp8B14KpSxNl2/ZesPE+RdclgLng47wsH6TdsQ6IfD4HQ4HAbhWfAneA6Mo28eC5PgONgKni/XBSfCYTBLrgP64NXQD6+HuXApzIP3w3z9Bq0QyuJiDhwKfw1HwblwHLxc7ADnwWL4O3g5vAIugfPh3XCBpAcXwufh9XArXAQ/gYvhfngjlG+vbhL7wSWwDbwF
*/