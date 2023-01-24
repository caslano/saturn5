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
lZTyWA3cJUaBmaGWUqHYJrMzgwgrRRQKvOesW7eAhDR15gRc1P5OSadTpWIR0j9Fxq6xsttEig/RirWrit9+2ootJmEvkg3yUEZZ2M6sBUN98A1tHYAFn7LHuwsFwlcLfrIO7c+GA6aBKwjNxCPMczLRVps9TxZRH+KH1OcjyKJvrEB349Ni+THSK+VBuD0yR/rnscUNCwJ5lfxk4tuwjfAl3A3NBQHnoCzTuzmzTyZ6nX3r+/OZcrSAbVmqDUIoi6Oi07HsLYs4z4UAJ5I8l1zUzf0B0PH8rcc/72HaBXi02F6nIm4d0ckA3JsaKmfJkbjuEFlxnMMvvfzR6KqKZAGH2Tp0LN8Cb2qRtCfre8iDQA8mJMsocLo2+kg9DukfF92ZgUy9b3gG+m6ILPheApmc/WqPfim5NQpFaNjiKawxUs2QVgo381DHf2SRt0tL+1zNKyaKLuopR73Lphii6rkYTSd6WwzqI8LH2/OwS5BmuPxetxvA/SgTQkFA8dkzGlJGHSh2HGbNoIESjefeVBYxefta+OggObU2/TnPvqz32znxfQT4AwA8G9rub2POZ5uHH1YsZZeE776A3q7nMQk9t06ycMUYFg7v+lbymXxlFZ7AzFb7a99++oA58Y0Dtyuf9UdhPIPfs7zZBxDrj9nhFzzeJs4mvfYZToaMSu1bzr5w10C0jUAE+tZB7TeXsFdP9lphXVsHL6qh
*/