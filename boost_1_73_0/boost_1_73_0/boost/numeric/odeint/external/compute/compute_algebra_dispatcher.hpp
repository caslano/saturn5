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
HPnmYDSRge54CVfLLqyZky6Bj1erd/MPK/g4XizGs9UNzN/CeHYTlL2/mv2ZAEoyZgHvSouOjFuQRakk5o3N77fSzg9Sc1XlCF2PjlLV7Ty5oipQ4fp4S45qRcQe3xZY5LiutlGF1JRdEu5xwSwMPiym/c4/HYAJnbjJQ+15+DV+vsnm70fNEwyEzsOH81SPWdCQeVlQY/T6ow7dhwLLtsqsmcqklr4XpLLL6fyP8TQbT6c1ipSQ8ohF5g41sh/0yk2PHvsQuMAJwqGnggxvSSQyv15ltCUQmI++ATybXy/ml4s3y2UCF98mMp6uln9NEugqs02Z8m7Hzy5+Pv+p20jXITrqoFLeGFtEB6Kb0Z0XBGv9obk3oOb6TI0Seyo2AhfIP1P1UpvG5o7dK1g4+DOyCYx7uWOhWqkcajV1LiLylEFelYJUKmw41GAiEZBHEl+nHnGjLzBiu0fgyjiM7eWQGx2GU7BBTWadb8ZX9MoBNbTzxtbohv8XbbTi4DNaHUIrb4mE2aHdW+k9zdi9wHo8arzzrREKSLSfvzh6f5o4rpDpqnzM/KFT/z5JMjUr+tP0kH+Vo+KtnWNFM5l1PBl76gVwRolK6hQRo/WaBlcAtJwoMuSEh0+V89C6tLHNSHsZ+L1snWo8+a8X
*/