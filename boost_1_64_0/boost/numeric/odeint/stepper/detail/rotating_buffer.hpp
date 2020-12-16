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
CPYyuPrdGbo6Dmo+iCFX2T8xNHcc9hXadueOG0TfEVzviEe38UQ5CfbDDjVJ3I4ukssl82ZDrbO9D30JACc0Xi3fVXxR36blwdhuVboxlcYrMv3LCKeV71r0aeKupPsIzOtapfOOxlJ59/RkEVD0FU/G83yoT+LWCe6TTs0P5h4fyB0D+gXBYSM+qF21KFjKC9usTa7i7km4PcLIP3qNBsejk23s/XOsGWVPYMlkOc7D9rKqNyKTwLhhiimIRBu0G4vXonPDZaJYjo/cQzA4z2QtnsDg/ISri68CuOJJPND0AjBf8BoX1e43Gna7Fxh7OC3uBabTbXuEAwMfla1q3sTYwfHYWJ4RGYk/NVIWQ8U5GumyUO4R4muQcnkYA5P1clkmkMUJHHbgru7afsKkECbBfuJo4Yly9fDmHPQuYyXRKnmfo7ybzgeK62feik8ArNeLb+cyTgWoHEP3F9n3TilpgUlOX2DC+H0AD3c1yy/XooyIVMZjs0NfaeziHyX5R1j8Y03ur3SuPwExTkHypDxp7l/Yuxb4pqoznpukbWgDCRigaIECVSrFUWk3wYA2UFqmPAKFBJSHbqjX6hzDBHBDaE0pCZco29S5zTm3uc1tbmPTQZ0KlA5a8AU4HYLzsbntdtHJxtaWZ/b/n3NvkhbY2Pt587u5557nd77znXO+833fOdfZOllIjts/zpF/RgG0GGvHwEMSiN111xC8jBOQxe/HPxUYQhly2Dgv9hS5ouhjQuPxO8IISmKKd0VczU73b4R7jXC/J9y324kVHvXbF0M5tB2zqe2YBfqgsmPwupSqd2EyreiYlcxQdFTiJaDvvoP/T6xO6TUuSfbQa4zJJmRHbSkpOEmNGXw2U7uxKlO7secuUw5+aKGUgz+/0GTVMkj+/YhGkkdHXYkD6htNSr9F0E4Fswovrr/CQtYiaOBz2Yy6rcSiEp5iojDkjTQ9JghtrFRqdNY9iDfOntg5vQTi/tbJDr4bLaX3qhcccnvbCVaA1AC1yk6pRyGxcOosdm3e+gu4WhsZzosWigLV1rMoVtq4hT8xSMLAc2vSypW2GF6RwXnazkzlCnNwRk6iZX5lzVCuxG4p7KFfecIq9SuU+UeSS3AqM0BXb8kyhrX4nSPVGs6bk+yiizFDIA3dDvqWV2wZxBjEC9SbK1Iqlyrh8W7DGbUkGxvOQUvispM+9lhPo487MvUkCzL1JN+sM+njqWslfXwbz9Poo3+dOSQ2fNyAj0NGaChG9fD5poT7YvV6uzm8L2n32qT+8zxWPtzbGKZd61gwskX3hMX9ZHuMfKWf46AfAWX7Iy3CFhCG3pOdJXu8ea7qPNtkxyyxHkHbFep9Pi4s4wrRYAoe6P1z1u5Ho+fBKH9U4oKLbcpkR8QLhXZasJ2iunzijDFDDqbxNoft1ZGWUg0F2vZiuKscyLLDbu/J250EC1YUdy1DN4RlYkMR1D+Aew6KGY5heIjEsTvUf/zdxCwnwhp0Xo5GQBCQp+0w0ffKaok+9SITP9v8AAR6iwu4kKo0fdVPcviykgJt6lOmbyxbnuYqjjjvlQXXOxa4OmV4Wtf0omLqmjJa7lqz6PmSRE1d0xcY+SRmgLsMXdOKLFPXxGg9dE3mXF14TYauqZK6po/DB+5pUtc0V1+K9163FcsObmidDJXTj+8QKqdu4D19pwFenQSvm8rpFF2PmAFC5WQC8pn5Z6DSjxqZgaqoypsP6ltdRQqdGdA/uTxT34REp+mbmMMlJjhvylJNtc4ydV9WinFJLFF3dQ+uUT+ZhcektAKq+ziXBvG5VUYB3+5BCQmPenOKDLgy3JabUd1H56U1RC9/QoyZ3aseMvJFuT0=
*/