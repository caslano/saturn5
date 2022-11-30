#ifndef BOOST_SMART_PTR_LOCAL_SHARED_PTR_HPP_INCLUDED
#define BOOST_SMART_PTR_LOCAL_SHARED_PTR_HPP_INCLUDED

//  local_shared_ptr.hpp
//
//  Copyright 2017 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.

#include <boost/smart_ptr/shared_ptr.hpp>

namespace boost
{

template<class T> class local_shared_ptr;

namespace detail
{

template< class E, class Y > inline void lsp_pointer_construct( boost::local_shared_ptr< E > * /*ppx*/, Y * p, boost::detail::local_counted_base * & pn )
{
    boost::detail::sp_assert_convertible< Y, E >();

    typedef boost::detail::local_sp_deleter< boost::checked_deleter<Y> > D;

    boost::shared_ptr<E> p2( p, D() );

    D * pd = static_cast< D * >( p2._internal_get_untyped_deleter() );

    pd->pn_ = p2._internal_count();

    pn = pd;
}

template< class E, class Y > inline void lsp_pointer_construct( boost::local_shared_ptr< E[] > * /*ppx*/, Y * p, boost::detail::local_counted_base * & pn )
{
    boost::detail::sp_assert_convertible< Y[], E[] >();

    typedef boost::detail::local_sp_deleter< boost::checked_array_deleter<E> > D;

    boost::shared_ptr<E[]> p2( p, D() );

    D * pd = static_cast< D * >( p2._internal_get_untyped_deleter() );

    pd->pn_ = p2._internal_count();

    pn = pd;
}

template< class E, std::size_t N, class Y > inline void lsp_pointer_construct( boost::local_shared_ptr< E[N] > * /*ppx*/, Y * p, boost::detail::local_counted_base * & pn )
{
    boost::detail::sp_assert_convertible< Y[N], E[N] >();

    typedef boost::detail::local_sp_deleter< boost::checked_array_deleter<E> > D;

    boost::shared_ptr<E[N]> p2( p, D() );

    D * pd = static_cast< D * >( p2._internal_get_untyped_deleter() );

    pd->pn_ = p2._internal_count();

    pn = pd;
}

template< class E, class P, class D > inline void lsp_deleter_construct( boost::local_shared_ptr< E > * /*ppx*/, P p, D const& d, boost::detail::local_counted_base * & pn )
{
    typedef boost::detail::local_sp_deleter<D> D2;

    boost::shared_ptr<E> p2( p, D2( d ) );

    D2 * pd = static_cast< D2 * >( p2._internal_get_untyped_deleter() );

    pd->pn_ = p2._internal_count();

    pn = pd;
}

template< class E, class P, class D, class A > inline void lsp_allocator_construct( boost::local_shared_ptr< E > * /*ppx*/, P p, D const& d, A const& a, boost::detail::local_counted_base * & pn )
{
    typedef boost::detail::local_sp_deleter<D> D2;

    boost::shared_ptr<E> p2( p, D2( d ), a );

    D2 * pd = static_cast< D2 * >( p2._internal_get_untyped_deleter() );

    pd->pn_ = p2._internal_count();

    pn = pd;
}

struct lsp_internal_constructor_tag
{
};

} // namespace detail

//
// local_shared_ptr
//
// as shared_ptr, but local to a thread.
// reference count manipulations are non-atomic.
//

template<class T> class local_shared_ptr
{
private:

    typedef local_shared_ptr this_type;

public:

    typedef typename boost::detail::sp_element<T>::type element_type;

private:

    element_type * px;
    boost::detail::local_counted_base * pn;

    template<class Y> friend class local_shared_ptr;

public:

    // destructor

    ~local_shared_ptr() BOOST_SP_NOEXCEPT
    {
        if( pn )
        {
            pn->release();
        }
    }

    // constructors

    BOOST_CONSTEXPR local_shared_ptr() BOOST_SP_NOEXCEPT : px( 0 ), pn( 0 )
    {
    }

#if !defined( BOOST_NO_CXX11_NULLPTR )

    BOOST_CONSTEXPR local_shared_ptr( boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT : px( 0 ), pn( 0 )
    {
    }

#endif

    // internal constructor, used by make_shared
    BOOST_CONSTEXPR local_shared_ptr( boost::detail::lsp_internal_constructor_tag, element_type * px_, boost::detail::local_counted_base * pn_ ) BOOST_SP_NOEXCEPT : px( px_ ), pn( pn_ )
    {
    }

    template<class Y>
    explicit local_shared_ptr( Y * p ): px( p ), pn( 0 )
    {
        boost::detail::lsp_pointer_construct( this, p, pn );
    }

    template<class Y, class D> local_shared_ptr( Y * p, D d ): px( p ), pn( 0 )
    {
        boost::detail::lsp_deleter_construct( this, p, d, pn );
    }

#if !defined( BOOST_NO_CXX11_NULLPTR )

    template<class D> local_shared_ptr( boost::detail::sp_nullptr_t p, D d ): px( p ), pn( 0 )
    {
        boost::detail::lsp_deleter_construct( this, p, d, pn );
    }

#endif

    template<class Y, class D, class A> local_shared_ptr( Y * p, D d, A a ): px( p ), pn( 0 )
    {
        boost::detail::lsp_allocator_construct( this, p, d, a, pn );
    }

#if !defined( BOOST_NO_CXX11_NULLPTR )

    template<class D, class A> local_shared_ptr( boost::detail::sp_nullptr_t p, D d, A a ): px( p ), pn( 0 )
    {
        boost::detail::lsp_allocator_construct( this, p, d, a, pn );
    }

#endif

    // construction from shared_ptr

    template<class Y> local_shared_ptr( shared_ptr<Y> const & r,
        typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty() )
        : px( r.get() ), pn( 0 )
    {
        boost::detail::sp_assert_convertible< Y, T >();

        if( r.use_count() != 0 )
        {
            pn = new boost::detail::local_counted_impl( r._internal_count() );
        }
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y> local_shared_ptr( shared_ptr<Y> && r,
        typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty() )
        : px( r.get() ), pn( 0 )
    {
        boost::detail::sp_assert_convertible< Y, T >();

        if( r.use_count() != 0 )
        {
            pn = new boost::detail::local_counted_impl( r._internal_count() );
            r.reset();
        }
    }

#endif

    // construction from unique_ptr

#if !defined( BOOST_NO_CXX11_SMART_PTR ) && !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template< class Y, class D >
    local_shared_ptr( std::unique_ptr< Y, D > && r,
        typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty() )
        : px( r.get() ), pn( 0 )
    {
        boost::detail::sp_assert_convertible< Y, T >();

        if( px )
        {
            pn = new boost::detail::local_counted_impl( shared_ptr<T>( std::move(r) )._internal_count() );
        }
    }

#endif

    template< class Y, class D >
    local_shared_ptr( boost::movelib::unique_ptr< Y, D > r ); // !
    //  : px( r.get() ), pn( new boost::detail::local_counted_impl( shared_ptr<T>( std::move(r) ) ) )
    //{
    //    boost::detail::sp_assert_convertible< Y, T >();
    //}

    // copy constructor

    local_shared_ptr( local_shared_ptr const & r ) BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
        if( pn )
        {
            pn->add_ref();
        }
    }

    // move constructor

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    local_shared_ptr( local_shared_ptr && r ) BOOST_SP_NOEXCEPT : px( r.px ), pn( r.pn )
    {
        r.px = 0;
        r.pn = 0;
    }

#endif

    // converting copy constructor

    template<class Y> local_shared_ptr( local_shared_ptr<Y> const & r,
        typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty() ) BOOST_SP_NOEXCEPT
        : px( r.px ), pn( r.pn )
    {
        boost::detail::sp_assert_convertible< Y, T >();

        if( pn )
        {
            pn->add_ref();
        }
    }

    // converting move constructor

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y> local_shared_ptr( local_shared_ptr<Y> && r,
        typename boost::detail::sp_enable_if_convertible<Y, T>::type = boost::detail::sp_empty() ) BOOST_SP_NOEXCEPT
        : px( r.px ), pn( r.pn )
    {
        boost::detail::sp_assert_convertible< Y, T >();

        r.px = 0;
        r.pn = 0;
    }

#endif

    // aliasing

    template<class Y>
    local_shared_ptr( local_shared_ptr<Y> const & r, element_type * p ) BOOST_SP_NOEXCEPT : px( p ), pn( r.pn )
    {
        if( pn )
        {
            pn->add_ref();
        }
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y>
    local_shared_ptr( local_shared_ptr<Y> && r, element_type * p ) BOOST_SP_NOEXCEPT : px( p ), pn( r.pn )
    {
        r.px = 0;
        r.pn = 0;
    }

#endif

    // assignment

    local_shared_ptr & operator=( local_shared_ptr const & r ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( r ).swap( *this );
        return *this;
    }

    template<class Y> local_shared_ptr & operator=( local_shared_ptr<Y> const & r ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( r ).swap( *this );
        return *this;
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    local_shared_ptr & operator=( local_shared_ptr && r ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( std::move( r ) ).swap( *this );
        return *this;
    }

    template<class Y>
    local_shared_ptr & operator=( local_shared_ptr<Y> && r ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( std::move( r ) ).swap( *this );
        return *this;
    }

#endif

#if !defined( BOOST_NO_CXX11_NULLPTR )

    local_shared_ptr & operator=( boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr().swap(*this);
        return *this;
    }

#endif

#if !defined( BOOST_NO_CXX11_SMART_PTR ) && !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y, class D>
    local_shared_ptr & operator=( std::unique_ptr<Y, D> && r )
    {
        local_shared_ptr( std::move(r) ).swap( *this );
        return *this;
    }

#endif

    template<class Y, class D>
    local_shared_ptr & operator=( boost::movelib::unique_ptr<Y, D> r ); // !

    // reset

    void reset() BOOST_SP_NOEXCEPT
    {
        local_shared_ptr().swap( *this );
    }

    template<class Y> void reset( Y * p ) // Y must be complete
    {
        local_shared_ptr( p ).swap( *this );
    }

    template<class Y, class D> void reset( Y * p, D d )
    {
        local_shared_ptr( p, d ).swap( *this );
    }

    template<class Y, class D, class A> void reset( Y * p, D d, A a )
    {
        local_shared_ptr( p, d, a ).swap( *this );
    }

    template<class Y> void reset( local_shared_ptr<Y> const & r, element_type * p ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( r, p ).swap( *this );
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class Y> void reset( local_shared_ptr<Y> && r, element_type * p ) BOOST_SP_NOEXCEPT
    {
        local_shared_ptr( std::move( r ), p ).swap( *this );
    }

#endif

    // accessors

    typename boost::detail::sp_dereference< T >::type operator* () const BOOST_SP_NOEXCEPT
    {
        return *px;
    }

    typename boost::detail::sp_member_access< T >::type operator-> () const BOOST_SP_NOEXCEPT
    {
        return px;
    }

    typename boost::detail::sp_array_access< T >::type operator[] ( std::ptrdiff_t i ) const BOOST_SP_NOEXCEPT_WITH_ASSERT
    {
        BOOST_ASSERT( px != 0 );
        BOOST_ASSERT( i >= 0 && ( i < boost::detail::sp_extent< T >::value || boost::detail::sp_extent< T >::value == 0 ) );

        return static_cast< typename boost::detail::sp_array_access< T >::type >( px[ i ] );
    }

    element_type * get() const BOOST_SP_NOEXCEPT
    {
        return px;
    }

    // implicit conversion to "bool"
#include <boost/smart_ptr/detail/operator_bool.hpp>

    long local_use_count() const BOOST_SP_NOEXCEPT
    {
        return pn? pn->local_use_count(): 0;
    }

    // conversions to shared_ptr, weak_ptr

#if !defined( BOOST_SP_NO_SP_CONVERTIBLE ) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
    template<class Y, class E = typename boost::detail::sp_enable_if_convertible<T,Y>::type> operator shared_ptr<Y>() const BOOST_SP_NOEXCEPT
#else
    template<class Y> operator shared_ptr<Y>() const BOOST_SP_NOEXCEPT
#endif
    {
        boost::detail::sp_assert_convertible<T, Y>();

        if( pn )
        {
            return shared_ptr<Y>( boost::detail::sp_internal_constructor_tag(), px, pn->local_cb_get_shared_count() );
        }
        else
        {
            return shared_ptr<Y>();
        }
    }

#if !defined( BOOST_SP_NO_SP_CONVERTIBLE ) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
    template<class Y, class E = typename boost::detail::sp_enable_if_convertible<T,Y>::type> operator weak_ptr<Y>() const BOOST_SP_NOEXCEPT
#else
    template<class Y> operator weak_ptr<Y>() const BOOST_SP_NOEXCEPT
#endif
    {
        boost::detail::sp_assert_convertible<T, Y>();

        if( pn )
        {
            return shared_ptr<Y>( boost::detail::sp_internal_constructor_tag(), px, pn->local_cb_get_shared_count() );
        }
        else
        {
            return weak_ptr<Y>();
        }
    }

    // swap

    void swap( local_shared_ptr & r ) BOOST_SP_NOEXCEPT
    {
        std::swap( px, r.px );
        std::swap( pn, r.pn );
    }

    // owner_before

    template<class Y> bool owner_before( local_shared_ptr<Y> const & r ) const BOOST_SP_NOEXCEPT
    {
        return std::less< boost::detail::local_counted_base* >()( pn, r.pn );
    }

    // owner_equals

    template<class Y> bool owner_equals( local_shared_ptr<Y> const & r ) const BOOST_SP_NOEXCEPT
    {
        return pn == r.pn;
    }
};

template<class T, class U> inline bool operator==( local_shared_ptr<T> const & a, local_shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=( local_shared_ptr<T> const & a, local_shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

#if !defined( BOOST_NO_CXX11_NULLPTR )

template<class T> inline bool operator==( local_shared_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator==( boost::detail::sp_nullptr_t, local_shared_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() == 0;
}

template<class T> inline bool operator!=( local_shared_ptr<T> const & p, boost::detail::sp_nullptr_t ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

template<class T> inline bool operator!=( boost::detail::sp_nullptr_t, local_shared_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get() != 0;
}

#endif

template<class T, class U> inline bool operator==( local_shared_ptr<T> const & a, shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=( local_shared_ptr<T> const & a, shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

template<class T, class U> inline bool operator==( shared_ptr<T> const & a, local_shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() == b.get();
}

template<class T, class U> inline bool operator!=( shared_ptr<T> const & a, local_shared_ptr<U> const & b ) BOOST_SP_NOEXCEPT
{
    return a.get() != b.get();
}

template<class T, class U> inline bool operator<(local_shared_ptr<T> const & a, local_shared_ptr<U> const & b) BOOST_SP_NOEXCEPT
{
    return a.owner_before( b );
}

template<class T> inline void swap( local_shared_ptr<T> & a, local_shared_ptr<T> & b ) BOOST_SP_NOEXCEPT
{
    a.swap( b );
}

template<class T, class U> local_shared_ptr<T> static_pointer_cast( local_shared_ptr<U> const & r ) BOOST_SP_NOEXCEPT
{
    (void) static_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = static_cast< E* >( r.get() );
    return local_shared_ptr<T>( r, p );
}

template<class T, class U> local_shared_ptr<T> const_pointer_cast( local_shared_ptr<U> const & r ) BOOST_SP_NOEXCEPT
{
    (void) const_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = const_cast< E* >( r.get() );
    return local_shared_ptr<T>( r, p );
}

template<class T, class U> local_shared_ptr<T> dynamic_pointer_cast( local_shared_ptr<U> const & r ) BOOST_SP_NOEXCEPT
{
    (void) dynamic_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = dynamic_cast< E* >( r.get() );
    return p? local_shared_ptr<T>( r, p ): local_shared_ptr<T>();
}

template<class T, class U> local_shared_ptr<T> reinterpret_pointer_cast( local_shared_ptr<U> const & r ) BOOST_SP_NOEXCEPT
{
    (void) reinterpret_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = reinterpret_cast< E* >( r.get() );
    return local_shared_ptr<T>( r, p );
}

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

template<class T, class U> local_shared_ptr<T> static_pointer_cast( local_shared_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) static_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = static_cast< E* >( r.get() );
    return local_shared_ptr<T>( std::move(r), p );
}

template<class T, class U> local_shared_ptr<T> const_pointer_cast( local_shared_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) const_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = const_cast< E* >( r.get() );
    return local_shared_ptr<T>( std::move(r), p );
}

template<class T, class U> local_shared_ptr<T> dynamic_pointer_cast( local_shared_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) dynamic_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = dynamic_cast< E* >( r.get() );
    return p? local_shared_ptr<T>( std::move(r), p ): local_shared_ptr<T>();
}

template<class T, class U> local_shared_ptr<T> reinterpret_pointer_cast( local_shared_ptr<U> && r ) BOOST_SP_NOEXCEPT
{
    (void) reinterpret_cast< T* >( static_cast< U* >( 0 ) );

    typedef typename local_shared_ptr<T>::element_type E;

    E * p = reinterpret_cast< E* >( r.get() );
    return local_shared_ptr<T>( std::move(r), p );
}

#endif // !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

// get_pointer() enables boost::mem_fn to recognize local_shared_ptr

template<class T> inline typename local_shared_ptr<T>::element_type * get_pointer( local_shared_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return p.get();
}

// operator<<

#if !defined(BOOST_NO_IOSTREAM)

template<class E, class T, class Y> std::basic_ostream<E, T> & operator<< ( std::basic_ostream<E, T> & os, local_shared_ptr<Y> const & p )
{
    os << p.get();
    return os;
}

#endif // !defined(BOOST_NO_IOSTREAM)

// get_deleter

template<class D, class T> D * get_deleter( local_shared_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return get_deleter<D>( shared_ptr<T>( p ) );
}

// hash_value

template< class T > struct hash;

template< class T > std::size_t hash_value( local_shared_ptr<T> const & p ) BOOST_SP_NOEXCEPT
{
    return boost::hash< typename local_shared_ptr<T>::element_type* >()( p.get() );
}

} // namespace boost

// std::hash

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

namespace std
{

template<class T> struct hash< ::boost::local_shared_ptr<T> >
{
    std::size_t operator()( ::boost::local_shared_ptr<T> const & p ) const BOOST_SP_NOEXCEPT
    {
        return std::hash< typename ::boost::local_shared_ptr<T>::element_type* >()( p.get() );
    }
};

} // namespace std

#endif // #if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

#endif  // #ifndef BOOST_SMART_PTR_LOCAL_SHARED_PTR_HPP_INCLUDED

/* local_shared_ptr.hpp
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
*/