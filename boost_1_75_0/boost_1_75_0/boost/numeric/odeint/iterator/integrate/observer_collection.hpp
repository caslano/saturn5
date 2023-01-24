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
QpIVgMogkTHdl7rSamEGOonrCe4dFZlYFJEbYfS9tjKFW2F+8knaPQ2OfpWFN7HsrYAFIq0uYT/ILyl0P2gMFqstCKy0Q+8IF1s+169Lz9U3Qi1zZdT2EaSteBpLbCLUapTKdG9INJMyvN+QmFiVttEVlGIfshbTRhkFBi1kDbmF+OvCk4RO9b8038eT2czhfk9qRiZrqacsnguMOwqYmezEri+JTvaUThkTBDpPqVfOosRU2glRlqNRHCOta6bwLTRkZ0A9/VMiLYFJoLpFlrPxaTe1ObtJKq/rdqSrxzTiNbhdgP56BnPvQ/3lNH3vugD9ijdnmIyE4YmMGEq3ldWJot9HIZvJiFRstM1Hl0ghpTZhD64RdvBfbbxwHMK9xAn2MadXWiyM+la5XglFYYgm6kWQWoSWXnlUpXsyYZ/xNi3NpwkiOYErjcTBThTnx2uoNznuEjR3pA0M76T2f2hcZqpd3iwHk9EplWHnX1bBgXdd9+LD6fz4+FF/J+DFHHiQhr2YQGsnsuDQl5AxtSCgFVeQtbHRn85iNCCyn97gtaBVWIG59nL2fmt/6d6Zg7k9Sv5iRBgLe5scE8/EfnBkCcB8o79n9fFOeijjwLR0q3TOOKAK9+qqj0BI8tCswTEobZ8xg1S97iNZ2vQ635XDaaGoo/wo5NbhxdPQxCR1lvSsGRLj2sv8ykvd2BDjT2KZkDSQ88qgqLDy
*/