//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005. 
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_POINTER_CAST_HPP
#define BOOST_POINTER_CAST_HPP

#include <boost/config.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>

namespace boost { 

//static_pointer_cast overload for raw pointers
template<class T, class U>
inline T* static_pointer_cast(U *ptr) BOOST_SP_NOEXCEPT
{  
   return static_cast<T*>(ptr);
}

//dynamic_pointer_cast overload for raw pointers
template<class T, class U>
inline T* dynamic_pointer_cast(U *ptr) BOOST_SP_NOEXCEPT
{  
   return dynamic_cast<T*>(ptr);
}

//const_pointer_cast overload for raw pointers
template<class T, class U>
inline T* const_pointer_cast(U *ptr) BOOST_SP_NOEXCEPT
{  
   return const_cast<T*>(ptr);
}

//reinterpret_pointer_cast overload for raw pointers
template<class T, class U>
inline T* reinterpret_pointer_cast(U *ptr) BOOST_SP_NOEXCEPT
{  
   return reinterpret_cast<T*>(ptr);
}

} // namespace boost

#if !defined( BOOST_NO_CXX11_SMART_PTR )

#include <boost/type_traits/has_virtual_destructor.hpp>
#include <boost/static_assert.hpp>
#include <memory>

namespace boost {

//static_pointer_cast overload for std::shared_ptr
using std::static_pointer_cast;

//dynamic_pointer_cast overload for std::shared_ptr
using std::dynamic_pointer_cast;

//const_pointer_cast overload for std::shared_ptr
using std::const_pointer_cast;

//reinterpret_pointer_cast overload for std::shared_ptr
template<class T, class U> std::shared_ptr<T> reinterpret_pointer_cast(const std::shared_ptr<U> & r ) BOOST_SP_NOEXCEPT
{
    (void) reinterpret_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename std::shared_ptr<T>::element_type E;

    E * p = reinterpret_cast< E* >( r.get() );
    return std::shared_ptr<T>( r, p );
}

//static_pointer_cast overload for std::unique_ptr
template<class T, class U> std::unique_ptr<T> static_pointer_cast( std::unique_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) static_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename std::unique_ptr<T>::element_type E;

    return std::unique_ptr<T>( static_cast<E*>( r.release() ) );
}

//dynamic_pointer_cast overload for std::unique_ptr
template<class T, class U> std::unique_ptr<T> dynamic_pointer_cast( std::unique_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) dynamic_cast< T* >( static_cast< U* >( 0 ) );

    BOOST_STATIC_ASSERT_MSG( boost::has_virtual_destructor<T>::value, "The target of dynamic_pointer_cast must have a virtual destructor." );

    T * p = dynamic_cast<T*>( r.get() );
    if( p ) r.release();
    return std::unique_ptr<T>( p );
}

//const_pointer_cast overload for std::unique_ptr
template<class T, class U> std::unique_ptr<T> const_pointer_cast( std::unique_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) const_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename std::unique_ptr<T>::element_type E;

    return std::unique_ptr<T>( const_cast<E*>( r.release() ) );
}

//reinterpret_pointer_cast overload for std::unique_ptr
template<class T, class U> std::unique_ptr<T> reinterpret_pointer_cast( std::unique_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) reinterpret_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename std::unique_ptr<T>::element_type E;

    return std::unique_ptr<T>( reinterpret_cast<E*>( r.release() ) );
}

} // namespace boost

#endif // #if !defined( BOOST_NO_CXX11_SMART_PTR )

#endif   //BOOST_POINTER_CAST_HPP

/* pointer_cast.hpp
CqQSVsOxCGBrkbr0INh6SpsHwW5Bau1BsDuRWp/oQxSP1qpkVzYib4u5oKw47uSt7Idb4uotsDrfKerN+eTQ2d9FBklD7JxHDq3skWkz9LQZetoMPW2GnjZDT5tBGwfOHJRDbNju/73Ept4nJNLbtUN7J/Dqd+LmJtTEffn8n/A3T6eTByg0pfs3i9b3t3+S/j/uaI0fsx4L9KXTsEDvuUUWaA8oaV+7MuGvRC3gK05H/ozW/Mor2ua/z/yJrfkz25X/I/NPa83/pF3+m8z/GvILVoKQ1F9JQNPjrwOidcKLyBd/QmW1OFyE5t23Xs7LTHUfnCb7AbicK/+oXcU03MXJAwx5m+GjkkX7owso7bc2c6HDzAVXrXgDXd0l/6ikaP2c3ohZUgJ2pgzeMIZWqwUN5qQzrpK1/7fblVt2q95P35gr6XVmiNWVPvGOgk+8cMKDIvwjGdYGw1rFp0D8Ii995fH2YFYIS0ZlxesF3wnRifblfpCf9hqK8U54VIjcJj0q2AOa56f/0n3WduvDBS3ZGfCA7I7NTWv4JZfIggNnuZDQ7RUXCfk9Kglkn0npTFqoko5lUuYrGVyIYTxXOeW5C58vxvOt6jmTz2fj+QL17OazH8+D1HNXPg/Gc4tDnrP4PBDPterZw+dsPPN+5ytH8hCsN20aQi24Z5I25ySJ+cnUmLr6vOec1vjnDfZDs3nBRt3518x5eU8MrgQRLWfVNcbSWcpfzkss6fBipH53HkaKJ8ey/fychO+wC1uvxvKOH63r6HbCvlGEzDX2WRdAr6cBpgnAs0lJgXweGXtxQe0FSaKtVMp5kwqE6rfeMWDqSj/2QQuNU9lX352jgUP/WwkJNEKi3C/HkTmu8qzvgewM+8Ai5UfmQ6mlWm3GE0GR49VR1RhzaaGSqKm8AMbR2oPMcmszm6oDwkaacc+ZvSYHcF9K7xt4fhZQGrL7rlStzRcxZeqtRTvmXJ1SG+oyYmc67etUfeHJUofuA92st4FdI7BjNWw+PQ9A7bssTfMAt+PEhmnx6sZ7k315EYYXL+urtfC2ocY1qHzdiklmn93jGfF2GbHeIouL6yxuTtIZ56vJGoOtwVqh0OI/7PTgy3+U/+ZFsVbPYTSMf+NW7bj5YPqRIB0gHKUsOjqWuBpC50nF6vKULcHvjci6uO0V65F6SuUOEb/n9ZA1V2pcKEOLi2GLMjBfBJgcbYl/WyhOt5fTOJnvO1TGCGaA8jBDKM9GnXEcM0B/mCH0Z5nO6MWMY1VGBjMe1RnNi5FR5ZSMLsxYrDN2MEPRpZeFLl3D1JVMvUClCnWazNRnmDpIpQqNGsnUB5kKSsVUoVT5TL2RqbUqVejVEUy9mqmkWi+Tar2gqNZu5txyjmyafWKlaXhsHamGV2/m4UDC3dKTmnAo50rwa/E9M3ZU/eDeDqjNavy9k/Ewnj+MlY6lEb4s4APotdAhWzaN6rRA0fbZW0NYBHmQRh3YgjwLf40sbEOeReudcgfTgDuH+DlelnpFin9Q3svuf24r0fuFTOCaBBmzb+G64nHSd+Qb8UHtceonKafJ2LDD8AxnOFJ8uDqFZczQyHzN15/g1BYNTG28XFGVw53quefNsvKPLymIN2RIWolXSl1E2wOrxI0ei0+SeH3DWCQ19EmpzQ/99KZLVUTYWw0JCAtwu0qSwh+WSERYijWFV6hWH+YrnY0mlcEPk2hvARKl4/kcrbpzXcEb8PpzRUD54DnlLkm8RJplwtBzJeFsmiTxQJRGyCZriAo9F9cgeX4x2J2KAGokeXkktV/DC4Bwx0qdJLAP3ie19IxXY97uVA7BGtO51BLEjgTtSI7+lZPQ5SRRFxr3gwc=
*/