#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED

//
//  detail/sp_counted_base_aix.hpp
//   based on: detail/sp_counted_base_w32.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//  Copyright 2006 Michael van der Westhuizen
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//
//  Thanks to Ben Hitchings for the #weak + (#shared != 0)
//  formulation
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/config.hpp>
#include <builtins.h>
#include <sys/atomic_op.h>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using AIX sp_counted_base")

#endif

namespace boost
{

namespace detail
{

inline void atomic_increment( int32_t* pw )
{
    // ++*pw;

    fetch_and_add( pw, 1 );
}

inline int32_t atomic_decrement( int32_t * pw )
{
    // return --*pw;

    int32_t originalValue;

    __lwsync();
    originalValue = fetch_and_add( pw, -1 );
    __isync();

    return (originalValue - 1);
}

inline int32_t atomic_conditional_increment( int32_t * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int32_t tmp = fetch_and_add( pw, 0 );
    for( ;; )
    {
        if( tmp == 0 ) return 0;
        if( compare_and_swap( pw, &tmp, tmp + 1 ) ) return (tmp + 1);
    }
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int32_t use_count_;        // #shared
    int32_t weak_count_;       // #weak + (#shared != 0)

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
        if( atomic_decrement( &use_count_ ) == 0 )
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
        if( atomic_decrement( &weak_count_ ) == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return fetch_and_add( const_cast<int32_t*>(&use_count_), 0 );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_AIX_HPP_INCLUDED

/* sp_counted_base_aix.hpp
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
*/