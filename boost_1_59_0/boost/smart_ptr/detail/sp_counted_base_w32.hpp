#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_W32_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_W32_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_w32.hpp
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

#include <boost/smart_ptr/detail/sp_interlocked.hpp>
#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/config/workaround.hpp>
#include <boost/config.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using Win32 sp_counted_base")

#endif

namespace boost
{

namespace detail
{

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
        BOOST_SP_INTERLOCKED_INCREMENT( &use_count_ );
    }

    bool add_ref_lock() // true on success
    {
        for( ;; )
        {
            long tmp = static_cast< long const volatile& >( use_count_ );
            if( tmp == 0 ) return false;

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1200 )

            // work around a code generation bug

            long tmp2 = tmp + 1;
            if( BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE( &use_count_, tmp2, tmp ) == tmp2 - 1 ) return true;

#else

            if( BOOST_SP_INTERLOCKED_COMPARE_EXCHANGE( &use_count_, tmp + 1, tmp ) == tmp ) return true;

#endif
        }
    }

    void release() // nothrow
    {
        if( BOOST_SP_INTERLOCKED_DECREMENT( &use_count_ ) == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        BOOST_SP_INTERLOCKED_INCREMENT( &weak_count_ );
    }

    void weak_release() // nothrow
    {
        if( BOOST_SP_INTERLOCKED_DECREMENT( &weak_count_ ) == 0 )
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

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_W32_HPP_INCLUDED

/* sp_counted_base_w32.hpp
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
*/