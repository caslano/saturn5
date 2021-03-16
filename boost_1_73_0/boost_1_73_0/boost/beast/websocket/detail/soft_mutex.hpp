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
K2WskrEgYzsYa2FMvwI70oxCz41MGhg41dordAn828F+EItKwA63HES5hPoGPm/dBBxtzqjeh3kZ2Gy4X0ZA0xyh7AH1Uy9D2zDLy9YUl9UuWVayKqk7NwDhG/sNJ75kxZ3FauEbCrI/YVd945dTGHMi3i/mGTup5UNdNaCZo1H6s0I7RaVqgtOlGn6CcuLk6DC+pFH8kkbxSxrFL0lhDmP1jP2Gsf2Mxe/dlzg5Ce8LmloRnbPxmEhcGIuW4Hk=
*/