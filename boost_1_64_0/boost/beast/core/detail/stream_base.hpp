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
CM772u4/HcDuozvqL923Fyq2v944BMmog2RVd10Ov8TuFahfu0yMVDsxa4iVevu2fHAaTSSwnVezlgmkYmKNWmjBWqKgw3tkOEk7VauHP5Ltx+wT/zI9GKKOXHxzhLwPs1Zuveu9AvTHfGReIW+n4RUNhbZez5AUxN5re2/A6BL6CQCRtGNF6Bea0ejhUM5N8/Ma2DBuPu7rlP9WK3cUPRkur67P4ZnByEffLW9BR+xM5LBPgFuaqE3F8iWPT6T6XCazhvXamdbbUQXMG19DUoELcs7xumZz1WIT6bx89VEzJhM5LHJ9SVbmGxh3mj+4lNtNXl0udGBBtIvhSjOJiWQZD5bNcXoJTA12GKi7G1punQUk/92e+UUUyPgDpNfqlBuvEJmEg62QRN9ow8ZON4FG0X9L0P3eLI9jcudQBv/eVGK8tSNTQ1HL8lRr59EdgOTbI9QDEU+MmIm/es54Sd4GkyYTu7U42DayjfpsEDs1JFA55JL/BothtW+QkGeN9Bjc7xV5WI4NEzG3O/CA+Lmg0yPRbVoGXlqV28agyPvcDJ+axNtWSwa0bQ==
*/