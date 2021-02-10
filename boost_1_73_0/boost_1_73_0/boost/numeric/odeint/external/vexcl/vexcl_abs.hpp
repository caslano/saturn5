/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_abs.hpp

  [begin_description]
  abs() specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/operations.hpp>

namespace vex {

template <typename T, size_t N>
typename std::enable_if<
    std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        abs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            abs_func(),
            boost::ref(arg)
            );
}

template <typename T, size_t N>
typename std::enable_if<
    !std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        fabs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            fabs_func(),
            boost::ref(arg)
            );
}

} // namespace vex

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

/* vexcl_abs.hpp
6BhPtB/SLzS5GI8HjeUd7WcPTC4Yc4Wld/da5rnM1wMP78ZiKwYue2BlBmurXdnXqVqJNJC5tC2XNTgdT98Mx8FwPK4dWJhtvRw+MBgGMzD5FZTpbBnM5tM/L32cIKuqiNDrw/aAuvvYVtbRHEsNIYSu0a/mwM0n1/bgCZ/FaD57DzlXMnqFTvaecq9g/c8YN8EqbnkxmYwAqf8korPR8GQ0f87rj9H8zXQxatzgV8mnZjZ7aBFRFCRQSsqtDIdYvRQr3RoM2uTk4IapS3zWMEjeiLSWIB4G1WIcueqkI5zRGrv+JqztThGZuIkjSOTg6KhKS3exHbtBmNNYf/CfhbJe6TUxNU6cgUCVOZAvGqW1Gwexwm4KVH6nN1albe1WZdz6bhfg1V+8lWbxd6WWSGF/u83gzG9Pgr9G82nrhY7ag8eWa/25BY22HwGMI/BQwwMXLxwZzgl/Kxp2zig6tPUXqlDo2m9Ywvu6FFqAh/oQXzGtgRO0uLOTP5ag3mJSdNDv3EHGRwT/cVSNt+o8P1D/CxB29D5LGdEnz6uMYcoiL4tXLgCgcZBgBNRYUfhjyTmOoQOy24JpNmwwua9nUDOiOcNx9Jm6Hnk02SpFNguVnnf2BwHNybFbqRvRbPHdcwfRwPvk/QtQSwME
*/