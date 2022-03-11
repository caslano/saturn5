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