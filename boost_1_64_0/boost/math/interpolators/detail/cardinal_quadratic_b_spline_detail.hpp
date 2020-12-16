// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_DETAIL_HPP
#include <vector>
#include <cmath>
#include <stdexcept>

namespace boost{ namespace math{ namespace interpolators{ namespace detail{

template <class Real>
Real b2_spline(Real x) {
    using std::abs;
    Real absx = abs(x);
    if (absx < 1/Real(2))
    {
        Real y = absx - 1/Real(2);
        Real z = absx + 1/Real(2);
        return (2-y*y-z*z)/2;
    }
    if (absx < Real(3)/Real(2))
    {
        Real y = absx - Real(3)/Real(2);
        return y*y/2;
    }
    return (Real) 0;
}

template <class Real>
Real b2_spline_prime(Real x) {
    if (x < 0) {
        return -b2_spline_prime(-x);
    }

    if (x < 1/Real(2))
    {
        return -2*x;
    }
    if (x < Real(3)/Real(2))
    {
        return x - Real(3)/Real(2);
    }
    return (Real) 0;
}


template <class Real>
class cardinal_quadratic_b_spline_detail
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n -1] = y(b), step_size = (b - a)/(n -1).

    cardinal_quadratic_b_spline_detail(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
    {
        if (h <= 0) {
            throw std::logic_error("Spacing must be > 0.");
        }
        m_inv_h = 1/h;
        m_t0 = t0;

        if (n < 3) {
            throw std::logic_error("The interpolator requires at least 3 points.");
        }

        using std::isnan;
        Real a;
        if (isnan(left_endpoint_derivative)) {
            // http://web.media.mit.edu/~crtaylor/calculator.html
            a = -3*y[0] + 4*y[1] - y[2];
        }
        else {
            a = 2*h*left_endpoint_derivative;
        }

        Real b;
        if (isnan(right_endpoint_derivative)) {
            b = 3*y[n-1] - 4*y[n-2] + y[n-3];
        }
        else {
            b = 2*h*right_endpoint_derivative;
        }

        m_alpha.resize(n + 2);

        // Begin row reduction:
        std::vector<Real> rhs(n + 2, std::numeric_limits<Real>::quiet_NaN());
        std::vector<Real> super_diagonal(n + 2, std::numeric_limits<Real>::quiet_NaN());

        rhs[0] = -a;
        rhs[rhs.size() - 1] = b;

        super_diagonal[0] = 0;

        for(size_t i = 1; i < rhs.size() - 1; ++i) {
            rhs[i] = 8*y[i - 1];
            super_diagonal[i] = 1;
        }

        // Patch up 5-diagonal problem:
        rhs[1] = (rhs[1] - rhs[0])/6;
        super_diagonal[1] = Real(1)/Real(3);
        // First two rows are now:
        // 1 0 -1 | -2hy0'
        // 0 1 1/3| (8y0+2hy0')/6


        // Start traditional tridiagonal row reduction:
        for (size_t i = 2; i < rhs.size() - 1; ++i) {
            Real diagonal = 6 - super_diagonal[i - 1];
            rhs[i] = (rhs[i] - rhs[i - 1])/diagonal;
            super_diagonal[i] /= diagonal;
        }

        //  1 sd[n-1] 0     | rhs[n-1]
        //  0 1       sd[n] | rhs[n]
        // -1 0       1     | rhs[n+1]

        rhs[n+1] = rhs[n+1] + rhs[n-1];
        Real bottom_subdiagonal = super_diagonal[n-1];

        // We're here:
        //  1 sd[n-1] 0     | rhs[n-1]
        //  0 1       sd[n] | rhs[n]
        //  0 bs      1     | rhs[n+1]

        rhs[n+1] = (rhs[n+1]-bottom_subdiagonal*rhs[n])/(1-bottom_subdiagonal*super_diagonal[n]);

        m_alpha[n+1] = rhs[n+1];
        for (size_t i = n; i > 0; --i) {
            m_alpha[i] = rhs[i] - m_alpha[i+1]*super_diagonal[i];
        }
        m_alpha[0] = m_alpha[2] + rhs[0];
    }

    Real operator()(Real t) const {
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-2)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quadratic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        // Let k, gamma be defined via t = t0 + kh + gamma * h.
        // Now find all j: |k-j+1+gamma|< 3/2, or, in other words
        // j_min = ceil((t-t0)/h - 1/2)
        // j_max = floor(t-t0)/h + 5/2)
        using std::floor;
        using std::ceil;
        Real x = (t-m_t0)*m_inv_h;
        size_t j_min = ceil(x - Real(1)/Real(2));
        size_t j_max = ceil(x + Real(5)/Real(2));
        if (j_max >= m_alpha.size()) {
            j_max = m_alpha.size() - 1;
        }

        Real y = 0;
        x += 1;
        for (size_t j = j_min; j <= j_max; ++j) {
            y += m_alpha[j]*detail::b2_spline(x - j);
        }
        return y;
    }

    Real prime(Real t) const {
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-2)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quadratic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        // Let k, gamma be defined via t = t0 + kh + gamma * h.
        // Now find all j: |k-j+1+gamma|< 3/2, or, in other words
        // j_min = ceil((t-t0)/h - 1/2)
        // j_max = floor(t-t0)/h + 5/2)
        using std::floor;
        using std::ceil;
        Real x = (t-m_t0)*m_inv_h;
        size_t j_min = ceil(x - Real(1)/Real(2));
        size_t j_max = ceil(x + Real(5)/Real(2));
        if (j_max >= m_alpha.size()) {
            j_max = m_alpha.size() - 1;
        }

        Real y = 0;
        x += 1;
        for (size_t j = j_min; j <= j_max; ++j) {
            y += m_alpha[j]*detail::b2_spline_prime(x - j);
        }
        return y*m_inv_h;
    }

    Real t_max() const {
        return m_t0 + (m_alpha.size()-3)/m_inv_h;
    }

private:
    std::vector<Real> m_alpha;
    Real m_inv_h;
    Real m_t0;
};

}}}}
#endif

/* cardinal_quadratic_b_spline_detail.hpp
ULY96+//1fQEAoFAIBAIBAKBQCAQ+hfh/v/2rh8bPv+fqM/Hz5QCAWedNENu0b+jtUTPmP8Wse26nvgk++iaOVi1uQiLRCsNTtUj+yqt164Xc+8DDW3+WbYLNa7EDLzcXK5yaUbfeRIIBAKBQCAQCAQC4R9GLOx44RPXTq3CjkBOxSMFqop8WL2uQXJ78Pp0VZNLlWVvoKoh0ORS1AwfvNomya/IcxwTJmRmZx80JSurSq6Zo1S1TD6oyuVvdLg9AX8GQvCuNnxrls7YILYHfOrLq5ngcN/6aL/qafDM9/jq0vPkBr/HKynYT2hwwkfx2HOqotSRl1tcPCM37yhHQclxRWVHl3C/mxUnfLKvphHPy58p3ge/PgYePHgZuGc86rdQ88/PdDg8AafD2eT0eJ01Xsnh8XlUNoxNS1B5Kqwi1yQFHIFGv7bemOTW8shN0DJu5+nj8HtGQs/WrVvv47/zYhKR9qe9+ZvkpccW5fMdqQay/IS1iJOMY5sOZUCLS8l0BFS0I37wPDbi+B3naHkUoy2OT4hB+KeoR6JeFpvDUetswgY/CEMZUsD78/gz2c5sMEvujcerJPlQHxQ4UZT3eR53LH4PRhsmxo9ivbALBhaM5Gs/7srLi3qYasHDeTlRB3MN+DhGjxj7cKfYWHzMG6e8+fzW7y/pmXfh3kPuWXwChjmu4OGNO2fHVT7iXrusrW12+5M15Yy9ysMPuCznkQ+PeuDbIVt2Xv5j1/ljsY7gEC18/ZUTJ1TOG73mwaH2tx+POy8P4zFDtfC5l64527k+Y8sl30vXF38+qYCxIh5/QdEbqz7bY8gNLw86cMiTQ5ehMpN4/MlzRt7uLrl6afqzTxz4yon3oqEcPPzg03N73v3kp2krhq7++tWR12PvqAt4+PKrastWx3753iM3jt56TeuiGxl7jIdfdk75pgeHLl6SeZ/jhl3nHvoGY5/z8LFtH60cuW6nH58tbX6neXhVI2PDhmnhCRVvX3/C6NKhvr2fPDp34sdzGXuHl/PJd26785ILHfknv3/94Z2b0z5l7Cgef1FJ4spzDjikJK3m+LiY2cfX44Tw8MIS17CPZvWM39mfuu6MSZseC45xVdjtTIW1wlbDOmGjpthYDzhpNzvL1KzIxgbDpiO8daqNHYEw/yE29gBsLSwpx8bGwCpgi2D2Q20sB1YM2wAbP83GFsDaYR2wdbBuGDvSxqoPs7F65HcteCWsB5Y63cbcMBW2ENaqMeL0gNNzbSwTNh3WhrDpM6CLfB4APwdbCxuVZ2P5MD9sCew12MOISyAQCAQCgUAgEPoH1vv/mlsdwNx7r/8f00/+v3b8iGmMRTjsOC47OD5gH619rx4fMl+/P8wGGwfrRP7nXaD5ywscZRV5jiKU3uP0eubD190Ffnb5NN4yfCxgCP66mMcdyf1q1rdfjfhTEpbzuNineDT3m41ydPdRjodN5ahA6+NcwOWOXI4noyjHu2Hl6BH7BkT2x/v2Z09L1cKfKj59yleHTC354Z4RaR0Ju6xgbAUPf++wzYtnLLz6jLqap4omZOXfHb2fPpPn88JpA+sG3rD089lXty+8rf2VWYwN5+Grf/rWNW/ETr7p+Xcc+PnrX27ua/yhb39/Dc/nyo60Des79lpSPfzySZMnf7Gp73GAyP5+3+MD9uFaeGX6hV3uM3oeOaW1aI+1aVt+6nscIPK4R9/jAJHHVfoeJ8G4AR8jMI8LrN7dzl6CrYdthiXF2X83VjAeYSHjBds5VjAd+YSPF5TG2f90zEAfL6hG3IjjBQg3jxkswO+2OBo3IBAIBAKBQCAQGPu7/f+AVI9D3rqJGQji/v8APlevY/eI/v8=
*/