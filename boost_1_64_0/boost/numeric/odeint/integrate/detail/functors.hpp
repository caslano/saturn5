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
L4YXY3ELOJo/lICUt4nM9uYrbKFFa+jCqWcX/FH2cvZhzd/BwNmW7/0WoangMuxx92LTcUCztxNi7CAa2IOEm6U4BttB5IQaKxw1ROiAg/5R1e2HgcRKWJFab1jCn9hzEQdSR2+eBQXuD3bzszWZIw2PBY+zVJemM/HRKB/k3zW56McOIzpOl1Qx4AggTeV3JPU54eAtDLcsw7mpmI0Oe2+dmWaIoyNlDF7wzaKTHQA0nxgCsBl59860L96S9QMxO+eqwg0zviuE0H2ZKlcoWTGTHsaeiF5S/7fujfUz7+r/0itxcILtvsoLaGJVkY/xiCogb2YCoe/CNask+0sGIF1mRDqElH6rGmdEV3b4ReIOOT2IuV3Jrjrnmhn8U4l4Sr/Qrf7FGHiK7ryoml94RC7Rs3XKE9TBkzXzSksegzrzV5go/MK62jBxZ7uDYciSVWNEsQA2pygANPhlrrVoNM0pEk7A00H0xzQYs63LISG/G3IztOj8ySyrsT+duDv3LS7w3dOdIIxjxO6/v6PbDcd2Xebw1fggQ/3h4a2yU7UOYD7tDMTdmBN1dg==
*/