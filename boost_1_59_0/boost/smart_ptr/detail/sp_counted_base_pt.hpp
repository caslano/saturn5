#ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  detail/sp_counted_base_pt.hpp
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2005 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/sp_typeinfo_.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <pthread.h>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using pthread_mutex sp_counted_base")

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

    boost::int_least32_t use_count_;        // #shared
    boost::int_least32_t weak_count_;       // #weak + (#shared != 0)

    mutable pthread_mutex_t m_;

public:

    sp_counted_base(): use_count_( 1 ), weak_count_( 1 )
    {
// HPUX 10.20 / DCE has a nonstandard pthread_mutex_init

#if defined(__hpux) && defined(_DECTHREADS_)
        BOOST_VERIFY( pthread_mutex_init( &m_, pthread_mutexattr_default ) == 0 );
#else
        BOOST_VERIFY( pthread_mutex_init( &m_, 0 ) == 0 );
#endif
    }

    virtual ~sp_counted_base() // nothrow
    {
        BOOST_VERIFY( pthread_mutex_destroy( &m_ ) == 0 );
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
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        ++use_count_;
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
    }

    bool add_ref_lock() // true on success
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        bool r = use_count_ == 0? false: ( ++use_count_, true );
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
        return r;
    }

    void release() // nothrow
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        boost::int_least32_t new_use_count = --use_count_;
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        if( new_use_count == 0 )
        {
            dispose();
            weak_release();
        }
    }

    void weak_add_ref() // nothrow
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        ++weak_count_;
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
    }

    void weak_release() // nothrow
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        boost::int_least32_t new_weak_count = --weak_count_;
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        if( new_weak_count == 0 )
        {
            destroy();
        }
    }

    long use_count() const // nothrow
    {
        BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        boost::int_least32_t r = use_count_;
        BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );

        return r;
    }
};

} // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_PT_HPP_INCLUDED

/* sp_counted_base_pt.hpp
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
*/