#ifndef BOOST_SMART_PTR_INTRUSIVE_PTR_HPP_INCLUDED
#define BOOST_SMART_PTR_INTRUSIVE_PTR_HPP_INCLUDED

//
//  intrusive_ptr.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

#include <boost/config.hpp>

#include <boost/assert.hpp>
#include <boost/config/workaround.hpp>
#include <boost/smart_ptr/detail/sp_convertible.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>

#include <boost/config/no_tr1/functional.hpp>           // for std::less

#if !defined(BOOST_NO_IOSTREAM)
#if !defined(BOOST_NO_IOSFWD)
#include <iosfwd>               // for std::basic_ostream
#else
#include <ostream>
#endif
#endif


namespace boost
{

//
//  intrusive_ptr
//
//  A smart pointer that uses intrusive reference counting.
//
//  Relies on unqualified calls to
//  
//      void intrusive_ptr_add_ref(T * p);
//      void intrusive_ptr_release(T * p);
//
//          (p != 0)
//
//  The object is responsible for destroying itself.
//

template<class T> class intrusive_ptr
{
private:

    typedef intrusive_ptr this_type;

public:

    typedef T element_type;

    BOOST_CONSTEXPR intrusive_ptr() BOOST_SP_NOEXCEPT : px( 0 )
    {
    }

    intrusive_ptr( T * p, bool add_ref = true ): px( p )
    {
        if( px != 0 && add_ref ) intrusive_ptr_add_ref( px );
    }

#if !defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC6_MEMBER_TEMPLATES)

    template<class U>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    intrusive_ptr( intrusive_ptr<U> const & rhs, typename boost::detail::sp_enable_if_convertible<U,T>::type = boost::detail::sp_empty() )

#else

    intrusive_ptr( intrusive_ptr<U> const & rhs )

#endif
    : px( rhs.get() )
    {
        if( px != 0 ) intrusive_ptr_add_ref( px );
    }

#endif

    intrusive_ptr(intrusive_ptr const & rhs): px( rhs.px )
    {
        if( px != 0 ) intrusive_ptr_add_ref( px );
    }

    ~intrusive_ptr()
    {
        if( px != 0 ) intrusive_ptr_release( px );
    }

#if !defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC6_MEMBER_TEMPLATES)

    template<class U> intrusive_ptr & operator=(intrusive_ptr<U> const & rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

#endif

// Move support

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    intrusive_ptr(intrusive_ptr && rhs) BOOST_SP_NOEXCEPT : px( rhs.px )
    {
        rhs.px = 0;
    }

    intrusive_ptr & operator=(intrusive_ptr && rhs) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< intrusive_ptr && >( rhs ) ).swap(*this);
        return *this;
    }

    template<class U> friend class intrusive_ptr;

    template<class U>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    intrusive_ptr(intrusive_ptr<U> && rhs, typename boost::detail::sp_enable_if_convertible<U,T>::type = boost::detail::sp_empty())

#else

    intrusive_ptr(intrusive_ptr<U> && rhs)

#endif        
    : px( rhs.px )
    {
        rhs.px = 0;
    }

    template<class U>
    intrusive_ptr & operator=(intrusive_ptr<U> && rhs) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< intrusive_ptr<U> && >( rhs ) ).swap(*this);
        return *this;
    }

#endif

    intrusive_ptr & operator=(intrusive_ptr const & rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

    intrusive_ptr & operator=(T * rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

    void reset()
    {
        this_type().swap( *this );
    }

    void reset( T * rhs )
    {
        this_type( rhs ).swap( *this );
    }

    void reset( T * rhs, bool add_ref )
    {
        this_type( rhs, add_ref ).swap( *this );
    }

    T * get() const BOOST_SP_NOEXCEPT
    {
        return px;
    }

    T * detach() BOOST_SP_NOEXCEPT
    {
        T * ret = px;
        px = 0;
        return ret;
    }

    T & operator*() const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        return *px;
    }

    T * operator->() const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        return px;
    }

// implicit conversion to "bool"
#include <boost/smart_ptr/detail/operator_bool.hpp>

    void swap(intrusive_ptr & rhs) BOOST_SP_NOEXCEPT
    {
        T * tmp = px;
        px = rhs.px;
        rhs.px = tmp;
    }

private:

    T * px;
};

template<class T, class U> inline bool operator==(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(intrusive_ptr<T> const & a, intrusive_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

template<class T, class U> inline bool operator==(intrusive_ptr<T> const & a, U * b) BOOST_SP_NOEXCEPT
{
    return a.get() == b;
}

template<class T, class U> inline bool operator!=(intrusive_ptr<T> const & a, U * b) BOOST_SP_NOEXCEPT
{
    return a.get() != b;
}

template<class T, class U> inline bool operator==(T * a, intrusive_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a == b.get();
}

template<class T, class U> inline bool operator!=(T * a, intrusive_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a != b.get();
}

#if __GNUC__ == 2 && __GNUC_MINOR__ <= 96

// Resolve the ambiguity between our op!= and the one in rel_ops

template<class T> inline bool operator!=(intrusive_ptr<T> const & a, intrusive_ptr<T> const & b) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

#endif

#if !defined( BOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( intrusive_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( boost::detail::sp_nullptr_t, intrusive_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( intrusive_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( boost::detail::sp_nullptr_t, intrusive_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T> inline bool operator<(intrusive_ptr<T> const & a, intrusive_ptr<T> const & b) BOOST_SP_NOEXCEPT
{
    return std::less<T *>()(a.get(), b.get());
}

template<class T> void swap(intrusive_ptr<T> & lhs, intrusive_ptr<T> & rhs) BOOST_SP_NOEXCEPT
{
    lhs.swap(rhs);
}

// mem_fn support

template<class T> T * get_pointer(intrusive_ptr<T> const & p) BOOST_SP_NOEXCEPT
{
    return p.get();
}

// pointer casts

template<class T, class U> intrusive_ptr<T> static_pointer_cast(intrusive_ptr<U> const & p)
{
    return static_cast<T *>(p.get());
}

template<class T, class U> intrusive_ptr<T> const_pointer_cast(intrusive_ptr<U> const & p)
{
    return const_cast<T *>(p.get());
}

template<class T, class U> intrusive_ptr<T> dynamic_pointer_cast(intrusive_ptr<U> const & p)
{
    return dynamic_cast<T *>(p.get());
}

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

template<class T, class U> intrusive_ptr<T> static_pointer_cast( intrusive_ptr<U> && p ) BOOST_SP_NOEXCEPT
{
    return intrusive_ptr<T>( static_cast<T*>( p.detach() ), false );
}

template<class T, class U> intrusive_ptr<T> const_pointer_cast( intrusive_ptr<U> && p ) BOOST_SP_NOEXCEPT
{
    return intrusive_ptr<T>( const_cast<T*>( p.detach() ), false );
}

template<class T, class U> intrusive_ptr<T> dynamic_pointer_cast( intrusive_ptr<U> && p ) BOOST_SP_NOEXCEPT
{
    T * p2 = dynamic_cast<T*>( p.get() );

    intrusive_ptr<T> r( p2, false );

    if( p2 ) p.detach();

    return r;
}

#endif // defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

// operator<<

#if !defined(BOOST_NO_IOSTREAM)

#if defined(BOOST_NO_TEMPLATED_IOSTREAMS) || ( defined(__GNUC__) &&  (__GNUC__ < 3) )

template<class Y> std::ostream & operator<< (std::ostream & os, intrusive_ptr<Y> const & p)
{
    os << p.get();
    return os;
}

#else

// in STLport's no-iostreams mode no iostream symbols can be used
#ifndef _STLP_NO_IOSTREAMS

# if defined(BOOST_MSVC) && BOOST_WORKAROUND(BOOST_MSVC, < 1300 && __SGI_STL_PORT)
// MSVC6 has problems finding std::basic_ostream through the using declaration in namespace _STL
using std::basic_ostream;
template<class E, class T, class Y> basic_ostream<E, T> & operator<< (basic_ostream<E, T> & os, intrusive_ptr<Y> const & p)
# else
template<class E, class T, class Y> std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, intrusive_ptr<Y> const & p)
# endif 
{
    os << p.get();
    return os;
}

#endif // _STLP_NO_IOSTREAMS

#endif // __GNUC__ < 3

#endif // !defined(BOOST_NO_IOSTREAM)

// hash_value

template< class T > struct hash;

template< class T > std::size_t hash_value( boost::intrusive_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return boost::hash< T* >()( p.get() );
}

} // namespace boost

// std::hash

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

namespace std
{

template<class T> struct hash< ::boost::intrusive_ptr<T> >
{
    std::size_t operator()( ::boost::intrusive_ptr<T> const & p ) const BOOST_SP_NOEXCEPT
    {
        return std::hash< T* >()( p.get() );
    }
};

} // namespace std

#endif // #if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

#endif  // #ifndef BOOST_SMART_PTR_INTRUSIVE_PTR_HPP_INCLUDED

/* intrusive_ptr.hpp
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
*/