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
M3JE8tAiy6+OKRwbiyRTht+CHiB1rBP+2ULn4Svpi7a8M2DWjJPdYpG0cMlNi/G7k/gQrcHAEOmEqG0xixQUj4//S7qYqdvuAkmdWp8K+ss09CDPfYJ+YP38R3W2U2tSeY8eJfO67pzVREbRNCBS95PUr72/Y/wO4mqAZlUt6GuUxchFliW4J5v5rqWfkREJYpH3Bo9U+RY+MXxoLAUvsF0aOarKaq7gG7GpNXXKa5q5eCPYPNxITxqO5Ubox0YHWnICUGMsgmbmW5s59q8Rk878gV7Jds1xXW5azLbxbXdtaqydtLKj19jZFrUubpaWrmi/pZHXcgvR0+kLHhB1SenyITBYcbPnG9XoBRVOL84BLV6tFqca7V6XwofETH3W0roUBZ6lmVPaZwHrVJEUqGjs7o1WTsbK2jP4y1jfGi+XrnslOoDqEJTdj/dEBb5H4AyiCGK+FYE30nia0lCwHHB99hXFZsHUve9gwYl4zXHtKC15OFZpjd3kHLRat1hYXIgQ0sHHyeEdjBU7JPw50jhfWX7IM9MbfrB715WDeptDVEIqLMQLk+SAU+cj3kHnwe0b6sHMe2rNu5SaSW2MDBBaZmBgrgNOCrRWgLABZn3cZ1JCw9UTp6efJ0HJndlT6wKTLR/yKaeACdd+/HgEKeCRWnFhr7cEDZLi9rOk6yZJplgjhSZpqZ8unhf3WPbwBYGqvanLz7FJ3zfr
*/