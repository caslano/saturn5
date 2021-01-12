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
Hf9FPp+m7qMXG7x1Epum0lD1fkl8HdUpgZd9GX9pHOuKzJqYBDr8mI2QrsfLiG4nnpFQkAX3jfdyzsdsPALZeQj9FZZOQn8Lm9Fa5zEznccrLY9jromjpk3Ol+Qy5cv7qnilVqx2SrIZUOlfbb+BQ7N3LL7G0jDruhAd7bVxHJ80TFfrpbOqzV4Xt2uo/sbr4ziNV1HiVvHeED/ZXFXhN+J8p57BqblaKfkyvMnh2APa3+bN
*/