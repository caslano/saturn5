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
YDUmQ1I9xlU7WXTHUWgooI1iv7eAZk5fGOjtpM3eLh7pV6FKvuLh4hYhMGOuYe6trKopIoidtY1PKTpjjPyuYUlWoWeqz9tIHu3WdltyjTF+KLnEzDaBFN6MbUCfGm0/pLHEQTFLJeeRVSAVYeKdna4xqF6TrhYB5tlxhZPcXIA1+uDLmzUpB+vK2O6TpPSB/8v5lCabbT6Oxibvx69lFejv3NkgKvZz1/19Z0lAqbLqS2kfGDwg+DwzteZMcmICPaaLFjnz86JzwtLXIfLeqG8RWXA+oSzfvGiIGsgytrnscfCkvyjL2ndhC65/m3m+IQrQrPQRNV1NwFF6bK2i4c3WgS53xHUmdwx/QQlBjpLbAo01o/jV9WyQMdjvbMZDgg25A9A/ta9PgK7XN9BQTTeQSRICObHAJ1OfA8ALcNLjoYt7FiYERzWCG1VRNL5HyGjxfpXnm+pNUwuhgEYbGDVdEbyX+QnsmHi+Be8EuvOp7FL2zeryUx6Jp11j4r8TbnID8Th/seSFUytk9Gn5hguge1ZnUu03gCe8Mpb8PpcXneh6ozgK4J93DA==
*/