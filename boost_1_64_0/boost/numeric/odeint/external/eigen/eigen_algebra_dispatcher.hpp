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
a4Wl6rFSdxQGEWXiydCfAPbll84HbpkDGBMwlCCSiafMSDzAiMYOx00WGBHFtu9fCJxwR1/6KBPTJeA/yYFgEhEl/roJQv/8kNcWnF0W0mMO+HfnY7fExgs7mO7JopmrCjeuzbiBBmukxIGioP+p/MblKWUWLZ65GWe1EGSMEq88mWznJDeaHNbNCZ0mLkvfm08TzmGus25qf/b92rSzsRVWRXYxF6moUdlzmYtToF6TJiPR7WK2dYBeYMnEEtWk4ZefsX43L6gUaYm5J1z11tc4cihbPzR1WujcUvGwufBoWn8V2sgJpuHVpZ5JFfEDe0ncAwokLqHQkSCMZR1hY4hcow2N79yg0r54Fet8ORrVnScOOvp1wpRdvWiRFojGSLzI78D8dfm+kueN+xuHoVKNfVmlcj1NDY5+Y0uTs+FvWSGx95NIcg07or+omt9Ak2lN7WhjGG3SfZKNk2kKEFmkXDhGH/1ijZW4InKKuy9xjPjj1Sm1+ru/+rGsPPll0hQ/BUHtaWf8OmorJfneiOEYEWCnFuGwbwOw1Gxu6M1NLcypvIotZvu7fg==
*/