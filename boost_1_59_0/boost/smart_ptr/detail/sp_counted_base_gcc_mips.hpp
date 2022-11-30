#ifndef BOOST_DETAIL_SP_COUNTED_BASE_GCC_MIPS_HPP_INCLUDED
#define BOOST_DETAIL_SP_COUNTED_BASE_GCC_MIPS_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_gcc_mips.hpp - g++ on MIPS
//
//  Copyright (c) 2009, Spirent Communications, Inc.
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
//  Lock-free algorithm by Alexander Terekhov
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/smart_ptr/detail/sp_obsolete.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using g++/MIPS sp_counted_base")

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

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
#if !defined(__mips_isa_rev) || (__mips_isa_rev < 6)
        ".set mips2\n\t"
#endif
        "ll %0, %1\n\t"
        "addiu %0, 1\n\t"
        "sc %0, %1\n\t"
        ".set pop\n\t"
        "beqz %0, 0b":
        "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw )
    );
}

inline int atomic_decrement( int * pw )
{
    // return --*pw;

    int rv, tmp;

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
#if !defined(__mips_isa_rev) || (__mips_isa_rev < 6)
        ".set mips2\n\t"
#endif
        "ll %1, %2\n\t"
        "addiu %0, %1, -1\n\t"
        "sc %0, %2\n\t"
        ".set pop\n\t"
        "beqz %0, 0b\n\t"
        "addiu %0, %1, -1":
        "=&r"( rv ), "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw ):
        "memory"
    );

    return rv;
}

inline int atomic_conditional_increment( int * pw )
{
    // if( *pw != 0 ) ++*pw;
    // return *pw;

    int rv, tmp;

    __asm__ __volatile__
    (
        "0:\n\t"
        ".set push\n\t"
#if !defined(__mips_isa_rev) || (__mips_isa_rev < 6)
        ".set mips2\n\t"
#endif
        "ll %0, %2\n\t"
        "beqz %0, 1f\n\t"
        "addiu %1, %0, 1\n\t"
        "sc %1, %2\n\t"
        ".set pop\n\t"
        "beqz %1, 0b\n\t"
        "addiu %0, %0, 1\n\t"
        "1:":
        "=&r"( rv ), "=&r"( tmp ), "=m"( *pw ):
        "m"( *pw ):
        "memory"
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

#endif  // #ifndef BOOST_DETAIL_SP_COUNTED_BASE_GCC_MIPS_HPP_INCLUDED

/* sp_counted_base_gcc_mips.hpp
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
*/