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
ycOFTLjer+yJ8UorsCIULjAefxLhLHIRweFPjmPkMi5EyGjKTR//KXGzdtbqwqh/JzTSbTVYoNP40+JWn8UaRPnG0+PFZnXN5/0M6osKCq0FnGHITlrrnvbMOM49XMg3Gk3Oxef/rDj6hZo5TYPCp3l2vN3BQYTay/VmxypCiA+Doz8n3jD1Q/ehYqXi0z03TlUsNGhAaJ+95xFuHAdxZFV9Ps83uJL5GX+B4OVG65THX6hw
*/