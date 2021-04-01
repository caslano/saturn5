/*
 [auto_generated]
 boost/numeric/odeint/util/resizer.hpp

 [begin_description]
 Implementation of the resizers.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED


#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>
#include <boost/numeric/odeint/util/resize.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class ResizeWrappedState , class State >
bool adjust_size_by_resizeability( ResizeWrappedState &x , const State &y , boost::true_type )
{
    if ( !same_size( x.m_v , y ) )
    {
        resize( x.m_v , y );
        return true;
    }
    else
        return false;
}

template< class ResizeWrappedState , class State >
bool adjust_size_by_resizeability( ResizeWrappedState & /* x */ , const State & /* y */ , boost::false_type )
{
    return false;
}

struct always_resizer
{
    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        return f( x );
    }
};


struct initially_resizer
{

    bool m_initialized;

    initially_resizer() : m_initialized( false )
    { }

    template< class State , class ResizeFunction >
    bool adjust_size( const State &x , ResizeFunction f )
    {
        if( !m_initialized )
        {
            m_initialized = true;
            return f( x );
        } else
            return false;
    }
};


struct never_resizer
{
    template< class State , class ResizeFunction >
    bool adjust_size( const State &/*x*/ , ResizeFunction /*f*/ )
    {
        return false;
    }
};


}
}
}

#endif // BOOST_NUMERIC_ODEINT_UTIL_RESIZER_HPP_INCLUDED

/* resizer.hpp
w3Q6Hd0AWyCbgbNJIBu7iFjIwK/Zjq9SjTQiipIzNoeL24k83JtgT3PctMrfoFqCbe6ggepAQoj3rKuMxo0V78uBtSKpW8qfEyaXudZ+FsMhjkLvPJbEM3WUXV2Br48ZIa73bZgkf0QVEHX1osqbZkYbDHs2JvwudBY6w97DqlDR+OASOaUXt0IX9bW13QFCuynRyHeL9O4KNGsGK03t3eZHLj2MOSn+Dv5YObvsFhOthRINVhA4gOw5ZcDXJQWcGw1dnaJAUnuyBejlumlDgt3xP1dcNiPXxl2gYE+Eb7gOvTBmbj4hxohffej82lI9Pti0IT7xbIDvPqm0I6R7jIeclcaELa+OYQdPlA8I/EBNB17YMn1EoP20BKnjnLuL2BvZ4ZKZ2DYKOjevgTHxtVwQDxfpbuu61OKOYZIBGOwKI5m4yEgklj6MM3Awc8iEbOoYgad3Ma9tJg2EOIxGwDvhBuixXMkug/OD/toglb8roq3blQSUofObmnJhVhw+eSy4INAKQbMvnIAArRxlMviOjd6v3GjeoHn4ErjLnvRe+Crm/SUhDYlaBQ==
*/