#ifndef BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_PTHREADS_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_PTHREADS_HPP_INCLUDED

//
//  boost/detail/atomic_count_pthreads.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/assert.hpp>
#include <pthread.h>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using pthread_mutex atomic_count")

#endif

//
//  The generic pthread_mutex-based implementation sometimes leads to
//    inefficiencies. Example: a class with two atomic_count members
//    can get away with a single mutex.
//
//  Users can detect this situation by checking BOOST_AC_USE_PTHREADS.
//

namespace boost
{

namespace detail
{

class atomic_count
{
private:

    class scoped_lock
    {
    public:

        scoped_lock(pthread_mutex_t & m): m_(m)
        {
            BOOST_VERIFY( pthread_mutex_lock( &m_ ) == 0 );
        }

        ~scoped_lock()
        {
            BOOST_VERIFY( pthread_mutex_unlock( &m_ ) == 0 );
        }

    private:

        pthread_mutex_t & m_;
    };

public:

    explicit atomic_count(long v): value_(v)
    {
        BOOST_VERIFY( pthread_mutex_init( &mutex_, 0 ) == 0 );
    }

    ~atomic_count()
    {
        BOOST_VERIFY( pthread_mutex_destroy( &mutex_ ) == 0 );
    }

    long operator++()
    {
        scoped_lock lock(mutex_);
        return ++value_;
    }

    long operator--()
    {
        scoped_lock lock(mutex_);
        return --value_;
    }

    operator long() const
    {
        scoped_lock lock(mutex_);
        return value_;
    }

private:

    atomic_count(atomic_count const &);
    atomic_count & operator=(atomic_count const &);

    mutable pthread_mutex_t mutex_;
    long value_;
};

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_SMART_PTR_DETAIL_ATOMIC_COUNT_PTHREADS_HPP_INCLUDED

/* atomic_count_pt.hpp
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
*/