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
aWJ0ZXN0L2xpYjU0Ny5jVVQFAAG2SCRgrVdrc9o4FP3Or7ilMztA3UDoI23TdtYB0rClOAPOZrPDjEfYAmtrJNeWk7Bt/vveK9tAGhKyM3VibMv3cXTuQ3Kz8euOCjRg5+GZ08MDr0bjNFH/cF9vl/a8H5D/odYEr7ucNGGt8sOrw26VH1AzKl7h5T3de94uRxPCRj9N0px4dIsjqEaaHRUvEzEPNdQ6ddh/+/YNPId2q92yoMuk4BGMNZdTnswteB+Ykd9Ddn29l/KPFnANLNorTLmhSCFVM33FEg54Hwmfy5QHwFIIeOonYooPQoIOOcxExKHjnF70h58suAqFH5KRpcogDVUWBRCySw4J97m4zG3ELNGgZqiOxgORajSYaaHkHvrmoHmySMkGuWdRqoBdMhGxKTpiGkKt4/Rds+lnSYTom4Hy06ZfTn8v1IvVTC4QxIItQcUatIIs5RaQpAULFYgZXZEQHIyzaSTS0FqjQVcyaKoEUh5FZAv1BE9z2BzGBT0WiUGMiIWmS6pkSq6uQrW4JYg8kpVZlkh0hDygUKCQZgsyGfDECJuZly4KTg3B94ZmjTcAJREMVO0x9MdVmLJUpBac990T58yFc3s0sofuBTjHYA8vyNjn/rCLoRfoLAF+HSc8RecJ
*/