/*
 [auto_generated]
 boost/numeric/odeint/integrate/null_observer.hpp

 [begin_description]
 null_observer
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

struct null_observer
{
    template< class State , class Time >
    void operator()( const State& /* x */ , Time /* t */ ) const
    {

    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

/* null_observer.hpp
+AT3DYcLE67tbXh1gtuW6cUJbjsOl5i+qnxViL7B8toa0qktXP4nJly9AMfzJrKFbVpH7LV+xcDNh1kk8l3IoHeF/svzz9TmdxvGUy7gTkTKo8p5XHlU+Q0pf5/bIj0GRRTY2/JO3nrEZMG3Q/LbcyRnRszKLO+LvDTS/32RV0YGvS/CcmlE+X3wnm4U83tjxF9R4fz+3xqpNPRZgGmSPyNkJzGg2MM+6OJhG+q7Tn4f6b4X
*/