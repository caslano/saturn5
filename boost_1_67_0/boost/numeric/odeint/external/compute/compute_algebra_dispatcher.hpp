/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct algebra_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

/* compute_algebra_dispatcher.hpp
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
*/