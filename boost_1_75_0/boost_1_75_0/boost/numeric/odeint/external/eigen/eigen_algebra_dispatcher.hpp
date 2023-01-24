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
zV7dQ5YfhxVz7TbMWxZzx55FnvhsChmYreyB15cNO2t6Io4elq0R1+6MiBPshb+5rkb+CgACLP3TRdx3DttvUrU0rOb84a7K+a971kPj+/ugHIy94DVfkmCmUcpsqdeF4bHnMvosvy3HjEq/ZhvrEX8EwxaapetFRSlUTJ4kPN4/9LLeSc+FNeik41CGbzf2RsZxucNp0mfUkOfZM/RubvZEA4t8lPltXu6fQ/7Gbb7wODLjSpSfodnXfUJtUXgaJyikHU9Wpi1pPmtqa9tK3tYvRf19W9+0W23rxz7Btq5V2zppAGvrpw28rSUDb2vbyuvi7IWKK4u39cWz9HTJ+GYXd5OqTbHGHYcE4U+raXErKPTELrYK29efzkSPgeg7INon0Zq/Ci/Fn7RK7R4D6x48JA+F7YQluP9JlD28DYucoxXpnw6FrOSF5LNCWkMhJw7Cx30hzsnjHHrcJoyLsQ18oMYVDd6vDnJ006V2YlJMJKDnapsu3RYFnrBDuLm4Aw9T2vBhKlRCsZVm1Q7WmvwhrhNbae0Lg6XB0reNhipGVze/MsYJWHsVKCfgIlU+D3bKqVOK2Bo+WncayEkJzt0NEyUskn6/m85a6foWmGPiHJ6c+EC+lY4PfrDbn0/gBZo9FlbD/8PwX5azLujEvtWgEbs3G4h9EhB7lpwu7VXM7Xbg6ZG9JNvgrXzAk/ZUEk/6sY54Uo187HeN
*/