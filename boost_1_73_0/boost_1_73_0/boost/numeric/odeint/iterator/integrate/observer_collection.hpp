/*
 [auto_generated]
 boost/numeric/odeint/integrate/observer_collection.hpp

 [begin_description]
 Collection of observers, which are all called during the evolution of the ODE.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED

#include <vector>

#include <boost/function.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class State , class Time >
class observer_collection
{
public:

    typedef boost::function< void( const State& , const Time& ) > observer_type;
    typedef std::vector< observer_type > collection_type;

    void operator()( const State& x , Time t )
    {
        for( size_t i=0 ; i<m_observers.size() ; ++i )
            m_observers[i]( x , t );
    }

    collection_type& observers( void ) { return m_observers; }
    const collection_type& observers( void ) const { return m_observers; }

private:

    collection_type m_observers;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_OBSERVER_COLLECTION_HPP_INCLUDED

/* observer_collection.hpp
Z/aS7RmKmHhtHkY6dBOOr+XvhSlcV4zERULzMkrOy1IeDY8HYD+x9fHxZyTHkZ7+JYGQ94L1wDakOjwSn3kg6GP4ASKwv4hFpPc+5wszdr0xBbHV1h7SYUfooIBw/cPp4LepcZArSRHINfQ0rGqpLZqNuRAJudNSpmLoPXCVfYnUIQsBa/oUSgsi+9LjpNj5Ps8Sbp3LL9ebiFYwu62Y1eurfaSXhlYTrAbxDn8s75h03jb+es55TDuvfA4ehV7KA3CHfLd2AIfteRael/ZBOq0bpPiligmJnw+AFyUgqD7sfXzaqz3crzyE6c3sI25m617Wqjz29XMfX5Rj0fF49Br/r4wuhtN4iS4KBSCR0U5lgHOop34UnhlSwTAD2pOcJ4cWBbPFgMb5nlfn+xeJ9ExKQHx0d9gZmIUHWvcsn0kzw6xOxkkGgVtyC6PUvkmkNkdj9LEOu5/4BlrEnraTquUWdEaz/W5mvcqaHvWkeUnOIce8XM+62hlk2RyOjoaj4fRUyqPVROD3ojrCUHIkdrxoK9MAxvTrltG0CwXO5xRK9+o74DwovsNKK0tkW1aAlghzPSnMM6aUoqc62EQ0sID/k2hoe2tFA89wVotWbC5kfYzCtBXmxlibFFOvJ72npaQLJnVo0uJRMz+a
*/