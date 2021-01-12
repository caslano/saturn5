/*
  [auto_generated]
  boost/numeric/odeint/external/eigen/eigen_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_DISPATCHER_HPP_INCLUDED


namespace boost {
namespace numeric {
namespace odeint {


template< class Derived >
struct algebra_dispatcher_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{ 
    typedef vector_space_algebra algebra_type;
};


template < class Derived  >
struct algebra_dispatcher_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{ 
    typedef vector_space_algebra algebra_type;
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_ALGEBRA_DISPATCHER_HPP_INCLUDED

/* eigen_algebra_dispatcher.hpp
i90RtuwGjX/jdz4Omk/PLx1cDvLIwJgfCjaXxpUnG2i+GKah0VP4tNCIm2Aqnoch3Nl+4x7HRaA7zaYQTacb9TQ03dq1YIz77kVuLaAtkhL+NITV1+u7+Nnp9f0lvL6/lNf3awLvQw19o3AmoH0LbrpalXqtBedpnzwCEHm5avsYUJwT5Vq5WajqfbKC1T5Z9ujU1y8WH7Kw7BGHV3LZXqVlM043rusBEXgNx32tyHQjiShS
*/