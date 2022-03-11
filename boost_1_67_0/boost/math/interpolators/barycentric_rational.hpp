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

namespace boost{ namespace math{

template<class Real>
class barycentric_rational
{
public:
    barycentric_rational(const Real* const x, const Real* const y, size_t n, size_t approximation_order = 3);

    barycentric_rational(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order = 3);

    template <class InputIterator1, class InputIterator2>
    barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order = 3, typename boost::disable_if_c<boost::is_integral<InputIterator2>::value>::type* = 0);

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
barycentric_rational<Real>::barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order, typename boost::disable_if_c<boost::is_integral<InputIterator2>::value>::type*)
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


}}
#endif

/* barycentric_rational.hpp
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
*/