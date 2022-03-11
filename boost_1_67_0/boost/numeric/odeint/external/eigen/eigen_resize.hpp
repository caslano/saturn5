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