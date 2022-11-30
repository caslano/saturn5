//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_SOFT_MUTEX_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_SOFT_MUTEX_HPP

#include <boost/assert.hpp>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

// used to order reads, writes in websocket streams

class soft_mutex
{
    int id_ = 0;

public:
    soft_mutex() = default;
    soft_mutex(soft_mutex const&) = delete;
    soft_mutex& operator=(soft_mutex const&) = delete;

    soft_mutex(soft_mutex&& other) noexcept
        : id_(boost::exchange(other.id_, 0))
    {
    }

    soft_mutex& operator=(soft_mutex&& other) noexcept
    {
        id_ = other.id_;
        other.id_ = 0;
        return *this;
    }

    // VFALCO I'm not too happy that this function is needed
    void
    reset()
    {
        id_ = 0;
    }

    bool
    is_locked() const noexcept
    {
        return id_ != 0;
    }

    template<class T>
    bool
    is_locked(T const*) const noexcept
    {
        return id_ == T::id;
    }

    template<class T>
    void
    lock(T const*)
    {
        BOOST_ASSERT(id_ == 0);
        id_ = T::id;
    }

    template<class T>
    void
    unlock(T const*)
    {
        BOOST_ASSERT(id_ == T::id);
        id_ = 0;
    }

    template<class T>
    bool
    try_lock(T const*)
    {
        // If this assert goes off it means you are attempting to
        // simultaneously initiate more than one of same asynchronous
        // operation, which is not allowed. For example, you must wait
        // for an async_read to complete before performing another
        // async_read.
        //
        BOOST_ASSERT(id_ != T::id);
        if(id_ != 0)
            return false;
        id_ = T::id;
        return true;
    }

    template<class T>
    bool
    try_unlock(T const*) noexcept
    {
        if(id_ != T::id)
            return false;
        id_ = 0;
        return true;
    }
};

} // detail
} // websocket
} // beast
} // boost

#endif

/* soft_mutex.hpp
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
*/