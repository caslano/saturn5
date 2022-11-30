#ifndef BOOST_SMART_PTR_ATOMIC_SHARED_PTR_HPP_INCLUDED
#define BOOST_SMART_PTR_ATOMIC_SHARED_PTR_HPP_INCLUDED

//
//  atomic_shared_ptr.hpp
//
//  Copyright 2017 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <cstring>

namespace boost
{

template<class T> class atomic_shared_ptr
{
private:

    boost::shared_ptr<T> p_;

    mutable boost::detail::spinlock l_;

    atomic_shared_ptr(const atomic_shared_ptr&);
    atomic_shared_ptr& operator=(const atomic_shared_ptr&);

private:

    bool compare_exchange( shared_ptr<T>& v, shared_ptr<T> w ) BOOST_SP_NOEXCEPT
    {
        l_.lock();

        if( p_._internal_equiv( v ) )
        {
            p_.swap( w );

            l_.unlock();
            return true;
        }
        else
        {
            shared_ptr<T> tmp( p_ );

            l_.unlock();

            tmp.swap( v );
            return false;
        }
    }

public:

#if !defined( BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX ) && !defined( BOOST_NO_CXX11_CONSTEXPR )

    constexpr atomic_shared_ptr() BOOST_SP_NOEXCEPT: l_ BOOST_DETAIL_SPINLOCK_INIT
    {
    }

    atomic_shared_ptr( shared_ptr<T> p ) BOOST_SP_NOEXCEPT
        : p_( std::move( p ) ), l_ BOOST_DETAIL_SPINLOCK_INIT
    {
    }

#else

    atomic_shared_ptr() BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock init = BOOST_DETAIL_SPINLOCK_INIT;
        std::memcpy( &l_, &init, sizeof( init ) );
    }

    atomic_shared_ptr( shared_ptr<T> p ) BOOST_SP_NOEXCEPT
#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )
        : p_( std::move( p ) )
#else
        : p_( p )
#endif
    {
        boost::detail::spinlock init = BOOST_DETAIL_SPINLOCK_INIT;
        std::memcpy( &l_, &init, sizeof( init ) );
    }

#endif

    atomic_shared_ptr& operator=( shared_ptr<T> r ) BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        p_.swap( r );

        return *this;
    }

    BOOST_CONSTEXPR bool is_lock_free() const BOOST_SP_NOEXCEPT
    {
        return false;
    }

    shared_ptr<T> load() const BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        return p_;
    }

    template<class M> shared_ptr<T> load( M ) const BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        return p_;
    }

    operator shared_ptr<T>() const BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        return p_;
    }

    void store( shared_ptr<T> r ) BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        p_.swap( r );
    }

    template<class M> void store( shared_ptr<T> r, M ) BOOST_SP_NOEXCEPT
    {
        boost::detail::spinlock::scoped_lock lock( l_ );
        p_.swap( r );
    }

    shared_ptr<T> exchange( shared_ptr<T> r ) BOOST_SP_NOEXCEPT
    {
        {
            boost::detail::spinlock::scoped_lock lock( l_ );
            p_.swap( r );
        }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

        return std::move( r );

#else

        return r;

#endif
    }

    template<class M> shared_ptr<T> exchange( shared_ptr<T> r, M ) BOOST_SP_NOEXCEPT
    {
        {
            boost::detail::spinlock::scoped_lock lock( l_ );
            p_.swap( r );
        }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

        return std::move( r );

#else

        return r;

#endif
    }

    template<class M> bool compare_exchange_weak( shared_ptr<T>& v, const shared_ptr<T>& w, M, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

    template<class M> bool compare_exchange_weak( shared_ptr<T>& v, const shared_ptr<T>& w, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

    bool compare_exchange_weak( shared_ptr<T>& v, const shared_ptr<T>& w ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

    template<class M> bool compare_exchange_strong( shared_ptr<T>& v, const shared_ptr<T>& w, M, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

    template<class M> bool compare_exchange_strong( shared_ptr<T>& v, const shared_ptr<T>& w, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

    bool compare_exchange_strong( shared_ptr<T>& v, const shared_ptr<T>& w ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, w );
    }

#if !defined( BOOST_NO_CXX11_RVALUE_REFERENCES )

    template<class M> bool compare_exchange_weak( shared_ptr<T>& v, shared_ptr<T>&& w, M, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

    template<class M> bool compare_exchange_weak( shared_ptr<T>& v, shared_ptr<T>&& w, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

    bool compare_exchange_weak( shared_ptr<T>& v, shared_ptr<T>&& w ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

    template<class M> bool compare_exchange_strong( shared_ptr<T>& v, shared_ptr<T>&& w, M, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

    template<class M> bool compare_exchange_strong( shared_ptr<T>& v, shared_ptr<T>&& w, M ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

    bool compare_exchange_strong( shared_ptr<T>& v, shared_ptr<T>&& w ) BOOST_SP_NOEXCEPT
    {
        return compare_exchange( v, std::move( w ) );
    }

#endif
};

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_ATOMIC_SHARED_PTR_HPP_INCLUDED

/* atomic_shared_ptr.hpp
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
*/