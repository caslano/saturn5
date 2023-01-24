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
5rebjV1UKu2RizsJgj9apLu5Zdx8LuLHI/ibp1uMeJmzcRbaM5KNyRWi+1ScuwofYhwa65YNi1uLUhv+VBramDRsD8CxPb2UcLXoHSmLbn+cmLbHaXfPjxUWpOD7SgMNriT5C3p/pQaaBfIdFev2GRbH0CuKhxySwYp5e4dDrSL90TZpaA0+wtW+C1sKJdMF604V370Bb97OVF8qpOdH8U2cx2iplVNDb2W4c2Qh5aA75zjdUg/ewwIdxFu7H223aQ8+qbZQWTRBlK6URp5NGlqbtL9t+cIY1lbPd8Lyr2Q33rMM8MJ7h7STzqPh8pwf7BP3Y8rwtIKzi6/1FNAbdLn7d0YYBH8UZtS9NUY78WbbCnVtZ4GGx8fe5MdmqnYIWCftDV/RI0ax90fVh4jrUo55smV6PE+UkeraqU+pVqGdZkf5VBsshj2lx0Od49ljIYxiIithtU+GB3QkiR3VSu3WylWLbxN0RLJ14EswrPm3ksl3Jb+SFxVNEh4xpLdFOdFUz9DfkI8NIFd6kJwh2ZYjCRi2k8VADOl5bX7JSeRlfldzMit9j/ytgQgV39Vwb5ebocYgOt4b8HbKue0GZ5vSZKiq/EV/thFOj6IEvcnA39g89BXqRwyEON6dzZ6fbqWYJ+wTBMu5SoMzpjSOltd75Ed5Zg3fy6S7lrXL4ONTfkuXTltRvViHz4LdaCoO2/I9jNM8tzw2r7Dc
*/