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
K0n3NdgP/EHqtU7Gx8/gJBI3DQ99P7AVvBi+E34O/gRO38AZcf5cQdg6fz47J/IM2rNBx3PolXG+NxhEdsmOjoTOoutyQ+fRbaSxn0lXm2XKNwljnU2fn9t+Nj0Bvpj4O4lbmh86n54W54z6cWRinVNfT/nPwevg4SOcxmTYA88foc+uNWnSpEmTJk2aNGn6P1DPn/+3W7H71Qv//uj5/x8/359Ybqh9wbW9/j37gnr/r2f3/74xoA1D+wR5YAU8GZ4Bz4Xb4Kth216B7BN0vUcQ3h9I8D138WzUZT8g5l6A7AOwB9A923RNmjRp0qRJkyZNmjRp+vP8/5uD9b764LwesP0vNpzKRnsjZftfH7C55ntc7oDpZWCUIXM7Bg7ZSoYP/jX7vPJufmo+FzPtoHumz2tsLHJFseRcBzfX18x22cSNTaXskZ3na69Sj+xVNJXTH5YdmCzfsuU8PRN+lDYsPCxkB6YslWvdgSBmyjV86tDV1Fhvdtu4QxrrPUXD+Z1434gRGww3IzYYb0D9seNaruy4muz2YeQZbR+2S8Zi9kt81OFg6uR0pCub+R/SzbSHuH3NXsIhu+OTVdre6vdf1e+BuvraoPrdrPOp5u+U4jCmZuQj02xADl574K1p9jNUXDWNjbPr2/M7TvLrxGasVb1zQWzGzPY0if2XpbtlSYaiAtHdYNHduR105234o7o7N4bunnNQySTRXe/0uLq5VqVNVbr5Pe3dVtp7uRh3pkp7B8CPI3efvb3+xqA7GG6qK9SLRnS/2tpG+qi2RbcjbDMYJeskHL89Rao9mdIeypaS2+39KCNUgrRzd2nnyN7hdipywpfROysOs79Lg0nM3zhHfQSU1vrqa+ZtuWVNY0Nt/axmv1dFGzYbRX85ZZV3XV+7vfnoPoaiSXAfwWfQ95shfdfWN3hcTV5ziJufBgnZ7D4Vss88yD3L65rpDpjNDY/51Spd/wjdv9lR99JP/kPcpq5kDCXNN+WGUkZvW39EpkdPqg4rqgyott7PyJfKqTpkEfu1kk8nD8L8J/kSTral9bltSY1MsTlep9KWGUWGQ9mKPqtkG4KuOq/b4/WHx/saJecw8kUfNhmX2+Px43QRlv1Iya4nYf6b3z7PPKzS1gcNSNUX/FLJDyf34lhtSNgemnpF9FKajEl0rzSv3u0i42AGCUwaJdddJfx8FWFV7sL6AOMv6G0w7xG+eeYVV+9x2fPODdvV2mPbfTrGqnxKKdFhHxvkHzE2OtX51PmJ67xayeaGdb61Cid3ORdbujszSnd2e/A7RVd9JGEKvBJ5vyqjZWpwYrPfj66meWcmdC1ac5+vn6FoM5EYDZ9DvvPm2+cEdw13eb83/IVgbuazw/qHgnV0Vm39TBQHWdfEYpVHvprTl1H/cZQVNOf0FKeasy078eZyo8vxZdZ5J6lznvgfbCgCI6TO90TU2XJDcNcyX9vfTFRjyH2mifq8DR9i1smZHj2nqTpmEpckdZwDz03AHtte18VS1zQRSJW6fhGzrjO9tY1+b3RlLT3NS7Ds7aXsbPEhGCoChVJ2r8NjlW3+H6zzM7QtT0Kr7YdS7mHw/G6W3zYg6n4j5Zd3Ub54joX74/DfUfbq1I5zyxLK3kKVvTCqbO/cGq/6DhWD2Mdw6donYIvDu+cTsMXh3fMJQD6W3woxtnrbykiPSpNNOD9cp/b2qec1W7rsqHR5km7O+Ih06n1a9nR5UemGWM8Ecq0ckUB/9YTfAvGqregmQjP5xOdJHtGt5zdVX9oY3ULlkzPdbJfkaR9TdWlh3xJFxfIuskNijufmhsjLWHyLRT8L4BZ4YQJ6ss8na6QOqYag1OGSBOrg518=
*/