#ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_W32_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SPINLOCK_W32_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/smart_ptr/detail/sp_interlocked.hpp>
#include <boost/smart_ptr/detail/yield_k.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using Win32 spinlock")

#endif

// BOOST_COMPILER_FENCE

#if defined(__INTEL_COMPILER)

#define BOOST_COMPILER_FENCE __memory_barrier();

#elif defined( _MSC_VER ) && _MSC_VER >= 1310

extern "C" void _ReadWriteBarrier();
#pragma intrinsic( _ReadWriteBarrier )

#define BOOST_COMPILER_FENCE _ReadWriteBarrier();

#elif defined(__GNUC__)

#define BOOST_COMPILER_FENCE __asm__ __volatile__( "" : : : "memory" );

#else

#define BOOST_COMPILER_FENCE

#endif

//

namespace boost
{

namespace detail
{

class spinlock
{
public:

    long v_;

public:

    bool try_lock()
    {
        long r = BOOST_SP_INTERLOCKED_EXCHANGE( &v_, 1 );

        BOOST_COMPILER_FENCE

        return r == 0;
    }

    void lock()
    {
        for( unsigned k = 0; !try_lock(); ++k )
        {
            boost::detail::yield( k );
        }
    }

    void unlock()
    {
        BOOST_COMPILER_FENCE
        *const_cast< long volatile* >( &v_ ) = 0;
    }

public:

    class scoped_lock
    {
    private:

        spinlock & sp_;

        scoped_lock( scoped_lock const & );
        scoped_lock & operator=( scoped_lock const & );

    public:

        explicit scoped_lock( spinlock & sp ): sp_( sp )
        {
            sp.lock();
        }

        ~scoped_lock()
        {
            sp_.unlock();
        }
    };
};

} // namespace detail
} // namespace boost

#define BOOST_DETAIL_SPINLOCK_INIT {0}

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_W32_HPP_INCLUDED

/* spinlock_w32.hpp
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
*/