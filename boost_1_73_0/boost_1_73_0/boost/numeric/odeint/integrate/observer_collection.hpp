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
vWr6csHfdYZVsOaQa+vTSsGyQsoNDsaYL3PLzY1q9gjFFLjRPxjhuA/d3w0oMTuGszR3pocDVvzFI+dvki9cr/G1txVQzdHqKGFSxiz5o1UioHVw33b7otCTOIBbLVLoYM2ZvN0g4j01nVzrDF5Ba3+m7e1QB4BYtAi442HhJZy1G9QODHdYS3BaryGs49e1E23vKniVyFBOVj5/PP3Ug66vaNwaioKnlri34g1WPWaJ7B4YPH3a2297uD3TW6YSyoNQWLkPTWshx8d7tmgqqdQor0BrasvKpbN9tp3lmm+XlYKxFhg4seJPSpivFI9tcB7tpgilNLYB3EY7HbQnucQ25Z1BJHQMqFSrlL+fXZapHOATdKgD9aq3RKekzGKw6XUUTd/5zOyllsLjZ+jhpIowWpGKXj1cRw/HEUBy1aLpdp1rIo6WUsdMRkIJ1yLK6M3l9Lx/GfUvL9vwZCejLoVFbtAdLCaH7QZLt7mH0oYF9lme4uZp9+5nZD4K59FoNot+6f88nUXn/WGvjjSBoEqPxZndVEi9UugTGv9vAfeM9ujvK0wkZ6rIW9+sDDN8IQy2CIunG/UIypmj3oFZYLEufL6rcwl0YeBqGs5PyiqipEdoiCeHj3bgwzm9mkd4CwiqTAaSTPQabM4T
*/