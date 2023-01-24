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
z5PvN0EmutJ2Y+gGsAxt6bAI0saEGm0+a0jqsGCvzl1N+iDSWq0ZQdrZHJqTRug2JkMuX1StAHwPszTx6J7K3LSGuxPcAYwpR2NMOYwxDRxRr+vOqAQp8PgGmxzO3qJ1bo7cya5aax35SOtcalCv8Yff9c6t/Jw6t4YAfHf1QurcHHnCR7xz19zCOjdH/nA4TST5uOqWj15xiZ//eK/ZsR7ylMZSS8iBTtrbK4ouNjTIa6XXNlnua2O1tcj+D7XaXs2E/r9+02t7ZB/VNozVNlnuv4BqmyxP/5DX9s0hrLbJ8g5oQRgcivmbAr74+OFdds4CCdS36ImL2j7ErCcuNuyM+4Zo6BXIq4Yx9LJlh47eFobeHQHoDWLo5RKA756cz22/933A0Ysaotp+97azWZ1PquOH0OIFe1gxL+vCMe7/blN9k9MiDvnTLSH7hrif6/GL2v74/Y9fbLxHxBjyxBDFPdJ8cWKA5tbXz6YfEjh3QVeV7PY3IpEf0gIGRKuhrA8y5ar3tT4oYuaLB/16H2zeQ33w/R4+INrN4wMi/X3eB8vT1AHx6jAkEYti3vIIb/Cyd5oy4sxu0S6Zc0gLmDnmaqHaGVntxoAs+PwDJAuiTJZ4llVJOSWopvn2TJsk4jr32G6qWgSrmkVOoWU24v/+INUudf9QZpcqeq3AcWovz+mpmC8OIk1CZ8XcOq3hHZfymD71jA/s+E9Q
*/