/*
 *  Copyright Nick Thompson, 2017
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_DETAIL_HPP

#include <vector>
#include <utility> // for std::move
#include <algorithm> // for std::is_sorted
#include <string>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/tools/assert.hpp>

namespace boost{ namespace math{ namespace interpolators { namespace detail{

template<class Real>
class barycentric_rational_imp
{
public:
    template <class InputIterator1, class InputIterator2>
    barycentric_rational_imp(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order = 3);

    barycentric_rational_imp(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order = 3);

    Real operator()(Real x) const;

    Real prime(Real x) const;

    // The barycentric weights are not really that interesting; except to the unit tests!
    Real weight(size_t i) const { return m_w[i]; }

    std::vector<Real>&& return_x()
    {
        return std::move(m_x);
    }

    std::vector<Real>&& return_y()
    {
        return std::move(m_y);
    }

private:

    void calculate_weights(size_t approximation_order);

    std::vector<Real> m_x;
    std::vector<Real> m_y;
    std::vector<Real> m_w;
};

template <class Real>
template <class InputIterator1, class InputIterator2>
barycentric_rational_imp<Real>::barycentric_rational_imp(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order)
{
    std::ptrdiff_t n = std::distance(start_x, end_x);

    if (approximation_order >= (std::size_t)n)
    {
        throw std::domain_error("Approximation order must be < data length.");
    }

    // Big sad memcpy.
    m_x.resize(n);
    m_y.resize(n);
    for(unsigned i = 0; start_x != end_x; ++start_x, ++start_y, ++i)
    {
        // But if we're going to do a memcpy, we can do some error checking which is inexpensive relative to the copy:
        if(boost::math::isnan(*start_x))
        {
            std::string msg = std::string("x[") + std::to_string(i) + "] is a NAN";
            throw std::domain_error(msg);
        }

        if(boost::math::isnan(*start_y))
        {
           std::string msg = std::string("y[") + std::to_string(i) + "] is a NAN";
           throw std::domain_error(msg);
        }

        m_x[i] = *start_x;
        m_y[i] = *start_y;
    }
    calculate_weights(approximation_order);
}

template <class Real>
barycentric_rational_imp<Real>::barycentric_rational_imp(std::vector<Real>&& x, std::vector<Real>&& y,size_t approximation_order) : m_x(std::move(x)), m_y(std::move(y))
{
    BOOST_MATH_ASSERT_MSG(m_x.size() == m_y.size(), "There must be the same number of abscissas and ordinates.");
    BOOST_MATH_ASSERT_MSG(approximation_order < m_x.size(), "Approximation order must be < data length.");
    BOOST_MATH_ASSERT_MSG(std::is_sorted(m_x.begin(), m_x.end()), "The abscissas must be listed in increasing order x[0] < x[1] < ... < x[n-1].");
    calculate_weights(approximation_order);
}

template<class Real>
void barycentric_rational_imp<Real>::calculate_weights(size_t approximation_order)
{
    using std::abs;
    int64_t n = m_x.size();
    m_w.resize(n, 0);
    for(int64_t k = 0; k < n; ++k)
    {
        int64_t i_min = (std::max)(k - static_cast<int64_t>(approximation_order), static_cast<int64_t>(0));
        int64_t i_max = k;
        if (k >= n - (std::ptrdiff_t)approximation_order)
        {
            i_max = n - approximation_order - 1;
        }

        for(int64_t i = i_min; i <= i_max; ++i)
        {
            Real inv_product = 1;
            int64_t j_max = (std::min)(static_cast<int64_t>(i + approximation_order), static_cast<int64_t>(n - 1));
            for(int64_t j = i; j <= j_max; ++j)
            {
                if (j == k)
                {
                    continue;
                }

                Real diff = m_x[k] - m_x[j];
                using std::numeric_limits;
                if (abs(diff) < (numeric_limits<Real>::min)())
                {
                   std::string msg = std::string("Spacing between  x[")
                      + std::to_string(k) + std::string("] and x[")
                      + std::to_string(i) + std::string("] is ")
                      + std::string("smaller than the epsilon of ")
                      + std::string(typeid(Real).name());
                    throw std::logic_error(msg);
                }
                inv_product *= diff;
            }
            if (i % 2 == 0)
            {
                m_w[k] += 1/inv_product;
            }
            else
            {
                m_w[k] -= 1/inv_product;
            }
        }
    }
}


template<class Real>
Real barycentric_rational_imp<Real>::operator()(Real x) const
{
    Real numerator = 0;
    Real denominator = 0;
    for(size_t i = 0; i < m_x.size(); ++i)
    {
        // Presumably we should see if the accuracy is improved by using ULP distance of say, 5 here, instead of testing for floating point equality.
        // However, it has been shown that if x approx x_i, but x != x_i, then inaccuracy in the numerator cancels the inaccuracy in the denominator,
        // and the result is fairly accurate. See: http://epubs.siam.org/doi/pdf/10.1137/S0036144502417715
        if (x == m_x[i])
        {
            return m_y[i];
        }
        Real t = m_w[i]/(x - m_x[i]);
        numerator += t*m_y[i];
        denominator += t;
    }
    return numerator/denominator;
}

/*
 * A formula for computing the derivative of the barycentric representation is given in
 * "Some New Aspects of Rational Interpolation", by Claus Schneider and Wilhelm Werner,
 * Mathematics of Computation, v47, number 175, 1986.
 * http://www.ams.org/journals/mcom/1986-47-175/S0025-5718-1986-0842136-8/S0025-5718-1986-0842136-8.pdf
 * and reviewed in
 * Recent developments in barycentric rational interpolation
 * Jean-Paul Berrut, Richard Baltensperger and Hans D. Mittelmann
 *
 * Is it possible to complete this in one pass through the data?
 */

template<class Real>
Real barycentric_rational_imp<Real>::prime(Real x) const
{
    Real rx = this->operator()(x);
    Real numerator = 0;
    Real denominator = 0;
    for(size_t i = 0; i < m_x.size(); ++i)
    {
        if (x == m_x[i])
        {
            Real sum = 0;
            for (size_t j = 0; j < m_x.size(); ++j)
            {
                if (j == i)
                {
                    continue;
                }
                sum += m_w[j]*(m_y[i] - m_y[j])/(m_x[i] - m_x[j]);
            }
            return -sum/m_w[i];
        }
        Real t = m_w[i]/(x - m_x[i]);
        Real diff = (rx - m_y[i])/(x-m_x[i]);
        numerator += t*diff;
        denominator += t;
    }

    return numerator/denominator;
}
}}}}
#endif

/* barycentric_rational_detail.hpp
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
*/