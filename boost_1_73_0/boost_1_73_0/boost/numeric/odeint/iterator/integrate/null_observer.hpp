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
Ey2svIt6W8gy5rChTgJjaVv7mUecfguYs5nYTv/azTwncxPTWWLqTMaQy8TEXw/TR4kZC2tJ7BpFG63J/Pldzofxf9VyyvQobYF+1HivRNnCxOfOwJfJXM98wdyLsrufOt47gT5YmZj1JX3lXgu/Mw4OpE620m7zUl9PMt86QJyZOtBCB8bneOaVM5lzfpOX9ltK4DDxf9KPEjsLMV70p820BtYTI+bRtqdvECj8gIpntNFyjKe0HZnFvPmaxMk=
*/