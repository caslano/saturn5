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
LMNz+C0Ujt/Gx6KZ8G7nWEd1H2g9MhgLM25HxB/aW/fC+jPyj7SW/yqRUiJRiDLyKTSMwROpUV1Y1VjRMltjJ6+QzAB4L07rgfWi7EjjHS4lg6u2+F9ZDXdG0kPum9WM1F8raVmekOrY6ybPqHsHKC6BTF0H35Mlzd1ErkEeUn/6avnnak632MEAtvdRXwflR4WofAyOnkgbuXtHtDErTvjrhhNS2/ikHUwGh2oCohRhXUc9fYMot2IsEEQi5usqyLAvn/SQ0QlwcEPxPinKbtfjYa6hfhyjM2zP2mCSQ8Z1FI1qWgRG5Qp8++PAB3pFK82MSoFBGtilnX4cIvhUBXhNN8pRaGtcgZ0/IO6puv9EU7VludY/z4dBjTal4z8CMAL0x68woGSh6j1VxPjH3fFxBIDhbLBsRPbzXXNRyk9TNaempZCyaSfOe07mWnEVsHEg3dAjQG3j7Fodmm8VSwTlVN+IFLHGYEhcEtTY1gdVu3MLuKEeKGm03kceIhKOPuO5KLhwh/M5MwrOcal3Ou2JgaZVOgq6vQ7SlN61RTXblz62663cg66Now==
*/