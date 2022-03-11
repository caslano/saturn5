/*
 * Copyright Nick Thompson, 2019
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_STATISTICS_LINEAR_REGRESSION_HPP
#define BOOST_MATH_STATISTICS_LINEAR_REGRESSION_HPP

#include <cmath>
#include <algorithm>
#include <utility>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/math/statistics/bivariate_statistics.hpp>

namespace boost::math::statistics {


template<class RandomAccessContainer>
auto simple_ordinary_least_squares(RandomAccessContainer const & x,
                                   RandomAccessContainer const & y)
{
    using Real = typename RandomAccessContainer::value_type;
    if (x.size() <= 1)
    {
        throw std::domain_error("At least 2 samples are required to perform a linear regression.");
    }

    if (x.size() != y.size())
    {
        throw std::domain_error("The same number of samples must be in the independent and dependent variable.");
    }
    auto [mu_x, mu_y, cov_xy] = boost::math::statistics::means_and_covariance(x, y);

    auto var_x = boost::math::statistics::variance(x);

    if (var_x <= 0) {
        throw std::domain_error("Independent variable has no variance; this breaks linear regression.");
    }


    Real c1 = cov_xy/var_x;
    Real c0 = mu_y - c1*mu_x;

    return std::make_pair(c0, c1);
}

template<class RandomAccessContainer>
auto simple_ordinary_least_squares_with_R_squared(RandomAccessContainer const & x,
                                   RandomAccessContainer const & y)
{
    using Real = typename RandomAccessContainer::value_type;
    if (x.size() <= 1)
    {
        throw std::domain_error("At least 2 samples are required to perform a linear regression.");
    }

    if (x.size() != y.size())
    {
        throw std::domain_error("The same number of samples must be in the independent and dependent variable.");
    }
    auto [mu_x, mu_y, cov_xy] = boost::math::statistics::means_and_covariance(x, y);

    auto var_x = boost::math::statistics::variance(x);

    if (var_x <= 0) {
        throw std::domain_error("Independent variable has no variance; this breaks linear regression.");
    }


    Real c1 = cov_xy/var_x;
    Real c0 = mu_y - c1*mu_x;

    Real squared_residuals = 0;
    Real squared_mean_deviation = 0;
    for(decltype(y.size()) i = 0; i < y.size(); ++i) {
        squared_mean_deviation += (y[i] - mu_y)*(y[i]-mu_y);
        Real ei = (c0 + c1*x[i]) - y[i];
        squared_residuals += ei*ei;
    }

    Real Rsquared;
    if (squared_mean_deviation == 0) {
        // Then y = constant, so the linear regression is perfect.
        Rsquared = 1;
    } else {
        Rsquared = 1 - squared_residuals/squared_mean_deviation;
    }

    return std::make_tuple(c0, c1, Rsquared);
}

}
#endif

/* linear_regression.hpp
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
*/