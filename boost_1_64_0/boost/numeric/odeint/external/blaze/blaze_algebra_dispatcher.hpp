/*
  [auto_generated]
  boost/numeric/odeint/external/blaze/blaze_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2009-2012 Karsten Ahnert
  Copyright 2009-2012 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <blaze/math/dense/StaticVector.h>
#include <blaze/math/dense/DynamicVector.h>






namespace boost {
namespace numeric {
namespace odeint {

template< typename T , size_t N , bool TF >
struct algebra_dispatcher< blaze::StaticVector< T , N , TF >  >
{
    typedef vector_space_algebra algebra_type;
};

template< typename T , bool TF >
struct algebra_dispatcher< blaze::DynamicVector< T , TF > >
{
    typedef vector_space_algebra algebra_type;
};





}
}
}


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_BLAZE_BLAZE_ALGEBRA_DISPATCHER_HPP_INCLUDED

/* blaze_algebra_dispatcher.hpp
Kbqc2zutmtzG4myQKRVRGQlstzgOvpM5tddNFa5auPJhp0hnu41C85Xi7nS80BIYnoPLDHFN2P2HHrGDo8QTd8/5llqfCAzcP0c6yBPMhy0P0FqX/c/0nwdjsP/yGEtQHw6spI+4VOlrKzsDvriUNU4AA2oLkq7+R33rz9d463xXG+0VJlRFSF8sEVmU7vZZ99Au5L+QxrqY4B8klj8Ur1SRphPHZWJxjJkibF3SWUBdnVMxju7n9+FJ5/+JMt55QL9kb3UqINbbkn8iRN23D9QZS1GYNaowE+NtgelYgG6SPxd3NxU+E6rhhrUQeB03k5ZeCxo04Z7FIaDwFmowwWhHJGU/VJV93YT6c6l5yRUCcgHuSdEyg852EnfTLV0wZROZP/AxefzZ5i8JTME0fPfGA92ENhIbH8+yXYUv+5kKEUVtVSQEekCUh640qSp20h6BN4sv/i+fyDIRsbzIKgNbbQqkChxYYfvoJlzMVgNpJXnLb3UHw8O47CUzFkBmkc8ltVmRVJM1CLtZ2/jvIeQTVHS3rbFPs50VuFHgve0t+k6K7mgQPwzQBg==
*/