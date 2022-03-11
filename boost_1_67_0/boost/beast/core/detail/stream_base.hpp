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
        bool& b_;
        bool clear_ = true;

    public:
        ~pending_guard()
        {
            if(clear_)
                b_ = false;
        }

        explicit
        pending_guard(bool& b)
            : b_(b)
        {
            // If this assert goes off, it means you are attempting
            // to issue two of the same asynchronous I/O operation
            // at the same time, without waiting for the first one
            // to complete. For example, attempting two simultaneous
            // calls to async_read_some. Only one pending call of
            // each I/O type (read and write) is permitted.
            //
            BOOST_ASSERT(! b_);
            b_ = true;
        }

        pending_guard(
            pending_guard&& other) noexcept
            : b_(other.b_)
            , clear_(boost::exchange(
                other.clear_, false))
        {
        }

        void
        reset()
        {
            BOOST_ASSERT(clear_);
            b_ = false;
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