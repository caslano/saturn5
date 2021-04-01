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
FBQ7mEMPPgxx9U6uoGt+RiGs0SLumfjY4fX7xy1ygTdRAy/UdMtfcW7gz420bNq7gBbpmcax3gv5EC8k9hyFZ3GQ5g90/fIOtCNm+v6KkugzEwwNdHsuf5UjmYPHImAmuG4MwUPRMSG6IgoiAO44zML3hFgFK5uzhujnm/AUzAaEpm6pNGIM0zG7eKtFn0a+y9TQ/gZ0Zi4KzcYdv7p6KkhcxLp1E6u8AQ1OxCvmlEhcOQiXJQxmzvSNlwqZk09F8ztFf/jT6hcFaDMfQZHPDd20Xuw+Xn88/f/Hcgz9VcTIbEn2CYPjV5ZcuGymiiHHF7P3UmWFboBiDis0SQ0FrsU+H2ItcaS3obF0sPx2NAt0DrT1+gyoZ9zbzu+u07Pcu5XFXTnUBUOqcarJ+7B34Lt6lgyYT0Ivvbu0FFgJP2f0zXPek82AaHqz6xF+MbqKWRfLhPw0HpY36j8DQiF8E1O1qjKflJnpF5D/KC3Sb60qQUNCmhBTr1yVrD5BtjqMV7moP5pfvchxSwQfQAwbW6n4HBlSmRO1VIiSx93S1jaDFw/e14Xb5HQZww==
*/