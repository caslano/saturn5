#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_cw_ppc.hpp - CodeWarrior on PowerPC
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
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
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using CodeWarrior/PowerPC sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline void atomic_increment( register long * pw )
{
    register int a;

    asm
    {
loop:

    lwarx   a, 0, pw
    addi    a, a, 1
    stwcx.  a, 0, pw
    bne-    loop
    }
}

inline long atomic_decrement( register long * pw )
{
    register int a;

    asm
    {
    sync

loop:

    lwarx   a, 0, pw
    addi    a, a, -1
    stwcx.  a, 0, pw
    bne-    loop

    isync
    }

    return a;
}

inline long atomic_conditional_increment( register long * pw )
{
    register int a;

    asm
    {
loop:

    lwarx   a, 0, pw
    cmpwi   a, 0
    beq     store

    addi    a, a, 1

store:

    stwcx.  a, 0, pw
    bne-    loop
    }

    return a;
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    long use_count_;        // #shared
    long weak_count_;       // #weak + (#shared != 0)

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
        return static_cast<long const volatile &>( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_CW_PPC_HPP_INCLUDED

/* sp_counted_base_cw_ppc.hpp
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
*/