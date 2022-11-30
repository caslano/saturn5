#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SYNC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SYNC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_counted_base_sync.hpp - g++ 4.1+ __sync intrinsics
//
//  Copyright (c) 2007 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/config.hpp>
#include <limits.h>

#if defined( __ia64__ ) && defined( __INTEL_COMPILER )
# include <ia64intrin.h>
#endif

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using __sync sp_counted_base")

#endif

namespace boost
{

namespace detail
{

#if INT_MAX >= 2147483647

typedef int sp_int32_t;

#else

typedef long sp_int32_t;

#endif

inline void atomic_increment( sp_int32_t * pw )
{
    __sync_fetch_and_add( pw, 1 );
}

inline sp_int32_t atomic_decrement( sp_int32_t * pw )
{
    return __sync_fetch_and_add( pw, -1 );
}

inline sp_int32_t atomic_conditional_increment( sp_int32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    sp_int32_t r = *pw;

    for( ;; )
    {
        if( r == 0 )
        {
            return r;
        }

        sp_int32_t r2 = __sync_val_compare_and_swap( pw, r, r + 1 );

        if( r2 == r )
        {
            return r;
        }
        else
        {
            r = r2;
        }
    }    
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    sp_int32_t use_count_;        // #shared
    sp_int32_t weak_count_;       // #weak + (#shared != 0)

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
        return const_cast< sp_int32_t const volatile & >( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SYNC_HPP_INCLUDED

/* sp_counted_base_sync.hpp
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
*/