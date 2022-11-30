#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_PPC_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_PPC_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_gcc_ppc.hpp - g++ on PowerPC
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
BOOST_PRAGMA_MESSAGE("Using g++/PowerPC sp_counted_base")

#endif

BOOST_SP_OBSOLETE()

namespace boost
{

namespace detail
{

inline void atomic_increment( int * pw )
{
    // ++*pw;

    int tmp;

    __asm__
    (
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "addi %1, %1, 1\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b":

        "=m"( *pw ), "=&b"( tmp ):
        "r"( pw ), "m"( *pw ):
        "cc"
    );
}

inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv;

    __asm__ __volatile__
    (
        "sync\n\t"
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "addi %1, %1, -1\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b\n\t"
        "isync":

        "=m"( *pw ), "=&b"( rv ):
        "r"( pw ), "m"( *pw ):
        "memory", "cc"
    );

    return rv;
}

inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv;

    __asm__
    (
        "0:\n\t"
        "lwarx %1, 0, %2\n\t"
        "cmpwi %1, 0\n\t"
        "beq 1f\n\t"
        "addi %1, %1, 1\n\t"
        "1:\n\t"
        "stwcx. %1, 0, %2\n\t"
        "bne- 0b":

        "=m"( *pw ), "=&b"( rv ):
        "r"( pw ), "m"( *pw ):
        "cc"
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
        return static_cast<int const volatile &>( use_count_ );
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_GCC_PPC_HPP_INCLUDED

/* sp_counted_base_gcc_ppc.hpp
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
*/