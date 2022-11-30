#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_X86_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_X86_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_gcc_x86.hpp - g++ on 486+ or AMD64
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
BOOST_PRAGMA_MESSAGE("Using g++/x86 sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline int atomic_exchange_and_add( int * pw, int dv )
{
    // int r = *pw;
    // *pw += dv;
    // return r;

    int r;

    __asm__ __volatile__
    (
        "lock\n\t"
        "xadd %1, %0":
        "=m"( *pw ), "=r"( r ): // outputs (%0, %1)
        "m"( *pw ), "1"( dv ): // inputs (%2, %3 == %1)
        "memory", "cc" // clobbers
    );

    return r;
}

inline void atomic_increment( int * pw )
{
    //atomic_exchange_and_add( pw, 1 );

    __asm__
    (
        "lock\n\t"
        "incl %0":
        "=m"( *pw ): // output (%0)
        "m"( *pw ): // input (%1)
        "cc" // clobbers
    );
}

inline int atomic_conditional_increment( int * pw )
{
    // int rv = *pw;
    // if( rv != 0 ) ++*pw;
    // return rv;

    int rv, tmp;

    __asm__
    (
        "movl %0, %%eax\n\t"
        "0:\n\t"
        "test %%eax, %%eax\n\t"
        "je 1f\n\t"
        "movl %%eax, %2\n\t"
        "incl %2\n\t"
        "lock\n\t"
        "cmpxchgl %2, %0\n\t"
        "jne 0b\n\t"
        "1:":
        "=m"( *pw ), "=&a"( rv ), "=&r"( tmp ): // outputs (%0, %1, %2)
        "m"( *pw ): // input (%3)
        "cc" // clobbers
    );

    return rv;
}

class BOOST_SYMBOL_VISIBLE sp_counted_base
{
private:

    sp_counted_base( sp_counted_base const & );
    sp_counted_base & operator= ( sp_counted_base const & );

    int use_count_;        // #shared
    int weak_count_;       // #weak + (#shared != 0)

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
        if( atomic_exchange_and_add( &use_count_, -1 ) == 1 )
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
        if( atomic_exchange_and_add( &weak_count_, -1 ) == 1 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        return static_cast<int const volatile &>( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_X86_HPP_INCLUDED

/* sp_counted_base_gcc_x86.hpp
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
*/