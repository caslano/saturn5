/*
  [auto_generated]
  boost/numeric/odeint/external/eigen/eigen_resize.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Ankur Sinha
  Copyright 2013 Karsten Ahnert

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED


#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <Eigen/Dense>

namespace boost {
namespace numeric {
namespace odeint {



template< class Derived >
struct is_resizeable_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};


template < class Derived  >
struct is_resizeable_sfinae< Derived ,
                      typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};



template< class Derived >
struct same_size_impl_sfinae< Derived , Derived ,
                       typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{
    static bool same_size( const Eigen::MatrixBase< Derived > &m1 , const Eigen::MatrixBase< Derived > &m2 )

    {
        return ( ( m1.innerSize () == m2.innerSize () ) && ( m1.outerSize() == m2.outerSize() ) );
    }
};

template< class Derived  >
struct same_size_impl_sfinae< Derived , Derived ,
                       typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{
    static bool same_size( const Eigen::ArrayBase< Derived > &v1 , const Eigen::ArrayBase< Derived >  &v2 )
    {
        return  ( ( v1.innerSize () == v2.innerSize () ) && ( v1.outerSize() == v2.outerSize() ) );
    }
};




template< class Derived >
struct resize_impl_sfinae< Derived , Derived ,
                    typename boost::enable_if< typename boost::is_base_of< Eigen::MatrixBase< Derived > , Derived >::type >::type >
{
    static void resize( Eigen::MatrixBase< Derived > &m1 , const Eigen::MatrixBase< Derived > &m2 )
    {
        m1.derived().resizeLike(m2);
    }
};

template< class Derived >
struct resize_impl_sfinae< Derived , Derived ,
                    typename boost::enable_if< typename boost::is_base_of< Eigen::ArrayBase< Derived > , Derived >::type >::type >
{
    static void resize( Eigen::ArrayBase< Derived > &v1 , const Eigen::ArrayBase< Derived > &v2 )
    {
        v1.derived().resizeLike(v2);
    }
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_EIGEN_EIGEN_RESIZE_HPP_DEFINED

/* eigen_resize.hpp
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
*/