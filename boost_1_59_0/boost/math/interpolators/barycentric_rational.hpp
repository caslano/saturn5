/*
 *  Copyright Nick Thompson, 2017
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Given N samples (t_i, y_i) which are irregularly spaced, this routine constructs an
 *  interpolant s which is constructed in O(N) time, occupies O(N) space, and can be evaluated in O(N) time.
 *  The interpolation is stable, unless one point is incredibly close to another, and the next point is incredibly far.
 *  The measure of this stability is the "local mesh ratio", which can be queried from the routine.
 *  Pictorially, the following t_i spacing is bad (has a high local mesh ratio)
 *  ||             |      | |                           |
 *  and this t_i spacing is good (has a low local mesh ratio)
 *  |   |      |    |     |    |        |    |  |    |
 *
 *
 *  If f is C^{d+2}, then the interpolant is O(h^(d+1)) accurate, where d is the interpolation order.
 *  A disadvantage of this interpolant is that it does not reproduce rational functions; for example, 1/(1+x^2) is not interpolated exactly.
 *
 *  References:
 *  Floater, Michael S., and Kai Hormann. "Barycentric rational interpolation with no poles and high rates of approximation."
*      Numerische Mathematik 107.2 (2007): 315-331.
 *  Press, William H., et al. "Numerical recipes third edition: the art of scientific computing." Cambridge University Press 32 (2007): 10013-2473.
 */

#ifndef BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_HPP
#define BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_HPP

#include <memory>
#include <boost/math/interpolators/detail/barycentric_rational_detail.hpp>

namespace boost{ namespace math{ namespace interpolators{

template<class Real>
class barycentric_rational
{
public:
    barycentric_rational(const Real* const x, const Real* const y, size_t n, size_t approximation_order = 3);

    barycentric_rational(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order = 3);

    template <class InputIterator1, class InputIterator2>
    barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order = 3, typename std::enable_if<!std::is_integral<InputIterator2>::value>::type* = nullptr);

    Real operator()(Real x) const;

    Real prime(Real x) const;

    std::vector<Real>&& return_x()
    {
        return m_imp->return_x();
    }

    std::vector<Real>&& return_y()
    {
        return m_imp->return_y();
    }

private:
    std::shared_ptr<detail::barycentric_rational_imp<Real>> m_imp;
};

template <class Real>
barycentric_rational<Real>::barycentric_rational(const Real* const x, const Real* const y, size_t n, size_t approximation_order):
 m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(x, x + n, y, approximation_order))
{
    return;
}

template <class Real>
barycentric_rational<Real>::barycentric_rational(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order):
 m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(std::move(x), std::move(y), approximation_order))
{
    return;
}


template <class Real>
template <class InputIterator1, class InputIterator2>
barycentric_rational<Real>::barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order, typename std::enable_if<!std::is_integral<InputIterator2>::value>::type*)
 : m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(start_x, end_x, start_y, approximation_order))
{
}

template<class Real>
Real barycentric_rational<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real barycentric_rational<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}


}}}
#endif

/* barycentric_rational.hpp
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
*/