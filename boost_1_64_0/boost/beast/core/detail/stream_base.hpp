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
HitLj7UiKwnL1vUjcpA62vVl3T/Ff7KP/076f6T/DfpZp3q8+YpnIV4O15t4Fu7lfsVap8UVRXL+Snddl8v0/OOpQnsc69Wbtg/9qKlX4cefZd6Q4+uVQlsudWZ8hp2L8pwOuYZHVug6mxvlkW0yaU4AzRmG7Md2DQruFbZj167h24WiDkK3V0wjY76k8T4LfgNPv8MVRqo2939PPSyj3/u8KxV5PuKpN/WzlmcPkWftdj7POcoz61V/eeaXVtnKc67QjqT8vGljTbyRhzb0c/IgZV78Ksvs0wbSedZiiOnd7chE8OJT5sVFVektPHNIHyJlU628U4S28AysZ3lyOGZOg/sFZa6zKU/+lGzb9y+Uh/Q5yDecsmv1jCxdviyfdx7z2VVVYdzrwvLtApcXp1Tka3blm20M/Q5lZBrkNLSDyxgXzg1xLOMEuNkoY4FdGadOzsdvhzIyDXIa3sFlfCjcX44HoIxr7Mo4q2U5rtlGcqzneYt7sYzZcL8Zc/2v25SxZEnhQpv+wTIyzUSRY4Q+b4tnRskzjDS42yDVU2iypBRLPe96fOecITTdZcxcAxkuQ8HWYfAO77KzjHlt5N+0/mfti3zm8FwrKZ/1HZXnCxZRJgXsn25/mYxsoX+SfrbRP/WzYu3rzfrOkBjTOx3Hxgclvpe8/7+Gm69AWc5MxrvD9ngAJEXgUdAlzcy/WR5nJLRdHk7t4YUeHuJ55H0f9v1GG95b6ftMk62Gmvjf9Y1m/gfb8J9uxJP/+gjw3wNliib/iSEG/0Oc+I/v2wH8c2Q/gPzneceVN/z5b3VckTQ5ariJ/zoT/2k2/F9j5r8H+Ed5ntP8h7bIf/0OHcB/lE/9c8xqsOG/5TGLaXzqf9j6Zv4H2vCfJPHkPxL8I991baz/85L/Ov/TyH/fnn76jCzE5K634b+qrNI4hHfpoqJF7qWl5VX+siDf3vQjtBxOFX830559t9u0V4L0afRrettv+qOAyyW+K/2kB2exhhxBsAYyvMAzjnQJ397zrt9W3dlmboT7yFlmvHsdtZ7v5/2s8hwQw+8mKE8j7dtJeHfxlyfOIy8urC4Dli4uqqzKLy9d5ChPpt/VtJfEDXo+Z0zxaaqbtKUk1OtaOC2D7r3CgyPUVsvBs19E7i1yaNBysM4r1FEOwcw4iPMeaoNVDsjH6f2TtMEtvX9Osn//tJ67OL+XhziddTKUZYn0KcuS0spKTCSaVF3HsjFteqv6udN8zNgN9vMxTSzrPdQ3bocbEYf+4VPW8qLD2Fb0mKL16WqhPUsNwf+T4LxnZ37L/Rm/9vRgYRt0WvN8wS29PRFHca6oDK4SP7LetJbNXYGxwSNFPad1SWTz/ijKkOmS9Nxngfj3Vwkq2P+di7wdIDRzVDzngXJ0PjuABn2D560vKpLhiTZVSUMd9iD454k/Q+5ziOc+stGE3/iQfrqMJ7+iTgaA9wsNHXWCvJcorx6ajHFmN0jnsshW518tfQvysOzFyvRpI7Ect6mjkp/md7lDhJZlRns6UsqrVIjP+bQF8db5vVLWWYN9nWEfTGFVUQt11uBTZ+otz/xfXAt19pukmaliTXXW0IY6a/Cps5/FP8Kpzki/h9RZHeprQxzrbJd/Zp3FvWVfZzEJ9nVW85ZtnVUvKCtd6NzPmM5UZ7VtqLPL3/KpM8mn9ToDjaXOLoHfuc5IzzpbhLZ6ep9/dp2tdqizyL5KLoJKgBuO9pf0ts8Z7YWHFpkeME7Pe6bra1pXWrJ0kWldifGOc+VDEG+eK99F/K42P0t9n/2RWkZSDgvvq8n0eD5fd/KuBfnyXrSwuqK06nAudjg9W5lu/F9e61iO9Hy2WvTcvok=
*/