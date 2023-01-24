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
4Q574OTyTKC4vswCzGKqpVcZ0hcVwPaI01WaBQBh6btV+sMBT1ulHi8eFhT6jnVLeS79x+CgVKX4b/rxpnQhHtomRw/c/k7x/bnNtw+4ad6ZJI+ul44fn/jIv07oM1o8Q2vsLHszX4jAqFmCeZjCbF+PBc+ulClqTmsJnXkzZGrq/iw7uTWS0kApHWVi9ddi9g+qe+tBele83QqfaRcn3HZ9sP5x3fqcwIp/eoBxB2Ufv9ddzudBs7Gf+TgYWRxU30/EHif8KYd+Xv+aWDG5PgmC1OleLP4UmWRkY3k27I2D8tXzzYoHPp1NmWPaKYDfy4zNj7gwdS6PdD2zzCyjEerbpYKRG9f/5Qy8go1/AUbDSG6R54sj4RLbXtrF/I8NTxRk2/MuneSsdZLCRv1OKMElOockCrCBzwn5XLniYndkhy6QiZy85PTlYvHePZuUMirXKUCbEfulfAmPc6vbOez3PocuIKWbZ5UY+4B8IQkWY8buSYIRGdtE0zCeZSINnCgRRp9Rn9nt9XSRAc4js44hZpyERqAlHM9CY7aGyveS7YrVLofTsHDEoFSYZfSFpeHIurN8xrcR9smWfv+6NPmwCjXw7Wx87Dsubu8wdt3TUy+VEnzVzBHaphJdswdiKUGXvgsJUxk+AiZubcidK9FdihuF0V1q0106nxMxp3i4ffvNtLz7kwwUUwbwo8aH+kQsZ3gOOhwySXam
*/