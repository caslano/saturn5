//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CONDITION_NUMBERS_HPP
#define BOOST_MATH_TOOLS_CONDITION_NUMBERS_HPP
#include <cmath>
#include <limits>
#include <boost/math/differentiation/finite_difference.hpp>

namespace boost::math::tools {

template<class Real, bool kahan=true>
class summation_condition_number {
public:
    summation_condition_number(Real const x = 0)
    {
        using std::abs;
        m_l1 = abs(x);
        m_sum = x;
        m_c = 0;
    }

    void operator+=(Real const & x)
    {
        using std::abs;
        // No need to Kahan the l1 calc; it's well conditioned:
        m_l1 += abs(x);
        if constexpr(kahan)
        {
            Real y = x - m_c;
            Real t = m_sum + y;
            m_c = (t-m_sum) -y;
            m_sum = t;
        }
        else
        {
            m_sum += x;
        }
    }

    inline void operator-=(Real const & x)
    {
        this->operator+=(-x);
    }

    // Is operator*= relevant? Presumably everything gets rescaled,
    // (m_sum -> k*m_sum, m_l1->k*m_l1, m_c->k*m_c),
    // but is this sensible? More important is it useful?
    // In addition, it might change the condition number.

    [[nodiscard]] Real operator()() const
    {
        using std::abs;
        if (m_sum == Real(0) && m_l1 != Real(0))
        {
            return std::numeric_limits<Real>::infinity();
        }
        return m_l1/abs(m_sum);
    }

    [[nodiscard]] Real sum() const
    {
        // Higham, 1993, "The Accuracy of Floating Point Summation":
        // "In [17] and [18], Kahan describes a variation of compensated summation in which the final sum is also corrected
        // thus s=s+e is appended to the algorithm above)."
        return m_sum + m_c;
    }

    [[nodiscard]] Real l1_norm() const
    {
        return m_l1;
    }

private:
    Real m_l1;
    Real m_sum;
    Real m_c;
};

template<class F, class Real>
Real evaluation_condition_number(F const & f, Real const & x)
{
    using std::abs;
    using std::isnan;
    using std::sqrt;
    using boost::math::differentiation::finite_difference_derivative;

    Real fx = f(x);
    if (isnan(fx))
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }
    bool caught_exception = false;
    Real fp;
    try
    {
        fp = finite_difference_derivative(f, x);
    }
    catch(...)
    {
        caught_exception = true;
    }

    if (isnan(fp) || caught_exception)
    {
        // Check if the right derivative exists:
        fp = finite_difference_derivative<decltype(f), Real, 1>(f, x);
        if (isnan(fp))
        {
            // Check if a left derivative exists:
            const Real eps = (std::numeric_limits<Real>::epsilon)();
            Real h = - 2 * sqrt(eps);
            h = boost::math::differentiation::detail::make_xph_representable(x, h);
            Real yh = f(x + h);
            Real y0 = f(x);
            Real diff = yh - y0;
            fp = diff / h;
            if (isnan(fp))
            {
                return std::numeric_limits<Real>::quiet_NaN();
            }
        }
    }

    if (fx == 0)
    {
        if (x==0 || fp==0)
        {
            return std::numeric_limits<Real>::quiet_NaN();
        }
        return std::numeric_limits<Real>::infinity();
    }

    return abs(x*fp/fx);
}

}
#endif

/* condition_numbers.hpp
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
*/