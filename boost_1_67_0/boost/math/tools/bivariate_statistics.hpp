//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_BIVARIATE_STATISTICS_HPP
#define BOOST_MATH_TOOLS_BIVARIATE_STATISTICS_HPP

#include <iterator>
#include <tuple>
#include <boost/assert.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/math/statistics/bivariate_statistics.hpp>");

namespace boost{ namespace math{ namespace tools {

template<class Container>
auto means_and_covariance(Container const & u, Container const & v)
{
    using Real = typename Container::value_type;
    using std::size;
    BOOST_ASSERT_MSG(size(u) == size(v), "The size of each vector must be the same to compute covariance.");
    BOOST_ASSERT_MSG(size(u) > 0, "Computing covariance requires at least one sample.");

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
    BOOST_ASSERT_MSG(size(u) == size(v), "The size of each vector must be the same to compute covariance.");
    BOOST_ASSERT_MSG(size(u) > 0, "Computing covariance requires at least two samples.");

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

    // If both datasets are constant, then they are perfectly correlated.
    if (Qu == 0 && Qv == 0)
    {
        return Real(1);
    }
    // If one dataset is constant and the other isn't, then they have no correlation:
    if (Qu == 0 || Qv == 0)
    {
        return Real(0);
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