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
f3x4V4zGmMdSiE0ZrPut7HnEL4mRDZ7fRsHwdAztUZz3MtlqYyIcWV0yYo0Yn1vi8GNjcsZN9pWvjZk7qs/gaAV3x9cbY913fDn8p5xeUQ0ti3lvj6+SMCT1n4urN3NUmx6L077Yz6scpj0e54cQNlr0XoWl8nePIL0Rd2KSx9rxE7i1roHYo+M4N11XabtNXO7ylriPHfKuQQfpT4xTn6yVNPbUuHlfwBK4HEcxs2fSHes3
*/