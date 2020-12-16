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
2/QHD8lZHaev9Zx5Rj3x/7a3j5L01Ba3Gb79TxJcIfF1jimu/7n8kbB7f96ERNP/7JD0P8u7UId9cgO9/Y9psyMkbE/e0U7mHT1entfXybA62/Psi61IP3OR2J/wu34mVcM9Ie7dyOPD1k7OITVw3rCcUKJp86skTQdJnxJp0x+IXe0Kl9trTX/cRMpjk7dfMWW/RZ6zkzNoTe2u9mZrP+dpU/bXi9sBTkPrezty1uhpsWvOuz6I/ZobTLt7VOwPjCmuj2kmZTOY9Mabc4CbJL3TQlWx8elfJFyqxHs47/zndqS9HiZ5OsX0d92l/R5i3uP+EuYOb99i8jxL3C+hz8rjJM8Su55zoqmvQyXuo5wDrNftJCda3ldKWhtbpNX04Q+42v7OaFlL/xH3J/Yf5qymTo3vsHku/IZ/luJ39GOm/8jNzot854ySCBJMPzIjN3t6v+LuAyIOz9qK3v/v10eoX+89Q+adyxb3bbbfGg5hvX1DNhuho7/h4t5F30VOaoj5PjuE3dHWUDvaB0w07eE88TPS9Akfi3m8y+8Jxm2euB1vJRi33LzMvBm5ljmLgo34aWYl6XdPgZin2yn0BdPsqMznRz33RPnVfZK77k0daP2btSIpa1P/S4qp/3Q9//SG9Om8yzBc/y8/7q5/fkP2Uv+pWk+vSbhNMZ3C/5KvJmxWfTHG9msfPMO3fZizKl+J+7DQPoxKXuJ3OMaJ9ft9IR7ftmP63vfF/ePQCM7hnOFc7bcOSBy+bci80/s+GXYfHsqi33rFSTdta9ZTYfss880z/4mw+Tz6hQy7kz3A/ivqcieMtcu+VjdC1g6v2//9p4efu6nr0ePjJz48bMy44tbwym9N0X+vf/nuZY+zdVyj47e2sAGapijq1VDhXfIfwuqwQwx7ZdXcCn4E+8GP4QnwE3iu+nsKHgRt4uoGW8FecBo8As6DA+BSOBh+8Bt71wIdxxSGb7bRFkseIk0rjbSq2qpIk5a2oprmQUgjkpCWsNnsTpJtNztrdvJovYqiKIqglCMOpShS6nE84/1+B6lTR1EURRAU1frm7p3J7NrQrYlH/d85//myd+6937137kzmv3fmXvAscCrqcRI4G+wGfwCeCk4ZgHzA+eBC8OXgmeArwSXg5WA/eBW4CbxbLPod+ATwaeAA+HTw4+CF4E7wOeB9Ue8LwbngxWC0CxpEf5ZCHqJdhsPQhziSRLvsAx4DHiXaYV/RDqPB54BVcAd4PjhGyxM8DnwuOBN8EXgZ+GLwTeDLwJ+Bl4LH2NCHwdPAN4E3gueDhw5APuAp4HPBOMbzuR18MXg1uB38BPg+8FjU837waeBHwFeAHwV/AX4KvAX8NHg26vkiOAB+CfwtQzn0/xvif1+muDYXi3ZYZ0O9wJ+Ck8EbwGngr8CZ4C/A08Ffg8vA3WAn+BtwA/hb8ALw9+BW8I/gd8CbwWORcQzKcQp4IPhLsB38DXg3Ub6WGHFPEvfmTPB4mFf03/mifAvAQ8FngQ8Cnw0+FLwGPA18HrgQvEiU83zwHPDF4IXgS8Bt4CXgx8CXgt8FXwb+BHwFOCcG1xq4AHwteCb4OnAl+AbwW+B7wF3gNeA14JvAPeDl4Dic35vBe4FvBZ8Mvgs8H9wOPgu8CrwEfC/4cvD9YPRBnu9Y8BrwOPCD4ALwQ+Bq8MNgL/gx8BPgp8GvgJ8Bvw1+FvwB+EXwevBb4JdjkS/4TTDy5dfLmeAu8fsmhnLhnYGnYF2wjTBms7Mk2BhYDqwU5obp78c/d0ws8/N34XvffX8JN56l4t33xeL99pyw99YXhr1/vtT0brk77L3xFui1wtphnTZ6p4FAIBAIBAKBQNhR8Hc=
*/