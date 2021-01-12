/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_operations_dispatcher.hpp

  [begin_description]
  operations_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_operations.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct operations_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_operations operations_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost




#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_OPERATIONS_DISPATCHER_HPP_DEFINED

/* compute_operations_dispatcher.hpp
j+R1za8ZEXgUf/fRPTZI1D4y7bFMu2WfMvGIXW+3G3uDUrlhytUNSdkez/lch23KTzB1r5XPMH+jdTcGpiEND4oARJ6oeNDYBX5L92s0Fq5zFJ7M9XoKl+fr3t6wnNkXoK4zw7IfhXmXdSibdjqYiMVJu8Vzi9Mls/k866ljFlvJHMomU2lExXZDuN0YGx7F4Qx/c5TT4UdZFqOw2cEyLzJhFKJRIuP5vtliuAXIg+U9FLZz
*/