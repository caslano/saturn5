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
WiP6PwKMXD+QU+yYP4qm9/pnSTMJvhoQk6l02SNGRrk/SmqshMKEBubsqlilhguNsd6ukpGqjDXeGsuTdg0GPC1X7a9jELQKRPclVLPdbQQQc4OhaKhUQhlpmsKLNH7ZesuNMGxVy+wPseOdai/OiMOSHUG+kjwembb3yv0XW8t4rDX7xliF6+fZ4DOSym2wDhvKBsPc+AmFp+wKh3MJpgkkVNAvrBYTBZHjUaXgTCa/wtXu97DzWyHA/x9GmFiFNBXQVB1ra6Ld8AROVa/TC2QXCNhcLmmwdH6Yz9Uloy80Ku/eTlpi/KNo18rzl2zn4huNwEFnsYL56TgGi6uc68PMeqrbVEigFq43BwsnYugu4SZ7l4o9GVtwBoh1qYBuz0FhZtqd4+KOm4vTd3wjeoZB8R3poi+ICPGxMw1SkN0yd4IqdQJ4dyQTzVuovN3nIYxv4SRL6nPNrB+dXsy44XpYN/RKSs5kFbAlL7v5FZ+WfCRr8ix0T03tdL56D72mvIMt+xc8keCAq9cdzWJSjp519tQjmiTx4TaZdBEeTjPl9tysE7d1kGtjtQ==
*/