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
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/core/demangle.hpp>
#include <boost/assert.hpp>

namespace boost{ namespace math{ namespace detail{

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
            std::string msg = std::string("x[") + boost::lexical_cast<std::string>(i) + "] is a NAN";
            throw std::domain_error(msg);
        }

        if(boost::math::isnan(*start_y))
        {
           std::string msg = std::string("y[") + boost::lexical_cast<std::string>(i) + "] is a NAN";
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
    BOOST_ASSERT_MSG(m_x.size() == m_y.size(), "There must be the same number of abscissas and ordinates.");
    BOOST_ASSERT_MSG(approximation_order < m_x.size(), "Approximation order must be < data length.");
    BOOST_ASSERT_MSG(std::is_sorted(m_x.begin(), m_x.end()), "The abscissas must be listed in increasing order x[0] < x[1] < ... < x[n-1].");
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
        int64_t i_min = (std::max)(k - (int64_t) approximation_order, (int64_t) 0);
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
                      + boost::lexical_cast<std::string>(k) + std::string("] and x[")
                      + boost::lexical_cast<std::string>(i) + std::string("] is ")
                      + boost::lexical_cast<std::string>(diff) + std::string(", which is smaller than the epsilon of ")
                      + boost::core::demangle(typeid(Real).name());
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
}}}
#endif

/* barycentric_rational_detail.hpp
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
*/