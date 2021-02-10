/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/functors.hpp

 [begin_description]
 some functors for the iterator based integrate routines
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

#include <utility>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {


template< class Observer >
struct obs_caller {

    size_t &m_n;
    Observer m_obs;

    obs_caller( size_t &m , Observer &obs ) : m_n(m) , m_obs( obs ) {}

    template< class State , class Time >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_n++;
    }
};

template< class Observer , class Time >
struct obs_caller_time {

    Time &m_t;
    Observer m_obs;

    obs_caller_time( Time &t , Observer &obs ) : m_t(t) , m_obs( obs ) {}

    template< class State >
    void operator()( std::pair< const State & , const Time & > x )
    {
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        observer_type &obs = m_obs;
        obs( x.first , x.second );
        m_t = x.second;
    }
};

} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_FUNCTORS_HPP_INCLUDED

/* functors.hpp
PE+oOtdMeWACK0vrACAtDODMAx6JRcoXfioaTkdhNJhOfh3NwvF0EpZsA62wPEuHdhTI1w8H4/EhrjmeAeHFaDYf/VZzHnGFR2HlS1iFCk8D/ELCM8VTUDV+ixcX49HlMBz/PgqgJbVath/U8jZg94KEXc5HXq+V77F4PqqEvgQO0c1G/eHF+8lgjpEJHrbnLU/dl5AnZ9Yfy8T1v3mG/Xk/gB/ImS32EgOFeYg1OuBPLYR2OZZUjmVqD0YLc3o+DUd12j1kfRBmqA8/JOrvqwr3AOBb1DmaPcC74mahTfkVYvifBdoGvkOt8az0DpQzfh/59uU5yh6225p5CeP5CNtrqDbji4qKyTXbWKhGS5wdQr1zK4RHt/Wub6MGPIUb/wBQSwMECgAAAAgALWdKUnGA82bZBAAABQwAACIACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjUwOS5jVVQFAAG2SCRgrVZtU9tGEP6uX7G4HyIRFRPStCWQTB2glMbFGWMmw5SO5iSd0CXnO83dCewm/Pfu3sk2aXDgQ47hJJ12n9199kXub36/FcEmPLgy/5/hwqvXeGf0B164+6Wz7DOEP9S6xOtDRvqwUvmcJfCwymeIvUrWWdmn+yx7yNAl+UZbnzQv
*/