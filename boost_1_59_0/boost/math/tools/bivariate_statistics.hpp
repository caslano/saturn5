//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_BIVARIATE_STATISTICS_HPP
#define BOOST_MATH_TOOLS_BIVARIATE_STATISTICS_HPP

#include <iterator>
#include <tuple>
#include <limits>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/header_deprecated.hpp>

BOOST_MATH_HEADER_DEPRECATED("<boost/math/statistics/bivariate_statistics.hpp>");

namespace boost{ namespace math{ namespace tools {

template<class Container>
auto means_and_covariance(Container const & u, Container const & v)
{
    using Real = typename Container::value_type;
    using std::size;
    BOOST_MATH_ASSERT_MSG(size(u) == size(v), "The size of each vector must be the same to compute covariance.");
    BOOST_MATH_ASSERT_MSG(size(u) > 0, "Computing covariance requires at least one sample.");

    // See Equation III.9 of "Numerically Stable, Single-Pass, Parallel Statistics Algorithms", Bennet et al.
    Real cov = 0;
    Real mu_u = u[0];
    Real mu_v = v[0];

    for(size_t i = 1; i < size(u); ++i)
    {
        Real u_tmp = (u[i] - mu_u)/(i+1);
        Real v_tmp = v[i] - mu_v;
        cov += i*u_tmp*v_tmp;
        mu_u = mu_u + u_tmp;
        mu_v = mu_v + v_tmp/(i+1);
    }

    return std::make_tuple(mu_u, mu_v, cov/size(u));
}

template<class Container>
auto covariance(Container const & u, Container const & v)
{
    auto [mu_u, mu_v, cov] = boost::math::tools::means_and_covariance(u, v);
    return cov;
}

template<class Container>
auto correlation_coefficient(Container const & u, Container const & v)
{
    using Real = typename Container::value_type;
    using std::size;
    BOOST_MATH_ASSERT_MSG(size(u) == size(v), "The size of each vector must be the same to compute covariance.");
    BOOST_MATH_ASSERT_MSG(size(u) > 0, "Computing covariance requires at least two samples.");

    Real cov = 0;
    Real mu_u = u[0];
    Real mu_v = v[0];
    Real Qu = 0;
    Real Qv = 0;

    for(size_t i = 1; i < size(u); ++i)
    {
        Real u_tmp = u[i] - mu_u;
        Real v_tmp = v[i] - mu_v;
        Qu = Qu + (i*u_tmp*u_tmp)/(i+1);
        Qv = Qv + (i*v_tmp*v_tmp)/(i+1);
        cov += i*u_tmp*v_tmp/(i+1);
        mu_u = mu_u + u_tmp/(i+1);
        mu_v = mu_v + v_tmp/(i+1);
    }

    // If one dataset is constant, then they have no correlation:
    // See https://stats.stackexchange.com/questions/23676/normalized-correlation-with-a-constant-vector
    // Thanks to zbjornson for pointing this out.
    if (Qu == 0 || Qv == 0)
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }

    // Make sure rho in [-1, 1], even in the presence of numerical noise.
    Real rho = cov/sqrt(Qu*Qv);
    if (rho > 1) {
        rho = 1;
    }
    if (rho < -1) {
        rho = -1;
    }
    return rho;
}

}}}
#endif

/* bivariate_statistics.hpp
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
*/