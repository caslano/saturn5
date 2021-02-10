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
CgAAAAgALWdKUlIil8VFBQAAuwsAACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjUwNC5jVVQFAAG2SCRgrVZrU9tGFP2uX3HjThmZCj+YNC1x6NQhTsLUwYxtmtJhRrOWVtamklbZXQGeJP+9Z1eSeYSUfogBS7p7n+eee0V/9/t9PNqlRz+h+wvxwdVZnCr5gUfmYe0w/Ez1D6wucH0sSJ9uTD6HXXrc5DP5ziRsoryw92H4WKALm5v96lvLi9DeQgIza3kky40S69SQf9Sl4cHBr7RH+4P9QUCvWCF4RgvDixVX64BexE7ye8qur3ua/xYQN8SyXuNqmQpNWibmiilOuM9ExAvNY2KaYq4jJVZ4EAWZlFMiMk5Hs9Pz45M3AV2lIkqtk42sSKeyymJK2SUnxSMuLmsfJVOGZAJzOI+FNnBYGSGLHmJzMlzl2vqw4VmmJbFLJjK2QiBmKDWm1M/7/ahSGbLvxzLS/agtv5eafFvJOZLI2YZkachIqjQPyGoGlMtYJPYKQCAsq1UmdBrcZINQRdyXijTPMusLdoLrOm1OiwaewKpRiYyFsRctC21DXaUyv6MIHK2XpFIFAgEHKMUSMAdUFTFXTtlV3oZoMHUAf7M1N/nGJAskQ53xgo4X
*/