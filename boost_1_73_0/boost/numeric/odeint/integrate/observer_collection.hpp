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
etpKZmE5mVJzbIenzWLnYkGw+Jya6NfrS7dpd/alcctxPa4PeuykkOLz3tVDk7cbw2mk3W7YQ8ONQB5fe5X3GsN0P7Zv7Gn0kIpvCS7rTfrQ9RjaLXR7I6284ejx3NxKntKa701ZfFZ1ieS1R2i6SyxtL9PCxSTavh4a8LuNgss+52aCmQtB08sHLX5AcLLtefzmoPHuOl4iNN5z4kNbaf7OLYgmb02m5nOhdfOWmq7S3Ypw
*/