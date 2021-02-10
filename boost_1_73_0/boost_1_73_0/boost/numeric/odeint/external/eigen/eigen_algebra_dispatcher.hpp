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
2AwMU6W2GDY8LbQEekl5QRcYiBrIjan0Ya+X1KpA9r1UJrqXbOTv56bcKpkhiZKuQFYGjIRaswCsZQClTHlmn5gQXKzqRcF1HuzYYCiR9qQCzYrCYqEfZ7qhzWCyTk9gzaBCxtzYh5ZC21BXuSzvGWIeLUpWK4GBMA9olEpMcwC1SJlyxk75JsQ6py7BPy3Njm8KUiAZ6PQnMJh0YEE11wF8HcTn0TSGr/3xuD+KZxCdQX80s2BfBqNPWHqOwRSw60oxjcEV8LIqOEvXMX/f6HnPuUiKOmXQMUxjqTreD0t4Cgq7vFtFoaJAYvdXS1ambFEvG4iUZVwwqBQXhjClfEFLrAxK6sLcA8jcTuZrg4lWAXTiVcWg5LqkJskhQ83hdDyMLmLyQoOPftgeMKEvdHcuOgHs4I48D5HAUvWTnCrYQ7+u993r7UEkipXbAZ7B5zAEg1GSnCXfuFjaWu1OMaYCwAIhHQx+DAdHKC5DHY7IYBSSeHZxGp6fhl8IQpFztE/waBnActfYu+zhJ4zqFR5tvDiwJ4+sUKl8iXDbXdJsE8GujT+aDodda2aH3E5+ai+7XfjurFBdbIXZTG3TFo3tXFtxW6V42xIldSMQJWa+hXZbpJBiucb35euPPO3Cs2Nv093skoWB4+Om
*/