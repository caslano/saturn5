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
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
*/