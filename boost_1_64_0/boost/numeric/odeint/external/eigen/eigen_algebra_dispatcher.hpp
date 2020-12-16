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
9GTjXKbnBIFIAmMIJNMzbEyV/sCQ7ENQBMi4Rx5OK8r+9UqrCElbnRUCnObt8NrPOzSgTjr2CUXUbeUx6sbthVyfaoXL9JzZA0lg+HFUeoxvyVFUilFr+kytbEeFyB6uz/C2I8XN9a+8cm7KoDg9WMlvgFMpMk5h9fz64tWLK/2q+c2BVi1wd6DV8qVfbRw1Q9/QstbEA3kr6QfHI6sYWJqoDqiD9iEauXeYpJh+K2AWc6xCqo9CJlgmWfVe9M5IK/EedFPz5YszCkgYEbxSHfJsbErhLGTrUQg73EzK4DznsE8h3yApwU0Cjgp5EF/SipV/tiopNUB4Y0xVEfRy5AfA9yg1shevx7Ad8ur0VBw50ROKwomvUgxOfFWPQfZ3SEKdLfBgMJsX8wO1LtVxnzJAYDHkrU62PBMGWzmwgpoVw+2SH+UqCZznxtfq+Oc4FCWB5U+UDIY7UaZneNxkepYz0Y4Oazt726HTUIdVqCdin6Co8p1jNgzSDrHJq2QyGidqu88iN/lwg1AeyNGjwhuPR58fTN7vJCUwHmLeY/jUyVpF4Cy0Ugxc0TYrj+SNJwYyGygAhqymlDpVW6aMGoJXu1STQnGwimj/Dl3KQInxznjUQsaJD6OqtD4HAQcsoUw4jKCDjNP2DmFz6iHVFOtzGCqxz2Fsy6M47PssZt82MUQtJnsQJCVYnZ1LgO1m8J1sX/VI2N3lYGqPnnIYO8JIBn4nP9RcEdi19ytuNaA+0r7PIDuOJANmQBz6PAVYr9KNGUnAGnTOBK7kuBWfWXkwmJVPbN42PTCkx2HXReokwpOEhzmtKK6xtKwkdciPae9xOM836neBqBGrsZM3xiimz2FEavc5LLsp4TC3n1Ak3qZyioN+s07diLfPcGJWl26jow1417MacyUg0RttpqQlHI/qp5YU1nIcxWCNtVIKQgg9LgXPKCAHHqacVo3+ZABF4WpaENAF1FlmllyPw5Uwt8vMg7WRRMqBRmfXBWYJo5ER/YtX9ZCQHCKZUhjRKCmDE4fSo/j7F/I8i0qZ5T1Lc2eMxlMG/G1hIQVeeazy0uNnUkYaOVNfc2/XxU6xar8fBH1GqYtTejcj98DEw5n8tL/rr9CgJ8et20t9sBN3Os1o76bd3h+MbJOhZA3ZwbbftGt+048PyxHwEDIch912oqDlif2VVl9170NbLWgGKDpyebyD2zGcuQf/PaHb9uu+5yI3mTi5jjimloZdGPxUsyOPkx49eickE5Kzx5FLqUC6zVOyRVfojWJgv+8w7mJz4NDZG/dxWm8n6EKvRQFZhqCZ7CY6NM5FqB6iLHRy3XGVHUSWxo3Qs7FGMfBpuSU2Ayklwrzh/SAlVSUnJe3VFjMiTnBYtZCtzPqPSsg/DcMoF2HsoJh6cUBAmt90cTPiCbAR6FjIhvp5zZUquAgeBhYQW7fkLLtsyY7RErVunMyhIB47wGxKWOqJ3tLEC4ufupFHvwn27/ouCkFq/ih2Yf4SpB/tAgI6WWn9BAHh3AOXthNSVFz/m/TKKEFYIbR38hJnZSoN+Yu/8t/vePDP2LlHQBkbCCvuAy9UCqIed5orrYA4CGOVZfL+TyvgJ1HdefvqRhtsvfWGG2y0VXWTbXfdYsfttq3uupKxAF4j1U4NhNFBzlbeH3PBZBauK57MTiAM1rPZRPQWvZ6tFirIzSFqyBzYrJDNwqwW4nXGoYVeaxwatZBZzyNVsD2xKpOGKxvFB5JI+0f4R+hm0Aljcv8GOwC/QucQFInKIOoGAXIgyJushVwk7dT3p6bfv2uHLiOTbizNsL2xaVgVz+yoQtNxaF1A8NbG0I1ygaDxdsg0XXo6QsOheW1stAI=
*/