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
mkdE2WpllL93cwJBJM2RmoSsTz+MJK6+72/5jCj1d0h10P/eyVB6W+mBKDaa+ZiFKlU5pCircoWDnSAqSPvD5LjsroTRWil6C+Kc/XBUdKYhcQ6HxFfyoZs4bX8FDtlws0bbNeC3eh6KYjUZRjWJZgKxWpkgxpPuuVXnPXK9CQf5345xUerrkE7gyxuTsDI2abZWG7zeAklDq02t9u6yLe0c1sRqcpxTdjpyd2aElwXWig/0yzfyWglYq6SbtFp1uQmtRuf8g1oNTqBBHTB65R5YOVqL4LWsmuCgmFdWkAFJYoO3tYwrlQgh5dgGg2uwu8rgMc4Fr2IehYm9MWf3CsLK7pPxynpPzAgE3pjjH6D8YbSCT05IwuE9nCKGYPyGMNdod1VYpfEO8LCLQGJM4PQYe1Ai4+69+HVMT5ZXFcsrhgrofhUm7J5IniGtMf/Prm3IoYPsD7L0Fy3omRTpCJvYbJ6F2XIcPYlRhVczYv+MIqYlaPRtr660Z+KReYfnwcPwv0b+hY5sV1HqxIapZdGbVcPsg2AoS3hvx8o57DnMu7FKXnNBPVYpo1ae8af6wEmGLLc7Q56s2kBJ3JpUGTTwsmoo7Rn4cBuuDaR60Wunx3zirVs6QzuS/Joli5Xl0KZLFHOHT1GnehwPLH6J5JiVCcu3lYvo7oZJ1VZpf9KoWmnY2aTtuCCjZzTatGFxkHGmqF2v4vBmZLPn
*/