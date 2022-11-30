#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_impl.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(BOOST_SP_USE_STD_ALLOCATOR) && defined(BOOST_SP_USE_QUICK_ALLOCATOR)
# error BOOST_SP_USE_STD_ALLOCATOR and BOOST_SP_USE_QUICK_ALLOCATOR are incompatible.
#endif

#include <boost/smart_ptr/detail/sp_counted_base.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/checked_delete.hpp>
#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)
#include <boost/smart_ptr/detail/quick_allocator.hpp>
#endif

#include <memory>           // std::allocator, std::allocator_traits
#include <cstddef>          // std::size_t

namespace boost
{

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

void sp_scalar_constructor_hook( void * px, std::size_t size, void * pn );
void sp_scalar_destructor_hook( void * px, std::size_t size, void * pn );

#endif

namespace detail
{

// get_local_deleter

template<class D> class local_sp_deleter;

template<class D> D * get_local_deleter( D * /*p*/ ) BOOST_SP_NOEXCEPT
{
    return 0;
}

template<class D> D * get_local_deleter( local_sp_deleter<D> * p ) BOOST_SP_NOEXCEPT;

//

template<class X> class BOOST_SYMBOL_VISIBLE sp_counted_impl_p: public sp_counted_base
{
private:

    X * px_;

    sp_counted_impl_p( sp_counted_impl_p const & );
    sp_counted_impl_p & operator= ( sp_counted_impl_p const & );

    typedef sp_counted_impl_p<X> this_type;

public:

    explicit sp_counted_impl_p( X * px ): px_( px )
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_constructor_hook( px, sizeof(X), this );
#endif
    }

    void dispose() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        boost::sp_scalar_destructor_hook( px_, sizeof(X), this );
#endif
        boost::checked_delete( px_ );
    }

    void * get_deleter( sp_typeinfo_ const & ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return 0;
    }

    void * get_local_deleter( sp_typeinfo_ const & ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return 0;
    }

    void * get_untyped_deleter() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return 0;
    }

#if defined(BOOST_SP_USE_STD_ALLOCATOR)

    void * operator new( std::size_t )
    {
        return std::allocator<this_type>().allocate( 1, static_cast<this_type *>(0) );
    }

    void operator delete( void * p )
    {
        std::allocator<this_type>().deallocate( static_cast<this_type *>(p), 1 );
    }

#endif

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)

    void * operator new( std::size_t )
    {
        return quick_allocator<this_type>::alloc();
    }

    void operator delete( void * p )
    {
        quick_allocator<this_type>::dealloc( p );
    }

#endif
};

//
// Borland's Codeguard trips up over the -Vx- option here:
//
#ifdef __CODEGUARD__
# pragma option push -Vx-
#endif

template<class P, class D> class BOOST_SYMBOL_VISIBLE sp_counted_impl_pd: public sp_counted_base
{
private:

    P ptr; // copy constructor must not throw
    D del; // copy/move constructor must not throw

    sp_counted_impl_pd( sp_counted_impl_pd const & );
    sp_counted_impl_pd & operator= ( sp_counted_impl_pd const & );

    typedef sp_counted_impl_pd<P, D> this_type;

public:

    // pre: d(p) must not throw

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    sp_counted_impl_pd( P p, D & d ): ptr( p ), del( static_cast< D&& >( d ) )
    {
    }

#else

    sp_counted_impl_pd( P p, D & d ): ptr( p ), del( d )
    {
    }

#endif

    sp_counted_impl_pd( P p ): ptr( p ), del()
    {
    }

    void dispose() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        del( ptr );
    }

    void * get_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return ti == BOOST_SP_TYPEID_(D)? &reinterpret_cast<char&>( del ): 0;
    }

    void * get_local_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return ti == BOOST_SP_TYPEID_(D)? boost::detail::get_local_deleter( boost::addressof( del ) ): 0;
    }

    void * get_untyped_deleter() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return &reinterpret_cast<char&>( del );
    }

#if defined(BOOST_SP_USE_STD_ALLOCATOR)

    void * operator new( std::size_t )
    {
        return std::allocator<this_type>().allocate( 1, static_cast<this_type *>(0) );
    }

    void operator delete( void * p )
    {
        std::allocator<this_type>().deallocate( static_cast<this_type *>(p), 1 );
    }

#endif

#if defined(BOOST_SP_USE_QUICK_ALLOCATOR)

    void * operator new( std::size_t )
    {
        return quick_allocator<this_type>::alloc();
    }

    void operator delete( void * p )
    {
        quick_allocator<this_type>::dealloc( p );
    }

#endif
};

template<class P, class D, class A> class BOOST_SYMBOL_VISIBLE sp_counted_impl_pda: public sp_counted_base
{
private:

    P p_; // copy constructor must not throw
    D d_; // copy/move constructor must not throw
    A a_; // copy constructor must not throw

    sp_counted_impl_pda( sp_counted_impl_pda const & );
    sp_counted_impl_pda & operator= ( sp_counted_impl_pda const & );

    typedef sp_counted_impl_pda<P, D, A> this_type;

public:

    // pre: d( p ) must not throw

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    sp_counted_impl_pda( P p, D & d, A a ): p_( p ), d_( static_cast< D&& >( d ) ), a_( a )
    {
    }

#else

    sp_counted_impl_pda( P p, D & d, A a ): p_( p ), d_( d ), a_( a )
    {
    }

#endif

    sp_counted_impl_pda( P p, A a ): p_( p ), d_( a ), a_( a )
    {
    }

    void dispose() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        d_( p_ );
    }

    void destroy() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
#if !defined( BOOST_NO_CXX11_ALLOCATOR )

        typedef typename std::allocator_traits<A>::template rebind_alloc< this_type > A2;

#else

        typedef typename A::template rebind< this_type >::other A2;

#endif

        A2 a2( a_ );

        this->~this_type();

        a2.deallocate( this, 1 );
    }

    void * get_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return ti == BOOST_SP_TYPEID_( D )? &reinterpret_cast<char&>( d_ ): 0;
    }

    void * get_local_deleter( sp_typeinfo_ const & ti ) BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return ti == BOOST_SP_TYPEID_( D )? boost::detail::get_local_deleter( boost::addressof( d_ ) ): 0;
    }

    void * get_untyped_deleter() BOOST_SP_NOEXCEPT BOOST_OVERRIDE
    {
        return &reinterpret_cast<char&>( d_ );
    }
};

#ifdef __CODEGUARD__
# pragma option pop
#endif

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_IMPL_HPP_INCLUDED

/* sp_counted_impl.hpp
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
*/