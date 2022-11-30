#ifndef BOOST_SMART_PTR_SHARED_ARRAY_HPP_INCLUDED
#define BOOST_SMART_PTR_SHARED_ARRAY_HPP_INCLUDED

//
//  shared_array.hpp
//
//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002, 2012 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

#include <boost/config.hpp>   // for broken compiler workarounds

#include <memory>             // TR1 cyclic inclusion fix

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/detail/shared_count.hpp>
#include <boost/smart_ptr/detail/sp_nullptr_t.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/config/workaround.hpp>

#include <cstddef>            // for std::ptrdiff_t
#include <algorithm>          // for std::swap
#include <functional>         // for std::less

namespace boost
{

//
//  shared_array
//
//  shared_array extends shared_ptr to arrays.
//  The array pointed to is deleted when the last shared_array pointing to it
//  is destroyed or reset.
//

template<class T> class shared_array
{
private:

    // Borland 5.5.1 specific workarounds
    typedef checked_array_deleter<T> deleter;
    typedef shared_array<T> this_type;

public:

    typedef T element_type;

    shared_array() BOOST_SP_NOEXCEPT : px( 0 ), pn()
    {
    }

#if !defined( BOOST_NO_CXX11_NULLPTR )

    shared_array( boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT : px( 0 ), pn()
    {
    }

#endif

    template<class Y>
    explicit shared_array( Y * p ): px( p ), pn( p, checked_array_deleter<Y>() )
    {
        boost::detail::sp_assert_convertible< Y[], T[] >();
    }

    //
    // Requirements: D's copy constructor must not throw
    //
    // shared_array will release p by calling d(p)
    //

    template<class Y, class D> shared_array( Y * p, D d ): px( p ), pn( p, d )
    {
        boost::detail::sp_assert_convertible< Y[], T[] >();
    }

    // As above, but with allocator. A's copy constructor shall not throw.

    template<class Y, class D, class A> shared_array( Y * p, D d, A a ): px( p ), pn( p, d, a )
    {
        boost::detail::sp_assert_convertible< Y[], T[] >();
    }

//  generated copy constructor, destructor are fine...

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

// ... except in C++0x, move disables the implicit copy

    shared_array( shared_array const & r ) BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
    }

    shared_array( shared_array && r ) BOOST_SP_NOEXCEPT : px( r.px ), pn()
    {
        pn.swap( r.pn );
        r.px = 0;
    }

#endif

    // conversion

    template<class Y>
#if !defined( BOOST_SP_NO_SP_CONVERTIBLE )

    shared_array( shared_array<Y> const & r, typename boost::detail::sp_enable_if_convertible< Y[], T[] >::type = boost::detail::sp_empty() )

#else

    shared_array( shared_array<Y> const & r )

#endif
    BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
        boost::detail::sp_assert_convertible< Y[], T[] >();
    }

    // aliasing

    template< class Y >
    shared_array( shared_array<Y> const & r, element_type * p ) BOOST_SP_NOEXCEPT : px( p ), pn( r.pn )
    {
    }

    // assignment

    shared_array & operator=( shared_array const & r ) BOOST_SP_NOEXCEPT
    {
        this_type( r ).swap( *this );
        return *this;
    }

#if !defined(BOOST_MSVC) || (BOOST_MSVC >= 1400)

    template<class Y>
    shared_array & operator=( shared_array<Y> const & r ) BOOST_SP_NOEXCEPT
    {
        this_type( r ).swap( *this );
        return *this;
    }

#endif

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    shared_array & operator=( shared_array && r ) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< shared_array && >( r ) ).swap( *this );
        return *this;
    }

    template<class Y>
    shared_array & operator=( shared_array<Y> && r ) BOOST_SP_NOEXCEPT
    {
        this_type( static_cast< shared_array<Y> && >( r ) ).swap( *this );
        return *this;
    }

#endif

    void reset() BOOST_SP_NOEXCEPT
    {
        this_type().swap( *this );
    }

    template<class Y> void reset( Y * p ) // Y must be complete
    {
        BOOST_ASSERT( p == 0 || p != px ); // catch self-reset errors
        this_type( p ).swap( *this );
    }

    template<class Y, class D> void reset( Y * p, D d )
    {
        this_type( p, d ).swap( *this );
    }

    template<class Y, class D, class A> void reset( Y * p, D d, A a )
    {
        this_type( p, d, a ).swap( *this );
    }

    template<class Y> void reset( shared_array<Y> const & r, element_type * p ) BOOST_SP_NOEXCEPT
    {
        this_type( r, p ).swap( *this );
    }

    T & operator[] (std::ptrdiff_t i) const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT(px != 0);
        BOOST_ASSERT(i >= 0);
        return px[i];
    }
    
    T * get() const BOOST_SP_NOEXCEPT
    {
        return px;
    }

// implicit conversion to "bool"
#include <boost/smart_ptr/detail/operator_bool.hpp>

    bool unique() const BOOST_SP_NOEXCEPT
    {
        return pn.unique();
    }

    long use_count() const BOOST_SP_NOEXCEPT
    {
        return pn.use_count();
    }

    void swap(shared_array<T> & other) BOOST_SP_NOEXCEPT
    {
        std::swap(px, other.px);
        pn.swap(other.pn);
    }

    void * _internal_get_deleter( boost::detail::sp_typeinfo_ const & ti ) const BOOST_SP_NOEXCEPT
    {
        return pn.get_deleter( ti );
    }

private:

    template<class Y> friend class shared_array;

    T * px;                     // contained pointer
    detail::shared_count pn;    // reference counter

};  // shared_array

template<class T> inline bool operator==(shared_array<T> const & a, shared_array<T> const & b) BOOST_SP_NOEXCEPT
{
    return a.get() == b.get();
}

template<class T> inline bool operator!=(shared_array<T> const & a, shared_array<T> const & b) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

#if !defined( BOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( shared_array<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( boost::detail::sp_nullptr_t, shared_array<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( shared_array<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( boost::detail::sp_nullptr_t, shared_array<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T> inline bool operator<(shared_array<T> const & a, shared_array<T> const & b) BOOST_SP_NOEXCEPT
{
    return std::less<T*>()(a.get(), b.get());
}

template<class T> void swap(shared_array<T> & a, shared_array<T> & b) BOOST_SP_NOEXCEPT
{
    a.swap(b);
}

template< class D, class T > D * get_deleter( shared_array<T> const & p ) BOOST_SP_NOEXCEPT
{
    return static_cast< D * >( p._internal_get_deleter( BOOST_SP_TYPEID_(D) ) );
}

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_SHARED_ARRAY_HPP_INCLUDED

/* shared_array.hpp
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
*/