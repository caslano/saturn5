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
OIhlmlNhwtn1xAQlay6zGn29/AK3Pfl+Rz6X8r6+6OWYrBc5IZC41K0EW5BK6pF/cRyHqAFKCRzBBFp8IISTadyzY6cn6w02EQxOmryYxYRr2IvBDi3t11J+6G1LKhzbSe/8BJqsJIzcZBUAt3YmjZo6IIDEJ/GoNMSPCfY4Je3fToKtHCXO7NmJlygi9I2RCvaxjzX4YEN6pFuLQBPpuDciRNi0jO6wRyyLWUCTEUwX6A1nuLopxHdW1F0Y7iG/hY7FPUpe/PoFDZKbuXxcPNYZdKvL+LQdjCh0aqoeknGJAxALqeI9+906oFfmu87HW1pGgCQh/FzPfnqGZMqyIXEgVSVaMWZZlIdq+e13i4UEzQafqvV6ECbx1CEFTYDibhNB8K78lMstFU8QATZ1t1yVPvIg8Kh+nJ9LzQCnbm02zywhJw5Y9+2o3e4ZObSL7ZkvXiaCEnC9nAXzZ51gMe7IYZVhv/8mqg3hg/srFqvaCiIv4I6tgEh2M5OJNs3SUxjEKRE3s2jws+upoWFyRcxuoMahLylIFqWnreUZB/IVnYJTCYa/Hnf5SQ==
*/