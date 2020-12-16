//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_TEARDOWN_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_TEARDOWN_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

namespace detail {

template<
    class Protocol, class Executor,
    class Handler>
class teardown_tcp_op
    : public beast::async_base<
        Handler, beast::executor_type<
            net::basic_stream_socket<
                Protocol, Executor>>>
    , public asio::coroutine
{
    using socket_type =
        net::basic_stream_socket<Protocol, Executor>;

    socket_type& s_;
    role_type role_;
    bool nb_;

public:
    template<class Handler_>
    teardown_tcp_op(
        Handler_&& h,
        socket_type& s,
        role_type role)
        : async_base<Handler,
            beast::executor_type<
                net::basic_stream_socket<
                    Protocol, Executor>>>(
            std::forward<Handler_>(h),
            s.get_executor())
        , s_(s)
        , role_(role)
    {
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            nb_ = s_.non_blocking();
            s_.non_blocking(true, ec);
            if(ec)
                goto upcall;
            if(role_ == role_type::server)
                s_.shutdown(net::socket_base::shutdown_send, ec);
            if(ec)
                goto upcall;
            for(;;)
            {
                {
                    char buf[2048];
                    s_.read_some(net::buffer(buf), ec);
                }
                if(ec == net::error::would_block)
                {
                    BOOST_ASIO_CORO_YIELD
                    s_.async_wait(
                        net::socket_base::wait_read,
                            beast::detail::bind_continuation(std::move(*this)));
                    continue;
                }
                if(ec)
                {
                    if(ec != net::error::eof)
                        goto upcall;
                    ec = {};
                    break;
                }
                if(bytes_transferred == 0)
                {
                    // happens sometimes
                    // https://github.com/boostorg/beast/issues/1373
                    break;
                }
            }
            if(role_ == role_type::client)
                s_.shutdown(net::socket_base::shutdown_send, ec);
            if(ec)
                goto upcall;
            s_.close(ec);
        upcall:
            if(! cont)
            {
                BOOST_ASIO_CORO_YIELD
                net::post(bind_front_handler(
                    std::move(*this), ec));
            }
            {
                error_code ignored;
                s_.non_blocking(nb_, ignored);
            }
            this->complete_now(ec);
        }
    }
};

} // detail

//------------------------------------------------------------------------------

template<class Protocol, class Executor>
void
teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    error_code& ec)
{
    if(role == role_type::server)
        socket.shutdown(
            net::socket_base::shutdown_send, ec);
    if(ec)
        return;
    for(;;)
    {
        char buf[2048];
        auto const bytes_transferred =
            socket.read_some(net::buffer(buf), ec);
        if(ec)
        {
            if(ec != net::error::eof)
                return;
            ec = {};
            break;
        }
        if(bytes_transferred == 0)
        {
            // happens sometimes
            // https://github.com/boostorg/beast/issues/1373
            break;
        }
    }
    if(role == role_type::client)
        socket.shutdown(
            net::socket_base::shutdown_send, ec);
    if(ec)
        return;
    socket.close(ec);
}

template<
    class Protocol, class Executor,
    class TeardownHandler>
void
async_teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    TeardownHandler&& handler)
{
    static_assert(beast::detail::is_invocable<
        TeardownHandler, void(error_code)>::value,
            "TeardownHandler type requirements not met");
    detail::teardown_tcp_op<
        Protocol,
        Executor,
        typename std::decay<TeardownHandler>::type>(
            std::forward<TeardownHandler>(handler),
            socket,
            role);
}

} // websocket
} // beast
} // boost

#endif

/* teardown.hpp
a8w2Bawz28ffL6I+eT3WWsPv+s9s2sw7WX92OiqT9VhwJqr6DCdk76m5Jm0T7/egdvL3czDsTKe9uF8wkjjStWoHo+91zdpTmCX3JZ5H1X7WU0/MnXVs2aOQQbnXs61B76xpu5a/d6GctW0HR1Wvb4u9mN/7IX7h/YDRda91+9C13i0DOmveyuC1qL0o//q3d47hrKglvN+E2oN6ChV0dpQ1TtfKEZY2/J2FytN1czt8a+f2ov8EvhIlyn+2VNPx1evpTuXveahKXVd3LdyD2szfWT/mHhRUJWozag/qEOodVMr9CVYmKge15P6GvfwNT8PT8DQ8DU/D0/D855+vZf1/6QLd/X/s6/8TXHv8N+rY5m2oE1A3ofZ0YexxrnffJz8fume7nczFqR1cymQ0eBFrGjYzd7QN5duPLfKTquXl3PBpKLd8bPX+bpHPqZaX88ML6KEaeTPPxqSQyk+rlpfzy/OIIyMfvhdY7Zg5ObNPgXlWUY2Ju1+1qf955EF7tf37snN4F+vbvz3bzHURJn2X591PKesQ18+r6h9v7+bdz3tQ9+Lv0zmE3aiirqTtvKD9vPxu+H5etTPYnInwpugvDdvfq/IDzBz9H0X/zcD9vs0txrer/CT6ImO/r/tcejxYPV/+rJhvEf00I9+htnRFptY93mYut8k5MvcbeB/BeMwHiXkH5uFjzXzxe+L2OF3rxPoOkWll1r7niP5kbMSY/LRC9u3Ceq4FPx57cfVsfAIctEfcm39ek7gh3rReuAP1fdzccU5Q/qF2CK8X1M4ep16QMrgTJfknoF5QeVMvqLw//4h8UbW8qRdUXtPYW49Mc8lrvaDyvnrEm3/UjqkXQvNapk+2KKAOSWzHWOcx1iH+NM8JSHNd1+GpV/IC6pWigHplyrlV9coNWq+cofliv3a/79B8cQvqTn537bnefFFRWCnXTJQXVlQUFvBnaXlBcUl+ZWFF7rix/ZaG5BV1B9dPIy3PQ11DutwQ/g0x8gOtpszndTLyieZcmZXO98PIDiHdF6JU1rXfZ1Xu/OIqt4td8hmU9/m4b+TD6xns1P79SCLtXzzGtHd/P06UtHfOblmp6e7sgZDwhH47uuZWpfGNvjTelehrE2ga5+UeRRqXhdYHuHN07QTkA9oJgWmMbEAbITyNkT/6NkJe7v9OGsfkmTQ2a2WyI2FrIMLWphz92pfgNShha3TC1kwcv7U7wWtrjt+amLA1In+XsyWWbbr/sVb3vfjUzv7N2r418Ps/DVvTE7ZmKGwNTdialbC1KcdvDY3Oo2p7mboiYB51pd5xsRp20HmebLgGjoSb4Th4EZwML4ZL4Fr+L1HzCngJXAnXw4vhBrhZzbfATXCb6smq5g6OMqfdB/ep/5JggfpvC3Jt4FadH/0uHK3zsflwO1wIb4SX6TzwFXAHRMl88E6dD96t88AaL9oG4PcD4mWOxss8jZdzNF7O1Xip1HjJgzLvrvEyH5aoeQUs0Hgp1HhZCLep+U2wBO5U/fdhhfGffqfgHQH+G67+y1b/na7+GqXxMxNOgGPgGXAsLIXj4flqvhxOhBfASfASOBleo+Zb4VR4g+pvg9ON/6SODc1X6eq/Nuq/thp/J6s/szT+Omj8ddT46wxL1LwCdtX466bxlwE3q/kW2A9uU/2tcBDkLpZ6zx3+X9/F8hXcw1KAmvlfdA/L0cyrHcsdLEHnTRQ8kGBtRO1GHUIl/KRh3qvhaXganoan4Wl4Gp6Gp+FpeBqehuc//Xwt8/9Lly2RBQDHYf4/zjX/z31T8gzUc0f6oFZ1w+1Rzli/3D1Qdft/bsEyZ+70XRmnx8A1d/p7sdNR540dN1Lxm7PHtNg=
*/