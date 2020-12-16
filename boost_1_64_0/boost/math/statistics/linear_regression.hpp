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
Z/rcboOOAwDpcCOz6At91R7FpkOf8NvXnyUd5tjg6Z7t25/Z/E7P+mzDuxdpzSjCWFRohkxt/8M+xInuQ0xP+VbwtgB01vFN5MrceC7R1PnBNtAHmc5t47r/8TxJnz8n14/F5eX3il5l+r4XKnT+bHxvOQx03LdM2f5MtHbZ7ryI6Swb9TnE8hZ06JOLK9MLcytsQ/0S+bse/2iSTsKEO32kDUenW465+tJ2HJxsCRO8rAVj5LH9WxvG8Hm493LE6Nu8Zl/36aOtGCum1JVXEI67z7CbW3xlG2YB7JdkFEwq69CrbByvjzie2zBGH1wZbcGQ7TLK9GgLRvPF4/LOH2vFgvCEgZxOLRi6Z6GOVn1/Pp75cZVmWeJApcZ5ScXVTuJlZRnljv50JllYJ7VH8ugQ3Alp/f+DOMcZGLQi5XPiehtjnn0/vcHGmGffsREbo559b7bQ+ezLNhLHaN1gHGJIn3OM5i9j1PXj0GbA0N1/6q01OhKIN7KPwNoFlMqfrKerMgR9qf4O+gmFPpmU3RwgkzW+oyHmU60YegqU9XxGwQhqEuj0L1hyYB1I/wrTB5nDDR3gV4FehlOTvgutm6yzBN8zv2HwmfV+25JLr/e7Jr+hs/zac5t3x6TbwTq/Z5bJPJL+fautKBP25w9b+xPLwPb+2Giv6/OYuAV/x/XekAY0HfU+tM7C0M7yyma+rBeYOvMnH5tOJiffFE5Mu2UwPQmvxi4cuxbAT1/TLZ4eATyfLxDAde7epNHP9/vgTXR2YVndyzqbVYwUm+fUFosm09ACHW35iS5XfRSA6F/YRnTocyJrdjxM1+se36nTuG621WQ6dSWVfWAX0alezkdANOoTLfbJI0hn3R4WwXZL+TMII2Sjei/vod9JZqDhekw0kpfyBu8VNNTL1qsLj8MimUkF7jJh6me1Y86tKOvTPsKQvlMWorQf7jc2BgqBMlCP19BD3xCFMJ3nMEYXheu5r2BUUYCOulWbfk65W8CcQ7qcE4KXaDcPajTgo7M82I6rtPHpeiJ58zQULk9ishTGXj20FlY2h7/t8zWsJs/cC3QacFI74xcSjToBy8X4aES3vsWWFxFN/xJqP7dg1DKefHFDnxg6tm6/xMTYY+vWERUjDWqscfG1l1oYLIYwkF+GMEPH6JWX2xgoheiLR5FO52xZAq+NrzDp+tgMXkl0XEN0/tFXmXTJz+vLqEqXvLyuParS9LbflzS0c7C/BeYcNTH2t7hznDBD+/DWmIqxx9aNE0hfY55fe7WJsef5pccI0zrP5/5D2pXH6LlO8Wk73Xu1qqqqqiiKi7Zm2rm2Pu++LzpTijKmM1/NMJv5vqG2aGLJlVSQEIRIY0n8UYktISJx7bVvF7X7Q4KoqNh353m+8z7nWd5vKLmZ7977nt85z76fZUzSW8d5fgfSW8b52OMkzRrnhx6v0sYoewmoIBrj/NIT1sAKqYT96RMR+1/MH3c/CbH/xfxx7ZSG1cr5fiZp1vzxRkfSWuePl7qSbrXxjCdpA+eP2rcxqownBEhfY/44GpoYu88eiiRm4PyxKzYx9vwxlEjMwL5/Q2La54/rKdIHzB+fyUy63uffn0t66/zx9kLSW+ePO0tJt+aP5UqjYdnJjnGkv4eYlpGLRQhbsp386R5dP7HKg7zMwlvWT1RtjEeNvev5EyOo8US4i+vbcZ1FxEn7eBsHF3q42SLc24dtXFfi9Do5IfeCKoRkXV1nYdCsQ7xRkQ3+egsHezURP1/W71Wzfp2wyotb94ei2jWfNHUQ8KDML0PLxCeb3PVrYys3ldgtG9fG9i7SPeztm9uw0Cp4qynnxkE4si+je/AtNtbUbxzb2oo=
*/