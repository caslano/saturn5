/*
  [auto_generated]
  boost/numeric/odeint/external/eigen/eigen_algebra.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Christian Shelton
  Copyright 2013 Karsten Ahnert

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED

#include <Eigen/Dense>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

// Necessary routines for Eigen matrices to work with vector_space_algebra
// from odeint
// (that is, it lets odeint treat the eigen matrices correctly, knowing
// how to add, multiply, compute the norm, etc)
namespace Eigen {

template<typename D>
inline const
typename Eigen::CwiseBinaryOp<
    internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
    typename DenseBase<D>::ConstantReturnType,
    const D>
operator+(const typename Eigen::MatrixBase<D> &m,
          const typename Eigen::internal::traits<D>::Scalar &s) {
    return CwiseBinaryOp<
        internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
        typename DenseBase<D>::ConstantReturnType,
        const D>(DenseBase<D>::Constant(m.rows(), m.cols(), s), m.derived());
}

template<typename D>
inline const
typename Eigen::CwiseBinaryOp<
    internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
    typename DenseBase<D>::ConstantReturnType,
    const D>
operator+(const typename Eigen::internal::traits<D>::Scalar &s,
          const typename Eigen::MatrixBase<D> &m) {
    return CwiseBinaryOp<
        internal::scalar_sum_op<typename internal::traits<D>::Scalar>,
        typename DenseBase<D>::ConstantReturnType,
        const D>(DenseBase<D>::Constant(m.rows(), m.cols(), s), m.derived());
}

template<typename D1,typename D2>
inline const
typename Eigen::CwiseBinaryOp<
    typename Eigen::internal::scalar_quotient_op<
        typename Eigen::internal::traits<D1>::Scalar>,
    const D1, const D2>
operator/(const Eigen::MatrixBase<D1> &x1, const Eigen::MatrixBase<D2> &x2) {
    return x1.cwiseQuotient(x2);
}


template< typename D >
inline const 
typename Eigen::CwiseUnaryOp<
    typename Eigen::internal::scalar_abs_op<
        typename Eigen::internal::traits< D >::Scalar > ,
        const D >
abs( const Eigen::MatrixBase< D > &m ) {
    return m.cwiseAbs();
}

} // end Eigen namespace


namespace boost {
namespace numeric {
namespace odeint {

template<typename B,int S1,int S2,int O, int M1, int M2>
struct vector_space_norm_inf< Eigen::Matrix<B,S1,S2,O,M1,M2> >
{
    typedef B result_type;
    result_type operator()( const Eigen::Matrix<B,S1,S2,O,M1,M2> &m ) const
    {
        return m.template lpNorm<Eigen::Infinity>();
    }
};

} } } // end boost::numeric::odeint namespace

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_HPP_INCLUDED

/* eigen_algebra.hpp
ReFMqiQMjtMoSd+qHkJ19KrkkIyDPWrPrCiItqVOtyqCDNKhTtVICifMTRFglXKuREJYhV+TlkvduaGXntqzpULImdfpU2pUc1QxuPceXowZTsXguMEVg3uHJwyHvMwiYeD89D0CJKF6KCyNKkdyPWhOj0dI4roScwDCUkjIS95RVZzbBC6mYacTu2tNasy6K5D+H67eWInv+VY5d8ibmsj0XLXlVWHQcgw6D91aRF2E3Sf8s8YrDwwfxo9gVIXBnoL4r5SraYyXUZvmwsrtyDhQmzRH2zzyzmWCTrfZ9KkDNZWRIpl3fxrODItiD6n7UYOVWY2l96o25iOgyZSaYa01yvO5nSbYZgsmt0ua9w9XD5RTEc0JLVsJuP7+nlmEBgjOGEMHB3EALFUjCcbuMueyqJHXACMTGSbXMUa2DxFYhh4IzG4/YdD9BTBCkhclxCCnBMh6RuXBiORIGAzzSG6omHxQvFSTkuIaVuMaVVKOgwBg8lXsk4IDOb6MHg3+IoZt2We5Y9SKdydnNH6dHD9o0AdVfRpCOlrcFsRHNbZr5Jj1AVro8q8zPlhDlD6LuZ1ARoQm5V40fHD0b5/ECWAYYNXJkScZiTM8ykjuYUY1lic5MXkDkgGW/AXDJWo4V0bljMr6JI72dPB/KGeJWsLgOIBl+gDx9QGrTAHC7MiSoAhthmwrRqtD3usADChXSt83SIBmrR5Mnt1RFN5y1z6nA+yfjU1WGmcMKrNvcNZr9ij0SSnJYO1MIRmsOQTJ4Moc4uLJe0ZKAkeTyvQsMyBhcJxLDv45ulOmdw7m1djphgcb+9MhexE8jnbBSNgzb8cxyOCscpGE4lZ/Yvok8/qMsbJLFqcCfRoUcrvz/A4yb+5dUmHeJlJiKqusMrFGERUs0GE3gZm1wk62Km95mxvJl5xXGXcLq/5WWAg7aHjNYCVjRMxQ5jj9StSJgZTD0Hgpg6GR0O/t7fK2ukgovF45YTA7ZUlhbQ8hGdTtIQY5vL0SJIW3JYGksLYkSBmMnkgyWJsYSAZrEwPJ4G1iICm8zQJSCisUwW3gnyXDkhDWnVUmJqjOG8nhCGQD/zxxTBgsyQKB49uT6TlS1dibZWbK9BwZbOCfI4EN/LPkLyGwjBvJYMlrQuBJK8JGk5k8hqsxoWDpQ4Vx6cDAJrTVgsK1MKYZDpVn2VxJccLAqdIDQhWD20iJC4kj4KAc1MVGVQdGxnjYAUrAv3oIXeMzVl15HAp5Ujmh1OVxtZhlkmW2TNQLCwmr8NY/IHNYytxrAsZKTEqbLyt4MRkOW7ocvnQ5fOlC3Tn3loPYn8jvULsPJ8Y/p9uXBLkimrx1uKQw1p6q9JETU/ZenZRDHhPK9AxLRKXHHLfv8KpBH6b2LgV1tYJMz+j5ZXrGTJv8oBtGTsAqDCKt5Vs1Ij+vo8+By5Q6yTHAofuj+ySGXdjjcMLi+xzGBuwZh/DkuD6nFSRvnHXmPQ4ntKzH4YSKKU71cEYurQgvznLMlMHaXqfPIUtaSggOCcnXRVI4mxf3GAfa7Ez8DpPgkfdNUQzOpsp9Rps6G6UYnE69xyBvKZISGI8cUAzWZs9OskzAoS9FUOl5SxEUh7cUQcVxpR+cVrYj9Cucvd8Ug7UQRVI4JqAiMFauKAJr5UovPAwt3Wwy9hCelNfyI3qlBoisug3yHPLy/0l4jM2LJ+ExVvb0eP2DIsY0E7ygRvUIUPlBDvfoczh9f62Nf0YfJtPLfY6p5pJiHNIJC9n5b2LQezHG8jNVmugg8rZVPQKvQaOGX+flgEdZ81qUEWKjCAHmjAsZn/P8Rb3M6TaPYiCCoZDSTlSKm6cqdGUabwcQ2SiYPKQOHtI=
*/