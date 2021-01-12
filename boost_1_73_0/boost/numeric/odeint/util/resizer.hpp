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
jNgcrBA43qllDwOctQEH8olY3Y2C6+MH+BDnW+AjRfFpLbA9FBCogPMtYEqXqFlgQX+7RWDyJIA9C3BRAXD+yFZjX3oGfffcdHlxZup4+ejo1Ix27RaDeZ/aXb+NnDc5kaOq8axfyI9KY8qv3LOqZJHa5UIWWRYp83lXxadu/3KBzYUyPRLDPcbj+uGQ4vE59XiMywSTy6N1bwPBX40eD0Il407jMsNF+zan2/F5VTzqPMvj
*/