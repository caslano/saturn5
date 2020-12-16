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
wA1yTE66WKR6ZnlqZ0MPfSQT7Qu7kcZ8ao4IpE2o5fI54JkNXf36TL+2F+hyHWmX6+6zkN4i1+FnI62l3pv7kTZErn89B+m6XKyrOSDo2JuzZ2nfv3YQfh/s00iEKJeoByK78Weq7x1JWKVekGTO4OJr+Ardfbbu25KFdSJzwRv5AZGNzwUq3xjUkdVRXDkT5KwPU6ip4x9aHb4DS5Yf5kFi1JGEhp//jv2aT4nr5SIhfGnlH98jcWyjHwVlUJXdmMuX8a0mSje34iAcRV68q3XLVITlY05kmDjY3C/VuHT95cXl98+vSvMypI/v1+8saSRS2D10qEqymX5ynyjP+Bi8DgMOc0Q928YpGaIol1SAOLNjCNgZnGU+DuOvL7FCJJltdPrcucG6/yGgyWs+nKphBEs7iY/ybwMHZbTzEbSLTBOrEFIGtPczTa6kSJTr8GeANjgZT+S4qMvfP4u/c0jzgVyXlbJgxncOwm/XB3uDB4+IycR07E7GtBfJveOGSsfeNfM/fbUpdyr3G7k/jr9JGSbK6ehNpT+Jcn8daPrxAuYs/P6NQV2TU66fTVeRmYKTBcM6ftSUk1dV9qa66QIp921Lbpv/Jw3/m8OJJHrrdO1OuAXQRL/80uoXaraU9ddrymr30U1dVinj72wZ1Rxesp4//Nc+QTzW8zPAcwyuQVv+aLWF2GjdzGFfflXr/ODz9+0WzFvFEVn3w7Uxhh3/jg0tGMOO/6NtGMOO/2+EseYq7UGLIzoGpOW4QBs1mhW39qZBlxv43PyqHD+k99cw2lvCdYMG0vOb6RaiqUEL+Gy/TafD6YJ9O7YLmsi7gOkTBkbp/L6xE+i4pyM/tenPT0OaOZLUuncDBvdek/8poln8JN/PHkGMXBZROOWO8ZtnCPriMhi9gA6+deqQveQX9qyF5Zs61I3nGcDTO6ttN7xvr0UnPdCxxt7sWYgZNuv4NkRyXvnvPCAF1zG+z8a3N43rOPXs/8oDD8qMH9v/X/B6PmW43yO+ffqyPfIQnPE+ju/HgH2AHM0jzwXcA+Zoho/dijVtnP/WjsOjPOMOHWrHmbGudj8fcLjf88Bm+qUX6fT5JXHyZHrnpTodt2HOp/Yqk66P7XxUp+PxgvOrH7Po8EWU9fK4Rcdlh3UQ1/dpvvFVEXtlnfiOfp7Q35G+gzx4RiyiKnSBHjbP7XhGPExxJySez9SpXxQim4RRySTp+/B96G/yHV0H4VGPznnxPhvDpzw9jvyoiTP2oEstGNzuCHNgvY0x/bF+3IJR/bHGN9h0M97j1wSG1m3GIQbfktoxkwrm/kbA0PrdXs6TmxBjl8Nvk8/SYyh4QVEHZQIvjY/DWi10BcFM34gh1ld5Sif16qxyg7J5cHxzlYWB+W70aZUnd6ASP3WTwlkEV+03rcxRHRSn/Iym+/GKyvXiKnOW5i9peIqjNKfgHyuSNHILL5DNeO+8kT/8xrP0ON1Qdpj5tUNncH6PpTvaFz6uxrPupl5UuWnuQNJ4Yw6pZY+n3cirA5eLprfYsplDKh50hHBhLPOiWz3sRaqZW1flnVj9Ejiz8L4j7horMoeDuLuA+DIB24B/E8y7j0oaZswl+vJcR3lPu4d1cG/x+/GLYP3/l0W3349v7FUx+vvxExrNfj/+AsznR4ne/n58ar2Ksd+Pv2PTxVTl9WCDSlef2pT51YIx49lc3UgYzD43Oo2DkvUtm1WM/lZ9Q6Ppeilni0aTx9qzH5CZOejd6tNbWzEDVXRHyQGxzcTJD4/aJJbno9tVnP4+/g+dhr6xqAPaodKkrgoHGQ0wkmX3Th1rynKwqU/HPQ5tOvcB1V/vaUjnuQBGScx/e5dFh74=
*/