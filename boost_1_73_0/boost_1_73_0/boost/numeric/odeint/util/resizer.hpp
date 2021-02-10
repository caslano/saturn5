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
vCtlBRTGwRLhPPpLugYwCR9lGC+E97Fp8abd1GRO45EhXYny7Sl8ClWweJTxRkc+7XpoSGXSVuNv8KKkQdEFVzYKtWnfWxXLUYM5gmbN0KK/rXokX6v4nmeORUWrqlmAjUKofxYRT1vyYimySF0v57PNN1GQgmqCZm4wrDKHdqaDXp96I75dUn8yHjwDlK0jy5xJgzlHHX77jN/Km5cvj9iVRZGktpusrwwGqtyCQT8SJlosVXNV3K06iAedWLMLSS+9b3KS1npj06kvtddePhzieDKn0+FaeKvgPi9bEltRpCFEkfZMvCwa7kTaDQFz/Hg58MVp9BJ/K9//XxFIAAu1SkdsAgpV8MS1yUUGYJeOj+3kGE5OPvTdKQZRbzpnBB4B/wI7yBr8ay50rBVbTFRT0XOJ+ChtN3JvUY0T3gAkzgTWnc8rjEt/Bu7kZwa70eC4eMaW3biL1VX80GHt4rWEnZMCyvh8NDqqeNb9q/g+0G7yL66sUIo74Ji6tpusby7bdU2UYKXZsvTrWC9E7EYqMjbT7rvR5G1v5PZGo5KBN6BymX1Zo+XS4EhiqY71YnI2d3FzeFeyYH6dDQP97WQ2cKi7jfM9kjeYVozl/LewM/5nk9mcfGEEBRlOKmKVC5uDrytFecxHp+fj
*/