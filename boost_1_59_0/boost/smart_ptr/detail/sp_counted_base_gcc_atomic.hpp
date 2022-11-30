#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_ATOMIC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_ATOMIC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// detail/sp_counted_base_gcc_atomic.hpp - g++ 4.7+ __atomic intrinsics
//
// Copyright 2007, 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using __atomic sp_counted_base")

#endif

namespace boost
{

namespace detail
{

inline void atomic_increment( boost::uint_least32_t * pw )
{
    __atomic_fetch_add( pw, 1, __ATOMIC_RELAXED );
}

inline boost::uint_least32_t atomic_decrement( boost::uint_least32_t * pw )
{
    return __atomic_fetch_sub( pw, 1, __ATOMIC_ACQ_REL );
}

inline boost::uint_least32_t atomic_conditional_increment( boost::uint_least32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    boost::uint_least32_t r = __atomic_load_n( pw, __ATOMIC_RELAXED );

    for( ;; )
    {
        if( r == 0 )
        {
            return r;
        }

        if( __atomic_compare_exchange_n( pw, &r, r + 1, true, __ATOMIC_RELAXED, __ATOMIC_RELAXED ) )
        {
            return r;
        }
    }
}

inline boost::uint_least32_t atomic_load( boost::uint_least32_t const * pw )
{
    return __atomic_load_n( pw, __ATOMIC_ACQUIRE );
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    boost::uint_least32_t use_count_;        // #shared
    boost::uint_least32_t weak_count_;       // #weak + (#shared != 0)

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
    }

    virtual ~sp_counted_base() // nothrow
    {
    }

    // dispose() is called when use_count_ drops to zero, to release
    // the resources managed by *this.

    virtual void dispose() = 0; // nothrow

    // destroy() is called when weak_count_ drops to zero.

    virtual void destroy() // nothrow
    {
        delete this;
    }

    virtual void * get_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_local_deleter( sp_typeinfo_ const & ti ) = 0;
    virtual void * get_untyped_deleter() = 0;

    void add_ref_copy()
    {
        atomic_increment( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        return atomic_conditional_increment( &use_count_ ) != 0;
    }

    void release() // nothrow
    {
        if( atomic_decrement( &use_count_ ) == 1 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        atomic_increment( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( atomic_decrement( &weak_count_ ) == 1 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return atomic_load( &use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SYNC_HPP_INCLUDED

/* sp_counted_base_gcc_atomic.hpp
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
*/