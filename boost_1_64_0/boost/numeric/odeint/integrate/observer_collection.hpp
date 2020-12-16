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
JEdCpcFvfY27D0l+X/fwG4AVa+/r78WLrMLVZpB3y0h9uxYi6YREYB1xaz9zfL+Q8+fL/earq+M2PTpDMuBi0IlMobe9Ud9e49oRUgzp8E0Oh9OfQThT96YtSOz8jXHalNmTc/NsW/ae3LWOxkCQe/9M25RxjBHvXc+30AduD5LyOtYvL9rZ/r6F7enudEyGmQENuyGy0xpm5ejuc944RjnOiulmb0CZoqzY6Zsimxa0UCdv1jq5w7oUzYUPmLg236rm3gvvgOHsO/40Du5mcf5EWe5RSRnAvPs1t8v8izkvzvMOpgEnPcG9xOB+j+lLBFffSyBt0sK8v71a5wu9S5h/T7W5O1Aof7H7f4aO5Ed07o/ah3lffLEHnO5JW35s/I6fsMyXVJkHTZmfmTIPIe2dg8Yxh7k4z4bPo0bOP2f6UU+fXGNwf8n0NR7cGwzu40wDrnAhK7OH/iTyn9k9TMfPJD5FXw39F8N/2uAj3+H/Tunz2v0ER2SKvWvSfNTQ/KOh+ShpPmt0AfNpTBeeM/mXm/znVf4j3GPV+S9Ivut/m/+ioW/z/0a9ekTp1SvGR/67h+6rpp6FSOO7ijEJ4H7jGB7iloRhMBi9hPEJ4nmMdsK4JiavvqV+mbv/rmJmvF6d1d6+jEQ3YZqxTfQbZfYM7T+lj5HvP0P7LzXONc4b1WavXNG6cCruuE4OMB/EaRUkKEfi/GhGvD4TkU8abn55ocSej0UMBkUjw3M++pzCpITv3pr/Ltguidj9JeDRBue9WzQp2DWh7Z7g27MDuyV4x1poK/r5yhUF70jke69pTe7mgLNQksx9z05OyPrBlAT3kyYGLr0708Gm+HsrM4Mg5+/tAZzwZgZ/I++o3O8V+Lrgb5BoC/bl98CeCbWn5upYw+rhV/g9P0ba+3KuLlP0Njl6iRy9hJv/8/GtHqh2mPwN3INivDcP9AylN9F3ZR024zoQgJCZ1GXT5kQXZML6vEvXZ5Q+oO7iTLC8x6V1d2/QCmX/NOB8E4Tjk2VMHNDyBM8KJmRtYkrCxCNDegb+ys17KhVqnAyEf8wvJ+19zVhDjFb8xWnM9ODYd1tmCR/ixNswOxHH/8PsOL5t81xDD3+x/GqVX+7hV5PI8y6VX0ecTOso03195axOc63u/QmZIw4wfTIP6QPZL7rtByXy8LB6znrNJ13wQx2F38EOLnL4INIfSsTlsIC6836Du9CD24C0e/9P8WjU5dimxabcIQn6K6Sr/ZUm6SfKI172sES8/jZ/maI93dBenoi3x+rQh4k/g/jvfi9p6XHAvLZEfCxliKP7baXpx71V3daZ+5hHUe6rtPwcnsRc+0sJ3/kh7jHE5bwC3PxvhCZZ5jiWkfsQQq/D6CN540/jI2Yk8VMGHzy975+uIf5axTvEZfw2l7eOea/mWbM+GvmFLo4fYwcSVuRgQ30OSht9LODFDo6YiAxDE8LbAS9xcHnHoxOwUgcLeTFOWEbe+1qN/DLGDxxcQzh5T5MYGy5dbmJsdANWgTWyzNqOzbihmCu73s0ha3r6O8JomP3rh8IYN4x92KPmjdmjxC3U944KsU/xdOxNv67jW3F5gjwjnCCztiaxrL9rqCeFxakcvMjBVwz2405EGhmEQ4aH9HT0dPZlDk+3r0kJfkkQ4sbgvM+CazD4YE/Vh40VvmVZeFghwue72JFro8oQtu6dLqbRFgIdrC+Ua0F6S+Om1AoIMjiYby/2KzlVhG/bL1u+6PCljY3NbS1H1UQm0QLlbRDUdRL0/kaeid1A3bsjrnv9XXq/xKX59iRxoHupjd2dsT2PYsJCTOJBXpjtEeJS45USpvGgZ0DS77YSIRZXk+/IEac=
*/