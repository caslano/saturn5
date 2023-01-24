/*
  [auto_generated]
  boost/numeric/odeint/algebra/fusion_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/numeric/odeint/algebra/fusion_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>



namespace boost {
namespace numeric {
namespace odeint {

// specialization for fusion sequences
template< class FusionSequence >
struct algebra_dispatcher_sfinae< FusionSequence ,
                           typename boost::enable_if<
                               typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef fusion_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

/* fusion_algebra_dispatcher.hpp
WI6BMXwDm6FFCFTf1513SSzV47LRad6NuSTqZD6TPEev+nslzWN3nMf3L0D772uhJ2Gape6bYvQkGiu19RO6hViJYVX/84mYbJfwjiYupEmemNjZmojft45bFYdbYlcFzDJOcrtVkYid1fiUa+a8JlZFIH5VmLlELlZ6D3XunN0nZyf/rgE4DJlQUxv4qthV1hiw4d78J8hEqppqTNzKB3NzKdxBBoO7t3jkBr9zVs7OUwrNsU0u6KTJ4DuiDdloIzCDW7oYUYJTpC80nCG+0GJmaGKMyfkfooFAMqttGo+J/qE1Z83MRK0i0peWI8Zl7+GvDiTiCn6B72i1hgIIQ6MWfNxuKU6bLzZYSa2/NTd2g5XbkRkxfCveKLjx98QYo4AvRR8m/uxoFKi3fET+2B2vGBbBx9HVNuQjTFS9g1IcZzj2nY1FsPujKMvpdh5YBEPObBG88RG3CMh1Q0uIdAvN/np6jDkA3atZH8WQOQGppn3UzhzIfZQzMNInomYBMbBYv+Diw8s5MV/8W6Kx0YUkeZzGCcYhSs0Z6rUfEt0q17z5MvdiZugjYWi4MUPhQ/WzUf3sw+hAmAEXrOQFPAC9xZv7GKhRa6r3Q139LxGI3P0In/7lfPrxaFA2TL+x79AejwlH4/CQO0fkgY0Ckf2rzh6RxBhE8gDySKpgZoBJ87ntMFm0sT0mL8w7DSYintVA4elf41DQ4afG
*/