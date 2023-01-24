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
8kg/+6exaYqh63mRILgOrTbsJV03cjop7+3V8G9copt8HNYifssDoxW5gbBJ7AXgNxpeO2jrk7Zc1OxZYXOfLnWvKFWKt9J4eQACs3vBUZiX3vCgs/EkeAT+F2kAHxi3lDaHPEqaqZjJp6XiZ2bkE1H86U6Hd9/K91hhjKSqqKG6VC9zFKPLq8+NFpPohRSYeeUjQ+6kYsCy6JFWAGXTZvHlk5ufcQTg9OZzyEH91xWCPvzBDvlFBKBxa/5J3yWwXvRav4Ei35o/NDiTY4uMQmyU/UEtMos/zynUldXe920bUt5LDA6d+5SCUrbBmXxBek23yl1xXuwVrShPIo3rHlQy+ksNx00CYwQmLpToL1DsB/renLpKVt+rGJKHVFiIgAUSKwPWFbgZ3pAIWQDtYNNmTANfnGiFFHSmiPY8AFtZyT74ak1GdOFQdlrTyKb737675JvcbSRh+GtAog3nBVrBJTKL3YEslbIfUaaBzZMdag4GjbMbJNRk9XIrGOmyMZyO1T7C6VldAzbO8BA6gPgFzv6TJMHVexn+bOnNYKTwGQsFybXeZOrMmk30cwniF3WGspqYOKYbxV7dGna7VFe416YsevKF5AgG/9Djm3EahrAifU3SxAsKxEaopX59C9iPcmgOTJ0w36RlprW++uL5c75mdaOAAiOKfZzoJQs1zkqHTbnEYKwTofnjHHa42TnqUTNxOkWThane
*/