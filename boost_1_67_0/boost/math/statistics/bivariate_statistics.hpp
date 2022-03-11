//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_BIVARIATE_STATISTICS_HPP
#define BOOST_MATH_STATISTICS_BIVARIATE_STATISTICS_HPP

#include <iterator>
#include <tuple>
#include <boost/assert.hpp>


namespace boost{ namespace math{ namespace statistics {

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
    auto [mu_u, mu_v, cov] = boost::math::statistics::means_and_covariance(u, v);
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