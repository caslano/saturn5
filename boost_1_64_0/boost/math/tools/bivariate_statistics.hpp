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
qbOthFpQ2lAjnecdgbGnS5OpygtFiCIzrHKIQsxBOCjLtNUwofp/WzCIxKPkf0PkRTVVzCPgMromwQHbYemHyeuckFc1KgKDcJ/zPbCRug3c4S+lWBMfClSw25/xjuXkiq7vfHbkiVGRgVJpTVLZBWO9oo3EdMXGlJlgyM/p0z15nD7Z3+AO5rvxjA83CpecqjBldMsFaD0NgYI3jbHdffWGZhXJiGei+MxXO2IBaM5kRpdHeTjZ7+5ujYrFLccm8YyPVDl4NK+bbhfRBx+w1kwxykCQA2tEr1zYgaUtZRpXr54qMPH5xCtucqj59XFBqpvS1i/BTtW9E0k5G4UNBz+beQ4A3f83nNJbew7INHwcuzbV4h+nE7nCYq+F57TnJ3Gdkn1LtIg+P3SxYfmsQRucDmfgD+tADF0QqvZeZU20DH7VlKKFH3ZKxRRpYNUHWv2ytAMrbzq1o/kfZV+dtvT0g9HXWndmCTQ+4S5t9SWLqSzpeOds8uNvV8w/B3XShvAxBE6955ueFrI4/zIXVT7RPE6uIBp6ea8NRvAj2O60F+lUZW6PNvf3QA==
*/