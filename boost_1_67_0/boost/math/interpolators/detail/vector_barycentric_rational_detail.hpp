/*
 *  Copyright Nick Thompson, 2019
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_DETAIL_HPP

#include <vector>
#include <utility> // for std::move
#include <limits>
#include <boost/assert.hpp>

namespace boost{ namespace math{ namespace detail{

template <class TimeContainer, class SpaceContainer>
class vector_barycentric_rational_imp
{
public:
    using Real = typename TimeContainer::value_type;
    using Point = typename SpaceContainer::value_type;

    vector_barycentric_rational_imp(TimeContainer&& t, SpaceContainer&& y, size_t approximation_order);

    void operator()(Point& p, Real t) const;

    void eval_with_prime(Point& x, Point& dxdt, Real t) const;

    // The barycentric weights are only interesting to the unit tests:
    Real weight(size_t i) const { return w_[i]; }

private:

    void calculate_weights(size_t approximation_order);

    TimeContainer t_;
    SpaceContainer y_;
    TimeContainer w_;
};

template <class TimeContainer, class SpaceContainer>
vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::vector_barycentric_rational_imp(TimeContainer&& t, SpaceContainer&& y, size_t approximation_order)
{
    using std::numeric_limits;
    t_ = std::move(t);
    y_ = std::move(y);

    BOOST_ASSERT_MSG(t_.size() == y_.size(), "There must be the same number of time points as space points.");
    BOOST_ASSERT_MSG(approximation_order < y_.size(), "Approximation order must be < data length.");
    for (size_t i = 1; i < t_.size(); ++i)
    {
        BOOST_ASSERT_MSG(t_[i] - t_[i-1] >  (numeric_limits<typename TimeContainer::value_type>::min)(), "The abscissas must be listed in strictly increasing order t[0] < t[1] < ... < t[n-1].");
    }
    calculate_weights(approximation_order);
}


template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::calculate_weights(size_t approximation_order)
{
    using Real = typename TimeContainer::value_type;
    using std::abs;
    int64_t n = t_.size();
    w_.resize(n, Real(0));
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
                Real diff = t_[k] - t_[j];
                inv_product *= diff;
            }
            if (i % 2 == 0)
            {
                w_[k] += 1/inv_product;
            }
            else
            {
                w_[k] -= 1/inv_product;
            }
        }
    }
}


template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::operator()(typename SpaceContainer::value_type& p, typename TimeContainer::value_type t) const
{
    using Real = typename TimeContainer::value_type;
    for (auto & x : p)
    {
        x = Real(0);
    }
    Real denominator = 0;
    for(size_t i = 0; i < t_.size(); ++i)
    {
        // See associated commentary in the scalar version of this function.
        if (t == t_[i])
        {
            p = y_[i];
            return;
        }
        Real x = w_[i]/(t - t_[i]);
        for (decltype(p.size()) j = 0; j < p.size(); ++j)
        {
            p[j] += x*y_[i][j];
        }
        denominator += x;
    }
    for (decltype(p.size()) j = 0; j < p.size(); ++j)
    {
        p[j] /= denominator;
    }
    return;
}

template<class TimeContainer, class SpaceContainer>
void vector_barycentric_rational_imp<TimeContainer, SpaceContainer>::eval_with_prime(typename SpaceContainer::value_type& x, typename SpaceContainer::value_type& dxdt, typename TimeContainer::value_type t) const
{
    using Point = typename SpaceContainer::value_type;
    using Real = typename TimeContainer::value_type;
    this->operator()(x, t);
    Point numerator;
    for (decltype(x.size()) i = 0; i < x.size(); ++i)
    {
        numerator[i] = 0;
    }
    Real denominator = 0;
    for(decltype(t_.size()) i = 0; i < t_.size(); ++i)
    {
        if (t == t_[i])
        {
            Point sum;
            for (decltype(x.size()) i = 0; i < x.size(); ++i)
            {
                sum[i] = 0;
            }

            for (decltype(t_.size()) j = 0; j < t_.size(); ++j)
            {
                if (j == i)
                {
                    continue;
                }
                for (decltype(sum.size()) k = 0; k < sum.size(); ++k)
                {
                    sum[k] += w_[j]*(y_[i][k] - y_[j][k])/(t_[i] - t_[j]);
                }
            }
            for (decltype(sum.size()) k = 0; k < sum.size(); ++k)
            {
                dxdt[k] = -sum[k]/w_[i];
            }
            return;
        }
        Real tw = w_[i]/(t - t_[i]);
        Point diff;
        for (decltype(diff.size()) j = 0; j < diff.size(); ++j)
        {
            diff[j] = (x[j] - y_[i][j])/(t-t_[i]);
        }
        for (decltype(diff.size()) j = 0; j < diff.size(); ++j)
        {
            numerator[j] += tw*diff[j];
        }
        denominator += tw;
    }

    for (decltype(dxdt.size()) j = 0; j < dxdt.size(); ++j)
    {
        dxdt[j] = numerator[j]/denominator;
    }
    return;
}

}}}
#endif

/* vector_barycentric_rational_detail.hpp
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
*/