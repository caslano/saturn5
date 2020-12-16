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
roOSxXngO2kz7zo9uN8+vwoONonXafY8e1TenHmZCz24iJtlZOroqccePaqMxWZuPKzyjYSwAfCKNG3YBFz6rf/z6BBhj3l5BlDeT7FDHw4Rd7tWjhzmrrAus6LS3m9Em8KLRFMoyttx+f6tyclYmtep5ycx1gdWJB/VAS0mtKE+3pTxkl7GIq2TIAj7ZTyBZVTHVTokFWGscfXGdSrdHh+3b1XpcgxQrPZtQG+PIyDPVyPbWzGtMc6P7mjFWmei+vd6X4f1xMtSz73Vvp42egGavIBxn3FhGKRGX5cmbOAQkj87iB04XARzUXc0eXv/73V9RDf1UniarvSzyX8+7sj9gyYvY0mW+TCuY1Pe6n846Uj/2qq8mpVlHftekWlbKntpGPLkuP6Drm8Vx1mSpSHy51O8XoSPdtpWy7T3aLweq/Kg4t7O+X5EsJediy3sXtP3b1f5R2CV9fPSyxl3LtDk82Izh4yo2JrB2u5nAboEtfdr9NYcIx+dA3M/rDx2Gr2Vj8o+oc1dnov8M8gv9zo5d+8YRsJHY6sQWsHdpj9qMgIWZzm0UxqwgWfQUes89HZNRs783HG9oE6svZ/esX2seUvP9uOavJDVQemUhZNhhXI11bZ69dW5KJNvJ/ZcdG2DSrfnmqGNnL527KirbRicPaTf/98be0jXLTzu0z0XBxKhqzsKaXOdhim4esaCrNuP/BMbyG8IvweDJzNZ5we0eSRnqZflbu3e8l0Nfzf+xAFYo2L+bsy/iuc5NAPtx0b/1iHYe3YW4Mms232hCJ1+nnzqwV8+pBktArviS2adpNsK0qpvsQ02zsQ8YZOOITF05/76LRyjWqEoMaS2AU22WVKGlWhUsoncbtLl0iExF3dYGFwyaI6//LthzadtnvlFGeYVtjsqX1xYWVrodwLU5ZhCHS0m+mozPtU+wGPb9k6MzD32OPlR0dLKWJT6RRRWzq32A6ln/Tt9zg7qMAvzjDbV02JnPQYryIj8hmoVTV+6Rn0JCiS7kuhLvzoEaT2Nv4j39bV5mrvh+6/pe+yMxyLG/W/lN+wD2N8Krb+J1xxIR4kDuI5jVIsn6gOzG4EG/UPkTEwlon0lPd9EdCFavDwR/77NBl2wk8+/uwS9MRdS4otu4985lnMq8ZG28+8txkJDxAtxowADt8SClfYwX78XfOd9Ua3QFvtktqcVB12fZN1ow1D3p5h5927BGbbMX9/bgjHixd11H4mRjW7aDV/dZ2PQJljm+9n3tTFt9r5n99s4097Xv5+NMe2djx5AzBr2zgfub2NQjhjX6znoZTvBN9HkC2fnVuaXl5bmJ88Ls/Wde5X3vHLoqXFyOq+rinzdzKzXvk+6cximRo13tknHhHMQulKhX92i0xPh/YfobKtObxLYDeP7oQ+E/vgTPkd4Fzl2G4xTGKZDq2P9/34w/+8TI1LW1+GvGjKKqeYF/uohDBjJn4Y7vdXnzM2IOSGEtM4kGEUS03qM+DYk6E/o04tgIq58oKvr/5M55cxEknMVKDjEv1B5h7p7fQsdtaBUf8ozP9HvGFPPz0K/jFkF8ylkV+pucm1GfjsowoRemJrGlfwR2NbXn7+bt/UkJMUVyiZXpsBVlHhqRv1f0Jne3+x9hpX5/sL0PHev0NDu0midJfC3KGmf0WhCMVHSbmq0C/PQ6yXtFxoN5qEuyfywRuOLCNFuaLTlVeCTPpjfrdDEojUzt8Sdki6Ay7cXXBDbrQvC5RDWT+1s5fUjaZPzQ0t7kcY8QWu4LjTpH1XTEDce8zBG8D59nUKLOr3x3kwsApKwEZnHa0M6Jlh8wRyo3S3AkvCUqZU5ft5+Kjt2XJ7hbxp4DzaeS/M=
*/