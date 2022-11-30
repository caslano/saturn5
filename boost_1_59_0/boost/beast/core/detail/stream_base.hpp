//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_STREAM_BASE_HPP
#define BOOST_BEAST_CORE_DETAIL_STREAM_BASE_HPP

#include <boost/asio/steady_timer.hpp>
#include <boost/assert.hpp>
#include <boost/core/exchange.hpp>
#include <chrono>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

struct any_endpoint
{
    template<class Error, class Endpoint>
    bool
    operator()(
        Error const&, Endpoint const&) const noexcept
    {
        return true;
    }
};

struct stream_base
{
    using clock_type = std::chrono::steady_clock;
    using time_point = typename
        std::chrono::steady_clock::time_point;
    using tick_type = std::uint64_t;

    struct op_state
    {
        net::steady_timer timer;    // for timing out
        tick_type tick = 0;         // counts waits
        bool pending = false;       // if op is pending
        bool timeout = false;       // if timed out

        template<class... Args>
        explicit
        op_state(Args&&... args)
            : timer(std::forward<Args>(args)...)
        {
        }
    };

    class pending_guard
    {
        bool* b_ = nullptr;
        bool clear_ = true;

    public:
        ~pending_guard()
        {
            if(clear_ && b_)
                *b_ = false;
        }

        pending_guard()
        : b_(nullptr)
        , clear_(true)
        {
        }

        explicit
        pending_guard(bool& b)
        : b_(&b)
        {
            // If this assert goes off, it means you are attempting
            // to issue two of the same asynchronous I/O operation
            // at the same time, without waiting for the first one
            // to complete. For example, attempting two simultaneous
            // calls to async_read_some. Only one pending call of
            // each I/O type (read and write) is permitted.
            //
            BOOST_ASSERT(! *b_);
            *b_ = true;
        }

        pending_guard(
            pending_guard&& other) noexcept
            : b_(other.b_)
            , clear_(boost::exchange(
                other.clear_, false))
        {
        }

        void assign(bool& b)
        {
            BOOST_ASSERT(!b_);
            BOOST_ASSERT(clear_);
            b_ = &b;

            // If this assert goes off, it means you are attempting
            // to issue two of the same asynchronous I/O operation
            // at the same time, without waiting for the first one
            // to complete. For example, attempting two simultaneous
            // calls to async_read_some. Only one pending call of
            // each I/O type (read and write) is permitted.
            //
            BOOST_ASSERT(! *b_);
            *b_ = true;
        }

        void
        reset()
        {
            BOOST_ASSERT(clear_);
            if (b_)
                *b_ = false;
            clear_ = false;
        }
    };

    static time_point never() noexcept
    {
        return (time_point::max)();
    }

    static std::size_t constexpr no_limit =
        (std::numeric_limits<std::size_t>::max)();
};

} // detail
} // beast
} // boost

#endif

/* stream_base.hpp
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
*/