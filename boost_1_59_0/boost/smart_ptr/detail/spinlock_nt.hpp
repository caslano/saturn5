#ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_NT_HPP_INCLUDED
#define BOOST_SMART_PTR_DETAIL_SPINLOCK_NT_HPP_INCLUDED

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

#include <boost/assert.hpp>

#if defined(BOOST_SP_REPORT_IMPLEMENTATION)

#include <boost/config/pragma_message.hpp>
BOOST_PRAGMA_MESSAGE("Using single-threaded spinlock emulation")

#endif

namespace boost
{

namespace detail
{

class spinlock
{
public:

    bool locked_;

public:

    inline bool try_lock()
    {
        if( locked_ )
        {
            return false;
        }
        else
        {
            locked_ = true;
            return true;
        }
    }

    inline void lock()
    {
        BOOST_ASSERT( !locked_ );
        locked_ = true;
    }

    inline void unlock()
    {
        BOOST_ASSERT( locked_ );
        locked_ = false;
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

#define BOOST_DETAIL_SPINLOCK_INIT { false }

#endif // #ifndef BOOST_SMART_PTR_DETAIL_SPINLOCK_NT_HPP_INCLUDED

/* spinlock_nt.hpp
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
*/