/*
 [auto_generated]
 boost/numeric/odeint/stepper/detail/rotating_buffer.hpp

 [begin_description]
 Implemetation of a rotating (cyclic) buffer for use in the Adam Bashforth stepper
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ROTATING_BUFFER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ROTATING_BUFFER_HPP_INCLUDED

#include <boost/array.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< class T , size_t N >
class rotating_buffer
{
public:

    typedef T value_type;
    const static size_t dim = N;

    rotating_buffer( void ) : m_first( 0 )
    { }

    size_t size( void ) const
    {
        return dim;
    }

    value_type& operator[]( size_t i )
    {
        return m_data[ get_index( i ) ];
    }

    const value_type& operator[]( size_t i ) const
    {
        return m_data[ get_index( i ) ];
    }

    void rotate( void )
    {
        if( m_first == 0 )
            m_first = dim-1;
        else
            --m_first;
    }

protected:

    value_type m_data[N];

private:

    size_t get_index( size_t i ) const
    {
        return ( ( i + m_first ) % dim );
    }

    size_t m_first;

};


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_DETAIL_ROTATING_BUFFER_HPP_INCLUDED

/* rotating_buffer.hpp
sVKfW69QDsv7sEKZ643YA3dLEDW3QothJrXn1sMbWb+Y7HzpN7VqGE8S1R4wWWM3+cpe7cMTt/swd6aPRc93yWIyeatMOArsaLz1ej2yGlCXPDz5zmwKx6fgG3tFZES6G9n2dD265uhIwALvtD+mDHKKXd+nnx42ShEw0dLzRyfCNlD/MT/C8xZHxc91uNJf6ImQVWeB7kO6HpylPOBugfAts2DNp4EvWujEkP/0wlJTfzTKIg+xCffHu16x6LNaDYJIdqPsHO3ylD+0UzbIW+O+cW/NB8H+dUICiRd3AUPNbLYlfmlny21uilWisc/cQaY99bo9zjrILNltuh69q3T5OyuyHtQY5q+1yj49YaNUzA2nK11vUJTv2sQ2PD+vk82hpkU9CswD9jXV71TPgxgEhbNS/q2b4xeUuNyvMYTrKZ72Qx0yrffAXynCFeqz2TsRrxVhfS6+YrooqB+dTTyBZT1qh2hTgt/zdBxvEN/vlBkSoaFp1gTTytL70UY+v30rLrr3sFSe434D8lW0oOkF5KbXkc6j3+vPm2iUEaDZin3Bk7Tyq+5np4OxUJQ5rp5fEfSDtnMGVMz2auEk2J6i4goi3Av3SPHsVh6L+JrYgozT9X0+7xDmM1CBqRWlgl71yXpUyenSafXE7X+t6t3prfEMhkBzh5k6WQyr88dPpMfBXs39prlsohWR6O8utU47vWvm3i7roVS1
*/