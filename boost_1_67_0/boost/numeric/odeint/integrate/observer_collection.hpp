/*
 [auto_generated]
 boost/numeric/odeint/integrate/observer_collection.hpp

 [begin_description]
 Collection of observers, which are all called during the evolution of the ODE.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

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
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
*/