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
N4Ly2lq9+ztrUCuQkiwoFoJWu96k9r4l9vnFAJEzynayTuOGB0ZQKrQLMmgUhv2/W3RNJPDiuqTnhGAstAvvYxzZRW42Oz/D8aOCJ5eWUCngZJmY4Lg5XclY/i9YZiHJe5ZNHkuiKGn1R4LlUfBLoTzMuiPBDxmhL5tEDs1y4UXqe2HaZkdDzoh8LSV6C42nkQdyXbc4nHnAXuQBl2cecA/iATSXsu1WI1u+OzMChVg+dVDs
*/