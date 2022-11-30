#ifndef BOOST_SMART_PTR_DETAIL_SHARED_COUNT_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SHARED_COUNT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/shared_count.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__BORLANDC__) && !defined(__clang__)
# pragma warn -8027     // Functions containing try are not expanded inline
#endif

#include <boost/smart_ptr/bad_weak_ptr.hpp>
#include <boost/smart_ptr/detail/sp_counted_base.hpp>
#include <boost/smart_ptr/detail/sp_counted_impl.hpp>
#include <boost/smart_ptr/detail/sp_disable_deprecated.hpp>
#include <boost/smart_ptr/detail/sp_noexcept.hpp>
#include <boost/checked_delete.hpp>
#include <boost/throw_exception.hpp>
#include <boost/core/addressof.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/cstdint.hpp>
#include <memory>            // std::auto_ptr
#include <functional>        // std::less
#include <cstddef>           // std::size_t

#ifdef BOOST_NO_EXCEPTIONS
# include <new>              // std::bad_alloc
#endif

#if defined( BOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace boost
{

namespace movelib
{

template< class T, class D > class unique_ptr;

} // namespace movelib

namespace detail
{

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)

int const shared_count_id = 0x2C35F101;
int const   weak_count_id = 0x298C38A4;

#endif

struct sp_nothrow_tag {};

template< class D > struct sp_inplace_tag
{
};

template< class T > class sp_reference_wrapper
{ 
public:

    explicit sp_reference_wrapper( T & t): t_( boost::addressof( t ) )
    {
    }

    template< class Y > void operator()( Y * p ) const
    {
        (*t_)( p );
    }

private:

    T * t_;
};

template< class D > struct sp_convert_reference
{
    typedef D type;
};

template< class D > struct sp_convert_reference< D& >
{
    typedef sp_reference_wrapper< D > type;
};

template<class T> std::size_t sp_hash_pointer( T* p ) BOOST_NOEXCEPT
{
    boost::uintptr_t v = reinterpret_cast<boost::uintptr_t>( p );

    // match boost::hash<T*>
    return static_cast<std::size_t>( v + ( v >> 3 ) );
}

class weak_count;

class shared_count
{
private:

    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class weak_count;

public:

    BOOST_CONSTEXPR shared_count() BOOST_SP_NOEXCEPT: pi_(0)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }

    BOOST_CONSTEXPR explicit shared_count( sp_counted_base * pi ) BOOST_SP_NOEXCEPT: pi_( pi )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
    }

    template<class Y> explicit shared_count( Y * p ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_p<Y>( p );
        }
        catch(...)
        {
            boost::checked_delete( p );
            throw;
        }

#else

        pi_ = new sp_counted_impl_p<Y>( p );

        if( pi_ == 0 )
        {
            boost::checked_delete( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif
    }

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1200 )
    template<class Y, class D> shared_count( Y * p, D d ): pi_(0)
#else
    template<class P, class D> shared_count( P p, D d ): pi_(0)
#endif
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, <= 1200 )
        typedef Y* P;
#endif
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_pd<P, D>(p, d);
        }
        catch(...)
        {
            d(p); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_impl_pd<P, D>(p, d);

        if(pi_ == 0)
        {
            d(p); // delete p
            boost::throw_exception(std::bad_alloc());
        }

#endif
    }

#if !defined( BOOST_NO_FUNCTION_TEMPLATE_ORDERING )

    template< class P, class D > shared_count( P p, sp_inplace_tag<D> ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = new sp_counted_impl_pd< P, D >( p );
        }
        catch( ... )
        {
            D::operator_fn( p ); // delete p
            throw;
        }

#else

        pi_ = new sp_counted_impl_pd< P, D >( p );

        if( pi_ == 0 )
        {
            D::operator_fn( p ); // delete p
            boost::throw_exception( std::bad_alloc() );
        }

#endif // #ifndef BOOST_NO_EXCEPTIONS
    }

#endif // !defined( BOOST_NO_FUNCTION_TEMPLATE_ORDERING )

    template<class P, class D, class A> shared_count( P p, D d, A a ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef sp_counted_impl_pda<P, D, A> impl_type;

#if !defined( BOOST_NO_CXX11_ALLOCATOR )

        typedef typename std::allocator_traits<A>::template rebind_alloc< impl_type > A2;

#else

        typedef typename A::template rebind< impl_type >::other A2;

#endif

        A2 a2( a );

#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = a2.allocate( 1 );
            ::new( static_cast< void* >( pi_ ) ) impl_type( p, d, a );
        }
        catch(...)
        {
            d( p );

            if( pi_ != 0 )
            {
                a2.deallocate( static_cast< impl_type* >( pi_ ), 1 );
            }

            throw;
        }

#else

        pi_ = a2.allocate( 1 );

        if( pi_ != 0 )
        {
            ::new( static_cast< void* >( pi_ ) ) impl_type( p, d, a );
        }
        else
        {
            d( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif
    }

#if !defined( BOOST_NO_FUNCTION_TEMPLATE_ORDERING )

    template< class P, class D, class A > shared_count( P p, sp_inplace_tag< D >, A a ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef sp_counted_impl_pda< P, D, A > impl_type;

#if !defined( BOOST_NO_CXX11_ALLOCATOR )

        typedef typename std::allocator_traits<A>::template rebind_alloc< impl_type > A2;

#else

        typedef typename A::template rebind< impl_type >::other A2;

#endif

        A2 a2( a );

#ifndef BOOST_NO_EXCEPTIONS

        try
        {
            pi_ = a2.allocate( 1 );
            ::new( static_cast< void* >( pi_ ) ) impl_type( p, a );
        }
        catch(...)
        {
            D::operator_fn( p );

            if( pi_ != 0 )
            {
                a2.deallocate( static_cast< impl_type* >( pi_ ), 1 );
            }

            throw;
        }

#else

        pi_ = a2.allocate( 1 );

        if( pi_ != 0 )
        {
            ::new( static_cast< void* >( pi_ ) ) impl_type( p, a );
        }
        else
        {
            D::operator_fn( p );
            boost::throw_exception( std::bad_alloc() );
        }

#endif // #ifndef BOOST_NO_EXCEPTIONS
    }

#endif // !defined( BOOST_NO_FUNCTION_TEMPLATE_ORDERING )

#ifndef BOOST_NO_AUTO_PTR

    // auto_ptr<Y> is special cased to provide the strong guarantee

    template<class Y>
    explicit shared_count( std::auto_ptr<Y> & r ): pi_( new sp_counted_impl_p<Y>( r.get() ) )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
#ifdef BOOST_NO_EXCEPTIONS

        if( pi_ == 0 )
        {
            boost::throw_exception(std::bad_alloc());
        }

#endif

        r.release();
    }

#endif 

#if !defined( BOOST_NO_CXX11_SMART_PTR )

    template<class Y, class D>
    explicit shared_count( std::unique_ptr<Y, D> & r ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef typename sp_convert_reference<D>::type D2;

        D2 d2( static_cast<D&&>( r.get_deleter() ) );
        pi_ = new sp_counted_impl_pd< typename std::unique_ptr<Y, D>::pointer, D2 >( r.get(), d2 );

#ifdef BOOST_NO_EXCEPTIONS

        if( pi_ == 0 )
        {
            boost::throw_exception( std::bad_alloc() );
        }

#endif

        r.release();
    }

#endif

    template<class Y, class D>
    explicit shared_count( boost::movelib::unique_ptr<Y, D> & r ): pi_( 0 )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        typedef typename sp_convert_reference<D>::type D2;

        D2 d2( r.get_deleter() );
        pi_ = new sp_counted_impl_pd< typename boost::movelib::unique_ptr<Y, D>::pointer, D2 >( r.get(), d2 );

#ifdef BOOST_NO_EXCEPTIONS

        if( pi_ == 0 )
        {
            boost::throw_exception( std::bad_alloc() );
        }

#endif

        r.release();
    }

    ~shared_count() /*BOOST_SP_NOEXCEPT*/
    {
        if( pi_ != 0 ) pi_->release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    shared_count(shared_count const & r) BOOST_SP_NOEXCEPT: pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        if( pi_ != 0 ) pi_->add_ref_copy();
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    shared_count(shared_count && r) BOOST_SP_NOEXCEPT: pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
    {
        r.pi_ = 0;
    }

#endif

    explicit shared_count(weak_count const & r); // throws bad_weak_ptr when r.use_count() == 0
    shared_count( weak_count const & r, sp_nothrow_tag ) BOOST_SP_NOEXCEPT; // constructs an empty *this when r.use_count() == 0

    shared_count & operator= (shared_count const & r) BOOST_SP_NOEXCEPT
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if( tmp != 0 ) tmp->add_ref_copy();
            if( pi_ != 0 ) pi_->release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(shared_count & r) BOOST_SP_NOEXCEPT
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const BOOST_SP_NOEXCEPT
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    bool unique() const BOOST_SP_NOEXCEPT
    {
        return use_count() == 1;
    }

    bool empty() const BOOST_SP_NOEXCEPT
    {
        return pi_ == 0;
    }

    bool operator==( shared_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return pi_ == r.pi_;
    }

    bool operator==( weak_count const & r ) const BOOST_SP_NOEXCEPT;

    bool operator<( shared_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return std::less<sp_counted_base *>()( pi_, r.pi_ );
    }

    bool operator<( weak_count const & r ) const BOOST_SP_NOEXCEPT;

    void * get_deleter( sp_typeinfo_ const & ti ) const BOOST_SP_NOEXCEPT
    {
        return pi_? pi_->get_deleter( ti ): 0;
    }

    void * get_local_deleter( sp_typeinfo_ const & ti ) const BOOST_SP_NOEXCEPT
    {
        return pi_? pi_->get_local_deleter( ti ): 0;
    }

    void * get_untyped_deleter() const BOOST_SP_NOEXCEPT
    {
        return pi_? pi_->get_untyped_deleter(): 0;
    }

    std::size_t hash_value() const BOOST_SP_NOEXCEPT
    {
        return sp_hash_pointer( pi_ );
    }
};


class weak_count
{
private:

    sp_counted_base * pi_;

#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
    int id_;
#endif

    friend class shared_count;

public:

    BOOST_CONSTEXPR weak_count() BOOST_SP_NOEXCEPT: pi_(0)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
    }

    weak_count(shared_count const & r) BOOST_SP_NOEXCEPT: pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

    weak_count(weak_count const & r) BOOST_SP_NOEXCEPT: pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        if(pi_ != 0) pi_->weak_add_ref();
    }

// Move support

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    weak_count(weak_count && r) BOOST_SP_NOEXCEPT: pi_(r.pi_)
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(weak_count_id)
#endif
    {
        r.pi_ = 0;
    }

#endif

    ~weak_count() /*BOOST_SP_NOEXCEPT*/
    {
        if(pi_ != 0) pi_->weak_release();
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        id_ = 0;
#endif
    }

    weak_count & operator= (shared_count const & r) BOOST_SP_NOEXCEPT
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if(tmp != 0) tmp->weak_add_ref();
            if(pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }

    weak_count & operator= (weak_count const & r) BOOST_SP_NOEXCEPT
    {
        sp_counted_base * tmp = r.pi_;

        if( tmp != pi_ )
        {
            if(tmp != 0) tmp->weak_add_ref();
            if(pi_ != 0) pi_->weak_release();
            pi_ = tmp;
        }

        return *this;
    }

    void swap(weak_count & r) BOOST_SP_NOEXCEPT
    {
        sp_counted_base * tmp = r.pi_;
        r.pi_ = pi_;
        pi_ = tmp;
    }

    long use_count() const BOOST_SP_NOEXCEPT
    {
        return pi_ != 0? pi_->use_count(): 0;
    }

    bool empty() const BOOST_SP_NOEXCEPT
    {
        return pi_ == 0;
    }

    bool operator==( weak_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return pi_ == r.pi_;
    }

    bool operator==( shared_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return pi_ == r.pi_;
    }

    bool operator<( weak_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return std::less<sp_counted_base *>()( pi_, r.pi_ );
    }

    bool operator<( shared_count const & r ) const BOOST_SP_NOEXCEPT
    {
        return std::less<sp_counted_base *>()( pi_, r.pi_ );
    }

    std::size_t hash_value() const BOOST_SP_NOEXCEPT
    {
        return sp_hash_pointer( pi_ );
    }
};

inline shared_count::shared_count( weak_count const & r ): pi_( r.pi_ )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if( pi_ == 0 || !pi_->add_ref_lock() )
    {
        boost::throw_exception( boost::bad_weak_ptr() );
    }
}

inline shared_count::shared_count( weak_count const & r, sp_nothrow_tag ) BOOST_SP_NOEXCEPT: pi_( r.pi_ )
#if defined(BOOST_SP_ENABLE_DEBUG_HOOKS)
        , id_(shared_count_id)
#endif
{
    if( pi_ != 0 && !pi_->add_ref_lock() )
    {
        pi_ = 0;
    }
}

inline bool shared_count::operator==( weak_count const & r ) const BOOST_SP_NOEXCEPT
{
    return pi_ == r.pi_;
}

inline bool shared_count::operator<( weak_count const & r ) const BOOST_SP_NOEXCEPT
{
    return std::less<sp_counted_base *>()( pi_, r.pi_ );
}

} // namespace detail

} // namespace boost

#if defined( BOOST_SP_DISABLE_DEPRECATED )
#pragma GCC diagnostic pop
#endif

#if defined(__BORLANDC__) && !defined(__clang__)
# pragma warn .8027     // Functions containing try are not expanded inline
#endif

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SHARED_COUNT_HPP_INCLUDED

/* shared_count.hpp
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
*/