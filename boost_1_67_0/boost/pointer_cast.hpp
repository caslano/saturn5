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