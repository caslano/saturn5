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
nisn0LIYDGn3r8Dafe0u79rtqxa3qxZgTfrhZauIYYw8Jy3YU0z63ptHVBm4UDPqte9uLw47CtFPBuiyZNQmV2mKCI7FbcM28Am5urI401QlkjN4Iqvv3HBnMYeifEMJ/FJWL8L5o6UEzcsukdRVlmcxi4HzuVNgkWd3Bur7QSbspyKpN4brRVZf6z5nGwxv5362Dx/ITBc2ZFa7s0tEBYFPhFwh4UaG19jXOdbwvZPOBJvsgvHePpBOfmR2ve1Yx8jmV6iKp/O4fHF5dUWoz33XONFFsk0n66dC5p+4xGmulF935n3L7jH9mMnySR/sEOPVWogxzjP66mOzibB2LG8oZDZRbOQ0bV67XT7j4ZjBzspsl9lqZ36JKC+a3a2+ZqtvDPgGEbi9RRifP2axPlGZzTjqzy7hZ33Aq0uBr3+R14XbNqTdG2hGajG/HnyOx27nZV6ygA9qXsUZm8PJ+8lTxu5WrmR1ZlCjEd+WLYPurHztGNMftdYiwMzMRv79tDb6KaosPrzD2poJGocPOov5HEa+plKMUalOloPB9+dh35y9VQZnk4/ZWXJRf4/ZaeCTHunzVqP/G1bK0meXCD/CCxTvhK6hXAddzqDVpLA9Nfzt4ssgJ5eEYI+xTM/lJOB1mC+K3N4UWGDUZE2daeRwJWSI4m4JzuLjAh6swr1IYxHgdJFlMAP0SkVYH5EWoXFZXQxlkI/Xfupe
*/