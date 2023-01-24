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
81WQ3phzPjk3LuT66ZW+CPx8/a5Da77s1wwCdunHvODqmzSXyaqP86Cia21uZb9VQjXYYZF7Mjx+LFmFdkTY9H0I4VqBO28eqT/s3Yd+3nBy3fegjxF7SrQi1ItFfciAGoYVxM5rFk1WEp3g0O1PZG5MKddP9LZ8UTStnbgwcfrSkoz/1HXFYQqmRFfZIL1u312GnMX9BTnNp0XKg8qtO67LPUpzCqrTrknMcGvszPXOFMi9E7zf7560YqDNOZuxYW3isDft0qvKjT91CI28YchtCaqvXpK6o8f20WjOtlq5r8wg6ejanbcxLXM2yM1yxO6M0q+g77ipSUzaJ36E8i0eNTr4YbUdVDNBPfL3bOBR68LOkHzD656Jq1ezm3mOsmZew0EG4lkp+4SfQcZVtI5PPvyTX7+p9/KjG7L2RGbhZ9Qd/dtnHWf/ydrjK9+qpD1HaLHiCosCRDueHHq7rrVe5+mJ3PPrEj8783h7DUvz4LymjVrUefnXwSdy2k0Yb37191vJnn+/2xBu9oZmoR0tTT34yXcOp9MB3/00/8036ufzz0sL979qP9z29LIBw8Ht0dXmuyNrlx5rPTx59kRdsqx/p13gw1b7B6upVa/Q6gjZxE/Ulj6it61l4wux6jHO789KBTeG3s+c/eg3mPifL9HX/1Q3a7VKNnePZEk9Bd6YU3tA1wPv6Y8frrOOtTfj7E063JnQvvds
*/