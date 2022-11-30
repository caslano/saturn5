#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SNC_PS3_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SNC_PS3_HPP_INCLUDED

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  detail/sp_counted_base_gcc_snc_ps3.hpp - PS3 Cell
//
//  Copyright (c) 2006 Piotr Wyderski
//  Copyright (c) 2006 Tomas Puverle
//  Copyright (c) 2006 Peter Dimov
//  Copyright (c) 2011 Emil Dotchevski
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  Thanks to Michael van der Westhuizen

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>
#include <inttypes.h> // uint32_t

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using PS3 sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline uint32_t compare_and_swap( uint32_t * dest_, uint32_t compare_, uint32_t swap_ )
{
    return __builtin_cellAtomicCompareAndSwap32(dest_,compare_,swap_);
}

inline uint32_t atomic_fetch_and_add( uint32_t * pw, uint32_t dv )
{
    // long r = *pw;
    // *pw += dv;
    // return r;

    for( ;; )
    {
        uint32_t r = *pw;

        if( __builtin_expect((compare_and_swap(pw, r, r + dv) == r), 1) )
        {
            return r;
        }
    }
}

inline void atomic_increment( uint32_t * pw )
{
    (void) __builtin_cellAtomicIncr32( pw );
}

inline uint32_t atomic_decrement( uint32_t * pw )
{
    return __builtin_cellAtomicDecr32( pw );
}

inline uint32_t atomic_conditional_increment( uint32_t * pw )
{
    // long r = *pw;
    // if( r != 0 ) ++*pw;
    // return r;

    for( ;; )
    {
        uint32_t r = *pw;

        if( r == 0 )
        {
            return r;
        }

        if( __builtin_expect( ( compare_and_swap( pw, r, r + 1 ) == r ), 1 ) )
        {
            return r;
        }
    }    
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    uint32_t use_count_;        // #shared
    uint32_t weak_count_;       // #weak + (#shared != 0)

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
        return const_cast< uint32_t const volatile & >( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SNC_PS3_HPP_INCLUDED

/* sp_counted_base_snc_ps3.hpp
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
*/