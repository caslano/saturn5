//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_CONDITION_NUMBERS_HPP
#define BOOST_MATH_TOOLS_CONDITION_NUMBERS_HPP
#include <cmath>
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
auto evaluation_condition_number(F const & f, Real const & x)
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