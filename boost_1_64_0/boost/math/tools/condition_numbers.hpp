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
xDZW5yC93Lcgj7SXLEunTiqfnTG2Fn3GXrP/u6rynawzrw7jmjORZ6wFqdejpRGwwvP9zIkAbm8zTF83X9d4feb6PGReXCKv3H4QK/H+Annl22EVpVFaFsBrb0sM+/LhH+l5DrLI5aHPdN72PB/QeENoiLJygypHXrmNIWbSYxpTeWuW135SFW7N9N2F3u65ylOxMvL7XVWbWTGT0reZypOzGtJIIj9kNOPqaczraQQ+jKEKmlDOkjJb9Pb1UpXHc1hR+V7i+y7r3/9BiM3nYdxRcOQw3Zm3zxvUT9+t1anDktrJPCfkAbpnOhcbK/apled09PPTRw0+Lw7c0i1cja+7AKNR1738MvJJfYOiKL08y4XVOZZ29Pwqj1HbZHW2SfOnBq/n13Xg15FyAG31c/F7K808i5zaZ5ieUkiZZsO75cc6bxnUbupGoeSlglr5PYC8lK6TpHXus+6LuoenuvxWRstvw3fU4MvdJAmqyhN8M8A4gM//sf6umDvQk8pAsD1/bumFZkxDOadq6SUsDkOY4bKQbLthkoNDDXQk3sOgZ+n6DT2NP2eeW1c88h7xw9UZjDKR/uISuoIQMsSd2V2wz78Y9e+6FItrcVb9JNC2xJJG1taq/RzfG5C9NQDx7K7oT/zsB7otWF2HQRIH0X97x9IDJ5BMpLnlnp+HPMFq2jyo1Lim8pBgPOcC86VBmOUXScxXWzFibecY8T57HTATZ8G82dXt0M7g12YxEcNO3QMOE8Y8v53dTDSMFWDxD28lDBC78HAqacvbiSY2rirfLqKJDSva8OAZGGjzs7LEWGDT1ufcnlacpV+2496tOMwu2QT9vh0nI0SoMn+6F7CtrQI1pL4L38fGUSYp7Uv7TJy5EySZvx+ANf0vv/u+No52fYR74/52nKlrOqONjZpVUZSGrv9f67n0uvDHSN7bf6D7ooMlOqgTmG+nutAwFM+6IzSOp3sXxZuJe+qwX4IO1JlcPFwo8u4y5WVREKWZ2y4P4nUOkLcfxtMw3BcE4+OTyfj4meD05DhcuDv5UJ+2GWhQW8FT6snCp6Eq7sy3Am1ifLIYjyaTooZanOjz7FJ5aOiKt9PbMC3hbCDxxXjeK+T0Yy4dhP+/P/JLGCUs5D/IyNPCMuVpt5CFjwbcU9dQX+bDTJnEKOiPsOiU8Ycqc8xTuHR0uWam81Bpw4o4SR2X4Qy6Cu7ysIk7y6/q8JKE5qaLG20chhCQmMubLIycGyiGqI2ZM97gt2yxMTAsqWw2nZfNipPxyq2tOCwb4Za3tePmFsT5UeLu2t6Kw6gz9E5xdQfH2X7P5Vvc99SzRBzGVVEG4DUX3salOyPpd09gaT9X1WVdZVHeoJ8KNhzFUhN5mva7w99X+O5wi9hNndxhK8KogeIVd5s87VLxJ92izoMAknvh1FzPuqM/gFipX1o5XlU6MaPoE0+dWllEPtJLHdH4YpaGKUxBcarwgW2XjIMs7bqaPNYq/4k0jdPECXzujc2Zx6TKpvxnBZbeREpIJ6wCDkYdcH2/P6viK1YEbll6aczx3OYyXFpZmEKWnvQbiTzyLOl7ReL6NeMBH6Ekzgtg8pPe1egd5bLBlzhh5nqRw3Xdp6c7y9CsNTl0Jn87VzS+gJVe7oR1Fip8Uqnd9L/6UYO35n48gzDlzrG5oZqdXfLV83W9bjKn9pKoqvn+tddZCFU/bp2yOROoPF4NeS3KJMr+a908XLvoPPS0ddo9SFimgRd6+Ezf7KAfK/WM5f2JukaVzE8d162qmLbA5BGUNW/qwyfUN/UkdmPIOby9HRU40mE+oq1/Xt92o/YCQJLegEigq+j6ku0G0/gdVuSxV3ixK/i5uqM=
*/