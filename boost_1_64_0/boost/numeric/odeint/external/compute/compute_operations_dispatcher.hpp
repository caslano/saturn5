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
lNvIvUNvyUCbCmgyu8BidryURmwLoO012XBpeGVO5cuZdCE+vo4o2JlqnHw5mnclSfnVa2mpOBWABVRS9VJ6oLcXqpaCL2iPvA4sSK/dUQLBR2E9mqPuOangDv5ofh8EkmN8MyFcLTi0TSYVGZduwRSg9kmI/6uhsLGmKQ5Y/ghYziC3Ei7ToDNjzcCcSxq4RmayrgglYsHX/mtAXYse+v1DG4nLVtq9jrRJ0i9H0EtFKIefKUuISrbj2gMXUc9ParYG0ir12BHkEIS0RR9lrjmA7ykxgNbb3zXRULgOudCrFKq6+tBniC/9czvmO9n2+CEQA7QUJworX6xwYqyQM6wtuR2NUf6vqFg609+wPrVTvd9B1X8bRjSkdgZ3bKniqB00grB7NN0cPYypppWvtQW/YSh+12XQ3lqh2hqC6WB6Cz8ZM1vyyE993toIN4MFjd22jhO1qx02rj6SjZzW7Ob2jrArA+6QrYOOc16AsGp4nEiXVa4nVTXtfGP/NL60LXSwdsdqcU51rcWJbo5GIjbbWL+8MVDXXNE+hM8WFd60YuJQEN1vcsiBhQ==
*/