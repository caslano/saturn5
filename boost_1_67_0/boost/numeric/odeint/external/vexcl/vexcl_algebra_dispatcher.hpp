/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for vexcl
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// specialization for vexcl vector
template< typename T >
struct algebra_dispatcher< vex::vector< T > >
{
    typedef vector_space_algebra algebra_type;
};

// specialization for vexcl multivector
template< typename T , size_t N >
struct algebra_dispatcher< vex::multivector< T , N > >
{
    typedef vector_space_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

/* vexcl_algebra_dispatcher.hpp
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
*/